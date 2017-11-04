<?php 
function mkmod_block_info(){
	return array(
		'hit-prodag'=>array(
			'info'=>'Хит продаж',
		),
	);
}
// ====================================
function mkmod_block_view($delta=''){
	$b=array();
	if ($delta=='hit-prodag'){
		$nids=_gethitprodag(4);
		if ($nids){
			$b['content']=theme('topprodaglist',array(
				'list'=>$nids,
			));
			//$b['content']=views_embed_view('bestsellers','block_1',implode(',',$nids));
		}
	}
	return $b;
}
?>