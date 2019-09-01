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
		for(var i in data){
			var a=$('<a>');
			a.addClass('mover');
			a.attr('href',data[i].href);
			a.text(data[i].name);
			list=list.add(a);
		}
		//console.log(list);
		return list;
	}
})(jQuery);