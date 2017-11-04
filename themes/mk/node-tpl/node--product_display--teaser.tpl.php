<div id="product_<?php print $node->nid; ?>" class="product teaser col-md-9 pad-3 <?php print $classes; ?>"<?php print $attributes; ?>>
	<div class="wrap_teaser">
		<?php 
			switch($marker){
				case '132':
					echo "<div class='icon_hit'></div>";
				break;
				case '224':
					echo "<div class='icon_new'></div>";
				break;
				case '313':
					echo "<div class='best_product'></div>";
					break;
			}
		?>
    	<?php print render($content['counter']);?>
		<?php print render($content['field_pic_product']);?>
		<?php print render($title_prefix); ?>
			<?php if (!$page): ?>
				<h2><a href="<?php echo $node_url;?>"><?php print $title; ?></a></h2>
			<?php endif; ?>
		<?php print render($title_suffix); ?>
		<div class="buy_more">
			<?php print render($content['field_product_variations']);?>
			<div class="show_more" data-link="<?php echo $node_url;?>">Подробнее</div>
		</div>
		<div class="hidden_from_js more_info">
			<?php //print render($content['field_text']);?>
			<?php print render($content['field_parameters_product']);?>
			<?php print render($content['flag_comparison']);?>
		</div>
	</div>
</div>