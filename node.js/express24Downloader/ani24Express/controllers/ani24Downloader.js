var http = require( 'http' );
var async = require( 'async' );
var url = require( 'url' );
var fs  = require( 'fs' );
var parser = require('./urlParser');


function aniDownloader() {
  this.fileList = [];
  this.fileCount = 0;
}
/* progress를 update하는 함수
 * fileName : fileList의 fileName과 비교할 이름 ( in )
 * progress : update할 progress 값 ( in )
 */
aniDownloader.prototype.updateProgress =
function(fileName,progress)
{
  this.fileList.some( function( item, index, array ){
    if ( item['fileName'] == fileName  )  //같츤 fileName에 대해 찾아서
    {
      item['progress'] = progress;        // progress를 업데이트하고 종료
      return true;
    }
    else {
      return false;
    }
  })
};

/* file을 다운받는 함수
 * fileName   : 다운받는 file의 이름을 지정 ( in )
 * url        : 다운받는 file의 주소 ( in )
 * onProgress : down받는 file이 1% 증가될 때마다 호출할 callback
 * onEnd      : down이 완료될 때 호출할 callback
 */
aniDownloader.prototype.downFile =
 function ( fileName,
            url,
            onProgress,
            onEnd )
{
    var file = fs.createWriteStream( fileName );
    var myObject = this;

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
            if ( prevPercent + 1 <= currPercent ) // 저번 퍼센트보다 1 이상 증가했으면
            {
                prevPercent = currPercent;
                myObject.updateProgress( fileName, currPercent);  //update를 하고
                onProgress();                                     //callback 호출
            }
        });

        response.on('end', function() {
            myObject.updateProgress( fileName, 100);
            onEnd();
        });
    });
}

/* fileName과 url을 파싱하는 함수.
 * urlList  : 파싱할 url. List가 아닌 하나의 string이다. ( in )
 * callback : 파싱이 끝났을 때 불릴 callback ( 인자는 infoList이다. )
 */
aniDownloader.prototype.getFileNameAndUrls =
function( urlList, callback )
{
  var options  = url.parse( urlList );
  var path     = options['path'];
  var myObject = this;

  if ( path.indexOf("list") > -1 )              //list를 가지고있는 URL이면
  {
      http.request( options, function( res ){
        myObject.getInfoList( res,              // getInfoList로 List를 얻어온 후
                              function( infoList )    // callback 호출
                              {
                                callback( infoList );
                              } );
      } ).end();

  }
  else if ( path.indexOf("view") > -1 )         // 하나짜리 비디오 URL이면
  {
      var fileListFromUrl = [];
      this.getOneInfo( urlList,                 // oneInfo를 얻은 후
                       function( oneFileInfo )
                       {
                          fileListFromUrl.push( oneFileInfo );  //List에 넣고
                          callback( fileListFromUrl );          // callback 호출
                       } );
  }
  else
  {
      console.log( "Invalid URL." );
      callback( [] ); // empty Array return
  }
}

/* 하나의 fileInfo를 callback으로 내보내는 함수.
 * aniUrl   : view로 시작하는 url주소.
 * callback : fileInfo를 구해 push한 이후 불릴 콜백 ( 인자 : fileInfo 하나 )
 */
aniDownloader.prototype.getOneInfo =
function ( aniUrl, callback )
{
    var options = url.parse( aniUrl )
    var myObject = this;
    var req = http.request( options, function ( res )
        {
            var str = '';
            res.setEncoding('utf8');

            res.on( 'data', function( chunk ) {
                str += chunk;
            });

            res.on( 'end', function() {
                var fileUrl = parser.getFileUrl( str );
                var fileName = parser.getNameOfFile( str );

                var postfix = fileUrl.substring( fileUrl.length-4, fileUrl.length );
                fileName = fileName + postfix;
                fileUrl = fileUrl.replace( 'https', 'http' );

                var myFileInfo = { fileName : fileName,                 // fileInfo를 만들고
                                   fileUrl  : fileUrl,
                                   progress : 0      ,
                                   idx      : myObject.fileCount };
                myObject.fileCount = myObject.fileCount + 1;            // count를 증가시키고
                myObject.fileList.push( myFileInfo );                   // fileList에 넣고
                callback( myFileInfo );                                 // callback 호출
            });
        }).end();
};
/* List를 가지고있는 URL을 파싱해서 fileInfoList를 내보내는 함수
 * res          : response ( in )
 * callbackList : List를 다 만든 경우 callback ( 인자 : fileInfoList )
 */
aniDownloader.prototype.getInfoList =
 function( res,
           callbackList ) {
    var infoList = [];
    var str = "";
    var myObject = this;
    res.setEncoding('utf8');

    res.on( 'data', function( chunk ) {
        str += chunk;
    } );

    res.on( 'end', function() {
        var urls = parser.getUrlList( str );

        urls.forEach( function( item, index, array ) {
            array[index] = "http://ani24.net"+item;
        });

        async.each( urls,
            function( item, callback ) {
                myObject.getOneInfo( item,
                function( oneInfo )
                {
                  infoList.push( oneInfo );
                  callback();
                } );
            },
            function( err ) {
                if ( err )
                    console.error( err.message );
                callbackList( infoList );
            });
    });
};

module.exports = aniDownloader;
