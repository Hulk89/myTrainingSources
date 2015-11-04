var mysql = require('mysql');

var connInfo = { host : '127.0.0.1',
                 user : 'root'}; // connection info를 적당히 세팅.

var connection = mysql.createConnection( connInfo ); 

connection.connect();

connection.query( 'CREATE DATABASE nodejs', 
                  function( err, results, fields )
{
    if ( err )
        throw err;
});

connection.query('USE nodejs');

connection.query('CREATE TABLE family ( id INT(3) AUTO_INCREMENT, name VARCHAR(20), PRIMARY KEY(id) )' );

connection.query('INSERT INTO family (name) VALUES (?)', "Chris" );
connection.query('INSERT INTO family (name) VALUES (?)', "Jihee" );
connection.query('INSERT INTO family (name) VALUES (?)', "Anna" );
connection.query('INSERT INTO family (name) VALUES (?)', "Shinhoo" );

connection.query( 'SELECT * FROM family', 
                  function( err, results, fields )
{
    if ( err )
        throw err;
    console.log( results );
    console.log( fields );
});


connection.end();
