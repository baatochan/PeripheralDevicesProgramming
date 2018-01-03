using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Automation.BDaq;
using System.Windows.Forms;
using System.IO;
using System.Threading;

namespace Akwizycja
{
    public partial class View : Form
    {
        static int sampleCount;
        static string[] wynikipomiarow; 
        static int startChannel = 4;
        static int channelCount = 1;
        static int convertClkRate = 200 * 1000;
        static Thread th;
        static double[] scaledData;
        static double[][] dataArr;
        ErrorCode errorCode = ErrorCode.Success;

        public View()
        {
            InitializeComponent();
            //for (int i = 0; i < sampleCount; i++)
           //     dataArr[i] = new double[channelCount];
        }


        private void run()
        {
            dataBox.Invoke(new MethodInvoker(delegate { dataBox.AppendText("Running..."); }));
            dataBox.Invoke(new MethodInvoker(delegate { dataBox.AppendText(Environment.NewLine); }));
            bool result = Int32.TryParse(textBox1.Text, out sampleCount);
            if (true == result)
                Console.WriteLine(sampleCount);
            else
                Console.WriteLine("Error");

            wynikipomiarow = new string[sampleCount];
            dataArr = new double[sampleCount][];
            for (int i = 0; i < sampleCount; i++)
                dataArr[i] = new double[channelCount];

            for (int j = 0; j < sampleCount; j++)
            {
                try
                {


                    // Step 3: Set necessary parameters for Asynchronous One Buffered AI operation, 
                    // Note: this step is optional(you can do these settings via "Device Configuration" dialog).
                    ScanChannel scanChannel = Program.bufferedAiCtrl.ScanChannel;
                    scanChannel.ChannelStart = startChannel;
                    scanChannel.ChannelCount = channelCount;
                    scanChannel.Samples = sampleCount;
                    Program.bufferedAiCtrl.ConvertClock.Rate = convertClkRate;

                    // Step 4: prepare the buffered AI. 
                    errorCode = Program.bufferedAiCtrl.Prepare();
                    if (BioFailed(errorCode))
                    {
                        throw new Exception();
                    }

                    // Step 5: Start buffered AI, 'RunOnce' indicates using synchronous mode,
                    // which means the method will not return until the acquisition is completed.
                    //Console.WriteLine(" SynchronousOneBufferedAI is in progress.");
                    //Console.WriteLine(" Please wait, until acquisition complete.\n");
                    errorCode = Program.bufferedAiCtrl.RunOnce();
                    if (BioFailed(errorCode))
                    {
                        throw new Exception();
                    }

                    // Step 6: Read samples and do post-process, we show the first sample of each channel to console here.
                    int channelCountMax = Program.bufferedAiCtrl.Features.ChannelCountMax;
                    scaledData = new double[sampleCount];
                    errorCode = Program.bufferedAiCtrl.GetData(sampleCount, scaledData);
                    if (BioFailed(errorCode))
                    {
                        throw new Exception();
                    }

                    dataArr[j] = scaledData;


                }
                catch (Exception ex)
                {
                    // Something is wrong
                    string errStr = BioFailed(errorCode) ? " Some error occurred. And the last error code is " + errorCode.ToString()
                                                             : ex.Message;
                    
                }

            }

            for (int j = 0; j < sampleCount; j++)
                for (int i = 0; i < channelCount; ++i)
                {
                    int k = j + i;
                    dataBox.Invoke(new MethodInvoker(delegate { dataBox.AppendText("data " + k + " : " + dataArr[j][3] + "\n"); }));
                    dataBox.Invoke(new MethodInvoker(delegate { dataBox.AppendText(Environment.NewLine); }));
                    wynikipomiarow[j] = dataArr[j][3].ToString();
                }
        }
        protected virtual void OnClosing(object sender, CancelEventArgs e)
        {
            th.Abort();
        }
        private void startBtn_Click(object sender, EventArgs e)
        {
            th = new Thread(run);
            th.Start();            
        }

        static bool BioFailed(ErrorCode err)
        {
            return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
        }

        private void saveBtn_Click(object sender, EventArgs e)
        {
            System.IO.File.WriteAllLines("C:\\Users\\lab\\Documents\\data" + ".txt", wynikipomiarow);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
