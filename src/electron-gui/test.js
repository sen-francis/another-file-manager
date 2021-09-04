console.log("brh");
const backend = require("./build/Release/backend.node");
var tmp = backend.search("/mnt/d/projects/tts-discord-bot","05/25/2021","05/30/2021","NULL","NULL");
tmp.forEach(item => alert(item));

