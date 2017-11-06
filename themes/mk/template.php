<?php 

	function mk_preprocess_page(&$variables) {
		if (!empty($variables['node'])) {
			$variables['theme_hook_suggestions'][] = 'page__node__' . $variables['node']->type;
		}

		if(arg(0) == 'taxonomy' && arg(1) == 'term') {
			$tid = (int)arg(2);
			$term = taxonomy_term_load($tid);
			if(is_object($term)) {
				$variables['theme_hook_suggestions'][] = 'page__taxonomy__'.$term->vocabulary_machine_name;
			}
		}
		if (preg_match('#node/(\d+)#',current_path(),$n)){
			// запрос sku 
			$res=db_select('node','n');
			$res->condition('n.nid',end($n));
			$res->leftjoin('field_data_field_product_variations','pr','pr.entity_id=n.nid and pr.bundle=n.type');
			$res->leftjoin('commerce_product','cp','cp.product_id=pr.field_product_variations_product_id');
			$res->fields('cp',array('sku'));
			$res->range(0,1);
			$res=$res->execute()->fetchField();
			if ($res)
				$variables['sku']=array(
					'#prefix'=>'<span class="prod-sku">Артикул: ',
					'#suffix'=>'</span>',
					'#markup'=>'<span class="val">'.$res.'</span>',
				);
		}
		//unset($variables['page']['content']['system_main']['nodes']);

		$menu_tree = menu_tree_all_data('main-menu');
		$variables['main_menu'] = menu_tree_output($menu_tree);
		$variables['searchform']=theme('searchform');
	}

	function mk_taxonomy_term_view($term, $view_mode, $langcode) {
		if ($term->vocabulary_machine_name == 'categories' && $view_mode == 'full') {
			$nids = taxonomy_select_nodes($term->tid);
			$nodes = node_load_multiple($nids);
			$term->content += node_view_multiple($nodes);
		}
	} 

	function mk_preprocess_image(&$variables){
		$variables['attributes'] = array(
				'class' => 'img-responsive',
		);
	}
	function mk_css_alter(&$css) {
			/*unset($css[drupal_get_path('module','system').'/system.theme.css']);
			unset($css[drupal_get_path('module','system').'/system.base.css']);
			unset($css[drupal_get_path('module','system').'/system.menus.css']);
			unset($css[drupal_get_path('module','system').'/system.messages.css']);
			unset($css[drupal_get_path('module','user').'/user.css']);
			unset($css[drupal_get_path('module','search').'/search.css']);
			unset($css[drupal_get_path('module','node').'/node.css']);
			unset($css[drupal_get_path('module','field').'/theme/field.css']);
			unset($css[drupal_get_path('sites','').'sites/all/modules/views/css/views.css']);*/
			$css['sites/all/themes/mk/custom.css']['preprocess']=false;
			//dsm($css);
	}
	// ----------------
	function mk_js_alter(&$js){
		$js['misc/jquery.js']['data']='http://code.jquery.com/jquery-1.8.3.min.js';
	}

	function mk_html_head_alter(&$head_elements) {
		unset($head_elements['system_meta_generator']);
		foreach ($head_elements as $key => $element) {
			if (isset($element['#attributes']['rel']) && $element['#attributes']['rel'] == 'shortlink') {
				unset($head_elements[$key]);
			}
		}
	};
	function mk_preprocess_comment(&$c){
		if (!empty($c['content']['field_rating'])){
			$r=field_get_items('comment',$c['comment'],'field_rating');
			$c['content']['field_rating'][0]=array(
				'#markup'=>sprintf('<span class="rating-out rating-widget-view"><span class="rating-in" data-rating="%d" style="width:%d%%"></span></span>',$r[0]['value'],$r[0]['value']),
			);
		}
	}	
	// ======================================
	function mk_preprocess_node(&$n){
		if ($n['type']=='delivery_truck' && $n['view_mode']=='teaser')
			hide($n['content']['links']);
		if ($n['type']=='product_display'){
			$marker=field_get_items('node',$n['node'],'field_marks_products');
			$n['marker']=0;
			if (!empty($marker[0]['tid']))
				$n['marker']=$marker[0]['tid'];	
		}
		if ($n['type']=='product_display' && $n['view_mode']=='full'){
			drupal_add_library('system','ui.tabs');
		if ($n['type']=='product_display')
			drupal_add_library('system','ui.tabs');

			// малюем рейтинг 
			// получаем данные .. 
			$res=db_select('comment','c');
			$res->condition('c.status',1);
			$res->condition('c.nid',$n['nid']);
			$res->leftjoin('field_data_field_rating','r','r.entity_id=c.cid');
			$res->addExpression('avg(r.field_rating_value)');
			$res=$res->execute()->fetchField();
			$r=number_format($res,2,'.','');
			$attr=array(
				'class'=>array("rating-in"),
				'data-rating'=>$r,
				'style'=>"width:$r%",
			);
			$n['content']['rating']=array(
				'#prefix'=>'<div>',
				'#suffix'=>'</div>',
				'#markup'=>sprintf('<span class="rating-out rating-widget-view" title="%s%%"><span %s ></span></span>',$r,drupal_attributes($attr)),
			);
			//dsm($n,'$n');
		}
		
	}
