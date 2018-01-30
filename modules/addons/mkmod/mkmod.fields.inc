<?php 
function mkmod_field_info(){
	return array(
		'grad_background'=>array(
			'label'=>'Градиентная заливка',
			'description'=>'Прямоугодьник (div) который заливается градиентом',
			'default_widget'=>'grad_background',
			'default_formatter'=>'grad_background',
			'settings'=>array(),
		),
	);
}
function mkmod_field_is_empty($item,$field){
	switch($field['type']){
		case 'grad_background':
			return empty($item['gradcolors']) || empty($item['gradtype']);
	}
	return true;
}
?>