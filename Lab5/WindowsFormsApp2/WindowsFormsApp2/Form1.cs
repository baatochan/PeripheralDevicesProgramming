using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using InTheHand.Net.Sockets;
using System.Threading;
using System.Collections;

namespace WindowsFormsApp2
{
    public partial class Form1 : Form
    {
        BluetoothDeviceInfo[] devices;
        List<String> result;
        Thread thread;
        bool done = false;

        public Form1()
        {
            InitializeComponent();
            statusLabel.Text = "DONE";
            result = new List<String>();
            button1.Text = "Reload";
        }

        public void getDevices()
        {
            done = false;
            using (BluetoothClient sdp = new BluetoothClient())
                devices = sdp.DiscoverDevices();

            result.Clear();
            foreach (BluetoothDeviceInfo deviceInfo in devices)
            {
                Debug.WriteLine(string.Format("{0} ({1})", deviceInfo.DeviceName, deviceInfo.DeviceAddress));
                result.Add(string.Format("{0} ({1})", deviceInfo.DeviceName, deviceInfo.DeviceAddress));
            }
            done = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (statusLabel.Text != "DONE")
                return;

            timer1.Start();
            statusLabel.Text = "RELOADING";
            thread = new Thread(getDevices);
            thread.Start();
        }

        private void checkStatus(object sender, EventArgs e)
        {
            if (!done)
                return;

            statusLabel.Text = "DONE";

            checkedListBox1.Items.Clear();
            foreach(String variable in result)
            {
                checkedListBox1.Items.Add(variable);
            }

            timer1.Stop();
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Form2 form = new Form2(devices[checkedListBox1.SelectedIndex]);
            form.ShowDialog();
        }
    }
}
