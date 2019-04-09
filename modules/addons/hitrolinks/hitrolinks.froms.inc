<?php

// форма управления категориями ссылок .. 
function hitro_list_form($form,$form_state,$type='')
{
	$entityid=0;
	$pid=0;

	$entitytype=arg(0);
	if ($type=='group'){
		$type=$entitytype[0].$type;
		switch(arg(0)){
			case 'node':
				$pid=arg(1);
				break;
			case 'taxonomy':
				$pid=arg(2);
				break;
		}
	}
	else
		switch(arg(0)){
			case 'node':
				$pid=arg(3);
				break;
			case 'taxonomy':
				$pid=arg(4);
				break;
		}
	$data=[];
	//if ($form_state['values'])
	//dsm($form_state,'fs');
	if (!empty($form_state['triggering_element'])){

		$data=$form_state['values'];
		$type=$data['type'];
		$pid=$data['pid'];
		$data=$data['tags'];
		form_state_values_clean($form_state);
		$vals=$form_state['values'];
		$te=$form_state['triggering_element'];
		$tename=end($te['#parents']);
		switch($tename){
			case 'addmore':
				$data[]=[];
			break;
			case 'del':
				unset($data[$te['#idis']]);
			break;
		}
		//dfb($vals,$te);
		//dfb($form_state['triggering_element'],'te');
	}
	else{
		//dsm([$type,$pid]);
		// читаем данные из базы .. 
		$res=db_select('hl','t');
		$res->fields('t');
		$res->condition('t.type',$type);
		$res->condition('t.pid',$pid);
		$res->orderBy('t.weight','asc');
		$res->groupBy('t.id');
		$res->leftJoin('hl','t2','t.id=t2.pid');
		$res->addExpression('count(t2.id)','col');
		$data=$res->execute()->fetchAll(PDO::FETCH_ASSOC);
	}

	$form=[
		'type'=>[
			'#type'=>'value',
			'#value'=>$type,
		],
		'pid'=>[
			'#type'=>'value',
			'#value'=>$pid,
		],
		'actions'=>[
			'#type'=>'actions',
			'submit'=>[
				'#type'=>'submit',
				'#name'=>'save',
				'#value'=>'Сохранить',
			],
			'back'=>[
				'#type'=>'submit',
				'#access'=>$type=='link',
				'#name'=>'back',
				'#value'=>'Назад на 1-й уровень',
			],
		],
	];

	$form['tags']=[
		'#type'=>'container',
		'#attributes'=>[
			'class'=>['tags-wraper'],
			'id'=>'tags-wraper',
		],
		'#tree'=>true,
		'#theme'=>'sortedtable',
		'#empty-text'=>'Нет ни одного '.($type=='link'?'тега':'заголовка'),
		'#tblheader'=>[
			'name'=>$type=='link'?'Теги (2-й уровень)':'Заголовки (1-й уровень)',
			'active'=>'Активно',
			'link'=>$type=='link'?'Ссылки':'Управление тегами-ссылками',
			'weight'=>'Вес',
			'del'=>'Удалить'],
	];

	foreach($data as $x=>$d){
		if ($type=='link')
			$link=[
				'#type'=>'textfield',
				'#size'=>46,
				'#default_value'=>empty($d['link'])?'':$d['link'],
				//'#title'=>'Перейти',
				//'#access'=>$d['id']>0,
			];
		else
			$link=[
				'#type'=>'link',
				'#href'=>current_path().'/'.$d['id'],
				'#title'=>sprintf('Перейти (%d)',$d['col']),
				'#access'=>$d['id']>0,
			];
			

		$form['tags'][$x]=[
			'id'=>[
				'#type'=>'value',
				'#value'=>empty($d['id'])?0:$d['id'],
			],
			'active'=>[
				'#type'=>'checkbox',
				'#default_value'=>isset($d['active'])? !empty($d['active']):true,
			],
			'name'=>[
				'#type'=>'textfield',
				'#size'=>46,
				'#default_value'=>empty($d['name'])?'':$d['name'],
			],
			'link'=>$link,
			'weight'=>[
				'#type'=>'weight',
				'#default_value'=>empty($d['weight'])?0:$d['weight'],
				'#attributes'=>['class'=>['is-weight']],
			],
			'del'=>[
				'#type'=>'button',
				'#value'=>'Удалить',
				'#name'=>"del-$x",
				'#idis'=>$x,
				'#ajax'=>[
					'callback'=>'hl_taggs_add_more_jscb',
					'wrapper'=>'tags-wraper',
				],
			],
		];
	}
	$form['addmore']=[
		'#type'=>'button',
		'#value'=>'Добавить ещё',
		'#ajax'=>[
			'callback'=>'hl_taggs_add_more_jscb',
			'wrapper'=>'tags-wraper',
		],
	];
	return $form;
}

function hl_taggs_add_more_jscb($form,$form_state)
{
	return $form['tags'];

}

// сохраняем ссылки ... 
function hitro_list_form_submit($form,$form_state)
{
	if ($form_state['clicked_button']['#name']=='back'){
		drupal_goto(dirname(current_path()));
		return;
	}
	//	dsm($form_state,dirname(current_path()));
	//return ;
	form_state_values_clean($form_state);
	$fs=$form_state['values'];
	
	// запрашиваем всех кто есть в таблице.. 
	$res=db_select('hl','t');
	$res->condition('t.type',$fs['type']);
	$res->condition('t.pid',$fs['pid']);
	$res->fields('t',['id']);
	$ids=$res->execute()->fetchCol();

	$ids2=[];
	kprint_r($fs);
	if (!empty($fs['tags']))
		foreach($fs['tags'] as $t){
			// пропускаем тех кто с пустыми полями . .
			if (empty($t['name']) || empty($t['link']) && $fs['type']=='link')
				continue;
			if (!$t['id'])
				$res=db_insert('hl');
			else{
				$res=db_update('hl');
				$res->condition('id',$t['id']);
				$ids2[]=$t['id'];
			}

			$ff=[
				'name'=>$t['name'],
				'weight'=>$t['weight'],
				'type'=>$fs['type'],
				'active'=>$t['active'],
				'pid'=>$fs['pid'],
				'link'=>empty($t['link'])?'':$t['link'],
			];
			
			$res->fields($ff);
			$res->execute();


		}
	$ids=array_diff($ids, $ids2);
	// удаление элементов 
	if ($ids){
		$or=db_or();
		$or->condition('id',$ids);
		$or->condition('pid',$ids);

		$res=db_delete('hl');
		$res->condition($or);
		$res->execute();
	}

	drupal_set_message('Данные сохранены');
}

