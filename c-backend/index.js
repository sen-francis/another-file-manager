// import native addon
const addonGreet = require('bindings')('greet');

// expose module API
exports.hello = addonGreet.greetHello;

const greet = require('greet');
console.log(greet.hello('John')); // Hello John!
