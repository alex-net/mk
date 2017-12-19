(function($){
	Drupal.ajax.prototype.commands.uptotsivstatus=function(a,r,s){
		el='.';
		for (c in a.element.classList)
			if (parseInt(c)!=NaN && typeof a.element.classList[c]=='string' &&  a.element.classList[c].match(/^record-/i))
				el+=a.element.classList[c];

			console.log(el);
		if ($(el).size()){// элемент есть .. 
			$(el).text(r.text);
			$(el).parents('.otsiv-item').toggleClass('unpublic, public');
		}
	}
})(jQuery);