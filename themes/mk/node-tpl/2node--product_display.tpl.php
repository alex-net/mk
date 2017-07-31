<?php if($teaser): ?>
<div class="wrap_teaser">
	<?php print render($content['field_pic_product']);?>
	<h2><?php print $title; ?></h2>
	<?php print render($content['field_product_variations']);?>
	<?php print render($content['field_views_product_variations']);?>
		<a href="<?php print $node_url; ?>">+</a>
	<div class="hidden">
		<?php print render($content['field_text']);?>
	</div>
</div>
<?php else: ?>
<div class="product full">
	<?php print render($content['field_product_variations']);?>
	<?php print render($content['field_views_product_variations']);?>
</div>
<?php endif; ?>
