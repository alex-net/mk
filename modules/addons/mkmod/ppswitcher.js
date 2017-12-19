(function($){
	Drupal.behaviors.ppswitcher={
		attach:function(c,s){
			$('.per-page-sizer').once(function(){
				$(this).find('a').on('click',function(e){
					e.preventDefault();
					$.cookie('pp-size',parseInt(e.target.hash.substr(1)));

					location.reload();
				});
			})
		}
	}
	
})(jQuery);