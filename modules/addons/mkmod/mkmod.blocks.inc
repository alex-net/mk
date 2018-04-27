<?php 

function mkmod_block_list_alter(&$blocks){

	foreach($blocks as $x=>$y)
		if ($y->status){
			$vis=false;
			$fd=variable_get('mk-vis-conf-for-'.$y->module.'-'.$y->delta,array());
			if (empty($fd['mkplaces']) || implode('',$fd['mkplaces'])=='000')
				continue;
			// если были заданы местоположения 
			foreach($fd['mkplaces'] as $v)
				switch($v.''){
					// товары 
					case 'products':
						if (preg_match('#^node/(\d+)$#',current_path(),$t)){ // это нода узнаём тип
							// ЗАПРОС В БАЗУ .. 
							$res=db_select('node','n');
							$res->condition('n.nid',end($t));
							$res->condition('n.type','product_display');
							$res->addExpression('count(*)');
							$res=$res->execute()->fetchField();
							$vis=$vis || !empty($res);
						}
					break;
					// каталог
					case 'cats':
						if (preg_match('#^taxonomy/term/(\d+)$#i',current_path(),$t)) { // это нода узнаём тип
							// ЗАПРОС В БАЗУ .. 
							$res=db_select('taxonomy_term_data','t');
							$res->condition('t.tid',end($t));
							$res->leftjoin('taxonomy_vocabulary','tv','tv.vid=t.vid');
							$res->condition('tv.machine_name','categories');
							$res->addExpression('count(*)');
							$res=$res->execute()->fetchField();
							$vis=$vis || !empty($res);
						}
					break;
					// главная 
					case 'front':
						$vis=$vis || drupal_is_front_page();
					break;
				}
			// если стало не видно = жахнуть блок 
			if (!$vis)
				unset($blocks[$x]);
		}
}
// ==========================================

