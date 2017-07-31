<div class="contacts_node vcard">
	<div class="top row">
		<div class="left col-sm-18 col-lg-18">
			<?php print render($content['field_phone_contacts']);?>
			<?php print render($content['field_e_mail_contacts']);?>
		</div>
		<div class="right col-sm-18 col-lg-13 col-lg-offset-2">
			<?php print render($content['field_logo_contacts']);?>
		</div>
	</div>
	<div class="middle row">
		<div class="left col-lg-17"><h3>Погрузка производится погрузчиком.</h3></div>
		<div class="right col-lg-17 col-lg-offset-2 pull-right hidden-xs hidden-sm">
			<h3>Мы в Интернете:  <span class="red">www.masterkrowli.ru</span></h3>
		</div>
	</div>
	<div class="row">
		<div class="col-lg-36">
		<br>
		<?php print render($content['field_message_to_client']);?>
	</div>
	<div class="bottom row">
		<div class="left col-sm-18 col-lg-17">
			<h2>Основной склад</h2>
			<?php print render($content['field_time_work_main']);?>
			<?php print render($content['field_download_main_map']);?>
			<?php print render($content['field_main_dynamic_map']);?>
			<?php print render($content['field_main_static_map']);?>
			<?php print render($content['field_address_main_link']);?>
		</div>
		<div class="right col-sm-18 col-lg-17 col-lg-offset-2">
			<h2>Склад по геотекстилю</h2>
			<?php print render($content['field_time_work_geo']);?>
			<?php print render($content['field_download_geo_map']);?>
			<?php print render($content['field_geo_dynamic_map']);?>
			<?php print render($content['field_geo_static_map']);?>
			<?php print render($content['field_address_geo_link']);?>
		</div>
	</div>
</div>