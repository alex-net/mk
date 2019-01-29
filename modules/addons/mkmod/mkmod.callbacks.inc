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
// подгрузить фому во всплывашку ..
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
?>