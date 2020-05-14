<?php 
include 'incl/funcs.php';
include 'incl/form-alter.php';
include 'incl/preprocess.php';
include 'incl/themes.php';


function mk2_js_alter(&$js)
{
	$js['misc/jquery.js']['data']=drupal_get_path('theme','mk2').'/node_modules/jquery/dist/jquery.min.js';
	unset($js['misc/form.js']);
	//'//code.jquery.com/jquery-3.4.1.min.js';
	//kprint_r($js);
}


function mk2_theme_registry_alter(&$r)
{
	//dsm($r['page']);
}


function mk2_html_head_alter(&$hels)
{
	$params=drupal_get_query_parameters();
	if (isset($hels['metatag_canonical']) && !$params &&  'taxonomy/term/93'==current_path())
		unset($hels['metatag_canonical']);
	/*if ( &&  !empty($params))
		$hels['dis']=[
			// <meta name="robots" content="noindex">
			'#type'=>'html_tag',
			'#tag'=>'meta',
			'#attributes'=>[
				'name'=>"robots",
				'content'=>"noindex",
			],
		];*/
}