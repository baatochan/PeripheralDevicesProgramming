using Automation.BDaq;
using System;
using System.Collections.Generic;
using System.Threading;
using System.Windows.Forms;

namespace Akwizycja
{
    class Program
    {
       static public BufferedAiCtrl bufferedAiCtrl = new BufferedAiCtrl();
        [STAThread]
        static void Main(string[] args)
        {
            string deviceDescription = "USB-4702,BID#0";
            // Step 2: Select a device by device number or device description and specify the access mode.
            // in this example we use AccessWriteWithReset(default) mode so that we can 
            // fully control the device, including configuring, sampling, etc.
            bufferedAiCtrl.SelectedDevice = new DeviceInformation(deviceDescription);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new View());
        }
    }
}
