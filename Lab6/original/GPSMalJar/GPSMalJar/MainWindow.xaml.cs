using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO.Ports;

namespace GPSMalJar
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        SerialPort serialPort = new SerialPort();
        public MainWindow()
        {
            InitializeComponent();
            GetAvailablePorts();
            if (COM_comboBox.Items.Count > 0)
                COM_comboBox.SelectedIndex = 0;
        }

        void GetAvailablePorts()
        {
            var ports = SerialPort.GetPortNames();
            foreach(var port in ports)
            {
                COM_comboBox.Items.Add(port);
            }
        }

        string Checksum(string sentence)
        {
            int checksum = Convert.ToByte(sentence[0]);
            for (int i = 1; i < sentence.IndexOf('*'); i++)
            {
                checksum ^= Convert.ToByte(sentence[i]); //wykonanie xor na poszczególnych elementach sentencji.
            }
            return "*" + checksum.ToString("X2"); //zwrócenie sumy jako "*" oraz dwa znaki hexadecymalne
        }

        private void open_button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                serialPort.Close();
                serialPort.PortName = COM_comboBox.SelectedItem.ToString(); //nazwa portu do otwarcia
                //serialPort.PortName = "COM18";
                serialPort.Open(); //otwarcie portu
                ReadText();

            }
            catch (Exception exception)
            {
                coord_textBox.Text = exception.ToString(); //wyświetlenie błędu
            }
        }

        private void load_button_Click(object sender, RoutedEventArgs e)
        {
            ReadText();
        }

        private void close_button_Click(object sender, RoutedEventArgs e)
        {
            serialPort.Close(); //zamknięcie portu
            //progressBarPortStatus.Value = 0; //ustawienie komponentu wyświetlającego status
            //ustawienie parametrów komponentów by zablokować możliwość niedostępnych funkcjonalności

        }

        void ReadText()
        {
            string gpsData = "";
            try
            {
                gpsData = serialPort.ReadExisting();
                coord_textBox.Text = gpsData;
            }
            catch (Exception exception)
            {
                coord_textBox.Text = exception.ToString();
            }
        }

        void Read()
        {
            string gpsData = "";
            try
            {
                gpsData = serialPort.ReadExisting(); //pobranie z portu szeregowego danych przesyłanych przez urządzenie
            }
            catch (Exception exception)
            {
                coord_textBox.Text = exception.ToString(); //wyświetlenie błędu
            }
            string[] splittedGpsData = gpsData.Split('$'); //podział danych gps według znaku $ oddzielajacego sekwencje

            for (int i = 0; i < splittedGpsData.Length; i++)
            {
                string[] splittedSequence = splittedGpsData[i].Split(','); //podział sekwencji na pola
                if (splittedSequence[0] == "GPGGA")
                {
                    //if (Checksum(splittedGpsData[i]) == splittedSequence[splittedSequence.Length - 1]) //sprawdzenie sumy kontrolnej
                    if(true)
                    {
                        try
                        {
                            //Szerokosc geograficzna
                            splittedSequence[2] = splittedSequence[2].Replace(".", ",");
                            Double dLatitude = Convert.ToDouble(splittedSequence[2]);
                            int minutes = (int)(dLatitude / 10000) % 100;
                            double seconds = (dLatitude) % 10000 / 100;
                            int degrees = (int)dLatitude / 1000000;
                            dLatitude = degrees + minutes / 60.0 + seconds / 3600.0;

                            //Dlugosc geograficzna
                            splittedSequence[4] = splittedSequence[4].Replace(".", ",");
                            Double dLongtitude = Convert.ToDouble(splittedSequence[4]);
                            minutes = (int)(dLongtitude / 10000) % 100;
                            seconds = (dLongtitude) % 10000 / 100;
                            degrees = (int)dLongtitude / 1000000;
                            dLongtitude = degrees + minutes / 60.0 + seconds / 3600.0;

                            //Wyswietlenie współrzędnych na mapie
                            coord_textBox.Text = "Szerokosc: " + dLatitude + splittedSequence[3] + "\n" +
                                                 "Dlugosc: " + dLongtitude + splittedSequence[5] + "\n" +
                                                 "Wysokosc: " + splittedSequence[9] + "m" + "\n" +
                                                 "https://www.google.com/maps/search/?api=1&query=" + dLatitude + "," + dLongtitude;
                            string link = "https://www.google.com/maps/search/?api=1&query=" + dLatitude + "," + dLongtitude;
                            webBrowser.Navigate(link); //funkcja wywołująca uruchomienie w komponencie web browser link podany jako argument
                        }
                        catch (Exception exception)
                        {
                            coord_textBox.Text = exception.ToString(); //wyświetlenie błędu
                        }
                    }
                    else
                    {
                        coord_textBox.Text = "Bledna suma kontrolna";
                    }
                }
            }
        }

    }
}
