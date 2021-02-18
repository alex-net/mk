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
			'#prefix'=>'<span class="btn-submit">в корзину',// <i class="fas fa-shopping-cart"></i>
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
	if ($form_id=='comment_node_product_display_form'){
		unset($form['field_rating'][LANGUAGE_NONE]['#options']['_none']);
		//dsm($form,'form');
	}

	// ловим капчу .. 
	if (isset($form['captcha']))
		$form['captcha']['#after_build'][]='mkcaptchastyler_abcb';
}


function mkcaptchastyler_abcb($el)
{
	$el['captcha_widgets']['captcha_response']['#title_display']='invisible';
	$el['captcha_widgets']['captcha_response']['#description']='';
	$el['captcha_widgets']['captcha_response']['#attributes']['placeholder']="Введите код *";
	return $el;
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
	$form['customer_profile_billing']['field_comments_to_order'][LANGUAGE_NONE][0]['value']['#default_value']='';

	//dsm($form);

}


function mk2_form_comment_node_product_display_form_alter(&$form,&$form_state)
{
	global $user;
	if (empty($form_state['fkey']))
		$form_state['fkey']=user_password();
	$form['#attributes']['class'][]='form-selector-'.$form_state['fkey'];

	$form['author']['#weight']=10;
	// field_trating
	$form['field_trating'][LANGUAGE_NONE][0]['rating']['#widget']=array('name'=>'basic','css'=>'basic');
	//dsm($form['field_trating'][LANGUAGE_NONE][0]['rating'],'rating');
	
	array_unshift($form['actions'],array(
		'#markup'=>'Ваш отзыв будет опубликован на сайте после проверки модератором.',
		'#prefix'=>'<span class="descr">',
		'#suffix'=>'</span>',
	));
	$form['actions']['submit']['#value']='Оставить отзыв';
	if ($user->uid)
		foreach($form['author'] as $x=>$y)
			if (!empty($y['#type']) && $y['#type']=='item')
				$form['author'][$x]['#access']=false;
}