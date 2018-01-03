/*******************************************************************************
Copyright (c) 1983-2012 Advantech Co., Ltd.
********************************************************************************
THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY INFORMATION
WHICH IS THE PROPERTY OF ADVANTECH CORP., ANY DISCLOSURE, USE, OR REPRODUCTION,
WITHOUT WRITTEN AUTHORIZATION FROM ADVANTECH CORP., IS STRICTLY PROHIBITED. 

================================================================================
REVISION HISTORY
--------------------------------------------------------------------------------
$Log:  $ 
--------------------------------------------------------------------------------
$NoKeywords:  $
*/
/******************************************************************************
*
* Windows Example:
*    AsynchronousOneBufferedAI.cs
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Asynchronous One Buffered AI function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device. 
*    2. Set the 'startChannel' as the first channel for scan analog samples  
*    3. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    4. Set the 'sampleCount' to decide the capacity of buffer in kernel and how many samples you want to get for each channel.
*    5. Set the 'convertClkRate' to tell driver sample data rate for each channel.    
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Reflection;
using System.Runtime.InteropServices;
using Automation.BDaq;
using System.IO;

namespace AI_AsynchronousOneBufferedAI
{
    class AsynchronousOneBufferedAI
    {
        static void Main(string[] args)
        {
            ErrorCode errorCode = ErrorCode.Success;
            string deviceDescription = "USB-4702,BID#0";
            //string deviceDescription = "DemoDevice,BID#0";

            // Za pomoca multimetra zostalo ustalone, ze generator pracuje w kanale CH05 (4 indeksujac od 0)
            int startChannel = 4;
            int channelCount = 1;

            // Ilosc probek = 256, Czas akwizycji - 1s, Czas miedzy probkami - 1/256 s, Czestotliwosc probkowania 256 Hz
            // Spelnia Twierdzenie Kotielnikowa-Shannona (badany sygnal ma czestliwosc 100 Hz)
            int sampleCount = 20000;
            int convertClkRatePerChan = 1000;

            // Step 1: Create a 'BufferedAiCtrl' for buffered AI function.
            BufferedAiCtrl bufferedAiCtrl = new BufferedAiCtrl();

            // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
            bufferedAiCtrl.Stopped += new EventHandler<BfdAiEventArgs>(bufferedAiCtrl_Stopped);

            try
            {
                // Step 3: Select a device by device number or device description and specify the access mode.
                // in this example we use AccessWriteWithReset(default) mode so that we can 
                // fully control the device, including configuring, sampling, etc.
                bufferedAiCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
                bufferedAiCtrl.Streaming = false;// specify the running mode: one-buffered.

                // Step 4: Set necessary parameters for Asynchronous One Buffered AI operation, 
                // Note: this step is optional(you can do these settings via "Device Configuration" dialog).
                ScanChannel scanChannel = bufferedAiCtrl.ScanChannel;
                scanChannel.ChannelStart = startChannel;
                scanChannel.ChannelCount = channelCount;
                scanChannel.Samples = sampleCount;
                bufferedAiCtrl.ConvertClock.Rate = convertClkRatePerChan;

                // Step 5: prepare the buffered AI. 
                errorCode = bufferedAiCtrl.Prepare();
                if (BioFailed(errorCode))
                {
                    throw new Exception();
                }

                // Step 6: start Asynchronous Buffered AI, 'Asynchronous' means the method returns immediately
                // after the acquisition has been started. The 'bufferedAiCtrl_Stopped' method will be called
                // after the acquisition is completed.
                errorCode = bufferedAiCtrl.Start();
                if (BioFailed(errorCode))
                {
                    throw new Exception();
                }
                Console.WriteLine(" AsynchronousOneBufferedAI is in progress...   any key to quit !\n");

                // Step 7: Do anything you are interesting while the device is acquiring data.
                do
                {
                    Thread.Sleep(1000);// do something yourself !
                } while (!Console.KeyAvailable);

                // step 8: Stop the operation if it is running.
                bufferedAiCtrl.Stop();
            }
            catch (Exception e)
            {
                // Something is wrong
                string errStr = BioFailed(errorCode) ? " Some error occurred. And the last error code is " + errorCode.ToString()
                                                       : e.Message;
                Console.WriteLine(errStr);
            }
            finally
            {
                // Step 9: close device, release any allocated resource before quit.
                bufferedAiCtrl.Dispose();
                Console.ReadKey(false);
            }
        }

        //  process the acquired data
        static void bufferedAiCtrl_Stopped(object sender, BfdAiEventArgs e)
        {
            Console.Write(" Acquisition has completed, sample count is " + e.Count.ToString() + ".\n");
            Console.WriteLine("");

            BufferedAiCtrl bufferedAiCtrl = (BufferedAiCtrl)sender;

            int channelCountMax = bufferedAiCtrl.Features.ChannelCountMax;
            int startChan = bufferedAiCtrl.ScanChannel.ChannelStart;
            int chanCount = bufferedAiCtrl.ScanChannel.ChannelCount;
            // e.Count notifys that how many samples had been gathered in the 'Stopped' event. 
            double[] allChanData = new double[e.Count];
            bufferedAiCtrl.GetData(e.Count, allChanData);// Get data

            string[] dataToMatlab = new string[e.Count];

            //Console.WriteLine(" Acquaired data:");

            //
            for (int i = 0; i < e.Count; ++i)
            {
                //Console.WriteLine(" " + allChanData[i] + " ");
                dataToMatlab[i] = allChanData[i].ToString();
            }

            // Zapis do pliku
            string FILE_NAME = "matlabSignal";
            Random rnd = new Random();
            FILE_NAME += rnd.Next();
            FILE_NAME += ".txt";
            System.IO.File.WriteAllLines(Directory.GetParent(Directory.GetCurrentDirectory()).Parent.FullName + "\\" + FILE_NAME, dataToMatlab);
            Console.WriteLine(" Data saved to: " + FILE_NAME);
        }



        static bool BioFailed(ErrorCode err)
        {
            return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
        }


    }

}
