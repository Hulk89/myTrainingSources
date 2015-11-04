var http = require( 'http' );


function onRequest( request, response )
{
    response.writeHead( 200, { 'Content-Type': 'text/plain' } );
    response.end("Hello World\n");
    console.dir( request );
    //console.dir( response );
}

var server = http.createServer( onRequest );

server.listen(8080);

console.log( "Server has been started... " );
