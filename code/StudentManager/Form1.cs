using System;
using System.Drawing;
using System.IO.Ports;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StudentManager
{
    public partial class Form1 : Form
    {
        private static SerialPort serialPort;
        private static bool isWaitingForSerial;

        public Form1()
        {
            InitializeComponent();
            addButton.Enabled = false;
            clearButton.Enabled = false;
            textBoxName.Enabled = false;
            textBoxStudentID.Enabled = false;
            init();
        }

        private void FindESP8266()
        {
            string[] COMPorts = SerialPort.GetPortNames();

            foreach (string COMPort in COMPorts)
            {
                SerialPort port = new SerialPort(COMPort, 115200)
                {
                    NewLine = "\r\n",
                    Encoding = System.Text.Encoding.UTF8
                };

                try
                {
                    port.Open();
                    port.Write("c");

                    for (int i = 0; i < 10; i++)
                    {
                        Thread.Sleep(100);
                        if (port.BytesToRead == 0)
                        {
                            port.Write("F");
                        }
                        else break;
                    }
                    if (port.BytesToRead == 0)
                    {
                        port.Dispose();
                        continue;
                    }
                    string response = port.ReadLine();
                    if (response == "Connected")
                    {
                        serialPort = port;
                        serialPort.DiscardInBuffer();
                        return;
                    }
                }
                catch (Exception)
                {
                    continue;
                }

                port.Dispose();
            }
        }

        private async void init()
        {
            await Task.Delay(200);
            while (serialPort == null) await Task.Run(() => FindESP8266());
            statusLabel.Text = "Đã kết nối với ESP8266 tại " + serialPort.PortName;
            statusLabel.ForeColor = Color.Green;
            addButton.Enabled = true;
            clearButton.Enabled = true;
            textBoxName.Enabled = true;
            textBoxStudentID.Enabled = true;

            serialPort.DataReceived += new SerialDataReceivedEventHandler(SerialPort_DataReceived);
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string data = serialPort.ReadLine();
            this.Invoke(new Action(() =>
            {
                serialOutput.AppendText(data + Environment.NewLine);
                if (data.Contains("EXIST"))
                {
                    MessageBox.Show("Student already exists. Please try again.");
                }
                else if (data.Contains("ADDED"))
                {
                    MessageBox.Show("Student added successfully.");
                }
                else if (data.Contains("UPDATED"))
                {
                    MessageBox.Show("Student updated successfully.");
                }
            }));
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            serialOutput.Clear();
            textBoxName.Clear();
            textBoxStudentID.Clear();
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            string studentName = textBoxName.Text;
            string studentId = textBoxStudentID.Text;
            // Gửi dữ liệu sinh viên qua cổng serial để thêm sinh viên
            serialPort.WriteLine($"ADD:{studentName},{studentId}");
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            string studentName = textBoxName.Text;
            string studentId = textBoxStudentID.Text;
            // Gửi dữ liệu sinh viên qua cổng serial để cập nhật sinh viên
            serialPort.WriteLine($"UPDATE:{studentName},{studentId}");
        }
    }
}
