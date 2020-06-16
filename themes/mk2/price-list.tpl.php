<?php if ($prices):?>
	<?php $p=reset($prices);?>
	<div class="price-list">
		<?php foreach($prices as $i=>$p):?>
			<div class="price-range-item">
				<?php if (!empty($p['from']) && !empty($p['to'])):?>
					<span class="range-count"><?=$p['from'];?> — <?=$p['to'];?> <?php if (!$i):?><?=$p['unit'];?><?php endif;?></span>
				<?php else:?>
					<span class="range-count"><?=!empty($p['from'])?'от '.$p['from']:''?> <?=!empty($p['to'])?'до '.$p['to']:''?> <?php if (!$i):?><?=$p['unit'];?><?php endif;?></span>
				<?php endif;?>
				<span class="price-tail">
					<?php if (!empty($p['field_old_price'])):?>
						<span class="old"><?=number_format($p['field_old_price'],1,'.','');?></span>
					<?php endif;?>
					<span class="cost"><?=number_format($p['commerce_price'],1,'.','');?>&nbsp;<i class="fas fa-ruble-sign"></i></span>
				</span>
			</div>
		<?php endforeach;?>
	</div>
<?php endif;?>