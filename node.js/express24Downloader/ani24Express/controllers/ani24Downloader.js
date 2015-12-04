var http = require( 'http' );
var async = require( 'async' );
var url = require( 'url' );
var fs  = require( 'fs' );

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

function downFile( fileName, url, onProgress, onEnd )
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
                prevPercent = currPercent;

                onProgress( url, currPercent );
            }
        });

        response.on('end', function() {
            onEnd( url );
        });
    });
}

function downOneMovie ( aniUrl, onProgress, onEnd )
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

                downFile( fileName,
                          fileUrl,
                          onProgress,
                          onEnd );
            });
        }).end();
}


function getUrlList( str ) {
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


function downFileList( res, onProgress, onEnd ) {

    var str = "";

    res.setEncoding('utf8');

    res.on( 'data', function( chunk ) {
        str += chunk;
    } );

    res.on( 'end', function() {
        var urls = getUrlList( str );

        urls.forEach( function( item, index, array ) {
            array[index] = "http://ani24.net"+item;
        });

        async.each( urls,
            function( item, callback ) {
                downOneMovie( item, callback );
            },
            function( err ) {
                if ( err )
                    console.error( err.message );
                console.log( "Download All!!" );
            });
    });

}

exports.download = function( fileUrl,
                             onProgress,
                             onEnd )
{
  var options  = url.parse( fileUrl );
  var path     = options['path'];

  if ( path.indexOf("list") > -1 )
  {
      console.log( "DownList" )
      http.request( options, function( res ){
        downFileList( res,
                      onProgress,
                      onEnd );
      } ).end();
  }
  else if ( path.indexOf("view") > -1 )
  {
      console.log( "Download One file" );
      downOneMovie( fileUrl,
                    onProgress,
                    onEnd );
  }
  else
  {
      console.log( "Invalid URL." );
  }
}
