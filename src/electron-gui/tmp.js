const backend = require("./build/Release/backend.node");
var createdFromDate = "NULL";
var createdToDate = "NULL";
var modifiedFromDate = "NULL";
var modifiedToDate = "NULL";
alert("post reuqior");
// Parse dates into MM/DD/YYYY strings
if(document.getElementById("createdCheckbox").checked == true){
  //check if user does not pick date (call alert)
  var tmpCreatedFromDate = new Date(document.getElementById("createdCheckbox").value);
  // might have to increment month seperately in var
  createdFromDate = tmpCreatedFromDate.getMonth()+1 + "/" + tmpCreatedFromDate.getDate() + "/" + tmpCreatedFromDate.getFullYear();

  var tmpCreatedToDate = new Date(document.getElementById("createdCheckbox").value);
  createdToDate = tmpCreatedToDate.getMonth()+1 + "/" + tmpCreatedToDate.getDate() + "/" + tmpCreatedToDate.getFullYear();
}

if(document.getElementById("modifiedCheckbox").checked == true){
  var tmpModifiedFromDate = new Date(document.getElementById("modifiedCheckbox").value);
  modifiedFromDate = tmpModifiedFromDate.getMonth()+1 + "/" + tmpModifiedFromDate.getDate() + "/" + tmpModifiedFromDate.getFullYear();

  var tmpModifiedToDate = new Date(document.getElementById("modifiedCheckbox").value);
  modifiedToDate = tmpModifiedToDate.getMonth()+1 + "/" + tmpModifiedToDate.getDate() + "/" + tmpModifiedToDate.getFullYear();
}
var fileName = document.getElementById("inputID").files[0].path;
var filePath = fileName.substring(0, fileName.lastIndexOf("/"));

alert("got here");
var tmpArr = backend.search(filePath,createdFromDate,createdToDate,modifiedFromDate,modifiedToDate);
alert("and here");
tmpArr.forEach(element => alert(element));
alert("not here");
postMessage(tmpArr[0]);