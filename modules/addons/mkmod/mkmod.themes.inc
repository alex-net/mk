<?php 
// ====================================================
function mkmod_theme(){
	return array(
		'skladmapballoon'=>array(
			'variables'=>array(
				'title'=>'Заголовок склада',
				'subname'=>'',// текст под заголовкам
				'timepn'=>'',// время работы понедельник пятница
				'vihi'=>'',// выходные 
				'descr'=>'', // доп инфа 
				'addres'=>'',//адрес
				'tel'=>'',// телефон 
			),
			'template'=>'skladmapballoon',
		),
		'topprodaglist'=>array(
			'render element'=>'list',
			'template'=>'topprodaglist',
			'preprocess functions'=>array('topprodaglist_prefunc'),
			'file'=>'mkmod.themes.inc',
		),
		// большой слайдер с акциями ...(единичка)
		'sliderbigel'=>array(
			'variables'=>array(
				'data'=>array(),
			),
			'template'=>'sliderbigel',
		),
		// мелкий слайдер на главной ( по 3 штуки ) сидит под большим и управляет большим . 		
		'slidersmalel'=>array(
			'variables'=>array(
				'data'=>array(),
			),
			'template'=>'slidersmalel',
		),
		// слайдер акций .  в сайтбаре
		'slidersidebarel'=>array(
			'variables'=>array(
				'data'=>array(),
			),
			'template'=>'slidersidebarel',
		),
		'catlistfromtel'=>array(
			'variables'=>array(
				'el'=>array(),
			),
			'template'=>'catlistfromtel',
		),
		'ppswitcher'=>array(
			'variables'=>array(
				'list'=>array(),
			),
		),
	);
}
// =====================================================
function theme_ppswitcher($vars){
	$links=array();
	global $pp_size;
	//kprint_r($_COOKIE);
	$pp=10;
	if (!empty($pp_size))
		$pp=intval($pp_size);
	foreach($vars['list'] as $x){
		$classes=array();
		if ($pp==$x)
			$classes[]='current';
		$links[]=array(
			'href'=>current_path(),
			'title'=>$x,
			'attributes'=>array(
				'title'=>$x.' записей на стрницу',
				'class'=>$classes,
			),
			'fragment'=>$x,
			//'query'=>array('perp_page'=>),
		);
	}
	drupal_add_js(drupal_get_path('module','mkmod').'/ppswitcher.js');
	drupal_add_library('system','jquery.cookie');
	return theme('links',array(
		'links'=>$links,
		'attributes'=>array(
			'class'=>array('per-page-sizer'),
		),
	));
}
// ======================================================
function topprodaglist_prefunc(&$vars){
	//dsm($vars['list']);
	$res=db_select('node','n');
	$res->condition('n.nid',$vars['list']);
	$res->fields('n',array('nid','title'));
	$res->leftJoin('field_data_field_pic_product','fi','fi.entity_id=n.nid and fi.bundle=n.type');
	$res->leftjoin('file_managed','fm','fm.fid=fi.field_pic_product_fid');
	$res->addField('fm','uri','uri');
	$res->leftjoin('field_data_field_product_variations','ep','ep.entity_id=n.nid and ep.bundle=n.type');
	$res->leftjoin('commerce_product','p','ep.field_product_variations_product_id=p.product_id and p.status=1');
	$res->leftjoin('field_data_commerce_price','cp','cp.entity_id=p.product_id');
	$res->addExpression('round(min(cp.commerce_price_amount)/100)','price');
	$res->leftjoin('field_data_field_unit_measure','ed','ed.entity_id=p.product_id');
	$res->leftjoin('taxonomy_term_data','td','td.tid=ed.field_unit_measure_tid');
	$res->addField('td','name','ed');
	$res->groupBy('n.nid');
	$res=$res->execute()->fetchAllAssoc('nid',PDO::FETCH_ASSOC);
	$list=array();
	foreach($vars['list'] as $x)
		if (!empty($res[$x])){
			$img=theme('image',array(
				'path'=>image_style_url('60x40',$res[$x]['uri']),
				'attributes'=>array(),
			));
			
			$list[$x]=array(
				
					'link'=>l($res[$x]['title'],'node/'.$res[$x]['nid']),
					'img'=>l($img,'node/'.$res[$x]['nid'],array(
						'html'=>true,
					)),
					'price'=>'от <span>'.$res[$x]['price'].' руб./'.$res[$x]['ed'].'</span>',
					
				
			);
		}
	//dsm($list,'$res');
	$vars['list']=$list;

	$vars['classes_array']=$vars['attributes_array']=$vars['title_attributes_array']=$vars['content_attributes_array']=array();
}
?>