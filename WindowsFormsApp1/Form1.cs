using System;
using System.IO;
using System.Text;
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
                fs.Close();
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
