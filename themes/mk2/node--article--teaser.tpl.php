<div class="<?=$classes;?>">
	<?=render($content['field_article_pic']);?>
	<div class="node-body-wrap">
		<div class="title-wrap">
			<div class="date"><?=date('d.m.Y',$created);?></div>
			<a href="<?=$node_url;?>" class='title-link'><?=$title;?></a>
		</div>
		<?=render($content['body']);?>
		<?=render($content);?>
	</div>
	<?php //kprint_r(get_defined_vars());?>
	
</div>