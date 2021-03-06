<?php 
function mkmod_token_info()
{
	return array(
		'types'=>array(
			'block'=>array(
				'name'=>'Токены для блоков',
				'description'=>'Группа токенов блока',
			),
			'mk'=>array(
				'name'=>'Токены MK',
				'description'=>'',
			),
		),
		'tokens'=>array(
			'node'=>array(
				'view-content'=>array(
					'name'=>'Контент ноды',
					'description'=>'Вернуть контент ноды',
				),
				'view-in-popup'=>array(
					'name'=>'Всплыть',
					'description'=>'Всплыть контентом ноды (full)',
				),
			),
			'commerce-order'=>array(
				'form-field'=>array(
					'name'=>'Поле из формы',
					'description'=>'',
				),
			),
			'mk'=>array(
				'show-comments'=>array(
					'name'=>'Коменты ноды',
					'description'=>'',
				),
				'socnets'=>array(
					'name'=>'Соцсети',
					'description'=>'Логотипы соц сетей',
				),
				'nacenka'=>array(
					'name'=>'Показать наценку',
					'description'=>'показать наценку если сумма заказа больше 10000',
				),
				'map-sclad'=>array(
					'name'=>'Карта складов',
					'description'=>'Карта складов',
				),
				'curdate'=>array(
					'name'=>'текущая дата с форматированием',
					'description'=>'формат даты как у функции date()',
				),
				'rekv'=>array(
					'name'=>'Поле реквизитов',
					'description'=>'Поле реквизитов',
				),
				'mashinki'=>[
					'name'=>'Машинки',
					'description'=>'Список доступного транспорта для доставки',
				],
			),
			'block'=>array(
				'view-content'=>array(
					'name'=>'Контент блока',
					'description'=>'Вернуть контент блока'
				),
			),
			'submission'=>array(
				'valueshtml'=>array(
					'name'=>'Html исполнение',
					'description'=>'',
				),
			),
		),
	);
}
//======================================================================
function mkmod_tokens($type,$tokens,$data=array(),$opt=array()){
	$rep=array();
	global $user;
	foreach($tokens as $t=>$o)
		switch($type){
			case 'submission':
				if(preg_match('#^valshtml:?(.*)#', $t,$json)){

					$json=end($json);
					
					if ($json)
						$json=drupal_json_decode($json);
					$json=$json?$json:array();
					

					$comps=$data['node']->webform['components'];
					$vals=$data['webform-submission']->data;
					$rows=array();
					$tdatrs=array();
					if (!empty($json['td1style']))
						$tdatrs['style']=$json['td1style'];
					foreach($comps as $c)
						if (isset($vals[$c['cid']])){

							$rows[]=array(
								array('data'=>$c['name'])+$tdatrs,
								empty($vals[$c['cid']][0])?'-':$vals[$c['cid']][0]);
						}
					//dsm(array('data'=>$data,'opt'=>$opt),'token');
					$tblparam=array(
						'rows'=>$rows,
						'sticky'=>false,
						'header'=>array(array('data'=>'Поле')+$tdatrs,'Значение'),
					);
					if (!empty($json['tblstyle']))
						$tblparam['attributes']['style']=$json['tblstyle'];
					$rep[$o]=theme('table',$tblparam);
				}
			break;
			case 'node':
				if (preg_match('#view-content:(\d+):(\w+)#',$t,$tn)){
					$n=node_load($tn[1]);
					if ($n){
						$n=node_view($n,$tn[2]);
						// выставить  заначение переменной page в true чтобы не отображалась ссылка на страницу ...
						if ($tn[2]=='full')
							$n['#setpagetotrue']=true;
						$n=nodetokens_replacer($n);
						$rep[$o]=render($n);
					}
				}
				// настраиваем всплывашку.. для ноды .  // классы через запятую, заголоовк контанта 
				if (preg_match('#view-in-popup:(\d+):(\S*):(.*)?#us',$t,$tn)){
					drupal_add_library('mkmod','myajaxcommands');
					$attrs=array(
						'class'=>array('node-popup','popup-for-'.$tn[1]),
						'data-show-node-in-popup'=>$tn[1],
					);
					if (!empty($tn[2]))
						$attrs['class']=array_merge($attrs['class'],explode(',',$tn[2]));
					$rep[$o]=sprintf('<span %s>%s</span>',drupal_attributes($attrs),$tn[3]);
				}
			break;
			case 'block':
				if(preg_match('#view-content:(\S+?):(\S+)#',$t,$tn)){
					$b=module_invoke($tn[1],'block_view',$tn[2]);
					if (is_string($b['content']))
						$b['content']=array(
							'content'=>array(
								'#markup'=>$b['content'],
							),
						);
					$b=(object)array(
						'content'=>$b['content'],
						'subject'=>$b['subject'],
						'module'=>$tn[1],
						'delta'=>$tn[2],
						'region'=>'undefined',
					);
					$b=_block_get_renderable_array(array($tn[1].'_'.$tn[2]=>$b));
					$rep[$o]=render($b);
				}
			break;
			case 'commerce-order':
			
				if (preg_match('#^form-field:(.*)#',$t,$tn)){
					$ord=commerce_order_load($data['commerce-order']->order_id);
					$prof=field_get_items('commerce_order',$ord,'field_form_ordering');
					$rep[$o]='';
					if (
						!empty($prof[0]['profile_id']) && 
						($prof=entity_load('commerce_customer_profile', array($prof[0]['profile_id']))) &&
						($prof=field_get_items('commerce_customer_profile',reset($prof),end($tn))) &&
						!empty($prof[0]['value'])
					){
						
						$rep[$o]=$prof[0]['value'];
						
					}

					//
					
					
				
				}
			break;	
			case 'mk':
				if (preg_match('#show-comments\:(\d+)\:(\d+)#',$t,$tn)){
					global $pager_page_array;
					$out=array(
						'addnewcomment'=>array(
							'#prefix'=>'<div class="new-onsiv" data-openform-new-otziv="">',
							'#suffix'=>'</div>',
							'#markup'=>'Написать отзыв',
						),
						'comment-wrap'=>array(
							'#type'=>'container',
							'#attributes'=>array(
								'class'=>array('comments-wrap'),
							),
						),
					);
					$nid=$tn[1];
					// проверяем что стоит в коментах 
					$res=db_select('node','n');
					$res->condition('n.nid',$nid);
					$res->fields('n',array('comment'));
					$res=$res->execute()->fetchField();
					$out['addnewcomment']['#access']=$res==2;
					$pp=$tn[2];
					$out['comment-wrap']=array_merge($out['comment-wrap'],_getcomentcontent(array(
						'nid'=>$nid,
						'pp'=>$pp,
					)));
					$out['#attached']['js'][]=array(
						'type'=>'file',
						'data'=>drupal_get_path('module','mkmod').'/mkmod-commends-control.js',
					);
					$out['#attached']['js'][]=array(
						'type'=>'setting',
						'data'=>array(
							'mkcc'=>array(
								'nid'=>$nid,
								'pp'=>$pp,
								'cps'=>array(0),
							),
						),
					);
					$out['#attached']['library'][]=array('mkmod','myajaxcommands');
					$rep[$o]=render($out);
				}
				if (preg_match('#^socnets:(.*)#', $t,$tn)){
					$imgpath="/sites/default/files/socnet/";
					$tn=explode('|',html_entity_decode($tn[1]));
					$r=array();

					// <a href="https://vk.com/megakrovlia" target="_blank"><img src="/sites/default/files/socnet/vk.png" style="height: 44px; width: 44px;" /></a>
					foreach($tn as $v){
						$v=explode('=>', $v);
						$im=file_create_url('public://socnet/'.$v[0].'.png');
						$r[]=l('',$v[1],array(
							'attributes'=>array(
								'target'=>'_blank',
								'style'=>'background:url('.$im.') no-repeat;background-size:cover;',
							)
						));
					}
					$rep[$o]=implode('',$r);
					
				}
				if ($t=='nacenka'){
					$nacenka=theme_get_setting('nacenka');
					$rep[$o]='';
					if (!empty($nacenka['text']) && !empty($nacenka['size']) && is_numeric($nacenka['size'])){
						$cart=commerce_cart_order_load($user->uid);
						//$total=field_get_items('commerce_cart_order',$cart,'commerce_order_total');
						$tot=empty($cart)?0:floatval($cart->commerce_order_total[LANGUAGE_NONE][0]['amount']/100);
						
						//dsm($tot,'$tot');
						if (floatval($nacenka['size'])>$tot)
							$rep[$o]='<div class="nacenka-action-popup warn-block">'.$nacenka['text'].'</div>';
					}
				}
				// карта складов ..
				if ('map-sclad'==$t){
					$SkladList=getSkladList();
					$rep[$o]='';
					if ($SkladList){
						drupal_add_js(array(
							'sklads'=>$SkladList,
						),'setting');
						drupal_add_js('https://api-maps.yandex.ru/2.1/?lang=ru_RU','external');
						drupal_add_js(drupal_get_path('module','mkmod').'/map-sklad.js','file');
						// 55.755814, 37.617635
						$rep[$o]='<div class="map-sklad"></div>';	
					}

					

				}
				// отображение текущей даты ...
				if (preg_match('#^curdate\:(.*)#i',$t,$dat)) 
					$rep[$o]=format_date(REQUEST_TIME,'custom',end($dat));

				// замена реквизитов 
				if (preg_match('#rekv:(.*)#',$t,$t0)){
					$fd=variable_get('site-trkvs',array());
					$t0=explode(':',$t0[1]);
					if ( empty($t0[0]) || empty($fd['rekv'][$t0[0]]) ){
						$rep[$o]='';
						break;
					}
					$res=$fd['rekv'][$t0[0]];
					list($res,$befhtml)=array_pad(explode('::',$res),2,'');
					
					
					
					if (in_array('colored',$t0)){
						if (preg_match('#mail#i',$t0[0])){
							$res=explode('@',$res);
							$res[0]='<span class="colored">'.$res[0].'</span>';
							$res=implode('@',$res);
						}
					}
					if (preg_match('#phone#i',$t0[0])){
						$res=explode('-',$res);
						

						if (in_array('text',$t0)){
							$ar=array();
							$ar[]=array_shift($res);
							$ar[]=array_shift($res);
							$ar[1]='('.$ar[1].')';
							$ar[0]='8';
							$ar=implode(' ',$ar);
							if (in_array('colored',$t0))
								$ar='<span class="colored">'.$ar.'</span>';
							$res=$ar.' '.implode('-', $res);
						}
						else
							$res=implode('',$res);	


					}
					if (in_array('plain',$t0))
						$rep[$o]=strip_tags($res);	
					else
						$rep[$o]='<span class="rekv-token">'.$befhtml.$res.'</span>';

				}
				// показываем машинки .. 
				if ($t=='mashinki'){
					$res=db_select('node','n');
					$res->condition('n.type','delivery_truck');
					$res->condition('n.status',1);
					$res->fields('n',['nid']);
					$res=$res->execute();
					$res=$res->fetchCol();
					$rep[$o]='';

					if ($res){
						$res=node_view_multiple(node_load_multiple($res));
						$res['#prefix']='<div class="tachki-wrapper">';
						$res['#suffix']='</div>';
						$rep[$o]=render($res);
					}
				}


				
			break;


	}

	
		
	return $rep;
}
?>