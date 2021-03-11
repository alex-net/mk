<?php 

/**
 * отображение страницы каталога для соответствующего родительского элемента
 * @param int $ptid номер родительского термина 
 * @return array массив для рендеринга страницы 
 */
function catalog_list_cb($ptid=0)
{
	$res=getOneLevelOfCatalog($ptid);
	if (!$res)
		return [];
	
	$terms=[];
	foreach($res as $v){
		$img=field_get_items('taxonomy_term',$v,'field_pic_category');
		$terms['t-'.$v->tid]=[
			'tid'=>$v->tid,
			'name'=>$v->name,
			'img'=>file_create_url($img[0]['uri']),
			'href'=>url('taxonomy/term/'.$v->tid),
			'childs'=>$v->childs,
			'childs-list'=>$v->childslist,
			'weight'=>$v->weight,
		];
	}

	return [
		'cat'=>[
			'#theme'=>'catalogpage',
			'terms'=>$terms,
		]
	];
}

// =====================================================================
/**
 * пробуем вернуть подуровни каталога
 * @return мааси рендеринга ajax запроса 
 */
function catalog_subitem_list_jscb()
{
	$cmd=[];
	$items=[];
	if (isset($_POST['id'])){
		$items=catalog_list_cb($_POST['id']);
		$items=empty($items['cat']['terms'])?[]:$items['cat']['terms'];
	}
	//dfb($items,'$items');
	$cmd[]=[
		'command'=>'put-content-to-front-catalog-page',
		'items'=>$items,
		'for'=>$_POST['id'],
	];
	return ['#type'=>'ajax','#commands'=>$cmd];
}


// =====================================================================
/**
 * Страница Хиты продаж 
 */
function bestsellers_cb()
{
	$out=[];
	// Предлагаем Вашему вниманию наши хиты продаж.
	// загрузить метки товаров 
	$res=getTopSalesNids(40);
	
	if ($res){
		$nn=node_view_multiple(node_load_multiple($res));
		$out=array_merge($out,$nn);
		$out['nodes']=array_merge($out['nodes'],[
			'#type'=>'container',
			'#attributes'=>[
				'class'=>['elements-list','products'],
			],
		]);
	}
	return $out;
}


//=======================================================
/**
 * страница  списка Акций 
 */
function akciilist_page_cb()
{
	$out=[];
	$els=getActionProdag();
	$fd=variable_get('discounts config',[]);

	if ($els &&  !empty($fd['mess-on-page-exist']) || !$els && !empty($fd['mess-on-page-void']))
		$out['ins']=['#markup'=>$els?$fd['mess-on-page-exist']:$fd['mess-on-page-void'],];
	if ($els){
		$ns=node_view_multiple(node_load_multiple(array_keys($els)));
		$ns=$ns['nodes'];
		$ns['#type']='container';
		$ns['#attributes']=array('class'=>array('elements-list','products'));
		$out['prodsist']=$ns;
	}

	return $out;
}


/**
 * позгрузить  контент ноды во всплывашку  (применяется вид default)
 * @param  object $n Объект ноды который надо загрузить 
 * @return [type]    [description]
 */
function _get_node_in_popup_cb($n)
{
	$cmd=[];
	// просмотр через объявленный вид ..
	$nw=node_view($n,'inpopup');
	//$nw['#prefix']='<div class="container-fluid col-lg-28">';
	//$nw['#suffix']='</div>';
	$cmd[]=[
		'command'=>'show_in_popup',
		'content'=>render($nw),
		'wrapCSS'=>'node-in-popup node-'.$n->nid.' node-'.$n->type,
		'autoHeight'=>true,
		//'scrolling'=>'no',
		'autoSize'=>false,
		//'fitToView'=>false,
		'width'=>'auto',
		//'type'=>'html',
		
		
		'tpl'=>[
			'closeBtn'=>'<a title="Закрыть" class="fancybox-item fancybox-close" href="javascript:;"></a>',
		],
	];
	return ['#type'=>'ajax','#commands'=>$cmd];
}

/**
 * показываем новости .. (страница .) 
 */
