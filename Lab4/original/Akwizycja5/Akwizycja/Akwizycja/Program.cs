using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Automation.BDaq;
using System.IO;

namespace Akwizycja
{
    class Program
    {
        static int sampleCount = 1024;
        static string[] wynikipomiarow = new string[sampleCount];

        static void Main(string[] args)
        { //-----------------------------------------------------------------------------------
          // Configure the following four parameters before running the demo
          //-----------------------------------------------------------------------------------
          //The default device of project is demo device, users can choose other devices according to their needs. 
            string deviceDescription =  "USB-4702,BID#0";
            int startChannel = 0;
            int channelCount = 1;// 4;
            int convertClkRate = 1000;

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
                    }
                    Console.WriteLine("\n");
                    
                }
                catch (Exception e)
                {
                    // Something is wrong
                    string errStr = BioFailed(errorCode) ? " Some error occurred. And the last error code is " + errorCode.ToString()
                                                             : e.Message;
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
            //save();
            Console.WriteLine("Podaj nazwe pliku:");
            string FILE_NAME = Console.ReadLine() + ".txt";
            System.IO.File.WriteAllLines("C:\\Users\\lab\\Documents\\Visual Studio 2015\\Projects\\Akwizycja\\Akwizycja\\bin\\Debug\\"+FILE_NAME, wynikipomiarow);
            bufferedAiCtrl.Dispose();
            Console.ReadKey(false);
        }
        static bool BioFailed(ErrorCode err)
        {
            return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
        }

        /// <summary>
        /// ////////////////////////////////////////////////////////
        /// </summary>
        //private const string FILE_NAME = "Test.txt";


        public static void save()
        {
            string FILE_NAME = Console.ReadLine() + ".txt";

            if (File.Exists(FILE_NAME))
            {
                Console.WriteLine("File already exists!", FILE_NAME);
                return;
            }

            using (FileStream fs = new FileStream(FILE_NAME, FileMode.CreateNew))
            {
                using (BinaryWriter w = new BinaryWriter(fs))
                {
                    for (int i = 0; i < sampleCount; i++)
                    {
                        w.Write(wynikipomiarow[i]); // zapis danych
                        //w.Write("\n");
                    }
                }
            }

           /* using (FileStream fs = new FileStream(FILE_NAME, FileMode.Open, FileAccess.Read))
            {
                using (BinaryReader r = new BinaryReader(fs))
                {
                    for (int i = 0; i < 11; i++)
                    {
                        Console.WriteLine(r.ReadInt32());
                    }
                }
            }*/
        }

    }

   
}
