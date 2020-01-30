<?php 

function mkmod_forms($form_id,$args){
	$forms=[];
	// форма добавления в корзину .. 
	if (preg_match('#^mkmodformaddtocart_((?:\d+_)+)form$#i', $form_id,$pids))
		$forms[$form_id]=['callback'=>'formaddtocart_form',];
	//форма поиска надо сделать дубль . 
	if (preg_match('#sf_\d+#', $form_id))
		$forms[$form_id]=['callback'=>'search_form'];

	return $forms;
}
//=================================================================
/**
 * форма добавления в корзину .. 
 * @param  array $dd          данные по товара .. + другие настройки 
 * @param  int $nid         номе рноды витрины 
 */
function formaddtocart_form($form,&$form_state,$dd,int $nid){
	//dsm($dd);
	unset($form_state['input']);
	
	$ddasarray=$dd;
	unset($ddasarray['#settings']);
	$form_state['fselector']=$form_state['fselector']??user_password();
	// поиск минимального количества товару .. 
	$co=0;
	foreach($ddasarray as $el){
		if (isset($el['from']) && (!$co || $el['from']<$co))
			$co=$el['from'];
		if(isset($el['to']) && !isset($el['from'])){
			$co=1;break;
		}
	}


	if (!$co)
		$co=1;
	//dsm($dd,'$dd');
	$form=[
		'#attributes'=>[
			'class'=>['mk-form-add-to-cart','mk-form-add-cart-'.$form_state['fselector']],
		],
		'#attached'=>[
			'js'=>[
				['data'=>drupal_get_path('module','mkmod').'/mkmod-formaddtocart.js','type'=>'file'],
				['data'=>['qtdata'=>[$form_state['build_info']['form_id']=>$ddasarray,]],'type'=>'setting'],
			],
		],
		'productdata'=>[
			'#type'=>'value',
			'#value'=>$dd,
		],
		'fromnid'=>[
			'#type'=>'value',
			'#value'=>$nid,
		],
		'actions'=>[
			'#type'=>'actions',
			'submit'=>[
				'#type'=>'submit',
				'#value'=>'Купить',
				'#ajax'=>[
					'callback'=>'formaddtocart_form_jscb',
					'progress'=>[],
				],
			],
		],
		'qty-wrap'=>[
			'#type'=>'container',
			'#attributes'=>[
				'class'=>['qty-wrapp','container-inline'],
			],
			'qty'=>[
				'#type'=>'textfield',
				'#default_value'=>$co,
				'#required'=>true,
				'#title_display'=>'invisible',
				'#size'=>5,
				'#title'=>'Количество',
				'#attributes'=>[
					'title'=>'Количество',
				],
			],
			'real-cost'=>[
				'#markup'=>'',
				'#prefix'=>'<div class="real-cost">',
				'#suffix'=>'</div>',
			],
		],
	];
	
	return $form;
}
/**
 * валидация формы добавления в корзину .. 
 */
function formaddtocart_form_validate(&$form,&$form_state){
	///dsm($form,'$formv');
	$val=$form['qty-wrap']['qty']['#value'];
	if (!is_numeric($val) || intval($val)<1)
		form_error($form['qty-wrap']['qty'],'Количество должно быть целым положительным числом');
}
/**
 * ajax обработчик формы .. 
 */
