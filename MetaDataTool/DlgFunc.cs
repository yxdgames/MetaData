using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MetaDataTool
{
    public partial class DlgFunc : Form
    {
        public DlgFunc()
        {
            InitializeComponent();
        }

        public bool NeedFunctionName
        {
            get { return m_bNeedFunctionName; }
            set
            {
                m_bNeedFunctionName = value;
                txtFuncName.Enabled = m_bNeedFunctionName;
            }
        }
        public bool NeedFunctionReturn
        {
            get { return m_bNeedFunctionReturn; }
            set
            {
                m_bNeedFunctionReturn = value;
                txtTypeName.Enabled = m_bNeedFunctionReturn;
            }
        }
        public string FunctionName { set { txtFuncName.Text = value; } }
        public string FunctionRet { set { txtTypeName.Text = value; } }
        public InfoFunc infoFunc = null;
        private List<InfoVar> Params = new List<InfoVar>();
        private bool m_bNeedFunctionName = true;
        private bool m_bNeedFunctionReturn = true;

        private void InitParamsView()
        {
            txtParams.Text = "";
            foreach (InfoVar item in Params)
            {
                if (txtParams.Text != "")
                    txtParams.Text += "\r\n";
                txtParams.Text += item.infoType.Name + " " + item.Name;
            }
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (m_bNeedFunctionName && txtFuncName.Text == "")
            {
                MessageBox.Show("函数名不能为空！");
                return;
            }
            if (m_bNeedFunctionReturn && txtTypeName.Text == "")
            {
                MessageBox.Show("返回值不能为空！");
                return;
            }
            infoFunc = new InfoFunc();
            if (Params.Count > 0)
            {
                infoFunc.Params = Params;
                Params = null;
            }
            infoFunc.Name = txtFuncName.Text;
            if (txtTypeName.Text != "void" && txtTypeName.Text != "")
            {
                string Outer1, Outer2;
                
                Utility.GetTypeNameOuters(txtTypeName.Text, out infoFunc.Ret.Name, out Outer1, out Outer2);

                infoFunc.Ret = new InfoType();
                if (Outer1 != "")
                {
                    infoFunc.Ret.Outer = new string[1];
                    if (Outer2 == "")
                    {
                        infoFunc.Ret.Outer[0] = Outer1;
                    }
                    else
                    {
                        infoFunc.Ret.Outer[0] = Outer2 + "::" + Outer1;
                    }
                }
            }
            else infoFunc.Ret = null;
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }

        private void btnAddParam_Click(object sender, EventArgs e)
        {
            DlgVar dlgVar = new DlgVar();
            try
            {
                if (dlgVar.ShowDialog() == System.Windows.Forms.DialogResult.OK && dlgVar.infoVar != null)
                {
                    Params.Add(dlgVar.infoVar);
                    dlgVar.infoVar = null;
                    InitParamsView();
                }
            }
            finally
            {
                dlgVar = null;
            }
        }

        private void btnDelParam_Click(object sender, EventArgs e)
        {
            int LineCount = 0;
            for (int i = txtParams.SelectionStart - 1; i >= 0; --i)
            {
                if (txtParams.Text[i] == '\n')
                {
                    ++LineCount;
                }
            }
            if (0 <= LineCount && LineCount < Params.Count)
            {
                Params.Remove(Params[LineCount]);
                InitParamsView();
            }
        }
    }
}
