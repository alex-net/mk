(function($){
	Drupal.behaviors['comment-control']={
		attach:function(c,s){
			$('.comment-list-pager').once(function(){
				var mkcc=Drupal.settings.mkcc;
				$(this).find('.next-comment-butt').on('click',function(e){
					
					mkcc.cps.push(mkcc.cps[mkcc.cps.length-1]+1);
					var ajax=new Drupal.ajax(false,false,{
						url:'/get-comments-list',
						submit:{mkcc:mkcc},
					});
					ajax.eventResponse(ajax);
				});
				$(this).find('.item-list li a').on('click',function(e){
					e.preventDefault();
					search=$(this)[0].search.substr(1).split('&');
					params={};
					for(i=0;i<search.length;i++){
						p=search[i].split('=');
						params[p[0]]=typeof(p[1])=='undefined'?true:p[1];
					}
					mkcc.cps=typeof params['page']!='undefined'?[params['page']]:[0];


					var ajax=new Drupal.ajax(false,false,{
						url:'/get-comments-list',
						submit:{mkcc:mkcc},
					});
					ajax.eventResponse(ajax);

				});
			});
		}
	}
})(jQuery)