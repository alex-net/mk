<div class="catalog-list">
	<?php foreach($terms['terms'] as $term):?>
		<div class="item<?=empty($term['childs'])?' empty':''?>" data-id='<?=$term['tid'];?>' data-href='<?=$term['href'];?>'>
			<div class="cat-image" style='background-image:url(<?=$term['img'];?>);'></div>
			<div class='tax-title'><a href="<?=$term['href'];?>"><?=$term['name'];?></a></div>
			<?php if (!empty($term['childs'])):?>
				<div class='open btn-controls' title='Развернуть'><span class="arrow">&darr;</span></div>
				<div class='close btn-controls' title='Свернуть'><span class="arrow">&uarr;</span></div>
			<?php else:?>
				<a class='btn-controls go-to' title='Перейти'><span class="arrow">&rarr;</span></a>
			<?php endif;?>

		</div>
		<div class="subitems for-<?=$term['tid'];?>"></div>
	<?php endforeach;?>
</div>