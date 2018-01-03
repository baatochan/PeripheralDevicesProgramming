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
        static int sampleCount = 32;
        static string[] wynikipomiarow = new string[sampleCount];

        static void Main(string[] args)
        {

            string deviceDescription = "USB-4702,BID#0";
            int startChannel = 0;
            int channelCount = 1;
            int convertClkRate = 15000;

            ErrorCode errorCode = ErrorCode.Success;

            BufferedAiCtrl buffer = new BufferedAiCtrl();


            for (int j = 0; j < sampleCount; j++)
            {
      
                try
                {

                    buffer.SelectedDevice = new DeviceInformation(deviceDescription);

                    ScanChannel scanChannel = buffer.ScanChannel;
                    scanChannel.ChannelStart = startChannel;
                    scanChannel.ChannelCount = channelCount;
                    scanChannel.Samples = sampleCount;
                    buffer.ConvertClock.Rate = convertClkRate;

                    buffer.Prepare();
                    buffer.RunOnce();


                    int channelCountMax = buffer.Features.ChannelCountMax;
                    double[] scaledData = new double[sampleCount];
                    errorCode = buffer.GetData(sampleCount, scaledData);

                 
                    for (int i = 0; i < channelCount; ++i)
                    {
                       // Console.WriteLine(scaledData[i]);
                        wynikipomiarow[j] = scaledData[i].ToString();
                    }

                }
                catch (Exception ex)
                {

                    Console.WriteLine(ex);
                }

            }
            Console.WriteLine("Podaj nazwe pliku:");
            string FILE_NAME = Console.ReadLine() + ".txt";
            System.IO.File.WriteAllLines("C:\\Users\\lab\\Desktop\\akwyziasdva\\akwyziasdva\\bin\\Debug" + FILE_NAME, wynikipomiarow);
            buffer.Dispose();
            Console.ReadKey(false);
        }
        static bool BioFailed(ErrorCode err)
        {
            return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
        }


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
                    }
                }
            }

            using (FileStream fs = new FileStream(FILE_NAME, FileMode.Open, FileAccess.Read))
            {
                using (BinaryReader r = new BinaryReader(fs))
                {
                    for (int i = 0; i < 11; i++)
                    {
                        Console.WriteLine(r.ReadInt32());
                    }
                }
            }
        }

    }


}
