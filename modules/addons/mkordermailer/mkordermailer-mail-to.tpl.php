<div style='width: <?=$width?>px;margin:0 auto;border: 8px solid #9a2a9cbb;padding: 0.5em;font-size:18px;background:white;'>
	<div style='text-align: center;margin: 1em 0;'>
		<a href="http://masterkrowli.ru"><img src="http://masterkrowli.ru/sites/all/themes/mk/i/logo.png" /> </a>
	</div>
	<hr>
	<?php if (empty($forManager)):?>
		
		<p>[commerce-order:field-form-ordering:field-user-name], спасибо за заказ <b>№[commerce-order:order-id]</b> на сайте Группы компаний <b style="color:#B22222;">"МегаКровля".</b></p>
		<p style="color: #6c6c6c;">Наш менеджер свяжется с Вами в ближайшее время по телефону: <span style="color: black;">[commerce-order:field-form-ordering:field-user-phone]</span></p>
		<hr>
	<?php endif;?>
	<?php if($items):?>
		<table width="100%;" cellpadding="15" style="border-collapse: collapse;">
			<thead style="font-size: 16px;">
				<tr>
					<th style="text-align: left;border-bottom:1px solid <?=$gscolor?>;" colspan="2">Заголовок</th>
					<th style="border-bottom:1px solid <?=$gscolor?>;">Цена</th>
					<th style="border-bottom:1px solid <?=$gscolor?>;">Количество</th>
					<th style="border-bottom:1px solid <?=$gscolor?>;">Итого</th></tr>
			</thead>
			<tbody>
			<?php foreach($items as $el):?>
				<tr style="font-size: 14px;">
					<td><a href="<?=$el['link'];?>"><img style="border: 1px solid <?=$gscolor?>;" src="<?=$el['img'];?>"></a></td>
					<td><a style="color:black;text-decoration: none;"  href="<?=$el['link'];?>"><?=$el['title'];?></a><br/>(<?=$el['size'];?>)</td>
					<td style="color: <?=$gscolor;?>; text-align:right;"><?=$el['price'];?></td>
					<td style="color: <?=$gscolor;?>; text-align:right;"><?=number_format(intval($el['quantity']),0,',',' ');?></td>
					<td style="color: <?=$rcolor;?>; text-align:right;"><?=$el['ptotal'];?></td>

				</tr>
			<?php endforeach;?>
			</tbody>
		</table>
	<?php endif;?>
	<?php /*<div class="table_order">[commerce-order:commerce_line_items]</div> */ ?>
	<div style="padding: 10px;">
		<table style=" align-items: center;padding: 10px 15px;background-color: #fcf7fd; width: 100%;"><tr>
			<td style="color:#640a66; text-transform: uppercase;font-size: 14px"><b>Общая сумма заказа:</b></td>
			<td align="right">
				<b style=" display: block;color:<?=$rcolor;?>;font-size: 24px;">[commerce-order:commerce_order_total]</b> 
				<span style="color:<?=$scolor;?>;font-size: 14px;">включая НДС, без стоимости доставки</span>
			</td>
		</tr></table>
	</div>
	
		
	
	<br /><br />
	<div >
		<h3 style="text-transform: uppercase;">Общая информация:</h3>
		<hr>
		<div>
			<p>Имя: <span style="color:<?=$gscolor;?>">[commerce-order:field-form-ordering:field-user-name]</span> <?php /*[commerce-order:field-form-ordering:field-user-last-name] */ ?></p>

			<p>Телефон: <span style="">[commerce-order:field-form-ordering:field-user-phone] </span></p>

			<p>E-mail: <span style="color:<?=$gscolor;?>">[commerce-order:field-form-ordering:field-email] </span></p>

			<p>Адрес доставки:<span style="color:<?=$gscolor;?>"> [commerce-order:field-form-ordering:field-address-delivery] </span></p>

			<p>Примечания к заказу:<span style="color:<?=$gscolor;?>"> [commerce-order:field-form-ordering:field-comments-to-order] </span></p>
		</div>
	</div>
	<hr>
	<div style="color:<?=$gscolor;?>;font-size: 14px;">Дата и время оформления заказа: <b>[commerce-order:created]</b>
		<?php if (empty($forManager)):?>
			<p>С уважением, Группа компаний  <b style="color:<?=$rcolor;?>;">МегаКровля</b></p>
		<?php endif;?>
	</div>
	

</div>
