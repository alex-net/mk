<div class="plashko cart <?=empty($ccart)?'empty':''?>">

	<?php if (empty($ccart)):?>
		<div class="cart-ico"></div>
		<div class="titl">Корзина</div>
	<?php else:?>
		<a class="cart-ico" href='/cart'></a>
		<a class="titl" href='/cart'>Корзина</a>
	<?php endif;?>
	<a class="checkout-button" href="/checkout"><span class='fas fa-arrow-right'></span></a>
	<div class="content">
		<?php if (!empty($ccart)):?>
			<div class='count'><b><?=$ccart['count'];?></b> товаров</div>
			<div class='sum'>Сумма <b><?=$ccart['sum'];?></b> руб.</div>
		<?php else:?>
			<span class='empty-cart'>Ваша корзина пуста </span>
		<?php endif;?>
	</div>
</div>