<div class="balloon-content">
	<div class="ball-titl"><span><?php echo $title;?> </span >
		<?php if ($subname):?>
		(<?php echo $subname;?>) 
		<?php endif;?>
	</div>
	<div class="ball-body">
		<?php echo $addres;?>
		<?php if ($tel):?>
			<div class="tel"><?php echo $tel;?></div>
		<?php endif; ?>
		<div class="regim-label">Режим работы</div>
		<div class="pn-pt">
			<span>ПН-ПТ</span><?php echo $timepn;?>
		</div>
		<div class="sb-vs">
			<span class="graph"><?php echo $vihi?></span><?php echo $descr;?>
		</div>
	</div>
</div>