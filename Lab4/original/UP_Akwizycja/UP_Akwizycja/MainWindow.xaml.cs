using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.Eventing;
using System.IO;
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
using System.Windows.Forms;
using Automation.BDaq;
using MessageBox = System.Windows.MessageBox;


namespace UP_Akwizycja
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static string path;
        private FolderBrowserDialog folderBrowserDialog;

        private int channelStart = 0;
        private int channelCount = 3;
        private int clockrate = 1000;
        private string deviceDescription = "USB-4702,BID#0";

        private List<string> results;

        private enum WaveStyle { Sine, Sawtooth, Square }
        private ErrorCode error = ErrorCode.Success;

        private BufferedAiCtrl buffer = new BufferedAiCtrl();

        public MainWindow()
        {
            InitializeComponent();
            folderBrowserDialog = new FolderBrowserDialog();
            folderBrowserDialog.RootFolder = Environment.SpecialFolder.Desktop;
            TextBoxSamples.Text = 2048.ToString();
            TextBoxChannels.Text = 1.ToString();
        }

        #region Eventy WPF
        // Wybór folderu.
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            folderBrowserDialog.Description = "Select directory";
            folderBrowserDialog.ShowNewFolderButton = true;
            folderBrowserDialog.ShowDialog();
            if (Directory.Exists(folderBrowserDialog.SelectedPath))
            {
                path = folderBrowserDialog.SelectedPath;
            }
            else
            {
                MessageBox.Show("Incorrect directory.");
            }
        }
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            Start();
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            Save();
        }

        private void Button_Click_4(object sender, RoutedEventArgs e)
        {
            Read();
        }
        #endregion

        #region Metody
        private void Start()
        {
            int totalSampleCount = Convert.ToInt32(TextBoxSamples.Text);
            channelCount = Convert.ToInt32(TextBoxChannels.Text);
            int sampleCount = totalSampleCount / channelCount;
            int iterations = 10;
            results = new List<string>();
            for (int i = 0; i < iterations; i++)
            {
                buffer.SelectedDevice = new DeviceInformation(deviceDescription);
                
                ScanChannel channel = buffer.ScanChannel;
                channel.ChannelStart = channelStart;
                channel.ChannelCount = channelCount;
                channel.Samples = sampleCount;
                buffer.ConvertClock.Rate = clockrate;

                // Prepare
                error = buffer.Prepare();
                ErrorCheck();

                // RunOnce => async mode
                // Will not return after acquisition is completed.
                error = buffer.RunOnce();
                ErrorCheck();

                // Read samples and post-process.
                double[] data = new double[sampleCount];
                error = buffer.GetData(sampleCount, data);
                ErrorCheck();

                for (int j = 0; j < channelCount; j++)
                {
                    results.Add(data[i].ToString());
                }

            }

            buffer.Dispose();
        }

        private void Save()
        {
            string filename = TextBoxFilename.Text;
            string fullPath = System.IO.Path.Combine(path, filename + ".txt.");
            using (FileStream fs = new FileStream(fullPath, FileMode.CreateNew))
            {
                using (BinaryWriter bw = new BinaryWriter(fs))
                {
                    foreach (var result in results)
                    {
                        bw.Write(result);
                        bw.Write('\n');
                    }
                }
            }
        }

        private void Read()
        {
            string filename = TextBoxFilename.Text;
            string fullPath = System.IO.Path.Combine(path, filename + ".txt.");
            string parsedText = "Odczytane dane:" + Environment.NewLine;
            using (FileStream fs = new FileStream(fullPath, FileMode.Open))
            {
                using (BinaryReader br = new BinaryReader(fs))
                {
                    for (int i = 0; i < (fs.Length)/8; i++)
                    {
                        parsedText += (br.ReadDouble()).ToString();
                    }
                }
            }
            DisplayWindow dw = new DisplayWindow(parsedText);
            dw.Show();
        }
        #endregion

        #region Reszta
        private void ErrorCheck()
        {
            if (BioFailed(error))
            {
                MessageBox.Show("Error");
                return;
            }
        }

        static bool BioFailed(ErrorCode error)
        {
            return error < ErrorCode.Success && error >= ErrorCode.ErrorHandleNotValid;
        }
        #endregion

    }
}
