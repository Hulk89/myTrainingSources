process.on( 'uncaughtException', function ( err ) {
    console.log( 'unCaughtException: ' + err );
    console.log( err.stack );
});


try{
    setTimeout( function() {
        throw new Error('test');
    }, 2000 );
}
catch( exception ) {
    consolt.log( 'outer:' );
    console.log( exception );
}
setTimeout( function(){
    console.log( 'final log' );
}, 4000 );
