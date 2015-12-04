

exports.view = function( req, res ) {

    var downList = req.app.get( 'downList' );

    res.render( 'index', {
      title: 'Ani24Downloader',
      fileList: downList
    });
}
