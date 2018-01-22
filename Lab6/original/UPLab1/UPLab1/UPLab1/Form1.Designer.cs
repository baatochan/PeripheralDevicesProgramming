namespace UPLab1
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
            this.ControlsGroupBox = new System.Windows.Forms.GroupBox();
            this.downButton = new System.Windows.Forms.Button();
            this.upButton = new System.Windows.Forms.Button();
            this.rightButton = new System.Windows.Forms.Button();
            this.backwardButton = new System.Windows.Forms.Button();
            this.forwardButton = new System.Windows.Forms.Button();
            this.leftButton = new System.Windows.Forms.Button();
            this.ConnectionGroupBox = new System.Windows.Forms.GroupBox();
            this.COMDisconnectButton = new System.Windows.Forms.Button();
            this.COMConnectButton = new System.Windows.Forms.Button();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.COMPortLabel = new System.Windows.Forms.Label();
            this.motorControlGroupBox = new System.Windows.Forms.GroupBox();
            this.motorGetStateButton = new System.Windows.Forms.Button();
            this.motorSetStateButton = new System.Windows.Forms.Button();
            this.motorResetbutton = new System.Windows.Forms.Button();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.motorStateGroupBox = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox10 = new System.Windows.Forms.TextBox();
            this.textBox9 = new System.Windows.Forms.TextBox();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBox4 = new System.Windows.Forms.ComboBox();
            this.comboBox3 = new System.Windows.Forms.ComboBox();
            this.drawBox = new System.Windows.Forms.PictureBox();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.ControlsGroupBox.SuspendLayout();
            this.ConnectionGroupBox.SuspendLayout();
            this.motorControlGroupBox.SuspendLayout();
            this.motorStateGroupBox.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.drawBox)).BeginInit();
            this.SuspendLayout();
            // 
            // ControlsGroupBox
            // 
            this.ControlsGroupBox.Controls.Add(this.downButton);
            this.ControlsGroupBox.Controls.Add(this.upButton);
            this.ControlsGroupBox.Controls.Add(this.rightButton);
            this.ControlsGroupBox.Controls.Add(this.backwardButton);
            this.ControlsGroupBox.Controls.Add(this.forwardButton);
            this.ControlsGroupBox.Controls.Add(this.leftButton);
            this.ControlsGroupBox.Location = new System.Drawing.Point(211, 263);
            this.ControlsGroupBox.Name = "ControlsGroupBox";
            this.ControlsGroupBox.Size = new System.Drawing.Size(117, 100);
            this.ControlsGroupBox.TabIndex = 0;
            this.ControlsGroupBox.TabStop = false;
            this.ControlsGroupBox.Text = "Controls";
            // 
            // downButton
            // 
            this.downButton.Location = new System.Drawing.Point(84, 71);
            this.downButton.Name = "downButton";
            this.downButton.Size = new System.Drawing.Size(20, 20);
            this.downButton.TabIndex = 6;
            this.downButton.UseVisualStyleBackColor = true;
            // 
            // upButton
            // 
            this.upButton.Location = new System.Drawing.Point(84, 19);
            this.upButton.Name = "upButton";
            this.upButton.Size = new System.Drawing.Size(20, 20);
            this.upButton.TabIndex = 5;
            this.upButton.UseVisualStyleBackColor = true;
            // 
            // rightButton
            // 
            this.rightButton.Location = new System.Drawing.Point(58, 45);
            this.rightButton.Name = "rightButton";
            this.rightButton.Size = new System.Drawing.Size(20, 20);
            this.rightButton.TabIndex = 1;
            this.rightButton.Text = "→";
            this.rightButton.UseVisualStyleBackColor = true;
            this.rightButton.Click += new System.EventHandler(this.rightButton_Click);
            this.rightButton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.rightButton_KeyDown);
            // 
            // backwardButton
            // 
            this.backwardButton.Location = new System.Drawing.Point(32, 71);
            this.backwardButton.Name = "backwardButton";
            this.backwardButton.Size = new System.Drawing.Size(20, 20);
            this.backwardButton.TabIndex = 3;
            this.backwardButton.Text = "↓";
            this.backwardButton.UseVisualStyleBackColor = true;
            this.backwardButton.Click += new System.EventHandler(this.backwardButton_Click);
            // 
            // forwardButton
            // 
            this.forwardButton.Location = new System.Drawing.Point(32, 19);
            this.forwardButton.Name = "forwardButton";
            this.forwardButton.Size = new System.Drawing.Size(20, 20);
            this.forwardButton.TabIndex = 1;
            this.forwardButton.Text = "↑";
            this.forwardButton.UseVisualStyleBackColor = true;
            this.forwardButton.Click += new System.EventHandler(this.forwardButton_Click);
            this.forwardButton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.forwardButton_KeyDown);
            // 
            // leftButton
            // 
            this.leftButton.Location = new System.Drawing.Point(6, 45);
            this.leftButton.Name = "leftButton";
            this.leftButton.Size = new System.Drawing.Size(23, 20);
            this.leftButton.TabIndex = 0;
            this.leftButton.Text = "←";
            this.leftButton.UseVisualStyleBackColor = true;
            this.leftButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // ConnectionGroupBox
            // 
            this.ConnectionGroupBox.Controls.Add(this.COMDisconnectButton);
            this.ConnectionGroupBox.Controls.Add(this.COMConnectButton);
            this.ConnectionGroupBox.Controls.Add(this.comboBox1);
            this.ConnectionGroupBox.Controls.Add(this.COMPortLabel);
            this.ConnectionGroupBox.Location = new System.Drawing.Point(13, 13);
            this.ConnectionGroupBox.Name = "ConnectionGroupBox";
            this.ConnectionGroupBox.Size = new System.Drawing.Size(314, 42);
            this.ConnectionGroupBox.TabIndex = 1;
            this.ConnectionGroupBox.TabStop = false;
            this.ConnectionGroupBox.Text = "Connection";
            // 
            // COMDisconnectButton
            // 
            this.COMDisconnectButton.Location = new System.Drawing.Point(234, 11);
            this.COMDisconnectButton.Name = "COMDisconnectButton";
            this.COMDisconnectButton.Size = new System.Drawing.Size(75, 23);
            this.COMDisconnectButton.TabIndex = 4;
            this.COMDisconnectButton.Text = "Disconnect";
            this.COMDisconnectButton.UseVisualStyleBackColor = true;
            // 
            // COMConnectButton
            // 
            this.COMConnectButton.Location = new System.Drawing.Point(153, 11);
            this.COMConnectButton.Name = "COMConnectButton";
            this.COMConnectButton.Size = new System.Drawing.Size(75, 23);
            this.COMConnectButton.TabIndex = 3;
            this.COMConnectButton.Text = "Connect";
            this.COMConnectButton.UseVisualStyleBackColor = true;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(65, 13);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(82, 21);
            this.comboBox1.TabIndex = 2;
            // 
            // COMPortLabel
            // 
            this.COMPortLabel.AutoSize = true;
            this.COMPortLabel.Location = new System.Drawing.Point(3, 16);
            this.COMPortLabel.Name = "COMPortLabel";
            this.COMPortLabel.Size = new System.Drawing.Size(56, 13);
            this.COMPortLabel.TabIndex = 1;
            this.COMPortLabel.Text = "COM Port:";
            // 
            // motorControlGroupBox
            // 
            this.motorControlGroupBox.Controls.Add(this.motorGetStateButton);
            this.motorControlGroupBox.Controls.Add(this.motorSetStateButton);
            this.motorControlGroupBox.Controls.Add(this.motorResetbutton);
            this.motorControlGroupBox.Controls.Add(this.comboBox2);
            this.motorControlGroupBox.Location = new System.Drawing.Point(13, 61);
            this.motorControlGroupBox.Name = "motorControlGroupBox";
            this.motorControlGroupBox.Size = new System.Drawing.Size(314, 42);
            this.motorControlGroupBox.TabIndex = 3;
            this.motorControlGroupBox.TabStop = false;
            this.motorControlGroupBox.Text = "Motor control";
            // 
            // motorGetStateButton
            // 
            this.motorGetStateButton.Location = new System.Drawing.Point(233, 13);
            this.motorGetStateButton.Name = "motorGetStateButton";
            this.motorGetStateButton.Size = new System.Drawing.Size(75, 23);
            this.motorGetStateButton.TabIndex = 3;
            this.motorGetStateButton.Text = "Get state";
            this.motorGetStateButton.UseVisualStyleBackColor = true;
            // 
            // motorSetStateButton
            // 
            this.motorSetStateButton.Location = new System.Drawing.Point(152, 13);
            this.motorSetStateButton.Name = "motorSetStateButton";
            this.motorSetStateButton.Size = new System.Drawing.Size(75, 23);
            this.motorSetStateButton.TabIndex = 2;
            this.motorSetStateButton.Text = "Set state";
            this.motorSetStateButton.UseVisualStyleBackColor = true;
            // 
            // motorResetbutton
            // 
            this.motorResetbutton.Location = new System.Drawing.Point(100, 13);
            this.motorResetbutton.Name = "motorResetbutton";
            this.motorResetbutton.Size = new System.Drawing.Size(46, 23);
            this.motorResetbutton.TabIndex = 1;
            this.motorResetbutton.Text = "Reset";
            this.motorResetbutton.UseVisualStyleBackColor = true;
            // 
            // comboBox2
            // 
            this.comboBox2.BackColor = System.Drawing.SystemColors.Window;
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Location = new System.Drawing.Point(6, 13);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(76, 21);
            this.comboBox2.TabIndex = 0;
            // 
            // motorStateGroupBox
            // 
            this.motorStateGroupBox.Controls.Add(this.label3);
            this.motorStateGroupBox.Controls.Add(this.label2);
            this.motorStateGroupBox.Controls.Add(this.label1);
            this.motorStateGroupBox.Controls.Add(this.textBox10);
            this.motorStateGroupBox.Controls.Add(this.textBox9);
            this.motorStateGroupBox.Controls.Add(this.textBox8);
            this.motorStateGroupBox.Location = new System.Drawing.Point(13, 109);
            this.motorStateGroupBox.Name = "motorStateGroupBox";
            this.motorStateGroupBox.Size = new System.Drawing.Size(314, 65);
            this.motorStateGroupBox.TabIndex = 4;
            this.motorStateGroupBox.TabStop = false;
            this.motorStateGroupBox.Text = "Motor state";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 41);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(127, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Tacho limit (0 run forever)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 15);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(37, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Power";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(137, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Turn ratio:";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // textBox10
            // 
            this.textBox10.Location = new System.Drawing.Point(47, 12);
            this.textBox10.Name = "textBox10";
            this.textBox10.Size = new System.Drawing.Size(80, 20);
            this.textBox10.TabIndex = 2;
            // 
            // textBox9
            // 
            this.textBox9.Location = new System.Drawing.Point(198, 12);
            this.textBox9.Name = "textBox9";
            this.textBox9.Size = new System.Drawing.Size(49, 20);
            this.textBox9.TabIndex = 1;
            // 
            // textBox8
            // 
            this.textBox8.Location = new System.Drawing.Point(140, 38);
            this.textBox8.Name = "textBox8";
            this.textBox8.Size = new System.Drawing.Size(107, 20);
            this.textBox8.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.comboBox4);
            this.groupBox1.Controls.Add(this.comboBox3);
            this.groupBox1.Location = new System.Drawing.Point(13, 180);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(314, 77);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 49);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(56, 13);
            this.label5.TabIndex = 3;
            this.label5.Text = "Run state:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(90, 13);
            this.label4.TabIndex = 2;
            this.label4.Text = "Regulation mode:";
            // 
            // comboBox4
            // 
            this.comboBox4.FormattingEnabled = true;
            this.comboBox4.Location = new System.Drawing.Point(126, 46);
            this.comboBox4.Name = "comboBox4";
            this.comboBox4.Size = new System.Drawing.Size(121, 21);
            this.comboBox4.TabIndex = 1;
            // 
            // comboBox3
            // 
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Location = new System.Drawing.Point(126, 19);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new System.Drawing.Size(121, 21);
            this.comboBox3.TabIndex = 0;
            // 
            // drawBox
            // 
            this.drawBox.Location = new System.Drawing.Point(333, 13);
            this.drawBox.Name = "drawBox";
            this.drawBox.Size = new System.Drawing.Size(446, 350);
            this.drawBox.TabIndex = 6;
            this.drawBox.TabStop = false;
            this.drawBox.Click += new System.EventHandler(this.pictureBox1_Click);
            this.drawBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.drawBox_MouseDown);
            this.drawBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.drawBox_MouseMove);
            this.drawBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.drawBox_MouseUp);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(13, 263);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(192, 100);
            this.button1.TabIndex = 7;
            this.button1.Text = "Stop";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(227, 369);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 20);
            this.textBox1.TabIndex = 8;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(228, 395);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(100, 20);
            this.textBox2.TabIndex = 9;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(228, 421);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(100, 20);
            this.textBox3.TabIndex = 10;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(186, 372);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(17, 13);
            this.label6.TabIndex = 11;
            this.label6.Text = "X:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(186, 398);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(17, 13);
            this.label7.TabIndex = 12;
            this.label7.Text = "Y:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(186, 424);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(17, 13);
            this.label8.TabIndex = 13;
            this.label8.Text = "Z:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(75, 398);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(78, 13);
            this.label9.TabIndex = 14;
            this.label9.Text = "Robot position:";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(227, 447);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(101, 23);
            this.button2.TabIndex = 15;
            this.button2.Text = "OK";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(791, 480);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.drawBox);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.motorStateGroupBox);
            this.Controls.Add(this.motorControlGroupBox);
            this.Controls.Add(this.ConnectionGroupBox);
            this.Controls.Add(this.ControlsGroupBox);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ControlsGroupBox.ResumeLayout(false);
            this.ConnectionGroupBox.ResumeLayout(false);
            this.ConnectionGroupBox.PerformLayout();
            this.motorControlGroupBox.ResumeLayout(false);
            this.motorStateGroupBox.ResumeLayout(false);
            this.motorStateGroupBox.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.drawBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox ControlsGroupBox;
        private System.Windows.Forms.Button leftButton;
        private System.Windows.Forms.Button downButton;
        private System.Windows.Forms.Button upButton;
        private System.Windows.Forms.Button rightButton;
        private System.Windows.Forms.Button backwardButton;
        private System.Windows.Forms.Button forwardButton;
        private System.Windows.Forms.GroupBox ConnectionGroupBox;
        private System.Windows.Forms.Button COMDisconnectButton;
        private System.Windows.Forms.Button COMConnectButton;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label COMPortLabel;
        private System.Windows.Forms.GroupBox motorControlGroupBox;
        private System.Windows.Forms.Button motorGetStateButton;
        private System.Windows.Forms.Button motorSetStateButton;
        private System.Windows.Forms.Button motorResetbutton;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.GroupBox motorStateGroupBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox10;
        private System.Windows.Forms.TextBox textBox9;
        private System.Windows.Forms.TextBox textBox8;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboBox4;
        private System.Windows.Forms.ComboBox comboBox3;
        private System.Windows.Forms.PictureBox drawBox;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button button2;
    }
}

