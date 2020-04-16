<?php 

// достать нужное количество хитов прожаж
/**
 * вернуть nidы хитов продаж...
 * @param  int    $count Количество возвращаемых элементов 
 * @return array        
 */
function getTopSalesNids(int $count){
	$cid=__FUNCTION__.$count;
	$result=&drupal_static($cid);

	if ($result)
		return $result;

	$data=cache_get($cid);
	if (!empty($data->data) && $data->expire>=REQUEST_TIME){
		$result=$data->data;
		return $data->data;
	}
	
	// найти купленные и оплаченные статусы 
	$st=module_invoke('commerce_order','statuses');
	foreach($st as $x=>$y)
		if ($y['cart'])
			unset($st[$x]);
	unset($st['canceled']);


	$res=db_select('node','n');
	$res->condition('n.status',1);
	$res->condition('n.type','product_display');
	// исключаем метки (Всякие новинки и т.п.)
	$res->leftjoin('field_data_field_marks_products','mark','mark.entity_id=n.nid and mark.bundle=n.type');
	$res->isNull('mark.field_marks_products_tid');
	// надо исключить акции  (так чтобы сегодняшняя дата попала между датами старта и стопа акции ))
	$res->leftjoin('field_data_field_product_variations','pe','pe.entity_id=n.nid and pe.bundle=n.type');
	$res->leftjoin('commerce_product,','p','p.product_id=pe.field_product_variations_product_id and p.status=1');
	//$res->leftjoin('field_data_field_discount_from_date','adate','adate.entity_id=p.product_id and adate.bundle=\'product\'');
	//$res->where(' not now() between adate.field_discount_from_date_value and adate.field_discount_from_date_value2 ');
	// надо взять все товары которые купили .. .
	$res->leftjoin('field_data_commerce_product','cp','cp.commerce_product_product_id=p.product_id');
	$res->leftjoin('commerce_line_item','li','li.line_item_id=cp.entity_id');
	
	
	
	if ($st){
		// примотать таблицу ордеров ..
		$res->leftjoin('commerce_order','o','o.order_id=li.order_id');
		$res->condition('o.status',array_keys($st));// куленый и оплаченный 
	}

	$res->fields('n',array('nid'));
	
	$res->orderBy('o.created','desc');
	$res->range(0,$count);
	$res->groupBy('n.nid');
	$res=$res->execute()->fetchCol();
	// запхали в static 
	$result=$res;
	// запхали в кеш .. на сутки 
	cache_set($cid,$res,'cache',REQUEST_TIME+3600*24);
	return $res; 
}



// =========================================================
/**
 * собрать акции 
 * @param int $mitcounteronly Отобразить акции только со счётчиком 
 * @param int $tid Текущий каталог
 * @param int $nid Текущая нода ..
 */
function getActionProdag($mitcounteronly=0,$tid=0,$nid=0){
	// пробуем читать из кеша 
	$data=cache_get(__FUNCTION__.'_'.$mitcounteronly.'tid'.$tid);
	if (!empty($data->data) && $data->expire>REQUEST_TIME && 0)
		return $data->data;

	$tids=[];
	if ($tid)
		$tids[]=$tid;

	$res=db_select('node','n');
	if ($nid)
		$res->condition('n.nid',$nid,'!=');
	$res->condition('n.status',1);
	$res->condition('n.type','product_display');
	// винтим товар //  и проверяем чтобы он был акционным
	$res->leftjoin('field_data_field_product_variations','pe','pe.entity_id=n.nid and pe.bundle=n.type');
	$res->leftjoin('commerce_product,','p','p.product_id=pe.field_product_variations_product_id and p.status=1');
	if ($mitcounteronly){
		$res->leftjoin('field_data_field_discount_from_date','adate','adate.entity_id=p.product_id and adate.bundle=\'product\'');
		$res->where(' now() between adate.field_discount_from_date_value and (adate.field_discount_from_date_value2 +  interval 1 day)');
		// выкатываем интервал акции (с по)
		$res->addfield('adate','field_discount_from_date_value','afrom');
		$res->addfield('adate','field_discount_from_date_value2','ato');
	}
	// проверяем чтобы была старая цена
	$res->leftjoin('field_data_field_old_price','oldp','oldp.entity_id=p.product_id and oldp.bundle=\'product\'');
	$res->condition('oldp.field_old_price_amount',0,'>');
	// собираем поля 
	$res->fields('n',array('nid','title'));

	$ff=array(
		array('field_pic_product','fid',''),
		//array('field_title_top','value','titletop'),
		//array('field_title_bot','value','titlebottom'),
		
	);
	foreach($ff as $i=>$v){
		$res->leftjoin('field_data_'.$v[0],"t$i","t$i.entity_id=n.nid and t$i.bundle=n.type and t$i.entity_type='node'");
		if ($v[2])
			$res->addField("t$i",$v[0].'_'.$v[1],$v[2]);
	}
	// добавляем ссыль на картинку товара 
	$res->leftjoin('file_managed','fm','fm.fid=t0.field_pic_product_fid');
	$res->fields('fm',array('uri'));
	
	// дергаем старую цену 
	$res->addField('oldp','field_old_price_amount','oldp');
	// дёргаем новую цену 
	$res->leftjoin('field_data_commerce_price','cp','cp.entity_id=p.product_id and cp.bundle=\'product\'');
	$res->addField('cp','commerce_price_amount','cp');
	$res->where('cp.commerce_price_amount<oldp.field_old_price_amount');

	// дёрнуть размерность 
	$res->leftjoin('field_data_field_unit_measure','m','m.entity_id=p.product_id and m.bundle=\'product\'');
	$res->leftjoin('taxonomy_term_data','td','td.tid=m.field_unit_measure_tid');
	$res->addField('td','name','measure');
	// дёрнуть разделы .. .категория .. 
	if ($tids){
		$res->leftjoin('field_data_field_product_category','cat','cat.entity_id=n.nid and cat.bundle=n.type');
		$res->condition('cat.field_product_category_tid',$tids);
	}
	$res->groupBy('n.nid');
	/// достать содержимое ... 
	$res->leftjoin('field_data_field_text','ft','ft.entity_id=n.nid and ft.bundle=n.type');
	$res->addField('ft','field_text_value','body');
	$res->range(0,100);
	$res->orderBy('rand()','asc');
	$res=$res->execute()->fetchAllAssoc('nid',PDO::FETCH_ASSOC);
	//dsm($res,'$res');
	cache_set(__FUNCTION__,$res,'cache',REQUEST_TIME+3600*24);
	return $res;
}



