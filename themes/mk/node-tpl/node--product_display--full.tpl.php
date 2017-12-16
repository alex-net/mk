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
	
	<div class="infa-tabs tabinit">
		<div class="tabs-wrap">
			<ul>
				<li><a href="#tovar-full-infa">Информация</a></li>
				<?php if (!empty($content['field_harakteristic'])):?>
					<li><a href="#tovar-full-haract">Характеристики</a></li>
				<?php endif;?>
				<?php if (!empty($content['field_text'])):?>
					<li><a href="#tovar-full-descr">Описание</a></li>
				<?php endif;?>
				<?php if (!empty($content['comments'])):?><li><a href="#tovar-full-otsivs">Отзывов о товаре(<?php echo $comment_count;?>)</a></li><?php endif;?>
			</ul>
			<div id='tovar-full-infa'><div class="wrap "><?php echo render($content['field_parameters_product']);?></div></div>
			<?php if (!empty($content['field_harakteristic'])):?>
				<div id='tovar-full-haract'><div class="wrap "><?php echo render($content['field_harakteristic']);?></div></div>
			<?php endif;?>
			<?php if (!empty($content['field_text'])):?>
				<div id='tovar-full-descr'><div class="wrap clearfix"><?php echo render($content['field_text']);?></div></div>
			<?php endif;?>
			<?php if (!empty($content['comments'])):?>
				<div id='tovar-full-otsivs'><div class="wrap clearfix"><?php echo render($content['comments']);?></div></div>
			<?php endif;?>
		</div>
	</div>
	<div class="mit-buy clearfix product-lists "><?php echo render($content['field_mit_tovar_buy']);?></div>
	<div class="analogs clearfix product-lists "><?php echo render($content['field_tovar_analogs']);?></div>
	<div class="old-viewed product-lists clearfix "><?php echo render($content['prod-viewed']);?></div>


</div>