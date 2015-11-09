var http = require( 'http' );
var downloader = require( './down');
var sleep = require( 'sleep' );


var options = 
{
    hostname:   'zangsisi.net',
    path:       process.argv[2],
    method:     'GET'
};


function pad(num) {
    var s = "00" + num;

    return s.substr( s.length - 3 );
}

function downImg( res ) {
    var str = '';
    var startIdx;

    res.setEncoding('utf8');
    
    res.on( 'data', function( chunk ) {
        str += chunk;
    });

    res.on( 'end', function() {
        startIdx = str.indexOf('<span class="title">');
        var subStr = str.substring( startIdx, str.length );
        
        console.log( subStr );
        var m;
        urls = []; 
        rex = /src="?([^"\s]+)"?\s*\/>/g;

        while ( m = rex.exec( str ) ) {
            urls.push( m[1] );
        }
        console.log( urls );

        var index = 1;
        var prefix = process.argv[3];
        var postfix = '.jpg'; // It should be changed to url's final 4 character.

        var fileName;
        var len = urls.length;

        for ( var i = 0 ; i < len ; i++ ) {
            console.log( urls[i] );
            fileName = prefix + pad( i ) + postfix;
            downloader.downFile( fileName, urls[i] );
            sleep.usleep(10000);
        }
    });
}

if ( process.argv.length != 4 )
{
    console.log( "node __filename urlPath dirName" );
    quit();
}


console.log( options );

http.request( options, downImg ).end();
