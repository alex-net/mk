<?php 

function theme_sortedtable($vars)
{
	//kprint_r($vars);
	// заполнение шапки  . 
	$head=[];
	foreach($vars['form']['#tblheader'] as $k=>$v)
		$head[$k]=$v;

	// строки ..
	$rows=[];
	foreach(element_children($vars['form']) as $k){
		$row=[];
		foreach($head as $k2=>$f)
			$row[$k2]['data']=render($vars['form'][$k][$k2]);
		$rows[]=['data'=>$row,'class'=>['draggable']];
	}
	drupal_add_tabledrag('sorted-tbl','order','sibling','is-weight');
	return theme('table',[
		'header'=>$head,
		'rows'=>$rows,
		'attributes'=>['id'=>'sorted-tbl'],
		'empty'=>empty($vars['form']['#empty-text'])?'':$vars['form']['#empty-text'],
	]).drupal_render_children($vars['form']);
}

// =========================
function popuplinks_prefunc(&$vars)
{
	// достать заголовки 
	$res=db_select('hl','t');
	$res->fields('t');
	$res->condition('t.active',1);
	$res->condition('t.type',$vars['group']);
	$res->condition('t.pid',$vars['pid']);
	$res->orderBy('t.weight','asc');

	$groups=[];
	$res=$res->execute()->fetchAll(PDO::FETCH_ASSOC);
	foreach($res as $v)
		$groups[$v['id']]=$v;
	
	
	$list=[];
	// собрать ссылки 
	$links=[];
	if($groups){
		$res=db_select('hl','t');
		$res->fields('t');
		$res->condition('t.type','link');
		$res->condition('t.active',1);
		$res->condition('t.pid',array_keys($groups));
		$res=$res->execute()->fetchAll(PDO::FETCH_ASSOC);
		if ($res){
			$res=array_merge($res,$groups);


			foreach($res as $r1)
				if (preg_match('#group#',$r1['type'])){
					$l=['name'=>$r1['name'],'ch'=>[]];
					foreach($res as $r2)
						if($r2['type']=='link' && $r2['pid']==$r1['id'])
							$l['ch'][]=l($r2['name'],$r2['link']);
					if ($l['ch'])	
						$list[]=$l;
				}

		}
		

	}
	//
	//$res->condition('t.type',['link',$vars['group']]);
	//$res->orderBy('t.weight');
	//$res=$res->execute()->fetchAll(PDO::FETCH_ASSOC);
	//kprint_r($vars);
	//kprint_r($res);
	
	
	
	//kprint_r($list);
	$vars['list']=$list;
	//kprint_r($vars);
	$vars['classes_array']=$vars['attributes_array']=$vars['title_attributes_array']=$vars['content_attributes_array']=[];
}