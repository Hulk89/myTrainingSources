var connect = require( 'connect' );
var morgan = require( 'morgan' );
var http = require( 'http' );

var app = connect();

//Logging middleware
app.use( morgan( 'combined' ) );

app.use( function( req, res, next ){
    if ( req.url == '/' )
    {
        res.writeHead( 200, {"content-type": "text/plain" } );
        res.end( "Root page!" );
    }
    else
    {
        next();
    }
});

app.use( function( req, res, next ){
    if ( req.url == '/about' )
    {
        res.writeHead( 200, {"content-type": "text/plain" } );
        res.end( "About page!" );
    }
    else
    {
        next()
    }
});

app.use( function( req, res ){
    res.writeHead( 404, {"content-type": "text/plain" } );
    res.end( "Page not found!" );
});
http.createServer( app ).listen( 4000 );
