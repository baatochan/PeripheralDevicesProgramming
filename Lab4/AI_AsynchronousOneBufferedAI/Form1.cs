﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Automation.BDaq;

namespace AI_AsynchronousOneBufferedAI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public BufferedAiCtrl buffer {get; set;}


    }
}
