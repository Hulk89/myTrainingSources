
function eat( food ) 
{
    if ( typeof food !== 'string' )
        return 'Error';
    else
        return food + ' tasted really good.';
}

console.log( eat( 'bananas' ) );
console.log( eat( 1 ) );