/*function mk_child_terms($vid = 1) {
	if(arg(0) == 'taxonomy' && arg(1) == 'term') {    
		$children = taxonomy_get_children(arg(2), $vid);
			if(!$children) {
				$custom_parent = taxonomy_get_parents(arg(2));
					$parent_tree = array();
					foreach ($custom_parent as $custom_child => $key) {
						$parent_tree = taxonomy_get_tree($vid, $key->tid);
					}
					$children = $parent_tree;
			}
	 
		$output = '<ul>';
		foreach ($children as $term) {
			$output .= '<li>';
			$output .= l($term->name, taxonomy_term_path($term));
			$output .= '</li>';
		}
		$output .= '</ul>';
		
		return $output;
	}
} 

*/
// ===========================================================
function mk_form_comment_node_product_display_form_alter(&$form,&$form_state){
	global $user;
	if (empty($form_state['fkey']))
		$form_state['fkey']=user_password();
	$form['#attributes']['class'][]='form-selector-'.$form_state['fkey'];

	$form['author']['#weight']=10;
	// field_trating
	$form['field_trating'][LANGUAGE_NONE][0]['rating']['#widget']=array('name'=>'basic','css'=>'basic');
	//dsm($form['field_trating'][LANGUAGE_NONE][0]['rating'],'rating');
	
	array_unshift($form['actions'],array(
		'#markup'=>'Перед публикацией на наш сайт, каждый отзыв или комментарий проходит премодерацию.',
		'#prefix'=>'<span class="descr">',
		'#suffix'=>'</span>',
	));
	$form['actions']['submit']['#value']='Оставить отзыв';
	if ($user->uid)
		foreach($form['author'] as $x=>$y)
			if (!empty($y['#type']) && $y['#type']=='item')
				$form['author'][$x]['#access']=false;
}


