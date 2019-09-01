<?php 
$stat=statistics_get($nid);
hide($content['links']);
?>
<div class="<?=$classes;?>">
	<?=render($content['field_article_pic']);?>
	<div class="title"><a href="<?=$node_url;?>"><?=$title;?></a></div>
	<div class="wrap">
		<div class="views"><?=intval($stat['totalcount']);?></div>
		<a class="more" href='<?=$node_url;?>'>Подробнее</a>
	</div>
	<?=render($content);?>
	
</div>