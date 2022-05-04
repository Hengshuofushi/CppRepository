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
    class FrameInfo
    {
        private int frameSeq;
        private string frameType;

        public FrameInfo(int seq, string type)
        {
            FrameSeq = seq;
            FrameType = type;
        }

        public int FrameSeq
        {
            set { frameSeq = value; }
            get { return frameSeq; }
        }
        public string FrameType
        {
            set { frameType = value; }
            get { return frameType; }
        }
    }
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
            byte[] buff = new byte[2048];

            while (true)
            {
                int rcount = fs.Read(buff, 0, buff.Length);
                if (rcount <= 0)
                {
                    break;
                }
                // TODO: parse ps stream
                string hex = ConvertHexString(buff, rcount);
                hexRichTextBox.Text = hex;
            }
        }

        private string ConvertHexString(byte[] bytes, int len)
        {
            StringBuilder builder = new StringBuilder();
            int size = bytes.Length > len ? len : bytes.Length;
            for (int i = 1; i < size; i++)
            {
                builder.Append(string.Format("{0:X2}", bytes[i])).Append(" ");
            }
            return builder.ToString().Trim();
        }
    }
}
