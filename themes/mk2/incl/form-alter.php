<?php


/**
 * Alter для всех форм ...   
 * @param  array &$form       массив формы ..
 * @param  array &$form_state данные формы (массив form_state
 * @param  string $form_id     Идентификатор формы
 */
function mk2_form_alter(&$form,&$form_state,$form_id)
{
	if (preg_match('#mkmodformaddtocart_.*?_form#', $form_id)){
		// оборачиваем кнопку .. 
		$form['actions']['submit']=array_merge($form['actions']['submit'],[
			'#prefix'=>'<span class="btn-submit">купить',// <i class="fas fa-shopping-cart"></i>
			'#suffix'=>'</span>',
		]);
		// оборачиваем input количества .. для стрелок ..
		$form['qty-wrap']['qty']=array_merge($form['qty-wrap']['qty'],[
			'#prefix'=>'<div class="qty-wrapp2"><span class="left-btn arrow"><i class="fas fa-chevron-left"></i></span>',
			'#suffix'=>'<span class="right-btn arrow"><i class="fas fa-chevron-right"></i></span></div>',
		]);
		if (!empty($form['productdata']['#value']['#settings']['viewotherbuttons']))
			$form['#theme']='fullproductbuttons';
		//dsm($form_state['dd']['#settings']['viewotherbuttons'],'form_state');
	}

	//dfb($form_id,'form_id');
	if(in_array($form_id,['webform_client_form_1562','webform_client_form_1682'])) {
		$form['#attached']['library'][]=['mklibs','inputmask'];
		//dfb(array_keys($form),'fr');
		$form['submitted']['telefon']['#attributes']['data-inputmask']="'mask':'+7(999)999-99-99'";
		
	}
}



/**
 * форма поиска 
 * @param  array &$form массив формы .. 
 * @param  array &$fs   данные формы (массив form_state
 */
function mk2_form_search_form_alter(&$form,&$fs)
{
	$form['basic']['keys']['#title_display']='invisible';
	$form['basic']['keys']['#attributes']['placeholder']='Поиск товара по сайту';
	$form['basic']['submit']['#value']='Найти';
	$form['basic']['close']=[
		'#type'=>'markup',
		'#markup'=>'<span class="close-btn" ><i class="far fa-times-circle"></i></span>',
	];
	//dsm($form);
}


function mk2_form_views_form_commerce_cart_form_default_alter(&$form,&$form_state)
{
	
	$form['actions']['clear']=[
		'#type'=>'link',
		'#href'=>'cart-clear',
		'#title'=>'Очистить корзину',
		'#weight'=>-5,
		'#attributes'=>['class'=>['clear-btn']],
	];
	
}


// =======================================
function mk2_form_commerce_checkout_form_checkout_alter(&$form,$form_state)
{
	foreach (element_children($form['buttons']) as $x)
		unset($form['buttons'][$x]['#prefix'],$form['buttons'][$x]['#suffix']);
	$form['buttons']['#weight']=10;
	$form['buttons']['continue']['#weight']=15;	
	$form['buttons']['continue']['#value']='Заказ подтверждаю';
	//dsm($form);
	$form['addons']=[
		'#type'=>'fieldset',
		'#attributes'=>[
			'class'=>['addons'],
		],
		'accept'=>[
			'#type'=>'checkbox',
			'#prefix'=>'<div class="el-assept-politik">',
			'#suffix'=>'</div>',
			'#weight'=>5,
			'#title'=>'Я даю своё согласие на обработку моих персональных данных. ',
			'#required'=>true,
		],
		'ppolitic'=>[
			'#prefix'=>'<div class="form-wrapper link-politik">',
			'#suffix'=>'</div>',
			'#markup'=>'<p class="center">'.l('Политика конфиденциальности','politika-konfidencialnosti').'</p>',
			'#weight'=>7,
		]
	];
	$form['#attached']['library'][]=['mklibs','inputmask'];
	$form['customer_profile_billing']['field_user_phone'][LANGUAGE_NONE][0]['value']['#attributes']['data-inputmask']="'mask':'+7(999)999-99-99'";
	//dsm($form);

}