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
				По Москве, Московской, Тверской, Калужской, Рязанской, Ярославской, Владимирской областям и по России
			</div>
			<div class="ahtung">
				<div class="title">Внимание!</div>
				О возможности поставки в день заказа узнавайте у менеджера.
			</div>
		</div>
	</div>

	<div class="tabs-of-tovar">
		<div class="tabs-line">
			<div class="info active"><span>Информация</span></div>
			<?php if (!empty($content['field_harakteristic'])):?>
				<div class="harackterist"><span>Характеристики</span></div>
			<?php endif;?>
			<div class="opis"><span>Описание</span></div>
			<?php if (!empty($content['field_instructions'])):?>
				<div class="instruction"><span>Инструкция по применению</span></div>
			<?php endif;?>
			<div class="otsiv"><span>Отзывы о товаре</span></div>
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
				<?php if (!empty($content['comments'])):?>
					<?php //kprint_r($content);?>
					<div class="comments-wraper"><?=render($content['comments']);?></div>
				<?php endif;?>
				
			</div>
		</div>
		
	</div>
	<?=render($content);?>
	<?php //kprint_r(get_defined_vars());?>
	<?php // kprint_r($content);?>
</div>
	
			
			

