var mod = require( './readDir' );

var dir       = process.argv[2];
var extension = process.argv[3];

mod( dir, 
     extension, 
     function ( err, list ) 
     {
        if ( err )
        {
            return console.error('There was an error:', err)
        }

        list.forEach( 
            function(file)
            {
                console.log( file );
            } );   
     } );

