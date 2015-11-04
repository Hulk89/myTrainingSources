var http = require('http');
var bl = require('bl');

var count = 0;
var buffer = [];

function printAll()
{
    buffer.forEach( function ( data ) {
                    console.log( data );
                    });
}

function getHTTP( index )
{
  http.get( process.argv[index + 2], function (response) {
              response.setEncoding('utf8')
              response.pipe( bl( function (err, data) {
                if ( err )
                    return console.error( "error : " + err );
                buffer[index]  = data.toString();
                count++;
                if ( count === 3 )
                    printAll();
              }))
          })

}



for ( var i = 0 ; i < 3 ; i++ )
{
    getHTTP( i ); 
}
