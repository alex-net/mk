<?php
/**
 * Тут находятся вспомогательные функции для сайта
 */

/**
 * Проверка поля на существования и наличия данныех ноды
 * Возврот массива с данными поля
 * @return array
 */
function addmi_get_field_items($entity, $field_name, $entity_type = 'node'){
  if(is_numeric($entity)){
    switch($entity_type){
      case "taxonomy_term":
        $entity = taxonomy_term_load($entity);
        break;
      case "user":
        $entity = user_load($entity);
        break;
      case "comment":
        $entity = comment_load($entity);
        break;
//      case "commerce_product":
//        $entity = commerce_product_load($entity);
//        break;
//      case "commerce_order":
//        $entity = commerce_order_load($entity);
//        break;
//      case "commerce_line_item":
//        $entity = commerce_line_item_load($entity);
//        break;
      default:
        $entity = node_load($entity);
        break;
    }
  }
  if(is_object($entity)){
    $field_items = field_get_items($entity_type, $entity, $field_name);
    if (!empty($field_items) && $field_items_filter = _field_filter_items(field_info_field($field_name), $field_items)) {
      return $field_items_filter;
    }
  }
  return FALSE;
}


/**
 * ПОлучаем entity текущей страници
 */
function addmi_get_entity_page($type = NULL){
  $entity = FALSE;
  if(arg(0) == 'node' && is_numeric(arg(1))){
    $tmp = node_load(arg(1));
    if(is_null($type)){
      $entity = $tmp;
    }
    else {
      if($tmp->type === $type){
        $entity = $tmp;
      }
    }
  }
  elseif(arg(0) == 'taxonomy' && is_numeric(arg(2))){
    $tmp = taxonomy_term_load(arg(2));
    if(is_null($type)){
      $entity = $tmp;
    }
    else {
      if($tmp->vocabulary_machine_name === $type){
        $entity = $tmp;
      }
    }
  }
  return $entity;
}

/**
 * Проверка поля на существования и наличия данныех ноды
 * Возврот значение певого елемента в списке значений поля
 * @return value
 */
function addmi_get_field_item_first($entity, $field_name, $num = 0, $entity_type = 'node'){
  $tmp = FALSE;
  $field_items = addmi_get_field_items($entity, $field_name, $entity_type = 'node');
  if(isset($field_items[$num])){
    foreach($field_items[$num] as $item){
      $tmp = $item;
      break;
    }
  }
  return $tmp;
}


/**
 * Выводим html блока
 */
function addmi_render_block($module_name, $block_delta){
  $block = block_load($module_name, $block_delta);
  $block = _block_render_blocks(array($block));
  $block_build = _block_get_renderable_array($block);
  return render($block_build);
}


/**
 * @param $number
 * @param $word - слово без окончания (к примеру "Отзыв")
 * @param $endings - массив с окончаниями (к примеру array('','a','ов'))
 * @param $space - пробел между числом с словом
 * @return mixed - число и полное слово с окончанием
 */
function NumberEnd($number, $word, $endings, $space = ' ') {
  $cases = array (2, 0, 1, 1, 1, 2);
  $ending = $endings[ ($number%100>4 && $number%100<20)? 2 : $cases[min($number%10, 5)] ];
  return $word+$space+$ending;
}
