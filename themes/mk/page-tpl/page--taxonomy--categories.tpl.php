<header class="full_width header">
	<div class="container-fluid">
		<div class="row logo_contacts_cart">
			<?php if ($logo): ?>
		        <div class="logo col-sm-9 col-xs-18 col-lg-8">
		        	<div class="logo_wrap row">
		        		<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
		        		  <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
		        		</a>
		        	</div>
		        </div>
			<?php endif; ?>
			<div class="contacts hidden-xs col-sm-18 col-lg-12 col-lg-offset-4">
				<div class="row">
					<div class="emails col-xs-16 col-lg-16">
						<div class="email animated"><span>9485571</span>@mail.ru</div>
						<div class="email animated col-xs-offset-3 col-lg-offset-3"><span>4927025</span>@mail.ru</div>
					</div>
					<span class="line"></span>
					<div class="phones col-xs-20 col-lg-20">
						<div class="phone"><span>8 (499)</span>492-70-25</div>
						<div class="phone col-xs-offset-3 col-lg-offset-3"><span>8 (926)</span>609-41-61</div>
						<div class="phone col-xs-offset-6 col-lg-offset-6"><span>8 (926)</span>959-99-25</div>
					</div>
				</div>
			</div>
			<div class="cart col-xs-18 col-sm-9 col-lg-8 col-lg-offset-4">
				<?php echo views_embed_view('commerce_cart_block', 'default'); ?>
			</div>
		</div>
		<div class="row link_catalog_main_menu">
			<div class="catalog col-xs-25 col-lg-8">
				<a href="/catalog">Каталог товаров</a>
			</div>
			<div id="main_menu" class="col-xs-10 col-xs-14 col-lg-28">
				<div class="menus row">
					<a href="/discounts">Акции</a>
					<?php print render($page['main_menu']); ?>
				</div>
				<div class="search col-xs-18 col-sm-18 hidden-xs hidden-sm hidden-md hidden-lg">
					<a href="/search">Поиск</a>
				</div>
			</div>
		</div>
		<div id="block-search-form">
			<h2>Введите название товара для поиска: </h2>
			<div class="content">
				<div class="container-inline">
					<div class="ya-site-form ya-site-form_inited_no" onclick="return {'action':'http://www.masterkrowli.ru/search','arrow':false,'bg':'transparent','fontsize':13,'fg':'#000000','language':'ru','logo':'rb','publicname':'Поиск по сайту masterkrowli.ru','suggest':true,'target':'_self','tld':'ru','type':2,'usebigdictionary':true,'searchid':2232022,'webopt':false,'websearch':false,'input_fg':'#000000','input_bg':'#ffffff','input_fontStyle':'normal','input_fontWeight':'normal','input_placeholder':'Поиск по сайту masterkrowli.ru','input_placeholderColor':'#000000','input_borderColor':'#cc0000'}"><form action="https://yandex.ru/sitesearch" method="get" target="_self"><input type="hidden" name="searchid" value="2232022"/><input type="hidden" name="l10n" value="ru"/><input type="hidden" name="reqenc" value=""/><input type="search" name="text" value=""/><input type="submit" value="Найти"/></form></div><style type="text/css">.ya-page_js_yes .ya-site-form_inited_no { display: none; }</style><script type="text/javascript">(function(w,d,c){var s=d.createElement('script'),h=d.getElementsByTagName('script')[0],e=d.documentElement;if((' '+e.className+' ').indexOf(' ya-page_js_yes ')===-1){e.className+=' ya-page_js_yes';}s.type='text/javascript';s.async=true;s.charset='utf-8';s.src=(d.location.protocol==='https:'?'https:':'http:')+'//site.yandex.net/v2.0/js/all.js';h.parentNode.insertBefore(s,h);(w[c]||(w[c]=[])).push(function(){Ya.Site.Form.init()})})(window,document,'yandex_site_callbacks');</script>
				</div>
			</div>
		</div>
	</div>
</header>
<div class="full_width container_wrap">
	<div class="container-fluid">
		<div class="row">
			<aside class="col-lg-8 for_catalog_menu sidebar">
				<?php print render($page['sidebar']); ?>
			</aside>
			<div id="main_content" class="col-lg-28 category_product">
				<div class="row">
					<div class="col-lg-36"><?php print $breadcrumb; ?></div>
					<?php print render($title_prefix); ?>
					<?php if ($title): ?>
							<div class="col-lg-36 page_title">
								<h1 class="title" id="page-title">
									<?php print render($page['content']['system_main']['term_heading']['term']['field_h1']); ?>
								</h1>
							</div>
						<?php endif; ?>
					<?php print render($title_suffix); ?>
					<?php print $messages; ?>
					<?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
					<?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
					<div class="col-lg-36 pad-9"><?php print render($page['content']); ?></div>
					<?php 
						$block = block_load('views', 'description_product_under-block');
						$block_content = _block_get_renderable_array(_block_render_blocks(array($block)));
						print render($block_content);
						
						$block = block_load('views', 'CatalogTerm-block');
						$block_content = _block_get_renderable_array(_block_render_blocks(array($block)));
						print render($block_content);
					?>
				</div>
			</div>
		</div>
		<div class="wrapupdown">
			<div class="up_down">
				<a href="#" class="up"><span></span></a>
				<a href="#" class="down"><span></span></a>
			</div>
		</div>
	</div>
</div>
<footer class="full_width">
	<div class="container-fluid text-center">
		<div class="row top menu">
			<?php print render($page['duplicate_main_menu']); ?>
		</div>
		<div class="row bottom">
			<div class="ooo col-lg-12">
				<p>ООО ГК «МегаКровля»</p>
			</div>
			<div class="figures col-lg-12">
				<p>ИНН: 7717797576          ОГРН: 5147746240384</p>
			</div>
			<div class="copyright col-lg-12">
				<p>&copy; <?php	$year = 2007; if (date('Y') > $year) {echo $year, " - ", date('Y');}else {echo $year, " г.";}?> МегаКровля. Все права защищены.</p>
			</div>
		</div>
	</div>
</footer>
