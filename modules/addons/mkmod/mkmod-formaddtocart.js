(function($){
	Drupal.behaviors.detectnewprice={
		attach:function(c,s){
			$('.mk-form-add-to-cart input[name="qty"]').once(function(){
				$(this).on('keyup',function(){
					val=$(this).val();
					var put=$(this).parents('.qty-wrapp').find('.real-cost');
					if (val.match(/\D+/)){
						put.html('Ошибка!');
						return;
					}
					val=parseInt(val);
					var data=$(this).parents('form').find('input[name="form_id"]').val();
					data=Drupal.settings.qtdata[data];

					//console.log(data);
					for(i=0;i<data.length;i++)
						if ((typeof data[i]['from'] !='undefined' && parseInt(data[i]['from'])<=val || typeof data[i]['from'] =='undefined' ) && 
							(typeof data[i]['to'] !='undefined' && parseInt(data[i]['to'])>=val || typeof data[i]['to'] =='undefined' ) 
							) {
								t=Math.round(parseFloat(data[i]['commerce_price'])*val*100)/100;
								if (t-Math.round(t)==0)
									t+='.0';
								put.html('Итого: <span>'+(t)+' руб</span>');
						}
							//console.log(data[i]);
					if (isNaN(val))
						put.html('Ошибка!');
					//console.log(val);

				}).trigger('keyup');
				//
			});
		}
	}
})(jQuery)