var connect = require( 'connect' );
var http = require( 'http' );

var app = connect();

/* Logging middleware
 * Logging이 끝나고 next를 호출하여 다음 function으로 넘긴다.
 */
function logging( req, res, next ){
    console.log( "In comes a " + req.method + " to " + req.url );
    next();
}
app.use( logging );

/* 하위 함수를 호출하고 next가 존재하지 않기 때문에 종료되겠지... 
 *
 */
app.use( function( req, res ){
    res.writeHead( 200, {"content-type": "text/plain" } );
    res.end( "Hello world!" );
});

http.createServer( app ).listen( 4000 );