function content_view_cb(string $ct)
{
	$res=db_select('node','n')->extend('PagerDefault');
	$res->limit(20);
	$res->condition('n.type',$ct);
	$res->condition('n.status',1);
	$res->fields('n',['nid']);
	$res->orderBy('n.created','desc');
	$res=$res->execute()->fetchCol();

	return [
		'nodes'=>node_view_multiple(node_load_multiple($res)),
		'pager'=>[
			'#theme'=>'pager',
		],
	];
}
// ========================================================
// подгрузить форму во всплывашку ..
function _get_form_in_popup_cb(){
	$cmd=array();
	$post=$_POST;
	if (!empty($post['fromclient'])){
		$post=$post['fromclient'];
		// отдать форму ... 
		
		$fn='';
		foreach($post as $x=>$y)
			if (preg_match('#^openform(\w+)$#', $x,$f))
				$fn=end($f);
		
		$f=$fn;
		$classfancy=array('form-in-popup form-'.$f);
		
		switch($fn){
			case 'NewOtziv':
				$res=db_select('node','n');
				$res->condition('n.nid',$post['from-nid']);
				$res->fields('n',array('type'));
				$res=$res->execute()->fetch(PDO::FETCH_ASSOC);

				$com=(object)array(
					'nid'=>$post['from-nid'],
				);
				$classfancy=array_merge($classfancy,array('product','full','node'));
				$fn=null;
				if (!empty($res))
					$fn=drupal_get_form('comment_node_'.$res['type'].'_form',$com);

			break;
			default:
				$fn='mkm_'.strtolower($fn).'_form';
				if (function_exists($fn))
					$fn=drupal_get_form($fn,$post);
				else
					$fn=null;

		}
		
		if ($fn)
			
			$cmd[]=array(
				'command'=>'show_in_popup',
				'content'=>render($fn),
				'wrapCSS'=>implode(' ',$classfancy),
				//'scrolling'=>'no',
				'autoSize'=>true,
				'autoHeight'=>true,
				//'fitToView'=>false,
				//'fixed'=>false,
				'tpl'=>array(
					'closeBtn'=>'<a title="Закрыть" class="fancybox-item fancybox-close" href="javascript:;"></a>',
				),
				
			);
		
	}
	return array('#type'=>'ajax','#commands'=>$cmd);
}

// ========================================================
// вернуть шаблон в ответ на аякс 
function get_tpl_in_popup_cb(){
	$cmd=[];
	//dfb($_POST);
	//dsm($_POST);
	if (!empty($_POST['showTplInPopup'])){
		$tpl=variable_get('tpls--'.$_POST['showTplInPopup'],'');
		$cmd[]=array(
			'command'=>'show_in_popup',
			//'content'=>theme(str_replace('-','_',$_POST['showTplInPopup'])),
			'content'=>$tpl,
			'wrapCSS'=>'tpl-in-popup',
			//'width'=>'auto',
			//'type'=>'html',
			'autoHeight'=>true,
			//'scrolling'=>'no',
			//'autoSize'=>false,
			//'fitToView'=>false,

			///'fixed'=>false,
			'tpl'=>array(
				'closeBtn'=>'<a title="Закрыть" class="fancybox-item fancybox-close" href="javascript:;"></a>',
			),
			
		);
	}
	return ['#type'=>'ajax','#commands'=>$cmd];
}
//=============================================================
// подгрузить список коментов ..куда надо .. 
function _get_comments_list_cb(){
	$cmd=array();
	if (empty($_POST['mkcc']))
		return array('#type'=>'ajax','#commands'=>$cmd);
	$mkcc=$_POST['mkcc'];
	
	$out=_getcomentcontent($mkcc);
	
	$cmd[]=ajax_command_html('.comment-wrapper .comments-wrap',render($out));
	return array('#type'=>'ajax','#commands'=>$cmd);
}



// ===========================================================================





/**
 * возвращаем списки нод отрендеренные .. 
 */
function get_nodes_list_jscb()
{
	$nids=$_POST['nids']??[];
	$mode=$_POST['mode']??'teaser';
	$selector=$_POST['selector']??'';

	$cmd=[];

	if ($nids && $selector){
		$nids=node_view_multiple(node_load_multiple($nids),$mode);
		$html=render($nids);
		$cmd[]=[
			'command'=>'place-nodes-list',
			'placeto'=>$selector,
			'html'=>$html,
		];
	}

	return ['#type'=>'ajax','#commands'=>$cmd];
}

/**
 * подгрузка товара по аяксу ..  по кнопке Ещё ..
 * @return [type] [description]
 */
function get_next_content_elements_jscb()
{
	$cmds=[];
	$post=$_POST;
	
	$page=ceil($post['exists']/$post['perpage'])+$post['curpage'];

	$prods=getProductsListForTaxonomy($post['curtid'],$page,$post['sort']);
	$res='';
	if ($prods){
		$res= node_view_multiple(node_load_multiple($prods));
		$res=render($res);
		$res=str_replace('destination='.current_path(), 'destination='.drupal_lookup_path('source',ltrim(parse_url($_SERVER['HTTP_REFERER'],PHP_URL_PATH),'/')), $res);
	}
	$cmd=[
		'command'=>'get-next-content-elements',
		'nids'=>$res,
		
	];
	$cmds[]=$cmd;
	return ['#type'=>'ajax','#commands'=>$cmds];
}


