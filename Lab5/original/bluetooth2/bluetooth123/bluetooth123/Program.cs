using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using InTheHand.Net;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;
using System.Threading;
using System.Windows;

namespace test
{
    class Program
    {
        public BluetoothRadio[] adapters;
        public BluetoothClient client = new BluetoothClient();
        public BluetoothDeviceInfo[] devices;
        public BluetoothDeviceInfo dev_choosen;
        Thread nasluchuj = new Thread(nasluch);

        static private void nasluch()
        {
            while (true)
            {
                var listener = new ObexListener(ObexTransport.Bluetooth);
                listener.Start();
                ObexListenerContext con = listener.GetContext();
                ObexListenerRequest req = con.Request;
                String[] pathSplits = req.RawUrl.Split('/');
                String filename = pathSplits[pathSplits.Length - 1];
                req.WriteFile(filename);
                listener.Stop();
            }
        }
        public void zadanie()
        {
            Console.WriteLine("Co chcesz zrobić?\n\t1 - Szukaj adaptera");
            string linijka = Console.ReadLine();
            int w = int.Parse(linijka);
            if (w == 1)
            {
                adapters = BluetoothRadio.AllRadios;
                for (int i = 0; i < adapters.Length; i++)
                {
                    Console.WriteLine(adapters[i].Name);
                }

            }
            Console.WriteLine("Co chcesz zrobić?\n\t1 - Szukaj urzadzen");
            linijka = Console.ReadLine();
            int w1 = int.Parse(linijka);
            if (w1 == 1)
            {
                devices = client.DiscoverDevices();
                foreach (var Dev in devices)
                {
                    Console.WriteLine(Dev.DeviceName);
                }
            }
            Console.WriteLine("Wyswietl adres MAC urzadzenia o numerze?");
            linijka = Console.ReadLine();
            int w2 = int.Parse(linijka);
            w2 = w2 - 1;
            string adres;
            adres = devices[w2].DeviceAddress.ToString();
            Console.WriteLine(adres);
            dev_choosen = devices[w2];
            Console.WriteLine("Co chcesz zrobić?\n\t1 - Autoryzuj wybrane urzadzenie");
            linijka = Console.ReadLine();
            int w3 = int.Parse(linijka);
            if (BluetoothSecurity.PairRequest(dev_choosen.DeviceAddress, "1234"))
            {
                nasluchuj.Start();
            }
            else
            {
                Console.WriteLine("Autoryzacja nieudana!", "Error");
            }
            Console.WriteLine("Co chcesz zrobić?\n\t1 - Przeslij plik");
            linijka = Console.ReadLine();
            int w4 = int.Parse(linijka);
            Console.WriteLine("Podaj nazwe pliku (musi byc umieszczony w katalogu z plikiem .exe)?");
            linijka = Console.ReadLine();
            string FileName = linijka;



            var fileToSend = new Uri("obex://" + dev_choosen.DeviceAddress + "/" + FileName);
            var obexReq = new ObexWebRequest(fileToSend);
            obexReq.ReadFile(FileName);
            var obexResp = obexReq.GetResponse();
            obexResp.Close();

        }
        static void Main(string[] args)
        {
            Program a = new Program();
            a.zadanie();
            Console.ReadKey();
        }
    }
}