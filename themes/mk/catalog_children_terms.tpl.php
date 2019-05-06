<?php if ($data): ?>
    <div class="clearfix">
        <?php foreach ($data as $term): ?>
            <div class="col-xs-18 col-sm-12 col-md-9 col-lg-9 col">
                <div class="row">
                    <div class="block_row">
                        <div class="wrap-title">
                            <?php if (empty($term->children)) {
                                $path_term = drupal_get_path_alias('taxonomy/term/' . $term->tid);
                                echo "<a href='" .$path_term. "'>";
                            } ?>
                            <div class="title">
                                <span><?php echo l($term->name,'taxonomy/term/'.$term->tid);  ?></span>
                                <?php if ($term->children): ?>
                                    <div class="has-children"></div>
                                <?php endif;?>
                            </div>
                                        
                            <?php if ($term->children): ?>
                                <div class="wrap-children">
                                    <div class="children">
                                        <ul>
                                            <?php foreach ($term->children as $child): ?>
                                                <li><?php print l($child->name, 'taxonomy/term/'.$child->tid); ?></li>
                                            <?php endforeach; ?>
                                        </ul>
                                    </div>
                                </div>
                            <?php endif;?>
                                        
                            <?php $img =field_view_field('taxonomy_term', $term, 'field_pic_category', 'token'); 
                            $img=image_style_url($img[0]['#image_style'],$img[0]['#item']['uri']);
                            //$img=field_get_items('taxonomy_term', $term, 'field_pic_category');
                            //dsm($img);
                            ?>
                            <a class='bg-image' href="<?=url('taxonomy/term/'.$term->tid);?>" style="background-image:url(<?=$img;?>);"></a>
                            <?php //print l(render($img),'taxonomy/term/'.$term->tid,['html'=>true]); ?>
                          
                        </div>
                    </div>
                </div>
            </div>
        <?php endforeach; ?>
    </div>
<?php endif;?>
