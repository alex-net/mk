<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in html.tpl.php and page.tpl.php.
 * Some may be blank but they are provided for consistency.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 *
 * @ingroup themeable
 */
?>
<!DOCTYPE html >
<html >

<head>
  <title><?php print $head_title; ?></title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php //print $scripts; ?>
</head>
<body class="<?php print $classes; ?>">
  <div id="page">
    
    <div class="message">
      <img class='logo' src="/<?=$directory;?>/logo.png"/>
      Сайт находится в процессе обновления. Приносим свои извинения за неудобства. <br/>Мы постараемся как можно быстрее снова быть с вами
      <img class="smile" src="/<?=$directory;?>/imgs/smile.png">
    </div>
  </div>

</body>
</html>
