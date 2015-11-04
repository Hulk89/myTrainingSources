var http = require('http');
var bl = require('bl');

var url = process.argv[2];

http.get( url, function (response) {
  response.setEncoding('utf8')
  response.pipe( bl( function (err, data) {
    if ( err )
        return console.error( "error : " + err );

    var buf = data.toString();

    var wc = buf.length;

    console.log( wc  );
    console.log( buf );
  }))  
  //response.on('data', console.log)
  //response.on('error', console.error)
})


