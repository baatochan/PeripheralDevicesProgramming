using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Diagnostics;

namespace GPS_v._2
{

    public partial class Form1 : Form
    {

        public static SerialPort port;
        char[] odczyt;
        char[] czas, szerokosc, dlugosc, liczbaSatelitow, fi, lambda, status, wspolczynnik, wysokosc;
        //string czas, szerokosc, dlugosc, liczbaSatelitow, fi, lambda, status, wspolczynnik, wysokosc;
        string stan;
        double szer, dlug;
        int i, szerMin, dlugMin, szerA, dlugA;
        void przenies(char[] stara, char[] nowa)   //funkcja kopiująca z tablica do mniejszych tablic do przecinka  
        {

            i++;
            int j = 0;
            for (; stara[i] != ','; i++)
                nowa[j++] = stara[i];
            nowa[j] = '\0';                  //znak null na końcu C-stringa
        }
        public void OpenConnection()
        {
            if (port != null)
            {
                if (port.IsOpen)
                {
                    textBoxInf.AppendText("Port jest otwarty. 1");
                    textBoxInf.AppendText(Environment.NewLine);
                }
                else
                {
                    port.Open();
                    port.ReadTimeout = 100000;
                    port.WriteTimeout = 10000;
                    textBoxInf.AppendText("Port został otwarty. 2");
                    textBoxInf.AppendText(Environment.NewLine);
                }
            }
            else
            {
                if (port.IsOpen)
                {
                    textBoxInf.AppendText("Port jest otwarty. 3");
                    textBoxInf.AppendText(Environment.NewLine);
                }
                else
                {
                    textBoxInf.AppendText("Port == Null");
                    textBoxInf.AppendText(Environment.NewLine);
                }
                
            }
        }
        public Form1()
        {
            i = 0;
            odczyt = new char[512];
            czas = new char[512];
            szerokosc = new char[512];
            dlugosc = new char[512];
            liczbaSatelitow = new char[512];
            fi = new char[512];
            lambda = new char[512];
            status = new char[512];
            wspolczynnik = new char[512];
            wysokosc = new char[512];
            
            InitializeComponent();
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            buttonStart.Enabled = false;
            odczyt = new char[512];
            port = new SerialPort("COM8", 9600, Parity.None, 8, StopBits.One);
            port.Handshake = Handshake.None;
            OpenConnection();
            port.Read(odczyt, 0, 512);

            for (; i < 100; i++)
                if (odczyt[i] == 'G' && odczyt[i + 1] == 'G' && odczyt[i + 2] == 'A')    //naglowek protokolu
                {
                    i += 3;
                    przenies(odczyt, czas);//kopiowanie kolejnych wartości do tablic
                    przenies(odczyt, szerokosc);
                    przenies(odczyt, fi);
                    przenies(odczyt, dlugosc);
                    przenies(odczyt, lambda);
                    przenies(odczyt, status);
                    przenies(odczyt, liczbaSatelitow);
                    przenies(odczyt, wspolczynnik);
                    przenies(odczyt, wysokosc);
                    break;
                }
            String strSzerokosc = new string(szerokosc);
            String strFi = new string(fi);
            String strDlugosc = new string(dlugosc);
            String strLambda = new string(lambda);
            String strStatus = new string(status);
            String strLiczba = new string(liczbaSatelitow);
            String strWysokosc = new string(wysokosc);
            textBoxInf.AppendText("Czas "+czas[0].ToString()+ czas[1].ToString() + ":" + czas[2].ToString() + czas[3].ToString());
            textBoxInf.AppendText(Environment.NewLine);
            textBoxInf.AppendText("Szerokość z GPS: "+strSzerokosc+" "+strFi);
            textBoxInf.AppendText(Environment.NewLine);
            textBoxInf.AppendText("Dlugość z GPS: "+strDlugosc+" "+strLambda);
            textBoxInf.AppendText(Environment.NewLine);
            int stanInt = int.Parse(strStatus);
             if (stanInt == 1)
                 stan= " - tryb SPS, rozwiazanie fix";
             if (stanInt == 0)
                 stan=" - nieprawidlowa";
                 
            textBoxInf.AppendText("Status wyznaczonej pozycji: "+strStatus+" "+stan);
            textBoxInf.AppendText(Environment.NewLine);
            textBoxInf.AppendText("Liczba Satelitów: "+strLiczba);
            textBoxInf.AppendText(Environment.NewLine);
            textBoxInf.AppendText("Wysokość nad poziomem morza: " +strWysokosc);
            textBoxInf.AppendText(Environment.NewLine);
            szer = Double.Parse(strSzerokosc,System.Globalization.CultureInfo.InvariantCulture);
            dlug = Double.Parse(strDlugosc, System.Globalization.CultureInfo.InvariantCulture);
            szerMin = (int)Math.Floor(szer);
            dlugMin = (int)Math.Floor(dlug);
            szerA = szerMin;
            dlugA = dlugMin;
            szerMin %= 100;
            szerA /= 100;
            dlugMin %= 100;
            dlugA /= 100;

            textBoxInf.AppendText("Szerokość geograficzna: " + szerA+" stopni "+szerMin+"'"+ (szer - (int)szer) * 60+"\"");
            textBoxInf.AppendText(Environment.NewLine);
            textBoxInf.AppendText("Dlugosc geograficzna: " + dlugA + " stopni " + dlugMin + "'" + (dlug - (int)dlug) * 60 + "\"");
            textBoxInf.AppendText(Environment.NewLine);
            port.Close();
            buttonShow.Enabled = true;
            buttonShow.Visible = true;
        }
        private void buttonShow_Click(object sender, EventArgs e)
        {
            System.Globalization.CultureInfo customCulture = (System.Globalization.CultureInfo)System.Threading.Thread.CurrentThread.CurrentCulture.Clone();
            customCulture.NumberFormat.NumberDecimalSeparator = ".";

            System.Threading.Thread.CurrentThread.CurrentCulture = customCulture;
            string google = "https://www.google.pl/maps/@";                 //string z adresem internetowym 
            double testSzer = (((szer - (int)szer) + szerMin) / 60) + szerA;
            google += testSzer;
            google += ",";
            double testDlug = (((dlug - (int)dlug) + dlugMin) / 60) + dlugA;
            google += testDlug;
            google += ",20z";
            Process.Start("chrome", google);
        }
    }
}
