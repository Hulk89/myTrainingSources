var http = require( 'http' );

/* request의 정보를 body에 써서 내보내는 서버.
 */
http.createServer( function( req, res )
    {
        var answer = "";
        answer += "Request URL     : " + req.url + "\n";
        answer += "Request type    : " + req.method + "\n";
        answer += "Request headers : " + JSON.stringify( req.headers ) + "\n";

        res.writeHead( 200, { 'Content-Type' : 'text/plain' } );
        res.end( 'Body\n\n' + answer );
    }).listen( 4000, '127.0.0.1' );

