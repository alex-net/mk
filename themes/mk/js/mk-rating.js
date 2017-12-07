(function($){
	// обрабатывается select На основе него строится рейтинг ... если элемент не является селектом но является контейнером вроде div .. то отрисовывается вывод 
	$.fn.mkrating=function(){
		return this.once(function(){
			select=$(this);
			select.wrapAll('<div class="mk-rating-widget"/>');
			select.hide();
			el=$('<span class="rating-wrapp"/>');
			select.find('option').each(function(){
				if ('_none'==$(this).val())
					return;
				it=$('<span class="one-star"><span class="star-ico"></span>'+$(this).html()+'</span>');
				it.data({it:$(this).val(),el:it});
				el.append(it);
			});
			select.on('change',function(){
				var val=$(this).val();
				var ind=-1;
				$(this).find('option').each(function(i){
					if ($(this).attr('value')==val)
						ind=i;
					
				});
				$(this).data('changed-val',ind);
				if (ind!=-1){
					el.find('.one-star').removeClass('hovered');
					for(i=0;i<=ind;i++)
						el.find('.one-star').eq(i).addClass('hovered');
				}
				
			});
			el.find('.one-star').hover(function(e){
				el.find('.one-star').removeClass('hovered');
				for(var i=0;i<=$(e.target).index();i++)
					el.find('.one-star').eq(i).addClass('hovered');
			},function(e){
				val=select.val();
				el.find('.one-star').removeClass('hovered');
				console.log(select[0].selectedIndex,select.data('changed-val'));
				for(var i=0;i<=select.data('changed-val');i++)
					el.find('.one-star').eq(i).addClass('hovered');
			}).on('click',function(){
				
				select.val($(this).data('it')).trigger('change');
				
				
			});
			select.after(el);
		});

	}
})(jQuery)