/**
 * замена токенов .. 
 * @param  array|string $el элемент  в котором нужно заменить токены
 * @return [type]      [description]
 */
function nodetokens_replacer($el)
{
	// щамена в строке .. 
	if (is_string($el))
		return  mkmod_tokensshashreplacer($el);
	
	// замена токенов в  местах наличия вёрстки .. 
	foreach(['#markup','#prefix','#suffix'] as $k)
		if (is_array($el) && !empty($el[$k]))
			$el[$k]=mkmod_tokensshashreplacer($el[$k]);

	// замена в массиве рендеринга ..  
	if (is_array($el))
		foreach(element_children($el) as $k)
			$el[$k]=nodetokens_replacer($el[$k]);
	return $el;
}

/**
 * полная замена токенов в массиве контента  Может использоваться как Хук ..
 * @param  array $el массив рендеринга 
 */
function mkmod_tokensshashreplacer($el){
	do{
		$a=md5($el);
		//dsm(array($el),$a);
		$el=token_replace($el);
	}while($a!=md5($el));
	//dsm(array($a,md5($el),$el));
	return $el;
}


/**
 * Достаём элементы каталога ...
 * @param int $ptid номер родительского термина (0 - достать корневые термины)
 */
function getOneLevelOfCatalog(int $ptid=0)
{
	// пробуем вытащить из кеша .. 
	$cat=&drupal_static('catalog-list-cb-data-'.$ptid,[]);
	if ($cat)
		return $cat;

	// достаём номера  дочерних терминов упорядоченные по весу и доступные к просмотру (vis=1)
	$res=db_select('taxonomy_term_data','td');
	$res->leftJoin('taxonomy_term_hierarchy','th','th.tid=td.tid');
	$res->condition('th.parent',$ptid);
	$res->condition('td.vid',2);
	$res->condition('td.vis',1);
	// подсчитываем количество потомков .. 
	$res->leftJoin('taxonomy_term_hierarchy','th2','th2.parent=td.tid');
	$res->leftJoin('taxonomy_term_data','td2','td2.tid=th2.tid and td2.vis=1');

	//$res->addExpression('count(td2.tid)','childs');
	$res->addExpression('group_concat(td2.tid)','childtids');
	$res->groupBy('td.tid');

	$res->fields('td',['tid']);
	$res->orderBy('td.weight','asc');
	$res=$res->execute();
	$res=$res->fetchAllAssoc('tid',PDO::FETCH_ASSOC);
	//$res=$res->fetchCol();
	$tids=$res;


	if ($res){
		// собираем все дочерние термины для загрузки ...
		$childstids=[];
		foreach($tids as $x=>$v){
			$tids[$x]['childtids']=empty($v['childtids'])?[]:explode(',',$v['childtids']);
			$childstids=array_merge($childstids,$tids[$x]['childtids']);
		}
		$childstids=array_unique($childstids);
		if ($childstids){
			$t=db_select('taxonomy_term_data','t');
			$t->condition('t.tid',$childstids);
			$t->fields('t',['tid','name']);
			$t->orderBy('t.weight','asc');
			$t=$t->execute();
			$childstids=$t->fetchAllAssoc('tid',PDO::FETCH_ASSOC);
			//dfb($t,'t');
			//dfb($t);

		}
		//dfb($childstids,'$childstids');

		// загружаем сущности  .
		$res=entity_load('taxonomy_term',array_keys($res));
		// проставляем количество потомков .. 
		foreach($res as $t=>$v){
			$ch=[];
			foreach($tids[$t]['childtids'] as $x)
				$ch[]=[
					'name'=>$childstids[$x]['name'],
					'url'=>url('taxonomy/term/'.$x),
				];
			$res[$t]->childs=count($ch);
			$res[$t]->childslist=$ch;

			//$res[$t]->childs=$ch;//$tids[$t]['childs'];
		}
	}
	$cat=$res;
	
	if (!$cat)
		return false;

	return $cat;
} 



