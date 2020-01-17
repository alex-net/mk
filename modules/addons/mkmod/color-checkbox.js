(function($){

	Drupal.behaviors['color-checkbox']={
		attach:function(c,r,s){
			$(window).on('form-styler-applyed',function(){
				$('.colored-checkboxes .form-type-checkbox').once(function(){

					$(this).find('span[data-color]').each(function(){
						var color=$(this).data('color');
						var root=$(this).parent().parent();
						if (color.substr(1).toLowerCase()=='ffffff')
							root.find('div.colored-checkboxes').addClass('white-color');
						//console.log(color.substr(1).toLowerCase());
						
						root.find('div.colored-checkboxes').css('background-color',color);
						// http://dev.masterkrowli.ru/bitumnaya-gidroizolyaciya
						root.find('label').hide();
					});
				});
			});
			
		},
	};

})(jQuery);