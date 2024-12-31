namespace FontTool
{
    partial class Padding
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.NUDX = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.NUDY = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.NUDW = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.NUDH = new System.Windows.Forms.NumericUpDown();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.NUDX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.NUDY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.NUDW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.NUDH)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // NUDX
            // 
            this.NUDX.Font = new System.Drawing.Font("PMingLiU", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.NUDX.Location = new System.Drawing.Point(26, 21);
            this.NUDX.Maximum = new decimal(new int[] {
            65536,
            0,
            0,
            0});
            this.NUDX.Name = "NUDX";
            this.NUDX.Size = new System.Drawing.Size(56, 23);
            this.NUDX.TabIndex = 0;
            this.NUDX.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.NUDX.ValueChanged += new System.EventHandler(this.NUDX_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(4, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(16, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "X:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(93, 21);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(16, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "Y:";
            // 
            // NUDY
            // 
            this.NUDY.Font = new System.Drawing.Font("PMingLiU", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.NUDY.Location = new System.Drawing.Point(115, 21);
            this.NUDY.Maximum = new decimal(new int[] {
            65536,
            0,
            0,
            0});
            this.NUDY.Name = "NUDY";
            this.NUDY.Size = new System.Drawing.Size(56, 23);
            this.NUDY.TabIndex = 2;
            this.NUDY.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.NUDY.ValueChanged += new System.EventHandler(this.NUDY_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(4, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(19, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "W:";
            // 
            // NUDW
            // 
            this.NUDW.Font = new System.Drawing.Font("PMingLiU", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.NUDW.Location = new System.Drawing.Point(26, 49);
            this.NUDW.Maximum = new decimal(new int[] {
            65536,
            0,
            0,
            0});
            this.NUDW.Name = "NUDW";
            this.NUDW.Size = new System.Drawing.Size(56, 23);
            this.NUDW.TabIndex = 4;
            this.NUDW.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.NUDW.ValueChanged += new System.EventHandler(this.NUDW_ValueChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(93, 50);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(16, 12);
            this.label4.TabIndex = 7;
            this.label4.Text = "H:";
            // 
            // NUDH
            // 
            this.NUDH.Font = new System.Drawing.Font("PMingLiU", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.NUDH.Location = new System.Drawing.Point(115, 50);
            this.NUDH.Maximum = new decimal(new int[] {
            65536,
            0,
            0,
            0});
            this.NUDH.Name = "NUDH";
            this.NUDH.Size = new System.Drawing.Size(56, 23);
            this.NUDH.TabIndex = 6;
            this.NUDH.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.NUDH.ValueChanged += new System.EventHandler(this.NUDH_ValueChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.NUDW);
            this.groupBox1.Controls.Add(this.NUDX);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.NUDY);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.NUDH);
            this.groupBox1.Location = new System.Drawing.Point(3, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(183, 89);
            this.groupBox1.TabIndex = 12;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Padding";
            // 
            // Padding
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBox1);
            this.Name = "Padding";
            this.Size = new System.Drawing.Size(192, 96);
            ((System.ComponentModel.ISupportInitialize)(this.NUDX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.NUDY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.NUDW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.NUDH)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NumericUpDown NUDX;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown NUDY;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown NUDW;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown NUDH;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}
