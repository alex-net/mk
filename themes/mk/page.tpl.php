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
					<div class="search-form-menu"><?php echo $sf=render($page['searchform']);?></div>
					<span class='menu-button' ></span>
					<?php echo render($page['main_menu']); ?>
				</div>
			</div>
		</div>
		<div class="site-search">
			<h2>Введите название товара для поиска: </h2> <?php echo $sf;?>
			
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
				<?php print $messages; ?>
				<?php //kprint_r(get_defined_vars());?>
				<div class="row">
					<?php print $breadcrumb; ?>
					<?php print render($title_prefix); ?>
					<?php if ($title): ?>
							<div id="page_title_wrap">
								<h1 class="title" id="page-title">
									<?php print $title; ?> <?php echo render($sku);?>
								</h1>
							</div>
						<?php endif; ?>
					<?php print render($title_suffix); ?>
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
	<div class="footer-blocks-wrap">
		<?php echo render($page['footer']);?>
	</div>
	<div class="corp-data-copyr">
		<div class="corp-data-copyr-wrap">
			<div class="ooo"><?php echo $md['footer-left']; ?></div>
			<div class="figures"><?php echo $md['footer-center']; ?></div>
			<div class="copyright"><?php echo $md['footer-right']; ?></div>
		</div>
	</div>
</footer>
