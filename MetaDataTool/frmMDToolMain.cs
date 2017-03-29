using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace MetaDataTool
{
    public partial class frmMDTool : Form
    {
        public frmMDTool()
        {
            InitializeComponent();
        }

        private void InitBaseClassView()
        {
            txtBaseClass.Text = "";
            foreach (InfoType item in BaseTypes)
            {
                if (txtBaseClass.Text != "")
                    txtBaseClass.Text += "\r\n";
                txtBaseClass.Text += item.Name;
            }
        }
        private void InitInterfaceView()
        {
            txtIntf.Text = "";
            foreach (InfoType item in Intfs)
            {
                if (txtIntf.Text != "")
                    txtIntf.Text += "\r\n";
                txtIntf.Text += item.Name;
            }
        }
        private void InitMemVarView()
        {
            txtMemVar.Text = "";
            foreach (InfoVar item in MemVar)
            {
                if (txtMemVar.Text != "")
                    txtMemVar.Text += "\r\n";
                txtMemVar.Text += item.infoType.Name + " " + item.Name;
            }
        }
        private void InitMemFuncView()
        {
            txtMemFunc.Text = "";
            bool bF;
            foreach (InfoFunc item in MemFunc)
            {
                if (txtMemFunc.Text != "")
                    txtMemFunc.Text += "\r\n";
                if (item.Ret != null)
                {
                    txtMemFunc.Text += item.Ret.Name + " " + item.Name + "(";
                }
                else txtMemFunc.Text += "void " + item.Name + "(";
                if (item.Params != null)
                {
                    bF = true;
                    foreach (InfoVar iv in item.Params)
                    {
                        if (!bF)
                            txtMemFunc.Text += ", ";
                        txtMemFunc.Text += iv.infoType.Name + " " + iv.Name;
                        bF = false;
                    }
                    txtMemFunc.Text += ")";
                }
                else { txtMemFunc.Text += "void)"; }
            }
        }
        private void InitStaticMemFuncView()
        {
            txtStaticMemFunc.Text = "";
            bool bF;
            foreach (InfoFunc item in StaticMemFunc)
            {
                if (txtStaticMemFunc.Text != "")
                    txtStaticMemFunc.Text += "\r\n";
                if (item.Ret != null)
                {
                    txtStaticMemFunc.Text += item.Ret.Name + " " + item.Name + "(";
                }
                else txtStaticMemFunc.Text += "void " + item.Name + "(";
                if (item.Params != null)
                {
                    bF = true;
                    foreach (InfoVar iv in item.Params)
                    {
                        if (!bF)
                            txtStaticMemFunc.Text += ", ";
                        txtStaticMemFunc.Text += iv.infoType.Name + " " + iv.Name;
                        bF = false;
                    }
                    txtStaticMemFunc.Text += ")";
                }
                else { txtStaticMemFunc.Text += "void)"; }
            }
        }
        private void InitStaticMemVarView()
        {
            txtStaticMemVar.Text = "";
            foreach (InfoVar item in StaticMemVar)
            {
                if (txtStaticMemVar.Text != "")
                    txtStaticMemVar.Text += "\r\n";
                txtStaticMemVar.Text += item.infoType.Name + " " +  item.Name;
            }
        }
        private void InitConstructorView()
        {
            txtConstructor.Text = "";
            bool bF;
            foreach (InfoFunc item in Constructor)
            {
                if (txtConstructor.Text != "")
                    txtConstructor.Text += "\r\n";
                if (item.Ret != null)
                {
                    return;
                }
                txtConstructor.Text += item.Name + "(";
                if (item.Params != null)
                {
                    bF = true;
                    foreach (InfoVar iv in item.Params)
                    {
                        if (!bF)
                            txtConstructor.Text += ", ";
                        txtConstructor.Text += iv.infoType.Name + " " + iv.Name;
                        bF = false;
                    }
                    txtConstructor.Text += ")";
                }
                else { txtConstructor.Text += "void)"; }
            }
        }
        private List<InfoType> BaseTypes { get { return ClsMDCreater.BaseTypes; } }
        private List<InfoType> Intfs { get { return ClsMDCreater.Intfs; } }
        private List<InfoVar> MemVar { get { return ClsMDCreater.MemVar; } }
        private List<InfoVar> StaticMemVar { get { return ClsMDCreater.StaticMemVar; } }
        private List<InfoFunc> MemFunc { get { return ClsMDCreater.MemFunc; } }
        private List<InfoFunc> StaticMemFunc { get { return ClsMDCreater.StaticMemFunc; } }
        private List<InfoFunc> Constructor { get { return ClsMDCreater.Constructor; } }
        private ClassMetaDataCreater ClsMDCreater = new ClassMetaDataCreater();

        private void btnAddBaseClass_Click(object sender, EventArgs e)
        {
            DlgClass dlgClass = new DlgClass();
            try
            {
                if (dlgClass.ShowDialog() == System.Windows.Forms.DialogResult.OK && dlgClass.infoType != null)
                {
                    BaseTypes.Add(dlgClass.infoType);
                    dlgClass.infoType = null;
                    InitBaseClassView();
                }
            }
            finally
            {
                dlgClass = null;
            }
        }

        private void btnAddInterface_Click(object sender, EventArgs e)
        {
            DlgClass dlgClass = new DlgClass();
            try
            {
                if (dlgClass.ShowDialog() == System.Windows.Forms.DialogResult.OK && dlgClass.infoType != null)
                {
                    Intfs.Add(dlgClass.infoType);
                    dlgClass.infoType = null;
                    InitInterfaceView();
                }
            }
            finally
            {
                dlgClass = null;
            }
        }

        private void btnAddMemVar_Click(object sender, EventArgs e)
        {
            DlgVar dlgVar = new DlgVar();
            try
            {
                if (dlgVar.ShowDialog() == System.Windows.Forms.DialogResult.OK && dlgVar.infoVar != null)
                {
                    MemVar.Add(dlgVar.infoVar);
                    dlgVar.infoVar = null;
                    InitMemVarView();
                }
            }
            finally
            {
                dlgVar = null;
            }
        }

        private void btnAddMemFunc_Click(object sender, EventArgs e)
        {
            DlgFunc dlgFunc = new DlgFunc();
            try
            {
                if (dlgFunc.ShowDialog() == System.Windows.Forms.DialogResult.OK && dlgFunc.infoFunc != null)
                {
                    MemFunc.Add(dlgFunc.infoFunc);
                    dlgFunc.infoFunc = null;
                    InitMemFuncView();
                }
            }
            finally
            {
                dlgFunc = null;
            }
        }

        private void btnAddStaticMemFunc_Click(object sender, EventArgs e)
        {
            DlgFunc dlgFunc = new DlgFunc();
            try
            {
                if (dlgFunc.ShowDialog() == System.Windows.Forms.DialogResult.OK && dlgFunc.infoFunc != null)
                {
                    StaticMemFunc.Add(dlgFunc.infoFunc);
                    dlgFunc.infoFunc = null;
                    InitStaticMemFuncView();
                }
            }
            finally
            {
                dlgFunc = null;
            }
        }

        private void btnAddStaticMemVar_Click(object sender, EventArgs e)
        {
            DlgVar dlgVar = new DlgVar();
            try
            {
                if (dlgVar.ShowDialog() == System.Windows.Forms.DialogResult.OK && dlgVar.infoVar != null)
                {
                    StaticMemVar.Add(dlgVar.infoVar);
                    dlgVar.infoVar = null;
                    InitStaticMemVarView();
                }
            }
            finally
            {
                dlgVar = null;
            }
        }

        private void chkOuter1_CheckedChanged(object sender, EventArgs e)
        {
            txtOuter1.Enabled = chkOuter1.Checked;
        }

        private void chkOuter2_CheckedChanged(object sender, EventArgs e)
        {
            txtOuter2.Enabled = chkOuter2.Checked;
        }

        private void CreateMetaDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ClsMDCreater.ClassName = txtClassName.Text;
            string result = ClsMDCreater.Create();
            FileInfo fi = new FileInfo("D:\\MD_Test.txt");
            StreamWriter sw = fi.CreateText();
            sw.Write(result);
            sw.Dispose();
        }

        private void btnAddConstr_Click(object sender, EventArgs e)
        {
            if (txtClassName.Text == "")
            {
                MessageBox.Show("请先定义类名！");
                return;
            }
            DlgFunc dlgFunc = new DlgFunc();
            try
            {
                dlgFunc.NeedFunctionName = false;
                dlgFunc.NeedFunctionReturn = false;
                dlgFunc.FunctionName = txtClassName.Text;
                if (dlgFunc.ShowDialog() == System.Windows.Forms.DialogResult.OK && dlgFunc.infoFunc != null)
                {
                    dlgFunc.infoFunc.Name = this.txtClassName.Text;
                    Constructor.Add(dlgFunc.infoFunc);
                    dlgFunc.infoFunc = null;
                    InitConstructorView();
                }
            }
            finally
            {
                dlgFunc = null;
            }
        }

        private void btnDelBaseClass_Click(object sender, EventArgs e)
        {

        }
    }
}
