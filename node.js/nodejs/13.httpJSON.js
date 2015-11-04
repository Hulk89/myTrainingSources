var http = require( 'http' );
var url  = require( 'url' );

function onReq( req, res )
{
    var parsed = url.parse( req.url, true );
    
    console.log( parsed );
    if ( parsed.pathname === '/api/parsetime' )
    {
        var isoStr =  parsed.query.iso;
        var date   = new Date( isoStr );

        var data = {
            hour : date.getHours(),
            minute : date.getMinutes(),
            second : date.getSeconds()
            };

        var json = JSON.stringify( data );
        
        //console.log( json );
        res.writeHead( 200, {'Content-Type': 'application/json' } );
        res.write( json );
        res.end();
    }
    else if ( parsed.pathname === '/api/unixtime' )
    {
        var isoStr =  parsed.query.iso;
        var date   = new Date( isoStr );
        var data = { unixtime:  date.getTime() };
        var json = JSON.stringify( data );

//        var json = { "unixtime": Math.round( date / 1000 ) };

        res.writeHead( 200, {'Content-Type': 'application/json' } );
        res.write( json );
        res.end();

    }
    else
    {
        res.end( "Give me proper url." );
    }
}

var server = http.createServer( onReq );

server.listen( process.argv[2] );

/*
    var http = require('http')
    var url = require('url')
    
    function parsetime (time) {
      return {
        hour: time.getHours(),
        minute: time.getMinutes(),
        second: time.getSeconds()
      }
    }
    
    function unixtime (time) {
      return { unixtime : time.getTime() }
    }
    
    var server = http.createServer(function (req, res) {
      var parsedUrl = url.parse(req.url, true)
      var time = new Date(parsedUrl.query.iso)
      var result
    
      if (/^\/api\/parsetime/.test(req.url))
        result = parsetime(time)
      else if (/^\/api\/unixtime/.test(req.url))
        result = unixtime(time)
    
      if (result) {
        res.writeHead(200, { 'Content-Type': 'application/json' })
        res.end(JSON.stringify(result))
      } else {
        res.writeHead(404)
        res.end()
      }
    })
    server.listen(Number(process.argv[2])) 

 */
// node -pe "require('url').parse('/test?q=1', true)"
