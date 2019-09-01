<div class='<?=$classes;?>'>
	<?=nodetokens_replacer('[block:view-content:block:14]');?>
	<div class='two-blocks'>
		<div class='nalog-data'>
			<p>Краткое наименование организации - <span><?=token_replace('[mk:rekv:short-name]');?></span></p>
			<p>Юридический адрес - <span><?=token_replace('[mk:rekv:ur-addres]');?></span></p>
			<p>Фактический адрес - <span><?=token_replace('[mk:rekv:fakt-addres]');?></span></p>
			<p>ИНН - <span><?=token_replace('[mk:rekv:inn]');?></span></p>
			<p>КПП - <span><?=token_replace('[mk:rekv:kpp]');?></span></p>
			<p>ОГРН - <span><?=token_replace('[mk:rekv:ogrn]');?></span></p>
			<p>Полное наименование банка - <span><?=token_replace('[mk:rekv:full-bank-name]');?></span></p>
			<p>Номер расчетный счет - <span><?=token_replace('[mk:rekv:rs]');?></span></p>
			<p>Номер корреспондентского счета - <span><?=token_replace('[mk:rekv:kor-s]');?></span></p>
			<p>БИК - <span><?=token_replace('[mk:rekv:bik]');?></span></p>
		</div>
		<div class="free-pogruska">
			<ul>
				<li><span>Древесно-плитные и плитные материалы грузятся только в машины с открывающимся боковым бортом.</span></li>
				<li><span>На всех складских комплексах товары отпускаются только при наличии доверенности из офиса.</span></li>
				<li><span>Наличные средства на складах не принимаются, возможна дистанционная оплата.</span></li>
				<li><span>Доставку товаров в субботу необходимо оформлять заранее.</span></li>
			</ul>
			<div class="fee-text">Погрузка производится погрузчиком бесплатно</div>
		</div>
	</div>

	<div class="subtitle">Наши основные складские комплексы</div>
	<div class="descr">Заезд на склады прекращается за час до окончания работы гипермаркета<br/>
		<div class="subdescr">О режиме работы других складов узнавайте у Вашего менеджера.</div>
	</div>
	<?=nodetokens_replacer('[mk:map-sclad]');?>
	<div class="regions-of-postavkin">
		<div class="subtitle">Регионы поставок</div>
		<div class="descr">Доставляем продукцию во все области Центрального Федерального округа и районы Крайнего Севера:
			<div class="subdescr">Воронежскую, Белгородскую, Тульскую, Владимирскую, Тверскую, Ярославскую, Брянскую, Липецкую, Рязанскую, Курскую, Тамбовскую, Ивановскую, Калужскую, Смоленскую, Орловскую, Костромскую и Ямало-Ненецкий автономный округ.</div>
		</div>
		<span class="mailed-to-uns" data-show-node-in-popup='1577'>Написать нам</span>
	</div>
</div>