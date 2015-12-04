var http = require( 'http' );
var fs = require('fs');

exports.downFile = function downFile( fileName, url, callback )
{
    var file = fs.createWriteStream( fileName );

    console.log( "downFileName : " + fileName );

    var request = http.get( url, function(response) {
        response.pipe(file);

        var fileSize = parseInt( response.headers['content-length'], 10 );
        var currSize = 0;
        var prevPercent = 0;
        var currPercent = 0;

        response.on( 'data', function( chunk ) // update Progress
        {
            currSize += chunk.length;
            currPercent = Math.round( 100.0 * currSize / fileSize );

            if ( prevPercent + 1 <= currPercent )
            {
                process.stdout.write( '\rProgress : '+ currPercent + " %" ); // '\r'은 커서를 맨 앞으로 보낸다.
                prevPercent = currPercent;
            }
        });

        response.on('end', function() {
            process.stdout.write( '\rProgress : COMPLETE!!\n' );
            callback();                                                     // 모두 끝나면 callback을 호출하게 되어있다.
        });
    });
}
