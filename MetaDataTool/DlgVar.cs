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
    public partial class DlgVar : Form
    {
        public DlgVar()
        {
            InitializeComponent();
        }
        public InfoVar infoVar = null;

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (txtVarName.Text == "")
            {
                MessageBox.Show("变量名不能为空！");
                return;
            }
            if (txtTypeName.Text == "")
            {
                MessageBox.Show("类型名不能为空！");
                return;
            }

            string Outer1, Outer2;

            infoVar = new InfoVar();
            infoVar.Name = txtVarName.Text;
            infoVar.infoType = new InfoType();
            Utility.GetTypeNameOuters(txtTypeName.Text, out infoVar.infoType.Name, out Outer1, out Outer2);
            if (Outer1 != "")
            {
                infoVar.infoType.Outer = new string[1];
                if (Outer2 == "")
                {
                    infoVar.infoType.Outer[0] = Outer1;
                }
                else
                {
                    infoVar.infoType.Outer[0] = Outer2 + "::" + Outer1;
                }
            }
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }
    }
}
