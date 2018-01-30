<?php 
function mkmod_field_widget_info(){
	return array(
		'grad_background'=>array(
			'field types'=>array('grad_background'),
			'label'=>'Градиентная заливка',
			'description'=>'Градиентная заливка',
		)
	);
}
// =========================================
function mkmod_field_widget_form($form,$form_state,$field,$inst,$langcode,$items,$delta,$el){

	// edit-field-gradbg-und-0-gradtype
	switch($inst['widget']['type']){
		case 'grad_background':

			$el['gradcolors']=array(
				'#type'=>'textfield',
				'#title'=>'Набор цветов',
				'#description'=>'цвета в формате rrggbb через точку с запятой',
				'#default_value'=>empty($items[$delta]['gradcolors'])?'':$items[$delta]['gradcolors'],
			);
			$el['gradtype']=array(
				'#type'=>'select',
				'#title'=>'тип градиента',
				'#default_value'=>empty($items[$delta]['gradtype'])?'':$items[$delta]['gradtype'],
				'#empty_option'=>'Не выбрано',
				'#options'=>array(
					'r'=>'Радиальный',
					'l'=>'линеный',	
				),
			);
			$el['angle']=array(
				'#type'=>'textfield',
				'#title'=>'угол поворота',
				'#default_value'=>empty($items[$delta]['angle'])?0:$items[$delta]['angle'],
				'#field_suffix'=>'град.',
				'#size'=>6,
				'#states'=>array(
					'visible'=>array(
						'#edit-'.str_replace('_','-',$inst['field_name']).'-'.$langcode.'-'.$delta.'-gradtype'=>array(
							'value'=>'l',
						),
					),
				),
			);
			$el['addonstyles']=array(
				'#type'=>'textarea',
				'#title'=>'доп стили элемента',
				'#rows'=>3,
				'#default_value'=>empty($items[$delta]['addonstyles'])?'':$items[$delta]['addonstyles'],
			);

			break;
	}
	return $el;
}
?>