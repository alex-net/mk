ymaps.ready(function(){
	var map= new ymaps.Map(jQuery('.map-sklad')[0],{
		center:[55.755814,37.617635],
		zoom:5,
		controls:['zoomControl'],
		behaviors:['drag','dblClickZoom']
	},{});
	for(k in Drupal.settings.sklads){
		p=Drupal.settings.sklads[k];
		
		if (typeof p.point!='undefined'){
			//console.log(p);
			var pp=new ymaps.Placemark([p.point.y,p.point.x],{
				hintContent:p.name+(p.subname?' ('+p.subname+')':''),
				balloonContent:p.content,
				
			},{
				//preset:'islands#violetDotIconWithCaption'
				iconLayout:'default#image',
				iconImageHref:'/sites/all/themes/mk2/imgs/map-marker.png',
				iconImageOffset:[-20,-42],
				iconImageSize:[41,43]
			});
			map.geoObjects.add(pp);
		}
	}
	map.setBounds(map.geoObjects.getBounds());
	map.setZoom(map.getZoom());
	
	
	
});