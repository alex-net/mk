(function($){
	// обрабатывается select На основе него строится рейтинг ... если элемент не является селектом но является контейнером вроде div .. то отрисовывается вывод 
	$.fn.mkrating=function(){
		return this.once(function(){
			select=$(this);
			select.wrapAll('<div class="mk-rating-widget"/>');
			select.hide();
			el=$('<span class="rating-wrapp"/>');
			var selectedDeteced=select.find('option[selected]').length;
			console.log(selectedDeteced);
			select.find('option').each(function(ind){
				it=$('<span class="one-star"><span class="star-ico"></span>'+$(this).html()+'</span>');
				it.data({it:$(this).val(),el:it});

				if (selectedDeteced )
					it.addClass('hovered');
				if (typeof $(this).attr('selected')!='undefined'){
					selectedDeteced=0;
					select.data('changed-val',ind);
				}
				//	it.addClass()
				
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
				for(var i=0;i<=select.data('changed-val');i++)
					el.find('.one-star').eq(i).addClass('hovered');
			}).on('click',function(){
				select.val($(this).data('it')).trigger('change');
				
			});
			select.after(el);
		});

	}
})(jQuery)