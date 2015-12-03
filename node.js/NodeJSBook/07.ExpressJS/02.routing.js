var http = require( 'http' );
/* routing�� �߰��غ���. server�� request.url�� ���� ������ routing�� ���ش�.
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
