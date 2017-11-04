<div class="about_node">
	<div class="about col-xs-36">
		<?php print render($content['field_pic_about']);?>
		<?php print render($content['body']);?>
	</div>
	<div class="why_choose_us col-xs-36">
		<h3 class="animated fadeInDown paddl05em">Мы решим Ваши проблемы <b>быстро</b> и <b>удобно</b> <span class="potomu-chto">потому, что</span> </h3>
		<?php print render($content['field_why_choose_us']);?>
	</div>
	<div class="certificates col-xs-36">
		<h3 class="first wow fadeInDown paddl05em"><span class="red">Присоединяйтесь к нам</span> и Вы будете с успехом пользоваться всеми преимуществами!</h3>
		<h3 class="wow bounceInRight paddl05em">Мы работаем с НДС и платим налоги</h3>
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
	<?php echo token_replace('[block:view-content:block:14]');?>

</div>
<script>
	
	jQuery(document).ready(function() {
		jQuery(".sertificates_wrap a").removeAttr('title');
		jQuery(".field-name-field-why-choose-us .field-item").addClass('wow fadeInDown');
	});

</script>