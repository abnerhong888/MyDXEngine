using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Drawing.Text;
using System.Drawing.Imaging;
using System.Text.RegularExpressions;
namespace FontTool
{
   
    public partial class FontToolForm : Form
    {
        string ChoiceFont = "";
        int FontSize = 12;
        int mWidth = 1024;
        int mHeight = 1024;
        bool mLoadFileContent = false;
        string[] defaultString;
        PictureBox PB = new PictureBox();
        Bitmap bitmap = null;
        FontEdit mFontEdit = new FontEdit();
        bool mRTBChangeFlag = false;
        public FontToolForm()
        {
            InitializeComponent();
            SystemFontEmunrator();
            bitmap = new Bitmap(mWidth, mHeight, PixelFormat.Format32bppArgb);
            
            NUD_FontSize.Value = FontSize;
            LB_BackgroundColor.BackColor = Color.Black;
            panel1.Controls.Add(PB);
            TB_Width.Text = mWidth.ToString();
            TB_Height.Text = mHeight.ToString();

            PB.BackColor = Color.Black;
            PB.ForeColor = Color.White;
            PB.Width = mWidth;
            PB.Height = mHeight;
            PB.Paint += pictureBox1_Paint;
            CreateDefaultString();

        }

        void SystemFontEmunrator()
        {
            FontFamily[] l_fontFamilies;
            InstalledFontCollection installedFontCollection = new InstalledFontCollection();
            l_fontFamilies = installedFontCollection.Families;
            int ArialIdx = 0, cnt = 0;
            foreach (FontFamily Font in l_fontFamilies)
            {
                Label label = new Label();
                label.BackColor = Color.White;
                label.Width = FLP.Width - 25;
                label.Text = Font.Name;
                label.Click += LabelClickEvent;
                FLP.Controls.Add(label);
                if (Font.Name == "Arial")
                {
                    ArialIdx = cnt;
                }
                cnt++;
            }

            FLP.Controls[ArialIdx].BackColor = Color.CornflowerBlue;
            ChoiceFont = FLP.Controls[ArialIdx].Text;
            PB.Font = new Font(ChoiceFont, FontSize);
        }
        void LabelClickEvent(object sender, EventArgs e)
        {
            Label clicklabel = (Label)sender;

            foreach (Control ctl in FLP.Controls)
            {
                ctl.BackColor = Color.White;
            }
            clicklabel.BackColor = Color.CornflowerBlue;
            ChoiceFont = clicklabel.Text;
            PB.Font = new Font(ChoiceFont, FontSize);
        }

        private void NUD_FontSize_ValueChanged(object sender, EventArgs e)
        {
            FontSize = (int)NUD_FontSize.Value;
            PB.Font = new Font(ChoiceFont, FontSize);
        }
        
        private void LB_BackgroundColor_Click(object sender, EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                LB_BackgroundColor.BackColor = colorDialog1.Color;
                PB.BackColor = colorDialog1.Color;
            }
        }

