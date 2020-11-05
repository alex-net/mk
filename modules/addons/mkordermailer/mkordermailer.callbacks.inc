<?php 


function mail_test_commerce_cb($oid)
{
	$order=commerce_order_load($oid);
	
	commerce_checkout_complete($order);
	echo token_replace( theme('mkordermailer_mail_to__customer',['orderId'=>$oid,'forManager'=>true]),['commerce_order'=>$order]);
	return ;
	
	dsm($order);
	$o=entity_metadata_wrapper('commerce_order',$order);
	$items=[];
	foreach($o->commerce_line_items as $it){
		$pod=entity_metadata_wrapper('commerce_product',$it->line_item_label->value());

		dsm($pod->getPropertyInfo());
		
		$node=entity_metadata_wrapper('node',$it->value()->data['fromnid']);
		dsm($node->getPropertyInfo());


		dsm([
			$pod->field_prod_amount_from->value(),
			$pod->field_prod_amount_to->value(),
		]);

		// 
		$price=$pod->commerce_price->value();
		$priceT=$it->commerce_total->value();
		$items[]=[
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
	//dsm($items);
	//dsm(count());
	//echo 'dsa!';
	//echo theme('mkordermailer_mail_to__customer');
	//echo '!da';
	//7404 7776  7795
	//print_r(module_implements('commerce_checkout_complete'));
	//commerce_cart_commerce_checkout_complete
	//commerce_checkout_complete($order);
	
	// /tmp/sublime-sftp-browse-1594934464/MK/var/www/fastuser/data/www/dev.masterkrowli.ru/sites/all/modules/rules/includes/faces.inc: 126
	// rules_config = > rules_send_to_customer  rules_send_to_manager 
	// http://dev.masterkrowli.ru/mail-test/7776
	// http://dev.masterkrowli.ru/adminer.php
	//kprint_r($order);
	//echo token_replace( theme('mkordermailer_mail_to__customer',['orderId'=>$oid]),['commerce_order'=>$order]);
	//return [];
}