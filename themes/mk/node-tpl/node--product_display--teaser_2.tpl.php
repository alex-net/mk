<?php print render($content['field_pic_product']);?>
<h3><a href="<?php print render($content['field_product_category'][0]['#href']);?>#product_<?php print $node->nid; ?>"><?php print $title; ?></a></h3>
<div class="price"></div>
<div class="buy"><a href="<?php print render($content['field_product_category'][0]['#href']);?>#product_<?php print $node->nid; ?>">Купить</a></div>