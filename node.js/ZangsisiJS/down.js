var http = require( 'http' )

var fs = require('fs');


exports.downFile = function downFile( fileName, url, callback )
{
    var file = fs.createWriteStream( fileName );
    var request = http.get( url, function(response) {
        response.pipe(file);

        response.on('end', function() {
            callback();
        });
    });
}

