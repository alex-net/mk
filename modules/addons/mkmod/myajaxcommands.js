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
				$.fancybox.close();
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
			// ресет (сброс) формы 
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

			/**
			 * всунуть в контент по серектору  список нод отрендеренных 
			 */
			Drupal.ajax.prototype.commands['place-nodes-list']=function(a,r,s){
				$(r.placeto).html(r.html);
				$('body').trigger('place-nodes-list',[true,r.placeto]);
				Drupal.attachBehaviors($(r.placeto));

			}

			
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


			// маскируем  gjkz  ввода . 
			$('input[data-inputmask]').once(function(){
				if (jQuery.fn.inputmask)
					$(this).inputmask();
					//console.log(this);
			});
		}
	}
})(jQuery)