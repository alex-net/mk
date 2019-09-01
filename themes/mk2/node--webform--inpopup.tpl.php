<?php 
$stat=statistics_get($nid);
hide($content['links']);
?>
<div class="<?=$classes;?>">
	<?=render($content);?>
</div>