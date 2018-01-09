using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp2
{
    public partial class Form2 : Form
    {
        BluetoothDeviceInfo device;
        public Form2(BluetoothDeviceInfo device)
        {
            InitializeComponent();
            this.device = device;

            labelName.Text = device.DeviceName;
            labelMac.Text = device.DeviceAddress.ToString();
            labelConnected.Text = device.Connected.ToString();

            backgroundWorker1.DoWork += new DoWorkEventHandler(backgroundWorker1_DoWork);
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void buttonPair_Click(object sender, EventArgs e)
        {
            listBox2.Items.Add("Pair request send!");
            
        }

        private bool pair()
        {

        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            if(pair())
        }
    }
}
