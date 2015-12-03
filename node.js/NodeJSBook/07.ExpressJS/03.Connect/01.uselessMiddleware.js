var connect = require( 'connect' );

function uselessMiddleWare( req, res, next )
{
    next( "Hey, are you busy?" );
}

var app = connect();
app.use( '/about', uselessMiddleWare );

var server = app.listen( 4000 );

