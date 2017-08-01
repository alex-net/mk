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
		//unset($variables['page']['content']['system_main']['nodes']);

		$menu_tree = menu_tree_all_data('main-menu');
		$variables['main_menu'] = menu_tree_output($menu_tree);
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
			unset($css[drupal_get_path('module','system').'/system.theme.css']);
			unset($css[drupal_get_path('module','system').'/system.base.css']);
			unset($css[drupal_get_path('module','system').'/system.menus.css']);
			unset($css[drupal_get_path('module','system').'/system.messages.css']);
			unset($css[drupal_get_path('module','user').'/user.css']);
			unset($css[drupal_get_path('module','search').'/search.css']);
			unset($css[drupal_get_path('module','node').'/node.css']);
			unset($css[drupal_get_path('module','field').'/theme/field.css']);
			unset($css[drupal_get_path('sites','').'sites/all/modules/views/css/views.css']);
			$css['sites/all/themes/mk/custom.css']['preprocess']=false;
			//dsm($css);
	}

	function mk_html_head_alter(&$head_elements) {
		unset($head_elements['system_meta_generator']);
		foreach ($head_elements as $key => $element) {
			if (isset($element['#attributes']['rel']) && $element['#attributes']['rel'] == 'shortlink') {
				unset($head_elements[$key]);
			}
		}
	};

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

// ============================================================
//function mk_breadcrumb($b){
//	return 'sad › ';
//}