var express = require('express');
var fs      = require( 'fs' );
var url     = require( 'url' );
var proj4   = require( 'proj4');

var app = express();

app.get('/', function (req, res) {
  res.writeHead( 200, {"Content-type" : "text/html" } );
  var buffer = fs.readFileSync( "skgps.html", "utf8" );
  res.write( buffer );
  res.end();

});

app.get('/map', function (req, res) {
  var parsed = url.parse( req.url, true );
  	console.log( parsed );
  var lati = parsed.query.lati;
  var longi = parsed.query.longi;
	//console.log( "lati : " + lati );
	//console.log( "longi : " + longi );
  res.writeHead( 200, {"Content-type" : "text/html" } );

  var result = proj4( proj4.defs["WGS84"], proj4.defs["EPSG:3857"], [ longi, lati] );
	//console.log( result );
  var x = result[0];
  var y = result[1];

  var buffer = fs.readFileSync( "skgps.html", "utf8" );

  var str = buffer.toString();
  str = str.replace( /STARTX/g, x );
  str = str.replace( /STARTY/g, y );
	//console.log( str );
  res.write( str );
  res.end();
});

/*app.get('/map', function (req, res) {
  var parsed = url.parse( req.url, true );
  	console.log( parsed );
  var lati = parsed.query.lati;
  var longi = parsed.query.longi;
	console.log( "lati : " + lati );
	console.log( "longi : " + longi );
  res.writeHead( 200, {"Content-type" : "text/html" } );

  var buffer = fs.readFileSync( "gps.html", "utf8" );

  var str = buffer.toString();
  str = str.replace( /LATITUDE/g, lati );
  str = str.replace( /LONGITUDE/g, longi );
	console.log( str );
  res.write( str );
  res.end();
});
*/

var server = app.listen(3000, function () {
  var host = server.address().address;
  var port = server.address().port;

  console.log('Example app listening at http://%s:%s', host, port);
});
