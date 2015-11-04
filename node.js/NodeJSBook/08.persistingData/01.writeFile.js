var fs = require('fs')
var data = "Hello world!!"

fs.writeFile( "persistData.txt", data, function( err ){
    if ( !err ) 
    {
        console.log( "Successfully saved!" );
    }
    else
    {
        throw err;
    }
});
