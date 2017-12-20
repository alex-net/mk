<?php 
function otzyvy_publicate_config_form($form){
	$fd=variable_get('otzyvy-publicate-config',array());
	$res=db_select('node','n');
	$res->condition('n.type','webform');
	$res->condition('n.status',1);
	$res->fields('n',array('nid','title'));
	$forms=$res->execute()->fetchAllKeyed();
	$form=array(
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Сохранить',
			),
		),
		'webform'=>array(
			'#type'=>'select',
			'#title'=>'Форма источник отзывов',
			'#options'=>$forms,
			'#required'=>true,
			'#default_value'=>empty($fd['webform'])?'':$fd['webform'],
		),
		'empty-text'=>array(
			'#type'=>'textarea',
			'#title'=>'Текст на странице, если отзывов нету',
			'#default_value'=>empty($fd['empty-text'])?'':$fd['empty-text'],
		),
	);
	return $form;
}
// ==========================================
function otzyvy_publicate_config_form_submit($form,$form_state){
	form_state_values_clean($form_state);
	variable_set('otzyvy-publicate-config',$form_state['values']);
	drupal_set_message('Настройки сохранены');
}

?>