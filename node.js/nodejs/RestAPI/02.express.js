var express = require( 'express' );
var app = express();

app.get( '/', function( req, res ) {
    res.send( "Hello Root!!\n" );
});

app.listen( 3001 );
console.log( "Listening port 3001 " );