function mkmod_block_info(){
	return array(
		'hit-prodag'=>array(
			'info'=>'Хит продаж',
		),
		'akcii-slider-big'=>array(
			'info'=>'Акции слайдер большой',
		),
		'akcii-slider-block'=>array(
			'info'=>'Акции слайдер мини',
		),
		'catlist'=>array(
			'info'=>'Категории товаров',
		),
		'ad-block'=>array(
			'info'=>'Объявления',		
		),
	);
}
function mkmod_block_configure ($delta=''){
	$form=array();
	$fd=variable_get('mkmod blocks '.$delta,array());
	switch($delta){
		case 'akcii-slider-big':
		case 'akcii-slider-block':
			$form['mkblock-data']=array(
				'#type'=>'fieldset',
				'#tree'=>true,
				'#title'=>'настройки слайдера',
				'timeslide'=>array(
					'#type'=>'textfield',
					'#title'=>'Интервал листания',
					'#size'=>10,
					'#field_suffix'=>'с.',
					'#default_value'=>empty($fd['timeslide'])?'':$fd['timeslide'],
				),
			);
		break;
	}
	return  $form;
}
// =====================================
function mkmod_block_save($delta='',$data=array()){
	if (!empty($data['mkblock-data']))
		variable_set('mkmod blocks '.$delta,$data['mkblock-data']);
}
// ====================================
function mkmod_block_view($delta=''){
	$b=array();
	$fd=variable_get('mkmod blocks '.$delta,array());
	switch($delta){
		case 'hit-prodag':
			$nids=_gethitprodag(4);
			if ($nids)
				$b['content']=theme('topprodaglist',array(
					'list'=>$nids,
				));
		break;
		case 'ad-block':
			$res=db_select('node','n');
			$res->condition('n.type','ad_for_main');
			$res->fields('n',array('nid'));
			$res->orderby('n.created','asc');
			$res=$res->execute()->fetchCol();
			if ($res){
				$res=node_view_multiple(node_load_multiple($res));
				$res['nodes']['#prefix']='<div class="slider-ad-wrapper">';
				$res['nodes']['#suffix']='</div>';
				//dsm($res);
				$b['content']=render($res);
			}
			//$b['content']='adad';
		break;
		// блок слайдеров 
		case 'akcii-slider-big':
			// Достать акционные товары
			$els=_getactionprodag();
			
			if ($els){
				foreach($els as $x=>$y){
					$els[$x]['img']=image_style_url('350x170',$y['uri']);
					$els[$x]['url']=url('node/'.$x);
					$els[$x]['oldp']=commerce_currency_format($y['oldp'],null);
					$els[$x]['cp']=commerce_currency_format($y['cp'],null);
					$els[$x]['measure']=drupal_strtolower($y['measure']);
				}

				//dsm($els);
				$b['content']=array(
					'slid-first'=>array(
						'#theme'=>'sliderbigel',
						'#data'=>$els,
						'#prefix'=>'<div class="slider-main-big">',
						'#suffix'=>'</div>',
					),
					'slid-second'=>array(
						'#theme'=>'slidersmalel',
						'#data'=>$els,
						'#prefix'=>'<div class="slider-main-small clearfix">',
						'#suffix'=>'</div>',
					),
					'#attached'=>array(
						'js'=>array(
							array('data'=>array('accii-slider-speed'=>empty($fd['timeslide'])|| !is_numeric($fd['timeslide']) ?3:intval($fd['timeslide'])),'type'=>'setting'),
						),
					),
				);
			}
		break;
		case 'akcii-slider-block':
			$els=_getactionprodag();
			if (empty($els))
				break;
			$bd=variable_get('discounts config',array());
			///dsm($fd);
			$out=array();
			if (count($els)>1)
				$out['nav']=array(
					'#type'=>'container',
					'#attributes'=>array(
						'class'=>array('flex-direction-nav'),
					),
					'prev'=>array('#markup'=>'<span class="flex-prev"></span>'),
					'next'=>array('#markup'=>'<span class="flex-next"></span>'),
				);
			if (!empty($$bd['block-top-mess']))
				$out['head']=array(
					'#markup'=>$$bd['block-top-mess'],
					'#prefix'=>'<div class="b-header">',
					'#suffix'=>'</div>',
				);
			$out['prod-list']=array(
				'#type'=>'container',
				'#attributes'=>array(
					'class'=>array('a-prod-list-wrap','clearfix'),
				),
			);
			foreach($els as $k=>$v){
				$v['url']=url('node/'.$k);
				$v['img']=image_style_url('60x40',$v['uri']);
				$v['oldp']=commerce_currency_format($v['oldp'],null);
				$v['cp']=commerce_currency_format($v['cp'],null);
				$v['afrom']=strtotime($v['afrom']);
				$v['ato']=strtotime($v['ato']);

				$out['prod-list'][]=array(
					'#theme'=>'slidersidebarel',
					'#data'=>$v,
				);
			}
			$out['#attached']=array(
				'js'=>array(
					array('data'=>array('accii-slider-small-speed'=>empty($fd['timeslide'])|| !is_numeric($fd['timeslide']) ?3:intval($fd['timeslide'])),'type'=>'setting'),
				),
			);
			$b['content']=$out;
		break;
		case 'catlist':
			// запрашиваем категории первый уровень 
		
			$res=db_select('taxonomy_term_data','t');
			$res->condition('t.vid',2);
			$res->fields('t',array('tid','name'));
			$res->orderBy('t.weight','asc');
			//  нужно выбрать первый уровень 
			$res->leftjoin('taxonomy_term_hierarchy','th','th.tid=t.tid');
			$res->condition('th.parent',0);
			// достаём картинки категорий . 
			$res->leftjoin('field_data_field_pic_category','cat','cat.entity_id=t.tid and cat.bundle=\'categories\' and cat.entity_type=\'taxonomy_term\'');
			$res->leftjoin('file_managed','fm','fm.fid=cat.field_pic_category_fid');
			$res->addField('fm','uri');
			$res=$res->execute()->fetchAll(PDO::FETCH_ASSOC);

			foreach($res as $x=>$y){
				$res[$x]['img']=image_style_url('product_teaser',$y['uri']);
				$res[$x]['url']=url('taxonomy/term/'.$y['tid']);
			}
			//dsm($res);
			$list=array();
			foreach($res as $v)
				$list[]=theme('catlistfromtel',array('el'=>$v));
				
			

			$b['content']=theme('item_list',array(
				'items'=>$list,
			));
		break;

	}

	return $b;
}
?>