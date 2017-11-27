using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using Microsoft.CSharp;
using System.CodeDom.Compiler;
using Mousemove;
using System.Runtime.Serialization;
using System.Runtime.InteropServices;
using System.Runtime.Serialization.Formatters.Binary;
using System.Threading;

namespace draw_on_desktop
{
    public partial class Form1 : Form
    {
        private bool isdrawing = false;
        private float width;
        private Color color = Color.Black;
        private Point prev = new Point();
        private Curve cv;
        private Drawing draw = new Drawing();
        private DateTime starttime;

        [DllImport("user32.dll")]
        static extern IntPtr GetDC(IntPtr hWnd);

        public Form1()
        {
            InitializeComponent();
            for (int i = 0; i < 24; i++)
            {
                widthcombo.Items.Add(i+0.5);
                widthcombo.Items.Add(i + 1);
            }

            widthcombo.SelectedIndex = 3;
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            prev = e.Location;
            isdrawing = true;
            cv = new Curve();
            cv.Color = color;
            cv.Width = width;
            cv.Pause = DateTime.Now - starttime;
            starttime = DateTime.Now;
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            Pen p = new Pen(color, width);
            if (isdrawing)
            {
                using (Graphics gr=this.CreateGraphics())
                {
                    gr.DrawLine(p, prev, e.Location);
                    cv.Coordinates.Add(prev);
                    prev = e.Location;
                }
            }
            p.Dispose();
        }

        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            isdrawing = false;
            cv.Coordinates.Add(prev);
            cv.Duration = DateTime.Now - starttime;
            starttime = DateTime.Now;
            draw.Curves.Add(cv);
        }

        private void ColorButton_Click(object sender, EventArgs e)
        {
            if (colorDialog.ShowDialog() == DialogResult.OK)
                ColorButton.BackColor = colorDialog.Color;
        }

        private void RePaint()
        {
            using (Graphics gr = this.CreateGraphics())
            {
                for (int i = 0; i < draw.Curves.Count; i++)
                {
                    Curve tempcv = draw.Curves[i];
                    Pen temp = new Pen(tempcv.Color, tempcv.Width);
                    for (int j = 0; j < tempcv.Coordinates.Count - 1; j++)
                    {
                        gr.DrawLine(temp, tempcv.Coordinates[j], tempcv.Coordinates[j + 1]);
                    }
                    temp.Dispose();
                }
            }
        }

        private void ColorButton_BackColorChanged(object sender, EventArgs e)
        {
            color = ColorButton.BackColor;
        }

        private void widthcombo_SelectedIndexChanged(object sender, EventArgs e)
        {
            width = float.Parse(widthcombo.SelectedItem.ToString());
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            RePaint();
        }

        private bool serialize(string name)
        {
            FileStream st = new FileStream(name, FileMode.OpenOrCreate, FileAccess.Write);
            BinaryFormatter formatter = new BinaryFormatter();
            try
            {
                formatter.Serialize(st, Convert(draw));
            }
            catch (SerializationException)
            {
                return false;
            }
            finally
            {
                st.Close();
            }
            return true;
        }

        private Drawing Convert(Drawing input)
        {
            Drawing output = new Drawing();
            for (int i = 0; i < input.Curves.Count; i++)
            {
                Curve temp=input.Curves[i];
                output.Curves.Add(new Curve(temp.Duration,temp.Pause,temp.Color,temp.Width));
                for (int j = 0; j < temp.Coordinates.Count; j++)
                {
                    output.Curves[i].Coordinates.Add(new Point());
                    output.Curves[i].Coordinates[j] = PointToScreen(temp.Coordinates[j]);
                }
            }

            if (output.Curves.Count>0)
            {
                output.Curves[0].Pause = TimeSpan.Zero; 
            }
            return output;
        }

        private void Draw()
        {
            using (Graphics gr = Graphics.FromHdc(GetDC(IntPtr.Zero)))
            {
                Drawing converted = Convert(draw);
                for (int i = 0; i < converted.Curves.Count; i++)
                {
                    Curve temp = converted.Curves[i];
                    Thread.Sleep(temp.Pause);
                    using (Pen p = new Pen(temp.Color, temp.Width))
                    {
                        TimeSpan pause = new TimeSpan(temp.Duration.Ticks / temp.Coordinates.Count);
                        for (int j = 0; j < temp.Coordinates.Count - 1; j++)
                        {
                            gr.DrawLine(p, temp.Coordinates[j], temp.Coordinates[j + 1]);
                            Thread.Sleep(pause);
                        }
                    }
                }
            }
        }

        private bool Compile(string path)
        {
            bool result;

            using (CSharpCodeProvider prov = new CSharpCodeProvider())
            {
                CompilerParameters param = new CompilerParameters();

                string pathtoicon = "";
                if (File.Exists(Application.StartupPath + "\\icon.ico"))
                {
                    pathtoicon = Application.StartupPath + "\\icon.ico";
                }

                param.CompilerOptions = "/target:winexe" + " " + "/win32icon:" + "\"" + pathtoicon + "\"";
                param.GenerateExecutable = true;
                param.IncludeDebugInformation = false;
                param.EmbeddedResources.Add(Environment.GetEnvironmentVariable("TEMP")+"\\points.dat");
                param.OutputAssembly = path;
                param.GenerateInMemory = false;
                
                param.ReferencedAssemblies.Add("System.dll");
                param.ReferencedAssemblies.Add("System.Data.dll");
                param.ReferencedAssemblies.Add("System.Deployment.dll");
                param.ReferencedAssemblies.Add("System.Drawing.dll");
                param.ReferencedAssemblies.Add("System.Windows.Forms.dll");
                param.ReferencedAssemblies.Add("System.Xml.dll");
                
                param.TreatWarningsAsErrors = false;
                CompilerResults compresults = prov.CompileAssemblyFromSource(param, Properties.Resources.Program);

                result = compresults.Errors.Count == 0;

                File.Delete(Environment.GetEnvironmentVariable("TEMP") + "\\points.dat");
            }

            return result;
        }

        private void previewToolStripButton_Click(object sender, EventArgs e)
        {
            this.Hide();
            Draw();
            Thread.Sleep(new TimeSpan(0, 0, 2));
            this.Show();
            this.Invalidate();
        }

        private void clearToolStripButton_Click(object sender, EventArgs e)
        {
            draw = new Drawing();
            prev = new Point();
            this.Invalidate();
        }

        private void BuildToolStripButton_Click(object sender, EventArgs e)
        {
            if (filesave.ShowDialog()==DialogResult.OK)
            {
                Workerthread.RunWorkerAsync(filesave.FileName);
            }
        }

        private void Workerthread_DoWork(object sender, DoWorkEventArgs e)
        {
            if (serialize(Environment.GetEnvironmentVariable("TEMP") + "\\points.dat"))
                e.Result = Compile((string)e.Argument);
            else e.Result = false;
        }

        private void Workerthread_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if ((bool)e.Result)
            {
                MessageBox.Show("Build Succedded.", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
                MessageBox.Show("Build failed", "Failure", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}