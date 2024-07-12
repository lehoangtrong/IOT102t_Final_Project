const sheetID = "11zydyUnpu7Gi1B4aFzKH0uMxLvV92aLwtLXHI0aQTAQ";

function doGet(e) {
  var result = "done";

  Logger.log(JSON.stringify(e));

  if (e.parameter.type == "takeAttendant") {
    // get studentID from e.parameter
    var fingerID = e.parameter.fingerID;
    // Check fingerID has been in the table students
    var sheet = SpreadsheetApp.openById(sheetID).getSheetByName("students");
    var data = sheet.getDataRange().getValues();
    var studentID = null;
    var studentName = null;
    for (var i = 1; i < data.length; i++) {
      if (data[i][3] == fingerID) {
        result = {
          studentID: data[i][1],
          studentName: data[i][2],
          fingerID: data[i][3],
        };
        studentID = data[i][1];
        studentName = data[i][2];
        break;
      }
    }
    if (result != "done") {
      var date = new Date();
      var currentDate = Utilities.formatDate(date, "GMT+7", "dd/MM/yyyy");

      var currentTime = Utilities.formatDate(date, "GMT+7", "HH:mm:ss");

      var sheet =
        SpreadsheetApp.openById(sheetID).getSheetByName("takeAttendant");

      var lastRow = sheet.getLastRow() + 1;
      sheet.appendRow([
        lastRow,
        studentID,
        studentName,
        currentDate,
        currentTime,
      ]);
    } else {
      result = "fingerID not found";
    }
  } else if (e.parameter.type == "enrollStudent") {
    var studentID = e.parameter.studentID;
    var studentName = e.parameter.studentName;
    var fingerID = e.parameter.fingerID;

    if (studentID == null || studentName == null || fingerID == null) {
      return ContentService.createTextOutput("null parameter");
    }

    var sheet = SpreadsheetApp.openById(sheetID).getSheetByName("students");

    // check studentID exist
    var studentIDExist = false;
    var data = sheet.getDataRange().getValues();
    for (var i = 1; i < data.length; i++) {
      if (data[i][1] == studentID) {
        studentIDExist = true;
        break;
      }
    }

    if (!studentIDExist) {
      sheet.appendRow([
        sheet.getLastRow() + 1,
        studentID,
        studentName,
        fingerID,
      ]);
      result = "enroll success";
    } else {
      result = "studentID exist";
    }
  } else if (e.parameter.type == "getStudentByFingerPrint") {
    var fingerID = e.parameter.fingerID;

    var sheet = SpreadsheetApp.openById(sheetID).getSheetByName("students");

    var data = sheet.getDataRange().getValues();
    for (var i = 1; i < data.length; i++) {
      if (data[i][3] == fingerID) {
        result = {
          studentID: data[i][1],
          studentName: data[i][2],
          fingerID: data[i][3],
        };
        break;
      }
    }

    if (result == "done") {
      result = "fingerID not found";
    }
  } else {
    result = "error";
  }
  return ContentService.createTextOutput(JSON.stringify(result));
}
