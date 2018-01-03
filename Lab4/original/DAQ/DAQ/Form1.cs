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

namespace DAQ
{
    public partial class Form1 : Form
    {
        static int numberDevice = 0, startChannel = 4, channels = 1, times = 0;
        static InstantAiCtrl ctrl = null;
        static double[] data = null;
        StreamWriter sw = null;
        public Form1()
        {
            InitializeComponent();
            ctrl = new InstantAiCtrl();
            ctrl.SelectedDevice = new DeviceInformation(numberDevice);
            data = new double[channels];
            if (!ctrl.Initialized)
            {
                MessageBox.Show("Nie znaleziono urzadzenia");
                this.Close();
                return;
            }
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            times = 0;
            timer1.Start();
            StartButton.Enabled = false;
            StopButton.Enabled = true;
            sw = File.CreateText("data.txt");
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            timer1.Stop();
            sw.Close();
            StartButton.Enabled = true;
            StopButton.Enabled = false;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            ErrorCode error = ErrorCode.Success;
            error = ctrl.Read(startChannel, channels, data);
            if (error != ErrorCode.Success)
            {
                MessageBox.Show("Błąd");
                timer1.Stop();
                sw.Close();
                StartButton.Enabled = true;
                StopButton.Enabled = false;
            }
            else
            {
               // sw.Write(times * timer1.Interval);
                sw.Write(" ");
             //   sw.Write("\n");
                for (int j = 0; j < channels; j++)
                {
                    sw.Write(data[j]);
              //      sw.Write(" ");
                }
                sw.Write("\n");
                times++;
            }
        }
    }
}
