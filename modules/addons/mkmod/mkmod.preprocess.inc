<?php 
/**
 * препроцесс ноды 
 * @param  [type] &$n [description]
 * @return [type]     [description]
 */
function mkmod_preprocess_node(&$n)
{
	// выставить  заначение переменной page в true чтобы не отображалась ссылка на страницу ...
	if (!empty($n['elements']['#setpagetotrue']))
		$n['page']=true;
	// распологаемся на странице ноды .. 
	if (preg_match('#^node/(\d+)$#',current_path(),$nod) && $nod[1]==$n['nid']){
		// записываем в настройки номер текущей ноды ..
		drupal_add_js(array('current-noda'=>$n['nid']),'setting');
		// пробуем добавить метатег в шапку .. 
		if ($n['type']=='product_display'){
			$isprod=&drupal_static('is-product-for-meta-head');
			$isprod=true;
		}
	}
	
	
	if (!empty($n['content']))
		// замена токенов 
		$n['content']=nodetokens_replacer($n['content']);
	
}

/**
 * препроцесс стрпницы ..
 * @param  [type] &$p [description]
 * @return [type]     [description]
 */
function mkmod_preprocess_page(&$p)
{
	// число элементов ... текущая страница  ...  всего страниц ..
	global $pager_total_items,$pager_page_array,$pager_total;
	$pp=variable_get('default_nodes_main',10);
	// замена токенов в массиве страницы ..
	$p=nodetokens_replacer($p);

	//dsm($p);
	// далее идёт автоподгрузка товаров .. 
	// не показывать на последней странице ..
	if (preg_match('#^taxonomy/term/(\d+)$#',current_path(),$tid) &&  $pager_total[0]>0 && $pager_total[0]-1!=$pager_page_array[0] ) {
		array_shift($tid);

		$tid=empty($tid)?'search':reset($tid);
		

			//dsm([$_SERVER['REQUEST_URI'],],'serv');
		//dsm($p['page']['content']['system_main']['pager']);
		//dsm(pager_find_page());
		//$p['page']['content']['system_main']['pager']['#access']=false;
		$p['page']['content']['system_main']['nodes']['#type']='container';
		$p['page']['content']['system_main']['nodes']['load-more']=[
			'#type'=>'container',
			'#attributes'=>['class'=>['load-more-contents']],
			'button'=>[
				'#type'=>'button',
				'#value'=>'Показать ещё ↓',
			],
			//'#markup'=>'<input type="button" value="Загрузить ещё" />',
			'#weight'=>1000,
		];
		
		$pparams=drupal_get_query_parameters();
		
		//$p['page']['content']['system_main']['nodes']['#attached']['js'][]=drupal_get_path('module','mkmod').'/pager-uploader.js';
		$p['page']['content']['system_main']['nodes']['#attached']['library'][]=['mklibs','contentuploader',];
		$p['page']['content']['system_main']['nodes']['#attached']['js'][]=[
			'type'=>'setting',
			'data'=>[
				'pageruploader'=>[
					'loadfrom'=>url('get-next-content-elements'),
					'data'=>[
						'curpage'=>$pparams['page']??0,
						'curtid'=>$tid,
						'total'=>$pager_total_items[0],
						'perpage'=>variable_get('default_nodes_main',10),
					],
				]
			],
		];
	}
}

// ========================================================
// передаём в обёртку коментов число коментов на страницу
function mkmod_preprocess_comment_wrapper(&$vars){
	$fd=variable_get('mkmodadmin_form',array());
	if(!empty($fd['otsivs-count']))
		$vars['cc']=$fd['otsivs-count'];
}

// ===================================================
function mkmod_preprocess_link(&$vars){

	// нужно подгрузить аякс команды .. 
	if (!empty($vars['options']['attributes']['data-show-node-in-popup']) && stripos(current_path(), 'admin')!==0){
		drupal_add_library('mkmod','myajaxcommands');
		$vars['options']['attributes']['class'][]='node-popup';
	}
		
}