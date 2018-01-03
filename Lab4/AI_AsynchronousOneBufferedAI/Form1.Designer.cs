namespace AI_AsynchronousOneBufferedAI
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
            this.textBoxRefresh = new System.Windows.Forms.TextBox();
            this.labelRefresh = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // textBoxRefresh
            // 
            this.textBoxRefresh.Location = new System.Drawing.Point(472, 25);
            this.textBoxRefresh.Name = "textBoxRefresh";
            this.textBoxRefresh.Size = new System.Drawing.Size(100, 20);
            this.textBoxRefresh.TabIndex = 0;
            // 
            // labelRefresh
            // 
            this.labelRefresh.AutoSize = true;
            this.labelRefresh.Location = new System.Drawing.Point(469, 9);
            this.labelRefresh.Name = "labelRefresh";
            this.labelRefresh.Size = new System.Drawing.Size(65, 13);
            this.labelRefresh.TabIndex = 1;
            this.labelRefresh.Text = "Refresh rate";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 362);
            this.Controls.Add(this.labelRefresh);
            this.Controls.Add(this.textBoxRefresh);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxRefresh;
        private System.Windows.Forms.Label labelRefresh;
    }
}