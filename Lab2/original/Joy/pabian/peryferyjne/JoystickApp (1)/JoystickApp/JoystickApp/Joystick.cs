using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX.DirectInput;
using System.Windows.Forms;
using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace JoystickApp
{
    class Joystick
    {
        public Device joystickDevice; // obiekt pozwalający na komunikację z kontrolerem
        public JoystickState state; // przechowanie informacji o statusie kontrolera
        public int Xaxis = 0; // ruch horyzontalny
        public int Yaxis = 0; // ruch wertykalny
        private IntPtr hWnd; // handler do okna, na którym będzie pracował kontroler
        public bool[] buttons; // tablica stanów przycisków
        private string systemJoysticks; // string przechowujący informację o urządzeniu
        public string joyName; // string przechowujący nazwę podłączonego urządzenia

        // importowanie funcji mouse_event, by móc symulować kliknięcia myszy za pomoca innych urządzeń
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern void mouse_event(uint flag, uint _x, uint _y, uint btn, uint exInfo);
        public const int MOUSEEVENT_LEFTDOWN = 0x0002; // numer odpowiada danej opracji na myszce
        public const int MOUSEEVENT_LEFTUP = 0x0004;
        public const int MOUSEEVENT_RIGHTDOWN = 0x0008;
        public const int MOUSEEVENT_RIGHTUP = 0x0010;
        private bool leftClicked;
        private bool rightClicked;

        public Joystick(IntPtr window_handle)
        {
            hWnd = window_handle; // przypisanie handlera
        }

        public string FindJoysticks()
        {
            systemJoysticks = null;

            try
            {
                // szukanie podłączonych kontrolerów
                DeviceList gameControllerList = Manager.GetDevices(DeviceClass.GameControl, EnumDevicesFlags.AttachedOnly);

                // sprawdzenie, czy zostało znalezione przynajmniej jedno urządzenie
                if (gameControllerList.Count > 0)
                {
                    foreach (DeviceInstance deviceInstance in gameControllerList)
                    {
                        // tworzenie obiektu urządzenia ze znalezionego kontrolera, by móc pobierać informacje
                        joystickDevice = new Device(deviceInstance.InstanceGuid);
                        joystickDevice.SetCooperativeLevel(hWnd, CooperativeLevelFlags.Background | CooperativeLevelFlags.NonExclusive);

                        systemJoysticks = joystickDevice.DeviceInformation.InstanceName;

                        break;
                    }
                }
            }
            catch
            {
                return null;
            }
            return systemJoysticks;
        }
       
        public bool AcquireJoystick(string name)
        {
            try
            {
                DeviceList gameControllerList = Manager.GetDevices(DeviceClass.GameControl, EnumDevicesFlags.AttachedOnly);
                bool found = false;

                foreach (DeviceInstance deviceInstance in gameControllerList)
                {
                    // jeśli zostanie znalezione urządzenie o podanym identyfikatorze, funkcja tworzy stałe połączenie z urządzeniem
                    if (deviceInstance.InstanceName == name)
                    {
                        found = true;
                        joyName = deviceInstance.InstanceName;
                        joystickDevice = new Device(deviceInstance.InstanceGuid);
                        joystickDevice.SetCooperativeLevel(hWnd, CooperativeLevelFlags.Background | CooperativeLevelFlags.NonExclusive);
                        break;
                    }
                }

                if (!found)
                    return false;

                // ustawienie interpretacji ruchu kontrolera
                joystickDevice.SetDataFormat(DeviceDataFormat.Joystick);
                foreach (DeviceObjectInstance doi in joystickDevice.Objects)
                {
                    if ((doi.ObjectId & (int)DeviceObjectTypeFlags.Axis) != 0)
                    {
                        joystickDevice.Properties.SetRange(ParameterHow.ById, doi.ObjectId, new InputRange(-100, 100));
                    }
                }
                // uzyskiwanie dostępu do urządzenia
                joystickDevice.Acquire();
                UpdateStatus();
            }
            catch (Exception err)
            {
                return false;
            }
            return true;
        }

        public void MouseMov(int posx, int posy)
        {
            // aktualizacja pozycji kursora
            Cursor.Position = new Point(Cursor.Position.X + posx / 2, Cursor.Position.Y + posy / 2);
        }

        public void UpdateStatus()
        {
            Poll();

            Xaxis = state.X;
            Yaxis = state.Y;
            MouseMov(Xaxis, Yaxis);

            byte[] jsButtons = state.GetButtons();
            buttons = new bool[jsButtons.Length];

            // konwersja przycisków na typ bool
            int i = 0;
            foreach (byte button in jsButtons)
            {
                buttons[i] = button >= 128;
                i++;
            }

            // wywołanie odpowiedniej funckji w zależności od stanu symulowanych przycisków
            if (buttons[0])
            {
                if (leftClicked == false)
                {
                    mouse_event(MOUSEEVENT_LEFTDOWN, 0, 0, 0, 0);
                    leftClicked = true;
                }
            }
            else if (buttons[1])
            {
                if (rightClicked == false)
                {
                    mouse_event(MOUSEEVENT_RIGHTDOWN, 0, 0, 0, 0);
                    rightClicked = true;
                }
            }
            else
            {
                if (leftClicked == true)
                {
                    mouse_event(MOUSEEVENT_LEFTUP, 0, 0, 0, 0);
                    leftClicked = false;
                }
                if (rightClicked == true)
                {
                    mouse_event(MOUSEEVENT_RIGHTUP, 0, 0, 0, 0);
                    rightClicked = false;
                }
            }
        }

        public void Poll()
        {
            try
            {
                // sprawdzenie połączenia
                joystickDevice.Poll();
                // aktualizacja informacji z urządzenia
                state = joystickDevice.CurrentJoystickState;
            }
            catch
            {
                throw (null);
            }
        }
    }
}
