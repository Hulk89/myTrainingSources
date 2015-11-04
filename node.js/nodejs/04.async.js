var fs = require('fs');

function readComplete( err, data )
{
    var buffer = data;    

    var string = buffer.toString();

    var lineArr = string.split('\n');

    console.log( lineArr.length - 1 );
}

fs.readFile( process.argv[2], readComplete );

console.log( "Hello world" );