        void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawString(RTB.Text, PB.Font, Brushes.White, new Point(0, 0));
        }

        private void RTB_TextChanged(object sender, EventArgs e)
        {
            if (mRTBChangeFlag) return;
            this.Refresh();
        }

        private void Btn_def_Click(object sender, EventArgs e)
        {
            mRTBChangeFlag = true;
            RTB.Text = defaultString[0] + "\n";
            RTB.Text += defaultString[1] + "\n";
            RTB.Text += defaultString[2] + "\n";
            RTB.Text += defaultString[3];
            this.Refresh();
            mRTBChangeFlag = false;
            mLoadFileContent = false;
        }
        private void Btn_clr_Click(object sender, EventArgs e)
        {
            RTB.Text = "";
            mLoadFileContent = false;
            TB_FilePath.Clear();
        }
        private void Btn_Save_Click(object sender, EventArgs e)
        {
            if(bitmap.Width != mWidth || bitmap.Height != mHeight)
            {
                bitmap.Dispose();
                bitmap = null;
                bitmap = new Bitmap(mWidth, mHeight, PixelFormat.Format32bppArgb);
            }
            if(bitmap != null)
            {
                PB.DrawToBitmap(bitmap, PB.ClientRectangle);
                string BmpName = ChoiceFont + FontSize.ToString() + ".bmp";
                bitmap.Save(@BmpName, ImageFormat.Bmp);
                
            }

            string wholeString;
            using (System.IO.StreamReader file = new System.IO.StreamReader(@"tempfile.tmp"))
            {
                wholeString = file.ReadToEnd();
            }

            string[] lines = wholeString.Split('\n');
            lines[0] = ChoiceFont + FontSize.ToString() + ".bmp";
            lines[3] = "FontSize=" + FontSize.ToString();
            lines[4] = "Face=" + ChoiceFont;
            string FontName = ChoiceFont + FontSize.ToString() + ".font";
            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@FontName))
            {
                foreach (string line in lines)
                {
                    string TrimedStr = Regex.Replace(line, @"\r", "");
                    file.WriteLine(TrimedStr);
                }
            }
            MessageBox.Show("Save Finish !");
        }

        private void TB_Width_KeyUp(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Enter)
            {
                mWidth = int.Parse(TB_Width.Text);
                PB.Width = mWidth;
            }
        }

        private void TB_Height_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                mHeight = int.Parse(TB_Height.Text);
                PB.Height = mHeight;
            }
        }

        private void Btn_Edit_Click(object sender, EventArgs e)
        {
            bool result = mFontEdit.UpdateContent(PB, RTB.Text, mLoadFileContent);
            if(result)
                mFontEdit.ShowDialog();
        }

        private void Btn_LoadFile_Click(object sender, EventArgs e)
        {
            var fileContent = string.Empty;
            var filePath = string.Empty;
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = ".\\";
                openFileDialog.Filter = "font files (*.font)|*.font|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 1;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    filePath = openFileDialog.FileName;
                    var fileStream = openFileDialog.OpenFile();
                    using (System.IO.StreamReader reader = new System.IO.StreamReader(fileStream))
                    {
                        fileContent = reader.ReadToEnd();
                    }
                }
            }
            TB_FilePath.Text = filePath;
            mRTBChangeFlag = true;
            string[] lines = fileContent.Split('\n');
            RTB.Text = "";
            string NextLineString = "";
            int cnt = 0;
            bool OtherWordFlag = false;
            foreach (string line in lines)
            {
                string TrimedStr = Regex.Replace(line, @"\r", "");
                string[] tmp;
                tmp = TrimedStr.Split(',');
                if (tmp.Length == 1)
                {
                    if (tmp[0].Contains(".bmp")) {/*PB.Image = Image.FromFile(tmp[0]);*/}
                    if (tmp[0].Contains("ImageW="))
                    {
                        string[] value = tmp[0].Split('=');
                        TB_Width.Text = value[1];
                        PB.Width = mWidth = int.Parse(TB_Width.Text);
                    }
                    if (tmp[0].Contains("ImageH="))
                    {
                        string[] value = tmp[0].Split('=');
                        TB_Height.Text = value[1];
                        PB.Height = mHeight = int.Parse(TB_Height.Text);
                    }
                    if (tmp[0].Contains("FontSize="))
                    {
                        string[] value = tmp[0].Split('=');
                        NUD_FontSize.Value = int.Parse(value[1]);
                    }
                    if (tmp[0].Contains("Face="))
                    {
                        string[] value = tmp[0].Split('=');
                        ChoiceFont = value[1];
                        LabelChoice(ChoiceFont);
                    }
                }

                if (tmp.Length == 5)
                {
                    if(ushort.Parse(tmp[0]) < 256)
                    {
                        RTB.Text += Char.ConvertFromUtf32(ushort.Parse(tmp[0])) + " ";
                        NextLineString += Char.ConvertFromUtf32(ushort.Parse(tmp[0])) + " ";
                    }
                    else
                    {
                        if(!OtherWordFlag)
                        {
                            RTB.Text += "\n";
                            OtherWordFlag = true;
                        } 
                        RTB.Text += Char.ConvertFromUtf32(ushort.Parse(tmp[0]));
                        NextLineString += Char.ConvertFromUtf32(ushort.Parse(tmp[0]));
                    }
                   
                    
                    if (NextLineString.Contains(defaultString[cnt]))
                    {
                        RTB.Text += "\n";
                        NextLineString = "";
                        if (cnt < 3)
                        {
                            cnt++;
                        }
                        
                    }
                }
            }
            mRTBChangeFlag = false;
            mFontEdit.UpdateFileContent(fileContent);
            mLoadFileContent = true;
            this.Refresh();
        }
        void LabelChoice(string pName)
        {
            foreach (Control ctl in FLP.Controls)
            {
                ctl.BackColor = Color.White;
                if (ctl.Text == pName)
                {
                    ctl.BackColor = Color.CornflowerBlue;
                }
                
            }
            PB.Font = new Font(ChoiceFont, FontSize);
        }
        void CreateDefaultString()
        {
            // 95 words include space, 
            // three space will generate a space
            defaultString = new string[4];
            defaultString[0] = "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z";
            defaultString[1] = "a b c d e f g h i j k l m n o p q r s t u v w x y z";
            defaultString[2] = "1 2 3 4 5 6 7 8 9 0";
            defaultString[3] = "\" ! ` ? ' . , ; : ( ) [ ] { } < > | / @ \\ ^ $ - % + = # _ & ~ *   ";
        }
    }
}