function formaddtocart_form_jscb($form,$form_state){
	$cmd=array();
	global $user;
	if (form_get_errors()){

		// вываливаем сообщение 
		$cmd[]=[
			'command'=>'show_in_popup',
			'content'=>theme('status_messages'),
		];
		// перебиваем форму
		$cmd[]=ajax_command_replace('.mk-form-add-cart-'.$form_state['fselector'],render($form));
		// тыкаем клиента носом в ошибку 
		$cmd[]=['command'=>'focustoerrorfield'];
	}
	else{
		// чистим сообщения ..
		drupal_get_messages('status');
		// надо обновить корзинку в шапке ... сайта .. 
		//$html=views_embed_view('commerce_cart_block', 'default');
		$cmd[]=ajax_command_replace ('.site-head .cart',theme('site_cart_head'));
		// показываем уведомлялку 
		if(!empty($form_state['li'])){
			$vals=$form_state['values'];
			//dsm($form_state['li'],'li');
			//$price=field_get_items('commerce_line_item',$form_state['li'],'commerce_unit_price');
			//$total=field_get_items('commerce_line_item',$form_state['li'],'commerce_total');
			//dsm($price);
			// цена из товара .. 
			//dsm($form_state['added'],'pro-added');
			$priceformproduct=field_get_items('commerce_product',$form_state['added'],'commerce_price');
			$unit=field_get_items('commerce_product',$form_state['added'],'field_unit_measure');
			$unit=taxonomy_term_load($unit[0]['tid']);
			$unit=field_get_items('taxonomy_term',$unit,'field_mini_unit_prod');
			//dsm($unit,'$unit');
			$unit=$unit[0]['value'];


			$sum=0;
			$nacenka='';
			//сумма заказа .. 
			if ($order = commerce_cart_order_load($user->uid)){
				$sum=field_get_items('commerce_order',$order,'commerce_order_total');
				$sum=$sum[0]['amount']/100;
				$fd=theme_get_setting('nacenka');
				if (!empty($fd['size']) && intval($fd['size'])>$sum && !empty($fd['text']))
					$nacenka=$fd['text'];
				
			}
			//$win=views_embed_view('confirm_message_product_display','default',$form_state['li-id']);
			//$win.='<a href="#" class="commerce-add-to-cart-confirmation-close"><span class="element-invisible">Закрыть</span></a><div class="clearfix"></div>';
			$nodaprod=node_view(node_load($form_state['values']['fromnid']),'inpopup');
			$nodaprod['cart-data']=[
				//'#qty'=>$form_state['li']->quantity,
				//'#price'=>number_format($price[0]['amount']/100,1,'.',' '),
				//'#total'=>$total[0]['amount'],
				'#added-now'=>$vals['qty'],
				'#price-from-product'=>number_format($priceformproduct[0]['amount']/100,1,'.',' '),
				'#summ-now'=>number_format($priceformproduct[0]['amount']/100*$vals['qty'],1,'.',' '),
				'#unit'=>$unit,
			];
			//dsm($nodaprod,'$nodaprod');
			$win=theme('product_in_popup',[
				'nodeview'=>$nodaprod,
				'nacenka'=>$nacenka,
			]);
				//'adasdd -- '.$form_state['added']->title;
			//$cmd[]=ajax_command_prepend('#main_content',$win);
			
			$cmd[]=[
				'command'=>'show_in_popup',
				'content'=>$win,
				'wrapCSS'=>'form-in-popup messages-commerce-add-to-cart-confirmation',
				'padding'=>10,
				'width'=>'auto',
				//'type'=>'html',
				//'scrolling'=>'no',
				'autoSize'=>false,
				'autoHeight'=>true,
				//'fitToView'=>false,

			];
		}	
	}
	return ['#type'=>'ajax','#commands'=>$cmd];
}
// ============================================================
/**
 * форма добавления товара в корзину ..  примененение действий.. 
 */
function formaddtocart_form_submit($form,&$form_state)
{
	form_state_values_clean($form_state);
	global $user;
	$vals=$form_state['values'];
	//dfb($vals,'$vals');
	$pd=$vals['productdata'];
	$pid=0;
	// ищем товар который надо добавить в корзину.. 
	foreach(element_children($pd) as $pk)
		if ( 
			(!empty($pd[$pk]['from']) && $vals['qty']>=intval($pd[$pk]['from']) || empty($pd[$pk]['from']) ) &&  
			(!empty($pd[$pk]['to']) && $vals['qty']<=intval($pd[$pk]['to']) || empty($pd[$pk]['to']) )
		)
			$pid=$pd[$pk]['product_id'];
	if (!$pid)
		return ;
	// грузим товар ..
	$pid=commerce_product_load($pid);
	// создаём запись в корзине ... 
	$li=commerce_product_line_item_new($pid,$vals['qty'],0,['fronnid'=>$vals['fromnid']]);
	drupal_alter('commerce_product_calculate_sell_price_line_item', $li);
	rules_invoke_event('commerce_product_calculate_sell_price', $li);

    // Only attempt an Add to Cart if the line item has a valid unit price.
	$line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $li);

	if (!is_null($line_item_wrapper->commerce_unit_price->value())) {
		// Add the product to the specified shopping cart.
		$li=commerce_cart_product_add(
			$user->uid,
			$li, 
			isset($li->data['context']['add_to_cart_combine']) ? $line_item->data['context']['add_to_cart_combine'] : TRUE
		);
		$form_state['li']=$li;
		$form_state['added']=$pid;
			//dfb($li,'li');
	}
		
}

