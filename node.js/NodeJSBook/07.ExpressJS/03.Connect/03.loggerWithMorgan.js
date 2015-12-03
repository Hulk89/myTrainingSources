var connect = require( 'connect' );
var morgan = require( 'morgan' );
var http = require( 'http' );

var app = connect();

//Logging middleware
app.use( morgan( 'combined' ) );


app.use( function( req, res ){
    res.writeHead( 200, {"content-type": "text/plain" } );
    res.end( "Hello world!" );
});

http.createServer( app ).listen( 4000 );
