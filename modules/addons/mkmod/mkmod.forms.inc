<?php 
// быстрый заказ
function mkm_quickzakaz_form($form,$form_state,$params=array()){
	$form=array(
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Отправить',
				'#ajax'=>array(
					'callback'=>'mkm_quickzakaz_form_jscb',
				),
			),
		),
		'titl'=>array(
			'#markup'=>'Быстрый заказ',
			'#prefix'=>'<div class="popup-titl">',
			'#suffix'=>'</div>',
		),
		'phone'=>array(
			'#type'=>'textfield',
			'#required'=>true,
			'#title'=>'Телефон',
			'#title_display'=>'invisible',
			'#attributes'=>array(
				'placeholder'=>'Телефон*',
				'data-masked'=>'+7(999)999-99-99',
			),
			'#size'=>30,
		),
		'name'=>array(
			'#type'=>'textfield',
			'#title'=>'Ваше имя',
			'#title_display'=>'invisible',
			'#required'=>true,
			'#attributes'=>array(
				'placeholder'=>'Ваше имя*',
			),
			'#size'=>30,
		),
	);
	if (!empty($params['from-nid']))
		$form['from-nid']=array(
			'#type'=>'value',
			'#value'=>$params['from-nid'],
			'#title'=>'Товар',
		);
	return $form;
}
// ================================================
function mkm_quickzakaz_form_jscb($form,$form_state){
	$cmd=array();
	$form['mess']=array(
		'#theme'=>'status_messages',
		'#weight'=>-1,
	);
	if (!form_get_errors())
		$form=array($form['mess']);
	$cmd[]=ajax_command_replace('.'.$form_state['fselector'],render($form));
	$cmd[]=array('command'=>'update_size_of_popup');
	return array('#type'=>'ajax','#commands'=>$cmd);
}
// ====================================================
function mkm_quickzakaz_form_submit($form,$form_state){
	drupal_set_message('Ваш заказ отправлен');
	form_state_values_clean($form_state);
	$vals=$form_state['values'];
	$fd=variable_get('mkmodadmin_form',array());
	// если нет ящика .. ничего не делаем . ..
	if (empty($fd['mailofadmin']))
		return ;
	if ($vals['from-nid']){
		$res=db_select('node','n');
		$res->condition('n.nid',$vals['from-nid']);
		$res->fields('n',array('title'));
		$res=$res->execute()->fetchField();
		$vals['from-nid']=l($res,'node/'.$vals['from-nid'],array('absolute'=>true));
	}

	$rows=array();
	foreach($vals as $x=>$y)
		$rows[]=array($form[$x]['#title'],$y);
	$mess=theme('table',array(
		'caption'=>'Новый быстрый заказ',
		'header'=>array('Поле','Значение'),
		'rows'=>$rows,
		'sticky'=>false,
		'empty'=>'Нет данных',
		'attributes'=>array(
			'border'=>'1',
			'cellpadding'=>5,
		),
	));

	$headers='MIME-Version: 1.0' . "\r\n";
	$headers.='Content-type: text/html; charset=utf8' . "\r\n";
	mail($fd['mailofadmin'],sprintf('"Быстрый заказ" для %s от %s',$vals['phone'],date('Y-m-d H:i',REQUEST_TIME)),$mess,$headers);
}
/// ===============================================================
function mkmod_forms($form_id,$args){
	$forms=array();
	if (preg_match('#^mkmodformaddtocart_((?:\d+_)+)form$#i', $form_id,$pids)){
		$forms[$form_id]=array(
			'callback'=>'formaddtocart_form',
		);
	}
	return $forms;
}
//=================================================================
// форма добавления в корзину .. 
function formaddtocart_form($form,&$form_state,$dd,$nid){
	//dsm($dd);
	unset($form_state['input']);
	if (empty($form_state['fromnid']))
		$form_state['fromnid']=$nid;
	if (empty($form_state['dd']))
		$form_state['dd']=$dd;
	$dd=$form_state['dd'];
	$form_state['fselector']=empty($form_state['fselector'])?user_password():$form_state['fselector'];

	//dsm($dd,'$dd');
	$form=array(
		'#attributes'=>array(
			'class'=>array('mk-form-add-to-cart','mk-form-add-cart-'.$form_state['fselector']),
		),
		'#attached'=>array(
			'js'=>array(
				array('data'=>drupal_get_path('module','mkmod').'/mkmod-formaddtocart.js','type'=>'file'),
				array('data'=>array('qtdata'=>array(
					$form_state['build_info']['form_id']=>$dd,
				)),'type'=>'setting'),
			),
		),
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Купить',
				'#ajax'=>array(
					'callback'=>'formaddtocart_form_jscb',
					'progress'=>array(),
				),
			),
		),
		'qty-wrap'=>array(
			'#type'=>'container',
			'#attributes'=>array(
				'class'=>array('qty-wrapp','container-inline'),
			),
			'qty'=>array(
				'#type'=>'textfield',
				'#default_value'=>1,
				'#required'=>true,
				'#title_display'=>'invisible',
				'#size'=>5,
				'#title'=>'Количество',
				'#attributes'=>array(
					'title'=>'Количество',
				),
			),
			'real-cost'=>array(
				'#markup'=>'',
				'#prefix'=>'<div class="real-cost">',
				'#suffix'=>'</div>',
			),
		),
		
	);
	///$form['#validate']=array('formaddtocart_form_validate');
	return $form;
}
//=======================================================
function formaddtocart_form_validate(&$form,&$form_state){
	///dsm($form,'$formv');
	$val=$form['qty-wrap']['qty']['#value'];
	if (!is_numeric($val) || intval($val)<1)
		form_error($form['qty-wrap']['qty'],'Количество должно быть целым положительным числом');

}
// ===========================================================
function formaddtocart_form_jscb($form,$form_state){
	$cmd=array();
	if (form_get_errors()){

		// вываливаем сообщение 
		$cmd[]=array(
			'command'=>'show_in_popup',
			'content'=>theme('status_messages'),
		);
		// перебиваем форму
		$cmd[]=ajax_command_replace('.mk-form-add-cart-'.$form_state['fselector'],render($form));
		// тыкаем клиента носом в ошибку 
		$cmd[]=array('command'=>'focustoerrorfield');
	}
	else{
		$html=views_embed_view('commerce_cart_block', 'default');
		$cmd[]=ajax_command_html('.logo_contacts_cart .cart',$html);
		// показываем уведомлялку 
		if($form_state['li-id']){
			$win=views_embed_view('confirm_message_product_display','default',$form_state['li-id']);
			$win.='<a href="#" class="commerce-add-to-cart-confirmation-close"><span class="element-invisible">Закрыть</span></a><div class="clearfix"></div>';
			$win='<div class="messages commerce-add-to-cart-confirmation"><div class="message-inner">'.$win.'</div></div>';
			$cmd[]=ajax_command_prepend('#main_content',$win);
			/*
			$cmd[]=array(
				'command'=>'show_in_popup',
				'content'=>$win,
				'wrapCSS'=>'messages commerce-add-to-cart-confirmation',
				'fitToView'=>false,

			);*/


			//dsm($win,'$win');
		}
		
	}


	return array('#type'=>'ajax','#commands'=>$cmd);
}
// ============================================================
function formaddtocart_form_submit($form,&$form_state){
	form_state_values_clean($form_state);
	global $user;
	$vals=$form_state['values'];
	//dfb($vals,'$vals');
	$dd=$form_state['dd'];
	//dfb($dd,'$dd');
	$pid=0;
	foreach($form_state['dd'] as $p)
		if ( 
			(!empty($p['from']) && $vals['qty']>=intval($p['from']) || empty($p['from']) ) &&  
			(!empty($p['to']) && $vals['qty']<=intval($p['to']) || empty($p['to']) )
		)
			$pid=$p['product_id'];
	if ($pid){
		$pid=commerce_product_load($pid);
		$li=commerce_product_line_item_new($pid,$vals['qty']);
		drupal_alter('commerce_product_calculate_sell_price_line_item', $li);
		rules_invoke_event('commerce_product_calculate_sell_price', $li);

    // Only attempt an Add to Cart if the line item has a valid unit price.
		$line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $li);

		if (!is_null($line_item_wrapper->commerce_unit_price->value())) {
			
			// 
			// Add the product to the specified shopping cart.
			$li=commerce_cart_product_add(
				$user->uid,
				$li, 
				isset($li->data['context']['add_to_cart_combine']) ? $line_item->data['context']['add_to_cart_combine'] : TRUE
			);
			$form_state['li-id']=$li->line_item_id;
			//dfb($li,'li');
		}


	}	

	//dsm($form_state['values'],'values');
}
// ==========================================
function product_finder_form(){
	$form=array(
		'#attributes'=>array(
			'class'=>array('container-inline'),
		),
		'prod'=>array(
			'#type'=>'textfield',
			'#title'=>'Артикул',
			'#size'=>10,
			'#required'=>true,
		),
		'submit'=>array(
			'#type'=>'submit',
			'#value'=>'Перейти на страницу витрины',
		),
	);
	return $form;
}
// ====================================
function product_finder_form_validate($form,&$form_state){
	$id=$form['prod']['#value'];
	if (!is_numeric($id))
		form_error($form['prod'],'Должно быть числовое значение ');
	if (is_numeric($id) ){
		$res=db_select('commerce_product','cp');
		$res->condition('cp.sku',addslashes($id));
		$res->leftjoin('field_data_field_product_variations','p','p.field_product_variations_product_id=cp.product_id');
		$res->addField('p','entity_id');

		$res=$res->execute()->fetchField();
		if (empty($res))
			form_error($form['prod'],'Товар не найден');
		else
			form_set_value($form['prod'],$res,$form_state);
	}
}
// =======================================
function product_finder_form_submit($form,&$form_state){
	form_state_values_clean($form_state);

	$form_state['redirect']='node/'.$form_state['values']['prod'];
	//dsm($vals,'$vals');
}



