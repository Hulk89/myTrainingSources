process.argv.forEach( function ( val, index, array )
{
    console.log( index + ":" + val );
} );

console.log( "cwd : ", process.cwd() );
console.log( "process.env : ", process.env );
console.log( "memoryUsage : " , process.memoryUsage() );
