using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void chooseFileButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.AddExtension = true;
            dialog.RestoreDirectory = true;
            DialogResult dialogResult = dialog.ShowDialog();
            if (dialogResult == DialogResult.OK)
            {
                string filePath = dialog.FileName;
                string fileName = filePath.Substring(filePath.LastIndexOf("\\") + 1);
                fileNameTextBox.Text = filePath;
                FileStream fs = (FileStream)dialog.OpenFile();
                parseMediaStream(fs);
            }
        }

        private void parseMediaStream(FileStream fs)
        {
            // TODO: parse media stream
        }
    }
}
