(function($){
	/**
	 * установить контент на страницу каталога 
	 */
	Drupal.ajax.prototype.commands['put-content-to-front-catalog-page']=function(a,r,s){
		if (typeof r.items !='object')
			return ;
		$('body').trigger('catallog-subitem-elements-is-loaded',[r.for,r.items]);

		//var el=$('.front .catalog-list .subitems.for-'+r.for);
		//el.html(Drupal.theme('front_catalog_sub_elements',r.items));
		//el.prev().trigger('open-close-sub-els');	
	}

})(jQuery)