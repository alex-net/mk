<?php 
function mksearch_theme(){
	return array(
		'searchresultinfo'=>array(
			'variables'=>array('rc'=>0),
		),
	);
}
// ==================================
function theme_searchresultinfo($vars){
	return sprintf('<span class="product-finder">Найдено %d товаров:</span>',$vars['rc']);
}
?>