// ============================================================
function mk_breadcrumb($b){
	$p=current_path();
	$b=$b['breadcrumb'];
	$ps=array(
		'articles'=>'Статьи',
		'news'=>'Новости',
		'discounts'=>'Акции',
	);
	if (preg_match('#^node/(\d+)$#', $p,$n)){
		$res=db_select('node','n');
		$res->condition('n.nid',$n[1]);
		$res->fields('n',array('title','type'));
		$res->leftJoin('field_data_field_product_category','c','c.entity_id=n.nid and c.bundle=n.type and c.entity_type=\'node\'');
		$res->addExpression('group_concat(c.field_product_category_tid)','tid');
		$n=$res->execute()->fetch(PDO::FETCH_ASSOC);
		switch($n['type']){
			case 'article':
				$b[]=l('Статьи','articles');
			break;
			case 'new':
				$b[]=l('Новости','news');
			break;
		}
		if (!empty($n['tid'])){
			$tids=array();
			$maxtid=array();
			foreach(explode(',',$n['tid']) as $t){
				$t=taxonomy_get_parents_all($t);
				if (count($t)>count($tids))
					$tids=$t;
			}

			foreach(array_reverse($tids) as $y)
				$b[]=l($y->name,'taxonomy/term/'.$y->tid);
		}

		$b[]=$n['title'];
	}
	if (preg_match('#^taxonomy/term/(\d+)$#',$p,$n)){
		$n=array_reverse(taxonomy_get_parents_all($n[1]));
		
		
		$b=array(l(t('Home'),'<front>'));
		//dsm($n,'$n1');
		//$t=array_pop($n);
		//dsm($n,'$n2');
		
		
		//array_shift($n);
		foreach($n as $x=>$y)
			if ($x==1)
				$b[]=$y->name;
			else
				$b[]=l($y->name,'taxonomy/term/'.$y->tid);
		//$b[]=$t->name;
		//dsm($n);
	}

	
	foreach($ps as $x=>$y)
		if ($p==$x)
			$b[]=$y;
	
	//http://mk.alex-net.pp.ua/articles
	if ($b)
		return '<div class="breadcrumb col-lg-36">'.implode(' - ',$b).'</div>';
	return '';
	//return 'sad › ';
}
// ==========================================================
// 
function mk_form_alter(&$form,$form_state,$form_id){
	if (preg_match('#mkmodformaddtocart_(?:\d+_)+form#i',$form_id) && preg_match('#^node/(\d+)$#i',current_path(),$nid) && !empty($form_state['fromnid']) && $form_state['fromnid']==end($nid)){
		//dsm($nid);
		$form['#attributes']['class'][]='buy-form';
			$form['actions']['argblock']=array(
				'#type'=>'container',
				'#attributes'=>array(
					'class'=>array('argblock-wrapp'),
				),
				'fastzakaz'=>array(
					'#markup'=>'<span class="quick-zakaz" data-openform-quick-zakaz>Быстрый заказ</span>',
					'#weight'=>109,
				),
				'submit'=>$form['actions']['submit'],
			);
			unset($form['actions']['submit']);
			
			$form['actions']['opt']=array(
				'#markup'=>'<div class="back-tovar" data-show-node-in-popup="1549">Возврат товара</div>
							<div class="change-tovar" data-show-node-in-popup="1550">Обмен товара</div>',
				'#prefix'=>'<div class="opetions-pluss back-change-tovars">',
				'#suffix'=>'</div>',
				'#weight'=>115,
			);
		//dsm(,'fs');
	}
	//dsm($form_id,'$form_id');
}
// ===========================================================
function mk_form_views_form_all_variations_product_block_alter(&$form,$form_state){
	if (!empty($form['add_to_cart_quantity'][0]['#product_id']) && preg_match('#node/(\d+)#',current_path(),$n)) {
		//  искать ноду для этого товара
		$n=end($n);
		$form['#action']=url(current_path());
		//dsm($form);

		$res=db_select('commerce_product','c');
		$res->condition('c.product_id',$form['add_to_cart_quantity'][0]['#product_id']);
		$res->leftJoin('field_data_field_product_variations','n','n.field_product_variations_product_id=c.product_id');
		$res->condition('n.entity_id',$n);
		$res->addExpression('count(*)');
		$res=$res->execute()->fetchField();
		if ($res){
		
		}
	}
	//dsm();
	
	
	//uasort($form['actions'], 'element_sort');
	//dsm($form['actions']);
}
/// ============================================
function mk_menu_link($m){
	//kprint_r($m);
	$m['element']['#attributes']['class'][]='mi-'.$m['element']['#original_link']['mlid'];
	return theme_menu_link($m);
}
// ======================================
function mk_theme(){
	return array(
		'searchform'=>array(
			'template'=>'searchform',
			'render element'=>'form',
		),
	);
}
// ====================================================
function mk_preprocess_views_view(&$vars){
	if ($vars['name']=='confirm_message_product_display')
		foreach(array('header','footer','rows') as $k)
			$vars[$k]=token_replace($vars[$k]);
}
//=========================================================
function mk_preprocess_username(&$vars){
	$vars['extra']='';
	//dsm($vars);
}
