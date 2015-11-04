var exitHandler = function(){
  console.log("EXIT");
};

var errHandler1 = function(err){
  console.log( "err1", err );
};

var errHandler2 = function(err){
  console.log( "err2", err );
};

process.on('exit',exitHandler);

process.on('uncaughtException', errHandler1 );
process.on('uncaughtException', errHandler2 );
process.on('test', function(err){
  console.log('GG' + err );
});
process.removeListener('uncaughtException', errHandler2 );
//process.removeAllListeners('uncaughtException');
process.emit('test',"히히");
//error

