/**
 * @author mrdoob / http://mrdoob.com/
 */

Sidebar.Corrosion = function ( editor ) {

	var signals = editor.signals;

	var container = new UI.CollapsiblePanel();
	container.setCollapsed( editor.config.getKey( 'ui/sidebar/corrosion/collapsed' ) );
	container.onCollapsedChange( function ( boolean ) {

		editor.config.setKey( 'ui/sidebar/corrosion/collapsed', boolean );

	} );
	container.setDisplay( 'none' );

	container.addStatic( new UI.Text('변퇴/부식 알고리즘') );
	container.add( new UI.Break() );

	// 유도공식
	var objectFuncRow = new UI.Panel();
	var outline = new UI.Outliner(editor).setHeight( '30px' );
	objectFuncRow.add( outline );
	objectFuncRow.add( new UI.Text( '1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9' ).setWidth( '240px' ) );
	container.add(objectFuncRow);

	// 조건설명
	var objectInitRow = new UI.Panel();
	objectInitRow.add( new UI.Text( '' ).setWidth( '90px' ) );
	objectInitRow.add( new UI.Text( '( α + β + γ = 1 )' ).setWidth( '150px' ) );
	container.add(objectInitRow);
	
	
	function update() {

		var object = editor.selected;

		if ( object !== null ) {

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

	}

	return container;

}
