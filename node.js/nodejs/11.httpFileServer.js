var http = require( 'http' );
var fs   = require( 'fs' );


function onRequest( request, response )
{
    var stream = fs.createReadStream( process.argv[3] );

    stream.pipe(response);
    // response.end(); 이거 있으면 안되네...ㅅㅂ
}

var server = http.createServer( onRequest );

server.listen(process.argv[2]);
