/**
 * @author mrdoob / http://mrdoob.com/
 */

var Loader = function ( editor ) {

	var scope = this;
	var signals = editor.signals;

	this.texturePath = '';

	this.loadFile = function ( file ) {

		var filename = file.name;
		var extension = filename.split( '.' ).pop().toLowerCase();

		switch ( extension ) {

			case 'amf':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var loader = new THREE.AMFLoader();
					var amfobject = loader.parse( event.target.result );

					editor.addObject( amfobject );
					editor.select( amfobject );

				}, false );
				reader.readAsArrayBuffer( file );

				break;

			case 'awd':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var loader = new THREE.AWDLoader();
					var scene = loader.parse( event.target.result );

					editor.setScene( scene );

				}, false );
				reader.readAsArrayBuffer( file );

				break;

			case 'babylon':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var contents = event.target.result;
					var json = JSON.parse( contents );

					var loader = new THREE.BabylonLoader();
					var scene = loader.parse( json );

					editor.setScene( scene );

				}, false );
				reader.readAsText( file );

				break;

			case 'babylonmeshdata':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var contents = event.target.result;
					var json = JSON.parse( contents );

					var loader = new THREE.BabylonLoader();

					var geometry = loader.parseGeometry( json );
					var material = new THREE.MeshPhongMaterial();

					var mesh = new THREE.Mesh( geometry, material );
					mesh.name = filename;

					editor.addObject( mesh );
					editor.select( mesh );

				}, false );
				reader.readAsText( file );

				break;

			case 'ctm':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var data = new Uint8Array( event.target.result );

					var stream = new CTM.Stream( data );
					stream.offset = 0;

					var loader = new THREE.CTMLoader();
					loader.createModel( new CTM.File( stream ), function( geometry ) {

						geometry.sourceType = "ctm";
						geometry.sourceFile = file.name;

						var material = new THREE.MeshPhongMaterial();

						var mesh = new THREE.Mesh( geometry, material );
						mesh.name = filename;

						editor.addObject( mesh );
						editor.select( mesh );

					} );

				}, false );
				reader.readAsArrayBuffer( file );

				break;

			case 'dae':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) 
				{

					var contents = event.target.result;

					var loader = new THREE.ColladaLoader();
					var collada = loader.parse( contents );

					collada.scene.name = filename;

					editor.addObject( collada.scene );
					editor.select( collada.scene );

				}, false );
				reader.readAsText( file );

				break;

			//triangle
			case 'tjson':
				var reader = new FileReader();
				//reader.readAsBinaryString(file);
				reader.addEventListener( 'load', function ( event ){
					var meshDataList = JSON.parse(event.target.result);
					var len = meshDataList.length;
					for (var meshIdx = 0; meshIdx < len; meshIdx++) 
					{
						var meshData = meshDataList[meshIdx];
						var geometry = new THREE.Geometry();
						var vertexArray = [];

						//uncompress vertices array
						for (var i = 0; i < meshData.VertexIndices.length; i += 1) 
						{
							var idx = 3 * meshData.VertexIndices[i];
							vertexArray[i] = new THREE.Vector3(
								meshData.VertexCoords[idx],
								meshData.VertexCoords[idx + 1],
								meshData.VertexCoords[idx + 2]);
						}
						var normalArray = [];
						var colorArray = [];

						//uncompress normals array
						for (var i = 0; i < meshData.NormalIndices.length; i += 1) 
						{
							var idx = 3 * meshData.NormalIndices[i];
							normalArray[i] = new THREE.Vector3(
								meshData.Normals[idx],
								meshData.Normals[idx + 1],
								meshData.Normals[idx + 2]);
						}

						//Generate Faces
						for (var i = 0; i < vertexArray.length; i += 3) 
						{
							geometry.vertices.push(vertexArray[i]);
							geometry.vertices.push(vertexArray[i + 1]);
							geometry.vertices.push(vertexArray[i + 2]);

							var face = new THREE.Face3(i, i + 1, i + 2)
							//face.materialIndex = meshData.ColorIndices[i];				
							geometry.faces.push(face);
							
							
							var bytes = [];
							var clr = meshData.Colors[meshData.ColorIndices[i/3]];
							bytes[0] = (clr >>> 24) & 0xFF; //R
							bytes[1] = (clr >>> 16) & 0xFF; //G
							bytes[2] = (clr >>> 8) & 0xFF;  //B
							bytes[3] = (clr >>> 0) & 0xFF;  //A
		
							var rgb = bytes[2] | (bytes[1] << 8) | (bytes[0] << 16);
							face.color = new THREE.Color(rgb);
							
							face.vertexNormals.push(normalArray[i]);
							face.vertexNormals.push(normalArray[i + 1]);
							face.vertexNormals.push(normalArray[i + 2]);
						}

						//center[0] += meshData.Center[0];
						//center[1] += meshData.Center[1];
						//center[2] += meshData.Center[2];

						//색상정보를 구해온다.
						// this material causes a mesh to use colors assigned to faces
						var material_4 = new THREE.MeshPhongMaterial( 
						{ color: 0xffffff, vertexColors: THREE.FaceColors } );
			
						var materials = [];
						for( var i=0; i < meshData.Colors.length; i+= 1)
						{
							var material = new THREE.MeshBasicMaterial(
								{
									color : meshData.Colors[i],
									shading: THREE.FlatShading,
									overdraw: true
								}
							);
							materials.push(material);
						}	
						geometry.materials = materials;
						geometry.computeFaceNormals();
						//============
						var mesh = new THREE.Mesh(geometry, material_4);//
						mesh.name = filename + "_t";
												
						editor.addObject( mesh );
						editor.select( mesh );
					}					
					
				}, false );
				reader.readAsText(file);
				break;
			case 'vjson':
				var reader = new FileReader();
				//reader.readAsBinaryString(file);
				reader.addEventListener( 'load', function ( event ){	
					var meshDataList = JSON.parse(event.target.result);
					var len = meshDataList.length;
					for (var meshIdx = 0; meshIdx < len; meshIdx++) 
					{
						var meshData = meshDataList[meshIdx];
						var geometry = new THREE.Geometry();
						var vertexArray = [];

						//uncompress vertices array
						for (var i = 0; i < meshData.VertexIndices.length; i += 1) {
							var idx = 3 * meshData.VertexIndices[i];
							vertexArray[i] = new THREE.Vector3(
								meshData.VertexCoords[idx],
								meshData.VertexCoords[idx + 1],
								meshData.VertexCoords[idx + 2]);
						}
						var normalArray = [];
						var colorArray = [];
						
						//uncompress normals array
						for (var i = 0; i < meshData.NormalIndices.length; i += 1) {
							var idx = 3 * meshData.NormalIndices[i];
							normalArray[i] = new THREE.Vector3(
								meshData.Normals[idx],
								meshData.Normals[idx + 1],
								meshData.Normals[idx + 2]);
						}
						//Generate Faces
						for (var i = 0; i < vertexArray.length; i += 3) 
						{
							geometry.vertices.push(vertexArray[i]);
							geometry.vertices.push(vertexArray[i + 1]);
							geometry.vertices.push(vertexArray[i + 2]);

							var face = new THREE.Face3(i, i + 1, i + 2)
							//face.materialIndex = meshData.ColorIndices[i];				
							geometry.faces.push(face);
							
							var bytes = [];
							var clr;

							clr = meshData.Colors[meshData.ColorIndices[i]];
							bytes[0] = (clr >>> 24) & 0xFF; //R
							bytes[1] = (clr >>> 16) & 0xFF; //G
							bytes[2] = (clr >>> 8) & 0xFF;  //B
							bytes[3] = (clr >>> 0) & 0xFF;  //A
							var rgb1 = bytes[2] | (bytes[1] << 8) | (bytes[0] << 16);
							
							clr = meshData.Colors[meshData.ColorIndices[i+1]];
							bytes[0] = (clr >>> 24) & 0xFF; //R
							bytes[1] = (clr >>> 16) & 0xFF; //G
							bytes[2] = (clr >>> 8) & 0xFF;  //B
							bytes[3] = (clr >>> 0) & 0xFF;  //A
							var rgb2 = bytes[2] | (bytes[1] << 8) | (bytes[0] << 16);
							
							clr = meshData.Colors[meshData.ColorIndices[i+2]];
							bytes[0] = (clr >>> 24) & 0xFF; //R
							bytes[1] = (clr >>> 16) & 0xFF; //G
							bytes[2] = (clr >>> 8) & 0xFF;  //B
							bytes[3] = (clr >>> 0) & 0xFF;  //A
							var rgb3 = bytes[2] | (bytes[1] << 8) | (bytes[0] << 16);
							
							face.vertexColors.push(new THREE.Color(rgb1));
							face.vertexColors.push(new THREE.Color(rgb2));
							face.vertexColors.push(new THREE.Color(rgb3));
							
							face.vertexNormals.push(normalArray[i]);
							face.vertexNormals.push(normalArray[i + 1]);
							face.vertexNormals.push(normalArray[i + 2]);
						}

						//center[0] += meshData.Center[0];
						//center[1] += meshData.Center[1];
						//center[2] += meshData.Center[2];

						//색상정보를 구해온다.
						// this material causes a mesh to use colors assigned to faces
						var material_4 = new THREE.MeshPhongMaterial( 
						{ color: 0xffffff, vertexColors: THREE.VertexColors } );
			
						var materials = [];
						for( var i=0; i < meshData.Colors.length; i+= 1)
						{
							var material = new THREE.MeshBasicMaterial(
								{
									color : meshData.Colors[i],
									shading: THREE.FlatShading,
									overdraw: true
								}
							);
							materials.push(material);
						}	
						geometry.materials = materials;
						geometry.computeFaceNormals();
						//============
						var mesh = new THREE.Mesh(geometry, material_4);
						mesh.name = filename + "_v";
						editor.addObject( mesh );
						editor.select( mesh );
					}					
					
				}, false );
				reader.readAsText(file);
				break;				
			case 'js':
			case 'json':
			case '3geo':
			case '3mat':
			case '3obj':
			case '3scn':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var contents = event.target.result;

					// 2.0

					if ( contents.indexOf( 'postMessage' ) !== -1 ) {

						var blob = new Blob( [ contents ], { type: 'text/javascript' } );
						var url = URL.createObjectURL( blob );

						var worker = new Worker( url );

						worker.onmessage = function ( event ) {

							event.data.metadata = { version: 2 };
							handleJSON( event.data, file, filename );

						};

						worker.postMessage( Date.now() );

						return;

					}

					// >= 3.0

					var data;

					try {

						data = JSON.parse( contents );

					} catch ( error ) {

						alert( error );
						return;

					}

					handleJSON( data, file, filename );

				}, false );
				reader.readAsText( file );

				break;


				case 'kmz':

					var reader = new FileReader();
					reader.addEventListener( 'load', function ( event ) {

						var loader = new THREE.KMZLoader();
						var collada = loader.parse( event.target.result );

						collada.scene.name = filename;

						editor.addObject( collada.scene );
						editor.select( collada.scene );

					}, false );
					reader.readAsArrayBuffer( file );

					break;

				case 'md2':

					var reader = new FileReader();
					reader.addEventListener( 'load', function ( event ) {

						var contents = event.target.result;

						var geometry = new THREE.MD2Loader().parse( contents );
						var material = new THREE.MeshPhongMaterial( {
							morphTargets: true,
							morphNormals: true
						} );

						var mesh = new THREE.Mesh( geometry, material );
						mesh.mixer = new THREE.AnimationMixer( mesh )
						mesh.name = filename;

						editor.addObject( mesh );
						editor.select( mesh );

					}, false );
					reader.readAsArrayBuffer( file );

					break;

			case 'obj':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var contents = event.target.result;

					var object = new THREE.OBJLoader().parse( contents );
					object.name = filename;

					editor.addObject( object );
					editor.select( object );

				}, false );
				reader.readAsText( file );

				break;

			case 'ply':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var contents = event.target.result;

					var geometry = new THREE.PLYLoader().parse( contents );
					geometry.sourceType = "ply";
					geometry.sourceFile = file.name;

					var material = new THREE.MeshPhongMaterial();

					var mesh = new THREE.Mesh( geometry, material );
					mesh.name = filename;

					editor.addObject( mesh );
					editor.select( mesh );

				}, false );
				reader.readAsText( file );

				break;

			case 'stl':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var contents = event.target.result;

					var geometry = new THREE.STLLoader().parse( contents );
					geometry.sourceType = "stl";
					geometry.sourceFile = file.name;

					var material = new THREE.MeshPhongMaterial();

					var mesh = new THREE.Mesh( geometry, material );
					mesh.name = filename;

					editor.addObject( mesh );
					editor.select( mesh );

				}, false );

				if ( reader.readAsBinaryString !== undefined ) {

					reader.readAsBinaryString( file );

				} else {

					reader.readAsArrayBuffer( file );

				}

				break;

			/*
			case 'utf8':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var contents = event.target.result;

					var geometry = new THREE.UTF8Loader().parse( contents );
					var material = new THREE.MeshLambertMaterial();

					var mesh = new THREE.Mesh( geometry, material );

					editor.addObject( mesh );
					editor.select( mesh );

				}, false );
				reader.readAsBinaryString( file );

				break;
			*/

			case 'vtk':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var contents = event.target.result;

					var geometry = new THREE.VTKLoader().parse( contents );
					geometry.sourceType = "vtk";
					geometry.sourceFile = file.name;

					var material = new THREE.MeshPhongMaterial();

					var mesh = new THREE.Mesh( geometry, material );
					mesh.name = filename;

					editor.addObject( mesh );
					editor.select( mesh );

				}, false );
				reader.readAsText( file );

				break;

			case 'wrl':

				var reader = new FileReader();
				reader.addEventListener( 'load', function ( event ) {

					var contents = event.target.result;

					var result = new THREE.VRMLLoader().parse( contents );

					editor.setScene( result );

				}, false );
				reader.readAsText( file );

				break;

			default:

				alert( 'Unsupported file format (' + extension +  ').' );

				break;

		}

	}

	var handleJSON = function ( data, file, filename ) {

		if ( data.metadata === undefined ) { // 2.0

			data.metadata = { type: 'Geometry' };

		}

		if ( data.metadata.type === undefined ) { // 3.0

			data.metadata.type = 'Geometry';

		}

		if ( data.metadata.version === undefined ) {

			data.metadata.version = data.metadata.formatVersion;

		}

		if ( data.metadata.type === 'BufferGeometry' ) {

			var loader = new THREE.BufferGeometryLoader();
			var result = loader.parse( data );

			var mesh = new THREE.Mesh( result );

			editor.addObject( mesh );
			editor.select( mesh );

		} else if ( data.metadata.type.toLowerCase() === 'geometry' ) {

			var loader = new THREE.JSONLoader();
			loader.setTexturePath( scope.texturePath );

			var result = loader.parse( data );

			var geometry = result.geometry;
			var material;

			if ( result.materials !== undefined ) {

				if ( result.materials.length > 1 ) {

					material = new THREE.MeshFaceMaterial( result.materials );

				} else {

					material = result.materials[ 0 ];

				}

			} else {

				material = new THREE.MeshPhongMaterial();

			}

			geometry.sourceType = "ascii";
			geometry.sourceFile = file.name;

			var mesh;

			if ( geometry.animation && geometry.animation.hierarchy ) {

				mesh = new THREE.SkinnedMesh( geometry, material );

			} else {

				mesh = new THREE.Mesh( geometry, material );

			}

			mesh.name = filename;

			editor.addObject( mesh );
			editor.select( mesh );

		} else if ( data.metadata.type.toLowerCase() === 'object' ) {

			var loader = new THREE.ObjectLoader();
			loader.setTexturePath( scope.texturePath );

			var result = loader.parse( data );

			if ( result instanceof THREE.Scene ) {

				editor.setScene( result );

			} else {

				editor.addObject( result );
				editor.select( result );

			}

		} else if ( data.metadata.type.toLowerCase() === 'scene' ) {

			// DEPRECATED

			var loader = new THREE.SceneLoader();
			loader.parse( data, function ( result ) {

				editor.setScene( result.scene );

			}, '' );

		}

	};

}
