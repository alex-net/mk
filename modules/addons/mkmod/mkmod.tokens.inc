<?php 
function mkmod_token_info(){
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
			),
			'block'=>array(
				'view-content'=>array(
					'name'=>'Контент блока',
					'description'=>'Вернуть контент блока'
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
			case 'node':
				if (preg_match('#view-content:(\d+):(\w+)#',$t,$tn)){
					$n=node_load($tn[1]);
					if ($n){
						$n=node_view($n,$tn[2]);
						
						if ($tn[2]=='full'){
							$n['#setpagetotrue']=true;
						}
						node_tokens_replacer($n);
						$rep[$o]=render($n);
					}
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
					$cart=commerce_cart_order_load($user->uid);
					//$total=field_get_items('commerce_cart_order',$cart,'commerce_order_total');
					//dsm($cart,'cart');
					$tot=floatval($cart->commerce_order_total[LANGUAGE_NONE][0]['amount']/100);

					//dsm($tot,'$tot');
					$rep[$o]=$tot>10000?'':'<div class="nacenka-action-popup warn-block">На розничные заказы до 10 000 рублей применяется дополнительная наценка 20% к цене, указанной на сайте!!!</div>';
				}
				if ('map-sclad'==$t){
					$fd=variable_get('sklad-config',array());// список складов 
					$skladlist=empty($fd['skladlist'])?array():$fd['skladlist'];
					foreach($skladlist as $x=>$y){
						$graf=explode("\n",$y['regim']);
						//dsm($y);
						$skladlist[$x]['content']=theme('skladmapballoon',array(
							'title'=>$y['name'],
							'subname'=>$y['subname'],// текст под заголовкам
							'timepn'=>$graf[0],// время работы понедельник пятница
							'vihi'=>$graf[1],// выходные 
							'descr'=>$y['descr'], // доп инфа
						));
					}
					
					drupal_add_js('https://api-maps.yandex.ru/2.1/?lang=ru_RU','external');
					drupal_add_js(drupal_get_path('module','mkmod').'/map-sklad.js','file');
					// 55.755814, 37.617635
					$rep[$o]='<div class="map-sklad"></div>';
					drupal_add_js(array(
						'sklads'=>$skladlist,
					),'setting');
				}
			break;
	}

	
		
	return $rep;
}
?>