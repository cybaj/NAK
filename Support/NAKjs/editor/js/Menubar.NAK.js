/**
 * @author mrdoob / http://mrdoob.com/
 */

Menubar.NAK = function ( editor ) {

	var container = new UI.Panel();
	container.setClass( 'menu' );

	var title = new UI.Panel();
	title.setClass( 'title' );
	title.setTextContent( '[NAK]' );
	container.add( title );

	var options = new UI.Panel();
	options.setClass( 'options' );
	container.add( options );
	
	return container;

};
