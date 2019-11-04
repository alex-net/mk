;(function($){

	/**
	 * темизация элемента подкаталога (главная страница каталога) 
	 */
	Drupal.theme.prototype.front_catalog_sub_elements=function(items)
	{
		var container=$();
		for(var k in items){
			var el=$('<a>');
			el.attr('href',items[k].href);
			el.addClass('s-item');
			el.append('<span class="name">'+items[k].name+'</span>');
			if (items[k].childs){
				el.find('span.name').wrap('<span class="menu-wrap"/>');
				for(var i in items[k]['childs-list']){
					var subel=$('<span class="subel" />');
					subel.data('link',items[k]['childs-list'][i].url);
					subel.append(items[k]['childs-list'][i].name);
					subel.on('click',function(e){
						e.preventDefault();
						location.href=$(this).data('link');
						//console.log();
						
						//return false;

					});
					el.find('span.menu-wrap').append(subel);
				}
			}

			el.css({'background-image':'url('+items[k].img+')'});
			el.data('id',items[k].id);
			container=container.add(el);
		}
		return container;
	}

	/**
	 * заполнение пунктами  каталога всплывающих окон (popup меню каталога
	 */
	Drupal.theme.prototype.catalogs_popup_fill=function()
	{
		var catmenu=$('.footer .catalog-tail ul').html();
		$('.catalog-menu-popup').html('<ul>'+catmenu+'</ul>');
		$('.catalog-menu-popup').find('a').addClass('first-level');
	}

	/**
	 * заполнение подэлементов каталога (всплывающее меню каталога ) 
	 */
	Drupal.theme.prototype.catalogs_sublevel_popup_fill=function(data)
	{
		//console.log(data,'data is ');
		var list=$();
		//console.log(data);
		for(var i in data){
			var a=$('<a>');
			a.addClass('mover');
			a.attr('href',data[i].href);
			a.html('<span>'+data[i].name+'</span>');
			// обёртка вокруг ... ссылки ... 
			var wrap=$('<div>');
			wrap.addClass('link-wrapper');

			wrap.append(a);
			wrap.on('click',function(e){
				e.stopPropagation();
				if ($(this).hasClass('has-child') && !$(this).hasClass('opened')){
					$(this).parent().find('.opened').removeClass('opened');
					$(this).addClass('opened');
					e.preventDefault();
				}
			});
			if (data[i].childs){
				wrap.addClass('has-child');
				var sublevel=$('<div class="sublevel-2"/>');
				for(var k in data[i]['childs-list']){
					var link=$('<a>');
					link.attr('href',data[i]['childs-list'][k].url);
					link.text(data[i]['childs-list'][k].name);
					sublevel.append(link);
				}
				wrap.append(sublevel);
			}

			list=list.add(wrap);

		}
		//console.log(list);
		return list;
	}
})(jQuery);