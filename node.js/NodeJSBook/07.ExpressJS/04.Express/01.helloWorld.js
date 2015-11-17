var express = require( 'express' );
var app = express();

// ��� �Լ��� �� �ڵ带 ���� ź��.
app.all( "*", function( req, res, next ) {
    res.writeHead( 200, { "content-type": "text/plain" } );
    next();
});

app.get( "/", function( req, res ) {
    res.end( "Root page!" );
});
app.get( "/about", function( req, res ) {
    res.end( "About page!" );
});
app.get( "/hi/:user", function( req, res ) {
    res.end( "Hi, " + req.params.user + "." );
});
app.get( "*", function( req, res ) {
    res.end( "404!" );
});


app.listen( 4000 );

// http://expressjs.com/api.html#app.VERB
