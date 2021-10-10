const backend = require("./build/Release/backend.node");
var createdFromDate = "05/31/2021";
var createdToDate = "09/24/2021";
var modifiedFromDate = "05/31/2021";
var modifiedToDate = "06/01/2021";

var tmpArr = backend.search("/mnt/d/projects/tts-discord-bot",createdFromDate,createdToDate,modifiedFromDate,modifiedToDate);
tmpArr.forEach(element => console.log(element));