function loadDoc() 
{
    // Entender o que isso ta fazendo
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() 
    {
      if (this.readyState == 4 && this.status == 200) 
        geraGrade(this);
    };

    xhttp.open("GET", "alunos.xml", true);
    xhttp.send();
  }