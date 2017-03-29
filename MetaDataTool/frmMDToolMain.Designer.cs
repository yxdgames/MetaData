namespace MetaDataTool
{
    partial class frmMDTool
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.tbcMain = new System.Windows.Forms.TabControl();
            this.tbpClass = new System.Windows.Forms.TabPage();
            this.chkNameSpace = new System.Windows.Forms.CheckBox();
            this.btnDelStaticMemVar = new System.Windows.Forms.Button();
            this.btnAddStaticMemVar = new System.Windows.Forms.Button();
            this.btnDelStaticMemFunc = new System.Windows.Forms.Button();
            this.btnAddStaticMemFunc = new System.Windows.Forms.Button();
            this.btnDelMemFunc = new System.Windows.Forms.Button();
            this.btnAddMemFunc = new System.Windows.Forms.Button();
            this.btnDelMemVar = new System.Windows.Forms.Button();
            this.btnAddMemVar = new System.Windows.Forms.Button();
            this.btnDelInterface = new System.Windows.Forms.Button();
            this.btnAddInterface = new System.Windows.Forms.Button();
            this.btnDelBaseClass = new System.Windows.Forms.Button();
            this.btnAddBaseClass = new System.Windows.Forms.Button();
            this.txtStaticMemVar = new System.Windows.Forms.TextBox();
            this.txtStaticMemFunc = new System.Windows.Forms.TextBox();
            this.txtMemVar = new System.Windows.Forms.TextBox();
            this.txtMemFunc = new System.Windows.Forms.TextBox();
            this.txtIntf = new System.Windows.Forms.TextBox();
            this.txtBaseClass = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.chkOuter2 = new System.Windows.Forms.CheckBox();
            this.chkOuter1 = new System.Windows.Forms.CheckBox();
            this.txtOuter2 = new System.Windows.Forms.TextBox();
            this.txtOuter1 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtClassName = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.CreateMetaDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.txtConstructor = new System.Windows.Forms.TextBox();
            this.btnDelConstr = new System.Windows.Forms.Button();
            this.btnAddConstr = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.tbcMain.SuspendLayout();
            this.tbpClass.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tbcMain
            // 
            this.tbcMain.Controls.Add(this.tbpClass);
            this.tbcMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbcMain.Location = new System.Drawing.Point(0, 25);
            this.tbcMain.Name = "tbcMain";
            this.tbcMain.SelectedIndex = 0;
            this.tbcMain.Size = new System.Drawing.Size(975, 634);
            this.tbcMain.TabIndex = 0;
            // 
            // tbpClass
            // 
            this.tbpClass.Controls.Add(this.btnDelConstr);
            this.tbpClass.Controls.Add(this.btnAddConstr);
            this.tbpClass.Controls.Add(this.label10);
            this.tbpClass.Controls.Add(this.txtConstructor);
            this.tbpClass.Controls.Add(this.chkNameSpace);
            this.tbpClass.Controls.Add(this.btnDelStaticMemVar);
            this.tbpClass.Controls.Add(this.btnAddStaticMemVar);
            this.tbpClass.Controls.Add(this.btnDelStaticMemFunc);
            this.tbpClass.Controls.Add(this.btnAddStaticMemFunc);
            this.tbpClass.Controls.Add(this.btnDelMemFunc);
            this.tbpClass.Controls.Add(this.btnAddMemFunc);
            this.tbpClass.Controls.Add(this.btnDelMemVar);
            this.tbpClass.Controls.Add(this.btnAddMemVar);
            this.tbpClass.Controls.Add(this.btnDelInterface);
            this.tbpClass.Controls.Add(this.btnAddInterface);
            this.tbpClass.Controls.Add(this.btnDelBaseClass);
            this.tbpClass.Controls.Add(this.btnAddBaseClass);
            this.tbpClass.Controls.Add(this.txtStaticMemVar);
            this.tbpClass.Controls.Add(this.txtStaticMemFunc);
            this.tbpClass.Controls.Add(this.txtMemVar);
            this.tbpClass.Controls.Add(this.txtMemFunc);
            this.tbpClass.Controls.Add(this.txtIntf);
            this.tbpClass.Controls.Add(this.txtBaseClass);
            this.tbpClass.Controls.Add(this.label9);
            this.tbpClass.Controls.Add(this.label8);
            this.tbpClass.Controls.Add(this.label7);
            this.tbpClass.Controls.Add(this.label6);
            this.tbpClass.Controls.Add(this.label5);
            this.tbpClass.Controls.Add(this.label4);
            this.tbpClass.Controls.Add(this.chkOuter2);
            this.tbpClass.Controls.Add(this.chkOuter1);
            this.tbpClass.Controls.Add(this.txtOuter2);
            this.tbpClass.Controls.Add(this.txtOuter1);
            this.tbpClass.Controls.Add(this.label3);
            this.tbpClass.Controls.Add(this.label2);
            this.tbpClass.Controls.Add(this.label1);
            this.tbpClass.Controls.Add(this.txtClassName);
            this.tbpClass.Location = new System.Drawing.Point(4, 22);
            this.tbpClass.Name = "tbpClass";
            this.tbpClass.Padding = new System.Windows.Forms.Padding(3);
            this.tbpClass.Size = new System.Drawing.Size(967, 608);
            this.tbpClass.TabIndex = 0;
            this.tbpClass.Text = "类元数据";
            this.tbpClass.UseVisualStyleBackColor = true;
            // 
            // chkNameSpace
            // 
            this.chkNameSpace.AutoSize = true;
            this.chkNameSpace.Checked = true;
            this.chkNameSpace.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkNameSpace.Location = new System.Drawing.Point(841, 34);
            this.chkNameSpace.Name = "chkNameSpace";
            this.chkNameSpace.Size = new System.Drawing.Size(72, 16);
            this.chkNameSpace.TabIndex = 32;
            this.chkNameSpace.Text = "命令空间";
            this.chkNameSpace.UseVisualStyleBackColor = true;
            // 
            // btnDelStaticMemVar
            // 
            this.btnDelStaticMemVar.Location = new System.Drawing.Point(525, 299);
            this.btnDelStaticMemVar.Name = "btnDelStaticMemVar";
            this.btnDelStaticMemVar.Size = new System.Drawing.Size(16, 16);
            this.btnDelStaticMemVar.TabIndex = 31;
            this.btnDelStaticMemVar.UseVisualStyleBackColor = true;
            // 
            // btnAddStaticMemVar
            // 
            this.btnAddStaticMemVar.Location = new System.Drawing.Point(503, 299);
            this.btnAddStaticMemVar.Name = "btnAddStaticMemVar";
            this.btnAddStaticMemVar.Size = new System.Drawing.Size(16, 16);
            this.btnAddStaticMemVar.TabIndex = 30;
            this.btnAddStaticMemVar.UseVisualStyleBackColor = true;
            this.btnAddStaticMemVar.Click += new System.EventHandler(this.btnAddStaticMemVar_Click);
            // 
            // btnDelStaticMemFunc
            // 
            this.btnDelStaticMemFunc.Location = new System.Drawing.Point(774, 299);
            this.btnDelStaticMemFunc.Name = "btnDelStaticMemFunc";
            this.btnDelStaticMemFunc.Size = new System.Drawing.Size(16, 16);
            this.btnDelStaticMemFunc.TabIndex = 29;
            this.btnDelStaticMemFunc.UseVisualStyleBackColor = true;
            // 
            // btnAddStaticMemFunc
            // 
            this.btnAddStaticMemFunc.Location = new System.Drawing.Point(752, 299);
            this.btnAddStaticMemFunc.Name = "btnAddStaticMemFunc";
            this.btnAddStaticMemFunc.Size = new System.Drawing.Size(16, 16);
            this.btnAddStaticMemFunc.TabIndex = 28;
            this.btnAddStaticMemFunc.UseVisualStyleBackColor = true;
            this.btnAddStaticMemFunc.Click += new System.EventHandler(this.btnAddStaticMemFunc_Click);
            // 
            // btnDelMemFunc
            // 
            this.btnDelMemFunc.Location = new System.Drawing.Point(750, 73);
            this.btnDelMemFunc.Name = "btnDelMemFunc";
            this.btnDelMemFunc.Size = new System.Drawing.Size(16, 16);
            this.btnDelMemFunc.TabIndex = 27;
            this.btnDelMemFunc.UseVisualStyleBackColor = true;
            // 
            // btnAddMemFunc
            // 
            this.btnAddMemFunc.Location = new System.Drawing.Point(728, 73);
            this.btnAddMemFunc.Name = "btnAddMemFunc";
            this.btnAddMemFunc.Size = new System.Drawing.Size(16, 16);
            this.btnAddMemFunc.TabIndex = 26;
            this.btnAddMemFunc.UseVisualStyleBackColor = true;
            this.btnAddMemFunc.Click += new System.EventHandler(this.btnAddMemFunc_Click);
            // 
            // btnDelMemVar
            // 
            this.btnDelMemVar.Location = new System.Drawing.Point(501, 73);
            this.btnDelMemVar.Name = "btnDelMemVar";
            this.btnDelMemVar.Size = new System.Drawing.Size(16, 16);
            this.btnDelMemVar.TabIndex = 25;
            this.btnDelMemVar.UseVisualStyleBackColor = true;
            // 
            // btnAddMemVar
            // 
            this.btnAddMemVar.Location = new System.Drawing.Point(479, 73);
            this.btnAddMemVar.Name = "btnAddMemVar";
            this.btnAddMemVar.Size = new System.Drawing.Size(16, 16);
            this.btnAddMemVar.TabIndex = 24;
            this.btnAddMemVar.UseVisualStyleBackColor = true;
            this.btnAddMemVar.Click += new System.EventHandler(this.btnAddMemVar_Click);
            // 
            // btnDelInterface
            // 
            this.btnDelInterface.Location = new System.Drawing.Point(273, 73);
            this.btnDelInterface.Name = "btnDelInterface";
            this.btnDelInterface.Size = new System.Drawing.Size(16, 16);
            this.btnDelInterface.TabIndex = 23;
            this.btnDelInterface.UseVisualStyleBackColor = true;
            // 
            // btnAddInterface
            // 
            this.btnAddInterface.Location = new System.Drawing.Point(251, 73);
            this.btnAddInterface.Name = "btnAddInterface";
            this.btnAddInterface.Size = new System.Drawing.Size(16, 16);
            this.btnAddInterface.TabIndex = 22;
            this.btnAddInterface.UseVisualStyleBackColor = true;
            this.btnAddInterface.Click += new System.EventHandler(this.btnAddInterface_Click);
            // 
            // btnDelBaseClass
            // 
            this.btnDelBaseClass.Location = new System.Drawing.Point(71, 73);
            this.btnDelBaseClass.Name = "btnDelBaseClass";
            this.btnDelBaseClass.Size = new System.Drawing.Size(16, 16);
            this.btnDelBaseClass.TabIndex = 21;
            this.btnDelBaseClass.UseVisualStyleBackColor = true;
            this.btnDelBaseClass.Click += new System.EventHandler(this.btnDelBaseClass_Click);
            // 
            // btnAddBaseClass
            // 
            this.btnAddBaseClass.Location = new System.Drawing.Point(49, 73);
            this.btnAddBaseClass.Name = "btnAddBaseClass";
            this.btnAddBaseClass.Size = new System.Drawing.Size(16, 16);
            this.btnAddBaseClass.TabIndex = 20;
            this.btnAddBaseClass.UseVisualStyleBackColor = true;
            this.btnAddBaseClass.Click += new System.EventHandler(this.btnAddBaseClass_Click);
            // 
            // txtStaticMemVar
            // 
            this.txtStaticMemVar.Location = new System.Drawing.Point(416, 316);
            this.txtStaticMemVar.Multiline = true;
            this.txtStaticMemVar.Name = "txtStaticMemVar";
            this.txtStaticMemVar.ReadOnly = true;
            this.txtStaticMemVar.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtStaticMemVar.Size = new System.Drawing.Size(243, 276);
            this.txtStaticMemVar.TabIndex = 19;
            // 
            // txtStaticMemFunc
            // 
            this.txtStaticMemFunc.Location = new System.Drawing.Point(665, 316);
            this.txtStaticMemFunc.Multiline = true;
            this.txtStaticMemFunc.Name = "txtStaticMemFunc";
            this.txtStaticMemFunc.ReadOnly = true;
            this.txtStaticMemFunc.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtStaticMemFunc.Size = new System.Drawing.Size(296, 276);
            this.txtStaticMemFunc.TabIndex = 18;
            // 
            // txtMemVar
            // 
            this.txtMemVar.Location = new System.Drawing.Point(416, 90);
            this.txtMemVar.Multiline = true;
            this.txtMemVar.Name = "txtMemVar";
            this.txtMemVar.ReadOnly = true;
            this.txtMemVar.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtMemVar.Size = new System.Drawing.Size(243, 197);
            this.txtMemVar.TabIndex = 17;
            // 
            // txtMemFunc
            // 
            this.txtMemFunc.Location = new System.Drawing.Point(665, 90);
            this.txtMemFunc.Multiline = true;
            this.txtMemFunc.Name = "txtMemFunc";
            this.txtMemFunc.ReadOnly = true;
            this.txtMemFunc.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtMemFunc.Size = new System.Drawing.Size(296, 197);
            this.txtMemFunc.TabIndex = 16;
            // 
            // txtIntf
            // 
            this.txtIntf.Location = new System.Drawing.Point(212, 90);
            this.txtIntf.Multiline = true;
            this.txtIntf.Name = "txtIntf";
            this.txtIntf.ReadOnly = true;
            this.txtIntf.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtIntf.Size = new System.Drawing.Size(196, 197);
            this.txtIntf.TabIndex = 15;
            // 
            // txtBaseClass
            // 
            this.txtBaseClass.Location = new System.Drawing.Point(10, 90);
            this.txtBaseClass.Multiline = true;
            this.txtBaseClass.Name = "txtBaseClass";
            this.txtBaseClass.ReadOnly = true;
            this.txtBaseClass.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtBaseClass.Size = new System.Drawing.Size(196, 197);
            this.txtBaseClass.TabIndex = 14;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(414, 301);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(83, 12);
            this.label9.TabIndex = 13;
            this.label9.Text = "静态成员变量:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(663, 301);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(83, 12);
            this.label8.TabIndex = 12;
            this.label8.Text = "静态成员函数:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(414, 75);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 12);
            this.label7.TabIndex = 11;
            this.label7.Text = "成员变量:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(663, 75);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(59, 12);
            this.label6.TabIndex = 10;
            this.label6.Text = "成员函数:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(210, 75);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "接口:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 75);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 12);
            this.label4.TabIndex = 8;
            this.label4.Text = "基类:";
            // 
            // chkOuter2
            // 
            this.chkOuter2.AutoSize = true;
            this.chkOuter2.Location = new System.Drawing.Point(789, 34);
            this.chkOuter2.Name = "chkOuter2";
            this.chkOuter2.Size = new System.Drawing.Size(15, 14);
            this.chkOuter2.TabIndex = 7;
            this.chkOuter2.UseVisualStyleBackColor = true;
            this.chkOuter2.CheckedChanged += new System.EventHandler(this.chkOuter2_CheckedChanged);
            // 
            // chkOuter1
            // 
            this.chkOuter1.AutoSize = true;
            this.chkOuter1.Location = new System.Drawing.Point(487, 34);
            this.chkOuter1.Name = "chkOuter1";
            this.chkOuter1.Size = new System.Drawing.Size(15, 14);
            this.chkOuter1.TabIndex = 6;
            this.chkOuter1.UseVisualStyleBackColor = true;
            this.chkOuter1.CheckedChanged += new System.EventHandler(this.chkOuter1_CheckedChanged);
            // 
            // txtOuter2
            // 
            this.txtOuter2.BackColor = System.Drawing.SystemColors.Window;
            this.txtOuter2.Enabled = false;
            this.txtOuter2.Location = new System.Drawing.Point(570, 31);
            this.txtOuter2.Name = "txtOuter2";
            this.txtOuter2.Size = new System.Drawing.Size(213, 21);
            this.txtOuter2.TabIndex = 5;
            // 
            // txtOuter1
            // 
            this.txtOuter1.BackColor = System.Drawing.SystemColors.Window;
            this.txtOuter1.Enabled = false;
            this.txtOuter1.Location = new System.Drawing.Point(291, 31);
            this.txtOuter1.Name = "txtOuter1";
            this.txtOuter1.Size = new System.Drawing.Size(190, 21);
            this.txtOuter1.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(517, 34);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "外层名:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(226, 34);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "紧外层名:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "类名:";
            // 
            // txtClassName
            // 
            this.txtClassName.Location = new System.Drawing.Point(49, 31);
            this.txtClassName.Name = "txtClassName";
            this.txtClassName.Size = new System.Drawing.Size(157, 21);
            this.txtClassName.TabIndex = 0;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(975, 25);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.CreateMetaDataToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(48, 21);
            this.toolStripMenuItem1.Text = "创 建";
            // 
            // CreateMetaDataToolStripMenuItem
            // 
            this.CreateMetaDataToolStripMenuItem.Name = "CreateMetaDataToolStripMenuItem";
            this.CreateMetaDataToolStripMenuItem.Size = new System.Drawing.Size(145, 22);
            this.CreateMetaDataToolStripMenuItem.Text = "创建元数据...";
            this.CreateMetaDataToolStripMenuItem.Click += new System.EventHandler(this.CreateMetaDataToolStripMenuItem_Click);
            // 
            // txtConstructor
            // 
            this.txtConstructor.Location = new System.Drawing.Point(165, 316);
            this.txtConstructor.Multiline = true;
            this.txtConstructor.Name = "txtConstructor";
            this.txtConstructor.ReadOnly = true;
            this.txtConstructor.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtConstructor.Size = new System.Drawing.Size(243, 276);
            this.txtConstructor.TabIndex = 33;
            // 
            // btnDelConstr
            // 
            this.btnDelConstr.Location = new System.Drawing.Point(250, 299);
            this.btnDelConstr.Name = "btnDelConstr";
            this.btnDelConstr.Size = new System.Drawing.Size(16, 16);
            this.btnDelConstr.TabIndex = 36;
            this.btnDelConstr.UseVisualStyleBackColor = true;
            // 
            // btnAddConstr
            // 
            this.btnAddConstr.Location = new System.Drawing.Point(228, 299);
            this.btnAddConstr.Name = "btnAddConstr";
            this.btnAddConstr.Size = new System.Drawing.Size(16, 16);
            this.btnAddConstr.TabIndex = 35;
            this.btnAddConstr.UseVisualStyleBackColor = true;
            this.btnAddConstr.Click += new System.EventHandler(this.btnAddConstr_Click);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(163, 301);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(59, 12);
            this.label10.TabIndex = 34;
            this.label10.Text = "构造函数:";
            // 
            // frmMDTool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(975, 659);
            this.Controls.Add(this.tbcMain);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.MaximumSize = new System.Drawing.Size(991, 697);
            this.MinimumSize = new System.Drawing.Size(991, 697);
            this.Name = "frmMDTool";
            this.Text = "元数据工具";
            this.tbcMain.ResumeLayout(false);
            this.tbpClass.ResumeLayout(false);
            this.tbpClass.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl tbcMain;
        private System.Windows.Forms.TabPage tbpClass;
        private System.Windows.Forms.TextBox txtClassName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtOuter2;
        private System.Windows.Forms.TextBox txtOuter1;
        private System.Windows.Forms.CheckBox chkOuter2;
        private System.Windows.Forms.CheckBox chkOuter1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtIntf;
        private System.Windows.Forms.TextBox txtBaseClass;
        private System.Windows.Forms.TextBox txtMemVar;
        private System.Windows.Forms.TextBox txtMemFunc;
        private System.Windows.Forms.TextBox txtStaticMemVar;
        private System.Windows.Forms.TextBox txtStaticMemFunc;
        private System.Windows.Forms.Button btnDelBaseClass;
        private System.Windows.Forms.Button btnAddBaseClass;
        private System.Windows.Forms.Button btnDelInterface;
        private System.Windows.Forms.Button btnAddInterface;
        private System.Windows.Forms.Button btnAddMemVar;
        private System.Windows.Forms.Button btnDelMemVar;
        private System.Windows.Forms.Button btnDelMemFunc;
        private System.Windows.Forms.Button btnAddMemFunc;
        private System.Windows.Forms.Button btnAddStaticMemFunc;
        private System.Windows.Forms.Button btnAddStaticMemVar;
        private System.Windows.Forms.Button btnDelStaticMemFunc;
        private System.Windows.Forms.Button btnDelStaticMemVar;
        private System.Windows.Forms.CheckBox chkNameSpace;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem CreateMetaDataToolStripMenuItem;
        private System.Windows.Forms.Button btnDelConstr;
        private System.Windows.Forms.Button btnAddConstr;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox txtConstructor;
    }
}

