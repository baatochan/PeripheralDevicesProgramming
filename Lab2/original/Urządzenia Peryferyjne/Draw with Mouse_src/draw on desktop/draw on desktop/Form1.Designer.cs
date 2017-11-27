namespace draw_on_desktop
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.ColorButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripLabel2 = new System.Windows.Forms.ToolStripLabel();
            this.widthcombo = new System.Windows.Forms.ToolStripComboBox();
            this.BuildToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.clearToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.previewToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.colorDialog = new System.Windows.Forms.ColorDialog();
            this.Workerthread = new System.ComponentModel.BackgroundWorker();
            this.filesave = new System.Windows.Forms.SaveFileDialog();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel1,
            this.ColorButton,
            this.toolStripSeparator1,
            this.toolStripLabel2,
            this.widthcombo,
            this.BuildToolStripButton,
            this.clearToolStripButton,
            this.previewToolStripButton});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(593, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel1.Text = "Colour";
            // 
            // ColorButton
            // 
            this.ColorButton.BackColor = System.Drawing.Color.Black;
            this.ColorButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ColorButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ColorButton.Name = "ColorButton";
            this.ColorButton.Size = new System.Drawing.Size(23, 22);
            this.ColorButton.Text = "toolStripButton1";
            this.ColorButton.ToolTipText = "Click to change";
            this.ColorButton.BackColorChanged += new System.EventHandler(this.ColorButton_BackColorChanged);
            this.ColorButton.Click += new System.EventHandler(this.ColorButton_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(0, 22);
            // 
            // toolStripLabel2
            // 
            this.toolStripLabel2.Name = "toolStripLabel2";
            this.toolStripLabel2.Size = new System.Drawing.Size(51, 22);
            this.toolStripLabel2.Text = "    Width";
            // 
            // widthcombo
            // 
            this.widthcombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.widthcombo.Name = "widthcombo";
            this.widthcombo.Size = new System.Drawing.Size(100, 25);
            this.widthcombo.SelectedIndexChanged += new System.EventHandler(this.widthcombo_SelectedIndexChanged);
            // 
            // BuildToolStripButton
            // 
            this.BuildToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("BuildToolStripButton.Image")));
            this.BuildToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BuildToolStripButton.Name = "BuildToolStripButton";
            this.BuildToolStripButton.Size = new System.Drawing.Size(54, 22);
            this.BuildToolStripButton.Text = "&Build";
            this.BuildToolStripButton.Click += new System.EventHandler(this.BuildToolStripButton_Click);
            // 
            // clearToolStripButton
            // 
            this.clearToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("clearToolStripButton.Image")));
            this.clearToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.clearToolStripButton.Name = "clearToolStripButton";
            this.clearToolStripButton.Size = new System.Drawing.Size(54, 22);
            this.clearToolStripButton.Text = "&Clear";
            this.clearToolStripButton.Click += new System.EventHandler(this.clearToolStripButton_Click);
            // 
            // previewToolStripButton
            // 
            this.previewToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("previewToolStripButton.Image")));
            this.previewToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.previewToolStripButton.Name = "previewToolStripButton";
            this.previewToolStripButton.Size = new System.Drawing.Size(68, 22);
            this.previewToolStripButton.Text = "&Preview";
            this.previewToolStripButton.Click += new System.EventHandler(this.previewToolStripButton_Click);
            // 
            // colorDialog
            // 
            this.colorDialog.AnyColor = true;
            // 
            // Workerthread
            // 
            this.Workerthread.DoWork += new System.ComponentModel.DoWorkEventHandler(this.Workerthread_DoWork);
            this.Workerthread.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.Workerthread_RunWorkerCompleted);
            // 
            // filesave
            // 
            this.filesave.Filter = "Executable files (*.exe)|*.exe";
            this.filesave.RestoreDirectory = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.ClientSize = new System.Drawing.Size(593, 389);
            this.Controls.Add(this.toolStrip1);
            this.DoubleBuffered = true;
            this.Name = "Form1";
            this.Text = "Form1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseUp);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton ColorButton;
        private System.Windows.Forms.ColorDialog colorDialog;
        private System.Windows.Forms.ToolStripLabel toolStripSeparator1;
        private System.Windows.Forms.ToolStripLabel toolStripLabel2;
        private System.Windows.Forms.ToolStripComboBox widthcombo;
        private System.Windows.Forms.ToolStripButton clearToolStripButton;
        private System.Windows.Forms.ToolStripButton BuildToolStripButton;
        private System.Windows.Forms.ToolStripButton previewToolStripButton;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.ComponentModel.BackgroundWorker Workerthread;
        private System.Windows.Forms.SaveFileDialog filesave;

    }
}

