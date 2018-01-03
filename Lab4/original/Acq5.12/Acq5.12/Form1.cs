using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using Automation.BDaq;
using System.IO;

namespace Acq5._12
{
    public partial class Form1 : Form
    {
        Thread t = null;
        static int sampleCount = 256;
        static string[] wynikipomiarow = new string[sampleCount];
        static float[] wynikiNumeric = new float[sampleCount];
        public Form1()
        {
            InitializeComponent();

            

            //BDaqDevice.Open(0, AccessMode.ModeWrite, out device);
            //device.GetModule(0, out ai);
            //ai.Property.Set(PropertyId.CFG_ScanChannelStart, 21);
            //ai.Property.Set(PropertyId.CFG_ScanChannelCount, 4);

            //ai.Event.GetHandle(EventId.EvtBufferedAiStopped, out aiStopEventHandle);
            //ai.BfdAiPrepare(1024, out rawData);
        }

        private void mesure()
        {
         System.Drawing.Graphics g;
         System.Drawing.Pen pen1 = new System.Drawing.Pen(Color.Blue, 2F);
            g = pictureBox1.CreateGraphics();
            
            //-----------------------------------------------------------------------------------
            // Configure the following four parameters before running the demo
            //-----------------------------------------------------------------------------------
            //The default device of project is demo device, users can choose other devices according to their needs. 
            string deviceDescription = "USB-4702,BID#0";
            int startChannel = 4;
            int channelCount = 1;// 4;
            int convertClkRate = 10000;

            ErrorCode errorCode = ErrorCode.Success;
            // Step 1: Create a 'BufferedAiCtrl' for buffered AI function.
            BufferedAiCtrl bufferedAiCtrl = new BufferedAiCtrl();


            for (int j = 0; j < sampleCount; j++)
            {
                Console.WriteLine("Zostalo " + (sampleCount - j) + " pomiarow.");
                try
                {
                    // Step 2: Select a device by device number or device description and specify the access mode.
                    // in this example we use AccessWriteWithReset(default) mode so that we can 
                    // fully control the device, including configuring, sampling, etc.
                    bufferedAiCtrl.SelectedDevice = new DeviceInformation(deviceDescription);


                    // Step 3: Set necessary parameters for Asynchronous One Buffered AI operation, 
                    // Note: this step is optional(you can do these settings via "Device Configuration" dialog).
                    ScanChannel scanChannel = bufferedAiCtrl.ScanChannel;
                    scanChannel.ChannelStart = startChannel;
                    scanChannel.ChannelCount = channelCount;
                    scanChannel.Samples = sampleCount;
                    bufferedAiCtrl.ConvertClock.Rate = convertClkRate;

                    // Step 4: prepare the buffered AI. 
                    errorCode = bufferedAiCtrl.Prepare();
                    if (BioFailed(errorCode))
                    {
                        throw new Exception();
                    }

                    // Step 5: Start buffered AI, 'RunOnce' indicates using synchronous mode,
                    // which means the method will not return until the acquisition is completed.
                    //Console.WriteLine(" SynchronousOneBufferedAI is in progress.");
                    //Console.WriteLine(" Please wait, until acquisition complete.\n");
                    errorCode = bufferedAiCtrl.RunOnce();
                    if (BioFailed(errorCode))
                    {
                        throw new Exception();
                    }

                    // Step 6: Read samples and do post-process, we show the first sample of each channel to console here.
                    int channelCountMax = bufferedAiCtrl.Features.ChannelCountMax;
                    double[] scaledData = new double[sampleCount];
                    errorCode = bufferedAiCtrl.GetData(sampleCount, scaledData);
                    if (BioFailed(errorCode))
                    {
                        throw new Exception();
                    }
                    //Console.WriteLine(" Acquisition has completed!");
                    //Console.WriteLine(" The first sample each channel are:\n");
                    for (int i = 0; i < channelCount; ++i)
                    {
                       
                        Console.WriteLine("  channel {0}:{1,13:f8}", (i % channelCount + startChannel) % channelCountMax, scaledData[i]);
                        wynikipomiarow[j] = scaledData[i].ToString();
                        wynikiNumeric[j] = (float)scaledData[i];
                        float scale = 40;



                        if (j>0)
                            g.DrawLine(pen1, j, wynikiNumeric[j-1]*scale + 340, (j + 1), wynikiNumeric[j]*scale + 340);
                    }

  
                    Console.WriteLine("\n");

                }
                catch (Exception err)
                {
                    // Something is wrong
                    string errStr = BioFailed(errorCode) ? " Some error occurred. And the last error code is " + errorCode.ToString()
                                                             : err.Message;
                    Console.WriteLine(errStr);
                }
                /*for (int i = 0; i < sampleCount; i++)
                    Console.WriteLine(wynikipomiarow[i]);*/

                /*finally
                {
                    //step 7: close device, release any allocated resource.
                    bufferedAiCtrl.Dispose();
                    Console.ReadKey(false);
                }*/
            }

        }

        private void startBtn_Click(object sender, EventArgs e)
        {

            t = new Thread(mesure);
            t.Start();
            ////eventCheckingThread = new Thread(new ThreadStart(CheckEventThread));
            ////eventCheckingThread.Start();
            ////ai.BfdAiRunOnce(true);

        }

        public static void save()
        {
            string FILE_NAME =  "dane.txt";

            if (File.Exists(FILE_NAME))
            {
                Console.WriteLine("File already exists!", FILE_NAME);
                return;
            }
            var csv = new StringBuilder();
            for (int i = 0; i < sampleCount; i++)
            {
                csv.Append(wynikipomiarow[i] + "\n");                
                
            }
            File.WriteAllText(FILE_NAME, csv.ToString());
        }

        static bool BioFailed(ErrorCode err)
        {
            return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
        }

        private void stopBtn_Click(object sender, EventArgs e)
        {
            t.Abort();
            save();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }

}
