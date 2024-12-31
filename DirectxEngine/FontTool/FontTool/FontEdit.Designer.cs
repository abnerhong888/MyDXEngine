namespace FontTool
{
    partial class FontEdit
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
            this.components = new System.ComponentModel.Container();
            this.panel1 = new System.Windows.Forms.Panel();
            this.LB_Info = new System.Windows.Forms.Label();
            this.FLP = new System.Windows.Forms.FlowLayoutPanel();
            this.BTN_FastGenerate = new System.Windows.Forms.Button();
            this.FLP2 = new System.Windows.Forms.FlowLayoutPanel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.Btn_FastSaveRow = new System.Windows.Forms.Button();
            this.Btn_FastShowAll = new System.Windows.Forms.Button();
            this.FLP3 = new System.Windows.Forms.FlowLayoutPanel();
            this.Btn_ShowAll = new System.Windows.Forms.Button();
            this.Btn_Save = new System.Windows.Forms.Button();
            this.paddingMouseRect = new FontTool.Padding();
            this.paddingEachWord = new FontTool.Padding();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.Btn_LoadTmp = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Location = new System.Drawing.Point(37, 34);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(763, 574);
            this.panel1.TabIndex = 0;
            // 
            // LB_Info
            // 
            this.LB_Info.Location = new System.Drawing.Point(35, 9);
            this.LB_Info.Name = "LB_Info";
            this.LB_Info.Size = new System.Drawing.Size(100, 23);
            this.LB_Info.TabIndex = 0;
            this.LB_Info.Text = "Info : ";
            this.LB_Info.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // FLP
            // 
            this.FLP.AutoScroll = true;
            this.FLP.BackColor = System.Drawing.Color.White;
            this.FLP.Location = new System.Drawing.Point(10, 16);
            this.FLP.Name = "FLP";
            this.FLP.Size = new System.Drawing.Size(118, 178);
            this.FLP.TabIndex = 2;
            // 
            // BTN_FastGenerate
            // 
            this.BTN_FastGenerate.Location = new System.Drawing.Point(143, 67);
            this.BTN_FastGenerate.Name = "BTN_FastGenerate";
            this.BTN_FastGenerate.Size = new System.Drawing.Size(82, 25);
            this.BTN_FastGenerate.TabIndex = 4;
            this.BTN_FastGenerate.Text = "Generate";
            this.BTN_FastGenerate.UseVisualStyleBackColor = true;
            this.BTN_FastGenerate.Click += new System.EventHandler(this.BTN_FastGenerate_Click);
            // 
            // FLP2
            // 
            this.FLP2.AutoScroll = true;
            this.FLP2.BackColor = System.Drawing.Color.White;
            this.FLP2.Location = new System.Drawing.Point(243, 16);
            this.FLP2.Name = "FLP2";
            this.FLP2.Size = new System.Drawing.Size(118, 178);
            this.FLP2.TabIndex = 3;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.Btn_FastSaveRow);
            this.groupBox1.Controls.Add(this.Btn_FastShowAll);
            this.groupBox1.Controls.Add(this.FLP);
            this.groupBox1.Controls.Add(this.BTN_FastGenerate);
            this.groupBox1.Controls.Add(this.FLP2);
            this.groupBox1.Location = new System.Drawing.Point(806, 34);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(383, 249);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Fast Edit";
            // 
            // Btn_FastSaveRow
            // 
            this.Btn_FastSaveRow.Location = new System.Drawing.Point(262, 224);
            this.Btn_FastSaveRow.Name = "Btn_FastSaveRow";
            this.Btn_FastSaveRow.Size = new System.Drawing.Size(82, 19);
            this.Btn_FastSaveRow.TabIndex = 11;
            this.Btn_FastSaveRow.Text = "SaveRow";
            this.Btn_FastSaveRow.UseVisualStyleBackColor = true;
            this.Btn_FastSaveRow.Click += new System.EventHandler(this.Btn_FastSaveRow_Click);
            // 
            // Btn_FastShowAll
            // 
            this.Btn_FastShowAll.Location = new System.Drawing.Point(262, 200);
            this.Btn_FastShowAll.Name = "Btn_FastShowAll";
            this.Btn_FastShowAll.Size = new System.Drawing.Size(82, 19);
            this.Btn_FastShowAll.TabIndex = 10;
            this.Btn_FastShowAll.Text = "ShowAllRows";
            this.Btn_FastShowAll.UseVisualStyleBackColor = true;
            this.Btn_FastShowAll.Click += new System.EventHandler(this.Btn_FastShowAll_Click);
            // 
            // FLP3
            // 
            this.FLP3.AutoScroll = true;
            this.FLP3.BackColor = System.Drawing.Color.White;
            this.FLP3.Location = new System.Drawing.Point(816, 399);
            this.FLP3.Name = "FLP3";
            this.FLP3.Size = new System.Drawing.Size(184, 178);
            this.FLP3.TabIndex = 4;
            // 
            // Btn_ShowAll
            // 
            this.Btn_ShowAll.Location = new System.Drawing.Point(1006, 399);
            this.Btn_ShowAll.Name = "Btn_ShowAll";
            this.Btn_ShowAll.Size = new System.Drawing.Size(82, 19);
            this.Btn_ShowAll.TabIndex = 12;
            this.Btn_ShowAll.Text = "ShowAll";
            this.Btn_ShowAll.UseVisualStyleBackColor = true;
            this.Btn_ShowAll.Click += new System.EventHandler(this.Btn_ShowAll_Click);
            // 
            // Btn_Save
            // 
            this.Btn_Save.Location = new System.Drawing.Point(1006, 437);
            this.Btn_Save.Name = "Btn_Save";
            this.Btn_Save.Size = new System.Drawing.Size(82, 19);
            this.Btn_Save.TabIndex = 13;
            this.Btn_Save.Text = "Save";
            this.Btn_Save.UseVisualStyleBackColor = true;
            this.Btn_Save.Click += new System.EventHandler(this.Btn_Save_Click);
            // 
            // paddingMouseRect
            // 
            this.paddingMouseRect.GBText = "Padding MouseRect";
            this.paddingMouseRect.Location = new System.Drawing.Point(806, 296);
            this.paddingMouseRect.Name = "paddingMouseRect";
            this.paddingMouseRect.Size = new System.Drawing.Size(194, 97);
            this.paddingMouseRect.TabIndex = 12;
            // 
            // paddingEachWord
            // 
            this.paddingEachWord.GBText = "Padding EeachWord";
            this.paddingEachWord.Location = new System.Drawing.Point(999, 296);
            this.paddingEachWord.Name = "paddingEachWord";
            this.paddingEachWord.Size = new System.Drawing.Size(190, 94);
            this.paddingEachWord.TabIndex = 11;
            // 
            // Btn_LoadTmp
            // 
            this.Btn_LoadTmp.Location = new System.Drawing.Point(1006, 474);
            this.Btn_LoadTmp.Name = "Btn_LoadTmp";
            this.Btn_LoadTmp.Size = new System.Drawing.Size(82, 19);
            this.Btn_LoadTmp.TabIndex = 14;
            this.Btn_LoadTmp.Text = "LoadTmp";
            this.Btn_LoadTmp.UseVisualStyleBackColor = true;
            this.Btn_LoadTmp.Click += new System.EventHandler(this.Btn_LoadTmp_Click);
            // 
            // FontEdit
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1211, 635);
            this.Controls.Add(this.Btn_LoadTmp);
            this.Controls.Add(this.Btn_Save);
            this.Controls.Add(this.Btn_ShowAll);
            this.Controls.Add(this.FLP3);
            this.Controls.Add(this.paddingMouseRect);
            this.Controls.Add(this.paddingEachWord);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.LB_Info);
            this.Controls.Add(this.panel1);
            this.Name = "FontEdit";
            this.Text = "FontEdit";
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label LB_Info;
        private System.Windows.Forms.FlowLayoutPanel FLP;
        private System.Windows.Forms.Button BTN_FastGenerate;
        private System.Windows.Forms.FlowLayoutPanel FLP2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button Btn_FastShowAll;
        private Padding paddingEachWord;
        private Padding paddingMouseRect;
        private System.Windows.Forms.FlowLayoutPanel FLP3;
        private System.Windows.Forms.Button Btn_FastSaveRow;
        private System.Windows.Forms.Button Btn_ShowAll;
        private System.Windows.Forms.Button Btn_Save;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button Btn_LoadTmp;
    }
}