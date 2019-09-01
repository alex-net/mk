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
						<div class="graph animated"><span><?php echo $tj=token_replace('[mk:rekv:timejob1]');?></span></div>						
					</div>
					<div class="emails">
						<div class="graph animated"><span><?php echo $tj;?></span></div>
						<div class="mail-wrap">
							<div class="min-width-480">
								<div class="email animated marg-do"><?php echo $m1c=token_replace('[mk:rekv:mail-1:colored]');?></div>
								<div class="email animated "><?php echo $m2c=token_replace('[mk:rekv:mail-2:colored]');?></div>
							</div>
							<div class="max-width-479">
								<div class="email animated marg-do"><a href="mailto:<?php echo token_replace('[mk:rekv:mail-1:plain]');?>"><?php echo $m1c;?></a></div>
								<div class="email animated "><a href="mailto:<?php echo token_replace('[mk:rekv:mail-2:plain]');?>"><?php echo $m2c;?></a></div>
							</div>
						</div>
						<div class="socnets-320">
							<?php echo token_replace('[mk:socnets:vk=>https://vk.com/megakrovlia|insta=>https://www.instagram.com/megakrovlya/|fb=>https://www.facebook.com/groups/masterkrowli/]');?>
						</div>
					</div>
					<div class="phones">
						<div class="min-width-480">
							<div class="phone marg-do"><?php echo $p1tc=token_replace('[mk:rekv:phone-1:colored:text]');?></div>
							<div class="phone "><?php echo $p2tc=token_replace('[mk:rekv:phone-2:colored:text]');?></div>
							<div class="phone marg-posle"><?php echo $p3tc=token_replace('[mk:rekv:phone-3:colored:text]');?></div>
						</div>
						<div class="max-width-479">
							<div class="phone marg-do"><a href="tel:<?php echo token_replace('[mk:rekv:phone-1:plain]');?>"><?php echo $p1tc;?></a></div>
							<div class="phone "><a href="tel:<?php echo token_replace('[mk:rekv:phone-2:plain]');?>"><?php echo $p2tc;?></a></div>
							<div class="phone marg-posle"><a href="tel:<?php echo token_replace('[mk:rekv:phone-3:plain]');?>"><?php echo $p3tc;?></a></div>
						</div>
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
		<?php /* 	<aside class="col-lg-8 for_catalog_menu sidebar">
				<?php print render($page['sidebar']); ?>
			</aside>
		*/	?>
			<div id="main_content" class="col-lg-36">
				<?php print $messages; ?>
				<?php //kprint_r(get_defined_vars());?>
				<div class="row">
					<?php print $breadcrumb; ?>
					<?php echo render($page['before-content']);?>
					<?php print render($title_prefix); ?>
					<?php if ($title): ?>
							<div id="page_title_wrap" class="cls">
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
			<div class="ooo"><?php echo $md['footer1-left']; ?></div>

			<div class="copyright"><?php echo $md['footer1-right']; ?></div>
		</div>

		<div class="corp-data-copyr-wrap">
			<div class="ooo"><?php echo $md['footer2-left']; ?></div>
			<div class="figures"><?php echo $md['footer2-center']; ?></div>
			<div class="copyright"><?php echo $md['footer2-right']; ?></div>
		</div>
	</div>
</footer>