// =============================================

/**
 * форма быстрого заказа 
 */
function mkm_quickzakaz_form($form,$form_state,$params=array()){
	$form=[
		'#attached'=>[
			'library'=>[
				['mklibs','inputmask'],
			]
		],

		'actions'=>[
			'#type'=>'actions',
			'submit'=>[
				'#type'=>'submit',
				'#value'=>'Отправить',
				'#ajax'=>[
					'callback'=>'mkm_quickzakaz_form_jscb',
				],
			],
		],
		'titl'=>[
			'#markup'=>'Быстрый заказ',
			'#prefix'=>'<div class="popup-titl">',
			'#suffix'=>'</div>',
		],
		'phone'=>[
			'#type'=>'textfield',
			'#required'=>true,
			'#title'=>'Телефон',
			'#title_display'=>'invisible',
			'#attributes'=>[
				'placeholder'=>'Телефон*',
				'data-inputmask'=>"'mask':'+7(999)999-99-99'",
			],
			'#size'=>30,
		],
		'name'=>[
			'#type'=>'textfield',
			'#title'=>'Ваше имя',
			'#title_display'=>'invisible',
			'#required'=>true,
			'#attributes'=>[
				'placeholder'=>'Ваше имя*',
				'data-inputmask'=>"'regex':'[a-zа-яA-ZА-Я]+[a-zа-яA-ZА-Я ]*'",
			],
			'#size'=>30,
		],
	];
	if (!empty($params['from-nid']))
		$form['from-nid']=[
			'#type'=>'value',
			'#value'=>$params['from-nid'],
			'#title'=>'Товар',
		];
	return $form;
}
/**
 * обработка отправки формы быстрого заказа  (ajax)
 */
function mkm_quickzakaz_form_jscb($form,$form_state){
	$cmd=[];
	$form['mess']=[
		'#theme'=>'status_messages',
		'#weight'=>-1,
	];
	if (!form_get_errors())
		$form=array($form['mess']);
	$cmd[]=ajax_command_replace('.'.$form_state['fselector'],render($form));
	$cmd[]=['command'=>'update_size_of_popup'];
	return ['#type'=>'ajax','#commands'=>$cmd];
}
/**
 * собственно обработка данных формы быстрого заказа 
 */
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

