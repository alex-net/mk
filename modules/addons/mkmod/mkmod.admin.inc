<?php 
function mkmodadmin_form(){
	$fd=variable_get(__FUNCTION__,array());
	return array(
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Сохранить',
			),
		),
		'mailofadmin'=>array(
			'#type'=>'textfield',
			'#title'=>'Почта админа',
			'#description'=>'Почта для отправки быстрокго заказа',
			'#required'=>true,
			'#default_value'=>empty($fd['mailofadmin'])?'':$fd['mailofadmin'],
		),
		'otsivs-count'=>array(
			'#type'=>'textfield',
			'#title'=>'число коментариев на странице',
			'#size'=>5,
			'#default_value'=>empty($fd['otsivs-count'])?'':$fd['otsivs-count'],
		),
	);
}
//=======================================
function mkmodadmin_form_submit($form,$form_state){
	form_state_values_clean($form_state);
	variable_set($form_state['build_info']['form_id'],$form_state['values']);
	drupal_set_message('Настройки сохранены');
}
// ====================================================
// вдминка складов .. 
function skladconfig_form($form,$form_state){
	$form=array(
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Сохранить',
			),
		),
	);
	$form['skladlist']=array(
		'#type'=>'container',
		'#tree'=>true,
		'#attributes'=>array(
			'class'=>array('skladlist-wrapper'),
		),
	);
	$fd=variable_get('sklad-config',array());// список складов 
	$skladlist=empty($fd['skladlist'])?array():$fd['skladlist'];
	if (!empty($form_state['triggering_element']) && $form_state['triggering_element']['#name']=='addmore'){
		//dfb($form_state['values'],'vals');
		$skladlist=array();
		foreach($form_state['values']['skladlist'] as $y)
			if (!empty($y['name']))
				$skladlist[]=$y;

		$skladlist[]=array();
		//dfb($form_state['triggering_element']);
	}
	if (empty($skladlist))
		$skladlist[]=array();
	$x=0;
	foreach($skladlist as $y){

		$key=empty($y['key'])?user_password(10):$y['key'];
		$form['skladlist'][$key]=array(
			'#type'=>'fieldset',
			'#title'=>sprintf('Склад №%d %s',++$x,empty($y['name'])?:'"'.$y['name'].'"'),
			'#collapsible'=>true,
			'#collapsed'=>true,
			'key'=>array('#type'=>'value','#value'=>$key),
			'name'=>array(
				'#type'=>'textfield',
				'#title'=>'Наименование',
				'#default_value'=>empty($y['name'])?'':$y['name'],
				'#description'=>'Для удадения ненужного - это поле оставить пустым',
			),
			'subname'=>array(
				'#type'=>'textfield',
				'#title'=>'Виды продукции склада',
				'#default_value'=>empty($y['subname'])?'':$y['subname'],
			),
			'addres'=>array(
				'#type'=>'textfield',
				'#title'=>'Адрес',
				'#default_value'=>empty($y['addres'])?'':$y['addres'],
				'#description'=>'можно указывать координаты точки, например, [55.664545 37.673740]',
			),
			'regim'=>array(
				'#type'=>'textarea',
				'#title'=>'Режим работы',
				'#rows'=>2,
				'#default_value'=>empty($y['regim'])?'':$y['regim'],
			),
			'descr'=>array(
				'#type'=>'textarea',
				'#title'=>'Примечание',
				'#default_value'=>empty($y['descr'])?'':$y['descr'],
			),
		);

	}
	$form['addmore']=array(
		'#type'=>'button',
		'#name'=>'addmore',
		'#value'=>'Добавить склад',
		'#ajax'=>array(
			'callback'=>'skladconfig_form_jscb',
		),
	);
	return $form;
}
// ========================================
function skladconfig_form_jscb($form,$form_state){
	$cmd=array();
	//$cmd[]=ajax_command_alert('adas');
	$cmd[]=ajax_command_replace('.skladlist-wrapper',render($form['skladlist']));
	return array('#type'=>'ajax','#commands'=>$cmd);
}
// =========================================
function skladconfig_form_submit($form,$form_state){
	form_state_values_clean($form_state);
	
	$args=array(
		'kind'=>'house',
		'format'=>'json',
	);
	foreach($form_state['values']['skladlist'] as $x=>$y)
		if (empty($y['name']))
			unset($form_state['values']['skladlist'][$x]);
		else{
			if (preg_match('#\[(.+?);(.+?)\]#',$y['addres'],$points)){
				
				$form_state['values']['skladlist'][$x]['point']=array(
					'x'=>floatval($points[2]),
					'y'=>floatval($points[1]),
				);
			}
			else{
				$args['geocode']=$y['addres'];
				// пробить геокодером .. 
				$res=drupal_http_request('https://geocode-maps.yandex.ru/1.x/?'.drupal_http_build_query($args));
				if ($res->code==200){
					$res=drupal_json_decode($res->data);
					if (!empty($res['response']['GeoObjectCollection']['featureMember'][0]['GeoObject']['Point']['pos'])){
						$res=explode(' ',$res['response']['GeoObjectCollection']['featureMember'][0]['GeoObject']['Point']['pos']);
						$form_state['values']['skladlist'][$x]['point']=array(
							'x'=>$res[0],
							'y'=>$res[1],
						);
					}

				}
			}
			
		}

	variable_set('sklad-config',$form_state['values']);
	drupal_set_message('Настройки сохранены');
}
// ================================================
function mkmod_otzivs_form(){
	return array(
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Применить',
			),
		),
		'type'=>array(
			'#type'=>'radios',
			'#title'=>'Типы отображения отзывывов',
			'#options'=>array(
				0=>'Отключить отзывы',
				1=>'Запретить оставлять новые отзывы',
				2=>'разрешить просмотривать и оставлять новые отзывы',
			),
		),
	);
}
// ===================================
function mkmod_otzivs_form_submit($form,$form_state){
	$ot=$form_state['values']['type'];
	$res=db_select('node','n');
	$res->condition('n.type','product_display');
	$res->fields('n',array('nid'));
	$nids=$res->execute()->fetchCol();
	if ($nids)
		foreach(array('node','node_revision') as $t){

			$res=db_update($t);
			$res->condition('nid',$nids);
			$res->fields(array('comment'=>$ot));
			$res->execute();
		}
	drupal_set_message('Выполнено');
	//dsm($ot);
}
// =============================================================================
// Настройка текстов акций 
function discounts_config_form(){
	$fd=variable_get('discounts config',array());
	$form=array(
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Сохранить',
			),
		),
		'block-top-mess'=>array(
			'#type'=>'textfield',
			'#default_value'=>empty($fd['block-top-mess'])?'':$fd['block-top-mess'],
			'#title'=>'Надпись в блоке акций',
		),
		'mess-on-page-exist'=>array(
			'#type'=>'textfield',
			'#title'=>'Надпись на странице акций (акции есть)',
			'#default_value'=>empty($fd['mess-on-page-exist'])?'':$fd['mess-on-page-exist'],
		),
		'mess-on-page-void'=>array(
			'#type'=>'textfield',
			'#title'=>'Надпись на странице акций (акций нет)',
			'#default_value'=>empty($fd['mess-on-page-void'])?'':$fd['mess-on-page-void'],
		),
	);
	return $form;
}
// ===============================================
function discounts_config_form_submit($form,$form_state){
	form_state_values_clean($form_state);
	variable_set('discounts config',$form_state['values']);
	drupal_set_message('Настройки сохранены');

}
?>