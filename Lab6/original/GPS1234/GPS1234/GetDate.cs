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
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;

namespace GPS1234
{
    class GetDate
    {
        SerialPort serialPort;
        string dlug = "";
        string szer = "";
        string port = "";
        Label labelDane;
        public GetDate(string port1, ref Label labelDane1)
        {
            labelDane = labelDane1;
            port = port1;
            connect();
            //openInBrowser();
        }
        private void ProcessDataLine(string line)
        {
            var splited = line.Split(',');
            string h = "";
            if (splited[0] == "GPGGA")
            {
                foreach(string spl in splited) h += spl + " ";
                MessageBox.Show(h);
                var dSzer = double.Parse(splited[2]);
                var dSzerSplit = dSzer.ToString().Split('.');
                szer = (((Double.Parse(splited[2])) / 100).ToString() + "," + (Double.Parse(splited[4]) / 100).ToString());
                // odczytuje godzine
                int hour1 = splited[1].Split('.')[0][0] - '0';
                int hour2 = splited[1].Split('.')[0][1] - '0';
                int min1 = splited[1].Split('.')[0][2] - '0';
                int min2 = splited[1].Split('.')[0][3] - '0';
                int sec1 = splited[1].Split('.')[0][4] - '0';
                int sec2 = splited[1].Split('.')[0][5] - '0';
                DateTime x = new DateTime(2017, 10, 10, hour1*10+hour2,min1*10+min2,sec1*10+sec2);
                string y = "Dlugosc: " + dlug + "\nSzerokosc: " + szer + "\nCzas: " + x.ToString() + "\nIlosc satelitow: " + splited[7] + "\nWysokosc: " + splited[8].ToString() + "m.n.p.m";
                MessageBox.Show(y);
                //labelDane.Text = y;
            }

        }

        public void connect()
        {
            serialPort = new SerialPort(port)
            {
                Parity = Parity.None,
                DataBits = 8,
                Handshake = Handshake.None,
                BaudRate = 9600
            };

            serialPort.DataReceived += (s, ev) =>
            {
                var sp = (SerialPort)s;
                var indata = sp.ReadExisting();
                var splited = indata.Split('$');
                string h = "";
                foreach (var j in splited) h += j+" ";
                try
                {
                    foreach (var sss in splited)
                    {
                        ProcessDataLine(sss);
                        //if (szer != "")
                        //{
                        //    openInBrowser();
                        //    System.Threading.Thread.Sleep(1000000);
                        //}
                    }
                }
                catch { }
            };

            serialPort.Open();
        }
        public void openInBrowser()
        {
            string d1 = @"http://www.google.com/maps/place/" + szer;
            ChromeDriver driver = new ChromeDriver();
            driver.Url =  d1;
        }
    }
}
