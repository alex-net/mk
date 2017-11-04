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
				console.log($(':input',r.selector).not('[type=hidden]'));
				$(':input',r.selector).not('[type=hidden],[type=submit]').each(function(){
					$(this).val('');
				});
			}
			// обновляем положение fancybox 
			Drupal.ajax.prototype.commands['fancy-update']=function(a,r,s){
				$.fancybox.update();
			}
			// ----------------------------
			$('[data-show-node-in-popup]').once(function(){
				$(this).on('click',function(){
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