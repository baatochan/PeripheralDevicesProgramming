namespace GPSWinForms
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
            this.btnConnectToGps = new System.Windows.Forms.Button();
            this.btnConnect = new System.Windows.Forms.Button();
            this.txtBoxPositionLong = new System.Windows.Forms.TextBox();
            this.txtBoxSerialPort = new System.Windows.Forms.TextBox();
            this.lblPosition = new System.Windows.Forms.Label();
            this.txtBoxPositionLatidute = new System.Windows.Forms.TextBox();
            this.btnShowInBrowser = new System.Windows.Forms.Button();
            this.txtSatelites = new System.Windows.Forms.TextBox();
            this.lblSatelities = new System.Windows.Forms.Label();
            this.txtHighAboveSee = new System.Windows.Forms.TextBox();
            this.lblHighAboveSee = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnConnectToGps
            // 
            this.btnConnectToGps.Location = new System.Drawing.Point(1107, 694);
            this.btnConnectToGps.Name = "btnConnectToGps";
            this.btnConnectToGps.Size = new System.Drawing.Size(79, 27);
            this.btnConnectToGps.TabIndex = 0;
            this.btnConnectToGps.Text = "Zbieraj Dane";
            this.btnConnectToGps.UseVisualStyleBackColor = true;
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(362, 38);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(97, 23);
            this.btnConnect.TabIndex = 1;
            this.btnConnect.Text = "Connect To Gps";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // txtBoxPositionLong
            // 
            this.txtBoxPositionLong.Location = new System.Drawing.Point(103, 35);
            this.txtBoxPositionLong.Name = "txtBoxPositionLong";
            this.txtBoxPositionLong.Size = new System.Drawing.Size(99, 20);
            this.txtBoxPositionLong.TabIndex = 2;
            // 
            // txtBoxSerialPort
            // 
            this.txtBoxSerialPort.Location = new System.Drawing.Point(362, 12);
            this.txtBoxSerialPort.Name = "txtBoxSerialPort";
            this.txtBoxSerialPort.Size = new System.Drawing.Size(67, 20);
            this.txtBoxSerialPort.TabIndex = 3;
            this.txtBoxSerialPort.Text = "COM4";
            // 
            // lblPosition
            // 
            this.lblPosition.AutoSize = true;
            this.lblPosition.Location = new System.Drawing.Point(12, 38);
            this.lblPosition.Name = "lblPosition";
            this.lblPosition.Size = new System.Drawing.Size(69, 13);
            this.lblPosition.TabIndex = 4;
            this.lblPosition.Text = "GPS Position";
            // 
            // txtBoxPositionLatidute
            // 
            this.txtBoxPositionLatidute.Location = new System.Drawing.Point(208, 35);
            this.txtBoxPositionLatidute.Name = "txtBoxPositionLatidute";
            this.txtBoxPositionLatidute.Size = new System.Drawing.Size(105, 20);
            this.txtBoxPositionLatidute.TabIndex = 5;
            // 
            // btnShowInBrowser
            // 
            this.btnShowInBrowser.Location = new System.Drawing.Point(22, 141);
            this.btnShowInBrowser.Name = "btnShowInBrowser";
            this.btnShowInBrowser.Size = new System.Drawing.Size(275, 23);
            this.btnShowInBrowser.TabIndex = 6;
            this.btnShowInBrowser.Text = "Show In Browser";
            this.btnShowInBrowser.UseVisualStyleBackColor = true;
            this.btnShowInBrowser.Click += new System.EventHandler(this.btnShowInBrowser_Click);
            // 
            // txtSatelites
            // 
            this.txtSatelites.Location = new System.Drawing.Point(103, 61);
            this.txtSatelites.Name = "txtSatelites";
            this.txtSatelites.Size = new System.Drawing.Size(210, 20);
            this.txtSatelites.TabIndex = 7;
            this.txtSatelites.TextChanged += new System.EventHandler(this.txtSatelites_TextChanged);
            // 
            // lblSatelities
            // 
            this.lblSatelities.AutoSize = true;
            this.lblSatelities.Location = new System.Drawing.Point(19, 65);
            this.lblSatelities.Name = "lblSatelities";
            this.lblSatelities.Size = new System.Drawing.Size(49, 13);
            this.lblSatelities.TabIndex = 8;
            this.lblSatelities.Text = "Satelities";
            // 
            // txtHighAboveSee
            // 
            this.txtHighAboveSee.Location = new System.Drawing.Point(103, 87);
            this.txtHighAboveSee.Name = "txtHighAboveSee";
            this.txtHighAboveSee.Size = new System.Drawing.Size(210, 20);
            this.txtHighAboveSee.TabIndex = 9;
            // 
            // lblHighAboveSee
            // 
            this.lblHighAboveSee.AutoSize = true;
            this.lblHighAboveSee.Location = new System.Drawing.Point(12, 90);
            this.lblHighAboveSee.Name = "lblHighAboveSee";
            this.lblHighAboveSee.Size = new System.Drawing.Size(85, 13);
            this.lblHighAboveSee.TabIndex = 10;
            this.lblHighAboveSee.Text = "High Above See";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(474, 282);
            this.Controls.Add(this.lblHighAboveSee);
            this.Controls.Add(this.txtHighAboveSee);
            this.Controls.Add(this.lblSatelities);
            this.Controls.Add(this.txtSatelites);
            this.Controls.Add(this.btnShowInBrowser);
            this.Controls.Add(this.txtBoxPositionLatidute);
            this.Controls.Add(this.lblPosition);
            this.Controls.Add(this.txtBoxSerialPort);
            this.Controls.Add(this.txtBoxPositionLong);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.btnConnectToGps);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnConnectToGps;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.TextBox txtBoxPositionLong;
        private System.Windows.Forms.TextBox txtBoxSerialPort;
        private System.Windows.Forms.Label lblPosition;
        private System.Windows.Forms.TextBox txtBoxPositionLatidute;
        private System.Windows.Forms.Button btnShowInBrowser;
        private System.Windows.Forms.TextBox txtSatelites;
        private System.Windows.Forms.Label lblSatelities;
        private System.Windows.Forms.TextBox txtHighAboveSee;
        private System.Windows.Forms.Label lblHighAboveSee;
    }
}

