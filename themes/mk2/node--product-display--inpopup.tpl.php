<div class="<?=$classes?>">
	<div class="product-name"><?=$title;?></div>
	<div class="content-wrap">
		<?=render($content['field_pic_product']);?>
		<div class="other-fields">
			<?=render($content);?>
			<?php if(!empty($content['cart-data'])):?>
				<div class='form-text-place'>
					<div class='one-product'><?=$content['cart-data']['#added-now'];?> <?=$content['cart-data']['#unit']; ?> = <?=$content['cart-data']['#price-from-product']; ?> руб.</div>
					<div class='total-current-added'>Всего = <?=$content['cart-data']['#summ-now']; ?> руб.</div>
				</div>
				
			<?php endif;?>
		</div>
	</div>
	
</div>
