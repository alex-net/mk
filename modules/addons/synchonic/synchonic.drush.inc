<?php 
function synchonic_drush_command(){
	return array(
		'priceimport'=>array(
			'arguments'=>array(
				'act'=>'операция',
			),
		),
	);
}
// =============================
function drush_synchonic_priceimport(){
	$a=drush_get_arguments();
	if (empty($a[1])){
		drush_log('Нужен аргумент','error');
		return false;
	}
	switch($a[1]){
		case 'price':
			$res=db_select('node','n');
			$res->condition('n.type','product_display');
			$res->condition('n.status',1);
			$res->fields('n',array('nid'));
			$prodnids=$res->execute()->fetchCol();
			foreach($prodnids as $v){
				$prids=_getprodids($v);
				if ($prids)
					_updatefields($prids,'field_data_commerce_price',array('commerce_price_amount'));
			}
			cache_clear_all('*','cache_field',true);
			drush_log('Выполнено','success');
		break;	
		case 'terms':
			$res=db_select('taxonomy_term_data','t',array('target'=>'prod'));
			$res->condition('t.vid',2);
			$res->fields('t',array('tid','description'));
			$terms=$res->execute()->fetchAllKeyed();
			foreach($terms as $x=>$y){
				//обновляем описание термина .. 
				$res=db_update('taxonomy_term_data');
				$res->condition('tid',$x);
				$res->fields(array('description'=>$y));
				$res->execute();
				// обновляемполя .. 
			}
			_updatefields(array_keys($terms),'field_data_field_text_between_cat_prods',array('field_text_between_cat_prods_value','field_text_between_cat_prods_format'));
			_updatefields(array_keys($terms),'field_data_field_text_under_products',array('field_text_under_products_value','field_text_under_products_format'));
			///drush_print_r($terms);
			cache_clear_all('*','cache_field',true);
			drush_log('Выполнено','success');
		break;
	}
	
}
?>