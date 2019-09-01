<?php foreach($list as $y):?>
	<div class="views-row">  
          <div class="pic col-lg-11"><?php echo $y['img'];?></div>    
          <div class="title_price col-lg-25"><h4><?php echo $y['link'];?></h4></div>
		<div class="price"><?php  echo $y['price'];?> </div>
	</div>

<?php endforeach;?>
<div class="more-link">
  <a href="/bestsellers">
    Все товары  </a>
</div>
