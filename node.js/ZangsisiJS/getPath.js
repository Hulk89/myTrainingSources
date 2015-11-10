
function getPathfromURL( url ){
    var m;
    urls = []; 
    rex = /zangsisi\.net(\/\?p=[0-9]*)/g;

    while ( m = rex.exec( url ) ) {
        urls.push( m[1] );
    }
    console.log ( urls );
    return urls;
}

getPathfromURL( process.argv[2] );
