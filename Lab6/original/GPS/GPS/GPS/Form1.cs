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

namespace GPS
{
    public partial class Form1 : Form
    {
        public SerialPort Port = new SerialPort();
        public Form1()
        {
            InitializeComponent();   
        }


        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Port.PortName = textBox1.Text;
            Port.Open();
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string czas="", wys = "", szer="", sat="",w1="",s1="";
            double w, s, alt;
            int wysokosc, szerokosc;
            string dane = Port.ReadExisting();

            Console.WriteLine("dfsdfsd");

            try
            {

                int w2, s2;

                for (int i = 19; i < 26; i++)
                    wys += dane[i].ToString();

                czas = dane[7].ToString() + ((char)((int)(dane[8]+1))) + ":" + dane[9] + dane[10] + ":" + dane[11] + dane[12];

                w = Convert.ToDouble(wys);
                w /= 60.0;
                w *= 100000;
                w2 = Convert.ToInt32(w);

                textBox3.Text = wys;


                w1 = dane[18].ToString() + dane[19].ToString();
                string w4 = w1 + "." + w2;
                textBox100.Text = w4;
                float w3 = w2 / 3600.0f;
                textBox4.Text = w1 + "." + Math.Round(w3, 2).ToString();

                for (int i = 33; i < 40; i++)
                    szer += dane[i].ToString();

                s = Convert.ToDouble(szer);
                s /= 60.0;
                s *= 100000;
                s2 = Convert.ToInt32(s);

                s1 = dane[31].ToString() + dane[32].ToString();
                string s4 = s1 + "." + s2;
                textBox101.Text = s4;
                float s3 = s2 / 3600.0f;
                textBox5.Text = s1 + "." + Math.Round(s3, 2).ToString();
                textBox6.Text = czas;
               
            }
            catch { };
           }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {

        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {

            webBrowser1.Navigate("https://mapa.targeo.pl/" + textBox100.Text + "%20" + textBox101.Text + "%20");
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox100_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox101_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
