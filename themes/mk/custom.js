(function ($) {
    Drupal.behaviors.customAddmi = {
        attach: function (context, settings) {

        }
    };
})(jQuery);


jQuery(document).ready(function() {

	var $ = jQuery.noConflict();

	if ($("aside.sidebar").height() > $("#main_content").height()) {
		var height_sidebar = $("aside.sidebar").height();
		$("#main_content").css('minHeight', height_sidebar);
	};

	$('body.page-checkout .checkout-buttons input.checkout-continue').val('Оформить заказ');

	new WOW().init();

	$("body.front .node-page.node-promoted .field-name-body").append('<a href="#">Читать далее</a>');
	$("body.front .node-page.node-promoted .field-name-body > a").click(function(event) {
		event.preventDefault();
		$("body.front .node-page.node-promoted .field-name-body").addClass('showed');
	});

	if ($(".breadcrumb > .inline").length == 4) {
		$(".breadcrumb > .inline:last-child").prev().prev().find('a').removeAttr('href').css({
			textDecoration: 'none',
			cursor: 'default'
		});;
	};


    $(window).load(function(){
      $('.view-display-id-main_slider_carousel').flexslider({
        animation: "slide",
        controlNav: false,
        animationLoop: false,
        slideshow: true,
        itemWidth: 210,
        maxItems: 3, 
        asNavFor: '.view-display-id-main_slider_focus'
      });

      $('.view-display-id-main_slider_focus').flexslider({
        animation: "fade",
        controlNav: false,
        directionNav: false,
        animationLoop: false,
        slideshow: true,
        sync: ".view-display-id-main_slider_carousel",
        start: function(slider){
          $('body').removeClass('loading');
        }
      });
      $('#block-views-discounts-slider-block .view-content').flexslider({
        animation: "slide",
        controlNav: false,
        animationLoop: true,
        slideshow: true,
        maxItems: 1, 
        prevText: "",
		nextText: "", 
		slideshowSpeed: 5000,
      });
      $('.view-best-products .view-content').flexslider({
        animation: "slide",
        controlNav: false,
        slideshow: true,
		itemWidth: 210,
        maxItems: 4, 
        prevText: "",
		nextText: "",      
    	});
    });
	
	
	/*$(".view-commerce-cart-form table tbody tr").each(function() {
		var from_val = parseInt($(this).find('.from_to .from .val').text());
		var to_val = $(this).find('.from_to .to .val').text();

		$(this).find('.views-field-edit-quantity input').bind("keyup change", function() {
		    if ($(this).val() < from_val) {
				$(this).val(2);
			} else {

			};

		    if ($(this).val() > to_val) {
				$(this).val(2);
			};
		})

	});*/

	(function($){
        $('.product').each(function(){
            var from_to=$('.from_to',this)
                    ,inputs=$('.form-text',this)
                    ,intervals=[]
                    ,i
                   
            for(i=0;i<from_to.length;i++)
                    intervals[i]=from_to.eq(i).text().replace(/\D+([\d\s]+)\D+([\d\s]+)?\D+/,'$1,$2').replace(/\s/g,'').split(',')
                    ,intervals[i][0]=parseInt(intervals[i][0])
                    ,intervals[i][1]=parseInt(intervals[i][1])
           
            intervals[0][1]=intervals[0][0]
            intervals[0][0]=0
            intervals[from_to.length-1][1]=Infinity
           
            inputs.bind('keyup',function(e,d){
               var $this=$(this)
                       ,val=$this.val()
                       ,i
                       
               for(i=0;i<intervals.length;i++){
                       if(intervals[i].length===2){
                               if(intervals[i][0]<=val&&intervals[i][1]>=val)
                                       select(inputs.eq(i))
                       }else{
                               if(intervals[i][0]<val)
                                       select(inputs.eq(i))              
                       }
               }
               
               function select($this){
                            inputs.val(0)
                        $this.val(val).focus()                       
               }
                       
            })
        });
		$('.right .form-item input').bind("change keyup input click", function() {
	        if (this.value.match(/[^0-9]/g)) {
	            this.value = this.value.replace(/[^0-9]/g, '');
	        }
	    });
	})(jQuery)




	$(".hidden_from_js").css('display', 'none');

	$(".wrap_teaser div.show_more").toggle(function() {
		$(this).parent().parent().addClass('show_more_info');
		$(this).text("Скрыть");
	}, function() {
		$(this).parent().parent().removeClass('show_more_info');
		$(this).text("Подробнее");
	});

	$(".field-name-field-download-price-list a").text('Скачать прайс-лист');
	$(".field-name-field-download-certificate a").text('Скачать сертификат');

	/*$(".view-category-products-home > .view-content > .item-list ul li").each(function (e) {
		$(this).find(' > .item-list').parent().addClass('has_child')
		$(this).not(':has(.item-list)').addClass('not_has_child')
	});*/

	$(".view-category-products-home > .view-content > .item-list > ul > li.has_child .to_child").live('click', function(e){
		e.preventDefault();
		$(".view-category-products-home > .view-content").fadeOut(0);
		$(this).parent().children('.item-list').clone(true).insertAfter("div.view-category-products-home > .view-content");
	});

	/*$(".view-category-products-home > .item-list > ul > li").live('click', function(e){
		if ($(this).hasClass("not_has_child")) {
			
		} else {
			e.preventDefault();
			$(".view-category-products-home > .item-list").fadeOut(0);
			var cloned_categories = $(this).children('.item-list').clone(true);
			$('.view-category-products-home > .item-list').remove();
			cloned_categories.insertAfter("div.view-category-products-home > .view-content");
		}
	});*/




	$(".up_down a.up").click(function() {
		if($(window).scrollTop() > 0) {
			// $("html, body").animate({ scrollTop: 70 }, 0);
			$("html, body").animate({ scrollTop: 0 }, 500);
			return false;
		}
	});
	$(".up_down a.down").click(function() {
		var height_scroll = $(document).height();
		if($(window).scrollTop() + $(window).height() < $(document).height()) {
			var height_scroll = height_scroll -70;
			// $("html, body").animate({ scrollTop: $('.container_wrap > .container-fluid').height() -600}, 0);
			$("html, body").animate({ scrollTop: $("html, body")[0].scrollHeight}, 800);
	    }
		return false;
	});

	$(window).resize(function() {
		if ($(this).width() <= 1200) {
			$(".breadcrumb a").click(function(e){
		        if(!$('.breadcrumb').hasClass('clickable'))
		        e.preventDefault();
		        $('.breadcrumb').addClass('clickable');
		    });
		}
	});
	$("#block-views-product-titles-block").hide(0);
	jQuery("#block-views-product-titles-block .views-row a").click(function () {
		$("#block-views-product-titles-block .views-row a").removeClass("active");
		$(this).addClass("active");
	})

	/*if ($(".page_title").length){ 

		$(".page_title").hover(function() {
				$("#block-views-product-titles-block").fadeIn(200);
			}, function() {
		    	$("#block-views-product-titles-block").fadeOut(200);
			}
		);




		var stickyOffset = $('.page_title').offset().top;

		$(window).scroll(function(){
		  var sticky = $('.page_title'),
		      scroll = $(window).scrollTop();
		  if (scroll >= stickyOffset) sticky.addClass('fixed');
		  else sticky.removeClass('fixed');
		  $(".for_fix").width(sticky.width());
		});
	 }*/



	$(".header .cart .line-item-total-raw").text(function(i, text) {
	    return text.slice(0, -4);
	});

	$('.certificates').viewportChecker();





	/******************************************************************/





	/* START SEARCH CLICK IN MAIN MENU */

	$("#menu-3095-1 a").click(function(e) {
		e.preventDefault();
		$("body").toggleClass("search_is_visible");
		if ($("body").hasClass('search_is_visible')) {
			$("#block-search-form").animate({bottom: -41,opacity:1}, 200);
			$("#block-search-form input[type='text']").focus();
		} else {
			$("#block-search-form").animate({bottom: 0,opacity:0}, 200);
		};
	});

	$("#block-search-form").append('<a class="close_it" href="#"><span>Х</span>закрыть</a>')

	$(".close_it").click(function(e) {
		e.preventDefault();
		$("body").toggleClass("search_is_visible");
		$("#block-search-form").animate({bottom: 0,opacity:0}, 200);
	});

	/* END SEARCH CLICK IN MAIN MENU */




	/******************************************************************/




	/* START HEIGHT PRODUCT BY VERY HIGHEST */

	var width_product = $(".product.teaser").width();
	$(".product.teaser img").height(width_product);

	// $(".product.teaser:nth-child(4n-2)").each(function (e) {
	// 	$(this).addClass('first')

	// 	var this_1 = $(this).height();
	// 	var this_2 = $(this).next().height();
	// 	var this_3 = $(this).next().next().height();
	// 	var this_4 = $(this).next().next().next().height();

	// 	var numbers_array = [this_1, this_2, this_3, this_4];

	// 	var biggest = Math.max.apply(null, numbers_array) + 35;

	// 	$(this).height(biggest);
	// 	$(this).next().height(biggest);
	// 	$(this).next().next().height(biggest);
	// 	$(this).next().next().next().height(biggest);

	// });

	/* END HEIGHT PRODUCT BY VERY HIGHEST */





	/******************************************************************/





	/* START PRODUCT TEASER FOCUS QUANTITY */
	

	$("input[id^='edit-add-to-cart-quantity']").focusin(function(){
	    $(this).css("background-color","#FFFFCC");
	    var inputValZero = $(this).val()
	    if (inputValZero == 0) {
			$(this).val('');
		};
	});

	$("input[id^='edit-add-to-cart-quantity']").focusout(function(){
	    $(this).css("background-color","#FFFFFF");
	    var inputValZero = $(this).val()
	    if (inputValZero == '') {
	    	$(this).val('0');
	    } else {
	    	$(this).val(inputValZero);
	    };
	});

	/* END PRODUCT TEASER FOCUS QUANTITY */


	/******************************************************************/


	var hash = window.location.hash;
	console.log(hash);
	$(hash).addClass('active_from_hash').fadeTo("slow", 0.40).fadeTo("slow", 0.80).fadeTo("slow", 0.20).fadeTo("slow", 0.80).fadeTo("slow", 100);

});



(function($) {

	$(function() {
		$('.views-field-edit-quantity .form-item input').bind("change keyup input click", function() {
		  if (this.value.match(/[^0-9]/g)) {
		      this.value = this.value.replace(/[^0-9]/g, '');
		  }
		});

		$("form .field-name-field-user-phone input").mask("+7 (999) 999-99-99");

		$('p:contains("На данный момент нет содержимого, классифицированного этим термином.")').css('display', 'none');

		$('#block-system-main .product.teaser .wrap_teaser').matchHeight();

		$(".page-checkout .commerce-line-item-views-form .views-field-edit-quantity input").attr('disabled', 'disabled');

		$('.page-checkout .commerce-line-item-views-form .views-field-title a').on('click',  function() {
			return false;
		});
	});
	
})(jQuery);