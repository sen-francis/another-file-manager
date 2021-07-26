/*// import native addon
const addonGreet = require('bindings')('greet');

// expose module API
exports.hello = addonGreet.greetHello;

const greet = require('greet');
console.log(greet.hello('John')); // Hello John!*/

// greet module: index.js
const addon = require('bindings')('greet'); // import 'greet.node'
exports.hello = addon.greetHello;
