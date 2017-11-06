<?php foreach($data as $v):?>
<div class="akcion-small-el">
	<div class="col-lg-13 pic"><img alt="<?php echo $v['title'];?>" src="<?php echo $v['img']?>" class="img-responsive"></div>    
	<div class="col-lg-23 info"><div class="title"><?php echo $v['title'];?></div>
	<div class="price"><?php echo $v['cp'];?> / <?php echo $v['measure'];?></div>
	<div class="old_price"><?php echo $v['oldp'];?> / <?php echo $v['measure'];?></div></div> 
</div>
<?php endforeach;?>