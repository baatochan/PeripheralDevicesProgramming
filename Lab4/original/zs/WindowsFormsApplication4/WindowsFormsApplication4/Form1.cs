using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Automation.BDaq;
using System.IO;

namespace WindowsFormsApplication4
{
    public partial class Form1 : Form
    {
        delegate void UpdateUIDelegate();
        double[] m_dataScaled;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            m_dataScaled = new double[bufferedAiCtrl1.BufferCapacity];
            bufferedAiCtrl1.Streaming = true;
            bufferedAiCtrl1.Prepare();
        }

        private void bufferedAiCtrl1_DataReady(object sender, BfdAiEventArgs e)
        {
            bufferedAiCtrl1.GetData(e.Count, m_dataScaled);
            System.IO.FileStream fs = new FileStream(Directory.GetCurrentDirectory().ToString() + "lapszo1.txt",
                FileMode.OpenOrCreate, FileAccess.ReadWrite);
            this.Invoke((UpdateUIDelegate)delegate ()
            {
                StreamWriter sw = new StreamWriter(fs);
                for (int i = 0; i< e.Count; ++i)
                {
                    listBoxData.Items.Add(m_dataScaled[i].ToString());
                    sw.WriteLine(m_dataScaled[i].ToString());
                }
                sw.Close();
            });
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            bufferedAiCtrl1.Start();
        }
    }
}
