using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.Globalization;

namespace GPS
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        bool condition;
        SerialPort sp;
        double szer, dl;
        int k;
        Thread readThread;
        private void button1_Click(object sender, EventArgs e)
        {
            //string gga = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47"; Sztywny przykład ponieważ nie udało nam się złapać sygnału od satelity
            //textBox1.Text = gga;
            //string[] tab = gga.Split(',');
            //gpgga(tab);


            szer = 0.0f;
            dl = 0.0f;
            k = 0;
            StringComparer stringComparer = StringComparer.OrdinalIgnoreCase;


            sp = new SerialPort();


            sp.PortName = "COM22";
            sp.BaudRate = 9600;
            sp.Parity = Parity.None;
            sp.DataBits = 8;
            sp.StopBits = StopBits.One;
            sp.Handshake = Handshake.None;

            sp.ReadTimeout = 1000;
            sp.WriteTimeout = 1000;

            sp.Open();






     

        }

        public void Read()
        {

            while (condition)
            {
                if (k > 1000)
                {
                    k = 0;
                    try
                    {
                        string message = sp.ReadLine();
                        string[] parts = message.Split(',');
                        Console.WriteLine(message);
                        textBox1.Text = message;
                        switch (parts[0])
                        {
                            case "$GPGGA": gpgga(parts); break;
                            default: message = ""; break;
                        }

                        Console.WriteLine(message);
                    }
                    catch (TimeoutException) { }
                }
                else
                {
                    k++;
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            sp.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string message = "";


            while (message.Equals(""))
            {

                try
                {
                    message = sp.ReadLine();
                }
                catch (TimeoutException)
                {

                }


                string[] parts = message.Split(',');
                if (parts[0].Equals("$GPGGA"))
                {
                    textBox1.Text = message;
                    gpgga(parts);
                }
                else
                {
                    message = "";
                }
            }
        }

        private void gpgga(string[] tab)
        {

            if (!tab[2].Equals(""))
                textBox2.Text = string.Format("Szer : {0} st {1} min {2} sek {3} \n\r", tab[2].Substring(0, 2), tab[2].Substring(2, 2), Convert.ToInt32(tab[2].Substring(5, 3)) * 0.6, tab[3]);
            else
                textBox2.Text = "Brak szerokosci geograficznej\n";

            if (!tab[4].Equals(""))
                textBox3.Text = string.Format("Dłu : {0} st {1} min {2} sek {3} \n\r", tab[4].Substring(0, 3), tab[4].Substring(3, 2), Convert.ToInt32(tab[4].Substring(6, 3)) * 0.6, tab[5]);
            else
                textBox3.Text = "Brak długosci geograficznej\n";

            textBox4.Text = string.Format("Fix quality : {0}\n", tab[6]);
            textBox5.Text = string.Format("Ilość satelit : {0}", tab[7]);
            NumberFormatInfo p = new NumberFormatInfo();
            p.NumberDecimalSeparator = ".";


            Double szer1 = Double.Parse(tab[2].Substring(0, 2));
            Double szer2 = Double.Parse(tab[2].Substring(2, 6));

            Double dl1 = Double.Parse(tab[4].Substring(0, 3));
            Double dl2 = Double.Parse(tab[4].Substring(3, 6));

            szer2 = szer2 / 60;
            szer1 = szer1 + szer2;

            dl2 = dl2 / 60;
            dl1 = dl1 + dl2;

            string url = string.Format("https://www.openstreetmap.org/#map=16/{0}/{1}", szer1.ToString(CultureInfo.InvariantCulture), dl1.ToString(CultureInfo.InvariantCulture));
            textBox6.Text = url;
            webBrowser1.Navigate(url,null,null, "User-Agent: howtofix.pro rullz!");


        }
    }
}