<div class='you-added-product'>Вы добавили в корзину товар</div>
<?=render($nodeview);?>
<?php if ($nacenka):?>
	<div class='nacenka'><?=$nacenka;?></div>
<?php endif;?>
<div class='info'> Нажмите <span class="checkout-colored">оформить заказ</span> для завершения покупки или нажмите <span class="continue-colored">продолжить покупки</span>, если вас ещё интересуют товары</div>
<div class='buttons'>
	<div class="continue-btn"></div>
	<a class="checkout-btn" href='/cart'></a>
</div>