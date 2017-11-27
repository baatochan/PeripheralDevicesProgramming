using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX.DirectInput;
using System.Threading;
namespace Joystick1
{
    public partial class Form1 : Form
    {
        Device joystickDevice;
        JoystickState state, temp_state;
        System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
        public Form1()
        {
            InitializeComponent();
            this.MouseClick += mouseClick;
            timer.Tick += timer1_Tick; // Everytime timer ticks, timer_Tick will be called
            timer.Interval = (1000);             // Timer will tick evert 1 second
            timer.Enabled = true;              
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // 1. Finding device attatched to usb port
            // find attachted devices
            DeviceList deviceList = Manager.GetDevices(DeviceClass.GameControl, EnumDevicesFlags.AttachedOnly);
            // checking whether at least one device is present
            if (deviceList.Count > 0)
            {
                // take the first device from the list
                deviceList.MoveNext();
                DeviceInstance deviceInstance = (DeviceInstance)
                    deviceList.Current;

                // create a joystick instance 
                joystickDevice = new Device(deviceInstance.InstanceGuid);
                // Tell DirectX that this is a Joystick.
                joystickDevice.SetDataFormat(DeviceDataFormat.Joystick);
                // set ranges
                //Set joystick axis ranges.
                foreach (DeviceObjectInstance doi in joystickDevice.Objects)
                {
                    if ((doi.ObjectId & (int)DeviceObjectTypeFlags.Axis) != 0)
                    {
                        joystickDevice.Properties.SetRange(
                            ParameterHow.ById,
                            doi.ObjectId,
                            new InputRange(-100, 100));
                    }
                }


                // Finally, acquire the device.
                joystickDevice.Acquire();
                MessageBox.Show("Wykryto urządzenie!");
                //   textBox1.Text = "Joystick podłączony";
                if (joystickDevice == null)
                {
                    //Throw exception if joystick not found.
                    throw new Exception("No joystick found.");
                }
                else
                {
                    textBox1.Clear();
                    textBox1.Text = joystickDevice.DeviceInformation.InstanceName.ToString();
                    textBox2.Text = "0";
                    textBox3.Text = "0";
                    textBox4.Text = "0";
                    //temp_state = joystickDevice.CurrentJoystickState;
                }
            
            }
        }

        private void updateJoystick()
        {
                joystickDevice.Poll();
                state = joystickDevice.CurrentJoystickState;
                textBox2.Text = state.X.ToString();
                textBox3.Text = state.Y.ToString();
                textBox4.Text = state.Z.ToString();
                
                byte[] buttons = state.GetButtons();
                if (buttons[0] != 0)
                {
                    mouseClick(this, new MouseEventArgs(MouseButtons.Left, 0, 0, 0, 0));
                }
                if (buttons[1] != 0)
                {
                    mouseClick(this, new MouseEventArgs(MouseButtons.Right, 0, 0, 0, 0));
                }
                this.Cursor = new Cursor(Cursor.Current.Handle);
                Cursor.Position = new Point(Cursor.Position.X - Math.Abs(state.X - temp_state.X) / 1000, Cursor.Position.X - Math.Abs(state.Y - temp_state.Y) / 1000);
                temp_state = joystickDevice.CurrentJoystickState;
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            updateJoystick();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            timer.Start();
        }
        private void mouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                MessageBox.Show("Left button clicked!");

            }
            if (e.Button == MouseButtons.Right)
            {
                MessageBox.Show("Right button clicked!");
            }
        }
    }
}
