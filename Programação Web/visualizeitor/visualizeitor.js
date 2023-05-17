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
var allSubjectsData = [];

// Dictionary to store subject data
let subjectDataObj = {};

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

      // Check if subject code already exists in the object
      if (subjectDataObj.hasOwnProperty(subCode)) 
        subjectDataObj[subCode].push(new SubjectData(subCode, situation, grade));
      else 
        subjectDataObj[subCode] = [new SubjectData(subCode, situation, grade)];

      //GRR00000000

      // Turn everything to an array, but ordered the way we want
      allSubjectsData = Object.values(subjectDataObj).flat();
    }
  }

  // teste
  for (i = 0; i < allSubjectsData.length; i++)
  {
    console.log("COD: " + allSubjectsData[i].subjectCode);
    console.log("SITUACAO: " + allSubjectsData[i].situation);
    console.log("MEDIA FINAL: " + allSubjectsData[i].grade);
  }

  // Agora para achar a materia mais recente eh so ler o vetor ao contrario
}

function updateGrade()
{

}