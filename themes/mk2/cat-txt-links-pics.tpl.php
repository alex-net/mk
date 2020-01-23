<div class="block-elements-cat-links-imgs">
	<?php foreach($els as $el):?>
		<div class='b-element'>
			<?php if ($el['text']):?>
				<div class='body-block-elemnt'><?=$el['text'];?></div>
			<?php endif;?>
			<?php if (!empty($el['pics'])):?>
				<div class='list-imgs'>
					<?php foreach ($el['pics'] as $pic): ?>
						<div class="col">

							<?php 
								
								$opt=[
									'attributes'=>[
										'class'=>['image-link'],
									],
								];
								if (!empty($pic['pic']))
									$opt['attributes']['style']='background-image:url('.file_create_url($pic['pic']).')';

								

								echo l('',$pic['link'],$opt);
								//kprint_r(file_create_url($im[0]['uri']));
								//$img[0]['#path']=['path'=>'taxonomy/term/'.$term->tid];
								//echo render($img);
							?>

							<div class="title">
								<?php echo l($pic['title'],$pic['link']);  ?>
							</div>
										
							
											
						</div>
					<?php endforeach; ?>
				</div>

			<?php endif;?>
		</div>
	<?php endforeach;?>
</div>