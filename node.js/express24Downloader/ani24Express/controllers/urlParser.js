
module.exports = {

getNameOfFile : function ( str ) {
    var startIdx = str.indexOf('<!-- 정보 시작 -->');
    var subStr = str.substring( startIdx, str.length );
    var endIdx = subStr.indexOf( '<!-- 정보 끝 -->' );
    var subStr = subStr.substring( 0, endIdx );

    rex = /<div style="font:bold 14pt Dotum; color:#333333; margin-bottom:5px;">(.*?)<\/div>/g

    return rex.exec( subStr )[1];
},

getFileUrl : function ( str ) {
    var startIdx = str.indexOf('<!-- 동영상 시작 -->');
    var subStr = str.substring( startIdx, str.length );
    var endIdx = subStr.indexOf( '<!-- 동영상 끝 -->' );
    var subStr = subStr.substring( 0, endIdx );

    rex = /<source.*?src=["'](.*?)["']/g;

    return rex.exec( subStr )[1];
},

getUrlList : function ( str ) {
    var startIdx = str.indexOf('공지사항 -->');
    var subStr = str.substring( startIdx, str.length );
    var endIdx = subStr.indexOf( '<!-- 바닥 영역 시작 -->' );
    var subStr = subStr.substring( 0, endIdx );

    rex = /onclick="location\.href='\.(.*?)';">/g;
    var urls = [];
    var m
    while( m = rex.exec( subStr ) )
    {
        urls.push( m[1] );
    }
    return urls;
}
};
