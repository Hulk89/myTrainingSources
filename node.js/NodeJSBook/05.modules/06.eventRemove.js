var eventHandler1 = function(){
    console.log( 'EXIT1' );
}
var eventHandler2 = function(){
    console.log( 'EXIT2' );
}
process.on('exit', eventHandler1 );
process.on('exit', eventHandler2 );
process.removeListener('exit', eventHandler2 );
