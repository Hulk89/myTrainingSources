var express = require('express')
var app = express()

app.get( '/home', function(req,res) {
    res.writeHead( 200, { 'Content-Type': 'text/html' } );
    res.write( 'Hello World!' );
    res.end();
}).listen(process.argv[2]);
