<?php if ($prices):?>
	<div class="price-list">
		<?php foreach($prices as $p):?>
			<div class="price-range-item">
				<span class="range-count"><?=!empty($p['from'])?'от '.$p['from']:''?> <?=!empty($p['to'])?'до '.$p['to']:''?>  <?=$p['unit'];?></span>
				<span class="price-tail">
					<?php if (!empty($p['field_old_price'])):?>
						<span class="old"><?=number_format($p['field_old_price'],1,'.','');?></span>
					<?php endif;?>
					<span class="cost"><?=number_format($p['commerce_price'],1,'.','');?></span> руб/<?=$p['unit'];?>
				</span>
			</div>
		<?php endforeach;?>
	</div>
<?php endif;?>