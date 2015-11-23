/**
 * @author mrdoob / http://mrdoob.com/
 */

Menubar.Help = function ( editor ) {

	var container = new UI.Panel();
	container.setClass( 'menu' );

	var title = new UI.Panel();
	title.setClass( 'title' );
	title.setTextContent( '도움말' );
	container.add( title );

	var options = new UI.Panel();
	options.setClass( 'options' );
	container.add( options );

	// About

	var option = new UI.Panel();
	option.setClass( 'option' );
	option.setTextContent( 'NAK 이란?' );
	option.onClick( function () {

		window.open( 'http://www.snut.ac.kr/', '_blank' );

	} );
	options.add( option );

	return container;

};
