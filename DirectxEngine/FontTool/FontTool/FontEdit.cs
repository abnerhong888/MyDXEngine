using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Drawing.Imaging;
using System.Text.RegularExpressions;
using System.Windows;

namespace FontTool
{
    public partial class FontEdit : Form
    {
        PictureBox mPB = new PictureBox();
        Bitmap bitmap = null;
        Pen RectPen = new Pen(Color.Red, 1);
        cFontRect mPaintFontRect;
        string[] mStrRows;
        Dictionary<ushort, cFontRect> mDictChar = new Dictionary<ushort, cFontRect>();

        Dictionary<ushort, cFontRect>[] mDicFast = null;
        cFontRect[] mRowsFRect;
        int mRowidx = 0;
        bool RowsBtnFlag = false;
        bool EachWordFLP2Flag = false;
        bool EachWordFLP3Flag = false;
        bool FastGenerateFlag = false;
        List<cFontRect> mFontRectList = new List<cFontRect>();
        ushort labelClickKeyFLP2;
        ushort labelClickKeyFLP3;
        bool FLP3Edit = false;
        bool mPaintFlag = false;
        bool mMouseHold = false;
        public string mSaveString = "";

        string mFileContent = "";
        bool mDefaultFileFlag = false;
        bool mTmpFileSaveFlag = false;
        Label FLP3ClickLabel;
        Label FLP3ClickLabelPre;
        public FontEdit()
        {
            InitializeComponent();
            panel1.Controls.Add(mPB);
            mPB.Paint += pictureBox1_Paint;
            mPB.MouseDown += pictureBox1_MouseDown;
            mPB.MouseUp += pictureBox1_MouseUp;
            mPB.MouseMove += pictureBox1_MouseMove;
            paddingEachWord.ValueChangeEvent += new EventHandler(paddingEachWord_ValueChangeEvent);
            paddingMouseRect.ValueChangeEvent += new EventHandler(paddingMouseRect_ValueChangeEvent);
        }
        public bool UpdateContent(PictureBox pPB, string pRTBstr, bool pDefaultFile)
        {
            mPB.Width = pPB.Width;
            mPB.Height = pPB.Width;
            mDefaultFileFlag = false;
            LB_Info.Text = "Info : " + pPB.Width.ToString() + " x " + pPB.Height.ToString();
            if (bitmap != null)
            {
                bitmap.Dispose();
                bitmap = null;
            }
            bitmap = new Bitmap(mPB.Width, mPB.Height, PixelFormat.Format32bppArgb);
            pPB.DrawToBitmap(bitmap, mPB.ClientRectangle);
            mPB.Image = bitmap;
            mStrRows = pRTBstr.Split('\n');
            mDictChar.Clear();
            FLP.Controls.Clear();
            
            mDicFast = new Dictionary<ushort, cFontRect>[mStrRows.Length];
            mRowsFRect = new cFontRect[mStrRows.Length];

            for (int i=0;i< mStrRows.Length;i++)
            {
                string TrimedStr = Regex.Replace(mStrRows[i], @" ", "");
                mDicFast[i] = new Dictionary<ushort, cFontRect>();
                int col = 0;
                foreach (ushort c in TrimedStr)
                {
                    try
                    {
                        mDictChar.Add(c, new cFontRect());
                        mDicFast[i].Add(c, new cFontRect());
                        col++;
                    }
                    catch(Exception e)
                    {
                        string str = "'" + Char.ConvertFromUtf32(c) + "' ";
                        str += "at Row " + i.ToString() + " Column " + col.ToString();
                        DialogResult result = MessageBox.Show(
                            str + "\nSame word ? Be careful !\nDo you wanna continue?", 
                            "Warning", 
                            MessageBoxButtons.YesNo, 
                            MessageBoxIcon.Warning);
                        if(result == DialogResult.No)
                        {
                            return false;
                        }
                    }
                    
                }
                if (mStrRows[i].Contains("   "))
                {
                    mDictChar.Add(Convert.ToUInt16(' '), new cFontRect());
                    mDicFast[i].Add(Convert.ToUInt16(' '), new cFontRect());
                }

                Button btn = new Button();
                btn.Width = FLP.Width - 8;
                btn.Text = "Row" + i.ToString();
                btn.Click += btn_click;
                FLP.Controls.Add(btn);
                mRowsFRect[i] = new cFontRect(0, 0, 10 + i * 10, 10 + i * 10);
            }

            UpdateFLP3();

            if(pDefaultFile)
            {
                if (mTmpFileSaveFlag)
                {
                    mTmpFileSaveFlag = false;
                    var fileContent = string.Empty;
                    var filePath = ".\\tempfile.tmp";
                    using (System.IO.StreamReader reader = new System.IO.StreamReader(filePath))
                    {
                        fileContent = reader.ReadToEnd();
                    }
                    UpdateFileContent(fileContent);
                }

                LoadFileFont();
                mDefaultFileFlag = true;
                
                
            }
            
            return true;
        }
        void btn_click(object sender, EventArgs e)
        {
            mPaintFlag = false;
            this.Refresh();
            Button btn = (Button)sender;
            string idx = Regex.Replace(btn.Text, @"Row", "");
            mRowidx = int.Parse(idx);
            mPaintFontRect = mRowsFRect[mRowidx];
            mPaintFlag = true;
            this.Refresh();
            RowsBtnFlag = true;
            EachWordFLP2Flag = false;
            EachWordFLP3Flag = false;
            FLP2.Controls.Clear();
            FLP3Edit = false;
            FLP3ClearColor();
            paddingMouseRect.UpdateRect(ref mPaintFontRect);
            Btn_FastSaveRow.Text = "SaveRow" + idx;

            if (mDefaultFileFlag)
            {
                RowsBtnFlag = false;
                FLP2.Controls.Clear();
                mFontRectList.Clear();
                Dictionary<ushort, cFontRect> l_DicFast = new Dictionary<ushort, cFontRect>(mDicFast[mRowidx]);
                
                foreach (KeyValuePair<ushort, cFontRect> entry in l_DicFast)
                {
                    if(mDictChar.ContainsKey(entry.Key))
                    {
                        mDicFast[mRowidx][entry.Key] = mDictChar[entry.Key];
                    }
                    Label label = new Label();
                    label.BackColor = Color.White;
                    label.Width = FLP.Width - 25;
                    string str = Char.ConvertFromUtf32(entry.Key);
                    label.Text = str + "(" + entry.Key.ToString() + ")";
                    label.Click += FLP2LabelClickEvent;
                    FLP2.Controls.Add(label);
                    mFontRectList.Add(mDicFast[mRowidx][entry.Key]);
                }
            }
            
        }
        void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            if(mPaintFlag)
            {
                e.Graphics.DrawLines(RectPen, mPaintFontRect.getDrawRect());
            }
            if(FastGenerateFlag)
            {
                foreach(cFontRect Rect in mFontRectList)
                {
                    e.Graphics.DrawLines(RectPen, Rect.getDrawRect());
                }
                FastGenerateFlag = false;
            }
           
        }
        void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if(RowsBtnFlag)
            {
                if (e.Button != MouseButtons.Middle)
                    mRowsFRect[mRowidx].x = e.X;
                if (e.Button != MouseButtons.Right)
                    mRowsFRect[mRowidx].y = e.Y;
                mMouseHold = true;
            }

