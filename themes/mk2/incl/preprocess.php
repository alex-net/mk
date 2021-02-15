<?php 

/**
 * препроыесс массива страницы 
 * @param  array &$vars Массив страницы 
 */
function mk2_preprocess_page(&$vars)
{
	// загружаем файлик который нужен для всплывашуек ..
	drupal_add_library('mkmod','myajaxcommands');
	drupal_add_library('mklibs','animate');

	$prevpath=drupal_lookup_path('source',trim(parse_url($_SERVER['HTTP_REFERER'],PHP_URL_PATH),'/') );
	if ($prevpath && preg_match('#taxonomy/term/(\d+)#',$prevpath,$tid)){
		$t=&drupal_static('prev-term-id');
		$t=end($tid);

		//dsm($tid);
	}




	// меню в шапка .. 
	$vars['menuSiteHead']=menu_tree('menu-main');
	array_unshift($vars['menuSiteHead'],[
		'#theme'=>'menu_link__menu_main',
		'#title'=>'каталог',
		'#href'=>'',
		'#attributes'=>[
			'class'=>['item-catalog'],
			'title'=>'Каталог',
		],
		'#below'=>[],
		'#localized_options'=>[],
	]);
	foreach(element_children($vars['menuSiteHead']) as $x)
		switch($vars['menuSiteHead'][$x]['#href']){
			// выделяем пункт Акции 
			case 'discounts':
				$vars['menuSiteHead'][$x]['#attributes']['class'][]='item-akcia';
				break;
			case 'search':
				$vars['menuSiteHead'][$x]['#title']='';
				$vars['menuSiteHead'][$x]['#href']='';
				$vars['menuSiteHead'][$x]['#attributes']['class'][]='search-but';
				break;
		}// f002
		//dsm($vars['menuSiteHead']);
		//
	// показываем форму поиска ..
	//$vars['sf']=drupal_get_form('search_form');	
	$vars['sfhead']=drupal_get_form('sf_1');	
	// форма поиска в подвале .. 
	$vars['sffooter']=drupal_get_form('sf_2');	

	// выкатываем первый уровень каталога (ориентировочно в подвал )
	$vars['catl0']=getOneLevelOfCatalog();//catalog_list_cb();


	// делаем обёртку на списках товаров .. .
	if (preg_match('#^taxonomy/term/\d+$#', current_path()) ){
		$vars['classes_array'][]='test';

		// запрос элементов .. на странице .. 
		if (!empty($vars['page']['content']['system_main']['nodes'])){
			$vars['page']['content']['system_main']['nodes']['#type']='container';
			$vars['page']['content']['system_main']['nodes']['#attributes']['class']=array_merge($vars['page']['content']['system_main']['nodes']['#attributes']['class']??[],['elements-list','products']);
			
			if (!empty($vars['page']['content']['views_term_description_category-block']))
				$vars['page']['content']['views_term_description_category-block']['#weight']=-50;
			uasort($vars['page']['content'], 'element_sort');
		}
		if (!empty($vars['page']['content']['addmi_catalog_children_terms'])){
			$vars['page']['content']['system_main']['childs']=$vars['page']['content']['addmi_catalog_children_terms'];
			unset($vars['page']['content']['addmi_catalog_children_terms']);
		}
		// перемещаем текст под товары 
		if (!empty($vars['page']['content']['system_main']['term_heading']['term']['field_text_under_products'])){
			$vars['page']['content']['system_main']['undernodes']=$vars['page']['content']['system_main']['term_heading']['term']['field_text_under_products'];
			unset($vars['page']['content']['system_main']['term_heading']['term']['field_text_under_products']);

		}
	}

	// пробуем сделать прокрутку на странице каталога если находимся на странице отличной от первой . 
	if (preg_match('#^taxonomy/term/\d+$#',current_path())){
		$q=drupal_get_query_parameters();
		if (!empty($q['page']) )
			drupal_add_js(['calaog-scroller'=>true],'setting');
	}


	// загрузить   данные по складам в jS
	$SkladList=getSkladList();
	if ($SkladList){
		
		drupal_add_js(array(
			'skladsList'=>$SkladList,
		),'setting');
	}

}

/**
 * Препроцесс массива Блоков 
 */
