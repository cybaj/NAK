/**
 * @author mrdoob / http://mrdoob.com/
 */

var Sidebar = function ( editor ) {

	var container = new UI.Panel();
	container.setId( 'sidebar' );

	container.add( new Sidebar.Project( editor ) );
	container.add( new Sidebar.Scene( editor ) );
	//실감형 색체 알고리즘
	container.add( new Sidebar.NakAlgorithm( editor ) );	
	//변태/부식색 알고리즘
	container.add( new Sidebar.Corrosion( editor ) );
	container.add( new Sidebar.Object3D( editor ) );
	container.add( new Sidebar.Geometry( editor ) );
	container.add( new Sidebar.Material( editor ) );
	container.add( new Sidebar.Animation( editor ) );
	container.add( new Sidebar.Script( editor ) );

	return container;

};
