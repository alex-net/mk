<?php 
/**
 * определяем временной интервал до конца акции .. 
 * @param  object $n объект ноды 
 * @return int    интервал до конца акции от текущего времени . в секундах
 */
function _checkdiscont($n)
{
	$date_discount = 0;
	if ($n->type!='product_display')
		return false;
	// список номеров товаров.. 
	$products=field_get_items('node',$n,'field_product_variations');
	//kprint_r($products,'n');
	// грузим товары по номерам .. 
	foreach($products as $x=>$y)
		$products[$x]=$y['product_id'];
	$products=commerce_product_load_multiple($products);
		
	// $node->field_product_variations
	foreach ($products as $p) {
		$dates=field_get_items('commerce_product',$p,'field_discount_from_date');
		$oldprice=field_get_items('commerce_product',$p,'field_old_price');
		if ($dates)
			$dates=array(
				'from'=>strtotime($dates[0]['value']),
				'to'=>strtotime($dates[0]['value2'].' +1 day'),
			);	
		// определяем наибольшую дату 
		if ($dates && $oldprice && $dates['from']<REQUEST_TIME && $dates['to']>REQUEST_TIME && $date_discount<$dates['to'])
			$date_discount=$dates['to'];
	}

	return $date_discount;
}