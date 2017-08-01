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
	<?php 
		$b=module_invoke('block','block_view',14);
		echo $b['content'];
	?>

</div>
<script>
	
	jQuery(document).ready(function() {
		jQuery(".sertificates_wrap a").removeAttr('title');
		jQuery(".field-name-field-why-choose-us .field-item").addClass('wow fadeInDown');
	});

</script>