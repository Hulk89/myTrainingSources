/*
 *
 */
var time1    = process.argv[2];
var operator = process.argv[3];
var time2    = process.argv[4];

var hour1 = parseInt( time1.slice( 0,2 ) );
var hour2 = parseInt( time2.slice( 0,2 ) );

var min1 = parseInt( time1.slice( 4, 6 ) );
var min2 = parseInt( time2.slice( 4, 6 ) );

var sec1 = parseInt( time1.slice( 8, 10 ) );
var sec2 = parseInt( time2.slice( 8, 10 ) );

if ( operator === '+' )
{
    var hour = hour1 + hour2;
    var min  = min1  + min2;
    var sec  = sec1  + sec2;

    if ( sec >= 60 )
    {
        sec = sec % 60;
        min = min + 1;
    }

    if ( min >= 60 )
    {
        min = min % 60;
        hour = hour + 1;
    }

    console.log( hour + "::" + min + "::" + sec );
}
else if ( operator === '-' )
{
    var hour = hour1 - hour2;
    var min  = min1  - min2;
    var sec  = sec1  - sec2;

    if ( sec < 0  )
    {
        sec = sec + 60;
        min = min - 1;
    }

    if ( min < 0 )
    {
        min = min + 60;
        hour = hour - 1;
    }

    console.log( hour + "::" + min + "::" + sec );
}
else
{
    console.log( 'undefined' );
}

