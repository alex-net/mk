(function($){
	Drupal.behaviors.detectnewprice={
		attach:function(c,s){
			$('.mk-form-add-to-cart input[name="qty"]').once(function(){
				// источник данных 
				var sourcedatael=$(this);
				// элемент обёртки 
				var wrap=$(this).parents('.qty-wrapp').eq(0);
				// элемент вывода .. 
				var put=wrap.find('.real-cost');
				// рулим кооличеством через кнопки 
				wrap.find('.arrow').on('click',function(){
					var val=sourcedatael.val();
					if (val.match(/\D+/))
						return ;
					val=parseInt(val);
					if ($(this).hasClass('right-btn'))
						val++;
					if ($(this).hasClass('left-btn'))
						val--;
					if (val<1)
						return ;
					sourcedatael.val(val).trigger('keyup');
				});
				// отслеживание ввода текста в input
				$(this).on('keyup',function(){
					val=$(this).val();
					
					if (val.match(/\D+/)){
						put.html('Ошибка!');
						return;
					}
					val=parseInt(val);
					var data=$(this).parents('form').find('input[name="form_id"]').val();
					data=Drupal.settings.qtdata[data];

					var valset=false;// была ли пересчитана   новое значение цены в поле ...
					for(i=0;i<data.length;i++)
						if ((typeof data[i]['from'] !='undefined' && parseInt(data[i]['from'])<=val || typeof data[i]['from'] =='undefined' ) && 
							(typeof data[i]['to'] !='undefined' && parseInt(data[i]['to'])>=val || typeof data[i]['to'] =='undefined' ) 
							) {
								t=Math.round(parseFloat(data[i]['commerce_price'])*val*100)/100;
								if (t-Math.round(t)==0)
									t+='.0';
								t+=' руб';
								if (typeof data[i].unit!='undefined')
									t+='/'+data[i].unit;
								put.html('Цена: <span>'+(t)+'</span>');
								valset=true;
						}
							//console.log(data[i]);
					if (isNaN(val)|| !valset)
						put.html('Ошибка!');
					//console.log(val);

				}).trigger('keyup');
				//
			});
		}
	}
})(jQuery)