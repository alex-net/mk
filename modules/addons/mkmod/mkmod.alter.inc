<?php 

function mkmod_html_head_alter(&$els)
{
	//if (preg_match('#node/(\d+)#',current_path())
	//kprint_r('a');
	$isprod=&drupal_static('is-product-for-meta-head');
	// параметры запроса .. 
	$params=drupal_get_query_parameters();
	
	if (isset($isprod) && !isset($params['_escaped_fragment_'])){
		$els['metatag_canonical']['#access']=false;
		$els['isajaxfragment']=[
			'#type'=>'html_tag',
			'#tag'=>'meta',
			'#attributes'=>['name'=>'fragment','content'=>'!'],
		];
		//kprint_r($els);
	}
}