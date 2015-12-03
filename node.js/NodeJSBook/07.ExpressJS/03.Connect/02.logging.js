var connect = require( 'connect' );
var http = require( 'http' );

var app = connect();

/* Logging middleware
 * Logging�� ������ next�� ȣ���Ͽ� ���� function���� �ѱ��.
 */
function logging( req, res, next ){
    console.log( "In comes a " + req.method + " to " + req.url );
    next();
}
app.use( logging );

/* ���� �Լ��� ȣ���ϰ� next�� �������� �ʱ� ������ ����ǰ���... 
 *
 */
app.use( function( req, res ){
    res.writeHead( 200, {"content-type": "text/plain" } );
    res.end( "Hello world!" );
});

http.createServer( app ).listen( 4000 );
