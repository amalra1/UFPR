var xmlhttp; 
var xmlStr;

// Structure for subject data
class SubjectData 
{
  constructor(subjectCode, situation, grade) 
  {
    this.subjectCode = subjectCode;
    this.situation = situation;
    this.grade = grade;
  }
}

// Array to store all subject datas from a student
var studentData = [];

function loadData()
{
    xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () 
    {
    // Request finished and response 
    // is ready and Status is "OK"
    if (this.readyState == 4 && this.status == 200)
    { 
      xmlStr = xmlhttp.responseXML;
      collectData(xmlStr);
      updateGrade();
    }
  };

  xmlhttp.open("GET", "alunos.xml", true);
  xmlhttp.send();
}

function collectData()
{
  let input = document.getElementById("grr");
  let grrAlunoInput = input.value;
  let alunos = xmlStr.getElementsByTagName("ALUNO");
  let grrAluno, subCode, situation, grade;

  console.log(grrAlunoInput);

  for (var i = 0; i < alunos.length; i++) 
  {
    grrAluno = alunos[i].getElementsByTagName("MATR_ALUNO")[0].childNodes[0].nodeValue;

    // Collect all necessary data from the student passed as input
    if (grrAluno === grrAlunoInput) 
    {
      subCode = alunos[i].getElementsByTagName("COD_ATIV_CURRIC")[0].childNodes[0].nodeValue;
      situation = alunos[i].getElementsByTagName("SITUACAO")[0].childNodes[0].nodeValue;
      grade = alunos[i].getElementsByTagName("MEDIA_FINAL")[0].childNodes[0].nodeValue;

      // New SubjectData object
      const subData = new SubjectData(subCode, situation, grade);

      //GRR00000000

      // Adding it to the student's array
      studentData.push(subData);
    }
  }

  // Lidar com materias que aparecem mais de uma vez pq o cara fez mais de uma vez
  for (i = 0; i < studentData.length; i++)
  {
    console.log("COD: " + studentData[i].subjectCode);
    console.log("SITUACAO: " + studentData[i].situation);
    console.log("MEDIA FINAL: " + studentData[i].grade);
  }
}

function updateGrade()
{

}