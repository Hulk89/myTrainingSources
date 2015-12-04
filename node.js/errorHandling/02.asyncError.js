try{
    setTimeout( function() {
        throw new Error('test');
    }, 2000 );
}
catch( exception ) {
    consolt.log( 'outer:' );
    console.log( exception );
}
console.log( 'final log' );
