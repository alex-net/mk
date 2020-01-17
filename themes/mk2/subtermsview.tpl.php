<?php if ($list): ?>
	<div >
		<?php foreach ($list as $term): ?>
			<div class="col<?=$term->children?' has-children':'';?>">

				<?php 
					$img = field_view_field('taxonomy_term', $term, 'field_pic_category', 'token'); 
					$im=field_get_items('taxonomy_term', $term, 'field_pic_category');
					$opt=[
						'attributes'=>[
							'class'=>['image-link'],
						],
					];
					if (!empty($im[0]['uri']))
						$opt['attributes']['style']='background-image:url('.file_create_url($im[0]['uri']).')';

					if ($term->children)
						$opt['attributes']['class'][]='has-children';

					echo l('','taxonomy/term/'.$term->tid,$opt);
					//kprint_r(file_create_url($im[0]['uri']));
					//$img[0]['#path']=['path'=>'taxonomy/term/'.$term->tid];
					//echo render($img);
				?>
				<div class="title">
					<?php echo l($term->name,'taxonomy/term/'.$term->tid);  ?>
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
								
			</div>
		<?php endforeach; ?>
	</div>
<?php endif;?>
