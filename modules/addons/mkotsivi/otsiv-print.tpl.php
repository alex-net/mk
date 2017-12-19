<div class="otsiv-item <?php echo $addonclass;?>">
	<div class="date"><?php echo render($el['time']);?></div>
	<div class="container-inline autor-data">
		<?php echo render($el[2]);?> 
	</div>
	<?php echo drupal_render_children($el);?>
	
</div>