<div class="top-line"></div>
<div class='site-head'>
	<a href="<?=$front_page;?>" class='logo'></a>
	<div class="plashko time-job">
		Гипермаркет<br/>строительных&nbsp;материалов
       <div class='interval'><?=token_replace('[mk:rekv:timejob1:plain]');?></div>
	</div>
	<div class="plashko contacts">
		<?=token_replace('[mk:rekv:phone-1:text:plain]<br>[mk:rekv:phone-2:text:plain]');?>
       <?=token_replace("<a class='mail' href='mailto:[mk:rekv:mail-1:plain]'>[mk:rekv:mail-1:plain]</a>");?>
	</div>
	<div class="plashko point-delover">
		<div class='point'>Москва и МО </div>
		<div class='deliver'>Доставка по всей россии</div>
	</div>
	<?=theme('site_cart_head');?>
</div>
<div class="site-hmenu">
	<div class="wrap">
		<?=render($menuSiteHead);?>
		<div class="mobile-block catalog-of-produucts-button" title='Каталог товаров'></div>
		<div class="searchform"><?php $sf=render($sf);echo $sf;?></div>
		<div class="mobile-block mobile-menu-open"><i class="fas fa-ellipsis-v"></i></div>
		<div class="catalog-menu-popup"></div>
	</div>
</div>

<div class="content-wrapper <?=$classes;?>">
	<?php //kprint_r(get_defined_vars());?>
	<?=$breadcrumb;?>
	<?=render($page['underh1']);?>
	<?php if (!empty($title)):?>
		<h1><?=$title;?></h1>
	<?php endif;?>
	<?=$messages;?>
	<?=render($tabs);?>
	<?=render($page['content']);?>
</div>


<div class="footer">
	<div class="page-scroller"><span class="fas fa-chevron-up"></div>
	<div class="menu-line">
		<div class="wrap">
			<div class="item-catalog" title="Каталог товаров"><a href="/">каталог товаров</a></div>
			<div class="searchform"><?=$sf;?></div>
			<div class="catalog-menu-popup"></div>
		</div>
	</div>
	<div class="blocks-in-footer">
		<div class="catalog-tail row">
			<div class="titel">Каталог</div>
			<ul>
				<?php foreach($catl0 as $t):?>
					<li class='item for-<?=$t->tid;?><?=empty($t->childs)?" empty":''?>' data-tid='<?=$t->tid;?>'>
						<a href="<?=url('taxonomy/term/'.$t->tid);?>"><span><?=$t->name;?></span></a>
					</li>
				<?php endforeach;?>
			</ul>
		</div>
		<div class="otcher-block row">
			<?=render($page['footer']);?>
		</div>

	</div>
	<?=token_replace(theme('footercontent'));?>
	

</div>