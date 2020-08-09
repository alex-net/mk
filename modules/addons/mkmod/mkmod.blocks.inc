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
		'top-sales'=>[
			'info'=>'Топ Продаж',
		],
		'news-list'=>[
			'info'=>'Новости',
		],
		'articles-list'=>[
			'info'=>'Статьи',
		],
		'left-articles-list'=>[
			'info'=>'Статьи слева 3',
		],
		'left-news-list'=>[
			'info'=>'Новости слева 3',
		],
		
		'sub-terms'=>[
			'info'=>'Подрубрики каталога',
			'cache' => DRUPAL_CACHE_PER_PAGE,
		],

		'term-products-and-links'=>[
			'info'=>'Тексты и ссылки в раделе каталога',
			'cache' => DRUPAL_CACHE_PER_PAGE,
		],

		'hit-prodag'=>array(
			'info'=>'Хит продаж',
		),
		'akcii-slider-big'=>array(
			'info'=>'Акции слайдер большой',
		),
		'catlist'=>array(
			'info'=>'Категории товаров',
		),
		'ad-block'=>array(
			'info'=>'Объявления',		
		),
		'product-filter'=>[
			'info'=>'Фильтр товаров',
		],
	);
}
function mkmod_block_configure ($delta=''){
	$form=array();
	$fd=variable_get('mkmod blocks '.$delta,array());
	switch($delta){
		case 'akcii-slider-big':
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
		// топ продаж 
		case 'top-sales':
			$hitnids=getTopSalesNids(4);
			if ($hitnids)
				$b['content']=node_view_multiple( node_load_multiple($hitnids));
			

			//dsm($hitnids);
			//$b['content']='dsa';
			break;
		// список новостей ..
		case 'news-list':
		case 'left-news-list':
			$res=db_select('node','n');
			$res->range(0,3);
			$res->condition('n.type','new');
			$res->condition('n.status',1);
			$res->fields('n',['nid']);
			$res->orderBy('n.created','desc');
			$res=$res->execute()->fetchCol();
			if (!$res)
				break;
			$b['content']=node_view_multiple(node_load_multiple($res),'inpopup');
			if ($delta=='left-news-list')
				$b['content']['all']=[
					'#type'=>'link',
					'#title'=>'Все новости',
					'#href'=>'/news',
					'#attributes'=>['class'=>['all-content']],
					//'#options'=>['class'=>['all-content']],
				];
			break;
		// статьи .. на главной .. 	
		case 'articles-list':
		case 'left-articles-list':
			$res=db_select('node','n');
			if ($delta=='articles-list')
				$res->range(0,20);
			else
				$res->range(0,3);
			$res->condition('n.type','article');
			$res->condition('n.status',1);
			$res->fields('n',['nid']);
			$res->orderBy('n.created','desc');
			$res=$res->execute()->fetchCol();
			if (!$res)
				break;
			$b['content']=node_view_multiple(node_load_multiple($res),'inpopup');
			if ($delta=='left-articles-list')
				$b['content']['all']=[
					'#type'=>'link',
					'#title'=>'Все статьи',
					'#href'=>'/articles',
					'#attributes'=>['class'=>['all-content']],
					//'#options'=>['class'=>['all-content']],
				];

			break;


		case 'hit-prodag':
			$nids=getTopSalesNids(4);
			if ($nids)
				$b['content']=theme('topprodaglist',array(
					'list'=>$nids,
				));
		break;
		case 'ad-block':
			// запрашваем акции  
			$els=_getactionprodag();
			if ($els)
				break;
			$res=db_select('node','n');
			$res->condition('n.type','ad_for_main');
			$res->fields('n',array('nid'));
			$res->orderby('n.created','asc');
			$res=$res->execute()->fetchCol();
			if ($res){
				$res=node_view_multiple(node_load_multiple($res));
				$res['nodes']['#prefix']='<div class="slider-ad-wrapper">';
				$res['nodes']['#suffix']='</div>';
				$b['content']=render($res);
			}
			//$b['content']='adad';
		break;
		// блок слайдеров 
		case 'akcii-slider-big':
			// Достать акционные товары
			$els=getActionProdag(1);
			//dsm($els);
			
			if ($els){
				foreach($els as $x=>$y){
					$els[$x]['img']=image_style_url('350x170',$y['uri']);
					$els[$x]['url']=url('node/'.$x);
					$els[$x]['oldp']=number_format($y['oldp']/100,0,',',' '); //commerce_currency_format($y['oldp'],null);
					$els[$x]['cp']= number_format($y['cp']/100,0,',',' '); //commerce_currency_format($y['cp'],null);
					$els[$x]['measure']=drupal_strtolower($y['measure']);
					$s=strip_tags($els[$x]['body']);
					$els[$x]['body']=drupal_strlen($s)>150?drupal_substr($s,0,150).'...':$s;
					$els[$x]['classe']='akcia-'.rand(1,2);
					$els[$x]['type']='akcia';
				}
			}
			// запрос новостей .. 
			$res=db_select('node','n');
			$res->range(0,3);
			$res->condition('n.type','new');
			$res->condition('n.status',1);
			$res->orderby('n.created','desc');
			$res->fields('n',['nid','title']);
			$res->leftJoin('field_data_body','b','b.entity_id=n.nid and b.bundle=n.type');
			$res->fields('b',['body_value']);
			$res=$res->execute();
			$res=$res->fetchAll(PDO::FETCH_ASSOC);
			foreach($res as $x=>$y){
				$s=strip_tags($y['body_value']);
				$els[]=[
					'type'=>'news',
					'classe'=>'news-'.rand(1,2),
					'body'=>drupal_strlen($s)>150?drupal_substr($s,0,150).'...':$s,
					'title'=>$y['title'],
					//'titlebottom'=>'',
					'url'=>url('node/'.$y['nid']),
				];
			}

				//dsm($els);
				$b['content']=array(
					'slid-first'=>array(
						'#theme'=>'sliderbigel',
						'#data'=>$els,
						//'#prefix'=>'<div class="slider-main-big">',
						//'#suffix'=>'</div>',
					),
					/*'slid-second'=>array(
						'#theme'=>'slidersmalel',
						'#data'=>$els,
						'#prefix'=>'<div class="slider-main-small clearfix">',
						'#suffix'=>'</div>',
					),*/
					'#attached'=>array(
						'js'=>array(
							array('data'=>array('accii-slider-speed'=>empty($fd['timeslide'])|| !is_numeric($fd['timeslide']) ?3:intval($fd['timeslide'])),'type'=>'setting'),
						),
					),
				);
			
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
		// подуровни каталога .. .
		case 'sub-terms':
			$data = array();
			$term = taxonomy_term_load(arg(2));

			// Выводим только на Каталоге
		    if(!$term || $term->vocabulary_machine_name !== 'categories')
				return false;

			// Выводим только на 1-м уровне таксономии
			/*$query = db_select('taxonomy_term_hierarchy', 't');
			$query->fields('t', array('parent'));
			$query->condition('tid', $term->tid);
			$parent = $query->execute()->fetchField();*/
			    /*if($parent !== '0'){
			        return false;
			    }
			    */
			// Формируем array для рендера
			$children = taxonomy_get_children($term->tid, $term->vid);
			
			foreach($children as $child){
				if (!$child->vis)
					continue;
				$data[$child->tid] = $child;
				$che=taxonomy_get_children($child->tid, $child->vid) ;// : false;;
				foreach($che as $x=>$y)
					if (!$y->vis)
						unset($che[$x]);
				$data[$child->tid]->children = $che;
			}
    //dsm($children);

    //return theme('catalog_children_terms', array('data' => $data));

			$b['content']=theme('subtermsview',['list'=>$data]);
		break;

		// фильтр товаров ...
		case 'product-filter':
			if (preg_match('#^taxonomy/term/(\d+)$#i', current_path(),$tid)){
				$form=drupal_get_form('pricefilter_form',end($tid));
				if (empty($form['#disabled']))
					$b['content']=$form;
			}
				
		break;
		// блок текстов ссылок и картинок .. из  хитрого поля в термине таксономии .каталога ..
		case 'term-products-and-links':
			if(!preg_match('#^taxonomy/term/(\d+)$#i',current_path(),$id))
				break;
			$term=taxonomy_term_load(end($id));
			$tal=field_get_items('taxonomy_term',$term,'field_block_pic_text_prod');
			if (empty($tal))
				break;
			$list=[];
			foreach($tal as $el)
				$list[]=$el['value'];
			if (empty($list))
				break;

			$list=entity_load('field_collection_item',$list);
			foreach($list as $x=>$el){
				$text=field_get_items('field_collection_item',$el,'field_text');
				$pics=field_get_items('field_collection_item',$el,'field_products_links');
				if (empty($pics))
					$pics=[];
				foreach($pics as $a=>$p)
					$pics[$a]=$p['value'];
				if ($pics){
					$pics=entity_load('field_collection_item',$pics);
					foreach($pics as $k=>$v){
						$link=field_get_items('field_collection_item',$v,'field_h3_link');
						$img=field_get_items('field_collection_item',$v,'field_pic_product_link');
						$pics[$k]=[
							'link'=>$link[0]['url'],
							'title'=>$link[0]['title'],
							'pic'=>$img[0]['uri'],
						];
					}

				}
				// если везде пусто - удаляем элемент..
				if (empty($pics) && empty($text)){
					unset($list[$x]);
					continue;
				}
				$list[$x]=[
					'text'=>$text[0]['value']??'',
					'pics'=>$pics,
				];
			}
			//dsm($list);
			if (!$list)
				break;

			$b['content']=theme('cat_txt_links_pics',['els'=>$list]);
		break;
	}



	return $b;
}
