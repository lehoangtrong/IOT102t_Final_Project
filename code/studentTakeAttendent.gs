const sheetID = "1qFt-k1qpbiFFuHlqcFvYNkydSImbJD_kSUYsNl-0JDE";

function doGet(e) {
  var result = "done";

  Logger.log(JSON.stringify(e));

  if (e.parameter.type == "takeAttendant") {
    // get studentID from e.parameter
    var studentID = e.parameter.studentID;
    if (studentID == null) {
      return ContentService.createTextOutput("studentID is null");
    }

    var date = new Date();
    var currentDate = Utilities.formatDate(date, "GMT+7", "dd/MM/yyyy");

    var currentTime = Utilities.formatDate(date, "GMT+7", "HH:mm:ss");

    var sheet =
      SpreadsheetApp.openById(sheetID).getSheetByName("takeAttendant");

    var lastRow = sheet.getLastRow() + 1;
    sheet.appendRow([lastRow, studentID, currentDate, currentTime]);

    result = "Attendant taken";
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
          studentID: data[i][2],
          studentName: data[i][3],
          fingerID: data[i][4],
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
  return ContentService.createTextOutput(JSON.stringify(result)).setMimeType(
    ContentService.MimeType.JSON
  );
}
