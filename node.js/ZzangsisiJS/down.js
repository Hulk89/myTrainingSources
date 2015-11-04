var http = require( 'http' )

var fs = require('fs');

var file = fs.createWriteStream("file.jpg");
var request = http.get("http://3.bp.blogspot.com/-CQE4zJhXc6g/VXvT-XbEEyI/AAAAAAAETLg/llP82BAd1V8/s1600/ATTACK.ON.TITAN.01_000.jpg", function(response) {
  response.pipe(file);
  });
