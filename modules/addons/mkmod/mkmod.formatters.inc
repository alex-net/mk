<?php 

function mkmod_field_formatter_info(){
	return array(
		'productslistbuy'=>array(
			'label'=>'Список цен',
			'description'=>'Описаное товаров с возможностью покупки',
			'field types'=>array('commerce_product_reference'),
		),
		'grad_background'=>array(
			'label'=>'Гардиентная заливка',
			'description'=>'гарадиентная заливка',
			'field types'=>array('grad_background'),
		),
		'image_backgound'=>array(
			'label'=>'Фоновая картинка',
			'description'=>'Каринка в качесве фона',
			'field types'=>array('image'),
		),
	);
}
// ===============================================
function mkmod_field_formatter_view($enttype,$ent,$field,$instance,$language,$items,$display){
	$el=array();
	$sett=$display['settings'];
	
	switch($display['type']){
		case 'productslistbuy':
			//dsm(array($field,$ent,$instance,$items,$display,$language));
			$pids=array();
			foreach($items as $y)
				$pids[]=$y['product_id'];


			// достаём данные. по товарам 
			$res=db_select('commerce_product','p');
			$res->condition('p.product_id',$pids);
			$res->fields('p',array('product_id'));

			$res->condition('p.status',1);
			foreach(array(
				'commerce_price'=>'amount',
				'field_old_price'=>'amount',
				'field_prod_amount_from'=>'value',
				'field_prod_amount_to'=>'value',
				'field_unit_measure'=>'tid',
			) as $tbl=>$field){
				$res->leftjoin('field_data_'.$tbl,$tbl,$tbl.'.entity_id=p.product_id');
				if ($tbl!='field_unit_measure')
					$res->addField($tbl,$tbl.'_'.$field,$tbl);
				else{
					$res->leftjoin('taxonomy_term_data','td','field_unit_measure.field_unit_measure_tid=td.tid');
					$res->leftjoin('field_data_field_mini_unit_prod','u','u.entity_id=td.tid');
					$res->addField('u','field_mini_unit_prod_value','unit');
				}

			}
			$res=$res->execute()->fetchAll(PDO::FETCH_ASSOC);
			foreach($res as $x=>$y){
				foreach($y as $k=>$v){
					if (!$v){
						unset($res[$x][$k]);
						continue;
					}
					if (strpos($k,'price')!==false)
						$res[$x][$k]/=100;
					if (strpos($k,'amount')!==false){
						unset($res[$x][$k]);
						$k=str_replace('field_prod_amount_','',$k);
						$res[$x][$k]=$v;
					}
					if ($k=='unit')
						$res[$x][$k]=drupal_strtolower($res[$x][$k]);
					//unset($res[$x]['product_id']);
					if (count($res)==1)
						unset($res[$x]['from'],$res[$x]['to']);
				}
			}

			//dsm($res);
			$rows=array(
				'#type'=>'container',
				'#attributes'=>array(
					'class'=>array('price-list'),
				),
			);
			
			foreach($res as $v){
				$s=array();
				$s[]='<span class="price-tail">';
				if (!empty($v['field_old_price']))
					$s[]='<span class="old">'.$v['field_old_price'].'</span>';
				if (!empty($v['commerce_price']))
					$s[]='<span class="cost">'.number_format($v['commerce_price'],1,'.','').'</span>';
				$s[]=' руб';
				if (!empty($v['unit']))
					$s[]='/'.$v['unit'];
				$s[]='</span>';

				if (!empty($v['from']) || !empty($v['to']))
					$s[]='<span class="range-count">';
				if (!empty($v['from']))
					$s[]='от '.$v['from'];	
				if (!empty($v['to']))
					$s[]=' до '.$v['to'];
				if (!empty($v['from']) || !empty($v['to'])){
					$s[]=' '.$v['unit'].'</span>';
					
				}

				$rows[]=array(
					'#prefix'=>'<div class="price-range-item clearfix">',
					'#suffix'=>'</div>',
					'#markup'=>implode('',$s),
				);
			}
			//dsm($s);
			$el[]=array(
				'price-list'=>$rows,
				'form'=>drupal_get_form('mkmodformaddtocart_'.implode('_',$pids).'_form',$res,$ent->nid),
			);
		break;

		case 'grad_background':
		
			foreach($items as $delta=>$item){
				$gt=array('l'=>'linear','r'=>'radial',);
				$grads=array();
				$colors=implode(',',array_map('trim',explode(';',$item['gradcolors'])));
				$deg=$item['gradtype']=='r'?'':$item['angle'].'deg,';
				foreach(array('','ms-','o-','webkit-','moz-') as $b)
					$grads[]='background-image:'.$b.$gt[$item['gradtype']].'-gradient('.$deg.$colors.');';
				if (!empty($item['addonstyles'])){
					$style=array();
					foreach(explode('\n',$item['addonstyles']) as $s)
						$style[]='.node-'.$ent->nid.'.node-teaser .field-name-'.trim($s);
					drupal_add_css(implode('',$style),array('type'=>'inline'));
					
				}

				
				$attrs=array(
					'class'=>array('grad-bg'),
					'style'=>$grads,
				);
				$el[$delta]=array(
					'#markup'=>sprintf('<span %s ></span>',drupal_attributes($attrs)),
				);
			}
		break;
		//фоноваое изображение 
		case 'image_backgound':
			foreach($items as $delta=>$item){
				$img=file_create_url($item['uri']);
				//dsm($item);
				$imgs=array(
					sprintf('background-image:url(%s);',$img),

				);
				$attrs=array(
						'class'=>array('image-bg'),
						'style'=>$imgs,
					);
					$el[$delta]=array(
						'#markup'=>sprintf('<span %s ></span>',drupal_attributes($attrs)),
					);
					//dsm('s');
			}
		break;
	}
	return $el;
}
?>
