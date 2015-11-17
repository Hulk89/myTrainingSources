var express = require( 'express' );
var app = express();

app.get( "/", function( req, res ) {
    res.writeHead( 200, { "content-type": "text/plain" } );
    res.end( "Root page!" );
});
app.get( "/about", function( req, res ) {
    res.writeHead( 200, { "content-type": "text/plain" } );
    res.end( "About page!" );
});
app.get( "/hi/:user", function( req, res ) {
    res.writeHead( 200, { "content-type": "text/plain" } );
    res.end( "Hi, " + req.params.user + "." );
});
app.get( "*", function( req, res ) {
    res.redirect( 'http://www.naver.com' );
});


app.listen( 4000 );

// http://expressjs.com/api.html
