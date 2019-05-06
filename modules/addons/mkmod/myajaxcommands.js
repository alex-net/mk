(function($){
	Drupal.behaviors.myajaxcommands={
		attach:function(c,s){
			// всплыть окном
			Drupal.ajax.prototype.commands.show_in_popup=function(a,r,s){
				delete r.command;
				r.afterShow=function(){
					Drupal.attachBehaviors(this.inner);
				}
				$.fancybox(r);
				
			}
			/// закрыть окно
			Drupal.ajax.prototype.commands.close_popup=function(a,r,s){
				$fancybox.close();
			}
			// обновить размеры окна 
			Drupal.ajax.prototype.commands.update_size_of_popup=function(a,r,s){
				$.fancybox.update();
				Drupal.attachBehaviors($.fancybox.inner);
			}
			// ткнуть юзера носом в поле ошибки .. 
			Drupal.ajax.prototype.commands.focustoerrorfield=function(a,r,s){
				$(':input.error').eq(0).focus();
			}
			// ресет формы 
			Drupal.ajax.prototype.commands['reset-form']=function(a,r,s){
			//	console.log($(':input',r.selector).not('[type=hidden]'));
				$(':input',r.selector).not('[type=hidden],[type=submit]').each(function(){
					$(this).val('');
				});
			}
			// обновляем положение fancybox 
			Drupal.ajax.prototype.commands['fancy-update']=function(a,r,s){
				$.fancybox.update();
			}

			///вставить подгруженный контент в конец списка .. 
			Drupal.ajax.prototype.commands['get-next-content-elements']=function(a,r,s){
					// завершили подгрузку
				var wrap=$('.container-term-wrapp-autoload');
				wrap.data('sended',r.finish);
				if (r.finish)
					wrap.find('.load-more-contents').remove();
				if (r.nids){
					//wrap.append(r.nids);
					//console.log(wrap.find('.load-more-contents'));
		
					
					wrap.find('.load-more-contents').before(r.nids);
					
					//	console.log(wrap.find('.load-more-contents'));
					//}
					Drupal.attachBehaviors($('.container-term-wrapp-autoload'));
					var im=wrap.find('img');
					//console.log(im.length);
					var compl=0;
					im.each(function(){
						compl+=this.complete-0;
						$(this).on('load',function(){
							compl++;
							if (compl>=im.length)
								$('body').trigger('one-height-elements',[$('#block-system-main'),'.product.teaser .wrap_teaser']);
								//console.log('Поехали');
								//$('#block-system-main .product.teaser .wrap_teaser').matchHeight();	
							//console.log('loaded');
						});
						//console.log(this.complete);
					});
				}
				//console.log(r);
			};
			// ----------------------------
			$('[data-show-node-in-popup]').once(function(){
				$(this).on('click',function(e){
					if ($(this).is('a'))
						e.preventDefault();
					c=$(this).data('show-node-in-popup');
					var ajax= new Drupal.ajax(false,false,{
						url:'/get-node-in-popup/'+c
					});
					ajax.eventResponse(ajax);
					
				});
			});
			// быстрый заказ
			$('[data-openform-quick-zakaz]').once(function(){
				$(this).on('click',function(e){
					dat=$(this).data();
					for (k in dat)
						if (!dat[k])
							dat[k]=k;
					dat['from-nid']=Drupal.settings["current-noda"];
					var ajax=new Drupal.ajax(false,false,{
						url:'/get-form-in-popup',
						submit:{
							fromclient:dat
						}
					});
					ajax.eventResponse(ajax);
				});
			});
			// Всплыть шаблоном .. из темы .. 
			$('[data-show-tpl-in-popup]').once(function(){
				$(this).on('click',function(e){
					e.preventDefault();
					dat=$(this).data();
					dat['from-nid']=Drupal.settings['current-noda'];
					var ajax= new Drupal.ajax(false,false,{
						url:'/get-tpl-in-popup',
						submit:dat,
					});
					ajax.eventResponse(ajax);
				});
			});
			$('[data-openform-new-otziv]').once(function(){
				$(this).on('click',function(e){
					dat=$(this).data();
					for (k in dat)
						if (!dat[k])
							dat[k]=k;
					dat['from-nid']=Drupal.settings["current-noda"];
					var ajax=new Drupal.ajax(false,false,{
						url:'/get-form-in-popup',
						submit:{
							fromclient:dat
						}
					});
					ajax.eventResponse(ajax);
				});
			});
		}
	}
})(jQuery)