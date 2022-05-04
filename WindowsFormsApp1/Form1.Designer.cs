namespace WindowsFormsApp1
{
    partial class MainWindow
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.chooseFileButton = new System.Windows.Forms.Button();
            this.fileNameTextBox = new System.Windows.Forms.TextBox();
            this.videoFrameCountLabel = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.frameInfoTabControl = new System.Windows.Forms.TabControl();
            this.videoFrameTabPage = new System.Windows.Forms.TabPage();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.audioFrameTabPage = new System.Windows.Forms.TabPage();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.bFrameCountTextBox = new System.Windows.Forms.TextBox();
            this.privateFrameCountTextBox = new System.Windows.Forms.TextBox();
            this.bFrameCountLabel = new System.Windows.Forms.Label();
            this.privateFrameCountLabel = new System.Windows.Forms.Label();
            this.pFrameCountTextBox = new System.Windows.Forms.TextBox();
            this.pFrameCountLabel = new System.Windows.Forms.Label();
            this.audioFrameTextBox = new System.Windows.Forms.TextBox();
            this.iFrameCountTextBox = new System.Windows.Forms.TextBox();
            this.audioFrameCountLabel = new System.Windows.Forms.Label();
            this.iFrameCountLabel = new System.Windows.Forms.Label();
            this.videoFrameCountTextBox = new System.Windows.Forms.TextBox();
            this.parseButton = new System.Windows.Forms.Button();
            this.parseResultLabel = new System.Windows.Forms.Label();
            this.frameTypeLabel = new System.Windows.Forms.Label();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.frameTypeTextBox = new System.Windows.Forms.TextBox();
            this.frameSizeTextBox = new System.Windows.Forms.TextBox();
            this.frameSizeLabel = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.frameInfoTabControl.SuspendLayout();
            this.videoFrameTabPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.audioFrameTabPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // chooseFileButton
            // 
            this.chooseFileButton.Location = new System.Drawing.Point(12, 12);
            this.chooseFileButton.Name = "chooseFileButton";
            this.chooseFileButton.Size = new System.Drawing.Size(94, 23);
            this.chooseFileButton.TabIndex = 0;
            this.chooseFileButton.Text = "choose file";
            this.chooseFileButton.UseVisualStyleBackColor = true;
            this.chooseFileButton.Click += new System.EventHandler(this.chooseFileButton_Click);
            // 
            // fileNameTextBox
            // 
            this.fileNameTextBox.Location = new System.Drawing.Point(136, 12);
            this.fileNameTextBox.Name = "fileNameTextBox";
            this.fileNameTextBox.ReadOnly = true;
            this.fileNameTextBox.Size = new System.Drawing.Size(642, 21);
            this.fileNameTextBox.TabIndex = 1;
            // 
            // videoFrameCountLabel
            // 
            this.videoFrameCountLabel.AutoSize = true;
            this.videoFrameCountLabel.Location = new System.Drawing.Point(6, 17);
            this.videoFrameCountLabel.Name = "videoFrameCountLabel";
            this.videoFrameCountLabel.Size = new System.Drawing.Size(113, 12);
            this.videoFrameCountLabel.TabIndex = 2;
            this.videoFrameCountLabel.Text = "Video Frame Count:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.frameSizeTextBox);
            this.groupBox1.Controls.Add(this.frameSizeLabel);
            this.groupBox1.Controls.Add(this.frameTypeTextBox);
            this.groupBox1.Controls.Add(this.richTextBox1);
            this.groupBox1.Controls.Add(this.frameTypeLabel);
            this.groupBox1.Controls.Add(this.frameInfoTabControl);
            this.groupBox1.Controls.Add(this.bFrameCountTextBox);
            this.groupBox1.Controls.Add(this.privateFrameCountTextBox);
            this.groupBox1.Controls.Add(this.bFrameCountLabel);
            this.groupBox1.Controls.Add(this.privateFrameCountLabel);
            this.groupBox1.Controls.Add(this.pFrameCountTextBox);
            this.groupBox1.Controls.Add(this.pFrameCountLabel);
            this.groupBox1.Controls.Add(this.audioFrameTextBox);
            this.groupBox1.Controls.Add(this.iFrameCountTextBox);
            this.groupBox1.Controls.Add(this.audioFrameCountLabel);
            this.groupBox1.Controls.Add(this.iFrameCountLabel);
            this.groupBox1.Controls.Add(this.videoFrameCountTextBox);
            this.groupBox1.Controls.Add(this.videoFrameCountLabel);
            this.groupBox1.Location = new System.Drawing.Point(15, 84);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(763, 354);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "PS Stream Attribute";
            // 
            // frameInfoTabControl
            // 
            this.frameInfoTabControl.Controls.Add(this.videoFrameTabPage);
            this.frameInfoTabControl.Controls.Add(this.audioFrameTabPage);
            this.frameInfoTabControl.Location = new System.Drawing.Point(8, 79);
            this.frameInfoTabControl.Name = "frameInfoTabControl";
            this.frameInfoTabControl.SelectedIndex = 0;
            this.frameInfoTabControl.Size = new System.Drawing.Size(200, 269);
            this.frameInfoTabControl.TabIndex = 14;
            // 
            // videoFrameTabPage
            // 
            this.videoFrameTabPage.Controls.Add(this.dataGridView1);
            this.videoFrameTabPage.Location = new System.Drawing.Point(4, 22);
            this.videoFrameTabPage.Name = "videoFrameTabPage";
            this.videoFrameTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.videoFrameTabPage.Size = new System.Drawing.Size(192, 243);
            this.videoFrameTabPage.TabIndex = 0;
            this.videoFrameTabPage.Text = "Video Frame";
            this.videoFrameTabPage.UseVisualStyleBackColor = true;
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(0, 0);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(192, 243);
            this.dataGridView1.TabIndex = 0;
            // 
            // audioFrameTabPage
            // 
            this.audioFrameTabPage.Controls.Add(this.dataGridView2);
            this.audioFrameTabPage.Location = new System.Drawing.Point(4, 22);
            this.audioFrameTabPage.Name = "audioFrameTabPage";
            this.audioFrameTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.audioFrameTabPage.Size = new System.Drawing.Size(192, 243);
            this.audioFrameTabPage.TabIndex = 1;
            this.audioFrameTabPage.Text = "Audio Frame";
            this.audioFrameTabPage.UseVisualStyleBackColor = true;
            // 
            // dataGridView2
            // 
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(0, 0);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowTemplate.Height = 23;
            this.dataGridView2.Size = new System.Drawing.Size(192, 243);
            this.dataGridView2.TabIndex = 0;
            // 
            // bFrameCountTextBox
            // 
            this.bFrameCountTextBox.Location = new System.Drawing.Point(653, 41);
            this.bFrameCountTextBox.Name = "bFrameCountTextBox";
            this.bFrameCountTextBox.ReadOnly = true;
            this.bFrameCountTextBox.Size = new System.Drawing.Size(100, 21);
            this.bFrameCountTextBox.TabIndex = 13;
            // 
            // privateFrameCountTextBox
            // 
            this.privateFrameCountTextBox.Location = new System.Drawing.Point(653, 14);
            this.privateFrameCountTextBox.Name = "privateFrameCountTextBox";
            this.privateFrameCountTextBox.ReadOnly = true;
            this.privateFrameCountTextBox.Size = new System.Drawing.Size(100, 21);
            this.privateFrameCountTextBox.TabIndex = 7;
            // 
            // bFrameCountLabel
            // 
            this.bFrameCountLabel.AutoSize = true;
            this.bFrameCountLabel.Location = new System.Drawing.Point(522, 44);
            this.bFrameCountLabel.Name = "bFrameCountLabel";
            this.bFrameCountLabel.Size = new System.Drawing.Size(89, 12);
            this.bFrameCountLabel.TabIndex = 12;
            this.bFrameCountLabel.Text = "B Frame Count:";
            // 
            // privateFrameCountLabel
            // 
            this.privateFrameCountLabel.AutoSize = true;
            this.privateFrameCountLabel.Location = new System.Drawing.Point(522, 17);
            this.privateFrameCountLabel.Name = "privateFrameCountLabel";
            this.privateFrameCountLabel.Size = new System.Drawing.Size(125, 12);
            this.privateFrameCountLabel.TabIndex = 6;
            this.privateFrameCountLabel.Text = "Private Frame Count:";
            // 
            // pFrameCountTextBox
            // 
            this.pFrameCountTextBox.Location = new System.Drawing.Point(388, 41);
            this.pFrameCountTextBox.Name = "pFrameCountTextBox";
            this.pFrameCountTextBox.ReadOnly = true;
            this.pFrameCountTextBox.Size = new System.Drawing.Size(100, 21);
            this.pFrameCountTextBox.TabIndex = 11;
            // 
            // pFrameCountLabel
            // 
            this.pFrameCountLabel.AutoSize = true;
            this.pFrameCountLabel.Location = new System.Drawing.Point(269, 44);
            this.pFrameCountLabel.Name = "pFrameCountLabel";
            this.pFrameCountLabel.Size = new System.Drawing.Size(89, 12);
            this.pFrameCountLabel.TabIndex = 10;
            this.pFrameCountLabel.Text = "P Frame Count:";
            // 
            // audioFrameTextBox
            // 
            this.audioFrameTextBox.Location = new System.Drawing.Point(388, 14);
            this.audioFrameTextBox.Name = "audioFrameTextBox";
            this.audioFrameTextBox.ReadOnly = true;
            this.audioFrameTextBox.Size = new System.Drawing.Size(100, 21);
            this.audioFrameTextBox.TabIndex = 5;
            // 
            // iFrameCountTextBox
            // 
            this.iFrameCountTextBox.Location = new System.Drawing.Point(125, 41);
            this.iFrameCountTextBox.Name = "iFrameCountTextBox";
            this.iFrameCountTextBox.ReadOnly = true;
            this.iFrameCountTextBox.Size = new System.Drawing.Size(100, 21);
            this.iFrameCountTextBox.TabIndex = 9;
            // 
            // audioFrameCountLabel
            // 
            this.audioFrameCountLabel.AutoSize = true;
            this.audioFrameCountLabel.Location = new System.Drawing.Point(269, 17);
            this.audioFrameCountLabel.Name = "audioFrameCountLabel";
            this.audioFrameCountLabel.Size = new System.Drawing.Size(113, 12);
            this.audioFrameCountLabel.TabIndex = 4;
            this.audioFrameCountLabel.Text = "Audio Frame Count:";
            // 
            // iFrameCountLabel
            // 
            this.iFrameCountLabel.AutoSize = true;
            this.iFrameCountLabel.Location = new System.Drawing.Point(6, 44);
            this.iFrameCountLabel.Name = "iFrameCountLabel";
            this.iFrameCountLabel.Size = new System.Drawing.Size(89, 12);
            this.iFrameCountLabel.TabIndex = 8;
            this.iFrameCountLabel.Text = "I Frame Count:";
            // 
            // videoFrameCountTextBox
            // 
            this.videoFrameCountTextBox.Location = new System.Drawing.Point(125, 14);
            this.videoFrameCountTextBox.Name = "videoFrameCountTextBox";
            this.videoFrameCountTextBox.ReadOnly = true;
            this.videoFrameCountTextBox.Size = new System.Drawing.Size(100, 21);
            this.videoFrameCountTextBox.TabIndex = 3;
            // 
            // parseButton
            // 
            this.parseButton.Location = new System.Drawing.Point(12, 41);
            this.parseButton.Name = "parseButton";
            this.parseButton.Size = new System.Drawing.Size(94, 23);
            this.parseButton.TabIndex = 4;
            this.parseButton.Text = "parse";
            this.parseButton.UseVisualStyleBackColor = true;
            // 
            // parseResultLabel
            // 
            this.parseResultLabel.AutoSize = true;
            this.parseResultLabel.Location = new System.Drawing.Point(134, 46);
            this.parseResultLabel.Name = "parseResultLabel";
            this.parseResultLabel.Size = new System.Drawing.Size(0, 12);
            this.parseResultLabel.TabIndex = 5;
            // 
            // frameTypeLabel
            // 
            this.frameTypeLabel.AutoSize = true;
            this.frameTypeLabel.Location = new System.Drawing.Point(214, 86);
            this.frameTypeLabel.Name = "frameTypeLabel";
            this.frameTypeLabel.Size = new System.Drawing.Size(71, 12);
            this.frameTypeLabel.TabIndex = 15;
            this.frameTypeLabel.Text = "Frame Type:";
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(214, 113);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(539, 231);
            this.richTextBox1.TabIndex = 16;
            this.richTextBox1.Text = "";
            // 
            // frameTypeTextBox
            // 
            this.frameTypeTextBox.Location = new System.Drawing.Point(291, 83);
            this.frameTypeTextBox.Name = "frameTypeTextBox";
            this.frameTypeTextBox.ReadOnly = true;
            this.frameTypeTextBox.Size = new System.Drawing.Size(100, 21);
            this.frameTypeTextBox.TabIndex = 17;
            // 
            // frameSizeTextBox
            // 
            this.frameSizeTextBox.Location = new System.Drawing.Point(601, 83);
            this.frameSizeTextBox.Name = "frameSizeTextBox";
            this.frameSizeTextBox.ReadOnly = true;
            this.frameSizeTextBox.Size = new System.Drawing.Size(100, 21);
            this.frameSizeTextBox.TabIndex = 19;
            // 
            // frameSizeLabel
            // 
            this.frameSizeLabel.AutoSize = true;
            this.frameSizeLabel.Location = new System.Drawing.Point(524, 86);
            this.frameSizeLabel.Name = "frameSizeLabel";
            this.frameSizeLabel.Size = new System.Drawing.Size(71, 12);
            this.frameSizeLabel.TabIndex = 18;
            this.frameSizeLabel.Text = "Frame Size:";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.parseResultLabel);
            this.Controls.Add(this.parseButton);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.fileNameTextBox);
            this.Controls.Add(this.chooseFileButton);
            this.Name = "MainWindow";
            this.Text = "Media Stream Parser";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.frameInfoTabControl.ResumeLayout(false);
            this.videoFrameTabPage.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.audioFrameTabPage.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button chooseFileButton;
        private System.Windows.Forms.TextBox fileNameTextBox;
        private System.Windows.Forms.Label videoFrameCountLabel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox videoFrameCountTextBox;
        private System.Windows.Forms.Button parseButton;
        private System.Windows.Forms.TextBox privateFrameCountTextBox;
        private System.Windows.Forms.Label privateFrameCountLabel;
        private System.Windows.Forms.TextBox audioFrameTextBox;
        private System.Windows.Forms.Label audioFrameCountLabel;
        private System.Windows.Forms.Label parseResultLabel;
        private System.Windows.Forms.TabControl frameInfoTabControl;
        private System.Windows.Forms.TabPage videoFrameTabPage;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.TabPage audioFrameTabPage;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.TextBox bFrameCountTextBox;
        private System.Windows.Forms.Label bFrameCountLabel;
        private System.Windows.Forms.TextBox pFrameCountTextBox;
        private System.Windows.Forms.Label pFrameCountLabel;
        private System.Windows.Forms.TextBox iFrameCountTextBox;
        private System.Windows.Forms.Label iFrameCountLabel;
        private System.Windows.Forms.TextBox frameSizeTextBox;
        private System.Windows.Forms.Label frameSizeLabel;
        private System.Windows.Forms.TextBox frameTypeTextBox;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Label frameTypeLabel;
    }
}

