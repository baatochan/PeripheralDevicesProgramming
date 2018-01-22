namespace UpGps20_11
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonConnect = new System.Windows.Forms.Button();
            this.buttonClose = new System.Windows.Forms.Button();
            this.textBoxData = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.labelWsp = new System.Windows.Forms.Label();
            this.labelSatelity = new System.Windows.Forms.Label();
            this.labelSat = new System.Windows.Forms.Label();
            this.labelWysokosc = new System.Windows.Forms.Label();
            this.labelWys = new System.Windows.Forms.Label();
            this.labelWspWE = new System.Windows.Forms.Label();
            this.webBrowserGPS = new System.Windows.Forms.WebBrowser();
            this.textBoxLink = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(12, 12);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 0;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // buttonClose
            // 
            this.buttonClose.Location = new System.Drawing.Point(93, 12);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(75, 23);
            this.buttonClose.TabIndex = 1;
            this.buttonClose.Text = "Close Port";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // textBoxData
            // 
            this.textBoxData.Location = new System.Drawing.Point(15, 41);
            this.textBoxData.Multiline = true;
            this.textBoxData.Name = "textBoxData";
            this.textBoxData.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxData.Size = new System.Drawing.Size(439, 85);
            this.textBoxData.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 129);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(75, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Wspolrzedne: ";
            // 
            // labelWsp
            // 
            this.labelWsp.AutoSize = true;
            this.labelWsp.Location = new System.Drawing.Point(93, 129);
            this.labelWsp.Name = "labelWsp";
            this.labelWsp.Size = new System.Drawing.Size(0, 13);
            this.labelWsp.TabIndex = 4;
            // 
            // labelSatelity
            // 
            this.labelSatelity.AutoSize = true;
            this.labelSatelity.Location = new System.Drawing.Point(12, 172);
            this.labelSatelity.Name = "labelSatelity";
            this.labelSatelity.Size = new System.Drawing.Size(64, 13);
            this.labelSatelity.TabIndex = 5;
            this.labelSatelity.Text = "Ilosc Satelit:";
            // 
            // labelSat
            // 
            this.labelSat.AutoSize = true;
            this.labelSat.Location = new System.Drawing.Point(93, 172);
            this.labelSat.Name = "labelSat";
            this.labelSat.Size = new System.Drawing.Size(0, 13);
            this.labelSat.TabIndex = 6;
            // 
            // labelWysokosc
            // 
            this.labelWysokosc.AutoSize = true;
            this.labelWysokosc.Location = new System.Drawing.Point(12, 200);
            this.labelWysokosc.Name = "labelWysokosc";
            this.labelWysokosc.Size = new System.Drawing.Size(60, 13);
            this.labelWysokosc.TabIndex = 7;
            this.labelWysokosc.Text = "Wysokosc:";
            // 
            // labelWys
            // 
            this.labelWys.AutoSize = true;
            this.labelWys.Location = new System.Drawing.Point(93, 200);
            this.labelWys.Name = "labelWys";
            this.labelWys.Size = new System.Drawing.Size(0, 13);
            this.labelWys.TabIndex = 8;
            // 
            // labelWspWE
            // 
            this.labelWspWE.AutoSize = true;
            this.labelWspWE.Location = new System.Drawing.Point(93, 142);
            this.labelWspWE.Name = "labelWspWE";
            this.labelWspWE.Size = new System.Drawing.Size(0, 13);
            this.labelWspWE.TabIndex = 9;
            // 
            // webBrowserGPS
            // 
            this.webBrowserGPS.Location = new System.Drawing.Point(225, 132);
            this.webBrowserGPS.MinimumSize = new System.Drawing.Size(20, 20);
            this.webBrowserGPS.Name = "webBrowserGPS";
            this.webBrowserGPS.Size = new System.Drawing.Size(786, 452);
            this.webBrowserGPS.TabIndex = 10;
            // 
            // textBoxLink
            // 
            this.textBoxLink.Location = new System.Drawing.Point(714, 106);
            this.textBoxLink.Name = "textBoxLink";
            this.textBoxLink.Size = new System.Drawing.Size(297, 20);
            this.textBoxLink.TabIndex = 11;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(641, 90);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(370, 13);
            this.label2.TabIndex = 12;
            this.label2.Text = "Jezeli mapa nie dziala, mozesz skorzystac z tego linku i wejsc w przegladarke";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1023, 596);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBoxLink);
            this.Controls.Add(this.webBrowserGPS);
            this.Controls.Add(this.labelWspWE);
            this.Controls.Add(this.labelWys);
            this.Controls.Add(this.labelWysokosc);
            this.Controls.Add(this.labelSat);
            this.Controls.Add(this.labelSatelity);
            this.Controls.Add(this.labelWsp);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxData);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.buttonConnect);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.TextBox textBoxData;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelWsp;
        private System.Windows.Forms.Label labelSatelity;
        private System.Windows.Forms.Label labelSat;
        private System.Windows.Forms.Label labelWysokosc;
        private System.Windows.Forms.Label labelWys;
        private System.Windows.Forms.Label labelWspWE;
        private System.Windows.Forms.WebBrowser webBrowserGPS;
        private System.Windows.Forms.TextBox textBoxLink;
        private System.Windows.Forms.Label label2;
    }
}

