var fs   = require( 'fs' );
var path = require( 'path' );

var extension = process.argv[3];

fs.readdir( process.argv[2], 
            function ( err, list ) 
            {
                //console.log( list );
                for ( var i = 0 ; i < list.length ; i++ )
                {
                    if ( path.extname( list[i] ) === ( '.' + extension ) )
                    {
                        console.log( list[i] );
                    }
                    else
                    {
                        /* Nothing to do */
                    }
                }
            }
            );
/*
var fs = require('fs')
var path = require('path')

fs.readdir( process.argv[2], 
            function (err, list) {
                list.forEach(function (file) 
                {
                    if (path.extname(file) === '.' + process.argv[3])
                        console.log(file)
                } )
            } )
*/

