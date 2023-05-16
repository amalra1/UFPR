var xmlhttp = new XMLHttpRequest();
  xmlhttp.onreadystatechange = function () {
  
  // Request finished and response 
  // is ready and Status is "OK"
  if (this.readyState == 4 && this.status == 200) {
    console.log("a");
  }
};
  
// employee.xml is the external xml file
xmlhttp.open("GET", "alunos.xml", true);
xmlhttp.send();