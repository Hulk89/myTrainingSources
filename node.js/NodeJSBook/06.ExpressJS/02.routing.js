var http = require( 'http' );
/* routing을 추가해본다. server의 request.url을 보고 적절히 routing을 해준다.
 */
http.createServer( function( req, res ) {
    if ( req.url == '/' )
    {
        res.writeHead( 200, { "content-type": "text/html" } );
        res.end( "Root dir!" );
    }
    else if ( req.url == '/about' )
    {
        res.writeHead( 200, { "content-type": "text/html" } );
        res.end( "About page" );
    }
    else
    {
        res.writeHead( 404, { "content-type": "text/html" } );
        res.end( "Page not found" );
    }
}).listen( 4000, '127.0.0.1' );
