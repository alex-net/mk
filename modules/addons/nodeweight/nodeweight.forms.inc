<?php
function nodesetweight_form($form,$form_state,$term){
	$form=array(
		'tid'=>array(
			'#type'=>'value',
			'#value'=>$term->tid,
		),
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Сохранить',
			),
		),
	);
	
	$ff=array();
	
	foreach(field_info_fields() as $v)
		if ($v['type']=='taxonomy_term_reference')
			$ff[]=$v['field_name'];
	// исследуем таблицы на предмет .. нод
	$nids=array();
	foreach($ff as $f){
		$res=db_select('node','n');
		$res->fields('n',array('nid','title'));
		$res->leftjoin('field_data_'.$f,'t','n.nid=t.entity_id and n.type=t.bundle and t.entity_type=\'node\'');
		$res->condition('t.'.$f.'_tid',$term->tid);

		$res->leftjoin('nodeweight','nw','nw.nid=t.entity_id and nw.tid=t.'.$f.'_tid');
		$res->addExpression('if(isNull(nw.weight),0,nw.weight)','weight');
		$res->orderBy('weight','asc');
		//$res->groupBy('n.nid');
		$res=$res->execute()->fetchall(PDO::FETCH_ASSOC);
		if ($res)
			$nids=array_merge($nids,$res);
	}
	$form['weight-tbl']=array(
		'#theme'=>'formtable',
		'#header'=>array('n'=>'№ ноды','title'=>'Заголовк','weight'=>'Вес',),
		'#stichy'=>false,
		'#tree'=>true,
	);
	foreach($nids as $x=>$v)
		$form['weight-tbl'][$x]=array(
			'n'=>array(
				'#markup'=>$v['nid'],
			),
			'nid'=>array(
				'#type'=>'value',
				'#value'=>$v['nid'],
			),
			'title'=>array(
				'#markup'=>$v['title'],
			),
			'weight'=>array(
				'#type'=>'weight',
				'#delta'=>100,
				'#default_value'=>$v['weight'],
				'#is-weight'=>true,
			),
		);
	//dsm($ff);

	return $form;
}
// =================================================
function nodesetweight_form_submit($form,$form_state){
	form_state_values_clean($form_state);
	$vals=$form_state['values'];
	// удаляем то что было .. 
	$res=db_delete('nodeweight');
	$res->condition('tid',$vals['tid']);
	$res->execute();
	// добавляем новые записи 
	$res=db_insert('nodeweight');
	$res->fields(array('nid','tid','weight'));
	foreach($vals['weight-tbl'] as $v)
		$res->values(array($v['nid'],$vals['tid'],$v['weight']));
	$res->execute();
}
// ===================================
?>