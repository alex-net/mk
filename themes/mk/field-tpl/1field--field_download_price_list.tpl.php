<?php foreach ($items as $delta => $item): ?> 
	<a href="/sites/default/files/price-lists/<?php print render($item['#items'][0]['filename']); ?>">Скачать прайс-лист</a>
<?php endforeach; ?>