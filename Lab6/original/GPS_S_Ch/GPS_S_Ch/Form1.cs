using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GPS_S_Ch
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private string szerGeo, dlugGeo;

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void openConection_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = portName.Text;
                serialPort1.Open();
                latitudeText.Text = "Czekam na dane...";
                longtitudeText.Text = "Czekam na dane...";
                timer1.Enabled = true;
                closeConection.Enabled = true;
                openConection.Enabled = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, portName.Text);
            }
        }

        private void closeConection_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            timer1.Enabled = false;
            closeConection.Enabled = false;
            openConection.Enabled = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if(serialPort1.IsOpen)
            {
                string allData = serialPort1.ReadExisting();
                string[] lineDataTab = allData.Split('$');//allData.Split('$');
                for (int i = 0; i < lineDataTab.Length; i++)
                {

                    string tmp = lineDataTab[i];
                    string[] valTab = tmp.Split(',');
                    if (valTab[0] == "GPGGA") // odczyt pozycji
                    {
                        try
                        {
                            //Szerokosc geograficzna
                            valTab[2] = valTab[2].Replace(".", ",");
                            Console.Out.WriteLine(valTab[2]);
                            //Double dSzer = Convert.ToDouble(valTab[2]);
                            //dSzer = dSzer / 100;
                            //string[] szer = dSzer.ToString().Split('.');
                            ////Konwersja minut na ulamek stopnia i zapis, 1 st = 60 min
                            //szerGeo = valTab[3].ToString() + (Convert.ToDouble(szer[0])
                            //+ ((Convert.ToDouble("," + szer[1]) / .6))).ToString("");
                            //szerGeo = szerGeo.Replace(",", ".");
                            ////Dlugosc geograficzna
                            //valTab[4] = valTab[4].Replace(".", ",");
                            //Double dDlug = Convert.ToDouble(valTab[4]);
                            //dDlug = dDlug / 100;
                            //string[] dlug = dDlug.ToString().Split(',');
                            ////Konwersja minut na ulamek stopnia i zapis, 1 st = 60 min
                            //dlugGeo = valTab[5].ToString() + (Convert.ToDouble(dlug[0])
                            //+ ((Convert.ToDouble("," + dlug[1]) / .6))).ToString("");
                            //dlugGeo = dlugGeo.Replace(",", ".");
                            //Wyswietlenie
                            latitudeText.Text = valTab[2] + " " + valTab[3];//szerGeo;
                            longtitudeText.Text = valTab[4] + " " + valTab[5];//dlugGeo;
                            wysnpmTextBox.Text = valTab[9] + "m n.p.m.";
                            sateliteAmountTextBox.Text = valTab[6];
                            textBox1.Text = valTab[9];
                            //Wlaczenie mozliwosci podgladu na mapie
                            //showOnMapButton.Enabled = true;
                        }
                        catch
                        {
                            //Komunikat o braku danych i blokada przycisku mapy
                            showOnMapButton.Enabled = false;
                            longtitudeText.Text = "Brak danych.";
                            latitudeText.Text = "Brak danych.";
                        }
                    }
                }
            }
        }
    }
}
