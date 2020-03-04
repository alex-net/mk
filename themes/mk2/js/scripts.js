;(function($){
	Drupal.behaviors.siteThemeInit={
		attach:function(c,s){
			// работаем с меню 
			$('.site-hmenu').once(function(){
				var menu=$(this);
				// скрыть показать поиск .. в полной версии .. 
				menu.find('.search-but, .searchform .close-btn').on('click',function(){
					menu.toggleClass('search');
				});

				// показать скрыть менюшку .. в шапке .. (мобильная версия .. )
				menu.find('.mobile-block.mobile-menu-open').on('click',function(){
					// закрыть менб каталога 
					if (!$(this).siblings('ul.menu').hasClass('vis'))
						$('body').trigger('close-all-opened-popup-menu');
					$(this).siblings('ul.menu').toggleClass('vis');
				});
			});

			// работаем с каталогом на главной .. 
			$('.front .catalog-list').once(function(){
				// открыть закрыть субэлементы (событие на элементе .. ) )
				$(this).find('.item').on('open-close-sub-els',function(){
					var isopened=$(this).hasClass('opened');
					// текущий элемент закрыт ..
					if (!isopened){
						// надо закрыть все остальные 
						$(this).siblings('.opened').toggleClass('opened');
						// проверка всплывашек . (закрываем все открыыте) 
						$('body').trigger('close-all-opened-popup-menu');
					}

					$(this).toggleClass('opened');
				});
				 
				// обработка кликов по кнопкам Развернуть Свернуить
				$(this).find('.item .btn-controls').on('click',function(){
					var el=$(this).parent();
					if (el.hasClass('empty')){
						location.href=el.data('href');
						return;
					}
					if (el.data('loaded')){
						el.trigger('open-close-sub-els');
						return;
					}
					// помечаем элемент который инициировал запрос..
					el.addClass('loadable');
					// маякуем о том что надо подгрузить  один из подсписков .. 
					$('body').trigger('catallog-subitem-elements-load',[el.data('id')]);
				});
			});

			// каруселька на главной страничке .. по товарам .. +  везде где есть класс sliked-carousel 
			$('#block-mkmod-top-sales .content, .sliked-carousel').once(function(){
				$(this).slick({
					nextArrow:'<span class="next-product"><i class="fas fa-angle-right"></i></span>',
					prevArrow:'<span class="prev-product"><i class="fas fa-angle-left"></i></span>',
					dots:parseInt($(this).data('dots'))>0,
					slidesToShow:3,
					slidesToScroll:3,
					responsive:[
						{breakpoint:1100,settings:{slidesToShow:2,slidesToScroll:2}},
						{breakpoint:760,settings:{slidesToShow:1,slidesToScroll:1}}
					],
				});
			});


			// каруселька в каталоге ...акции 
			$('.akcii-in-catalog-wrapper .elements-list').once(function(){
				$(this).slick({
					nextArrow:'<span class="next-product"><i class="fas fa-chevron-right"></i></span>',
					prevArrow:'<span class="prev-product"><i class="fas fa-chevron-left"></i></span>',
					dots:true,//parseInt($(this).data('dots'))>0,
					slidesToShow:3,
					slidesToScroll:3,
					responsive:[
						{breakpoint:1100,settings:{slidesToShow:2,slidesToScroll:2}},
						{breakpoint:760,settings:{slidesToShow:1,slidesToScroll:1}}
					],
				});
			});


			// слайдер акций на главной странице
			$('#block-mkmod-akcii-slider-big .content').once(function(){
				$(this).slick({
					nextArrow:'<span class="next-product"><i class="fas fa-angle-right"></i></span>',
					prevArrow:'<span class="prev-product"><i class="fas fa-angle-left"></i></span>',
					//dots:parseInt($(this).data('dots'))>0,
					slidesToShow:1,
					slidesToScroll:1,
					//autoplay: true,
  					autoplaySpeed: 7000,
					
				});
			});

			// карусель производителей . 
			$('.vendors-list > .content p, #block-block-12 .content > p').once(function(){
				$(this).slick({
					nextArrow:'<span class="next-product"><i class="fas fa-chevron-right"></i></span>',
					prevArrow:'<span class="prev-product"><i class="fas fa-chevron-left"></i></span>',
					dots:parseInt($(this).data('dots'))>0,
					slidesToShow:6,
					slidesToScroll:6,
					responsive:[
						{breakpoint:1024,settings:{slidesToShow:5,slidesToScroll:5}},
						{breakpoint:824,settings:{slidesToShow:4,slidesToScroll:4}},
						{breakpoint:624,settings:{slidesToShow:3,slidesToScroll:3}},
						{breakpoint:424,settings:{slidesToShow:2,slidesToScroll:2}},
						
					],
				});


			});
			// по статьям .. 
			$('#block-mkmod-articles-list > .content').once(function(){
				$(this).slick({
					//nextArrow:'<span class="next-product"><i class="fas fa-angle-right"></i></span>',
					//prevArrow:'<span class="prev-product"><i class="fas fa-angle-left"></i></span>',
					dots:true,
					arrows:false,
					slidesToScroll:4,
					slidesToShow:4,
					adaptiveHeight:true,
					responsive:[
						{breakpoint:1000,settings:{slidesToShow:3,slidesToScroll:3}},
						{breakpoint:650,settings:{slidesToShow:2,slidesToScroll:2}},
						{breakpoint:450,settings:{slidesToShow:1,slidesToScroll:1,dots:false}},
						//{breakpoint:760,settings:{slidesToShow:1}}
					],
				});
			});

			// однократная инициализациия .. срабатывает один раз после загрузки .. 
			$('body').once(function(){
				// заполнение попапа каталога .  элементами ...
				Drupal.theme.prototype.catalogs_popup_fill();
				// close-all-popups // надо закрыть меню...
				// блокируем спуск клика к body
				$('.catalog-menu-popup').on('click',function(e){e.stopPropagation();});
				// закрыть переход в корневые разделы .. 
				$('.catalog-menu-popup').find('ul li  a.first-level').on('click',function(e){
					var li =$(this).parent();
					if (!li.hasClass('opened') && !li.hasClass('empty'))
						e.preventDefault();
				});
				// пробуем обработать клики по корневым .. подгрузить элементы .. 
				$('.catalog-menu-popup').find('ul li').on({
					'open-close-sub-els':function(e){
						$(this).parent().find('.opened').removeClass('opened');
						$(this).addClass('opened');
					},
					click(e){
						// корневые элементы подгружены = просто  показываем 
						if ($(this).data('loaded')){
							$(this).trigger('open-close-sub-els');
							return ;
						}
						// пометить элемент .. как инициатор загрузки 
						$(this).addClass('loadable');
						// если ничего не загружено - надо загрузить
						$('body').trigger('catallog-subitem-elements-load',[$(this).data('tid')]);
					},
				});

				// показываем и скрываем менюхи .. 
				var buttons=$('.site-hmenu .wrap li.item-catalog, .footer .menu-line .wrap .item-catalog, .site-hmenu .wrap .catalog-of-produucts-button');

				buttons.on('click',function(){
					var cbut= $(this);
					var wrap=$(this).parents('.wrap').eq(0);
					// проверяем .. было ли открыто меню ...
					if (!wrap.hasClass('show-catalog')) {// меню закрыто  ..= надо проверить есть ли открытые меню ... и их закрыть 
						// проверка всплывашек . (закрываем все открыыте) 
						$('body').trigger('close-all-opened-popup-menu');
						// проверка каталога на главной ..
						$('.front .catalog-list').find('.opened').removeClass('opened');
					}

					// засвечиваем меню ..
					wrap.toggleClass('show-catalog');
					// вешаем допкласс на кнопку 
					buttons.each(function(){
						if ($(this).parents('.wrap').eq(0).is(wrap))
							$(this).toggleClass('hovered');
					});


					if (!wrap.hasClass('show-catalog')) // меню уже  закрыто  ..= сворачиваем подпункты 
						wrap.find('.opened').removeClass('opened');
					



				});

				// добавляем звёзды на заголоовк товара . .+ артикул (если есть ..) 
				if ($('body.page-node.node-type-product-display').length){
					$('.content-wrapper  h1').wrapInner('<span class="title"/>');
					$('.content-wrapper  h1').append('<span class="p-rating" ><span style="width:'+Drupal.settings.productstars+'%"></span></span>');
					if (typeof Drupal.settings.productsku != 'undefined')
						$('.content-wrapper  h1').append('<span class="prod-sku">Артикул: '+Drupal.settings.productsku+'</span>');
				}

				// работаем с кнопками всплывашек ...  
				// тыкнули на продолжить покупки .. 
				$('body').on('click','.fancybox-inner .continue-btn',function(){
					$.fancybox.close();
				});

				// подгружаем .. контент в списки товаров в карточке .. 
				$('.node-product-display.node-full .ajax-loadable').each(function(){
					var key=$(this).data('key');
					var data=Drupal.settings[key];
					var ajax=new Drupal.ajax(false,false,{
						url:'/get-nodes-list',
						submit:{
							nids:data.nids,
							mode:'teaser',
							selector:data.to,
						}
					});
					ajax.eventResponse(ajax);
				});

				$('#block-mkmod-sub-terms .content .col.has-children').find('.title > a').on('click',function(e){
					if (!$(this).parents('.col').eq(0).hasClass('opened')){
						$(this).parents('.col').eq(0).addClass('opened');
						e.preventDefault();
					}
				});
				
				$(function(){
					// прокрутка на странице каталога в стучае перехода на вторую и последующие страницы 
					if ($('div.elements-list.products').length>0 && Drupal.settings['calaog-scroller']){
						var p=$('div.elements-list.products').position().top;
						if (p>window.scrollY)
							$('body,html').animate({scrollTop:p},500);
					}
				});
				

			});

			// управляем анимацией появлением скроллера
			$('.page-scroller').once(function(){
				var el=$(this);
				el.on('click',function(){
					$('body,html').animate({scrollTop:0},300);
				});
				$(window).on('scroll init',function(){
					var docH=$('body').height();
					if (window.scrollY>docH*0.15 && window.scrollY>100)
						el.addClass('vis');
					else 
						el.removeClass('vis');
					//console.log('sY',window.scrollY,);
				}).trigger('init');

			});

			// инициализация дисконтного счётчика.. 
			$('.discont-time').once(function(){
				var dt=new Date($(this).data('discont'));
				$(this).countdown({timestamp:dt});
			});
				
			// клацаем по табам . в товаре .
			$('.tabs-of-tovar').once(function(){
				var root=$(this);
				$(this).find('.tabs-line > div').on('click',function(){
					if ($(this).hasClass('active'))
						return;
					$(this).siblings('.active').removeClass('active');
					root.find('.tabs-content > .active').removeClass('active');
					root.find('.tabs-content > div.'+$(this).attr('class')).addClass('active');
					$(this).addClass('active');
				});
			});
			// показыываем и скрываем  информацию о товаре (поле параметры в списке товаров) 
			$('.node-teaser .morebtn').once(function(){
				$(this).on('click',function(){
					$(this).parents('.node-product-display').toggleClass('morebtn');
				});
			});
			
			//  инициализация  звёздочек в форме Оставить отзыв о компании .. 
			$('.webform-component--reyting, .field-name-field-rating').once(function(){
				$(this).find('select').mkrating();
			});
			

			//  открыть закрыть меню  .. фильтров .. и вообще фильтры ..
			$('#block-hitrolinks-menu-hl-block h2, form.form-of-filters .form-type-checkboxes > label, form.form-of-filters fieldset > legend').on('click',function(){
				$(this).parent().toggleClass('closed');
			});
			$('#block-hitrolinks-menu-hl-block .content > ul > li ').on('click', function(){
				if (!$(this).find('ul').length)
					return true;
				var op=$(this).hasClass('opened');
				$(this).toggleClass('opened');
				$(this).find('.ptaha').toggleClass('opened');
				return op;
			});
			/// показать ещё  скрытые элементы списка ...
			$('#block-hitrolinks-menu-hl-block .show-more-elements').on('click',function(){
				$(this).prev().find('.el-invis').removeClass('el-invis');
				$(this).remove();

			});
			if (typeof $.fn.styler!='undefined')
				$('form.form-of-filters .form-type-checkboxes input').styler({
					onFormStyled:function(){
						$(this).trigger('form-styler-applyed');
						
					},
				});

			// пробуем поймать клики по form-item у формы ... фильтра ..  и порулить всплывашкой .. 
			$('form.form-of-filters').on('change','.form-item input',function(){
				$(this).parents().filter('.form-item').last().trigger('apply-popup-show');
			});
			// кнопка применить от формы фильтр .. 
			var btn=$('form.form-of-filters .popup-apply-button');
			// закрываем окно ...с кнопкой применить  
			btn.find('.close-btn').on('click',function(){
				btn.removeClass('vis');
			});

			$('form.form-of-filters > div > *').on('apply-popup-show',function(e){
				
				var newtop=$(this).position().top+$(this).height()/2;
				if (newtop,btn.position().top!=newtop){
					btn.removeClass('vis');
					btn.css('top',newtop);
				}
				if (!$(e.target).parents().find('.fancybox-opened').length)
					setTimeout(function(){
						btn.addClass('vis');
					},1000);
				
				//console.log(,btn);
			});

			// проставляем хитрый класс  если нашли форму фильтра ... на странице
			if ($('.region-filtrus').length){
				$('.content-wrapper.page').addClass('filter-exists');
				$('.btn-show-filter').on('click',function(){
					$.fancybox.open({
						content:$('.region-filtrus'),//$('.region-filtrus'),
						type:'inline',
						width:'100%',
						autoSize:false,
						wrapCSS:'filters-popup',
						afterShow:function(){
							//console.log(this,arguments,'ss');
						},
					});
				});
			}

		}
	};



	Drupal.behaviors['seo-hitro-links']={
		attach:function(c,s){
			$('.hitrolinks-wrapper').once(function(){
				$(this).find('.show-popup-links').on('click',function(){
					jQuery.fancybox({
						type:'inline',
						href:'.hitrolinks-wrapper .hl-win-wrapp',
						padding:0,
					});
				});
			});
		}
	}

})(jQuery);

