<div class="<?=$classes;?>">
	<div class="product-blocks">
		<div class="image">
			<?=render($content['field_pic_product']);?>
			<?php if (isset($discont_dt)):?>
					<div class="discont-time" data-discont='<?=$discont_dt*1000;?>'></div>
			<?php endif;?>
		</div>
		<div class="form-and-buttons">
			<?=render($content['field_product_variations']);?>
		</div>
		<div class="info-blocks">
			<div class="pay">
				<div class="title">Оплата<span class="i" data-show-node-in-popup="1523">i</span></div>
				Для юридических и физических лиц
			</div>
			<div class="deliver">
				<div class="title">Доставка<span class="i" data-show-node-in-popup="1524">i</span></div>
				Доставка по Москве, Московской, Тверской, Калужской, Рязанской, Ярославской, Владимирской областям и по всей России
			</div>
			<div class="ahtung">
				<div class="title">Внимание!</div>
				О возможности доставки товара в день заказа узнавайте у Вашего менеджера.
			</div>
		</div>
	</div>

	<div class="tabs-of-tovar">
		<div class="tabs-line">
			<div class="info active">Информация</div>
			<?php if (!empty($content['field_harakteristic'])):?>
				<div class="harackterist">Характеристики</div>
			<?php endif;?>
			<div class="opis">Описание</div>
			<?php if (!empty($content['field_instructions'])):?>
				<div class="instruction">Инструкция по применению</div>
			<?php endif;?>
			<div class="otsiv">Отзывы о товаре</div>
		</div>
		<div class="tabs-content">
			<div class="info active"><?=render($content['field_parameters_product']);?></div>
			<?php if (!empty($content['field_harakteristic'])):?>
				<div class="harackterist"><?=render($content['field_harakteristic']);?></div>
			<?php endif;?>
			<div class="opis"><?=render($content['field_text']);?></div>
			<?php if (!empty($content['field_instructions'])):?>
				<div class="instruction"><?=render($content['field_instructions']);?></div>
			<?php endif;?>
			<div class="otsiv">
				<?php if (!empty($content['comments']['comments']) && element_children($content['comments']['comments'])):?>
					<?php //kprint_r($content);?>
					<div class="comments-wrap"><?=render($content['comments']['comments']);?></div>
				<?php endif;?>
				
			</div>
		</div>
		
	</div>
	<?=render($content);?>
	<?php //kprint_r(get_defined_vars());?>
	<?php // kprint_r($content);?>
</div>
	
			
			

