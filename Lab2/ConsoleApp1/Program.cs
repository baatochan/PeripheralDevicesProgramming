using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SharpDX.DirectInput;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Threading;

namespace ConsoleApp1
{
    class Program
    {
        [DllImport("User32.Dll")]
        public static extern long SetCursorPos(int x, int y);

        [DllImport("User32.Dll")]
        public static extern bool ClientToScreen(IntPtr hWnd, ref POINT point);
        [StructLayout(LayoutKind.Sequential)]
        public struct POINT
        {
            public int x;
            public int y;
        }

        static void Main(string[] args)
        {
            // Initialize DirectInput
            var directInput = new DirectInput();

            // Find a Joystick Guid
            var joystickGuid = Guid.Empty;
            var deviceInstanceList = new List<DeviceInstance>();
            int choosen;
            foreach (var deviceInstance in directInput.GetDevices(DeviceType.Gamepad,
                        DeviceEnumerationFlags.AllDevices))
            {
                deviceInstanceList.Add(deviceInstance);
            }
            foreach (var deviceInstance in directInput.GetDevices(DeviceType.Joystick,
                        DeviceEnumerationFlags.AllDevices))
            {
                deviceInstanceList.Add(deviceInstance);
            }

            Console.Out.WriteLine("Choose one: \n");
            foreach (var deviceInstance in deviceInstanceList)
            {
                Console.Out.WriteLine(deviceInstance.InstanceName);
            }

            joystickGuid = deviceInstanceList[((int)Console.In.Read()) - 49].InstanceGuid;

            // If Joystick not found, throws an error
            if (joystickGuid == Guid.Empty)
            {
                Console.WriteLine("No joystick/Gamepad found.");
                Console.ReadKey();
                Environment.Exit(1);
            }

            // Instantiate the joystick
            var joystick = new Joystick(directInput, joystickGuid);

            Console.WriteLine("Found Joystick/Gamepad with GUID: {0}", joystickGuid);

            // Query all suported ForceFeedback effects
            var allEffects = joystick.GetEffects();
            foreach (var effectInfo in allEffects)
                Console.WriteLine("Effect available {0}", effectInfo.Name);

            // Set BufferSize in order to use buffered data.
            joystick.Properties.BufferSize = 128;

            // Acquire the joystick
            joystick.Acquire();

            // Poll events from joystick
            var BaseX = joystick.GetCurrentState().ForceX;
            var BaseY = joystick.GetCurrentState().ForceY;
            var x = 0;
            var y = 0;
            while (true)
            {
                joystick.Poll();
                var datas = joystick.GetBufferedData();
                foreach (var state in datas)
                {
                    Console.WriteLine(state);
                }
                //Thread.Sleep(1000);

                /*SetCursorPos(Cursor.Position.X +
                    BaseX - joystick.GetCurrentState().ForceX>0?1:-1,
                    Cursor.Position.Y -
                    (BaseY - joystick.GetCurrentState().ForceY>0?1:-1)
                    );
                    */
            }

        }
    }
}
