var http = require( 'http' );
var downloader = require( './down');
var async = require( 'async' );

var options = 
{
    hostname:   'zangsisi.net',
    path:       process.argv[2],
    method:     'GET'
};

function pad(num) {
    var s = "00000" + num;

    return s.substr( s.length - 4 );
}

function cropImageHTML( strHTML )
{
    var startIdx = strHTML.indexOf('<span class="title">');
    var subStr = strHTML.substring( startIdx, strHTML.length );
    var endIdx = subStr.indexOf( '<!-- 하단 광고 -->' );
    var subStr = subStr.substring( 0, endIdx );

    return subStr;
}

function downImg( res ) {
    var str = '';

    res.setEncoding('utf8');
    
    res.on( 'data', function( chunk ) {
        str += chunk;
    });

    res.on( 'end', function() {
        var imageHTML = cropImageHTML( str );

        var m;
        urls = []; 
        rex = /<img.*?src=["'](.*?)["']/g;

        while ( m = rex.exec( imageHTML ) ) {
            urls.push( m[1] );
        }

        var prefix = process.argv[3];
        var postfix = '.jpg'; // It should be changed to url's final 4 character.
        var fileName;
        var len = urls.length;

        console.log( urls );

        async.each( urls, 
            function( item, callback ) {
                postfix = item.substring( item.length-4, item.length );
                fileName = prefix + pad( urls.indexOf(item) ) + postfix;
                downloader.downFile( fileName, item, function(){
                    callback();
                } );
            },
            function ( err ) {
                if ( err ) 
                    console.error( err.message );
                console.log( "Download completed." );
            }
        );
    });
}

if ( process.argv.length != 4 )
{
    console.log( "usage : node zzangsisiDownloader.js <urlPath> <dirName>" );
}
else
{
    http.request( options, downImg ).end();
}
