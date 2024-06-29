using System.IO.Ports;
using System.Text;

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

        }

        private void clearButton_Click(object sender, EventArgs e)
        {

        }

        private void addButton_Click(object sender, EventArgs e)
        {

        }
    }
}
