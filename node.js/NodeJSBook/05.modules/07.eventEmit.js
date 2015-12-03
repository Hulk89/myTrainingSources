process.on('test',function() {
    console.log( 'Test event emitted!!' );
});

process.emit('test');
