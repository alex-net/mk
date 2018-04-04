<div class="product full <?php echo $classes;?>">
	<?php //kprint_r(array_keys($content));?>
	<div class=" clearfix">
		<div class="sku-small"><?php echo render($content['product:sku']);?></div>
		<?php echo render($content['rating']);?>

		<div class="col-lg-12 col-md-12 col-sm-12 col-xs-24 img-block">
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
			<?php echo render($content['field_pic_product']);?>
			<?php echo render($content['counter']);?>	
		</div>
		<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 buy-form full-view-form">
			<?php echo render($content['field_product_variations']);?>
			
		</div>
		<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12  info-tail"><?php echo token_replace('[block:view-content:block:15]');?></div>

	</div>
	<?php echo render($content['tabslinks']);?>
	<?php if (!empty($tabcontent)): ?>
	<div class="current-content-of-tab">
		<div class="wrap clearfix">
			<?php echo render($content[$tabcontent]);?>
		</div>
	</div>
	<?php endif;?>
	
	<div class="mit-buy clearfix product-lists "><?php echo render($content['field_mit_tovar_buy']);?></div>
	<div class="analogs clearfix product-lists "><?php echo render($content['field_tovar_analogs']);?></div>
	<div class="old-viewed product-lists clearfix "><?php echo render($content['prod-viewed']);?></div>

	</div>
	
			
			

