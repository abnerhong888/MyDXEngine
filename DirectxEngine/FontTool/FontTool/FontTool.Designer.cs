namespace FontTool
{
    partial class FontToolForm
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.NUD_FontSize = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.FLP = new System.Windows.Forms.FlowLayoutPanel();
            this.RTB = new System.Windows.Forms.RichTextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.Btn_clr = new System.Windows.Forms.Button();
            this.Btn_def = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.Btn_Edit = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.TB_Height = new System.Windows.Forms.TextBox();
            this.TB_Width = new System.Windows.Forms.TextBox();
            this.Btn_Save = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.LB_BackgroundColor = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.label7 = new System.Windows.Forms.Label();
            this.TB_FilePath = new System.Windows.Forms.TextBox();
            this.Btn_LoadFile = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NUD_FontSize)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.Btn_LoadFile);
            this.groupBox1.Controls.Add(this.TB_FilePath);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.NUD_FontSize);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.FLP);
            this.groupBox1.Location = new System.Drawing.Point(12, 40);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(322, 224);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Font";
            // 
            // NUD_FontSize
            // 
            this.NUD_FontSize.Location = new System.Drawing.Point(80, 124);
            this.NUD_FontSize.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.NUD_FontSize.Name = "NUD_FontSize";
            this.NUD_FontSize.Size = new System.Drawing.Size(37, 22);
            this.NUD_FontSize.TabIndex = 3;
            this.NUD_FontSize.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.NUD_FontSize.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.NUD_FontSize.ValueChanged += new System.EventHandler(this.NUD_FontSize_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(31, 127);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(33, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "Size : ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(31, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "System : ";
            // 
            // FLP
            // 
            this.FLP.AutoScroll = true;
            this.FLP.BackColor = System.Drawing.Color.White;
            this.FLP.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FLP.Location = new System.Drawing.Point(80, 21);
            this.FLP.Name = "FLP";
            this.FLP.Size = new System.Drawing.Size(236, 88);
            this.FLP.TabIndex = 1;
            // 
            // RTB
            // 
            this.RTB.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.RTB.Font = new System.Drawing.Font("Arial Narrow", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RTB.Location = new System.Drawing.Point(6, 16);
            this.RTB.Name = "RTB";
            this.RTB.Size = new System.Drawing.Size(403, 174);
            this.RTB.TabIndex = 2;
            this.RTB.Text = "";
            this.RTB.TextChanged += new System.EventHandler(this.RTB_TextChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.Btn_clr);
            this.groupBox2.Controls.Add(this.Btn_def);
            this.groupBox2.Controls.Add(this.RTB);
            this.groupBox2.Location = new System.Drawing.Point(355, 40);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(415, 224);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Text";
            // 
            // Btn_clr
            // 
            this.Btn_clr.Location = new System.Drawing.Point(95, 196);
            this.Btn_clr.Name = "Btn_clr";
            this.Btn_clr.Size = new System.Drawing.Size(74, 21);
            this.Btn_clr.TabIndex = 4;
            this.Btn_clr.Text = "Clear";
            this.Btn_clr.UseVisualStyleBackColor = true;
            this.Btn_clr.Click += new System.EventHandler(this.Btn_clr_Click);
            // 
            // Btn_def
            // 
            this.Btn_def.Location = new System.Drawing.Point(6, 196);
            this.Btn_def.Name = "Btn_def";
            this.Btn_def.Size = new System.Drawing.Size(74, 21);
            this.Btn_def.TabIndex = 3;
            this.Btn_def.Text = "Default";
            this.Btn_def.UseVisualStyleBackColor = true;
            this.Btn_def.Click += new System.EventHandler(this.Btn_def_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.Btn_Edit);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.TB_Height);
            this.groupBox3.Controls.Add(this.TB_Width);
            this.groupBox3.Controls.Add(this.Btn_Save);
            this.groupBox3.Controls.Add(this.panel1);
            this.groupBox3.Controls.Add(this.LB_BackgroundColor);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Location = new System.Drawing.Point(12, 287);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(758, 364);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Rendering";
            // 
            // Btn_Edit
            // 
            this.Btn_Edit.Location = new System.Drawing.Point(526, 18);
            this.Btn_Edit.Name = "Btn_Edit";
            this.Btn_Edit.Size = new System.Drawing.Size(86, 31);
            this.Btn_Edit.TabIndex = 8;
            this.Btn_Edit.Text = "Edit";
            this.Btn_Edit.UseVisualStyleBackColor = true;
            this.Btn_Edit.Click += new System.EventHandler(this.Btn_Edit_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(279, 43);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(13, 12);
            this.label6.TabIndex = 7;
            this.label6.Text = "H";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(192, 43);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(16, 12);
            this.label5.TabIndex = 6;
            this.label5.Text = "W";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(237, 23);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(11, 12);
            this.label4.TabIndex = 5;
            this.label4.Text = "x";
            // 
            // TB_Height
            // 
            this.TB_Height.Location = new System.Drawing.Point(254, 18);
            this.TB_Height.Name = "TB_Height";
            this.TB_Height.Size = new System.Drawing.Size(62, 22);
            this.TB_Height.TabIndex = 5;
            this.TB_Height.Text = "Height";
            this.TB_Height.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.TB_Height.KeyUp += new System.Windows.Forms.KeyEventHandler(this.TB_Height_KeyUp);
            // 
            // TB_Width
            // 
            this.TB_Width.Location = new System.Drawing.Point(169, 18);
            this.TB_Width.Name = "TB_Width";
            this.TB_Width.Size = new System.Drawing.Size(62, 22);
            this.TB_Width.TabIndex = 4;
            this.TB_Width.Text = "Width";
            this.TB_Width.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.TB_Width.KeyUp += new System.Windows.Forms.KeyEventHandler(this.TB_Width_KeyUp);
            // 
            // Btn_Save
            // 
            this.Btn_Save.Location = new System.Drawing.Point(657, 18);
            this.Btn_Save.Name = "Btn_Save";
            this.Btn_Save.Size = new System.Drawing.Size(86, 31);
            this.Btn_Save.TabIndex = 3;
            this.Btn_Save.Text = "Save";
            this.Btn_Save.UseVisualStyleBackColor = true;
            this.Btn_Save.Click += new System.EventHandler(this.Btn_Save_Click);
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Location = new System.Drawing.Point(8, 64);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(735, 264);
            this.panel1.TabIndex = 2;
            // 
            // LB_BackgroundColor
            // 
            this.LB_BackgroundColor.BackColor = System.Drawing.Color.White;
            this.LB_BackgroundColor.Location = new System.Drawing.Point(78, 18);
            this.LB_BackgroundColor.Name = "LB_BackgroundColor";
            this.LB_BackgroundColor.Size = new System.Drawing.Size(53, 22);
            this.LB_BackgroundColor.TabIndex = 1;
            this.LB_BackgroundColor.Click += new System.EventHandler(this.LB_BackgroundColor_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 23);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(72, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "Background : ";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(31, 161);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(31, 12);
            this.label7.TabIndex = 5;
            this.label7.Text = "File : ";
            // 
            // TB_FilePath
            // 
            this.TB_FilePath.Location = new System.Drawing.Point(68, 158);
            this.TB_FilePath.Name = "TB_FilePath";
            this.TB_FilePath.Size = new System.Drawing.Size(224, 22);
            this.TB_FilePath.TabIndex = 6;
            // 
            // Btn_LoadFile
            // 
            this.Btn_LoadFile.Location = new System.Drawing.Point(292, 158);
            this.Btn_LoadFile.Name = "Btn_LoadFile";
            this.Btn_LoadFile.Size = new System.Drawing.Size(24, 21);
            this.Btn_LoadFile.TabIndex = 9;
            this.Btn_LoadFile.Text = "...";
            this.Btn_LoadFile.UseVisualStyleBackColor = true;
            this.Btn_LoadFile.Click += new System.EventHandler(this.Btn_LoadFile_Click);
            // 
            // FontToolForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(876, 698);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "FontToolForm";
            this.Text = "FontTool";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NUD_FontSize)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.FlowLayoutPanel FLP;
        private System.Windows.Forms.RichTextBox RTB;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown NUD_FontSize;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label LB_BackgroundColor;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button Btn_def;
        private System.Windows.Forms.Button Btn_Save;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox TB_Height;
        private System.Windows.Forms.TextBox TB_Width;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button Btn_clr;
        private System.Windows.Forms.Button Btn_Edit;
        private System.Windows.Forms.Button Btn_LoadFile;
        private System.Windows.Forms.TextBox TB_FilePath;
        private System.Windows.Forms.Label label7;
    }
}

