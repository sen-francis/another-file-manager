// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
document.getElementById("searchButtonID").addEventListener("click",()=>{
    alert("hii");
    const backend = require("./build/Release/backend.node");
    alert("hiii");
    document.getElementById("headerID").innerHTML = "BUTTON CLICKED";
});