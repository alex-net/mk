<?php 

function hitrolinks_block_info()
{
	return [
		///  блок отображения менюшки ... из фильтров ... 
		'menu-hl-block'=>[
			'info'=>'Менюшка фильтров',
		],
	];
}

function hitrolinks_block_configure($delta='')
{

	$data=variable_get('block-data-'.$delta,[]);
	$form=[];
	switch ($delta){
		case 'menu-hl-block':
			$form['settings']=[
				'#tree'=>true,
				'visfilterscount'=>[
					'#type'=>'textfield',
					'#title'=>'Количество отображаемых элементов',
					'#default_value'=>$data['visfilterscount']??5,
				],
			];
		break;
	}
	return $form;
}


function hitrolinks_block_save($delta='',$edit=[])
{
	if ($delta)
		$data=variable_get('block-data-'.$delta,[]);
	switch($delta){
		case 'menu-hl-block':
			if(!empty($edit['settings']))
				$data=array_merge($data,$edit['settings']);

			//dsm($edit['settings'],'edit');
		break;
	}
	if ($delta)
		variable_set('block-data-'.$delta,$data);
	
}


function hitrolinks_block_view($delta='')
{
	$b=[];
	$conf=variable_get('block-data-'.$delta,[]);

	switch($delta){
		case 'menu-hl-block':

			if (!preg_match('#^taxonomy/term/(\d+)$#i',current_path(),$tid))
				break;
			// запрашиваем .. данные по ссылкам фильтров ... (формирование меню) 
			$res=db_select('hl','t1');
			$res->condition('t1.active',1);
			$res->where('length(t1.link)>0');
			$res->orderBy('t1.weight','asc');
			$res->orderBy('t2.weight','asc');
			$res->leftJoin('hl','t2',"t2.pid=t1.id ");
			//$res->condition('t2.active',1);
			$res->addField('t1','id','gid');
			$res->addField('t1','weight','gw');
			$res->addField('t1','name','gname');
			$res->addField('t1','link','glink');
			$res->addField('t2','id','lid');
			$res->addField('t2','name','lname');
			$res->addField('t2','link','llink');
			$res->addField('t2','weight','lw');
			$res->addField('t2','active','la');

// http://dev.masterkrowli.ru/bitumnaya-gidroizolyaciya
			
			$res->condition('t1.type','fgroup');
			$res->condition('t1.pid',end($tid));
			
			$res=$res->execute()->fetchAll(PDO::FETCH_ASSOC);
			//dsm($res);
			if (!$res)
				break;

			$menu=_createMenuFromList($res);

			//dsm($menu,'$menu');

			$b['content']=theme('katblockmenu',['menu'=>$menu,'limit'=>$conf['visfilterscount']??5]);
			$b['subject']='Категории';
			break;
	}
	return $b;
}