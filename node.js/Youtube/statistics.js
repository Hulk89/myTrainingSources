var https = require( 'https' );
var url = require( 'url' );

var query = 'https://www.googleapis.com/youtube/v3/videos?part=statistics&id=' + process.argv[2] + '&key=AIzaSyBNkwK9qzmYzdRvq7Qd2fF_FnA2mvkYu-U';

function getNumber( res ) {
    var str = '';

    res.setEncoding('utf8');
    
    res.on( 'data', function( chunk ) {
        str += chunk;
    });

    res.on( 'end', function() {
      var obj = JSON.parse( str );
      var viewCount = obj['items'][0]['statistics']['viewCount'];

      console.log( viewCount );
       
    });
}

var options = url.parse( query );

https.get( options, getNumber ).end();