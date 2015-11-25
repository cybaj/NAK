/**
 * @author mrdoob / http://mrdoob.com/
 */

Sidebar.NakAlgorithm = function ( editor ) {

	var signals = editor.signals;

	var container = new UI.CollapsiblePanel();
	container.setCollapsed( editor.config.getKey( 'ui/sidebar/nakalrorithm/collapsed' ) );
	container.onCollapsedChange( function ( boolean ) {

		editor.config.setKey( 'ui/sidebar/nakalrorithm/collapsed', boolean );

	} );
	container.setDisplay( 'none' );

	container.addStatic( new UI.Text('실감형색체 변환 알고리즘') );
	container.add( new UI.Break() );

	// 유도공식
	var objectFuncRow = new UI.Panel();
	objectFuncRow.add( new UI.Text( '유도공식' ).setWidth( '90px' ) );
	objectFuncRow.add( new UI.Text( 'α*R + β*G + γ*B' ).setWidth( '150px' ) );
	container.add(objectFuncRow);

	// 조건설명
	var objectInitRow = new UI.Panel();
	objectInitRow.add( new UI.Text( '' ).setWidth( '90px' ) );
	objectInitRow.add( new UI.Text( '( α + β + γ = 1 )' ).setWidth( '150px' ) );
	container.add(objectInitRow);
	
	
	// Red 베이스

	var objectRedRow = new UI.Panel();
	var objectRedX = new UI.Number().setWidth( '50px' ).onChange( update );
	var objectRedY = new UI.Number().setWidth( '50px' ).onChange( update );
	var objectRedZ = new UI.Number().setWidth( '50px' ).onChange( update );

	objectRedRow.add( new UI.Text( 'Rad 베이스' ).setWidth( '90px' ) );
	objectRedRow.add( objectRedX, objectRedY, objectRedZ );
	container.add( objectRedRow );

	// Green 베이스

	var objectGreenRow = new UI.Panel();
	var objectGreenX = new UI.Number().setWidth( '50px' ).onChange( update );
	var objectGreenY = new UI.Number().setWidth( '50px' ).onChange( update );
	var objectGreenZ = new UI.Number().setWidth( '50px' ).onChange( update );

	objectGreenRow.add( new UI.Text( 'Green 베이스' ).setWidth( '90px' ) );
	objectGreenRow.add( objectGreenX, objectGreenY, objectGreenZ );
	container.add( objectGreenRow );

	// Blue 베이스

	var objectBlueRow = new UI.Panel();
	var objectBlueX = new UI.Number().setWidth( '50px' ).onChange( update );
	var objectBlueY = new UI.Number().setWidth( '50px' ).onChange( update );
	var objectBlueZ = new UI.Number().setWidth( '50px' ).onChange( update );

	objectBlueRow.add( new UI.Text( 'Blue 베이스' ).setWidth( '90px' ) );
	objectBlueRow.add( objectBlueX, objectBlueY, objectBlueZ );
	container.add( objectBlueRow );

	// light select
	var ignoreObjectSelectedSignal = false;
	var outliner_light = new UI.Outliner( editor );
	outliner_light.onChange( function () {

		ignoreObjectSelectedSignal = true;

		updateUI(this);

		ignoreObjectSelectedSignal = false;

	} );
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
	var cameraDirect = new THREE.Vector3(-editor.camera.position.x,
									-editor.camera.position.y,
									-editor.camera.position.z);
	cameraDirect.normalize();								
	var objectCameraVectorRow = new UI.Panel();
	var objectCameraX = new UI.Number(cameraDirect.x).setWidth( '50px' ).onChange( update );
	var objectCameraY = new UI.Number(cameraDirect.y).setWidth( '50px' ).onChange( update );
	var objectCameraZ = new UI.Number(cameraDirect.z).setWidth( '50px' ).onChange( update );

	objectCameraVectorRow.add( new UI.Text( 'View 방향' ).setWidth( '90px' ) );
	objectCameraVectorRow.add( objectCameraX, objectCameraY, objectCameraZ );
	container.add( objectCameraVectorRow );

	// 조명 Vector
	var lightDirect = new THREE.Vector3();						
	var objectLightVectorRow = new UI.Panel();
	var objectLightX = new UI.Number(lightDirect.x).setWidth( '50px' ).onChange( update );
	var objectLightY = new UI.Number(lightDirect.y).setWidth( '50px' ).onChange( update );
	var objectLightZ = new UI.Number(lightDirect.z).setWidth( '50px' ).onChange( update );

	objectLightVectorRow.add( new UI.Text( 'Light 방향' ).setWidth( '90px' ) );
	objectLightVectorRow.add( objectLightX, objectLightY, objectLightZ );
	container.add( objectLightVectorRow );
	container.add( new UI.Break() );
	
	//변환 버튼
	var objectTransColorRow = new UI.Panel();

	var transColorButton = new UI.Button( '변환' ).setWidth( '150px' ).setMarginLeft( '7px' ).onClick( function () {
		
		generationColors();

	} );
	objectTransColorRow.add( new UI.Text( '색상변환' ).setWidth( '90px' ) );
	objectTransColorRow.add( transColorButton );
	container.add( objectTransColorRow );

	//message 출력 문자열
	var statusMessage = new UI.Text( '' ).setWidth( '240px' );
	container.add( statusMessage );
	
	//선택된 객체의 triangle의 노멀정보를 이용해서 색상을 변환시킨다.
	function generationColors() 
	{
		//광원이 선택되었는지 확인한다.
		var value = outliner_light.getValue();
		var helper = editor.helpers[ value ];
		if(helper==undefined)
		{
			statusMessage.setValue("주의 : Light를 선택하세요");
			return;
		}
		
		//
		var object = editor.selected;
		if(object.type!=="Mesh")
		{
			statusMessage.setValue("경고 : NAK용 모델을 선택하세요.");
			return;
		}
		
		for( var f = 0, fl = object.geometry.faces.length; f < fl; f ++ ) 
		{
			var face = object.geometry.faces[ f ];

			var centroid = new THREE.Vector3()
				.add( object.geometry.vertices[ face.a ] )
				.add( object.geometry.vertices[ face.b ] )
				.add( object.geometry.vertices[ face.c ] )
				.divideScalar( 3 );

			// 가장 가까운 면의색을 변경 .
			var k = (256-(face.color.r+face.color.g+face.color.b)/3)/256;
			face.color.setRGB( k * face.color.r, k * face.color.g, k * face.color.b ); 
			object.geometry.colorsNeedUpdate = true;			
		}
		statusMessage.setValue("변환을 완료하였습니다.");	
	}

	function update() 
	{

		var object = editor.selected;

		if ( object !== null ) 
		{
			
			
			//object.position.x = objectRedX.getValue();
			//object.position.y = objectRedX.getValue();
			//object.position.z = objectRedX.getValue();

			//object.rotation.x = objectGreenX.getValue();
			//object.rotation.y = objectGreenX.getValue();
			//object.rotation.z = objectGreenX.getValue();

			//object.scale.x = objectBlueX.getValue();
			//object.scale.y = objectBlueX.getValue();
			//object.scale.z = objectBlueX.getValue();

			//object.visible = objectVisible.getValue();

			signals.objectChanged.dispatch( object );

		}

	}

	function updateRows( object ) {



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
	
	function updateUI( object ) {

		/*
		if ( object.parent !== null ) {

			objectParent.setValue( object.parent.id );

		}
		*/

		// 카메라 Vector
		var cameraDirect = new THREE.Vector3(-editor.camera.position.x,
										-editor.camera.position.y,
										-editor.camera.position.z);
		cameraDirect.normalize();
		objectCameraX.setValue(cameraDirect.x);
		objectCameraY.setValue(cameraDirect.y);
		objectCameraZ.setValue(cameraDirect.z);		

		// light Vector
		var value = outliner_light.getValue();
		if(value!==null)
		{
			var helper = editor.helpers[ value ];
			if(helper!==undefined)
			{
				var lightDirect = new THREE.Vector3(-helper.light.position.x,-helper.light.position.y,-helper.light.position.z);
				lightDirect.normalize();
				objectLightX.setValue(lightDirect.x);
				objectLightY.setValue(lightDirect.y);
				objectLightZ.setValue(lightDirect.z);
			}			
		}
		
		//메시지
		statusMessage.setValue("");
	}

	return container;

}
