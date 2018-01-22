namespace GPS_S_Ch
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
            this.components = new System.ComponentModel.Container();
            this.namePort = new System.Windows.Forms.Label();
            this.portName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.longtitudeText = new System.Windows.Forms.TextBox();
            this.latitudeText = new System.Windows.Forms.TextBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.openConection = new System.Windows.Forms.Button();
            this.closeConection = new System.Windows.Forms.Button();
            this.showOnMapButton = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.wysnpmTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.sateliteAmountTextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // namePort
            // 
            this.namePort.AutoSize = true;
            this.namePort.Location = new System.Drawing.Point(12, 9);
            this.namePort.Name = "namePort";
            this.namePort.Size = new System.Drawing.Size(70, 13);
            this.namePort.TabIndex = 0;
            this.namePort.Text = "Nazwa portu:";
            // 
            // portName
            // 
            this.portName.Location = new System.Drawing.Point(88, 6);
            this.portName.Name = "portName";
            this.portName.Size = new System.Drawing.Size(48, 20);
            this.portName.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 40);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(111, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Dugosc geograficzna:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(124, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Szerokosc geograficzna:";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // longtitudeText
            // 
            this.longtitudeText.Location = new System.Drawing.Point(142, 37);
            this.longtitudeText.Name = "longtitudeText";
            this.longtitudeText.Size = new System.Drawing.Size(89, 20);
            this.longtitudeText.TabIndex = 4;
            // 
            // latitudeText
            // 
            this.latitudeText.Location = new System.Drawing.Point(142, 63);
            this.latitudeText.Name = "latitudeText";
            this.latitudeText.Size = new System.Drawing.Size(89, 20);
            this.latitudeText.TabIndex = 5;
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // openConection
            // 
            this.openConection.Location = new System.Drawing.Point(142, 4);
            this.openConection.Name = "openConection";
            this.openConection.Size = new System.Drawing.Size(89, 23);
            this.openConection.TabIndex = 6;
            this.openConection.Text = "Polacz";
            this.openConection.UseVisualStyleBackColor = true;
            this.openConection.Click += new System.EventHandler(this.openConection_Click);
            // 
            // closeConection
            // 
            this.closeConection.Location = new System.Drawing.Point(237, 3);
            this.closeConection.Name = "closeConection";
            this.closeConection.Size = new System.Drawing.Size(89, 23);
            this.closeConection.TabIndex = 7;
            this.closeConection.Text = "Rozlacz";
            this.closeConection.UseVisualStyleBackColor = true;
            this.closeConection.Click += new System.EventHandler(this.closeConection_Click);
            // 
            // showOnMapButton
            // 
            this.showOnMapButton.Location = new System.Drawing.Point(237, 37);
            this.showOnMapButton.Name = "showOnMapButton";
            this.showOnMapButton.Size = new System.Drawing.Size(89, 42);
            this.showOnMapButton.TabIndex = 8;
            this.showOnMapButton.Text = "Pokaz na mapie";
            this.showOnMapButton.UseVisualStyleBackColor = true;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 147);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(314, 85);
            this.textBox1.TabIndex = 9;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 89);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(92, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Wysokosc n.p.m.:";
            // 
            // wysnpmTextBox
            // 
            this.wysnpmTextBox.Location = new System.Drawing.Point(110, 89);
            this.wysnpmTextBox.Name = "wysnpmTextBox";
            this.wysnpmTextBox.Size = new System.Drawing.Size(121, 20);
            this.wysnpmTextBox.TabIndex = 11;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 118);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(62, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "Ilosc satelit:";
            // 
            // sateliteAmountTextBox
            // 
            this.sateliteAmountTextBox.Location = new System.Drawing.Point(80, 115);
            this.sateliteAmountTextBox.Name = "sateliteAmountTextBox";
            this.sateliteAmountTextBox.Size = new System.Drawing.Size(151, 20);
            this.sateliteAmountTextBox.TabIndex = 13;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(334, 249);
            this.Controls.Add(this.sateliteAmountTextBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.wysnpmTextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.showOnMapButton);
            this.Controls.Add(this.closeConection);
            this.Controls.Add(this.openConection);
            this.Controls.Add(this.latitudeText);
            this.Controls.Add(this.longtitudeText);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.portName);
            this.Controls.Add(this.namePort);
            this.Name = "Form1";
            this.Text = "Nazwa portu";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label namePort;
        private System.Windows.Forms.TextBox portName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox longtitudeText;
        private System.Windows.Forms.TextBox latitudeText;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button openConection;
        private System.Windows.Forms.Button closeConection;
        private System.Windows.Forms.Button showOnMapButton;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox wysnpmTextBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox sateliteAmountTextBox;
    }
}

