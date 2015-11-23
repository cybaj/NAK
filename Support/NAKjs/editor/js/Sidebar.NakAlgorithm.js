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

	function updateScaleX() {

		var object = editor.selected;

		if ( objectScaleLock.getValue() === true ) {

			var scale = objectScaleX.getValue() / object.scale.x;

			objectScaleY.setValue( objectScaleY.getValue() * scale );
			objectScaleZ.setValue( objectScaleZ.getValue() * scale );

		}

		update();

	}

	function updateScaleY() {

		var object = editor.selected;

		if ( objectScaleLock.getValue() === true ) {

			var scale = objectScaleY.getValue() / object.scale.y;

			objectScaleX.setValue( objectScaleX.getValue() * scale );
			objectScaleZ.setValue( objectScaleZ.getValue() * scale );

		}

		update();

	}

	function updateScaleZ() {

		var object = editor.selected;

		if ( objectScaleLock.getValue() === true ) {

			var scale = objectScaleZ.getValue() / object.scale.z;

			objectScaleX.setValue( objectScaleX.getValue() * scale );
			objectScaleY.setValue( objectScaleY.getValue() * scale );

		}

		update();

	}

	function update() {

		var object = editor.selected;

		if ( object !== null ) {

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

	function updateUI( object ) {

		/*
		if ( object.parent !== null ) {

			objectParent.setValue( object.parent.id );

		}
		*/

		//objectPositionX.setValue( object.position.x );
		//objectPositionY.setValue( object.position.y );
		//objectPositionZ.setValue( object.position.z );

		//objectRotationX.setValue( object.rotation.x );
		//objectRotationY.setValue( object.rotation.y );
		//objectRotationZ.setValue( object.rotation.z );

		//objectScaleX.setValue( object.scale.x );
		//objectScaleY.setValue( object.scale.y );
		//objectScaleZ.setValue( object.scale.z );
	}

	return container;

}
