(function($){
	Drupal.behaviors.jqac={
		attach:function(c,s){
			$('input.autocompleter-todo').once(function(){
				///console.log($(this));
				limit=$(this).data('countel');
				if (typeof limit =='undefined')
					limit=10;
				console.log();
				$(this).autocompleter({
					source:'/getsearchvitrs',
					cache:false,
					limit:limit
				});
			});
		}
	}
})(jQuery);