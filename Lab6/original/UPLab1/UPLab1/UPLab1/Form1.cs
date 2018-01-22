using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UPLab1
{
    public partial class Form1 : Form
    {
        Boolean isDrawing = false;
        Bitmap bitmap;
        Point lastLocation; 
        Graphics g;
        public Form1()
        {
            InitializeComponent();
            bitmap = new Bitmap(drawBox.Width, drawBox.Height);
            g = Graphics.FromImage(bitmap);
            drawBox.Image = bitmap;
            lastLocation = new Point(drawBox.Width / 2, drawBox.Height / 2);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Pen pen = new Pen(Color.Black);
            g.DrawLine(pen, lastLocation.X, lastLocation.Y, lastLocation.X -10 , lastLocation.Y);
            drawBox.Image = bitmap;
            lastLocation = new Point(lastLocation.X - 10, lastLocation.Y);
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void drawBox_MouseDown(object sender, MouseEventArgs e)
        {
            isDrawing = true;
        }

        private void drawBox_MouseUp(object sender, MouseEventArgs e)
        {
            isDrawing = false;
        }

        private void drawBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (!isDrawing)
                return;
            Pen pen = new Pen(Color.Black);
            g.DrawLine(pen, e.Location.X, e.Location.Y,e.Location.X+1,e.Location.Y+1);
            drawBox.Image = bitmap;
            lastLocation = e.Location;
        }

        private void rightButton_KeyDown(object sender, KeyEventArgs e)
        {
            Pen pen = new Pen(Color.Black);
            g.DrawLine(pen, lastLocation.X, lastLocation.Y, lastLocation.X + 1, lastLocation.Y);
            drawBox.Image = bitmap;
            lastLocation = new Point(lastLocation.X+1,lastLocation.Y);
        }

        private void forwardButton_Click(object sender, EventArgs e)
        {
            Pen pen = new Pen(Color.Black);
            g.DrawLine(pen, lastLocation.X, lastLocation.Y, lastLocation.X, lastLocation.Y - 10);
            drawBox.Image = bitmap;
            lastLocation = new Point(lastLocation.X, lastLocation.Y - 10);
        }

        private void forwardButton_KeyDown(object sender, KeyEventArgs e)
        {
            Pen pen = new Pen(Color.Black);
            g.DrawLine(pen, lastLocation.X, lastLocation.Y, lastLocation.X, lastLocation.Y+1);
            drawBox.Image = bitmap;
            lastLocation = new Point(lastLocation.X, lastLocation.Y+1);
        }

        private void rightButton_Click(object sender, EventArgs e)
        {
            Pen pen = new Pen(Color.Black);
            g.DrawLine(pen, lastLocation.X, lastLocation.Y, lastLocation.X + 10, lastLocation.Y);
            drawBox.Image = bitmap;
            lastLocation = new Point(lastLocation.X + 10, lastLocation.Y);
        }

        private void backwardButton_Click(object sender, EventArgs e)
        {
            Pen pen = new Pen(Color.Black);
            g.DrawLine(pen, lastLocation.X, lastLocation.Y, lastLocation.X, lastLocation.Y+10);
            drawBox.Image = bitmap;
            lastLocation = new Point(lastLocation.X, lastLocation.Y+10);
        }
    }
}
