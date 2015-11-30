/**
 * @author mrdoob / http://mrdoob.com/
 */

Sidebar.Geometry.Modifiers = function ( signals, object ) {

	var subdivisions = 1;
	
	var container = new UI.Panel().setPaddingLeft( '90px' );

	var geometry = object.geometry;

	// Compute Vertex Normals

	var button = new UI.Button( 'Compute Vertex Normals' ).setWidth('150px');
	button.onClick( function () {

		geometry.computeVertexNormals();

		if ( geometry instanceof THREE.BufferGeometry ) {

			geometry.attributes.normal.needsUpdate = true;

		} else {

			geometry.normalsNeedUpdate = true;

		}

		signals.geometryChanged.dispatch( object );

	} );

	container.add( button );

	//
	container.add( new UI.Break() );
	
	// subdivision
	
	var sbutton = new UI.Button( 'Subdivisions' ).setWidth('150px');
	
	sbutton.onClick( function() {
		
		subdivisions = Math.max( 0, subdivisions + 1 );
		var modifier = new THREE.SubdivisionModifier( subdivisions );

		// mergeVertices(); is run in case of duplicated vertices
		geometry.mergeVertices();
		geometry.computeFaceNormals();
		geometry.computeVertexNormals();

		modifier.modify( geometry );
		geometry.normalsNeedUpdate = true;
		
		signals.geometryChanged.dispatch( object );
	});
	
	container.add ( sbutton);
	
	return container;

}
