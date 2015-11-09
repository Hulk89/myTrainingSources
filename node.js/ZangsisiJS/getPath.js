
exports.getPathfromURL( url ){
    var m;
    urls = []; 
    rex = /zangsisi\.net(\/\?p=[0-9]*)/g;

    while ( m = rex.exec( url ) ) {
        urls.push( m[1] );
    }
    return urls;
}

