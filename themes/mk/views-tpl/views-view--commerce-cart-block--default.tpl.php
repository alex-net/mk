<div class="links_main row">
	<div class="to_cart col-md-36 col-lg-12">
		<div class="row">
			<a href="/cart">КОРЗИНА</a>
		</div>
	</div>
	<div class="to_chackout col-md-24 col-lg-24">
		<div class="row visible-lg">
			<a href="/checkout">ОФОРМИТЬ ЗАКАЗ</a>
		</div>
	</div>
</div>
<div class="values row">
	<div class="cart_pic col-lg-9  visible-lg">
		<div class="row">
			<a href="/cart"></a>
		</div>
	</div>
	<div class="val col-lg-27">
		<div class="row"> 
			<?php if ($rows): ?>
		      	<?php print $footer; ?>
			<?php elseif ($empty): ?>
				<?php print $empty; ?>
			<?php endif; ?>
		</div>
	</div>
</div>