var fs = require('fs');

var buffer = fs.readFileSync( process.argv[2], 'utf8' );

var string = buffer.toString();

var lineArr = string.split('\n');

console.log( lineArr.length - 1 );
