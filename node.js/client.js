var select = require('soupselect').select;
var htmlParser = require( 'htmlparser' );
var http    = require( 'http' );
var sys     = require( 'sys' );
var fs      = require( 'fs' );
var request = require( 'request' );

var options = {
  hostname: 'comic.naver.com',
  method: 'GET',
  port: 80,
  path: '/webtoon/detail.nhn?titleId=628997&no=58&weekday=sat'
};

var download = function( uri, filename, callback){
  request.head(uri,function(err,res,body){
    //console.log('content-type:',res.headers['content-type']);
    //console.log('content-length:',res.headers['content-length']);

    request(uri).pipe(fs.createWriteStream(filename)).on('close', callback);
  });
}

var req = http.request(options, function(res) {
  //console.log('STATUS: ' + res.statusCode);
  //console.log('HEADERS: ' + JSON.stringify(res.headers));
  res.setEncoding('utf8');
  
  var body = "";

  res.on('data', function (chunk) {
    body = body + chunk;
  });

  res.on('end',function () {

    var handler = new htmlParser.DefaultHandler( function ( err, dom ) {
      
      if ( err ) {
        return console.error( "Err : " + err );
      }
      else {
        var img1 = htmlParser.DomUtils.getElementById("content_image_0",dom );
        console.log( img1.attribs.src );
        var url = img1.attribs.src;
    
        download( url, 'test.jpg',function(){console.log('done');});       
        //fs.writeFileSync( "test.jpg", img1 );
      }
    } );

    var parser = new htmlParser.Parser( handler );
    parser.parseComplete( body );
    
    //sys.puts(sys.inspect(handler.dom, false, null));

  });

});

req.on('error', function(e) {
  console.log('problem with request: ' + e.message);
});

// write data to request body
 req.end();
