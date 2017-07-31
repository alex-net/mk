<div class="<?php print $classes; ?> news_articles">
  <div class="col-xs-36 pager_for top">
    <div class="row">
      <div class="per_page hidden-xs col-sm-18 col-md-18 col-lg-18"><?php print $exposed; ?></div>
      <div class="pages col-sm-18 col-md-18 col-lg-18 text-right"><?php print $pager; ?></div>
    </div>
  </div>
  <?php if ($rows): ?>
    <div class="view-content">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>
  <div class="col-xs-36 pager_for bottom">
    <div class="row">
      <div class="per_page hidden-xs col-sm-18 col-md-18 col-lg-18"><?php print $exposed; ?></div>
      <div class="pages col-sm-18 col-md-18 col-lg-18 text-right"><?php print $pager; ?></div>
    </div>
  </div>
</div>