// =====================================================================
// форма заполнения реквизитов 
function mkrekvisits_form($form,$form_state){
	$form=array(
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#value'=>'Сохранить данные',
				'#type'=>'submit',
			),
		),
	);

	$armas=mkmod_getrekvlist();
	$fd=variable_get('site-trkvs',array());
	$form['settings']=array(
		'#type'=>'fieldset',
		'#title'=>'Настройки',
		'#tree'=>true,
		'#collapsed'=>true,
		'#collapsible'=>true,
		'phones'=>array(
			'#type'=>'textfield',
			'#title'=>'Число телефонов',
			'#default_value'=>empty($fd['settings']['phones'])?0:$fd['settings']['phones'],
		),
		'mails'=>array(
			'#type'=>'textfield',
			'#title'=>'Число почт',
			'#default_value'=>empty($fd['settings']['mails'])?0:$fd['settings']['mails'],
		),
		'addresses'=>array(
			'#type'=>'textfield',
			'#title'=>'Число адресов',
			'#default_value'=>empty($fd['settings']['addresses'])?0:$fd['settings']['addresses'],
		),
	);
	$form['rekv']=array(
		'#type'=>'fieldset',
		'#title'=>'Список реквизитов и важных данных',
		'rekv'=>array(
			'#tree'=>true,
			'#theme'=>'formtable',
			'#header'=>array('Название','токен','Значение'),
		),
	);
	$fields=mkmod_getrekvlist();
	foreach(array(
		'phones'=>array('k'=>'phone','t'=>'Телефон'),
		'mails'=>array('k'=>'mail','t'=>'Почта'),
		'addresses'=>array('k'=>'address','t'=>'Адрес',),
	) as $x=>$y)
		if (!empty($fd['settings'][$x]))
			for($i=1;$i<=$fd['settings'][$x];$i++)
				$fields[$y['k'].'-'.$i]=$y['t'];
	foreach($fields as $k=>$t)
		$form['rekv']['rekv'][$k]=array(
			array('#markup'=>$t),
			array('#markup'=>"[ mk:rekv:$k ]"),
			array(
				'#type'=>'textfield',
				'#default_value'=>empty($fd['rekv'][$k])?'':$fd['rekv'][$k],
			),
		);
	return $form;
}
//=================================================
function mkrekvisits_form_submit($form,$form_state){
	form_state_values_clean($form_state);
	$vals=$form_state['values'];
	$vals['rekv']=array_map('reset', $vals['rekv']);
	variable_set('site-trkvs',$vals);
	drupal_set_message('Настройки сохранены');
}
?>