/**
 * запрос диапазонов цен для списка товаров = формирование ценников + инфа для формы добавления  в корзину 
 * @param array $pids список номеров товаров 
 * @return  array данные по диапазонам цен 
 */
function getDataForProductList($pids)
{
	$dat=&drupal_static(__FUNCTION__.'--'.implode('-',$pids));
	if ($dat)
		return $dat;
	
	// достаём данные. по товарам 
	$res=db_select('commerce_product','p');
	$res->condition('p.product_id',$pids);
	$res->fields('p',array('product_id'));

	$res->condition('p.status',1);
	// подключение таблиц 
	foreach([
		'commerce_price'=>'amount',
		'field_old_price'=>'amount',
		'field_prod_amount_from'=>'value',
		'field_prod_amount_to'=>'value',
		'field_unit_measure'=>'tid',
	] as $tbl=>$field){
		$res->leftjoin('field_data_'.$tbl,$tbl,$tbl.'.entity_id=p.product_id');
		if ($tbl!='field_unit_measure')
			$res->addField($tbl,$tbl.'_'.$field,$tbl);
		else{
			$res->leftjoin('taxonomy_term_data','td','field_unit_measure.field_unit_measure_tid=td.tid');
			$res->leftjoin('field_data_field_mini_unit_prod','u','u.entity_id=td.tid');
			$res->addField('u','field_mini_unit_prod_value','unit');
		}
	}
	$res=$res->execute()->fetchAll(PDO::FETCH_ASSOC);

	foreach($res as $x=>$y){
		foreach($y as $k=>$v){
			if (!$v){
				unset($res[$x][$k]);
				continue;
			}
			if (strpos($k,'price')!==false)
				$res[$x][$k]/=100;
			if (strpos($k,'amount')!==false){
				unset($res[$x][$k]);
				$k=str_replace('field_prod_amount_','',$k);
				$res[$x][$k]=$v;
			}
			if ($k=='unit')
				$res[$x][$k]=drupal_strtolower($res[$x][$k]);
			//unset($res[$x]['product_id']);
		}
	}

	$dat=$res;
	return $res;
}


/**
 * получить товары для раздела каталога с применением фильтров ..
 * @param int $tid номер раздела .. 
 * @param int $forpage номер страницы с которой надо выдрать товары ..(0 = отправляем с пагинатором ...это начальная загрузка ..  ) 
 */
function getProductsListForTaxonomy($tid,$forpage=0,$sortby='rating')
{
	$pp=variable_get('default_nodes_main',10);
	$res=db_select('node','n');
	if (!$forpage){
		$res=$res->extend('PagerDefault');
		$res->limit($pp);
	}
	else
		$res->range($forpage*$pp,$pp);
	$res->condition('n.type','product_display');
	$res->condition('n.status',1);
	$res->leftJoin('taxonomy_index','ti','ti.nid=n.nid');
	$res->condition('ti.tid',$tid);
	//$res->addExpression('count(*)','c');
	$res->fields('n',['nid']);
	$res->groupBy('n.nid');

	// привинчиваем веса нод .. если у нас сортировка по рейтингу .. 
	if ($sortby=='rating'){
		$res->leftjoin('nodeweight','nw','nw.nid=n.nid and nw.tid='.intval($tid));
		$res->orderBy('nw.weight','asc');
	}
	

	// привигтить ценники товаров ... по ним будет как сортировка так и фильтрация ... 
	$res->leftjoin('field_data_field_product_variations','ppref','ppref.entity_id=n.nid and ppref.bundle=n.type ');
	$res->leftJoin('commerce_product','cp','cp.product_id=ppref.field_product_variations_product_id and cp.status=1');
	$res->leftjoin('field_data_commerce_price','cpp',"cpp.entity_id=cp.product_id and cpp.entity_type='commerce_product' and cpp.bundle='product'");
	// фильтр по ценнику .. 
	$params=drupal_get_query_parameters();
	if (!empty($params['dprice']) && preg_match('#^\d+-\d+$#',$params['dprice'])){
		$dp=explode('-',$params['dprice']);
		
		$res->having('min(cpp.commerce_price_amount) between :pfrom and :pto',[':pfrom'=>min($dp)*100,':pto'=>max($dp)*100]);
	}

	
	//$res->groupBy('cp.product_id');
	if (preg_match('#^price(up|down)$#',$sortby,$direct)){
		$direct=end($direct);
		$sortar=['up'=>'asc','down'=>'desc'];
		$res->orderBy('min(cpp.commerce_price_amount)',$sortar[$direct]);
		//dsm($sortby);
	}

	$res->orderBy('n.created','desc');
	
	return $res->execute()->fetchCol();
}


