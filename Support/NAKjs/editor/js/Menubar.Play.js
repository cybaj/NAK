/**
 * @author mrdoob / http://mrdoob.com/
 */

Menubar.Play = function ( editor ) {

	var signals = editor.signals;

	var container = new UI.Panel();
	container.setClass( 'menu' );

	var isPlaying = false;

	var title = new UI.Panel();
	title.setClass( 'title' );
	title.setTextContent( '플레이' );
	title.onClick( function () {

		if ( isPlaying === false ) {

			isPlaying = true;
			title.setTextContent( '정지' );
			signals.startPlayer.dispatch();

		} else {

			isPlaying = false;
			title.setTextContent( '플레이' );
			signals.stopPlayer.dispatch();

		}

	} );
	container.add( title );

	return container;

};
