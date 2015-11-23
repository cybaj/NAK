/**
 * @author mrdoob / http://mrdoob.com/
 */

Menubar.Add = function ( editor ) {

	var container = new UI.Panel();
	container.setClass( 'menu' );

	var title = new UI.Panel();
	title.setClass( 'title' );
	title.setTextContent( '조명추가' );
	container.add( title );

	var options = new UI.Panel();
	options.setClass( 'options' );
	container.add( options );

	//

	var meshCount = 0;
	var lightCount = 0;
	var cameraCount = 0;

	editor.signals.editorCleared.add( function () {

		meshCount = 0;
		lightCount = 0;
		cameraCount = 0;

	} );


	// Sprite

	var option = new UI.Panel();
	option.setClass( 'option' );
	option.setTextContent( 'Sprite' );
	option.onClick( function () {

		var sprite = new THREE.Sprite( new THREE.SpriteMaterial() );
		sprite.name = 'Sprite ' + ( ++ meshCount );

		editor.addObject( sprite );
		editor.select( sprite );

	} );
	options.add( option );

	//

	options.add( new UI.HorizontalRule() );

	// PointLight

	var option = new UI.Panel();
	option.setClass( 'option' );
	option.setTextContent( '포인트 조명' );
	option.onClick( function () {

		var color = 0xffffff;
		var intensity = 1;
		var distance = 0;

		var light = new THREE.PointLight( color, intensity, distance );
		light.name = 'PointLight ' + ( ++ lightCount );

		editor.addObject( light );
		editor.select( light );

	} );
	options.add( option );

	// SpotLight

	var option = new UI.Panel();
	option.setClass( 'option' );
	option.setTextContent( '스포트 라이트' );
	option.onClick( function () {

		var color = 0xffffff;
		var intensity = 1;
		var distance = 0;
		var angle = Math.PI * 0.1;
		var exponent = 10;

		var light = new THREE.SpotLight( color, intensity, distance, angle, exponent );
		light.name = 'SpotLight ' + ( ++ lightCount );
		light.target.name = 'SpotLight ' + ( lightCount ) + ' Target';

		light.position.set( 0.5, 1, 0.75 ).multiplyScalar( 200 );

		editor.addObject( light );
		editor.select( light );

	} );
	options.add( option );

	// DirectionalLight

	var option = new UI.Panel();
	option.setClass( 'option' );
	option.setTextContent( '방향성 조명' );
	option.onClick( function () {

		var color = 0xffffff;
		var intensity = 1;

		var light = new THREE.DirectionalLight( color, intensity );
		light.name = 'DirectionalLight ' + ( ++ lightCount );
		light.target.name = 'DirectionalLight ' + ( lightCount ) + ' Target';

		light.position.set( 0.5, 1, 0.75 ).multiplyScalar( 200 );

		editor.addObject( light );
		editor.select( light );

	} );
	options.add( option );

	// HemisphereLight

	var option = new UI.Panel();
	option.setClass( 'option' );
	option.setTextContent( '반구 조명' );
	option.onClick( function () {

		var skyColor = 0x00aaff;
		var groundColor = 0xffaa00;
		var intensity = 1;

		var light = new THREE.HemisphereLight( skyColor, groundColor, intensity );
		light.name = 'HemisphereLight ' + ( ++ lightCount );

		light.position.set( 0.5, 1, 0.75 ).multiplyScalar( 200 );

		editor.addObject( light );
		editor.select( light );

	} );
	options.add( option );

	// AmbientLight

	var option = new UI.Panel();
	option.setClass( 'option' );
	option.setTextContent( '주변 라이트' );
	option.onClick( function() {

		var color = 0x222222;

		var light = new THREE.AmbientLight( color );
		light.name = 'AmbientLight ' + ( ++ lightCount );

		editor.addObject( light );
		editor.select( light );

	} );
	options.add( option );

	//

	options.add( new UI.HorizontalRule() );

	// PerspectiveCamera

	var option = new UI.Panel();
	option.setClass( 'option' );
	option.setTextContent( '원근 카메라' );
	option.onClick( function() {

		var camera = new THREE.PerspectiveCamera( 50, 1, 1, 10000 );
		camera.name = 'PerspectiveCamera ' + ( ++ cameraCount );

		editor.addObject( camera );
		editor.select( camera );

	} );
	options.add( option );

	return container;

}
