namespace WindowsFormsApp2
{
    partial class Form2
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
            this.labelName = new System.Windows.Forms.Label();
            this.labelMac = new System.Windows.Forms.Label();
            this.labelConnected = new System.Windows.Forms.Label();
            this.labelOtherText = new System.Windows.Forms.Label();
            this.labeConnectedText = new System.Windows.Forms.Label();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.labelMactext = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonPair = new System.Windows.Forms.Button();
            this.listBox2 = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.SuspendLayout();
            // 
            // labelName
            // 
            this.labelName.AutoSize = true;
            this.labelName.Location = new System.Drawing.Point(82, 9);
            this.labelName.Name = "labelName";
            this.labelName.Size = new System.Drawing.Size(35, 13);
            this.labelName.TabIndex = 0;
            this.labelName.Text = "label1";
            // 
            // labelMac
            // 
            this.labelMac.AutoSize = true;
            this.labelMac.Location = new System.Drawing.Point(82, 22);
            this.labelMac.Name = "labelMac";
            this.labelMac.Size = new System.Drawing.Size(35, 13);
            this.labelMac.TabIndex = 1;
            this.labelMac.Text = "label2";
            // 
            // labelConnected
            // 
            this.labelConnected.AutoSize = true;
            this.labelConnected.Location = new System.Drawing.Point(82, 35);
            this.labelConnected.Name = "labelConnected";
            this.labelConnected.Size = new System.Drawing.Size(35, 13);
            this.labelConnected.TabIndex = 2;
            this.labelConnected.Text = "label3";
            // 
            // labelOtherText
            // 
            this.labelOtherText.AutoSize = true;
            this.labelOtherText.Location = new System.Drawing.Point(12, 48);
            this.labelOtherText.Name = "labelOtherText";
            this.labelOtherText.Size = new System.Drawing.Size(33, 13);
            this.labelOtherText.TabIndex = 3;
            this.labelOtherText.Text = "Other";
            // 
            // labeConnectedText
            // 
            this.labeConnectedText.AutoSize = true;
            this.labeConnectedText.Location = new System.Drawing.Point(12, 35);
            this.labeConnectedText.Name = "labeConnectedText";
            this.labeConnectedText.Size = new System.Drawing.Size(64, 13);
            this.labeConnectedText.TabIndex = 4;
            this.labeConnectedText.Text = "Connection:";
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(13, 65);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(150, 290);
            this.listBox1.TabIndex = 5;
            // 
            // labelMactext
            // 
            this.labelMactext.AutoSize = true;
            this.labelMactext.Location = new System.Drawing.Point(10, 22);
            this.labelMactext.Name = "labelMactext";
            this.labelMactext.Size = new System.Drawing.Size(45, 13);
            this.labelMactext.TabIndex = 6;
            this.labelMactext.Text = "Address";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Name";
            // 
            // buttonPair
            // 
            this.buttonPair.Location = new System.Drawing.Point(397, 13);
            this.buttonPair.Name = "buttonPair";
            this.buttonPair.Size = new System.Drawing.Size(75, 23);
            this.buttonPair.TabIndex = 8;
            this.buttonPair.Text = "Pair this device";
            this.buttonPair.UseVisualStyleBackColor = true;
            this.buttonPair.Click += new System.EventHandler(this.buttonPair_Click);
            // 
            // listBox2
            // 
            this.listBox2.FormattingEnabled = true;
            this.listBox2.Location = new System.Drawing.Point(169, 143);
            this.listBox2.Name = "listBox2";
            this.listBox2.Size = new System.Drawing.Size(302, 212);
            this.listBox2.TabIndex = 9;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(169, 127);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(58, 13);
            this.label1.TabIndex = 10;
            this.label1.Text = "Log output";
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(484, 361);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.listBox2);
            this.Controls.Add(this.buttonPair);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.labelMactext);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.labeConnectedText);
            this.Controls.Add(this.labelOtherText);
            this.Controls.Add(this.labelConnected);
            this.Controls.Add(this.labelMac);
            this.Controls.Add(this.labelName);
            this.Name = "Form2";
            this.Text = "Form2";
            this.Load += new System.EventHandler(this.Form2_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelName;
        private System.Windows.Forms.Label labelMac;
        private System.Windows.Forms.Label labelConnected;
        private System.Windows.Forms.Label labelOtherText;
        private System.Windows.Forms.Label labeConnectedText;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label labelMactext;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonPair;
        private System.Windows.Forms.ListBox listBox2;
        private System.Windows.Forms.Label label1;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
    }
}