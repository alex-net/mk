<?php 

function mkordermailer_mail_to_customer_prefunc(&$vars)
{
	$origin=explode('--',str_replace('_', '-', $vars['theme_hook_original']));
	
	$vars['theme_hook_suggestions'][]=implode('--',$origin);
	//$vars['theme_hook_suggestions'][]=$origin[0];
	//kprint_r($vars);

	$vars['items']=[];
	if (!empty($vars['orderId'])){
		$o=entity_metadata_wrapper('commerce_order',$vars['orderId']);
		
		foreach($o->commerce_line_items as $it){
			$pod=entity_metadata_wrapper('commerce_product',$it->line_item_label->value());
			$node=entity_metadata_wrapper('node',$it->value()->data['fromnid']);
			// 
			$price=$pod->commerce_price->value();
			$priceT=$it->commerce_total->value();
			$vars['items'][]=[
				'price'=>commerce_currency_format($price['amount'],$price['currency_code']),
				'quantity'=>$it->quantity->value(),
				'ptotal'=>commerce_currency_format($priceT['amount'],$priceT['currency_code']),
				'size'=>$pod->field_unit_measure->name->value(),
				'title'=>$node->title->value(),
				'link'=>url('node/'.$node->nid->value(),['absolute'=>true]),
				'img'=>image_style_url('thumbnail', $node->field_pic_product->value()['uri']),
				//$it->line_item_label->value(),
			];
		}
	}

	$vars['classes_array']=$vars['attributes_array']=$vars['title_attributes_array']=$vars['content_attributes_array']=[];
}