;(function($){
	Drupal.behaviors.siteEvents={
		attach:function(c,s){
			// должен навешиваться один раз 
			$('body').once(function(){

				// показываем и скрываем менюхи .. 
				var buttons=$('.site-hmenu .wrap li.item-catalog, .footer .menu-line .wrap .item-catalog, .site-hmenu .wrap .catalog-of-produucts-button');

				$(this).on({
					// подгрузка элементов каталога .. 
					'catallog-subitem-elements-load':function(e,tid)
					{
						// элемент не открывался ни разу .. надо открыть 
						var ajax=new Drupal.ajax(false,false,{
							url:'/catalog-get-sub-ajax',
							submit:{
								id:tid,
							}
						});
						ajax.eventResponse(ajax);
					},
					//  клик по пустому месту  .. закрыть все попапы ..
					click:function(e)
					{
						$(this).trigger('close-all-popups');
					},

					// перехватываем загрузку контента для элемента  для подкаталога во всплывающем меню 
					'catallog-subitem-elements-is-loaded':function(e,ptid,items)
					{
						var el;

						// проверяем наличие коасса инициатора .. 
						el=$('.catalog-menu-popup ul li.item.for-'+ptid);
						var c=$('<div class="sublevel"/>');
						// пихаем данные в элемент ... 
						c.append(Drupal.theme('catalogs_sublevel_popup_fill',items));
						el.append(c);
						el.data('loaded',true);
						// выбираем менюшку инициатор 
						el=el.filter('.loadable');
						if(el.length){
							
							el.removeClass('loadable');
							el.trigger('open-close-sub-els');
						}



						// шерстим по странице 
						el=$('.front .catalog-list .subitems.for-'+ptid);
						el.html(Drupal.theme('front_catalog_sub_elements',items));
						el.prev().data('loaded',true);// помечаем что элемент загружен

						// // заполнение подгруженными элементами ..	
						if (el.prev().hasClass('loadable')){
							el.prev().trigger('open-close-sub-els');	
							el.prev().removeClass('loadable');
						}
					},

					// закрыть все открытые попап меню
					'close-all-opened-popup-menu' :function(){
						buttons.each(function(){
							// пробуем закрыть меню шапки ..
							if ($('.site-hmenu .wrap ul.menu').hasClass('vis'))
								$('.site-hmenu .wrap ul.menu').removeClass('vis');
							// меню закрыто .. идём дальше .. 
							if (!$(this).hasClass('hovered'))
								return ;
							
							$(this).removeClass('hovered');
							var wrap=$(this).parents('.wrap').eq(0);
							if (wrap.hasClass('show-catalog')){
								// закрываем все открытые подуровни ..
								wrap.find('.opened').removeClass('opened');
								wrap.removeClass('show-catalog');
							}
						});
					},
					
					/**
					 * сработала вставка контента из списка нод .. 
					 */
					'place-nodes-list':function(e,apply,placeto){
						// sliked-carousel
						if (apply){
							if (placeto.match(/tovar-analogs|mit-tovar-buy|old-viewed-products/))
								$(placeto).addClass('sliked-carousel');
							// блок акций . в каталоге .. 
							var slikedCarousel=['.product-akcions-list.elements-list.products','.hits-prods-list.elements-list.products','.zakaz-prods-list.elements-list.products'];
							if (slikedCarousel.indexOf(placeto)!=-1)
							//if (placeto=='.product-akcions-list.elements-list.products' /*&& $(placeto).children().length>3*/)
								$(placeto).slick({
									nextArrow:'<span class="next-product"><i class="fas fa-chevron-right"></i></span>',
									prevArrow:'<span class="prev-product"><i class="fas fa-chevron-left"></i></span>',
									dots:true,//parseInt($(this).data('dots'))>0,
									slidesToShow:3,
									slidesToScroll:3,
									responsive:[
										//{breakpoint:1200,settings:{slidesToShow:3,slidesToScroll:3}},
										{breakpoint:1100,settings:{slidesToShow:2,slidesToScroll:2}},
										{breakpoint:760,settings:{slidesToShow:1,slidesToScroll:1}}
									],
								});
							
						}
							
					},

				});
			});
		}
	};
})(jQuery);