(function($){
	Drupal.behaviors['taxonomy- content-uploder']={
		attach:function(c,s){
			$('.container-term-wrapp-autoload').once(function(){
				var w=$(this);
				w.data('sended',false);
				var sendet=false;
	
				//console.log(w.offset().top);
				$(window).on('scroll resize',function(){
					var h=w.offset().top+w.height();
					if ($(this).scrollTop()+$(this).height()>h && !w.data('sended')){
						
						w.data('sended',true);
						var data=w.data();
						data['exists']=w.children('.product.teaser').length;
						var ajax=new Drupal.ajax(false,false,{
							url:'/get-next-content-elements',
							submit:data
						});
						ajax.eventResponse(ajax);
						//console.log(data);
						
					}
						
				});
			});

		}
	};
	
})(jQuery);