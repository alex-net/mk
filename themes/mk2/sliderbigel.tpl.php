<?php foreach($data as $v):?>
	<div class="slider-el <?=$v['classe'];?>">
		<h2><span><?php echo $v['titletop'];?></span><span><?php echo $v['titlebottom'];?></span></h2>
		<div class="body"><?php echo $v['body'];?></div>
		<a class="more-link" href="<?php echo $v['url'];?>" >подробнее</a>
		<?php if ($v['type']=='akcia'):?>
			<div class="prices">
				<div class="title">акция</div>
				<div class="new"><?php echo $v['cp'];?></div>
				<div class="v">руб. / <?php echo $v['measure'];?></div>
				<div class="old"><?php echo $v['oldp'];?></div>
			</div>
			<div class="kartinko" style='background-image:url(<?=$v['img'];?>);'></div>
		<?php endif;?>
	</div>
<?php endforeach;?>