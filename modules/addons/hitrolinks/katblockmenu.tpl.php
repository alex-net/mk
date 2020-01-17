<?php $ind=0;?>
<ul>
<?php foreach($menu as $i=>$m):?>
	<li <?=$ind>=$limit?'class="el-invis"':''; ?>>
		<span class="wrapper" >
			<a href='<?=$m['href'];?>'><?=$m['title'];?></a>
			<?php if ($m['items']|| 1):?>
				<span class="ptaha"></span>
			<?php endif;?>
		</span>
		<?php if ($m['items']):?>
			<ul>
			<?php foreach($m['items'] as $k=>$v):?>
				<li><a href='<?=$v['href'];?>'><?=$v['title'];?></a></li>
			<?php endforeach;?>
			</ul>
		<?php endif;?>
	</li>
<?php 
$ind++;
endforeach;?>
</ul>

<?php if ($limit>0 && $limit<count($menu)):?>
	<div class='show-more-elements'>Показать ещё</div>
<?php 

endif;?>
