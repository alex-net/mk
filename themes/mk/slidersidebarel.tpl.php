<div class="prod-els-wrap">
<div class="col-lg-36 date">Только <span class="date-display-range">с <span content="<?php echo date('c',$data['afrom']);?>" datatype="xsd:dateTime" property="dc:date" class="date-display-start"><?php echo date('d.m.Y',$data['afrom']);?></span> по <span content="<?php echo date('c',$data['ato']);?>" datatype="xsd:dateTime" property="dc:date" class="date-display-end"><?php echo date('d.m.Y',$data['ato']);?></span></span> </div>    
  <div class="col-lg-36">        
  	<h3><a href="<?php echo $data['url'];?>"><?php echo  $data['title'];?></a></h3>  
  </div>  
	<div class="col-lg-10 pic"><a href="<?php echo $data['url'];?>"><img width="60" height="40" alt="<?php echo $data['title'];?>" src="<?php echo $data['img']?>" class="img-responsive" draggable="false"></a></div>    
          <div class="info col-lg-26"><div class="price">Цена: <span><?php echo $data['cp'];?></span></div>
<div class="old_price">Старая цена: <span class="line-through"><?php echo $data['oldp'];?></span></div>
<a href="<?php echo $data['url'];?>" class="buy_prod_button">подробнее</a></div>  
</div>