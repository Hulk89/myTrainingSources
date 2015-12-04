var http = require( 'http' );
var downloader = require( './down');
var async = require( 'async' );
var url = require( 'url' );


function getNameOfFile( str ) {
    var startIdx = str.indexOf('<!-- 정보 시작 -->');
    var subStr = str.substring( startIdx, str.length );
    var endIdx = subStr.indexOf( '<!-- 정보 끝 -->' );
    var subStr = subStr.substring( 0, endIdx );

    rex = /<div style="font:bold 14pt Dotum; color:#333333; margin-bottom:5px;">(.*?)<\/div>/g

    return rex.exec( subStr )[1];

}

function getFileUrl( str ) {
    var startIdx = str.indexOf('<!-- 동영상 시작 -->');
    var subStr = str.substring( startIdx, str.length );
    var endIdx = subStr.indexOf( '<!-- 동영상 끝 -->' );
    var subStr = subStr.substring( 0, endIdx );

    rex = /<source.*?src=["'](.*?)["']/g;

    return rex.exec( subStr )[1];
}

exports.downOneMovie = function ( aniUrl, callback )
{
    var options = url.parse( aniUrl )

    var req = http.request( options, function ( res )
        {
            var str = '';

            res.setEncoding('utf8');

            res.on( 'data', function( chunk ) {
                str += chunk;
            });

            res.on( 'end', function() {
                var fileUrl = getFileUrl( str );
                var fileName = getNameOfFile( str );

                var postfix = fileUrl.substring( fileUrl.length-4, fileUrl.length );
                fileName = fileName + postfix;

                fileUrl = fileUrl.replace( 'https', 'http' );

                downloader.downFile( fileName, fileUrl, callback );
            });
        }).end();
}
