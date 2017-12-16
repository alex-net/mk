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
	//dsm($form);
}
?>