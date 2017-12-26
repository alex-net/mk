<?php 
function mk_form_system_theme_settings_alter(&$form){
	$fd=theme_get_setting('magaz-data');
	$form['magaz-data']=array(
		'#type'=>'fieldset',
		'#title'=>'Данные магазина',
		'#tree'=>true,
		'footer-left'=>array(
			'#type'=>'textfield',
			'#title'=>'Подвал слева',
			'#default_value'=>empty($fd['footer-left'])?'':$fd['footer-left'],
		),
		'footer-center'=>array(
			'#type'=>'textfield',
			'#title'=>'Подвал центр',
			'#default_value'=>empty($fd['footer-center'])?'':$fd['footer-center'],
		),
		'footer-right'=>array(
			'#type'=>'textfield',
			'#title'=>'Подвал справа',
			'#default_value'=>empty($fd['footer-right'])?'':$fd['footer-right'],
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