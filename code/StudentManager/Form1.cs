using System;
using System.Drawing;
using System.IO.Ports;
using System.Text;

namespace StudentManager
{
    public partial class Form1 : Form
    {
        private static SerialPort? serialPort;

        public Form1()
        {
            InitializeComponent();
            addButton.Enabled = false;
            clearButton.Enabled = false;
            textBoxName.Enabled = false;
            textBoxStudentID.Enabled = false;
            init();
        }

        private async void init()
        {
            await Task.Delay(1000);
            while (serialPort == null) await Task.Run(() => FindDevice());
            GetData();
            CheckComStatus();
        }

        private void GetData()
        {
            serialPort.Write("g");

            List<Student> students = new List<Student>();

            while (true)
            {
                string response = serialPort.ReadLine().Replace("\r", "");
                if (response.Equals("DONE")) break;
                string[] data = response.Split(';');
                Student student = new Student
                {
                    Name = data[0],
                    StudentID = data[1],
                    fingerPrintID = data[2]
                };
                students.Add(student);             
            }
            dataStudent.DataSource = students;
        }

        private void FindDevice()
        {
            string[] COMPorts = SerialPort.GetPortNames();

            SerialPort? port = new SerialPort();

            foreach (string COMPort in COMPorts)
            {
                try
                {
                    port = new SerialPort(COMPort, 115200)
                    {
                        Encoding = System.Text.Encoding.UTF8
                    };
                    port.Open();
                    if (port.IsOpen)
                    {
                        port.Write("c");
                        string response = port.ReadLine().Replace("\r", "");
                        if (response == "Connected")
                        {
                            serialPort = port;
                            Invoke(new Action(() =>
                            {
                                statusLabel.Text = "Đã kết nối";
                                statusLabel.ForeColor = Color.Green;
                                addButton.Enabled = true;
                                clearButton.Enabled = true;
                                textBoxName.Enabled = true;
                                textBoxStudentID.Enabled = true;
                            }));
                        }
                    }
                }
                catch (Exception e)
                {

                    MessageBox.Show(e.Message);
                    port.Dispose();
                }
            }
        }

        private async void CheckComStatus()
        {
            await Task.Delay(200);
            while (serialPort == null) await Task.Run(() => FindESP8266());
            statusLabel.Text = "Đã kết nối với ESP8266 tại " + serialPort.PortName;
            statusLabel.ForeColor = Color.Green;
            addButton.Enabled = true;
            clearButton.Enabled = true;
            textBoxName.Enabled = true;
            textBoxStudentID.Enabled = true;

        }

        private void clearButton_Click(object sender, EventArgs e)
        {

        }

        private void addButton_Click(object sender, EventArgs e)
        {

        }
    }
}
