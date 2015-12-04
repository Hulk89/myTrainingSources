var http = require( 'http' );
var async = require( 'async' );
var url = require( 'url' );
var fs  = require( 'fs' );
var parser = require('./urlParser');


function Downloader() {
  this.fileList = [];
  this.count = 0;
}

Downloader.prototype.updateProgress =
function(fileName,progress)
{
  this.fileList.some( function( item, index, array ){
    if ( item['fileName'] == fileName  )
    {
      item['progress'] = progress;
      return true;
    }
    else {
      return false;
    }
  })
};

Downloader.prototype.downFile =
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
            if ( prevPercent + 1 <= currPercent )
            {
                prevPercent = currPercent;
                myObject.updateProgress( fileName, currPercent);
                onProgress();
            }
        });

        response.on('end', function() {
            myObject.updateProgress( fileName, 100);
            onEnd();
        });
    });
};
Downloader.prototype.getFileNameAndUrls =
function( urlList, callback )
{
  var options  = url.parse( urlList );
  var path     = options['path'];
  var myObject = this;
  if ( path.indexOf("list") > -1 )
  {
      http.request( options, function( res ){
        myObject.getInfoList( res,
                              function( infoList )
                              {
                                callback( infoList );
                              } );
      } ).end();

  }
  else if ( path.indexOf("view") > -1 )
  {
      var fileListFromUrl = [];
      this.getOneInfo( urlList,
                       function( oneFileInfo )
                       {
                          fileListFromUrl.push( oneFileInfo );
                          callback( fileListFromUrl );
                       } );
  }
  else
  {
      console.log( "Invalid URL." );
  }
}

Downloader.prototype.getOneInfo =
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

                //fileName = fileName.replace(/ /g,"");
                var myFileInfo = { fileName : fileName,
                                   fileUrl  : fileUrl,
                                   progress : 0      ,
                                   idx      : myObject.count };
                myObject.count = myObject.count + 1;
                myObject.fileList.push( myFileInfo );
                callback( myFileInfo );
            });
        }).end();
};

Downloader.prototype.getInfoList =
 function( res,
           callback ) {
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
                callback( infoList );
            });
    });
};

module.exports = Downloader;
