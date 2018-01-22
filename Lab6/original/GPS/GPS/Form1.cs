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
            Port.Close();
            Port.PortName = textBox1.Text;
            Port.Open();
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string czas="", wys = "", szer="", sat="",w1="",s1="";
            double w, s;
            string dane = Port.ReadExisting();
        

            try
            {
                czas += dane[7].ToString() + dane[8] + ":" + dane[9] + dane[10] + ":" + dane[11] + dane[12];
                textBox3.Text = czas;

                int w2, s2;

                for (int i = 20; i < 27; i++)
                    wys += dane[i].ToString();

                w = Convert.ToDouble(wys);
                w /= 60.0;
                w *= 100000;
                w2 = Convert.ToInt32(w);

                w1 = dane[18].ToString() + dane[19].ToString() + "." + w2.ToString();
                textBox4.Text = w1;

                for (int i = 33; i < 40; i++)
                    szer += dane[i].ToString();

                s = Convert.ToDouble(szer);
                s /= 60.0;
                s *= 100000;
                s2 = Convert.ToInt32(s);

                s1 = dane[31].ToString() + dane[32].ToString() + ".0" + s2.ToString();
                textBox5.Text = s1;
                textBox6.Text = dane;
               
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

            webBrowser1.Navigate("https://mapa.targeo.pl/" + textBox4.Text + "%20" + textBox5.Text + "%20");
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
