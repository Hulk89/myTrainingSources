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

function downImg( res ) {
    var str = '';

    res.setEncoding('utf8');
    
    res.on( 'data', function( chunk ) {
        str += chunk;
    });

    res.on( 'end', function() {
        var startIdx = str.indexOf('<span class="title">');
        var subStr = str.substring( startIdx, str.length );
        var endIdx = subStr.indexOf( '<!-- 하단 광고 -->' );
        var subStr = subStr.substring( 0, endIdx );

        var m;
        urls = []; 
        rex = /<img.*?src=["'](.*?)["']/g;

        while ( m = rex.exec( subStr ) ) {
            urls.push( m[1] );
        }
        console.log( urls );

        var prefix = process.argv[3];
        var postfix = '.jpg'; // It should be changed to url's final 4 character.
        var fileName;
        var len = urls.length;

        async.each( urls, 
            function( item, callback ) {
                postfix = item.substring( item.length-4, item.length );
                fileName = prefix + pad( urls.indexOf(item) ) + postfix;

                var item2 = item.replace( 'https', 'http' );
                downloader.downFile( fileName, item2, function(){
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
