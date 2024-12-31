using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace FontTool
{
    public partial class Padding : UserControl
    {
        cFontRect mRect;
        public bool updateflag = false;
        public Padding()
        {
            InitializeComponent();
        }
        public string GBText
        {
            get { return groupBox1.Text; }
            set { groupBox1.Text = value; }
        }
        public void UpdateRect(ref cFontRect pRect)
        {
            if(pRect.width <0)
            {
                pRect.x += pRect.width;
                pRect.width = Math.Abs(pRect.width);
            }
            if (pRect.height < 0)
            {
                pRect.y += pRect.height;
                pRect.height = Math.Abs(pRect.height);
            }
            if (pRect.x < 0)
            {
                pRect.width += pRect.x;
                pRect.x = 0;
            }
            if (pRect.y < 0)
            {
                pRect.height += pRect.y;
                pRect.y = 0;
            }
            mRect = pRect;

            updateflag = true;
            NUDX.Value = mRect.x;
            NUDY.Value = mRect.y;
            NUDW.Value = mRect.width;
            NUDH.Value = mRect.height;
            updateflag = false;
        }
        
        [Browsable(true)]
        [Category("Action")]
        [Description("Invoked when user clicks button")]
        public event EventHandler ValueChangeEvent;

       
        private void NUDX_ValueChanged(object sender, EventArgs e)
        {
            if (updateflag) return;

            NumericUpDown l_NUD = (NumericUpDown)sender;
            mRect.x = (int)l_NUD.Value;
            ValueChangeEvent?.Invoke(this, e);
        }

        private void NUDY_ValueChanged(object sender, EventArgs e)
        {
            if (updateflag) return;
            NumericUpDown l_NUD = (NumericUpDown)sender;
            mRect.y = (int)l_NUD.Value;
            ValueChangeEvent?.Invoke(this, e);
        }

        private void NUDW_ValueChanged(object sender, EventArgs e)
        {
            if (updateflag) return;
            NumericUpDown l_NUD = (NumericUpDown)sender;
            mRect.width = (int)l_NUD.Value;
            ValueChangeEvent?.Invoke(this, e);
        }

        private void NUDH_ValueChanged(object sender, EventArgs e)
        {
            if (updateflag) return;
            NumericUpDown l_NUD = (NumericUpDown)sender;
            mRect.height = (int)l_NUD.Value;
            ValueChangeEvent?.Invoke(this, e);
        }
    }
}
