using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GPSWinForms
{
    public class Cords
    {
        public string Destination { get; set; }
        public double Data { get; set; }

        public int Degrees { get; set; }
        public int Mins { get; set; }
        public int Secs { get; set; }

        public override string ToString()
        {
            var template = "{0}°{1}'{2}.0\"{3}";

            return string.Format(template, this.Degrees, this.Mins, this.Secs, this.Destination);
        }
    }

    public partial class Form1 : Form
    {
        SerialPort serialPort;
        Cords dlug, szer;

        public Form1()
        {
            TextBox.CheckForIllegalCrossThreadCalls = false;

            InitializeComponent();

        }


        private void ProcessDataLine(string line)
        {
            var splited = line.Split(',');

            if (splited[0] == "GPGGA")
            { 
                var dSzer = double.Parse(splited[2]);
                var dSzerSplit = dSzer.ToString().Split('.');
                szer = new Cords()
                {
                    Data = dSzer,
                    Destination = splited[3],
                    Degrees = int.Parse(dSzerSplit[0]) / 100,
                    Mins = int.Parse(dSzerSplit[0]) % 100,
                    Secs = (int)(int.Parse(dSzerSplit[1]) * 0.6) / 100
                };

                var dDlug = double.Parse(splited[4]);
                var dDlugSplit = dDlug.ToString().Split('.');
                dlug = new Cords()
                {
                    Data = dDlug,
                    Destination = splited[5],
                    Degrees = int.Parse(dDlugSplit[0]) / 100,
                    Mins = int.Parse(dDlugSplit[0]) % 100,
                    Secs = (int)(int.Parse(dDlugSplit[1]) * 0.6) / 100
                };

                //Wyswietlanie
                txtBoxPositionLong.Text = szer.ToString();     //Szerokosc geograficzna
                txtBoxPositionLatidute.Text = dlug.ToString(); //Dlugosc geograficzna

                txtSatelites.Text = splited[7];     //Ilosc satelit
                txtHighAboveSee.Text = splited[9];  //Wysokosc nad poziomem morza
            }

        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            var sPort = txtBoxSerialPort.Text.Trim();

            serialPort = new SerialPort(sPort)
            {
                Parity = Parity.None,
                //StopBits = StopBits.None,
                DataBits = 8,
                Handshake = Handshake.None,
                BaudRate = 9600
            };

            Debug.Print("Nasluchuje");

            serialPort.DataReceived += (s, ev) => {
                var sp = (SerialPort)s;
                var indata = sp.ReadExisting();
                MessageBox.Show(indata);
                Debug.Print("Data Recived: \n" + indata);

                var splited = indata.Split('$')
                    .ToList()
                    .Where(l => !string.IsNullOrEmpty(l))
                    .ToList();

                try
                {
                    splited.ForEach(ProcessDataLine);
                }
                catch { }
            };

            serialPort.Open();
        }

        private void btnShowInBrowser_Click(object sender, EventArgs e)
        {
            var navigateLink = "https://www.google.pl/maps/dir//";

            var dir = szer + " " + dlug;

            System.Diagnostics.Process.Start("iexplore", navigateLink + dir);
        }

        private void txtSatelites_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
