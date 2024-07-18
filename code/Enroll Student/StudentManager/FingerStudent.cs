using System.IO.Ports;
using System.Text;
using System.Text.RegularExpressions;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace StudentManager
{
    public partial class FingerStudent : Form
    {
        private static SerialPort? serialPort = null;

        public FingerStudent()
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
            while (serialPort == null)
            {
                await Task.Run(() => FindDevice());
            }
            ReadSerial();
            CheckComStatus();
        }


        private void FindDevice()
        {
            string[] COMPorts = SerialPort.GetPortNames();

            SerialPort? port = new SerialPort();

            foreach (string COMPort in COMPorts)
            {
                port.Dispose();
                try
                {
                    port = new SerialPort(COMPort, 115200)
                    {
                        NewLine = "\r\n",
                        Encoding = System.Text.Encoding.UTF8,
                        ReadTimeout = 1000,
                        WriteTimeout = 1000
                    };
                    port.Open();
                    if (port.IsOpen)
                    {
                        port.DiscardInBuffer();
                        port.Write("c");
                        port.NewLine = "\r\n";
                        // Read the response from the device if read timeout is not reached
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
                    port.Dispose();
                    Task.Delay(5000);
                }
            }
        }
        private async void ReadSerial()
        {
            while (true)
            {
                await Task.Delay(100);
                if (serialPort != null && serialPort.IsOpen)
                {
                    try
                    {
                        string response = serialPort.ReadLine().Replace("\r", "");
                        if (response.Contains("DONE"))
                        {
                            return;
                        }
                        if (response != "")
                        {
                            Invoke(new Action(() =>
                            {
                                serialOutput.AppendText(response + "\r\n");
                            }));
                        }
                    }
                    catch (Exception e)
                    {
                        
                    }
                }
            }
        }

        private async void CheckComStatus()
        {
            while (true)
            {
                await Task.Delay(800);
                if (serialPort == null || !serialPort.IsOpen)
                {
                    statusLabel.Text = "Đã ngắt kết nối!!";
                    statusLabel.ForeColor = Color.Red;
                    serialPort.Dispose();
                    serialPort.Close();
                    serialPort = null;
                    addButton.Enabled = false;
                    clearButton.Enabled = false;
                    textBoxName.Enabled = false;
                    textBoxStudentID.Enabled = false;
                    init();
                    break;
                }
            }
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            serialOutput.Clear();
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            if (textBoxName.Text == "" || textBoxStudentID.Text == "")
            {
                MessageBox.Show("Vui lòng nhập đầy đủ thông tin");
                return;
            }
            if (Regex.IsMatch(textBoxStudentID.Text, @"^\S{2}\d{6}$") == false)
            {
                MessageBox.Show("Mã sinh viên không hợp lệ");
                return;
            }
            serialPort.Write("a" + textBoxStudentID.Text + ";" + textBoxName.Text);
            ReadSerial();
            textBoxName.Text = "Nhập tên sinh viên";
            textBoxStudentID.Text = "Nhập mã sinh viên";
        }
    }
}
