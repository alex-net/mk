<?php foreach($data as $v):?>
<div class="akcion-big-el clearfix">
	<div class="col-sm-21 col-md-21"><h2><span><?php echo $v['titletop'];?></span><span><?php echo $v['titlebottom'];?></span></h2>
	<p>Битумный праймер предназначен для обработки бетонных и цементно-песчаных стяжек перед началом кровельных или гидроизоляционных работ. Позволяет...</p>
	<div class="price_buy_button">
	<div class="price_discount_wrap"><span class="discount_price">Акционная цена: <?php echo $v['cp'];?>  / <span><?php echo $v['measure'];?></span></span></div>
	<a href="<?php echo $v['url'];?>" class="buy_prod_button">подробнее</a>
	</div>
	<div class="old_price">Старая цена: <span class="crossed"><?php echo $v['oldp'];?></span> / <span><?php echo $v['measure'];?></span></div></div>    
	  <span class="views-field views-field-field-pic-product">  <span class="field-content col-sm-15 col-md-15"><img width="350" height="220" alt="<?php echo $v['title']; ?>" src="<?php  echo $v['img'];?>" class="img-responsive"></span>  </span>
</div>
<?php endforeach;?>