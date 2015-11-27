var Task = require('../models/task.js');

exports.create = function( req,res ) {
    console.log( 'create' );
    console.log( req.body );
    Task.find( { contents: req.body.contents },
               function( err, tasks ) {
      if ( err )
        throw err;

      var newTask = true;

      // find same task
      if ( tasks.length > 0 ) {
        console.log( 'There are same contents already, skip to create this task. Contents : '
                     + req.body.contents );
        newTask = false;
      }

      if ( newTask )
      {
        new Task({
          contents : req.body.contents,
          author : req.body.author
        }).save();

        console.log( 'Succeed to create new Tasks {' + req.body.contents + '}' );
      }
    });

    //display all tasks
    res.redirect('/');
    res.end();
}

exports.update = function( req, res ) {
    Task.update(
      { contents : req.body.contents },
      { status   : req.body.status },
      function( err, numberAffected, raw )
      {
        if (err)
          throw err;
        console.log( 'The number of updated documents was %d', numberAffected );
        console.log( 'The raw response from MongoDB was ', raw );
      });

    //display all tasks
    res.redirect('/');
    res.end();
}

exports.remove = function( req, res ) {
    Task.remove(
      { contents : req.body.contents },
      function( err)
      {
        if (err)
          throw err;
        console.log( 'Succeed to remove task. content is {' + req.body.contents + '}' );
      });

    //display all tasks
    res.redirect('/');
    res.end();
}


exports.list = function( req, res ) {
    Task.find( function( err, tasks ) {
      console.log( 'Succeed to get all tasks {' + tasks + '}' );
      var todoTasks       = [];
      var inProgressTasks = [];
      var doneTasks       = [];

      for ( var key in tasks )
      {
        var task = tasks[key];
        var status = task.get('status');
        if ( status === 'TO-DO' )
        {
          todoTasks.push( task.get('contents') );
        }
        else if ( status === 'In-Progress' )
        {
          inProgressTasks.push( task.get('contents') );
        }
        else if ( status === 'Done' )
        {
          doneTasks.push( task.get('contents') );
        }
        else
        {
          console.log( 'Task status is not valid.' + task );
        }

      }

      res.render( 'index', {
        title: 'Hulk Kanbanboard',
        todoTasks: todoTasks,
        inProgressTasks: inProgressTasks,
        doneTasks: doneTasks
      });

    });
}
