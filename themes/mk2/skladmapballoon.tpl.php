<div class="balloon-content">
	<div class="ball-titl"><span><?php echo $title;?> </span >
		<?php if ($subname):?>
		<?php echo $subname;?>
		<?php endif;?>
	</div>
	<div class="ball-body">
		<?php echo $addres;?>
		<?php if ($tel):?>
			<div class="tel"><?php echo $tel;?></div>
		<?php endif; ?>
		<div class="graphik">
			<?php echo $timepn;?>
			<div class='vihi'><?php echo $vihi?></div>
		</div>
		<div class="descr-primechanie"><?=$descr;?></div>
	</div>
</div>