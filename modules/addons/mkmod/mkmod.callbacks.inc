<?php 
// позгрузить  контент ноды во всплывашку
function _get_node_in_popup_cb($n){
	$cmd=array();
	$nw=node_view($n);
	//$nw['#prefix']='<div class="container-fluid col-lg-28">';
	//$nw['#suffix']='</div>';
	$cmd[]=array(
		'command'=>'show_in_popup',
		'content'=>render($nw),
		'wrapCSS'=>'node-in-popup node-'.$n->nid.' node-'.$n->type,
		'autoHeight'=>true,
		'scrolling'=>'no',
		'autoSize'=>false,
		'fitToView'=>false,
		/*'width'=>'auto',
		//'type'=>'html',
		
		*/
		'tpl'=>array(
			'closeBtn'=>'<a title="Закрыть" class="fancybox-item fancybox-close" href="javascript:;"></a>',
		),
	);
	return array('#type'=>'ajax','#commands'=>$cmd);
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
				//'width'=>'auto',
				//'type'=>'html',
				'scrolling'=>'no',
				'autoSize'=>true,
				'autoHeight'=>true,
				'fitToView'=>false,
				'fixed'=>false,
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
			'scrolling'=>'no',
			'autoSize'=>false,
			'fitToView'=>false,

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
// =====================================================================
// хиты продаж
function _bestsellers_cb(){
	$out=array();
	// Предлагаем Вашему вниманию наши хиты продаж.
	// загрузить метки товаров 
	$res=_gethitprodag(40);
	
	if ($res){
		$nn=node_view_multiple(node_load_multiple($res));
		$out=array_merge($out,$nn);
	}
	return $out;
}
//=======================================================
function _akciilist_page_cb(){
	$out=array();
	$els=_getactionprodag();
	$fd=variable_get('discounts config',array());

	if ($els &&  !empty($fd['mess-on-page-exist']) || !$els && !empty($fd['mess-on-page-void']))
		$out['ins']=array(
			'#markup'=>$els?$fd['mess-on-page-exist']:$fd['mess-on-page-void'],
		);
	if ($els){
		$ns=node_view_multiple(node_load_multiple(array_keys($els)));
		$ns=$ns['nodes'];
		$ns['#type']='container';
		$ns['#attributes']=array('class'=>array('cls'));
		$out['prodsist']=$ns;
				
	}

	return $out;
}

// ===========================================================================
function tpls_view_cb(){
	$tpllist=[
		'uslovia-of-kredit-for-pokupatel'=>'Условия кредитования для покупателей'
	];
	$links=[];
	foreach($tpllist as $x=>$y){
		$links[]=[
			'title'=>$y,
			'href'=>'admin/config/administration/mkmod/tpls-editor/'.$x,
		];
	}
	$out=[
		'mark'=>[
			'#markup'=>'<h1>Список шаблонов, для редактирования</h1>',
		],
		'links'=>[
			'#theme'=>'links',
			'#links'=>$links,
		],
	];

	return $out;
}


function get_next_content_elements_jscb()
{
	$cmds=[];
	// запрашиваем витрины .. 
	$res=db_select('node','n');
	$res->fields('n',['nid']);
	$res->condition('n.status',1);
	$res->condition('n.type','product_display');
	$res->leftJoin('taxonomy_index','ti','ti.nid=n.nid');
	$res->condition('ti.tid',$_POST['curtid']);
	$res->range($_POST['exists'],$_POST['ppsize']);
	$res=$res->execute()->fetchCol();
	$fin=true;
	if ($res){
		$fin=count($res)<$_POST['ppsize'];

		$res= node_view_multiple(node_load_multiple($res));

	}
	$cmd=[
		'command'=>'get-next-content-elements',
		'data'=>'test',
		'nids'=>render($res),
		'finish'=>$fin,
	];
	$cmds[]=$cmd;
	return ['#type'=>'ajax','#commands'=>$cmds];
}
?>