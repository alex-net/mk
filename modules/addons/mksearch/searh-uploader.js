(function($){
	// подгрузка товаа 
	
	Drupal.behaviors['searh-uploader']={
		attach:function(c,s){
			var el=$('.product-placer .product-more');

			el.once(function(){
				$(window).on('scroll resize',function(){
					var pos=el.offset().top;
		
					var s_top=$(window).scrollTop();
					var h=$(window).height();
					var vis=(s_top+h-pos)>0;

					eldata=el.data();
					//console.log(vis,eldata);
					if (vis && (typeof eldata['ended']=='undefined' || !eldata['ended'])){
						el.data('ended',true);
						var pp=typeof eldata['perpage'] == 'undefined'?8:eldata['perpage'];
						var cp=typeof eldata['currentpage'] == 'undefined'?0:eldata['currentpage'];
						console.log('as');
						var ajax=new Drupal.ajax(false,false,{
							url:'/get-next-page-search',
							submit:{
								ss:Drupal.settings['search-string'],
								cp:cp, // текущая страница 
								pp:pp // число записей на страницу 
							}
						});
						ajax.eventResponse(ajax);

					}

				});


			});
			console.log('dsa');
		}
	}

	Drupal.ajax.prototype.commands['update-prod-list']=function(a,r,s){
		if (r.content)
			$('.product-placer .product-list').append(r.content);
		Drupal.attachBehaviors($('.product-placer .product-list'));

		if (r.loaded==r.pp)// загружен полный объём
			$('.product-placer .product-more').data({'ended':false,'currentpage':r.cp});
		console.log(r);
	}
})(jQuery);