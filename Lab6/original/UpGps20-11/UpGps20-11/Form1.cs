using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UpGps20_11
{
    public partial class Form1 : Form
    {
        private SerialPort port = new SerialPort("COM4", 9600, Parity.None, 8, StopBits.One);
        private string inData = "";
        //KodProgramu obiekt = new KodProgramu();
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            //var port = new SerialPort("COM20");

            port.DataReceived += new SerialDataReceivedEventHandler(DataReceivedEventHandler);

            port.Open();
            if (port.IsOpen)
                MessageBox.Show("Port otwarty");
            else
                MessageBox.Show("Blad otwierania portu");

            //obiekt.Connect();
            

        }

        public void DataReceivedEventHandler(object sender, SerialDataReceivedEventArgs e)
        {
            var senderPort = (SerialPort)sender;
            inData += senderPort.ReadExisting();
            textBoxData.Text = inData;
            //int indexOfLE = inData.IndexOf("\n");
            //string temp = inData.Substring(0, indexOfLE);

            /*if (temp.Contains("GPGGA"))
            {
                string[] table = inData.Split(',');
                string tempStr = "";
                foreach (var item in table)
                {
                    tempStr += item + " XYZ ";
                }

                MessageBox.Show(tempStr);
            }*/
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            port.Close();
            var ns = 0.0;
            var we = 0.0;
            string[] tempStr = null;
            bool gpsSignal = false;
            foreach (var line in textBoxData.Lines)
            {
                if(line.Contains("GPGGA"))
                {
                    tempStr = line.Split(',');
                    if(tempStr[2] != "")
                    {
                        gpsSignal = true;
                        ns = Convert.ToDouble(tempStr[2]) / 100;
                        we = Convert.ToDouble(tempStr[4]) / 100;
                        labelWsp.Text = ns.ToString() + " " + tempStr[3];
                        labelWspWE.Text = we.ToString() + " " + tempStr[5];
                        labelSat.Text = tempStr[7];
                        labelWys.Text = tempStr[9];
                    }
                }
            }
            if (!gpsSignal)
            {
                MessageBox.Show("Nie odnaleziono wspolrzednych.\nSproboj dluzej odczytywac dane z GPSa");
            }
            else
            {
                if (tempStr[3] == "S")
                    ns *= -1;
                if (tempStr[5] == "W")
                    we *= -1;
                var link = $"https://www.google.pl/maps/@{ns},{we},14z";
                webBrowserGPS.Navigate(link);
                textBoxLink.Text = link;
            }
        }
    }
}
