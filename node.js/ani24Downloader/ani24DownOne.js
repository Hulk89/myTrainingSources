var http = require( 'http' );
var downloader = require( './down');
var async = require( 'async' );
var url = require( 'url' );

function pad(num) {
    var s = "00000" + num;

    return s.substr( s.length - 4 );
}

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

function downMovie( res, callback ) {
    var str = '';

    res.setEncoding('utf8');
    
    res.on( 'data', function( chunk ) {
        str += chunk;
    });

    res.on( 'end', function() {
        var fileUrl = getFileUrl( str );
        var fileName = getNameOfFile( str );

        console.log( "file name : " + fileName );
        console.log( "file url  : " + fileUrl );

        var postfix = fileUrl.substring( fileUrl.length-4, fileUrl.length ); 
        fileName = fileName + postfix;

        fileUrl = fileUrl.replace( 'https', 'http' );

        downloader.downFile( fileName, fileUrl, callback );

    });
}

exports.downOneMovie = function ( aniUrl )
{
    var options = url.parse(process.argv[2])
    http.request( options, downMovie ).end();
}

