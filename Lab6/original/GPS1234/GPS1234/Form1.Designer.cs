namespace GPS1234
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
            this.buttonGetData = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.labelDane = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonGetData
            // 
            this.buttonGetData.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.buttonGetData.Location = new System.Drawing.Point(12, 38);
            this.buttonGetData.Name = "buttonGetData";
            this.buttonGetData.Size = new System.Drawing.Size(111, 36);
            this.buttonGetData.TabIndex = 0;
            this.buttonGetData.Text = "Uzyskaj dane";
            this.buttonGetData.UseVisualStyleBackColor = false;
            this.buttonGetData.Click += new System.EventHandler(this.buttonGetData_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 12);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(111, 20);
            this.textBox1.TabIndex = 1;
            this.textBox1.Text = "COM12";
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // labelDane
            // 
            this.labelDane.AutoSize = true;
            this.labelDane.Location = new System.Drawing.Point(134, 14);
            this.labelDane.Name = "labelDane";
            this.labelDane.Size = new System.Drawing.Size(36, 13);
            this.labelDane.TabIndex = 2;
            this.labelDane.Text = "Dane:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.labelDane);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.buttonGetData);
            this.Name = "Form1";
            this.Text = "GPS";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonGetData;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label labelDane;
    }
}