function mk2_preprocess_block(&$vars)
{
	//dsm($vars['block']->delta,'bb');
	switch($vars['block']->delta){
		// добавим ссылку
		case 'top-sales':
			//dsm($vars);
			
			$vars['title_attributes_array']['class'][]='all-link';
			$vars['block']->subject.=l('Все товары','bestsellers',['attributes'=>['class'=>['all']]]);//'<a class="all" href="/">adasd</a>';
		case 12:	
			drupal_add_library('mklibs','slick');
		break;
		case 'news-list':
			//dsm($vars);
			$vars['title_attributes_array']['class'][]='all-link';
			$vars['block']->subject.=l('Все новости','news',['attributes'=>['class'=>['all']]]);
		break;
		case 'articles-list':
			//dsm($vars);
			$vars['title_attributes_array']['class'][]='all-link';
			drupal_add_library('mklibs','slick');
			$vars['block']->subject.=l('Все статьи','articles',['attributes'=>['class'=>['all']]]);
		break;
		case 'menu-menu-futer':
			$vars['content']=preg_replace('#<a[^>]*href="/"[^>]*>(.*?)</a>#iusm','<h2>$1</h2>',$vars['content']);
		// 
			//dsm($vars['content']);
		break;
	}
}

/**
 * препроцесс  ноды .. 
 */
function mk2_preprocess_node(&$vars)
{
	$vars['classes_array'][]='node-'.$vars['view_mode'];

	// раскраска таблицы информация .. 
	if ($vars['node']->type=='product_display'){
		if (!empty($vars['content']['field_parameters_product']))
			foreach(element_children($vars['content']['field_parameters_product']) as $i)
				foreach(['статус'=>'green','Получение'=>'colored'] as $x=>$y)
				if(preg_match('#'.$x.'#ius', $vars['content']['field_parameters_product'][$i]['#item']['first'])){
					$vars['content']['field_parameters_product'][$i]['#item']['second']='<span class="'.$y.'">'.$vars['content']['field_parameters_product'][$i]['#item']['second'].'</span>';
				}
		
		// определить акционные товары ... 
		if (current_path()!='discounts'){
			$disconttime=_checkdiscont($vars['node']);
			if ($disconttime)
				$vars['classes_array'][]='akcia-to-do';	
		}
		if (current_path()!='bestsellers'){
			$hits=getTopSalesNids(40);
			if ($hits && in_array($vars['node']->nid, $hits))
				$vars['classes_array'][]='hit-to-do';	
		}
		// получить  метки товара .. 
		$merks=field_get_items('node',$vars['node'],'field_marks_products');
		// 224 новинка ..
		for($i=0;$i<count($merks);$i++)
			$vars['classes_array'][]='marks-tid-'.$merks[$i]['tid'];
		
	}


	
	
	if ($vars['node']->type=='product_display' && $vars['view_mode']=='full' ){
		
		// подсчёт звёзд по коментариям .. 
		$comments=comment_load_multiple([],['nid'=>$vars['nid']]);
		$stars=0;
		if ($comments){
			foreach($comments as $c){
				$p=field_get_items('comment',$c,'field_rating');
				$stars+=intval($p[0]['value']);
			}
			$stars/=count($comments);
		}
		// узнаём артикул .. 
		$proids=field_get_items('node',$vars['node'],'field_product_variations');
		//kprint_r($vars);
		drupal_add_js([
			'productstars'=>$stars,
			'productsku'=>$proids[0]['product_id'],
		],'setting');

		
		// инфрмация о скидках .. и акциях 
		if ($disconttime>0){
			// подгружаем стили и скрипты для счётчика .. 
			drupal_add_js(drupal_get_path('theme','mk2').'/js/timer/jquery.countdown.js');
			drupal_add_css(drupal_get_path('theme','mk2').'/js/timer/jquery.countdown.css');
			$vars['discont_dt']=$disconttime;
			//kprint_r(drupal_get_path('theme','mk2'));
			//drupal_
			//jquery.countdown
		}


		
		//kprint_r($vars);
		// пока форму коментов лочим .. 
		hide($vars['content']['comments']);//['#access']=false;
		hide($vars['content']['links']);

		// 

		$qparams=drupal_get_query_parameters();
		//аяксовая версия 
		if (!isset($qparams['_escaped_fragment_'])){
			//kprint_r($qparams);
			
			foreach(['tovar_analogs','mit_tovar_buy'] as $k){
				if (empty($vars['content']['field_'.$k]))
					continue;
				$nids=[];
				foreach(element_children($vars['content']['field_'.$k]) as $i)
					if (isset($vars['content']['field_'.$k][$i]['#node']))
						$nids[]=$vars['content']['field_'.$k][$i]['#node']->nid;
				$classe='field-name-field-'.str_replace('_', '-', $k);
				drupal_add_js(['product-page-'.$k=>['nids'=>$nids,'to'=>'.'.$classe.' .elements-list']],'setting');
				hide($vars['content']['field_'.$k]);
				$vars['content'][$k]=[
					'#attached'=>[
						'library'=>[
							['mklibs','slick'],
						],
					],
					'#type'=>'container',
					'#weight'=>$vars['content']['field_'.$k]['#weight'],
					'#attributes'=>[
						'class'=>['ajax-loadable',$classe], 
						'data-key'=>'product-page-'.$k,
					],
					'field-label'=>[
						'#markup'=>$vars['content']['field_'.$k]['#title'],
						'#prefix'=>'<div class="field-label">',
						'#suffix'=>'</div><div class="elements-list products" data-dots="1"></div>',
					],
				];
			}
			$oldvieved=&drupal_static('old-viewed-products-list');
			if (!empty($oldvieved)){
				$k='old_viewed_products';

				$classe='field-name-field-'.str_replace('_', '-', $k);
				drupal_add_js(['product-page-'.$k=>['nids'=>$oldvieved,'to'=>'.'.$classe.' .elements-list']],'setting');
				$vars['content'][$k]=[
					'#attached'=>[
						'library'=>[
							['mklibs','slick'],
						],
					],
					'#type'=>'container',
					'#weight'=>1040,
					'#attributes'=>[
						'class'=>['ajax-loadable',$classe], 
						'data-key'=>'product-page-'.$k,
					],
					'field-label'=>[
						'#markup'=>'Ранее просмотренные товары',
						'#prefix'=>'<div class="field-label">',
						'#suffix'=>'</div><div class="elements-list products" data-dots="1"></div>',
					],
				];
			}

			// акционные товары ..
			$tid=drupal_static('prev-term-id');
			$vars['content']['prodycts-at-akcia']=getMarkupsOfAkciiProducts($tid,$vars['node']->nid);
			$vars['content']['prodycts-at-akcia']['#weight']=1005;

			// хиты продаж
			$term=taxonomy_term_load($tid);
			foreach(['hits'=>'field_mit_tovar_buy','zakaz'=>'field_tovar_analogs'] as $v=>$f){
				$$v=field_get_items('taxonomy_term',$term,$f);
				if ($$v)
					foreach($$v as $x=>$y)
						if ($y)
							$$v[$x]=$y['nid'];
			}
			if (!empty($hits)){
				$vars['content']['hits-pro-list']=carouselMarkupGen($hits,'hits-prods-list','Хиты продаж');
				$vars['content']['hits-pro-list']['#weight']=1020;
			}
			if (!empty($zakaz)){
				$vars['content']['zakaz-pro-list']=carouselMarkupGen($zakaz,'zakaz-prods-list','Товары под заказ');
				$vars['content']['zakaz-pro-list']['#weight']=1030;
			}
			
				//$prodyctsAtAkcia=node_view_multiple(node_load_multiple($prodyctsAtAkcia));
				
				
				//$prodyctsAtAkcia=;
			

		}
	}
}