/**
 * Просмотр катлога товаров раздел такосномии ..
 */
function tovarsList_cb($term)
{

	taxonomy_term_view($term);

	$uri = entity_uri('taxonomy_term', $term);
	drupal_add_html_head_link([
		'rel' => 'canonical',
		'href' => url($uri['path'], $uri['options']),
	], TRUE);

	// Set the non-aliased path as a default shortlink.
	drupal_add_html_head_link([
		'rel' => 'shortlink',
		'href' => url($uri['path'], array_merge($uri['options'], ['alias' => TRUE,])),
	], TRUE);

	
	$h1=field_get_items('taxonomy_term',$term,'field_h1');
	if ($h1)
		drupal_set_title($h1[0]['value']);
	///dsm();
	$qp=drupal_get_query_parameters();
	// делаем сортировку по умолчанию ..
	$sorttype=$qp['sort']??'rating';
	unset($qp['sort']);
	$res=getProductsListForTaxonomy($term->tid,0,$sorttype);
	
	if ($res){
		$res=node_view_multiple(node_load_multiple($res));
		$res['#type']='container';
		$res['#attributes']=['class'=>['elements-list','products']];
	}
	$textunderproducts=field_get_items('taxonomy_term',$term,'field_text_under_products');
	//if (!empty($textunderproducts[0]['value']))
	
	
	$st=[
		'rating'=>'По рейтингу',
		'priceup'=>'По возрастанию цены ',
		'pricedown'=>'По убыванию цены',
	];
	$sortlinks=[];
	foreach($st as $k=>$v){
		$class=$k;
		if ($k==$sorttype)
			$class.=' current';
		
		$sortar=$k=='rating'?[]:['sort'=>$k];

		$sortlinks['link-'.$class]=['html'=>true,'title'=>$v,'href'=>current_path(),'query'=>array_merge($qp,$sortar) ];
	}
	
	$textBetweenCatProd=field_get_items('taxonomy_term',$term,'field_text_between_cat_prods');
	//dsm($term->description,'$term');
	$text=$term->description.($textBetweenCatProd[0]['value']??'');

	
	// хиты продаж
	foreach(['hits'=>'field_mit_tovar_buy','zakaz'=>'field_tovar_analogs'] as $v=>$f){
		$$v=field_get_items('taxonomy_term',$term,$f);
		if ($$v)
			foreach($$v as $x=>$y)
				if ($y)
					$$v[$x]=$y['nid'];
	}
	

	//dsm($term);
	return [
		'button-show-filter'=>[
			'#access'=>!empty($res),
			'#type'=>'container',
			'#attributes'=>[
				'class'=>['btn-show-filter'],
			],
			'text'=>['#markup'=>'фильтр'],
			'#weight'=>-100,
		],
		'text'=>[
			'#access'=>!empty($text),
			'#type'=>'container',
			'#attributes'=>['class'=>['text-between-cat-prods']],
			'val'=>[
				'#markup'=>$text,
			],
		],
		'sort'=>[
			'#access'=>!empty($res),
			'#type'=>'container',
			'#attributes'=>['class'=>['products-sort-block']],
			'links'=>[
				'#theme'=>'links',
				'#links'=>$sortlinks,
				'#heading'=>['text'=>'Сортировать:','level'=>'span' ,'class'=>['header-block']],
			],
		],
		'products'=>$res,
		'pager'=>['#theme'=>'pager'],
		'products-at-akca'=>getMarkupsOfAkciiProducts($term->tid),
		'hits-pro-list'=>$hits?carouselMarkupGen($hits,'hits-prods-list','Хиты продаж'):[],
		'zakaz-pro-list'=>$zakaz?carouselMarkupGen($zakaz,'zakaz-prods-list','Товары под заказ'):[],
		//'hits-pro-list'=>$hits?getMarkupsOfAkciiProducts($hits,'hits-prods-list','Хиты продаж'),
		'undertext'=>[
			'#access'=>empty($qp['page']),//$term->tid==75 && empty($qp['page']) || $term->tid!=75,
			'#type'=>'container',
			'#attributes'=>['class'=>['text-undertext']],
			'text'=>[
				'#markup'=>$textunderproducts[0]['value']??'',
			],
			
		]
	];
}
