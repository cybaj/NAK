/**
 * @author mrdoob / http://mrdoob.com/
 */

var Viewport = function ( editor ) {

	var signals = editor.signals;

	var container = new UI.Panel();
	container.setId( 'viewport' );
	container.setPosition( 'absolute' );

	container.add( new Viewport.Info( editor ) );

	var scene = editor.scene;
	var sceneHelpers = editor.sceneHelpers;

	var objects = [];

	// helpers

	var grid = new THREE.GridHelper( 500, 25 );
	sceneHelpers.add( grid );

	//

	var camera = editor.camera;

	//

	var selectionBox = new THREE.BoxHelper();
	selectionBox.material.depthTest = false;
	selectionBox.material.transparent = true;
	selectionBox.visible = false;
	sceneHelpers.add( selectionBox );

	var matrix = new THREE.Matrix4();

	var transformControls = new THREE.TransformControls( camera, container.dom );
	transformControls.addEventListener( 'change', function () {

		var object = transformControls.object;

		if ( object !== undefined ) {

			selectionBox.update( object );

			if ( editor.helpers[ object.id ] !== undefined ) {

				editor.helpers[ object.id ].update();

			}

		}

		render();

	} );
	transformControls.addEventListener( 'mouseDown', function () {

		var object = transformControls.object;

		matrix.copy( object.matrix );

		controls.enabled = false;

	} );
	transformControls.addEventListener( 'mouseUp', function () {

		var object = transformControls.object;

		if ( matrix.equals( object.matrix ) === false ) {

			( function ( matrix1, matrix2 ) {

				editor.history.add(
					function () {
						matrix1.decompose( object.position, object.quaternion, object.scale );
						signals.objectChanged.dispatch( object );
					},
					function () {
						matrix2.decompose( object.position, object.quaternion, object.scale );
						signals.objectChanged.dispatch( object );
					}
				);

			} )( matrix.clone(), object.matrix.clone() );

		}

		signals.objectChanged.dispatch( object );
		controls.enabled = true;

	} );

	sceneHelpers.add( transformControls );

	// fog

	var oldFogType = "None";
	var oldFogColor = 0xaaaaaa;
	var oldFogNear = 1;
	var oldFogFar = 5000;
	var oldFogDensity = 0.00025;

	// object picking

	var raycaster = new THREE.Raycaster();
	var mouse = new THREE.Vector2();

	// events

	function getIntersects( point, objects ) {

		mouse.set( ( point.x * 2 ) - 1, - ( point.y * 2 ) + 1 );

		raycaster.setFromCamera( mouse, camera );

		return raycaster.intersectObjects( objects );

	};

	var onDownPosition = new THREE.Vector2();
	var onUpPosition = new THREE.Vector2();
	var onDoubleClickPosition = new THREE.Vector2();

	function getMousePosition( dom, x, y ) {

		var rect = dom.getBoundingClientRect();
		return [ ( x - rect.left ) / rect.width, ( y - rect.top ) / rect.height ];

	};
	
	/**
	* addLine
	*/
	function addLine(group, pt1, pt2, clr)
	{
		var geometry = new THREE.Geometry();
		geometry.vertices.push( pt1 );
		geometry.vertices.push( pt2 );
		var line = new THREE.Line( geometry, new THREE.LineBasicMaterial( { color: clr } ) );
		line.name = "line"
		group.children.push( line );
	}
	
	function handleClick() {

		if ( onDownPosition.distanceTo( onUpPosition ) == 0 ) {

			var intersects = getIntersects( onUpPosition, objects );

			if ( intersects.length > 0 ) 
			{
				for( var i =0; i < intersects.length; i++)
				{
					var object = intersects[ i ].object;
					//
					//{{! sunghan : 선택된 면의 normal, view direction을 가시화 함
					if(editor.selected!==null && object.type==="Mesh" && object.name !== "picker")
					{				
						var normalLength = 10;
						var face = intersects[ i ].face;
						var centroid = new THREE.Vector3();
						var geometry = object.geometry;
						var pt1,pt2,pt3;
						if(geometry.vertices!==undefined)
						{
							pt1 = geometry.vertices[ face.a ];
							pt2 = geometry.vertices[ face.b ];
							pt3 = geometry.vertices[ face.c ];				
						}
						else if(geometry.attributes!==undefined)
						{
							pt1 = geometry.attributes.position.array[ face.a ];
							pt2 = geometry.attributes.position.array[ face.b ];
							pt3 = geometry.attributes.position.array[ face.c ];														
						}
						centroid 
							.add( pt1 )
							.add( pt2 )
							.add( pt3 )
							.divideScalar( 3 );
							
						// group object 생성
						var supportObj = new THREE.Group();
						supportObj.name = "Support";
						
						// triangle edge
						addLine(supportObj,pt1,pt2,0xffffff);
						addLine(supportObj,pt2,pt3,0xffffff); 
						addLine(supportObj,pt3,pt1,0xffffff);
						// normal direction
						var normalArrow = new THREE.ArrowHelper(
								face.normal,
								centroid,
								normalLength,
								0x3333FF );
						normalArrow.name = "Normal 방향";
						supportObj.children.push(normalArrow);
						// viewport direction
						var vector = new THREE.Vector3();
						vector.x = centroid.x - camera.position.x;
						vector.y = centroid.y - camera.position.y;
						vector.z = centroid.z - camera.position.z;	
						vector.normalize();
						supportObj.userData = [new THREE.Vector3(face.normal.x,face.normal.y,face.normal.z),
											   new THREE.Vector3(centroid.x,centroid.y,centroid.z)];
						var viewArrow = new THREE.ArrowHelper(
								vector,
								new THREE.Vector3(  centroid.x - (vector.x * normalLength),
													centroid.y - (vector.y * normalLength),
													centroid.z - (vector.z * normalLength)),
								normalLength,
								0xFF3333 );					
						viewArrow.name = "View 방향";
						supportObj.children.push(viewArrow);
						
						editor.addObject( supportObj );
						//editor.addObject( viewArrow );
					}
				}
				//}}

				if ( object.userData.object !== undefined ) {

					// helper

					editor.select( object.userData.object );

				} else {

					editor.select( object );
				}		

			} else {

				editor.select( null );

			}

			render();

		}

	};

	function onMouseDown( event ) {

		event.preventDefault();

		var array = getMousePosition( container.dom, event.clientX, event.clientY );
		onDownPosition.fromArray( array );

		document.addEventListener( 'mouseup', onMouseUp, false );

	};

	function onMouseUp( event ) {

		var array = getMousePosition( container.dom, event.clientX, event.clientY );
		onUpPosition.fromArray( array );

		handleClick();

		document.removeEventListener( 'mouseup', onMouseUp, false );

	};

	function onTouchStart( event ) {

		var touch = event.changedTouches[ 0 ];

		var array = getMousePosition( container.dom, touch.clientX, touch.clientY );
		onDownPosition.fromArray( array );

		document.addEventListener( 'touchend', onTouchEnd, false );

	};

	function onTouchEnd( event ) {

		var touch = event.changedTouches[ 0 ];

		var array = getMousePosition( container.dom, touch.clientX, touch.clientY );
		onUpPosition.fromArray( array );

		handleClick();

		document.removeEventListener( 'touchend', onTouchEnd, false );

	};

	function onDoubleClick( event ) {

		var array = getMousePosition( container.dom, event.clientX, event.clientY );
		onDoubleClickPosition.fromArray( array );

		var intersects = getIntersects( onDoubleClickPosition, objects );

		if ( intersects.length > 0 ) {

			var intersect = intersects[ 0 ];

			signals.objectFocused.dispatch( intersect.object );

		}

	};

	container.dom.addEventListener( 'mousedown', onMouseDown, false );
	container.dom.addEventListener( 'touchstart', onTouchStart, false );
	container.dom.addEventListener( 'dblclick', onDoubleClick, false );

	// controls need to be added *after* main logic,
	// otherwise controls.enabled doesn't work.

	var controls = new THREE.EditorControls( camera, container.dom );
	controls.addEventListener( 'change', function () {

		transformControls.update();
		signals.cameraChanged.dispatch( camera );

	} );

	// signals

	signals.editorCleared.add( function () {

		controls.center.set( 0, 0, 0 );
		render();

	} );

	var clearColor;

	signals.themeChanged.add( function ( value ) {

		switch ( value ) {

			case 'css/light.css':
				grid.setColors( 0x444444, 0x888888 );
				clearColor = 0xaaaaaa;
				break;
			case 'css/dark.css':
				grid.setColors( 0xbbbbbb, 0x888888 );
				clearColor = 0x333333;
				break;

		}

		renderer.setClearColor( clearColor );

		render();

	} );

	signals.transformModeChanged.add( function ( mode ) {

		transformControls.setMode( mode );

	} );

	signals.snapChanged.add( function ( dist ) {

		transformControls.setTranslationSnap( dist );

	} );

	signals.spaceChanged.add( function ( space ) {

		transformControls.setSpace( space );

	} );

	signals.rendererChanged.add( function ( newRenderer ) {

		if ( renderer !== null ) {

			container.dom.removeChild( renderer.domElement );

		}

		renderer = newRenderer;

		renderer.autoClear = false;
		renderer.autoUpdateScene = false;
		renderer.setClearColor( clearColor );
		renderer.setPixelRatio( window.devicePixelRatio );
		renderer.setSize( container.dom.offsetWidth, container.dom.offsetHeight );

		container.dom.appendChild( renderer.domElement );

		render();

	} );

	signals.sceneGraphChanged.add( function () {

		render();

	} );

	var saveTimeout;

	signals.cameraChanged.add( function () {

		render();

	} );

	signals.objectSelected.add( function ( object ) {

		selectionBox.visible = false;
		transformControls.detach();

		if ( object !== null ) {

			if ( object.geometry !== undefined &&
				 object instanceof THREE.Sprite === false ) {

				selectionBox.update( object );
				selectionBox.visible = true;

			}

			transformControls.attach( object );

		}

		render();

	} );

	signals.objectFocused.add( function ( object ) {

		controls.focus( object );

	} );

	signals.geometryChanged.add( function ( geometry ) {

		selectionBox.update( editor.selected );

		render();

	} );

	signals.objectAdded.add( function ( object ) {

		var materialsNeedUpdate = false;

		object.traverse( function ( child ) {

			if ( child instanceof THREE.Light ) materialsNeedUpdate = true;

			objects.push( child );

		} );

		if ( materialsNeedUpdate === true ) updateMaterials();

	} );

	signals.objectChanged.add( function ( object ) {

		selectionBox.update( object );
		transformControls.update();

		if ( object instanceof THREE.PerspectiveCamera ) {

			object.updateProjectionMatrix();

		}

		if ( editor.helpers[ object.id ] !== undefined ) {

			editor.helpers[ object.id ].update();

		}

		render();

	} );

	signals.objectRemoved.add( function ( object ) {

		var materialsNeedUpdate = false;

		object.traverse( function ( child ) {

			if ( child instanceof THREE.Light ) materialsNeedUpdate = true;

			objects.splice( objects.indexOf( child ), 1 );

		} );

		if ( materialsNeedUpdate === true ) updateMaterials();

	} );

	signals.helperAdded.add( function ( object ) {

		objects.push( object.getObjectByName( 'picker' ) );

	} );

	signals.helperRemoved.add( function ( object ) {

		objects.splice( objects.indexOf( object.getObjectByName( 'picker' ) ), 1 );

	} );

	signals.materialChanged.add( function ( material ) {

		render();

	} );

	signals.fogTypeChanged.add( function ( fogType ) {

		if ( fogType !== oldFogType ) {

			if ( fogType === "None" ) {

				scene.fog = null;

			} else if ( fogType === "Fog" ) {

				scene.fog = new THREE.Fog( oldFogColor, oldFogNear, oldFogFar );

			} else if ( fogType === "FogExp2" ) {

				scene.fog = new THREE.FogExp2( oldFogColor, oldFogDensity );

			}

			updateMaterials();

			oldFogType = fogType;

		}

		render();

	} );

	signals.fogColorChanged.add( function ( fogColor ) {

		oldFogColor = fogColor;

		updateFog( scene );

		render();

	} );

	signals.fogParametersChanged.add( function ( near, far, density ) {

		oldFogNear = near;
		oldFogFar = far;
		oldFogDensity = density;

		updateFog( scene );

		render();

	} );

	signals.windowResize.add( function () {

		camera.aspect = container.dom.offsetWidth / container.dom.offsetHeight;
		camera.updateProjectionMatrix();

		renderer.setSize( container.dom.offsetWidth, container.dom.offsetHeight );

		render();

	} );

	signals.showGridChanged.add( function ( showGrid ) {

		grid.visible = showGrid;
		render();

	} );

	//

	var renderer = null;

	animate();

	//

	function updateMaterials() {

		editor.scene.traverse( function ( node ) {

			if ( node.material ) {

				node.material.needsUpdate = true;

				if ( node.material instanceof THREE.MeshFaceMaterial ) {

					for ( var i = 0; i < node.material.materials.length; i ++ ) {

						node.material.materials[ i ].needsUpdate = true;

					}

				}

			}

		} );

	}

	function updateFog( root ) {

		if ( root.fog ) {

			root.fog.color.setHex( oldFogColor );

			if ( root.fog.near !== undefined ) root.fog.near = oldFogNear;
			if ( root.fog.far !== undefined ) root.fog.far = oldFogFar;
			if ( root.fog.density !== undefined ) root.fog.density = oldFogDensity;

		}

	}

	function animate() {

		requestAnimationFrame( animate );

		/*

		// animations

		if ( THREE.AnimationHandler.animations.length > 0 ) {

			THREE.AnimationHandler.update( 0.016 );

			for ( var i = 0, l = sceneHelpers.children.length; i < l; i ++ ) {

				var helper = sceneHelpers.children[ i ];

				if ( helper instanceof THREE.SkeletonHelper ) {

					helper.update();

				}

			}

			render();

		}

		*/

	}

	function render() {

		sceneHelpers.updateMatrixWorld();
		scene.updateMatrixWorld();

		renderer.clear();
		renderer.render( scene, camera );

		if ( renderer instanceof THREE.RaytracingRenderer === false ) {

			renderer.render( sceneHelpers, camera );

		}

	}

	return container;

}
