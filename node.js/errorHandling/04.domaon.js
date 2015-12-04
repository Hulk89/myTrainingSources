var domain = require('domain').create();

domain.on('error', function ( err ) {
    console.log( 'error: ' + err );
    console.log( err.stack );
});

domain.run( function() {
    try {
        setTimeout( function() {
            throw new Error('test' );
        }, 2000 );
    }
    catch ( exception ){
        console.log( 'Outer: ' );
        console.log(  exception );
    }
});
setTimeout( function(){ console.log('GG')}, 3000 );
