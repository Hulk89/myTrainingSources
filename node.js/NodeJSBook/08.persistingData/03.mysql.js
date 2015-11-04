var mysql = require('mysql');

var connInfo = { host : '127.0.0.1',
                 user : 'root'}; // connection info를 적당히 세팅.

var connection = mysql.createConnection( connInfo ); 

connection.connect();

connection.query( 'SELECT "Hello, world!!"', 
                  function( err, results, fields )
{
    if ( err )
        throw err;
    console.log( results );
    console.log( fields );
});

connection.end();