            if(EachWordFLP2Flag)
            {
                if (e.Button != MouseButtons.Middle)
                    mDicFast[mRowidx][labelClickKeyFLP2].x = e.X;
                if (e.Button != MouseButtons.Right)
                    mDicFast[mRowidx][labelClickKeyFLP2].y = e.Y;
                mMouseHold = true;
            }
            
            if(EachWordFLP3Flag)
            {
                if (e.Button != MouseButtons.Middle)
                    mDictChar[labelClickKeyFLP3].x = e.X;
                if(e.Button != MouseButtons.Right)
                    mDictChar[labelClickKeyFLP3].y = e.Y;
                
                
                mMouseHold = true;
            }
        }
        void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            if (RowsBtnFlag)
            {
                mMouseHold = false;
                paddingMouseRect.UpdateRect(ref mPaintFontRect);
                this.Refresh();
            }
            if(EachWordFLP2Flag || EachWordFLP3Flag)
            {
                mMouseHold = false;
                paddingEachWord.UpdateRect(ref mPaintFontRect);
                this.Refresh();
            }

            if (EachWordFLP3Flag)
            {
                mMouseHold = false;
                paddingEachWord.UpdateRect(ref mPaintFontRect);
                UpdateSingleFLP3();
                this.Refresh();
            }

           
        }
        void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if(mMouseHold && RowsBtnFlag)
            {
                if (e.Button != MouseButtons.Middle)
                    mRowsFRect[mRowidx].width = e.X - mRowsFRect[mRowidx].x;
                if (e.Button != MouseButtons.Right)
                    mRowsFRect[mRowidx].height = e.Y - mRowsFRect[mRowidx].y;
                this.Refresh();
            }

            if (mMouseHold && EachWordFLP2Flag)
            {
                if (e.Button != MouseButtons.Middle)
                    mDicFast[mRowidx][labelClickKeyFLP2].width = e.X - mDicFast[mRowidx][labelClickKeyFLP2].x;
                if (e.Button != MouseButtons.Right)
                    mDicFast[mRowidx][labelClickKeyFLP2].height = e.Y - mDicFast[mRowidx][labelClickKeyFLP2].y;
                this.Refresh();
            }
            if (mMouseHold && EachWordFLP3Flag)
            {
                if (e.Button != MouseButtons.Middle)
                    mDictChar[labelClickKeyFLP3].width = e.X - mDictChar[labelClickKeyFLP3].x;
                if (e.Button != MouseButtons.Right)
                    mDictChar[labelClickKeyFLP3].height = e.Y - mDictChar[labelClickKeyFLP3].y;
                this.Refresh();
            }
        }
        
        private void UpdateRectListDraw()
        {
            mFontRectList.Clear();
            mPaintFlag = false;
            this.Refresh();
            int avgW = mRowsFRect[mRowidx].width / mDicFast[mRowidx].Count;
            int height = mRowsFRect[mRowidx].height;
            int i = 0;
            foreach (KeyValuePair<ushort, cFontRect> entry in mDicFast[mRowidx])
            {
                mDicFast[mRowidx][entry.Key].x = mRowsFRect[mRowidx].x + avgW * i;
                mDicFast[mRowidx][entry.Key].y = mRowsFRect[mRowidx].y;
                mDicFast[mRowidx][entry.Key].width = avgW;
                mDicFast[mRowidx][entry.Key].height = height;// mRowsFRect[mRowidx].height;
                i++;
                mFontRectList.Add(mDicFast[mRowidx][entry.Key]);
            }
            FastGenerateFlag = true;
            this.Refresh();
            
        }
        private void BTN_FastGenerate_Click(object sender, EventArgs e)
        {
            if(RowsBtnFlag)
            {
                UpdateRectListDraw();
                RowsBtnFlag = false;

                FLP2.Controls.Clear();
                foreach (KeyValuePair<ushort, cFontRect> entry in mDicFast[mRowidx])
                {
                    Label label = new Label();
                    label.BackColor = Color.White;
                    label.Width = FLP.Width - 25;
                    string str = Char.ConvertFromUtf32(entry.Key);
                    label.Text = str + "(" + entry.Key.ToString() + ")";
                    label.Click += FLP2LabelClickEvent;
                    FLP2.Controls.Add(label);
                }

            }
            
        }
        void FLP2LabelClickEvent(object sender, EventArgs e)
        {
            Label clicklabel = (Label)sender;

            foreach (Control ctl in FLP2.Controls)
            {
                ctl.BackColor = Color.White;
            }
            clicklabel.BackColor = Color.CornflowerBlue;
            char[] key = clicklabel.Text.ToCharArray();
            labelClickKeyFLP2 = Convert.ToUInt16(key[0]);
            mPaintFlag = false;
            this.Refresh();
            mPaintFontRect = mDicFast[mRowidx][labelClickKeyFLP2];
            paddingEachWord.UpdateRect(ref mPaintFontRect);
            mPaintFlag = true;
            this.Refresh();
            FLP3Edit = false;
            FLP3ClearColor();
            EachWordFLP2Flag = true;
            RowsBtnFlag = false;
            EachWordFLP3Flag = false;
        }
        void UpdateFLP3()
        {
            FLP3.Controls.Clear();
            foreach (KeyValuePair<ushort, cFontRect> entry in mDictChar)
            {
                Label label = new Label();
                label.BackColor = Color.White;
                label.Width = FLP3.Width - 25;
                
                string str = Char.ConvertFromUtf32(entry.Key);
                label.Text = str + "(" + entry.Key.ToString() + ") ";
                label.Text += "(" + entry.Value.x.ToString() + ", ";
                label.Text += entry.Value.y.ToString() + ", ";
                label.Text += entry.Value.width.ToString() + ", ";
                label.Text += entry.Value.height.ToString() + ")";
                label.Click += FLP3LabelClickEvent;
                FLP3.Controls.Add(label);
            }
            
        }
        void UpdateSingleFLP3()
        {
            int i = 0;
            foreach (KeyValuePair<ushort, cFontRect> entry in mDictChar)
            {
                if (entry.Key == labelClickKeyFLP3)
                {
                    FLP3.Controls[i].BackColor = Color.CornflowerBlue;
                    string str = Char.ConvertFromUtf32(entry.Key);
                    FLP3.Controls[i].Text = str + "(" + entry.Key.ToString() + ") ";
                    FLP3.Controls[i].Text += "(" + entry.Value.x.ToString() + ", ";
                    FLP3.Controls[i].Text += entry.Value.y.ToString() + ", ";
                    FLP3.Controls[i].Text += entry.Value.width.ToString() + ", ";
                    FLP3.Controls[i].Text += entry.Value.height.ToString() + ")";
                    break;
                }
                i++;
            }
            
        }
        void FLP3ClearColor()
        {
            if(FLP3ClickLabel != null)
            {
                FLP3ClickLabel.BackColor = Color.White;
                FLP3ClickLabel = null;
            }
        }
        void FLP3LabelClickEvent(object sender, EventArgs e)
        {
            Label clicklabel = (Label)sender;

            if(FLP3ClickLabel == null)
            {
                FLP3ClickLabel = clicklabel;
                FLP3ClickLabel.BackColor = Color.CornflowerBlue;
            }
            else if(FLP3ClickLabelPre != FLP3ClickLabel)
            {
                FLP3ClickLabelPre = FLP3ClickLabel;
                FLP3ClickLabelPre.BackColor = Color.White;
                FLP3ClickLabel = clicklabel;
                FLP3ClickLabel.BackColor = Color.CornflowerBlue;
            }
            
            
            char[] key = clicklabel.Text.ToCharArray();
            labelClickKeyFLP3 = Convert.ToUInt16(key[0]);
            mPaintFlag = false;
            this.Refresh();
            mPaintFontRect = mDictChar[labelClickKeyFLP3];
            paddingEachWord.UpdateRect(ref mPaintFontRect);
            mPaintFlag = true;
            this.Refresh();
            FLP3Edit = true;
            FLP2.Controls.Clear();
            RowsBtnFlag = false;
            EachWordFLP2Flag = false;
            EachWordFLP3Flag = true;
        }
        private void Btn_FastShowAll_Click(object sender, EventArgs e)
        {
            foreach (Control ctl in FLP2.Controls)
            {
                ctl.BackColor = Color.White;
            }
            mPaintFlag = false ;
            this.Refresh();
            FastGenerateFlag = true;
            this.Refresh();
            EachWordFLP2Flag = false;
            EachWordFLP3Flag = false;
        }
        
        protected void paddingEachWord_ValueChangeEvent(object sender, EventArgs e)
        {
            if (paddingEachWord.updateflag) return;
            
            if(FLP3Edit)
            {
                UpdateSingleFLP3();
            }
            mPaintFlag = false;
            this.Refresh();
            mPaintFlag = true;
            this.Refresh();
        }
        protected void paddingMouseRect_ValueChangeEvent(object sender, EventArgs e)
        {
            if (paddingMouseRect.updateflag) return;
            mPaintFlag = false;
            this.Refresh();
            mPaintFlag = true;
            this.Refresh();
        }

        private void Btn_FastSaveRow_Click(object sender, EventArgs e)
        {
            foreach (KeyValuePair<ushort, cFontRect> entry in mDicFast[mRowidx])
            {
                mDictChar[entry.Key] = entry.Value;
            }
            UpdateFLP3();
            EachWordFLP2Flag = false;
            EachWordFLP3Flag = false;
        }
       
        private void Btn_ShowAll_Click(object sender, EventArgs e)
        {
            mFontRectList.Clear();
            mPaintFlag = false;
            this.Refresh();
            FLP3ClearColor();
            foreach (KeyValuePair<ushort, cFontRect> entry in mDictChar)
            {
                mFontRectList.Add(entry.Value);
            }
            FastGenerateFlag = true;
            this.Refresh();
            FLP3Edit = false;
            RowsBtnFlag = false;
            EachWordFLP2Flag = false;
            EachWordFLP3Flag = false;
        }

        private void Btn_Save_Click(object sender, EventArgs e)
        {
            mSaveString = "";
            mSaveString = "123.bmp\n";
            mSaveString += "ImageW=" + mPB.Width.ToString() + "\n";
            mSaveString += "ImageH=" + mPB.Height.ToString() + "\n";
            mSaveString += "FontSize=\n";
            mSaveString += "Face=\n";
            foreach (KeyValuePair<ushort, cFontRect> entry in mDictChar)
            {
                mSaveString += entry.Key.ToString() + ",";
                mSaveString += entry.Value.x.ToString() + ",";
                mSaveString += entry.Value.y.ToString() + ",";
                mSaveString += entry.Value.width.ToString() + ",";
                mSaveString += entry.Value.height.ToString() + "\n";
            }
            using (System.IO.StreamWriter file =
            new System.IO.StreamWriter(@"tempfile.tmp"))
            {
                string[] lines = mSaveString.Split('\n');
                foreach (string line in lines)
                {
                   file.WriteLine(line);
                }
            }
            mTmpFileSaveFlag = true;
        }
        public void UpdateFileContent(string pFileContent)
        {
            mFileContent = pFileContent;
        }

        private void LoadFileFont()
        {
            var fileContent = mFileContent;
            
            string[] lines = fileContent.Split('\n');
            mDictChar.Clear();
            foreach (string line in lines)
            {
                string TrimedStr = Regex.Replace(line, @"\r", "");
                string[] tmp = TrimedStr.Split(',');
                if (tmp.Length == 5)
                {
                    ushort first = ushort.Parse(tmp[0]);
                    int x = int.Parse(tmp[1]);
                    int y = int.Parse(tmp[2]);
                    int w = int.Parse(tmp[3]);
                    int h = int.Parse(tmp[4]);
                    mDictChar.Add(first, new cFontRect(x, y, w, h));
                }
            }
            UpdateFLP3();

        }
        private void Btn_LoadTmp_Click(object sender, EventArgs e)
        {
            var fileContent = string.Empty;
            var filePath = string.Empty;
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = ".\\";
                openFileDialog.Filter = "tmp files (*.tmp)|*.tmp|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    //Get the path of specified file
                    filePath = openFileDialog.FileName;

                    //Read the contents of the file into a stream
                    var fileStream = openFileDialog.OpenFile();

                    using (System.IO.StreamReader reader = new System.IO.StreamReader(fileStream))
                    {
                        fileContent = reader.ReadToEnd();
                    }
                }
            }
           
            string[] lines = fileContent.Split('\n');
            mDictChar.Clear();
            foreach (string line in lines)
            {
                string TrimedStr = Regex.Replace(line, @"\r", "");
                string[] tmp = TrimedStr.Split(',');
                if(tmp.Length == 5)
                {
                    ushort first = ushort.Parse(tmp[0]);
                    int x = int.Parse(tmp[1]);
                    int y = int.Parse(tmp[2]);
                    int w = int.Parse(tmp[3]);
                    int h = int.Parse(tmp[4]);
                    mDictChar.Add(first, new cFontRect(x, y, w, h));
                }
            }
            UpdateFLP3();
        }
        
    }
}
