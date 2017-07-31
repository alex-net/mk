<div id="node-<?php print $node->nid; ?>" class="col-lg-36 <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print $user_picture; ?>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <?php if (drupal_is_front_page()) { ?>
      <h1><?php print $title; ?></h1>
    <?php } else {?>
      <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php }; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>
  <?php if (!drupal_is_front_page()) { ?>
    <?php print render($content['links']); ?>
  <?php }; ?>

  <?php print render($content['comments']); ?>

</div>