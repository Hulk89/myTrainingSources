var net = require( 'net' );

function pad( n ) 
{ 
    return n < 10 ? '0' + n : n 
}

function getDate( date )
{
    return date.getFullYear()           + '-' + 
           pad( date.getMonth() + 1 )   + '-' + 
           pad( date.getDate() )        + ' ' + 
           pad( date.getHours() )       + ':' + 
           pad( date.getMinutes() );
}
net.createServer( function (socket) {
        var date = new Date();
        socket.write( getDate(date) );
        socket.end('\n');
    } ).listen(process.argv[2]);
