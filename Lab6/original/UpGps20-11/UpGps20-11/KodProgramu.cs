using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UpGps20_11
{
    class KodProgramu
    {
        private SerialPort port = new SerialPort("COM24", 9600, Parity.None, 8, StopBits.One);
        private string inData;

        public void Connect()
        {
            port.DataReceived += new SerialDataReceivedEventHandler(DataReceivedEventHandler);

            if (!port.IsOpen)
                port.Open();
            else
            {
                port.Close();
                port.Open();
            }
        }

        public void PortClose()
        {
            port.Close();
        }

        public string ParseData()
        {
            int indexOfLE = inData.IndexOf("\n");
            string temp = inData.Substring(0, indexOfLE);

            if (temp.Contains("GPGGA"))
            {
                string[] table = inData.Split(',');
                string tempStr = "";
                foreach (var item in table)
                {
                    tempStr += item;
                }

                MessageBox.Show(tempStr);
            }

            return "123";
        }

        public void DataReceivedEventHandler(object sender, SerialDataReceivedEventArgs e)
        {
            var senderPort = (SerialPort)sender;
            inData = senderPort.ReadExisting();
            ParseData();
        }
    }
}
