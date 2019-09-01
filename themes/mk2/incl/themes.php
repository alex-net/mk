<?php

function mk2_theme()
{
	return [
		// темизаци кнопок в полном просмотре товара 
		'fullproductbuttons'=>[
			'render element'=>'form',
			'template'=>'fullproductbuttons',
		],
		'footercontent'=>[
			'template'=>'footercontent',
			'variables'=>[],
			'postrender functions'=>[
				'footer_postrender_cb',
			],
		],
	];
}

/**
 * пострендер .. для подвала 
 */
function footer_postrender_cb($vars){
	kprint_r($vars);
}

function mk2_breadcrumb($vars)
{
	$p=current_path();
	$b=$vars['breadcrumb'];
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
		$n=array_values(array_reverse(taxonomy_get_parents_all($n[1])));
		$b=[l(t('Home'),'<front>')];
		foreach($n as $x=>$y)
			if ($x!=count($n)-1)
				$b[]=l($y->name,'taxonomy/term/'.$y->tid);
			else
				$b[]='<span class="current">'.$y->name.'</span>';
	}
	switch(current_path()){
		case 'cart':
			$b[]='<span class="current">Корзина</span>';
		break;
	}
	
	
	foreach($ps as $x=>$y)
		if ($p==$x)
			$b[]=$y;
	
	//http://mk.alex-net.pp.ua/articles
	if ($b)
		return '<div class="breadcrumb">'.implode(' &rsaquo; ',$b).'</div>';
	return '';
}

/**
 * стилизация пагинатора
 */
function mk2_pager($vars)
{
	//kprint_r($vars);
	$vars['tags'][0]='первая';
	$vars['tags'][1]='предыдущая';
	$vars['tags'][3]='следующая';
	$vars['tags'][4]='последняя';
	return theme_pager($vars);
}
