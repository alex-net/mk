<?php

// форма управления категориями ссылок .. 
function hitro_list_form($form,$form_state,$type='',$entitytype='')
{
	$entityid=0;
	$pid=0;
	
	//$entitytype=arg(0);
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
	$needreload=true;
	//if ($form_state['values'])
	//dsm($form_state,'fs');
	if (!empty($form_state['triggering_element'])){
		$needreload=false;
		$data=$form_state['values'];
		$type=$data['type'];
		$pid=$data['pid'];
		$data=$data['tags']??[];
		form_state_values_clean($form_state);
		$vals=$form_state['values'];
		$te=$form_state['triggering_element'];
		$tename=end($te['#parents']);
		//dfb($tename,'$tename');
		switch($tename){
			case 'addmore':
				$data[]=[];
			break;
			case 'del':
				unset($data[$te['#idis']]);
			break;
			case 'copy':
				$_SESSION['mk-tags-list-from']="$type--$pid";
				break;
			case 'paste':
				if (!empty($_SESSION['mk-tags-list-from'])){
					list($fromtype,$frompid)=explode('--',$_SESSION['mk-tags-list-from']);
					$res=db_select('hl','t');
					$res->condition('t.type',$fromtype);
					$res->condition('t.pid',$frompid);
					$res->fields('t');
					$groupslist=$res->execute()->fetchAll(PDO::FETCH_ASSOC);
					$pids=[];
					foreach($groupslist as $g)
						$pids[]=$g['id'];
					// надо выдрать линки .. 
					$res=db_select('hl','t');
					$res->condition('t.type','link');
					$res->condition('t.pid',$pids);
					$res->fields('t');
					$linklist=$res->execute()->fetchAll(PDO::FETCH_ASSOC);
					//dfb(['g'=>count($groupslist),'l'=>count($linklist)],'lists');

					//dfb([$type,$pid],'insert to');
					// зачистка текущего расположения .. 
					// достаём id групп ..
					$res=db_select('hl','t');
					$res->condition('t.type',$type);
					$res->condition('t.pid',$pid);
					$res->fields('t',['id']);
					$old=$res->execute()->fetchCol();

					// процесс зачистки .. 
					if ($old){
						//dfb($old,'$res');
						// удаляем группы 
						$res=db_delete('hl');
						$res->condition('id',$old);						
						$res->execute();
						// удаляем ссылки 
						$res=db_delete('hl');
						$res->condition('pid',$old);
						$res->condition('type','link');
						$res->execute();
					}
					// проходим по группам .. 
					foreach($groupslist as $g){
						$gid=$g['id'];
						unset($g['id']);
						$g['pid']=$pid;
						$g['type']=$type;
						$res=db_insert('hl');
						$res->fields($g);
						$g=$res->execute();
						foreach($linklist as $l){
							if ($l['pid']!=$gid)
								continue;
							unset($l['id']);
							$l['pid']=$g;
							$res=db_insert('hl');
							$res->fields($l);
							$res->execute();
						}
					}
					$needreload=true;

					//$groupslist=$res->fetchAll(PDO::FETCH_ASSOC);
					// собрать idы копируемых групп  .. 
					
					//dfb($_SESSION['mk-tags-list-from'],'test');
					//unset($_SESSION['mk-tags-list-from']);
				}
				
		}
		//dfb($vals,$te);
		//dfb($form_state['triggering_element'],'te');
	}
	// загрузка из базы . 
	if ($needreload){
	
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
	else 
	{
		$ids=[];
		foreach($data as $y)
			$ids[]=$y['id'];
		if ($ids){
			$res=db_select('hl','t');
			$res->condition('t.type','link');
			$res->condition('t.pid',$ids);
			$res->fields('t',['pid']);
			$res->groupBy('t.pid');
			$res->addExpression('count(*)','co');
			$res=$res->execute()->fetchAllKeyed(0);
			foreach($data as $x=>$y)
				$data[$x]['col']=$res[$y['id']]??0;
			//dfb($res);
		}
	}

	$form=[
		'#attributes'=>['class'=>['tags-edit-form']],
		/*'from'=>[
			'#markup'=>$_SESSION['mk-tags-list-from']??'--',
		],*/
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
			'link'=>'Ссылки',
			'tagslinkscontrol'=>'Управление дочерями',//$type=='link'?'Ссылки':'Управление тегами-ссылками',
			'weight'=>'Вес',
			'del'=>'Удалить'],
	];
	//dsm($type,'$type');
	switch($type){
		case 'link':
			unset($form['tags']['#tblheader']['tagslinkscontrol']);
			break;
		case 'tgroup':
		case 'ngroup':
			unset($form['tags']['#tblheader']['link']);
			break;
		case 'fgroup':
			$form['tags']['#tblheader']['link'].=' (для связанные категории)';
			break;
	}
	
		
	//dsm($data);
	foreach($data as $x=>$d){
		
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
			'link'=>[
				'#type'=>'textfield',
				'#size'=>46,
				'#default_value'=>empty($d['link'])?'':$d['link'],
				//'#title'=>'Перейти',
				'#access'=>!in_array($type, ['tgroup','ngroup']),//$d['id']>0,
			],
			'tagslinkscontrol'=>[
				'#type'=>'link',
				'#href'=>current_path().'/'.($d['id']??0),
				'#title'=>sprintf('Перейти (%d)',$d['col']??0),
				'#access'=>!empty($d['id']) && strpos($type, 'group')!==false,
			],
			'weight'=>[
				'#type'=>'weight',
				'#delta'=>100,
				'#default_value'=>empty($d['weight'])?$x*2:$d['weight'],
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
	$form['buttons']['#markup']='<div class="buttons-ajax">';
	$form['addmore']=[
		'#type'=>'button',
		'#value'=>'Добавить ещё',
		'#ajax'=>[
			'callback'=>'hl_taggs_add_more_jscb',
			'wrapper'=>'tags-wraper',
		],
	];
	// вставить кнопки копипаста списка ...
	if (strpos($type, 'group')!==false ){
		$form=array_merge($form,[
			'copy'=>[
				'#access'=>count($data),
				'#type'=>'button',
				'#value'=>'Копировать',
				'#ajax'=>[
					'callback'=>'hl_taggs_add_more_jscb',
					'wrapper'=>'tags-wraper',
				],
			],
			'paste'=>[
				'#type'=>'button',
				'#access'=>isset($_SESSION['mk-tags-list-from'])&& $_SESSION['mk-tags-list-from']!="$type--$pid" ,
				'#value'=>'Вставить/Заменить',
				'#ajax'=>[
					'callback'=>'hl_taggs_add_more_jscb',
					'wrapper'=>'tags-wraper',
				],
			]
		]);
	}
	$form['buttons1']['#markup']='</div>';
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
	//dsm($fs['tags'],'save');
	//kprint_r($fs);
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


