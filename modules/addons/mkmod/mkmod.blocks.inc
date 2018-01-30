<?php 
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
// ====================================
function mkmod_block_view($delta=''){
	$b=array();
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
					'#attaced'=>array(
						'libraries'=>array(

						),
					),
				);
			}
		break;
		case 'akcii-slider-block':
			$els=_getactionprodag();
			if (empty($els))
				break;
			$fd=variable_get('discounts config',array());
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
			if (!empty($fd['block-top-mess']))
				$out['head']=array(
					'#markup'=>$fd['block-top-mess'],
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