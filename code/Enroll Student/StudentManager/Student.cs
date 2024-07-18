using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StudentManager
{
    internal class Student
    {
        public string? Name { get; set; }
        public string? StudentID { get; set; }
        public string? fingerPrintID { get; set; }


        public Student()
        {
            this.Name = "";
            this.StudentID = "";
            this.fingerPrintID = "";
        }

        public Student(string name, string studentID, string fingerPrintID)
        {
            this.Name = name;
            this.StudentID = studentID;
            this.fingerPrintID = fingerPrintID;
        }
    }
}
