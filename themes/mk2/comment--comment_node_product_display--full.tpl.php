<?php
$comUser=user_load($comment->uid);
$isAdmin=array_search('administrator',$comUser->roles)!==false;

 if ($comment->pid):
	$classes.=' indented';
endif ?>
<div class="<?=$classes;?>">
	<div class="author"><?=$isAdmin?'Админ':$comment_author;?>
		<?php if (!$isAdmin):?><span class="stars-wrap" ><span style='width:<?=$comment_stars;?>%'></span></span><?php endif;?>
	</div>
	<div class="date"><?=$comment_created;?></div>
	<?=render($content['comment_body']);?>
	<?=render($content['field_tovar_pluss']);?>
	<?=render($content['field_tovar_minus']);?>
	<?php if (user_access('administer comments')):?>
		<?=render($content['links']);?>
	<?php endif;?>
</div>