/**
 * препроцесс для коментов 
 */
function mk2_preprocess_comment(&$vars)
{
	//kprint_r($vars);
	//kprint_r($vars['comment']);
	// автор 
	$vars['comment_author']=$vars['comment']->name??'Аноним';
	// дата создания .. 
	$vars['comment_created']=format_date($vars['comment']->created,'my2');
	// Звёзды 
	$stars=field_get_items('comment',$vars['comment'],'field_rating');
	$vars['comment_stars']=0;
	if (isset($stars[0]['value']))
		$vars['comment_stars']=intval($stars[0]['value']);	

	if (!empty($vars['content']['field_rating'])){
		$r=field_get_items('comment',$vars['comment'],'field_rating');
		$vars['content']['field_rating'][0]=array(
			'#markup'=>sprintf('<span class="rating-out rating-widget-view"><span class="rating-in" data-rating="%d" style="width:%d%%"></span></span>',$r[0]['value'],$r[0]['value']),
		);
	}

}

function mk2_preprocess_html(&$vars)
{
	$fd=theme_get_setting('magaz-data');
	$vars['isprod']=!empty($fd['is-prod']);

	//kprint_r($vars);
	///$vars['page']['content']['metatags']['taxonomy_term:categories']['robots']=''
}


/**
 * препроцесс  
 */
function mk2_preprocess(&$vars,$hook)
{
	//dsm($hook);
	//kprint_r($hook);
	//if ($hook=='comment')
	//	dsm($vars);
	//if ('views_view_unformatted'==$hook)
	//	dsm($vars);
	//dsm($hook);
}


