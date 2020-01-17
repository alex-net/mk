(function($){

	Drupal.behaviors['tovar-filter-form-']={
		attach:function(c){
			$('.ranger-placer',c).once(function(){
				//var inputs=$('.text-fields-wrap input');
				var slider=this;
				var format=function(val){return Math.round(val);}
				//console.log({'min':inputs.eq(0).val()-0,'max':inputs.eq(1).val()-0});
				noUiSlider.create(slider,{
					start:Drupal.settings.sliderdata.rangsmal,
					step:1,
					connect:true,
					range:{'min':Drupal.settings.sliderdata.rangbig[0],'max':Drupal.settings.sliderdata.rangbig[1]},
					format:{
						to:format,
						from:format,
					},
				});
				var funcevent=function(range){
					var rootel=$(this.target);
					//console.log($(this.target).attr('class'));
					$('.text-fields-wrap input').each(function(ind){
						$(this).val(range[ind]);//.trigger('change');
					});
				};
				this.noUiSlider.on('update',funcevent);
				this.noUiSlider.on('change',funcevent);
				// пинаем всплывашку при изменениях вдиапазона цен ..
				this.noUiSlider.on('change',function(e){
					$(this.target).parents().filter('.form-item').last().trigger('apply-popup-show')
				});
				
				$('.text-fields-wrap input').on('change',function(){
					var input=this.name.match(/\[(from|to)\]/i);

					if (input.length!=2)
						return;
					var range=input[1]=='from'?[this.value-0,null]:[null,this.value-0];
					slider.noUiSlider.set(range);
					//console.log(input[]);
				})
				
			});
			//console.log(c);
		}
	}


})(jQuery)