/**
 * запрос максимальной и минимальной цены по категории ... 
 */
function getPriceRange($tid)
{
	$range=&drupal_static(__FUNCTION__);
	if ($range)
		return $range;

	$res=db_select('node','n');
	$res->condition('n.type','product_display');
	$res->condition('n.status',1);
	$res->leftJoin('taxonomy_index','ti','ti.nid=n.nid');
	$res->condition('ti.tid',$tid);
	//$res->addExpression('count(*)','c');
	//$res->fields('n',['nid']);
	$res->groupBy('n.nid');

	// привигтить ценники товаров ... по ним будет как сортировка так и фильтрация ... 
	$res->leftjoin('field_data_field_product_variations','ppref','ppref.entity_id=n.nid and ppref.bundle=n.type ');
	$res->leftJoin('commerce_product','cp','cp.product_id=ppref.field_product_variations_product_id and cp.status=1');
	$res->leftjoin('field_data_commerce_price','cpp',"cpp.entity_id=cp.product_id and cpp.entity_type='commerce_product' and cpp.bundle='product'");
	$res->addExpression('min(cpp.commerce_price_amount)','price');

	$res=$res->execute()->fetchCol();
	$range=$res?[min($res)/100,max($res)/100]:[null,null];

	return $range;
}


/**
 * список товаров по акциям ... 
 * @return [type] [description]
 */
function getMarkupsOfAkciiProducts($tid,$nid=0)
{
	// блок акций ...
	$prodyctsAtAkcia=getActionProdag(0,$tid,$nid);
	if (!$prodyctsAtAkcia)
		return [];
	$prodyctsAtAkcia=array_chunk(array_keys($prodyctsAtAkcia), 36);
	$prodyctsAtAkcia=reset($prodyctsAtAkcia);
	//dsm($prodyctsAtAkcia,'$prodyctsAtAkcia '.$tid);

	foreach($prodyctsAtAkcia as $x=>$y)
		if (!$y)
			unset($prodyctsAtAkcia[$x]);
	
	//dsm($prodyctsAtAkcia);
	if (!$prodyctsAtAkcia)
		return [];

	return carouselMarkupGen($prodyctsAtAkcia,'product-akcions-list','Товары по акции');

	
	//$prodyctsAtAkcia=node_view_multiple(node_load_multiple($prodyctsAtAkcia));
		
		
		//$prodyctsAtAkcia=;
}

/**
 * Карусель  внутри категории ...  генерация обёртки вокруг 
 */
function carouselMarkupGen($nids,$key,$title){
	// бахнули товар в котором находимся ..
	if (preg_match('#^node/(\d+)$#i',current_path(),$cnid) &&  in_array(end($cnid), $nids)) 
		unset($nids[array_search(end($cnid), $nids)]);

	//dsm($nids,current_path());
	return [	
		'#type'=>'container',
		'#attached'=>[
			'library'=>[['mklibs','slick']],
			'js'=>[
				[
					'type'=>'setting',
					'data'=>[
						$key=>[
							'to'=>'.'.$key.'.elements-list.products',
							'nids'=>$nids,
						],
					],
				],
			],
		],
		'header'=>[
			'#markup'=>'<h2>'.$title.'</h2>',
		],
		'#attributes'=>['class'=>[$key.'-wrapper']],
		'list'=>[
			'#type'=>'container',
			'#attributes'=>[
				'class'=>[$key,'elements-list','products','ajax-loadable'],
				'data-key'=>$key,
			],
		],	
	
	];
}

/**
 * собрать nid товаров которые прикреплены к разделу 
 * @param int|array $tid Номер раздела ... для отображения .. .
 */
function GetProductsByTerm($tid)
{

	$res=db_select('node','n');
	$res->fields('n',['nid']);
	$res->condition('n.status',1);
	$res->condition('n.type','product_display');
	$res->leftJoin('field_data_field_product_category','cat','cat.entity_id=n.nid and cat.bundle=n.type');
	$res->condition('cat.field_product_category_tid',$tid);
	
	return $res->execute()->fetchCol();
}