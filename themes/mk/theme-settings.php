<?php 
function mk_form_system_theme_settings_alter(&$form){
	$fd=theme_get_setting('magaz-data');
	$form['magaz-data']=array(
		'#type'=>'fieldset',
		'#title'=>'Данные магазина',
		'#tree'=>true,
		'footer1-left'=>array(
			'#type'=>'textfield',
			'#title'=>'Подвал лево',
			'#description'=>'первая строка',
			'#default_value'=>empty($fd['footer1-left'])?'':$fd['footer1-left'],
		),
		'footer1-right'=>array(
			'#type'=>'textfield',
			'#title'=>'Подвал право',
			'#description'=>'первая строка',
			'#default_value'=>empty($fd['footer1-right'])?'':$fd['footer1-right'],
		),
		'footer2-left'=>array(
			'#type'=>'textfield',
			'#title'=>'Подвал слева',
			'#default_value'=>empty($fd['footer2-left'])?'':$fd['footer2-left'],
		),
		'footer2-center'=>array(
			'#type'=>'textfield',
			'#title'=>'Подвал центр',
			'#default_value'=>empty($fd['footer2-center'])?'':$fd['footer2-center'],
		),
		'footer2-right'=>array(
			'#type'=>'textfield',
			'#title'=>'Подвал справа',
			'#default_value'=>empty($fd['footer2-right'])?'':$fd['footer2-right'],
		),
	);
	$fd=theme_get_setting('nacenka');
	$form['nacenka']=array(
		'#type'=>'fieldset',
		'#title'=>'Данные наценки',
		'#tree'=>true,
		'text'=>array(
			'#type'=>'textfield',
			'#title'=>'Текст наценки',
			'#default_value'=>empty($fd['text'])?'':$fd['text'],
		),
		'size'=>array(
			'#type'=>'textfield',
			'#title'=>'Наценочный порог',
			'#description'=>'Сумма заказа после перехода через которую наценка не будет действовать',
			'#default_value'=>empty($fd['size'])?0:$fd['size'],
			'#field_suffix'=>'р.',
		),
	);
	//dsm($form);
}
?>