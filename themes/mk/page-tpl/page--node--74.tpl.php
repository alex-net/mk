<header class="full_width header">
	<div class="container-fluid">
		<div class="row over-head-blocks">
			<div class="wrapp">
			<div class="titl">гипермаркет<br/>cтроительных материалов </div>
			<div class="socnet--767"><?php echo token_replace('[mk:socnets:vk=>https://vk.com/megakrovlia|insta=>https://www.instagram.com/megakrovlya/|fb=>https://www.facebook.com/groups/masterkrowli/]');?></div>
			<div class="cart-block"><?php echo $cart_block=views_embed_view('commerce_cart_block', 'default'); ?></div>
			</div>
		</div>
		<div class=" logo_contacts_cart">
			<?php if ($logo): ?>
		        <div class="logo ">
		        	<div class="logo_wrap">
		        		<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
		        		  <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
		        		</a>
		        	</div>
		        </div>
			<?php endif; ?>
			
			<div class="contacts">
					<div class="graphs ">
						<div class="titl">гипермаркет<br/>cтроительных материалов </div>
						<div class="graph animated"><span>ПН-ПТ: 9.00 - 19.00</span></div>						
					</div>
					<div class="emails">
						<div class="graph animated"><span>ПН-ПТ: 9.00 - 19.00</span></div>
						<div class="mail-wrap">
							<div class="email animated marg-do"><span>9485571</span>@mail.ru</div>
							<div class="email animated "><span>4927025</span>@mail.ru</div>
						</div>
						<div class="socnets-320">
							<?php echo token_replace('[mk:socnets:vk=>https://vk.com/megakrovlia|insta=>https://www.instagram.com/megakrovlya/|fb=>https://www.facebook.com/groups/masterkrowli/]');?>
						</div>
					</div>
					<div class="phones">
						<div class="phone marg-do"><span>8 (499)</span>492-70-25</div>
						<div class="phone "><span>8 (495)</span>664-44-21</div>
						<div class="phone marg-posle"><span>8 (926)</span>609-41-61</div>
					</div>
			</div>
			<div class="cart ">
				<?php echo $cart_block; ?>
			</div>
			
		</div>

		<div class="row link_catalog_main_menu">
			<div class="catalog">
				<a href="/catalog">Каталог товаров</a>
			</div>
			<div class="socnet-1024-1280"><?php echo token_replace('[mk:socnets:vk=>https://vk.com/megakrovlia|insta=>https://www.instagram.com/megakrovlya/|fb=>https://www.facebook.com/groups/masterkrowli/]');?></div>
			<div id="main_menu" >
				<div class="menus">
					<a class="akcii" href="/discounts">Акции</a>
					<span class="search-butt"></span>
					<div class="search-form"><?php echo $searchform;?></div>
					<span class='menu-button' ></span>
					<?php echo render($page['main_menu']); ?>
				</div>
			</div>
		</div>
		<div id="block-search-form">
			<h2>Введите название товара для поиска: </h2>
			<div class="content">
				<div class="container-inline">
					<div class="ya-site-form ya-site-form_inited_no" onclick="return {'action':'https://www.masterkrowli.ru/search','arrow':false,'bg':'transparent','fontsize':13,'fg':'#000000','language':'ru','logo':'rb','publicname':'Поиск по сайту masterkrowli.ru','suggest':true,'target':'_self','tld':'ru','type':2,'usebigdictionary':true,'searchid':2232022,'webopt':false,'websearch':false,'input_fg':'#000000','input_bg':'#ffffff','input_fontStyle':'normal','input_fontWeight':'normal','input_placeholder':'Поиск по сайту masterkrowli.ru','input_placeholderColor':'#000000','input_borderColor':'#cc0000'}"><?php echo $searchform;?></div><style type="text/css">.ya-page_js_yes .ya-site-form_inited_no { display: none; }</style><script type="text/javascript">(function(w,d,c){var s=d.createElement('script'),h=d.getElementsByTagName('script')[0],e=d.documentElement;if((' '+e.className+' ').indexOf(' ya-page_js_yes ')===-1){e.className+=' ya-page_js_yes';}s.type='text/javascript';s.async=true;s.charset='utf-8';s.src=(d.location.protocol==='https:'?'https:':'http:')+'//site.yandex.net/v2.0/js/all.js';h.parentNode.insertBefore(s,h);(w[c]||(w[c]=[])).push(function(){Ya.Site.Form.init()})})(window,document,'yandex_site_callbacks');</script>
					
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
			<div id="main_content" class="col-lg-28">
				<div class="row">
					<?php print $messages; ?>
					<?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
					<?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
					<?php print render($page['content']); ?>
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
		<div class="row bottom"><?php echo render($page['footer']);?></div>
	</div>
</footer>
