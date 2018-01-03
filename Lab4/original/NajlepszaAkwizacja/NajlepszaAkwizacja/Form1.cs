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

namespace NajlepszaAkwizacja
{
    public partial class Form1 : Form
    {
                string deviceDescription = "USB-4702,BID#0";
        static public BufferedAiCtrl a = new BufferedAiCtrl();
        int startChannel = 0;
        int clockRate = 15000;
        const int samples = 512;
        int channelCount = 1;
        ErrorCode errorCode = ErrorCode.Success;
        static string[] wynikipomiarow = new string[samples];
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
  
            

            //   Application.EnableVisualStyles();
            //  Application.SetCompatibleTextRenderingDefault(false);
            // Application.Run(new Form1());

        }

        private void button2_Click(object sender, EventArgs e)
        {
  
                for (int i = 0; i < samples; i++)
                {
                    try 
                    {
                    a.SelectedDevice = new DeviceInformation(deviceDescription);
                    ScanChannel scanChannel = a.ScanChannel;
                    scanChannel.ChannelStart = startChannel;
                    scanChannel.ChannelCount = channelCount;
                    scanChannel.Samples = samples;
                    a.ConvertClock.Rate = clockRate;

      
                  
                    int channelCountMax = a.Features.ChannelCountMax;
                    double[] scaledData = new double[samples];
                    errorCode = a.GetData(samples, scaledData);
               
                    for (int j = 0; j < channelCount; ++j)
                    {
                        richTextBox1.Text = ((j % channelCount + startChannel) % channelCountMax).ToString() + scaledData[j].ToString();
                        wynikipomiarow[i] = scaledData[j].ToString();
                       // richTextBox1.Text = wynikipomiarow[i];
                    }
                   
                    }
                    catch (Exception ex)
                    {
                         Console.WriteLine(ex);
                    }
                }
            }

                /*for (int i = 0; i < sampleCount; i++)
                    Console.WriteLine(wynikipomiarow[i]);*/
                
                /*finally
                {
                    //step 7: close device, release any allocated resource.
                    bufferedAiCtrl.Dispose();
                    Console.ReadKey(false);
                }*/

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
        
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
        }    
     }
    
}
