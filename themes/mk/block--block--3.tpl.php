<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block block-<?php print $block->module ?>">
<?php // let's get the parent term title for the child term we are visiting
$parent_title = array_reverse(taxonomy_get_parents_all(arg(2)));
if($parent_title) {
$block->subject = $parent_title{0}->name;
}
?>
<?php if ($block->subject): ?><h2><?php print $block->subject ?></h2><?php endif;?>
<div class="content">
<?php print $block->content; ?>
</div>
</div>