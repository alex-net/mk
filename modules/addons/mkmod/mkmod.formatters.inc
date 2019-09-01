<?php 

function mkmod_field_formatter_info(){
	return array(
		'productslistbuy'=>array(
			'label'=>'Список цен + форма',
			'description'=>'Описаное товаров с возможностью покупки',
			'field types'=>array('commerce_product_reference'),
			'settings'=>['viewotherbuttons'=>true],
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
		// список цен + форма.. 
		case 'productslistbuy':
			// номера товаров для вывода ценников .. 
			$pids=[];
			foreach($items as $y)
				$pids[]=$y['product_id'];

			if (!$pids)// если не прикручено ни одного товара ..= показывать нечего ..
				break;
				
			$res=getDataForProductList($pids);
			$res['#settings']=$display['settings'];
			//dsm($s);
			$el[]=array(
				'price-list'=>['#theme'=>'price_list','#pids'=>$pids],
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

/**
 * форма настроек форматтеров 
 */
function mkmod_field_formatter_settings_form($field,$int,$viewmode,$form,$form_state)
{
	//dsm($int,$viewmode);
	$els=[];
	switch($int['display'][$viewmode]['type']){
		case 'productslistbuy':

			$els['viewotherbuttons']=[
				'#type'=>'checkbox',
				'#title'=>'Отображать дополнительные кнопки в форме товара',
				'#default_value'=>!empty($int['display'][$viewmode]['settings']['viewotherbuttons']),
			];
		break;
	}
	return $els;
}