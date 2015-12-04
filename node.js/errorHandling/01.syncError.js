
try {
    throw new Error( 'test' );
}
catch (exception) {
    console.log( exception );
    console.log( exception.stack );
}

console.log( 'final log' );
