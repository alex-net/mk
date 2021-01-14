
<div class="buttons-block qty-wrapp">
	<div class="left-tail">
		<noindex>
			<?=render($form['qty-wrap']['qty']);?>
		</noindex>
		<div class="tovar-back" data-show-node-in-popup="1549">Возврат</div>
		<div class="tovar-change" data-show-node-in-popup="1550">Обмен</div>
	</div>
	<div class="right-tail">
		<?=render($form['qty-wrap']['real-cost']);?>
		<?=drupal_render_children($form);?>
		<div class="quick-order" data-openform-quick-zakaz>Быстрый заказ</div>
		<div class="buy-in-credit" data-show-tpl-in-popup="uslovia-of-kredit-for-pokupatel">Купить в кредит</div>
	</div>
</div>