<?php if($list):?>
<div class='popup-lisks'>
	<div class='show-popup-links'>Часто ищут</div>

	<div class="hl-win-wrapp">
		
		<ul class='l1'>
		<?php foreach($list as $el):?>
			<li>
				<div class="group"><?=$el['name'];?></div>
				<ul class="l2">
					<?php foreach($el['ch'] as $l):?>
						<li><?=$l;?></li>
					<?php endforeach;?>
				</ul>
			</li>
		<?php endforeach;?>
		</ul>
	</div>
</div>
<?php endif;?>