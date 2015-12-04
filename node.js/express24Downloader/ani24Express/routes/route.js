var fileControl = require( '../controllers/fileControl.js' );

exports.route = function( app ) {
    app.get( '/', fileControl.view );
};
