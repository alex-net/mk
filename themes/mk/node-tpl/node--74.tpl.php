<div class="col-xs-36 col-lg-36 error404">
	<?php print render($content['body']);?>
	<div class="search">
		<?php 
			$block = block_load('search', 'form');
			$block_content = _block_get_renderable_array(_block_render_blocks(array($block)));
			print render($block_content);
		?>
	</div>
	<?php 
		$block = block_load('menu', 'menu-404-links');
		$block_content = _block_get_renderable_array(_block_render_blocks(array($block)));
		print render($block_content);
	?>
</div>