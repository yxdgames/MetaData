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
    public partial class DlgClass : Form
    {
        public DlgClass()
        {
            InitializeComponent();
        }
        public InfoType infoType = null;
        private void btnOK_Click(object sender, EventArgs e)
        {
            string Name, Outer1, Outer2;
            Utility.GetTypeNameOuters(txtClassName.Text, out Name, out Outer1, out Outer2);
            if (Name == "")
            {
                MessageBox.Show("类名不能为空！");
                return;
            }
            infoType = new InfoType();
            infoType.Name = Name;
            if (Outer1 != "")
            {
                infoType.Outer = new string[1];
                if (Outer2 == "")
                {
                    infoType.Outer[0] = Outer1;
                }
                else
                {
                    infoType.Outer[0] = Outer2 + "::" + Outer1;
                }
            }
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }
    }
}
