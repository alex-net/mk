<div class="<?=$classes;?>">
	<div class="author"><?=$comment_author;?>
		<span class="stars-wrap" ><span style='width:<?=$comment_stars;?>%'></span></span>
	</div>
	<div class="date"><?=$comment_created;?></div>
	<?=render($content['comment_body']);?>
	<?=render($content['field_tovar_pluss']);?>
	<?=render($content['field_tovar_minus']);?>
	<?php if (user_access('administer comments')):?>
		<?=render($content['links']);?>
	<?php endif;?>
</div>