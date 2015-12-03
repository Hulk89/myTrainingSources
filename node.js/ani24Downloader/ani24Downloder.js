var http = require( 'http' );
var url  = require( 'url' );
var async = require( 'async' );

var ani24DownOne = require( './ani24DownOne.js' );


function getFileUrls( str ) {
    var startIdx = str.indexOf('공지사항 -->');
    var subStr = str.substring( startIdx, str.length );
    var endIdx = subStr.indexOf( '<!-- 바닥 영역 시작 -->' );
    var subStr = subStr.substring( 0, endIdx );


    rex = /onclick="location\.href='\.(.*?)';">/g;
    var urls = [];
    var m
    while( m = rex.exec( subStr ) )
    {
        urls.push( m[1] );
    }
    return urls;
}

function downFileList( res ) {
    
    var str = "";

    res.setEncoding('utf8');

    res.on( 'data', function( chunk ) {
        str += chunk;
    } );

    res.on( 'end', function() {
        var urls = getFileUrls( str );

        urls.forEach( function( item, index, array ) {
            array[index] = "http://ani24.net"+item;
        });
        console.log( urls );

        async.eachSeries( urls,
            function( item, callback ) {

                ani24DownOne.downOneMovie( item, function() {
                    callback();
                });
            },
            function( err ) {
                if ( err )
                    console.error( err.message );
                console.log( "Download All!!" );
            });
    });

}


var options = url.parse( process.argv[2] );

http.request( options, downFileList ).end();

