/**
 * Module dependencies.
 */
 
var express = require('express');
//var routes = require('./routes');
var http = require('http');
var path = require('path');
var fs   = require('fs');

var app = express();
app.use(express.static(path.join(__dirname, 'public')));


app.get( '/client', function ( req, res ) {
    var buffer = fs.readFileSync( "client.html", "utf8" );
    res.end( buffer );
});

var httpServer =http.createServer(app).listen(8080, function(req,res){
  console.log('Socket IO server has been started');
});

// upgrade http server to socket.io server
var io = require('socket.io').listen(httpServer);
 
io.sockets.on('connection',function(socket){
   socket.emit('toclient',{msg:'Welcome !'});
   socket.on('fromclient',function(data){
       socket.broadcast.emit('toclient',data); 
       socket.emit('toclient',data); 
       console.log('Message from client :'+data.msg);
   })
});
