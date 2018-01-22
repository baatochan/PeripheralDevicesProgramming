using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace gps
{
    class Program
    {
        static bool _continue;
        static SerialPort _serialPort;
        static string _gpgga = null;

        static void Main(string[] args)
        {
            string message;
            StringComparer stringComparer = StringComparer.OrdinalIgnoreCase;
            Thread readThread = new Thread(Read);

            // Create a new SerialPort object with default settings.
            _serialPort = new SerialPort();

            // Allow the user to set the appropriate properties.
            _serialPort.PortName = "COM8";
            //_serialPort.BaudRate = SetPortBaudRate(_serialPort.BaudRate);
            //_serialPort.Parity = SetPortParity(_serialPort.Parity);
            //_serialPort.DataBits = SetPortDataBits(_serialPort.DataBits);
            //_serialPort.StopBits = SetPortStopBits(_serialPort.StopBits);
            //_serialPort.Handshake = SetPortHandshake(_serialPort.Handshake);

            // Set the read/write timeouts
            _serialPort.ReadTimeout = 500;
            _serialPort.WriteTimeout = 500;

            _serialPort.Open();
            _continue = true;
            readThread.Start();

/*            Console.Write("Name: ");
            name = Console.ReadLine();
*/
            readThread.Join();
            _serialPort.Close();
            Console.WriteLine(_gpgga + "\n");
            String[] tab = _gpgga.Split(',');
            double szerokosc = (Double.Parse(tab[2]))/100;
            double stopnie = Math.Floor(szerokosc);
            szerokosc -= stopnie;
            szerokosc *= 100;
            double minutes = Math.Floor(szerokosc);
            szerokosc %= 1;
            double seconds = Math.Floor((szerokosc) * 60.0);

            double dlugosc = (Double.Parse(tab[4])) / 100;
            double stopnie2 = Math.Floor(dlugosc);
            dlugosc -= stopnie2;
            dlugosc *= 100;
            double minutes2 = Math.Floor(dlugosc);
            dlugosc %= 1;
            double seconds2 = Math.Floor((dlugosc) * 60.0);
            
            Console.WriteLine("Czas: " + tab[1].Substring(0,2) + ":" + tab[1].Substring(2,2) + ":" + tab[1].Substring(4,2)) ;
            Console.WriteLine("Szerokosc geograficzna: " + stopnie + "stopni " + minutes + "min " + seconds + "s " + tab[3]);
            Console.WriteLine("Dlugosc geograficzna: " + stopnie2 + "stopni " + minutes2 + "min " + seconds2 + "s " + tab[5]);
            Console.WriteLine("Liczba satelit: " + tab[7]);
            Console.WriteLine("Wysokosc: " + tab[9] + tab[10]);

            System.Diagnostics.Process.Start("https://www.google.com/maps/place/" + stopnie + "°" + minutes + "'" + seconds + tab[3] + "+" + stopnie2 + "°" + minutes2 + "'" + seconds2 + tab[5]);

            Console.ReadLine();
        }

        public static void Read()
        {
            while (_continue)
            {
                try
                {
                    string message = _serialPort.ReadLine();
                    if (_gpgga == null && message.Contains("$GPGGA"))
                    {
                        if (((message.Split(','))[6].Equals("1")))
                        {
                            _gpgga = message;
                            //_continue = false;
                            break;
                        }
                        
                    }
                    //Console.WriteLine(message);
                }
                catch (TimeoutException) { }
            }
        }
    }
}
