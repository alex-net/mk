<?php if($teaser): ?>
<div class="product teaser col-md-9 pad-3 <?php print $classes; ?>"<?php print $attributes; ?>>
	<div class="wrap_teaser">
		<?php print render($content['field_pic_product']);?>
		<?php print render($title_prefix); ?>
			<?php if (!$page): ?>
				<h2><?php print $title; ?></h2>
			<?php endif; ?>
		<?php print render($title_suffix); ?>
		<div class="buy_more">
			<?php print render($content['field_views_product_variations']);?>
			<div class="show_more">Подробнее</div>
		</div>
		<div class="hidden_from_js more_info">
			<?php print render($content['field_parameters_product']);?>
			<?php print render($content['field_text']);?>
			<?php print render($content['flag_comparison']);?>
		</div>
	</div>
</div>
<?php else: ?>
<div class="product full">
	<?php print render($content['field_product_variations']);?>
	<?php print render($content['field_views_product_variations']);?>
	<?php print render($content['flag_comparison']);?>
</div>
<?php endif; ?>
