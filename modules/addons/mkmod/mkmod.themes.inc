<?php 
function topprodaglist_prefunc(&$vars){
	//dsm($vars['list']);
	$res=db_select('node','n');
	$res->condition('n.nid',$vars['list']);
	$res->fields('n',array('nid','title'));
	$res->leftJoin('field_data_field_pic_product','fi','fi.entity_id=n.nid and fi.bundle=n.type');
	$res->leftjoin('file_managed','fm','fm.fid=fi.field_pic_product_fid');
	$res->addField('fm','uri','uri');
	$res->leftjoin('field_data_field_product_variations','ep','ep.entity_id=n.nid and ep.bundle=n.type');
	$res->leftjoin('commerce_product','p','ep.field_product_variations_product_id=p.product_id and p.status=1');
	$res->leftjoin('field_data_commerce_price','cp','cp.entity_id=p.product_id');
	$res->addExpression('round(min(cp.commerce_price_amount)/100)','price');
	$res->leftjoin('field_data_field_unit_measure','ed','ed.entity_id=p.product_id');
	$res->leftjoin('taxonomy_term_data','td','td.tid=ed.field_unit_measure_tid');
	$res->addField('td','name','ed');
	$res->groupBy('n.nid');
	$res=$res->execute()->fetchAllAssoc('nid',PDO::FETCH_ASSOC);
	$list=array();
	foreach($vars['list'] as $x)
		if (!empty($res[$x])){
			$img=theme('image',array(
				'path'=>image_style_url('60x40',$res[$x]['uri']),
				'attributes'=>array(),
			));
			
			$list[$x]=array(
				
					'link'=>l($res[$x]['title'],'node/'.$res[$x]['nid']),
					'img'=>l($img,'node/'.$res[$x]['nid'],array(
						'html'=>true,
					)),
					'price'=>'от <span>'.$res[$x]['price'].' руб./'.$res[$x]['ed'].'</span>',
					
				
			);
		}
	//dsm($list,'$res');
	$vars['list']=$list;

	$vars['classes_array']=$vars['attributes_array']=$vars['title_attributes_array']=$vars['content_attributes_array']=array();
}
?>