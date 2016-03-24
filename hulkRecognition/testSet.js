var execSync = require('child_process').execSync;
var fs = require('fs');
var  child;

console.log( __dirname );

fileList = fs.readdirSync( __dirname + "/" + process.argv[2] );
        
for ( var i = 0 ; i < fileList.length ; i++ )
{
    if ( fileList[i] == ".DS_Store" )
    {

    }
    else
    {
        var fileName =  __dirname + "/" + process.argv[2] + fileList[i];

        var removeKor = "python hulkEquationExtractor.py " + fileName + " >> " + fileName + ".res";
        execSync ( removeKor )
        console.log( fileName + " Done..." );
    }
}
