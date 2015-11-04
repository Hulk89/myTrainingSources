var mongoose = require('mongoose');

mongoose.connect('mongodb://localhost/test');

var db = mongoose.connection;

db.on( 'error', console.error.bind( console, 'connection error:'));
db.once('open', function callback () {
    // connection success
    var mySchema = mongoose.Schema({ //schema 설정
        name: String
    });

    // speak라는 method 추가
    mySchema.methods.speak = function(){
        var greeting = this.name ? 
                       "Meow name is " + this.name : 
                       "I don't have name";
        console.log( greeting );
    };
    
    // model 만들기
    var myModel = mongoose.model( 'myModel', mySchema );
    
    // myModel로 된 변수 만들기
    var fluffy = new myModel( { name : 'fluffy' } );

    fluffy.speak();
    
    // save
    fluffy.save( function( err, fluffy ) {
        if (err) {
            throw err;
        }
    });

    myModel.find( {name : /^fluff/}, function( err, myModels ) {
        if (err)
            throw err;
        db.close();
        console.log( 'myModels : ' + myModels );
    });

});
