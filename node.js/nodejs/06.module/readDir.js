var fs   = require('fs');
var path = require('path');

module.exports = function readDir( dirName, extName, callback )
{
    fs.readdir( dirName, function (err, list) {
      if (err)
        return callback( err, null);

      var newList = [];

      list.forEach( function(file )
      {
        if ( path.extname( file ) === '.'+extName )
        newList.push( file );
      } );

      return callback( null, newList );

    } );
}
