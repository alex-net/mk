<?php 


// ===================================
// автокомплит для форм поиска 
function vitrfinder_cb(){
	$params=drupal_get_query_parameters();
	if (empty($params['query'])){
		drupal_json_output(array());
		return ;
	}
	$limit=5;
	if (!empty($params['limit']))
		$limit=$params['limit'];
	$res=db_select('node','n');
	$res->condition('n.status',1);
	$res->condition('n.type','product_display');
	$res->condition('n.title','%'.db_like($params['query']).'%','like');
	$res->fields('n',array('title'));
	$res->range(0,$limit);
	$res->orderBy('n.title','asc');
	$res=$res->execute()->fetchCol();
	$out=array();
	foreach($res as $v)
		$out[]=array('value'=>$v,'label'=>preg_replace('#('.addslashes($params['query']).')#iu', '<strong>$1</strong>', $v));
	drupal_json_output($out);
	//$res=array_combine($res, $res);
}

/**
 * подгрузка результатов ..
 */
function GetNextpageSearch_jscb()
{
	$cmd=[];
	$post=$_POST;
	$pp=variable_get('default_nodes_main',10);
	$out=[];

	$nids=_getproductslist($post['ss'],$post['exists']+$post['curpage']*$pp);
	
	$fin=true;
	if ($nids){
		$out=node_view_multiple(node_load_multiple($nids));
		$fin=count($nids)<$pp;
	}
	$cmd[]=array(
		'command'=>'get-next-content-elements',
		'nids'=>render($out),
		'finish'=>$fin,
	);
	//dsm(arg(5,$url['path']),'url');
	return array('#type'=>'ajax','#commands'=>$cmd);
}