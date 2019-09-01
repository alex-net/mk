<div class="<?=$classes;?>  n-<?=$nid;?>">
	<div class="n-wrap">
		<?=render($title_suffix);?>
		<?=render($content['field_pic_product']);?>
		<a href='<?=$node_url?>' class='title'><?=$title;?></a>
		<?=render($content['field_product_variations']);?>
		<div class="more-block">
			<div class="morebtn">Подробнее</div>
			<?=render($content['field_parameters_product']);?>
		</div>
		
	</div>
</div>