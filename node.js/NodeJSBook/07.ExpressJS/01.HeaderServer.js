var http = require( 'http' );

/* request�� ������ body�� �Ἥ �������� ����.
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

