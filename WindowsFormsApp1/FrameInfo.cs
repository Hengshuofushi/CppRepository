using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
}
