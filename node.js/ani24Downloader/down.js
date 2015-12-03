var http = require( 'http' )

var fs = require('fs');


exports.downFile = function downFile( fileName, url, callback )
{
    var file = fs.createWriteStream( fileName );
    var request = http.get( url, function(response) {
        response.pipe(file);

        var fileSize = parseInt( response.headers['content-length'], 10 ); 
        var currSize = 0;
        var prevPercent = 0;
        var currPercent = 0;

        response.on( 'data', function( chunk )
        {
            currSize += chunk.length;
            
            currPercent = 100.0 * currSize / fileSize;

            if ( prevPercent + 1 <= currPercent )
            {
                process.stdout.write('Progress: '+ currPercent + " % Complete" + '\r');
                prevPercent = currPercent;
            }

        });

        response.on('end', function() {
            callback();
        });
    });
}

