<div class="<?=$classes?>">
	<div class="product-name"><?=$title;?></div>
	<div class="content-wrap">
		<?=render($content['field_pic_product']);?>
		<div class="other-fields">
			<?=render($content);?>
			<?php if(!empty($content['cart-data'])):?>
				<div class='form-text-place'>
					<div class='price-of-product'>Цена за <?=$content['cart-data']['#unit']; ?> = <?=$content['cart-data']['#price-from-product']; ?> руб.</div>
					<div class="qty-added">Количество <?=$content['cart-data']['#added-now'];?> <?=$content['cart-data']['#unit']; ?></div>

					<div class='total-current-added'>Всего = <?=$content['cart-data']['#summ-now']; ?> руб.</div>
				</div>

			<?php endif;?>
		</div>
	</div>
</div>
