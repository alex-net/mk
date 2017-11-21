(function($){
	Drupal.behaviors['discount-time']={
		attach:function(c,s){
			$('.discont-couner').once(function(){
				dt=$(this).data('counter');
				if (!dt){
					$(this).remove();
					return;
				}

				//dt=0;
				ts={timestamp:dt};
				$(this).countdown(ts);
			});
		}
	}
})(jQuery)