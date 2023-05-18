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

var subjectCodes = [
  'CI069', 'CI084', 'CI085', 'CI086', 'CI087', 'CI088', 'CI089', 'CI090',
  'CI091', 'CI092', 'CI093', 'CI094', 'CI095', 'CI097', 'CI167', 'CI168',
  'CI169', 'CI170', 'CI171', 'CI172', 'CI173', 'CI174', 'CI204', 'CI205',
  'CI214', 'CI301', 'CI302', 'CI303', 'CI304', 'CI305', 'CI306', 'CI309',
  'CI310', 'CI311', 'CI312', 'CI313', 'CI314', 'CI315', 'CI316', 'CI317',
  'CI318', 'CI320', 'CI321', 'CI337', 'CI338', 'CI339', 'CI340', 'CI350',
  'CI351', 'CI355', 'CI358', 'CI359', 'CI360', 'CI361', 'CI362', 'CI363',
  'CI364', 'CI365', 'CI366', 'CI367', 'CI394', 'CI395', 'CI396', 'ET082',
  'CE211', 'CM043', 'HL077', 'SA017', 'SC003', 'SC202', 'SC203',
  'CI068', 'CI055', 'CM046', 'CM045', 'CM201',
  'CI210', 'CI056', 'CI067', 'CM005', 'CM202',
  'CI212', 'CI057', 'CI064', 'CI237', 'CI166',
  'CI215', 'CI062', 'CE003', 'CI058', 'CI164',
  'CI162', 'CI065', 'CI059', 'CI061', 'SA214',
  'CI163', 'CI165', 'CI209', 'CI218', 'CI220',
  'CI221', 'CI211'
];

// Dictionary to store subject data
var subjectDataObj = {};

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
  let i, element, a;

  for (i = 0; i < subjectCodes.length; i++)
  {
    a = subjectCodes[i];
    element = document.getElementById(a);

    element.style.backgroundColor = "white";
  }


  console.log(grrAlunoInput);

  for (i = 0; i < alunos.length; i++) 
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
  /*
  for (i = 0; i < allSubjectsData.length; i++)
  {
    console.log("COD: " + allSubjectsData[i].subjectCode);
    console.log("SITUACAO: " + allSubjectsData[i].situation);
    console.log("MEDIA FINAL: " + allSubjectsData[i].grade);
  }
  */
}

// Function that goes over the sorted array of subjects and gets
// the last record of a given subject code (the last record is 
// the one that matters for the box colors)
function getLastRecordOfSubject(subCode) 
{
  let lastRecord = null;
  let i;
  
  for (i = allSubjectsData.length - 1; i >= 0; i--) 
  {
    if (allSubjectsData[i].subjectCode === subCode) 
    {
      lastRecord = allSubjectsData[i];
      console.log(allSubjectsData[i].subjectCode);
      console.log(allSubjectsData[i].situation);
      break;
    }
  }
  return lastRecord;
}

function updateGrade()
{
  // Agora para achar a materia mais recente eh so ler o vetor ao contrario
  let i, subCode, lastRecord, element;

  for (i = 0; i < subjectCodes.length; i++) 
  {
    subCode = subjectCodes[i];
    lastRecord = getLastRecordOfSubject(subCode);

    element = document.getElementById(subCode);

    if (lastRecord && lastRecord.situation === "Aprovado") 
      element.style.backgroundColor = "green";
    else if (lastRecord && lastRecord.situation === "Reprovado por nota")
      element.style.backgroundColor = "red";
    else if (lastRecord && lastRecord.situation === "Reprovado por Frequência")
      element.style.backgroundColor = "red";
    else if (lastRecord && lastRecord.situation === "Matrícula")
      element.style.backgroundColor = "blue";
    else if (lastRecord && lastRecord.situation === "Equivalência de Disciplina")
      element.style.backgroundColor = "yellow";
    else
      element.style.backgroundColor = "white";
  }
}