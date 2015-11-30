/**
 * @author mrdoob / http://mrdoob.com/
 */

Sidebar.NakAlgorithm = function ( editor ) {
	
	var unitViewAngle = 18;//Math.asin(1/5) * 180/ Math.PI;
	var viewregion = [0, unitViewAngle*1, unitViewAngle*2, unitViewAngle*3, unitViewAngle*4, unitViewAngle*5];//[11.5,23,34.5,46,57,5,69];
	var colorData = [];
	var test = true;
	if(test===true)
	{
	// 실제 실험 색채 DATA
	// vangle = arcsin(1/5) * 180/pi = 11.53
	//rad base 
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[0],"rad":252,"green":69,"blue": 73});//rgb 임의 변경
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[1],"rad":241,"green":39,"blue": 43});
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[2],"rad":225,"green":21,"blue": 27});
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[3],"rad":236,"green":14,"blue": 17});
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[4],"rad":159,"green": 9,"blue": 11});
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[5],"rad": 87,"green":14,"blue": 14});

	colorData.push({"base":"rad","langle":30,"vangle": viewregion[0],"rad":253,"green": 86,"blue": 88});
	colorData.push({"base":"rad","langle":30,"vangle": viewregion[1],"rad":255,"green":115,"blue":119});//
	colorData.push({"base":"rad","langle":30,"vangle": viewregion[2],"rad":255,"green": 66,"blue": 78});
	colorData.push({"base":"rad","langle":30,"vangle": viewregion[3],"rad":253,"green": 50,"blue": 55});
	colorData.push({"base":"rad","langle":30,"vangle": viewregion[4],"rad":240,"green": 35,"blue": 41});
	colorData.push({"base":"rad","langle":30,"vangle": viewregion[5],"rad":201,"green": 27,"blue": 33});
	
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[0],"rad":228,"green": 37,"blue": 39});
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[1],"rad":253,"green": 99,"blue":104});
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[2],"rad":255,"green":131,"blue":139});//
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[3],"rad":255,"green": 92,"blue": 96});
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[4],"rad":254,"green": 71,"blue": 79});
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[5],"rad":238,"green": 49,"blue": 58});
		
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[0],"rad":122,"green": 10,"blue": 10});
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[1],"rad":217,"green": 47,"blue": 52});
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[2],"rad":253,"green":130,"blue":140});
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[3],"rad":255,"green":172,"blue":172});//
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[4],"rad":255,"green":121,"blue":127});
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[5],"rad":248,"green": 91,"blue":100});
	
	//green base
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[0],"rad": 77,"green":225,"blue":168});
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[1],"rad": 42,"green":218,"blue":154});
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[2],"rad": 25,"green":202,"blue":135});
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[3],"rad": 21,"green":176,"blue":115});
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[4],"rad": 11,"green":126,"blue": 81});
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[5],"rad": 15,"green": 59,"blue": 39});
	
	colorData.push({"base":"green","langle":30,"vangle": viewregion[0],"rad": 87,"green":223,"blue":164});
	colorData.push({"base":"green","langle":30,"vangle": viewregion[1],"rad":100,"green":232,"blue":183});
	colorData.push({"base":"green","langle":30,"vangle": viewregion[2],"rad": 66,"green":230,"blue":171});
	colorData.push({"base":"green","langle":30,"vangle": viewregion[3],"rad": 46,"green":227,"blue":163});
	colorData.push({"base":"green","langle":30,"vangle": viewregion[4],"rad": 28,"green":212,"blue":148});
	colorData.push({"base":"green","langle":30,"vangle": viewregion[5],"rad": 19,"green":152,"blue":106});
	
	colorData.push({"base":"green","langle":60,"vangle": viewregion[0],"rad": 41,"green":207,"blue":135});
	colorData.push({"base":"green","langle":60,"vangle": viewregion[1],"rad":106,"green":233,"blue":178});
	colorData.push({"base":"green","langle":60,"vangle": viewregion[2],"rad":123,"green":240,"blue":197});
	colorData.push({"base":"green","langle":60,"vangle": viewregion[3],"rad":103,"green":242,"blue":190});
	colorData.push({"base":"green","langle":60,"vangle": viewregion[4],"rad": 78,"green":240,"blue":184});
	colorData.push({"base":"green","langle":60,"vangle": viewregion[5],"rad": 46,"green":195,"blue":155});
	
	colorData.push({"base":"green","langle":90,"vangle": viewregion[0],"rad": 17,"green":100,"blue": 51});
	colorData.push({"base":"green","langle":90,"vangle": viewregion[1],"rad": 58,"green":190,"blue":133});
	colorData.push({"base":"green","langle":90,"vangle": viewregion[2],"rad":136,"green":236,"blue":197});
	colorData.push({"base":"green","langle":90,"vangle": viewregion[3],"rad":169,"green":250,"blue":224});
	colorData.push({"base":"green","langle":90,"vangle": viewregion[4],"rad":139,"green":250,"blue":212});
	colorData.push({"base":"green","langle":90,"vangle": viewregion[5],"rad":110,"green":238,"blue":197});
	
	//blue base
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[0],"rad": 39,"green":172,"blue":252});
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[1],"rad": 58,"green":158,"blue":247});
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[2],"rad":136,"green":140,"blue":234});
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[3],"rad":169,"green":121,"blue":215});
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[4],"rad":139,"green": 83,"blue":167});
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[5],"rad":110,"green": 47,"blue":105});
	
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[0],"rad": 73,"green":174,"blue":254});
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[1],"rad":128,"green":196,"blue":255});
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[2],"rad": 95,"green":186,"blue":255});
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[3],"rad": 64,"green":174,"blue":254});
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[4],"rad": 48,"green":163,"blue":251});
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[5],"rad": 33,"green":122,"blue":216});
	
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[0],"rad": 28,"green":134,"blue":226});
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[1],"rad": 86,"green":175,"blue":252});
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[2],"rad":143,"green":202,"blue":255});
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[3],"rad":110,"green":191,"blue":254});
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[4],"rad":106,"green":187,"blue":254});
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[5],"rad": 77,"green":161,"blue":246});
	
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[0],"rad": 10,"green": 54,"blue":116});
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[1],"rad": 42,"green":127,"blue":218});
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[2],"rad":127,"green":189,"blue":253});
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[3],"rad":175,"green":216,"blue":255});
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[4],"rad":154,"green":207,"blue":255});
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[5],"rad":124,"green":192,"blue":254});
	}
	else
	{
	//가상 색채 DATA
	//rad base 
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[0],"rad":252,"green":69,"blue": 73});//rgb 임의 변경
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[1],"rad":241,"green":39,"blue": 43});
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[2],"rad":225,"green":21,"blue": 27});
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[3],"rad":236,"green":14,"blue": 17});
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[4],"rad":159,"green": 9,"blue": 11});
	colorData.push({"base":"rad","langle": 0,"vangle": viewregion[5],"rad": 87,"green":14,"blue": 14});


	colorData.push({"base":"rad","langle":30,"vangle": viewregion[0],"rad":253,"green": 86,"blue": 88});
	colorData.push({"base":"rad","langle":30,"vangle": viewregion[1],"rad":255,"green":115,"blue":119});//
	colorData.push({"base":"rad","langle":30,"vangle": viewregion[2],"rad":255,"green": 66,"blue": 78});
	colorData.push({"base":"rad","langle":30,"vangle": viewregion[3],"rad":253,"green": 50,"blue": 55});
	colorData.push({"base":"rad","langle":30,"vangle": viewregion[4],"rad":240,"green": 35,"blue": 41});
	colorData.push({"base":"rad","langle":30,"vangle": viewregion[5],"rad":201,"green": 27,"blue": 33});


	colorData.push({"base":"rad","langle":60,"vangle": viewregion[0],"rad":228,"green": 37,"blue": 39});
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[1],"rad":253,"green": 99,"blue":104});
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[2],"rad":255,"green":131,"blue":139});//
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[3],"rad":255,"green": 92,"blue": 96});
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[4],"rad":254,"green": 71,"blue": 79});
	colorData.push({"base":"rad","langle":60,"vangle": viewregion[5],"rad":238,"green": 49,"blue": 58});
  
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[0],"rad":122,"green": 10,"blue": 10});
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[1],"rad":217,"green": 47,"blue": 52});
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[2],"rad":253,"green":130,"blue":140});
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[3],"rad":255,"green":172,"blue":172});//
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[4],"rad":255,"green":121,"blue":127});
	colorData.push({"base":"rad","langle":90,"vangle": viewregion[5],"rad":248,"green": 91,"blue":100});
	
	//green base
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[0],"rad": 77,"green":225,"blue":168});
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[1],"rad": 42,"green":218,"blue":154});
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[2],"rad": 25,"green":202,"blue":135});
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[3],"rad": 21,"green":176,"blue":115});
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[4],"rad": 11,"green":126,"blue": 81});
	colorData.push({"base":"green","langle": 0,"vangle": viewregion[5],"rad": 15,"green": 59,"blue": 39});
	
	colorData.push({"base":"green","langle":30,"vangle": viewregion[0],"rad": 87,"green":223,"blue":164});
	colorData.push({"base":"green","langle":30,"vangle": viewregion[1],"rad":100,"green":232,"blue":183});
	colorData.push({"base":"green","langle":30,"vangle": viewregion[2],"rad": 66,"green":230,"blue":171});
	colorData.push({"base":"green","langle":30,"vangle": viewregion[3],"rad": 46,"green":227,"blue":163});
	colorData.push({"base":"green","langle":30,"vangle": viewregion[4],"rad": 28,"green":212,"blue":148});
	colorData.push({"base":"green","langle":30,"vangle": viewregion[5],"rad": 19,"green":152,"blue":106});
	
	colorData.push({"base":"green","langle":60,"vangle": viewregion[0],"rad": 41,"green":207,"blue":135});
	colorData.push({"base":"green","langle":60,"vangle": viewregion[1],"rad":106,"green":233,"blue":178});
	colorData.push({"base":"green","langle":60,"vangle": viewregion[2],"rad":123,"green":240,"blue":197});
	colorData.push({"base":"green","langle":60,"vangle": viewregion[3],"rad":103,"green":242,"blue":190});
	colorData.push({"base":"green","langle":60,"vangle": viewregion[4],"rad": 78,"green":240,"blue":184});
	colorData.push({"base":"green","langle":60,"vangle": viewregion[5],"rad": 46,"green":195,"blue":155});
	
	colorData.push({"base":"green","langle":90,"vangle": viewregion[0],"rad": 17,"green":100,"blue": 51});
	colorData.push({"base":"green","langle":90,"vangle": viewregion[1],"rad": 58,"green":190,"blue":133});
	colorData.push({"base":"green","langle":90,"vangle": viewregion[2],"rad":136,"green":236,"blue":197});
	colorData.push({"base":"green","langle":90,"vangle": viewregion[3],"rad":169,"green":250,"blue":224});
	colorData.push({"base":"green","langle":90,"vangle": viewregion[4],"rad":139,"green":250,"blue":212});
	colorData.push({"base":"green","langle":90,"vangle": viewregion[5],"rad":110,"green":238,"blue":197});
	
	//blue base
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[0],"rad": 138,"green": 185,"blue": 246});
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[1],"rad": 118,"green": 172,"blue": 239});
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[2],"rad": 91,"green": 151,"blue": 226});
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[3],"rad": 65,"green": 128,"blue": 207});
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[4],"rad": 46,"green": 102,"blue": 180});
	colorData.push({"base":"blue","langle": 0,"vangle": viewregion[5],"rad": 37,"green": 77,"blue": 138});
	
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[0],"rad": 121,"green": 175,"blue": 241});
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[1],"rad": 148,"green": 192,"blue": 250});
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[2],"rad": 148,"green": 195,"blue": 252});
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[3],"rad": 126,"green": 182,"blue": 224});
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[4],"rad": 95,"green": 162,"blue": 238});
	colorData.push({"base":"blue","langle":30,"vangle": viewregion[5],"rad": 72,"green": 133,"blue": 211});
	
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[0],"rad": 66,"green": 121,"blue": 191});
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[1],"rad": 115,"green": 168,"blue": 232});
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[2],"rad": 153,"green": 201,"blue": 252});
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[3],"rad": 171,"green": 214,"blue": 254});
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[4],"rad": 148,"green": 201,"blue": 255});
	colorData.push({"base":"blue","langle":60,"vangle": viewregion[5],"rad": 114,"green": 177,"blue": 247});
	
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[0],"rad": 26,"green": 53,"blue": 94});
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[1],"rad": 60,"green": 105,"blue": 164});
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[2],"rad": 117,"green": 167,"blue": 224});
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[3],"rad": 170,"green": 213,"blue": 252});
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[4],"rad": 188,"green": 228,"blue": 252});
	colorData.push({"base":"blue","langle":90,"vangle": viewregion[5],"rad": 164,"green": 213,"blue":254});
	}
	
	var signals = editor.signals;

	var container = new UI.CollapsiblePanel();
	container.setCollapsed( editor.config.getKey( 'ui/sidebar/nakalrorithm/collapsed' ) );
	container.onCollapsedChange( function ( boolean ) {

		editor.config.setKey( 'ui/sidebar/nakalrorithm/collapsed', boolean );

	} );
	container.setDisplay( 'none' );

	container.addStatic( new UI.Text('실감형 색채 변환 알고리즘') );
	container.add( new UI.Break() );

	// 유도공식
	
	var objectFuncRow = new UI.Panel();
	objectFuncRow.add( new UI.Text( '유도공식' ).setWidth( '90px' ) );
	objectFuncRow.add( new UI.Text( 'α*R + β*G + γ*B' ).setWidth( '150px' ) );
	container.add(objectFuncRow);
	container.add( new UI.Break() );

	// 조건설명
	
	var objectInitRow = new UI.Panel();
	objectInitRow.add( new UI.Text( '* Support에 대한 실감색체 코드' ).setWidth( '200px' ) );
	container.add(objectInitRow);
	
	// Red 베이스

	var objectRedRow = new UI.Panel();
	var objectRedX = new UI.Integer().setWidth( '40px' ).onChange( update );
	var objectRedY = new UI.Integer().setWidth( '40px' ).onChange( update );
	var objectRedZ = new UI.Integer().setWidth( '40px' ).onChange( update );
	var radBaseColor = new UI.Color().setWidth( '30px' );
	radBaseColor.setValue("#000000");
	//this.color1 = [ 0, 128, 255 ]; // RGB array
	objectRedRow.add( new UI.Text( 'Rad 베이스' ).setWidth( '90px' ) );
	objectRedRow.add( objectRedX, objectRedY, objectRedZ );
	objectRedRow.add( radBaseColor );
	container.add( objectRedRow );

	// Green 베이스

	var objectGreenRow = new UI.Panel();
	var objectGreenX = new UI.Integer().setWidth( '40px' ).onChange( update );
	var objectGreenY = new UI.Integer().setWidth( '40px' ).onChange( update );
	var objectGreenZ = new UI.Integer().setWidth( '40px' ).onChange( update );
	var greenBaseColor = new UI.Color().setWidth( '30px' );
	greenBaseColor.setValue("#000000");

	objectGreenRow.add( new UI.Text( 'Green 베이스' ).setWidth( '90px' ) );
	objectGreenRow.add( objectGreenX, objectGreenY, objectGreenZ );
	objectGreenRow.add( greenBaseColor );
	container.add( objectGreenRow );

	// Blue 베이스

	var objectBlueRow = new UI.Panel();
	var objectBlueX = new UI.Integer().setWidth( '40px' ).onChange( update );
	var objectBlueY = new UI.Integer().setWidth( '40px' ).onChange( update );
	var objectBlueZ = new UI.Integer().setWidth( '40px' ).onChange( update );
	var blueBaseColor = new UI.Color().setWidth( '30px' );
	blueBaseColor.setValue("#000000");
	
	objectBlueRow.add( new UI.Text( 'Blue 베이스' ).setWidth( '90px' ) );
	objectBlueRow.add( objectBlueX, objectBlueY, objectBlueZ );
	objectBlueRow.add( blueBaseColor );
	container.add( objectBlueRow );
	container.add( new UI.Break() );
	
	// light select
	
	var ignoreObjectSelectedSignal = false;
	var outliner_light = new UI.Outliner( editor ).setHeight( '50px' );
	outliner_light.onChange( function () {

		ignoreObjectSelectedSignal = true;

		updateUI(this);

		ignoreObjectSelectedSignal = false;

	} );
	container.add( new UI.Text( '* 색채보정을 위한 광원 선택' ).setWidth( '200px' ) );
	container.add( outliner_light );
	container.add( new UI.Break() );
	
	var refreshLightUI = function () {

		var camera = editor.camera;
		var scene = editor.scene;

		var options = [];

		// options.push( { value: camera.id, html: '<span class="type ' + camera.type + '"></span> ' + camera.name } );
	
		( function addObjects( objects, pad ) {

			for ( var i = 0, l = objects.length; i < l; i ++ ) {

				var object = objects[ i ];

				if(object.type=='PointLight')
				{
					var html = pad + '<span class="type ' + object.type + '"></span> ' + object.name;

					options.push( { value: object.id, html: html } );

					addObjects( object.children, pad + '&nbsp;&nbsp;&nbsp;' );
				}
			}

		} )( scene.children, '&nbsp;&nbsp;&nbsp;' );

		outliner_light.setOptions( options );

		if ( editor.selected !== null ) {

			outliner_light.setValue( editor.selected.id );
		}
	};
	refreshLightUI();

	// 카메라 Vector
	var cameraDirect = new THREE.Vector3(-editor.camera.position.x,-editor.camera.position.y,-editor.camera.position.z);
	cameraDirect.normalize();
	
	var objectCameraVectorRow = new UI.Panel();
	var objectCameraX = new UI.Number(cameraDirect.x).setWidth( '40px' ).onChange( update );
	var objectCameraY = new UI.Number(cameraDirect.y).setWidth( '40px' ).onChange( update );
	var objectCameraZ = new UI.Number(cameraDirect.z).setWidth( '30px' ).onChange( update );
	var UIcameraAngle = new UI.Integer('0').setWidth( '30px' );
	
	objectCameraVectorRow.add( new UI.Text( 'View 방향' ).setWidth( '90px' ) );
	objectCameraVectorRow.add( objectCameraX, objectCameraY, objectCameraZ , UIcameraAngle);
	container.add( objectCameraVectorRow );

	// 조명 Vector
	var lightDirect = new THREE.Vector3();						
	var objectLightVectorRow = new UI.Panel();
	var objectLightX = new UI.Number(lightDirect.x).setWidth( '40px' ).onChange( update );
	var objectLightY = new UI.Number(lightDirect.y).setWidth( '40px' ).onChange( update );
	var objectLightZ = new UI.Number(lightDirect.z).setWidth( '30px' ).onChange( update );
	var UIlightAngle = new UI.Integer('0').setWidth( '30px' );
	
	objectLightVectorRow.add( new UI.Text( 'Light 방향' ).setWidth( '90px' ) );
	objectLightVectorRow.add( objectLightX, objectLightY, objectLightZ, UIlightAngle );
	container.add( objectLightVectorRow );
	container.add( new UI.Break() );
	
	//변환 버튼
	var objectTransColorRow = new UI.Panel();
	var transColorButton = new UI.Button( '변환' ).setWidth( '150px' ).setMarginLeft( '7px' ).onClick( function () {
		var result = false;
		var clock = new THREE.Clock();
		clock.start();
		result=generationColors();
		clock.stop();
		if(result===true)
		statusMessage.setValue("변환을 완료하였습니다.(" + parseFloat(clock.elapsedTime) + "ms)");	
	} );
	objectTransColorRow.add( new UI.Text( '색상변환' ).setWidth( '90px' ) );
	objectTransColorRow.add( transColorButton );
	container.add( objectTransColorRow );

	//message 출력 문자열
	var statusMessage = new UI.Text( '' ).setWidth( '240px' );
	container.add( statusMessage );
	
	/**
	* InterpolationColor : 색상 Data에서 각도를 찾고 보간 RGB를 취합니다.
	* db : 절대색채계의 색상 Data
	* base : db의 rgb 필터
	* langle : 광원과 노멀벡터의 사이각
	* vangle : view와 노멀벡터의 사이각
	*/
	function InterpolationColor(db, base, langle, vangle)
	{
		var find = false;
		var resRGB1 = {"rad":0,"green":0,"blue":0};
		var resRGB2 = {"rad":0,"green":0,"blue":0};
		
		//light의 사이값을 얻어옵니다.
		var lightBefore, lightAfter;
		for( var l = 0; l < db.length-1; l++) //6->data에서 첫번째 열만 비교하도록 함
		{
			if(db[l].base===base)
			{
				if(db[l].langle <= langle && langle < db[l+1].langle)
				{
					lightBefore = db[l].langle;
					lightAfter = db[l+1].langle;
					find = true;
					break;
				}
			}
		}
		if(find===false)
			return resRGB1;
		
		//vangle에 대해서 사이값에 의한 보간을 진행합니다.
		for( var l = 0; l < db.length-1; l++)
		{
			if(db[l].base===base)
			{
				//light befor에 대한 vlight의 rgb얻음
				if( db[l].langle===lightBefore && db[l].vangle <= vangle && vangle < db[l+1].vangle)
				{
					var intRad = db[l].rad + ( vangle* (db[l+1].rad - db[l].rad) / (db[l+1].vangle - db[l].vangle) );
					var intGreen = db[l].green +( vangle* (db[l+1].green - db[l].green) / (db[l+1].vangle - db[l].vangle) );
					var intBlue = db[l].blue + ( vangle* (db[l+1].blue - db[l].blue) / (db[l+1].vangle - db[l].vangle) );

					resRGB1.rad = parseInt(intRad);
					resRGB1.green = parseInt(intGreen);
					resRGB1.blue = parseInt(intBlue);
				}
				//light after에 대한 vlight의 rgb얻음				
				if( db[l].langle===lightAfter && db[l].vangle <= vangle && vangle < db[l+1].vangle)
				{
					var intRad = db[l].rad + ( vangle * (db[l+1].rad - db[l].rad) / (db[l+1].vangle - db[l].vangle) );
					var intGreen = db[l].green + ( vangle * (db[l+1].green - db[l].green) / (db[l+1].vangle - db[l].vangle) );
					var intBlue = db[l].blue + ( vangle * (db[l+1].blue - db[l].blue) / (db[l+1].vangle - db[l].vangle) );
										
					resRGB2.rad = parseInt(intRad);
					resRGB2.green = parseInt(intGreen);
					resRGB2.blue = parseInt(intBlue);
				}
			}					
		}
		
		// 두개의 결과값에 대한 보간값을 계산합니다.
		return {"rad":(resRGB1.rad+resRGB2.rad)/2,"green":(resRGB1.green+resRGB2.green)/2,"blue":(resRGB1.blue+resRGB2.blue)/2};
	}
	
	
	/** 
	* generationColors : 선택된 객체의 triangle의 노멀정보를 이용해서 색상을 변환시킨다.
	*
	*/
	function generationColors() 
	{
		var camera = editor.camera;
		var scene = editor.scene;
		
		//광원이 선택되었는지 확인한다.
		var value = outliner_light.getValue();
		var helper = editor.helpers[ value ];
		if(helper==undefined)
		{
			statusMessage.setValue("주의 : Light를 선택하세요");
			return false;
		}
		var lightPosition = helper.light.position;
		
		//
		var object = editor.selected;
		if(object.type!=="Mesh")
		{
			statusMessage.setValue("경고 : NAK용 모델을 선택하세요.");
			return false;
		}
		
		//레퍼런스 rgb , for l=30', v=sin-1(1/5) => viewregion[1]
		var Rr0 = InterpolationColor(colorData,   "rad", 30, viewregion[1]/2);
		var Gg0 = InterpolationColor(colorData, "green", 30, viewregion[1]/2);
		var Bb0 = InterpolationColor(colorData,  "blue", 30, viewregion[1]/2);
		
		var Ir0 = (Rr0.rad+Rr0.green+Rr0.blue) / 3;	
		var Ig0 = (Gg0.rad+Gg0.green+Gg0.blue) / 3;	
		var Ib0 = (Bb0.rad+Bb0.green+Bb0.blue) / 3;	
		
		for( var f = 0, fl = object.geometry.faces.length; f < fl; f ++ ) 
		{
			var face = object.geometry.faces[ f ];
			//normal
			var normal = face.normal;
			normal.normalize(0);
			
			var centroid = new THREE.Vector3()
			var pt1,pt2,pt3;
			if(object.geometry.vertices!==undefined)
			{
				pt1 = object.geometry.vertices[ face.a ];
				pt2 = object.geometry.vertices[ face.b ];
				pt3 = object.geometry.vertices[ face.c ];				
			}
			else if(object.geometry.attributes!==undefined)
			{
				pt1 = object.geometry.attributes.position.array[ face.a ];
				pt2 = object.geometry.attributes.position.array[ face.b ];
				pt3 = object.geometry.attributes.position.array[ face.c ];														
			}
			centroid.add(pt1).add(pt2).add(pt3).divideScalar(3);
						
			// view direction
			var viewDir = new THREE.Vector3();
			viewDir.x = camera.position.x - centroid.x;
			viewDir.y = camera.position.y - centroid.y;
			viewDir.z = camera.position.z - centroid.z;	
			viewDir.normalize();
			
			// light direction
			var lightDir = new THREE.Vector3();
			lightDir.x = lightPosition.x - centroid.x;
			lightDir.y = lightPosition.y - centroid.y;
			lightDir.z = lightPosition.z - centroid.z;
			lightDir.normalize();
			
			// radian to degree
			var lightAngle = Math.acos(lightDir.dot(normal)) * 180 / Math.PI;
			var viewAngle = Math.acos(viewDir.dot(normal)) * 180 / Math.PI;
					
			// 내적이 적으면 뒷면이므로 현재 광원으로 적용하지 않는다.
			var l_seta = viewDir.dot(normal);
			if(l_seta>0)
			{		
				if(face.vertexColors.length>0)
				{
					for(var c = 0; c <face.vertexColors.length; c++)
					{
						var color = face.vertexColors[c];
						
						//절대색채 light 보간
						var radRgb  = InterpolationColor(colorData, "rad",  lightAngle, viewAngle);
						var Ir = (radRgb.rad + radRgb.green + radRgb.blue)/3;
						var greenRgb= InterpolationColor(colorData, "green", lightAngle, viewAngle);
						var Ig = (greenRgb.rad + greenRgb.green + greenRgb.blue)/3;
						var blueRgb = InterpolationColor(colorData, "blue", lightAngle, viewAngle);
						var Ib = (blueRgb.rad + blueRgb.green + blueRgb.blue)/3;
						
						//intensive
						var Ri = color.r * (1+(Ir0-Ir)/256);
						var Gi = color.g * (1+(Ig0-Ig)/256);
						var Bi = color.b * (1+(Ib0-Ib)/256);
						
						var Rr = radRgb.rad;
						var Gg = radRgb.green;
						var Bb = radRgb.blue;
						
						var RRi = Rr0.rad  * Ri/Rr;
						var GGi = Gg0.green* Gi/Gg;
						var BBi = Bb0.blue * Bi/Bb;
				
						face.vertexColors[c].setRGB( RRi, GGi, BBi ); 
					}
				}
				else
				{
					var color = face.color;
					
					//절대색채 light 보간
					var radRgb  = InterpolationColor(colorData, "rad",  lightAngle, viewAngle);
					var Ir = (radRgb.rad + radRgb.green + radRgb.blue)/3;
					var greenRgb= InterpolationColor(colorData, "green", lightAngle, viewAngle);
					var Ig = (greenRgb.rad + greenRgb.green + greenRgb.blue)/3;
					var blueRgb = InterpolationColor(colorData, "blue", lightAngle, viewAngle);
					var Ib = (blueRgb.rad + blueRgb.green + blueRgb.blue)/3;
					
					//intensive
					var Ri = color.r * (1+(Ir0-Ir)/256);
					var Gi = color.g * (1+(Ig0-Ig)/256);
					var Bi = color.b * (1+(Ib0-Ib)/256);
					
					var Rr = color.r;
					var Gg = color.g;
					var Bb = color.b;
					
					var RRi = Rr0.rad*Ri/Rr;
					var GGi = Gg0.green*Gi/Gg;
					var BBi = Bb0.blue*Bi/Bb;
			
					face.color.setRGB( RRi, GGi, BBi ); 					
				}
				object.geometry.colorsNeedUpdate = true;
			}			
		}
		return true;
	}

	function update() 
	{

		var object = editor.selected;

		if ( object !== null ) 
		{
			//object.position.x = objectRedX.getValue();
			//object.position.y = objectRedX.getValue();
			//object.position.z = objectRedX.getValue();

			signals.objectChanged.dispatch( object );
		}
	}

	function updateRows( object ) 
	{

	}

	// events

	signals.objectSelected.add( function ( object ) {

		if ( object !== null ) {

			container.setDisplay( 'block' );

			updateRows( object );
			updateUI( object );

		} else {

			container.setDisplay( 'none' );

		}

	} );

	signals.objectChanged.add( function ( object ) {

		if ( object !== editor.selected ) return;

		updateUI( object );

	} ); 

	//in camera
	signals.cameraChanged.add( function (object) {
			
		if (editor.selected === null) return;
		
		updateUI(object);
	});
	
	// events

	signals.sceneGraphChanged.add( refreshLightUI );

	signals.objectSelected.add( function ( object ) {

		if ( ignoreObjectSelectedSignal === true ) return;

		outliner_light.setValue( object !== null ? object.id : null );

	} );
	
	signals.geometryChanged.add( function( object ) {
		
		statusMessage.setValue("");
		
	} );
	
	/**
	* getSelectedNormal : 사용자가 선택한 Triangle의 normal vector를 얻어옵니다. 
	* (주의 : 여러개가 존재할때 최초의 것을 취합니다.)
	*/
	function getSelectedNormal()
	{
		var scene = editor.scene;
		for ( var i = 0; i < scene.children.length; i ++ ) 
		{
			var object = scene.children[i];
			if(object.name === 'Support')
			{
				var userData = object.userData;
				return userData;
			}
		}	
		return undefined;
	}
	
	function updateUI( object ) 
	{
		/*
		if ( object.parent !== null ) {

			objectParent.setValue( object.parent.id );

		}
		*/
		// light Vector
		var value = outliner_light.getValue();
		if(value!==null)
		{
			var helper = editor.helpers[ value ];
			if(helper!==undefined)
			{		
				//업데이트
				var normalInfo = getSelectedNormal();
				if(normalInfo !== undefined)
				{
					var normalDirection = new THREE.Vector3(normalInfo[0].x,normalInfo[0].y,normalInfo[0].z);
					var normalPosition = new THREE.Vector3(normalInfo[1].x,normalInfo[1].y,normalInfo[1].z);
					
					//View vector
					var cameraDirect = new THREE.Vector3();
					cameraDirect.subVectors(editor.camera.position,normalPosition);
					cameraDirect.normalize();
					objectCameraX.setValue(cameraDirect.x);
					objectCameraY.setValue(cameraDirect.y);
					objectCameraZ.setValue(cameraDirect.z);
										
					//Light vector
					var lightDirect = new THREE.Vector3();
					lightDirect.subVectors(helper.light.position,normalPosition);
					lightDirect.normalize();
					objectLightX.setValue(lightDirect.x);
					objectLightY.setValue(lightDirect.y);
					objectLightZ.setValue(lightDirect.z);
				
				    //colorData의 측정
					var lightAngle = Math.acos(normalDirection.dot(lightDirect)) * 180 / Math.PI;
					var viewAngle = Math.acos(normalDirection.dot(cameraDirect)) * 180 / Math.PI;
					UIcameraAngle.setValue(parseInt(viewAngle));
					UIlightAngle.setValue(parseInt(lightAngle));
					
					var radRgb  = InterpolationColor(colorData, "rad",  lightAngle, viewAngle);
					var greenRgb= InterpolationColor(colorData, "green", lightAngle, viewAngle);
					var blueRgb = InterpolationColor(colorData, "blue", lightAngle, viewAngle);
					
					// Red 베이스
					objectRedX.setBackgroundColor(new THREE.Color(radRgb.rad/255,0,0));
					objectRedX.setValue(radRgb.rad);
					objectRedX.setBackgroundColor(new THREE.Color(0,radRgb.green/255,0));
					objectRedY.setValue(radRgb.green);
					objectRedX.setBackgroundColor(new THREE.Color(0,0,radRgb.blue/255));
					objectRedZ.setValue(radRgb.blue);
					radBaseColor.setHexValue(new THREE.Color(radRgb.rad/255,radRgb.green/255,radRgb.blue/255).getHex());
					// Green 베이스
					objectGreenX.setValue(greenRgb.rad);
					objectRedX.setBackgroundColor(new THREE.Color(greenRgb.rad/255,0,0));
					objectGreenY.setValue(greenRgb.green);
					objectRedX.setBackgroundColor(new THREE.Color(0,greenRgb.green/255,0));
					objectGreenZ.setValue(greenRgb.blue);
					objectRedX.setBackgroundColor(new THREE.Color(0,0,greenRgb.blue/255));
					greenBaseColor.setHexValue(new THREE.Color(greenRgb.rad/255,greenRgb.green/255,greenRgb.blue/255).getHex());
					// Blue 베이스
					objectBlueX.setValue(blueRgb.rad);
					objectRedX.setBackgroundColor(new THREE.Color(blueRgb.rad/255,0,0));
					objectBlueY.setValue(blueRgb.green);
					objectRedX.setBackgroundColor(new THREE.Color(0,blueRgb.green/255,0));
					objectBlueZ.setValue(blueRgb.blue);
					objectRedX.setBackgroundColor(new THREE.Color(0,0,blueRgb.blue/255));
					blueBaseColor.setHexValue(new THREE.Color(blueRgb.rad/255,blueRgb.green/255,blueRgb.blue/255).getHex());					
				}
			}			
		}
		//메시지
		statusMessage.setValue("");
	}
	return container;
}
