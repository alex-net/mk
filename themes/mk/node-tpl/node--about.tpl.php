<div class="about_node">
	<div class="about col-xs-36">
		<?php print render($content['field_pic_about']);?>
		<?php print render($content['body']);?>
	</div>
	<div class="why_choose_us col-xs-36">
		<h3 class="animated fadeInDown">Наши <span class="color">ПРЕИМУЩЕСТВА!</span> <i>Или почему выбирают нас</i></h3>
		<?php print render($content['field_why_choose_us']);?>
	</div>
	<div class="certificates col-xs-36">
		<h3 class="first wow fadeInDown">Присоединяйтесь к нам и <span class="red">Вы</span> будете с <span class="color">успехом</span> пользоваться всеми <span class="color">преимуществами!</span></h3>
		<h3 class="wow bounceInRight">Также <span class="color">ПОСМОТРИТЕ</span> наши <span class="color">СВИДЕТЕЛЬСТВА</span> о  регистрации</h3>
		<div class="sertificates_wrap">
			<div class="col-xs-18 wow fadeInUp">
				<?php print render($content['field_certificate_img_1']);?>
				<?php print render($content['field_download_certificate_1']);?>
			</div>
			<div class="col-xs-18 wow fadeInUp" data-wow-delay="0.5s">
				<?php print render($content['field_certificate_img_2']);?>
				<?php print render($content['field_download_certificate_2']);?>
			</div>
		</div>
	</div>
	<div class="quastions col-xs-36">
		<h3 class="wow zoomIn">Все еще есть <span class="color">ВОПРОСЫ</span>? <i>С удовольствием ответим на них!</i></h3>
		<div class="logo_info row">
			<div class="logo col-md-12 hidden-sm wow flipInY">
				<img src="/sites/all/themes/mk/i/logo_about_page.png" alt="МегаКровля">
			</div>
			<div class="info col-md-24">
				<div class="row top">
					<div class="col-sm-16 emails wow fadeInLeft">
						<p>4927025@mail.ru</p>
						<p>9485571@mail.ru</p>
					</div>
					<div class="col-sm-20 phones wow fadeInRight">
						<p>8-926-609-41-61</p>
						<p>8-965-367-87-68</p> 
						<p class="red">(499) 492-70-25 многоканальный</p>
					</div>
				</div>
				<div class="row bot">
					<div class="col-sm-16 address wow fadeInLeft">
						<p>г. Москва, </p>
						<p>Строительный проезд,</p> 
						<p>д. 7 а, корп.35</p>
					</div>
					<div class="col-sm-20 time_work wow fadeInRight">
                       <p><b>Пн-Пт:</b>    8.00 - 17.00 (без перерыва)</p>
                       <p><b>Суббота:</b>  с 8.00 до 14.00</p>
                       <p><b>Воскресенье:</b>  выходной</p>
					</div>
				</div>
			</div>
		</div>
	</div>
</div>
<script>
	
	jQuery(document).ready(function() {
		jQuery(".sertificates_wrap a").removeAttr('title');

		jQuery(".field-name-field-why-choose-us .field-item").addClass('wow fadeInDown');
	});

</script>