// ==================================================
// форма фильтра товара .. в разделах каталога
function pricefilter_form($form,$firm_state,$tid)
{
	list($min,$max)=getPriceRange($tid);
	$getmin=$min;
	$getmax=$max;
	$get=drupal_get_query_parameters();
	if (!empty($get['dprice']) && preg_match('#(\d+)-(\d+)#', $get['dprice'])){
		$arr=explode('-',$get['dprice']);
		$getmin=min($arr);
		$getmax=max($arr);
	}
		
	$form=[
		'tid'=>[
			'#type'=>'value',
			'#value'=>$tid,
		],
		
		'#attributes'=>['class'=>['form-of-filters']],
		'actions'=>[
			'#weight'=>10000,
			'#type'=>'actions',
			'submit'=>[
				'#name'=>'apply',
				'#type'=>'submit',
				'#value'=>'Применить фильтры',
			],
			'clear'=>[
				'#type'=>'submit',
				'#name'=>'clear',
				'#value'=>'Очистить фильтры',
			],
			'popup'=>[
				'#prefix'=>'<div class="popup-apply-button"><span class="close-btn">x</span>',
				'#suffix'=>'</div>',
				'#type'=>'submit',
				'#name'=>'apply',
				'#value'=>'Применить',
			],
		],
	];
	
	$form['prices']=[
		'#weight'=>0,
		'#access'=>isset($min)&& $min<$max ,
		'startrange'=>[
			'#type'=>'value',
			'#value'=>[
				'from'=>$min,
				'to'=>$max,
			],
		],
		'#weight'=>5,
		'#attached'=>[
			'library'=>[['mklibs','slider']],
			//'library'=>[['system','ui']],
			'js'=>[
				drupal_get_path('module','mkmod').'/slider-filter-form.js',
				['type'=>'setting','data'=>['sliderdata'=>['rangbig'=>[$min,$max],'rangsmal'=>[$getmin,$getmax]]]],
			],
		],
		'#type'=>'fieldset',
		'#title'=>'Цена',
		
		'#attributes'=>['class'=>['delta-price','form-item']],
		'ranger'=>['#type'=>'container','#attributes'=>['class'=>['ranger-placer']]],
		'range'=>[
			'#tree'=>true,
			'#type'=>'container',
			'#attributes'=>['class'=>['text-fields-wrap']],
			'from'=>['#type'=>'textfield','#title'=>'От','#title_display'=>'invisible','#attributes'=>['placeholder'=>'От'],'#default_value'=>$getmin,'#size'=>0],
			'defis'=>['#markup'=>'<span>-</span>'],
			'to'=>['#type'=>'textfield','#title'=>'До','#title_display'=>'invisible','#attributes'=>['placeholder'=>'До'],'#default_value'=>$getmax,'#size'=>0],	
		],
	];

	$filters=module_invoke('hitrolinks','getotherfilters',$tid);
	if ($filters)
		$form['#attached']['library']=[['mklibs','formstyler']];
	
	$i=0;
	foreach($filters as $k=>$el){
		$i++;
		$opt=[];
		$attrs=[];
		foreach($el['items'] as $x=>$y){
			$opt[$x]=$y['title'];
			if (preg_match('~^#[0-9a-f]+~is',$y['title'])){
				$form['#attached']['js'][]=drupal_get_path('module','mkmod').'/color-checkbox.js';
				$opt[$x]=sprintf('<span data-color="%s">%s</span>',$y['title'],$y['title']);
				$attrs['class']['cl']='colored-checkboxes';
			}
		}

		$form['fg'.$k]=[
			'#weight'=>10*$i,
			'#access'=>true,
			'#type'=>'checkboxes',
			'#attributes'=>$attrs,
			'#options'=>$opt,
			'#title'=>$el['title'],
		];
	}

	$fk=element_children($form);
	$els=0;
	for($i=0;$i<count($fk);$i++){
		if (in_array($fk[$i],['tid','actions']))
			continue;
		if (!empty($form[$fk[$i]]['#access']))
			$els++;
	}
	if (!$els)
		$form['#disabled']=true;

	
	// http://dev.masterkrowli.ru/bitumnaya-gidroizolyaciya
	return $form;
}


function pricefilter_form_submit($form,$form_state)
{
	form_state_values_clean($form_state);
	$vals=$form_state['values'];
	//dsm($vals);
	//dsm($form_state['triggering_element']);
	if ('clear'==$form_state['triggering_element']['#name']){
		drupal_goto(current_path());
		return ;
	}

	// устраиваем переход .. .
	$ids=[];
	foreach($vals as $x=>$y)
		if (preg_match('#fg\d+#',$x))
			foreach($y as $i=>$j)
				if ($j)
					$ids[]=$i;
	switch(count($ids)){
		case 0:
			break;
		case 1:
			$link=module_invoke('hitrolinks','getLinkById',reset($ids));
			if ($link)
				drupal_goto($link);
			return ;
		default:
			$tids=taxonomy_get_parents_all($vals['tid']);
			if ($tids){
				$tids=end($tids);
				drupal_goto('taxonomy/term/'.$tids->tid);
				return;
			}

	}

	$rang=$vals['range'];

	$range=$vals['startrange'];
	foreach(['from','to'] as $k)
		if (empty($rang[$k]) || !is_numeric($rang[$k]))
			$rang[$k]=$range[$k];

	$get=drupal_get_query_parameters();
	if ($rang['from']!=$range['from'] || $rang['to']!=$range['to'])
		$get['dprice']=implode('-',$rang);

	drupal_goto(current_path(),['query'=>$get]);
	
}