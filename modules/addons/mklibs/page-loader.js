(function($){
	Drupal.behaviors['content-loder']={
		attach:function(c,s){
			// кнопка подгрузки товара 
			$('.load-more-contents input').once(function(){
				// вешаем обработчик на кнопку .. 
				$(this).on('click',function(){
					var data=Drupal.settings.pageloader.data;
					data['exists']=$(this).parents('.load-more-contents').eq(0).siblings('.node-product-display.node-teaser').length;
					
					var ajax=new Drupal.ajax(false,false,{
						url:Drupal.settings.pageloader.loadfrom,
						submit:data
					});
					ajax.eventResponse(ajax);
				});

								///вставить подгруженный контент в конец списка .. 
				Drupal.ajax.prototype.commands['get-next-content-elements']=(a,r,s) => {
					var data=Drupal.settings.pageloader.data;
					// если есть ноды ..  надо показать 
					if (r.nids){
						$(this).parent().before(r.nids);
						
						// работаем с пагинатором ..
						var p=$('ul.pager li.pager-current:last').next();
						if (p.hasClass('pager-item')){
							p.html(p.find('a').html());
							p.addClass('pager-current').removeClass('pager-item');
							if (!p.next().hasClass('pager-item')){
								p=p.next();
								do{
									var p1=p.next();
									if (p.hasClass('pager-current'))
										break;
									p.remove();
									p=p1;
								}while(p.length);
							}
						}
						
						Drupal.attachBehaviors($(this).parents('.load-more-contents').eq(0).parent());
					}
					/// всё закончилось .
					co=data.perpage*data.curpage+$(this).parents('.load-more-contents').eq(0).siblings('.node-product-display.node-teaser').length;

					if ( co==data.total*1 )
						$(this).remove();
				};
			});
		}
	};
	
})(jQuery);