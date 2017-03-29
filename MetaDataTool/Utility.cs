using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MetaDataTool
{
    class Utility
    {
        public static void GetTypeNameOuters(string FullName, out string Name, out string Outer1, out string Outer2)
        {
            Name = null;
            Outer1 = null;
            Outer2 = null;
            if (FullName == "") return;

            int index = FullName.LastIndexOf("::");
            if (index == -1)
            {
                Name = FullName;
            }
            else
            {
                string Outer = FullName.Substring(0, index);
                Name = FullName.Substring(index + 2);

                index = Outer.LastIndexOf("::");
                if (index == -1)
                {
                    Outer1 = Outer;
                }
                else
                {
                    Outer1 = Outer.Substring(index + 2);
                    Outer2 = Outer.Substring(0, index);
                }
            }
        }
    }
}
