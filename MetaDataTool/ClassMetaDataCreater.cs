using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MetaDataTool
{
    class ClassMetaDataCreater
    {
        public string Create()
        {
            string header_str = CreateHeader();
            string src_str = CreateSrc();
            return header_str + "\r\n\r\n\r\n\r\n\r\n" + src_str;
        }

        private string CreateHeader()
        {
            if (ClassName == "") return "";

            string func_wrapper_str = CreateHeader_func_wrapper();
            string func_def_str = CreateHeader_func_def();
            string var_dec_str = CreateHeader_var_def();
            string base_type_str = CreateHeader_base_type_def();

            if (func_wrapper_str != "")
                func_wrapper_str += "\r\n";
            if (base_type_str != "")
                base_type_str += "\r\n";
            if (var_dec_str != "")
                var_dec_str += "\r\n";
            if (func_def_str != "")
                func_def_str += "\r\n";
            return MACRO_CLASS_DEC_BEGIN + "(" + ClassName + ")\r\n"
                 + func_wrapper_str
                 + MACRO_CLASS_DEC_DETAIL + "(" + ClassName + ")\r\n"
                 + base_type_str
                 + var_dec_str
                 + func_def_str
                 + MACRO_CLASS_DEC_END + "(" + ClassName + ")";
        }

        private string CreateHeader_func_wrapper()
        {
            string func_wrapper_str = "";
            FuncIndexList func_index_list = new FuncIndexList();

            foreach (InfoFunc item in Constructor)
            {
                if (func_wrapper_str != "")
                {
                    func_wrapper_str += "\r\n";
                }
                func_wrapper_str += "   " + MACRO_CLASS_CONS_WRAPPER_DEC + "(" + item.Name + ", " + func_index_list.GetIndex(item.Name) + ")";
            }
            foreach (InfoFunc item in MemFunc)
            {
                if (func_wrapper_str != "")
                {
                    func_wrapper_str += "\r\n";
                }
                func_wrapper_str += "   " + MACRO_CLASS_MEM_FUNC_WRAPPER_DEC + "(" + ClassName + ", " + item.Name + ", " + func_index_list.GetIndex(item.Name) + ")";
            }
            foreach (InfoFunc item in StaticMemFunc)
            {
                if (func_wrapper_str != "")
                {
                    func_wrapper_str += "\r\n";
                }
                func_wrapper_str += "   " + MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEC + "(" + ClassName + ", " + item.Name + ", " + func_index_list.GetIndex(item.Name) + ")";
            }
            return func_wrapper_str;
        }
        private string CreateHeader_func_def()
        {
            string func_def_str = "";
            FuncIndexList func_index_list = new FuncIndexList();

            string tmpStr1, tmpStr2;
            int num;

            foreach (InfoFunc item in Constructor)
            {
                if (func_def_str != "")
                {
                    func_def_str += "\r\n";
                }
                func_def_str += "   " + MACRO_CLASS_CONS_DEF + "(" + item.Name + ", " + func_index_list.GetIndex(item.Name) + ")";
                //parameters
                if (item.Params != null)
                {
                    foreach (InfoVar param in item.Params)
                    {
                        if (func_def_str != "")
                        {
                            func_def_str += "\r\n";
                        }
                        tmpStr1 = "";
                        if (param.infoType.Outer != null && param.infoType.Outer.Count() > 0)
                        {
                            foreach (string str in param.infoType.Outer)
                            {
                                if (tmpStr1 != "")
                                {
                                    tmpStr1 += "::";
                                }
                                tmpStr1 += str;
                            }
                        }
                        tmpStr2 = param.infoType.Name;
                        num = 0;
                        for (int i = tmpStr2.Count() - 1; i >= 0; --i)
                        {
                            if (tmpStr2[i] == '*')
                            {
                                ++num;
                            }
                            else break;
                        }
                        tmpStr2 = tmpStr2.Substring(0, tmpStr2.Count() - num);
                        if (tmpStr1 != "")
                            tmpStr2 = tmpStr1 + "::" + tmpStr2;
                        func_def_str += "       " + MACRO_CLASS_CONS_PARAM_DEF + "(" + param.Name + ", " + "*TypeTraits<" + tmpStr2 + ">::GetMetaDataType(), " + num.ToString() + ")";
                    }
                }
            }
            foreach (InfoFunc item in MemFunc)
            {
                if (func_def_str != "")
                {
                    func_def_str += "\r\n";
                }
                func_def_str += "   " + MACRO_CLASS_MEM_FUNC_DEF + "(" + ClassName + ", " + item.Name + ", " + func_index_list.GetIndex(item.Name) + ")";
                //parameters & return
                if (item.Params != null)
                {
                    foreach (InfoVar param in item.Params)
                    {
                        if (func_def_str != "")
                        {
                            func_def_str += "\r\n";
                        }
                        tmpStr1 = "";
                        if (param.infoType.Outer != null && param.infoType.Outer.Count() > 0)
                        {
                            foreach (string str in param.infoType.Outer)
                            {
                                if (tmpStr1 != "")
                                {
                                    tmpStr1 += "::";
                                }
                                tmpStr1 += str;
                            }
                        }
                        tmpStr2 = param.infoType.Name;
                        num = 0;
                        for (int i = tmpStr2.Count() - 1; i >= 0; --i)
                        {
                            if (tmpStr2[i] == '*')
                            {
                                ++num;
                            }
                            else break;
                        }
                        tmpStr2 = tmpStr2.Substring(0, tmpStr2.Count() - num);
                        if (tmpStr1 != "")
                            tmpStr2 = tmpStr1 + "::" + tmpStr2;
                        func_def_str += "       " + MACRO_CLASS_MEM_FUNC_PARAM_DEF + "(" + param.Name + ", " + "*TypeTraits<" + tmpStr2 + ">::GetMetaDataType(), " + num.ToString() + ")";
                    }
                }
                if (item.Ret != null)
                {
                    tmpStr1 = "";
                    if (item.Ret.Outer != null && item.Ret.Outer.Count() > 0)
                    {
                        foreach (string str in item.Ret.Outer)
                        {
                            if (tmpStr1 != "")
                            {
                                tmpStr1 += "::";
                            }
                            tmpStr1 += str;
                        }
                    }
                    tmpStr2 = item.Ret.Name;
                    num = 0;
                    for (int i = tmpStr2.Count() - 1; i >= 0; --i)
                    {
                        if (tmpStr2[i] == '*')
                        {
                            ++num;
                        }
                        else break;
                    }
                    tmpStr2 = tmpStr2.Substring(0, tmpStr2.Count() - num);
                    if (tmpStr1 != "")
                        tmpStr2 = tmpStr1 + "::" + tmpStr2;
                    for (int i = tmpStr2.Count() - 1; i >= 0; --i)
                    {
                        if (tmpStr2[i] == '*')
                        {
                            ++num;
                        }
                        else break;
                    }
                    if (func_def_str != "")
                    {
                        func_def_str += "\r\n";
                    }
                    func_def_str += "       " + MACRO_CLASS_MEM_FUNC_RET_DEF + "(" + "*TypeTraits<" + tmpStr2 + ">::GetMetaDataType(), " + num.ToString() + ")";
                }
            }
            foreach (InfoFunc item in StaticMemFunc)
            {
                if (func_def_str != "")
                {
                    func_def_str += "\r\n";
                }
                func_def_str += "   " + MACRO_CLASS_STATIC_MEM_FUNC_DEF + "(" + ClassName + ", " + item.Name + ", " + func_index_list.GetIndex(item.Name) + ")";
                //parameters & return
                if (item.Params != null)
                {
                    foreach (InfoVar param in item.Params)
                    {
                        if (func_def_str != "")
                        {
                            func_def_str += "\r\n";
                        }
                        tmpStr1 = "";
                        if (param.infoType.Outer != null && param.infoType.Outer.Count() > 0)
                        {
                            foreach (string str in param.infoType.Outer)
                            {
                                if (tmpStr1 != "")
                                {
                                    tmpStr1 += "::";
                                }
                                tmpStr1 += str;
                            }
                        }
                        tmpStr2 = param.infoType.Name;
                        num = 0;
                        for (int i = tmpStr2.Count() - 1; i >= 0; --i)
                        {
                            if (tmpStr2[i] == '*')
                            {
                                ++num;
                            }
                            else break;
                        }
                        tmpStr2 = tmpStr2.Substring(0, tmpStr2.Count() - num);
                        if (tmpStr1 != "")
                            tmpStr2 = tmpStr1 + "::" + tmpStr2;
                        func_def_str += "       " + MACRO_CLASS_STATIC_MEM_FUNC_PARAM_DEF + "(" + param.Name + ", " + "*TypeTraits<" + tmpStr2 + ">::GetMetaDataType(), " + num.ToString() + ")";
                    }
                }
                if (item.Ret != null)
                {
                    tmpStr1 = "";
                    if (item.Ret.Outer != null && item.Ret.Outer.Count() > 0)
                    {
                        foreach (string str in item.Ret.Outer)
                        {
                            if (tmpStr1 != "")
                            {
                                tmpStr1 += "::";
                            }
                            tmpStr1 += str;
                        }
                    }
                    tmpStr2 = item.Ret.Name;
                    num = 0;
                    for (int i = tmpStr2.Count() - 1; i >= 0; --i)
                    {
                        if (tmpStr2[i] == '*')
                        {
                            ++num;
                        }
                        else break;
                    }
                    tmpStr2 = tmpStr2.Substring(0, tmpStr2.Count() - num);
                    if (tmpStr1 != "")
                        tmpStr2 = tmpStr1 + "::" + tmpStr2;
                    for (int i = tmpStr2.Count() - 1; i >= 0; --i)
                    {
                        if (tmpStr2[i] == '*')
                        {
                            ++num;
                        }
                        else break;
                    }
                    if (func_def_str != "")
                    {
                        func_def_str += "\r\n";
                    }
                    func_def_str += "       " + MACRO_CLASS_STATIC_MEM_FUNC_RET_DEF + "(" + "*TypeTraits<" + tmpStr2 + ">::GetMetaDataType(), " + num.ToString() + ")";
                }
            }

            return func_def_str;
        }
        private string CreateHeader_var_def()
        {
            string var_dec_str = "";
            string tmpStr1, tmpStr2;
            int num;

            foreach (InfoVar item in MemVar)
            {
                if (var_dec_str != "")
                    var_dec_str += "\r\n";
                tmpStr1 = "";
                if (item.infoType.Outer != null && item.infoType.Outer.Count() > 0)
                {
                    foreach (string str in item.infoType.Outer)
                    {
                        if (tmpStr1 != "")
                        {
                            tmpStr1 += "::";
                        }
                        tmpStr1 += str;
                    }
                }
                tmpStr2 = item.infoType.Name;
                num = 0;
                for (int i = tmpStr2.Count() - 1; i >= 0; --i)
                {
                    if (tmpStr2[i] == '*')
                    {
                        ++num;
                    }
                    else break;
                }
                tmpStr2 = tmpStr2.Substring(0, tmpStr2.Count() - num);
                if (tmpStr1 != "")
                    tmpStr2 = tmpStr1 + "::" + tmpStr2;
                var_dec_str += "   " + MACRO_CLASS_MEM_VAR_DEF + "(" + ClassName + ", " + item.Name + ", " + "*TypeTraits<" + tmpStr2 + ">::GetMetaDataType(), " + num.ToString() + ")";
            }

            foreach (InfoVar item in StaticMemVar)
            {
                if (var_dec_str != "")
                    var_dec_str += "\r\n";
                tmpStr1 = "";
                if (item.infoType.Outer != null && item.infoType.Outer.Count() > 0)
                {
                    foreach (string str in item.infoType.Outer)
                    {
                        if (tmpStr1 != "")
                        {
                            tmpStr1 += "::";
                        }
                        tmpStr1 += str;
                    }
                }
                tmpStr2 = item.infoType.Name;
                num = 0;
                for (int i = tmpStr2.Count() - 1; i >= 0; --i)
                {
                    if (tmpStr2[i] == '*')
                    {
                        ++num;
                    }
                    else break;
                }
                tmpStr2 = tmpStr2.Substring(0, tmpStr2.Count() - num);
                if (tmpStr1 != "")
                    tmpStr2 = tmpStr1 + "::" + tmpStr2;
                var_dec_str += "   " + MACRO_CLASS_STATIC_MEM_VAR_DEF + "(" + ClassName + ", " + item.Name + ", " + "*TypeTraits<" + tmpStr2 + ">::GetMetaDataType(), " + num.ToString() + ")";
            }

            return var_dec_str;
        }
        private string CreateHeader_base_type_def()
        {
            string base_type_str = "";
            string tmpStr1;

            foreach (InfoType item in BaseTypes)
            {
                if (base_type_str != "")
                {
                    base_type_str += "\r\n";
                }
                tmpStr1 = "";
                if (item.Outer != null && item.Outer.Count() > 0)
                {
                    foreach (string str in item.Outer)
                    {
                        if (tmpStr1 != "")
                        {
                            tmpStr1 += "::";
                        }
                        tmpStr1 += str;
                    }
                }
                if (tmpStr1 != "")
                    tmpStr1 = tmpStr1 + "::" + item.Name;
                else tmpStr1 = item.Name;
                base_type_str += "   " + MACRO_CLASS_BASE_CLASS_DEF + "(" + ClassName + ", " + tmpStr1 + ")";
            }
            foreach (InfoType item in Intfs)
            {
                if (base_type_str != "")
                {
                    base_type_str += "\r\n";
                }
                tmpStr1 = "";
                if (item.Outer != null && item.Outer.Count() > 0)
                {
                    foreach (string str in item.Outer)
                    {
                        if (tmpStr1 != "")
                        {
                            tmpStr1 += "::";
                        }
                        tmpStr1 += str;
                    }
                }
                if (tmpStr1 != "")
                    tmpStr1 = tmpStr1 + "::" + item.Name;
                else tmpStr1 = item.Name;
                base_type_str += "   " + MACRO_CLASS_INTERFACE_DEF + "(" + ClassName + ", " + tmpStr1 + ")";
            }

            return base_type_str;
        }

        private string CreateSrc()
        {
            string cls_def = CreateSrc_class_def();
            string cls_constructor_def = CreateSrc_constructor_def();
            string cls_mem_func_def = CreateSrc_mem_func_def();
            string cls_static_mem_func_def = CreateSrc_static_mem_func_def();
            if (cls_constructor_def != "")
                cls_constructor_def += "\r\n\r\n";
            if (cls_mem_func_def != "")
                cls_mem_func_def += "\r\n\r\n";
            if (cls_static_mem_func_def != "")
                cls_static_mem_func_def += "\r\n\r\n";
            return cls_def + "\r\n\r\n"
                 + cls_constructor_def
                 + cls_mem_func_def
                 + cls_static_mem_func_def;
        }

        private string CreateSrc_class_def()
        {
            string ret;
            if (Outer1 == null)
            {
                ret = MACRO_CLASS_DEF + "(" + ClassName + ")";
            }
            else
            {
                if (InNameSpace)
                {
                    if (Outer2 == null)
                    {
                        ret = MACRO_CLASS_IN_NS_1_DEF + "(" + ClassName + ",  " + Outer1 + ")";
                    }
                    else
                    {
                        ret = MACRO_CLASS_IN_NS_2_DEF + "(" + ClassName + ",  " + Outer1 + ", " + Outer2 + ")";
                    }
                }
                else
                {
                    if (Outer2 == null)
                    {
                        ret = MACRO_CLASS_IN_CLS_1_DEF + "(" + ClassName + ",  " + Outer1 + ")";
                    }
                    else
                    {
                        ret = MACRO_CLASS_IN_CLS_2_DEF + "(" + ClassName + ",  " + Outer1 + ", " + Outer2 + ")";
                    }
                }
            }
            return ret;
        }
        private string CreateSrc_constructor_def()
        {
            string ret = "";
            string Params;
            int loop;
            string tmpStr;
            InfoVar var;
            FuncIndexList func_index_list = new FuncIndexList();

            foreach (InfoFunc item in Constructor)
            {
                if (ret != "")
                {
                    ret += "\r\n\r\n";
                }
                if (Outer1 == null)
                {
                    ret += MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_BEG + "(" + func_index_list.GetIndex(item.Name) + ", " + ClassName + ")";
                }
                else
                {
                    if (Outer2 == null)
                    {
                        ret += MACRO_CLASS_CONSTRUCTOR_WRAPPER_1_DEF_BEG + "(" + func_index_list.GetIndex(item.Name) + ", " + ClassName + ", " + Outer1 + ")";
                    }
                    else
                    {
                        ret += MACRO_CLASS_CONSTRUCTOR_WRAPPER_1_DEF_BEG + "(" + func_index_list.GetIndex(item.Name) + ", " + ClassName + ", " + Outer2 + "::" + Outer1 + ")";
                    }
                }
                //check & parameters
                Params = "";
                if (item.Params == null)
                    ret += "\r\n    " + MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_PROC_CHECK + "(0)\r\n";
                else
                {
                    ret += "\r\n    " + MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_PROC_CHECK + "(" + item.Params.Count() + ")\r\n";
                    for (loop = 0; loop < item.Params.Count(); ++loop)
                    {
                        if (Params != "")
                        {
                            Params += ",\r\n";
                        }
                        var = item.Params[loop];
                        if (var.infoType.Outer == null)
                        {
                            Params += "		" + MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_DP_PARAM + "(" + loop + ", " + var.infoType.Name + ")";
                        }
                        else
                        {
                            tmpStr = "";
                            foreach (string it in var.infoType.Outer)
                            {
                                if (tmpStr != "")
                                {
                                    tmpStr += "::";
                                }
                                tmpStr += it;
                            }
                            Params += "		" + MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_DP_PARAM + "(" + loop + ", " + tmpStr + "::" + var.infoType.Name + ")";
                        }
                    }
                }
                if (Params != "")
                {
                    ret += "    " + MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_NEW_OBJ + "(" + ClassName + ")\r\n	(\r\n" + Params + "\r\n	);\r\n" + MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_END + "()";
                }
                else
                {
                    ret += "    " + MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_NEW_OBJ + "(" + ClassName + ");\r\n" + MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_END + "()";
                }
            }
            return ret;
        }
        private string CreateSrc_mem_func_def()
        {
            string ret = "";
            string Params;
            int loop;
            string tmpStr;
            InfoVar var;
            FuncIndexList func_index_list = new FuncIndexList();

            foreach (InfoFunc item in MemFunc)
            {
                if (ret != "")
                {
                    ret += "\r\n\r\n";
                }
                if (Outer1 == null)
                {
                    ret += MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_BEG + "(" + func_index_list.GetIndex(item.Name) + ", " + item.Name + ", " + ClassName + ")";
                }
                else
                {
                    if (Outer2 == null)
                    {
                        ret += MACRO_CLASS_MEM_FUNC_WRAPPER_1_DEF_BEG + "(" + func_index_list.GetIndex(item.Name) + ", " + item.Name + ", " + ClassName + ", " + Outer1 + ")";
                    }
                    else
                    {
                        ret += MACRO_CLASS_MEM_FUNC_WRAPPER_1_DEF_BEG + "(" + func_index_list.GetIndex(item.Name) + ", " + item.Name + ", " + ClassName + ", " + Outer2 + "::" + Outer1 + ")";
                    }
                }
                //check & parameters
                Params = "";
                if (item.Params == null)
                    ret += "\r\n    " + MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_PROC_CHECK + "(0)\r\n";
                else
                {
                    ret += "\r\n    " + MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_PROC_CHECK + "(" + item.Params.Count() + ")\r\n";
                    for (loop = 0; loop < item.Params.Count(); ++loop)
                    {
                        if (Params != "")
                        {
                            Params += ",\r\n";
                        }
                        var = item.Params[loop];
                        if (var.infoType.Outer == null)
                        {
                            Params += "		" + MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_DP_PARAM + "(" + loop + ", " + var.infoType.Name + ")";
                        }
                        else
                        {
                            tmpStr = "";
                            foreach (string it in var.infoType.Outer)
                            {
                                if (tmpStr != "")
                                {
                                    tmpStr += "::";
                                }
                                tmpStr += it;
                            }
                            Params += "		" + MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_DP_PARAM + "(" + loop + ", " + tmpStr + "::" + var.infoType.Name + ")";
                        }
                    }
                }
                if (item.Ret != null)
                {
                    tmpStr = "";
                    if (item.Ret.Outer != null)
                    {
                        foreach (string it in item.Ret.Outer)
                        {
                            if (tmpStr != "")
                            {
                                tmpStr += "::";
                            }
                            tmpStr += it;
                        }
                    }
                    if (tmpStr != "") tmpStr += "::";
                    tmpStr += item.Ret.Name;
                    ret += "    " + MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_DP_RET + "(" + tmpStr + ")\r\n    = ";
                }
                if (Params != "")
                {
                    ret += MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_THIS + "(" + ClassName + ")->" + item.Name + "\r\n	(\r\n" + Params + "\r\n	);\r\n" + MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_END + "()";
                }
                else
                {
                    ret += MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_THIS + "(" + ClassName + ")->" + item.Name + "();\r\n" + MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_END + "()";
                }
            }
            return ret;
        }
        private string CreateSrc_static_mem_func_def()
        {
            string ret = "";
            string Params;
            int loop;
            string tmpStr;
            InfoVar var;
            FuncIndexList func_index_list = new FuncIndexList();

            foreach (InfoFunc item in StaticMemFunc)
            {
                if (ret != "")
                {
                    ret += "\r\n\r\n";
                }
                if (Outer1 == null)
                {
                    ret += MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_BEG + "(" + func_index_list.GetIndex(item.Name) + ", " + item.Name + ", " + ClassName + ")";
                }
                else
                {
                    if (Outer2 == null)
                    {
                        ret += MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_1_DEF_BEG + "(" + func_index_list.GetIndex(item.Name) + ", " + item.Name + ", " + ClassName + ", " + Outer1 + ")";
                    }
                    else
                    {
                        ret += MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_1_DEF_BEG + "(" + func_index_list.GetIndex(item.Name) + ", " + item.Name + ", " + ClassName + ", " + Outer2 + "::" + Outer1 + ")";
                    }
                }
                //check & parameters
                Params = "";
                if (item.Params == null)
                    ret += "\r\n    " + MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_PROC_CHECK + "(0)\r\n";
                else
                {
                    ret += "\r\n    " + MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_PROC_CHECK + "(" + item.Params.Count() + ")\r\n";
                    for (loop = 0; loop < item.Params.Count(); ++loop)
                    {
                        if (Params != "")
                        {
                            Params += ",\r\n";
                        }
                        var = item.Params[loop];
                        if (var.infoType.Outer == null)
                        {
                            Params += "		" + MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_DP_PARAM + "(" + loop + ", " + var.infoType.Name + ")";
                        }
                        else
                        {
                            tmpStr = "";
                            foreach (string it in var.infoType.Outer)
                            {
                                if (tmpStr != "")
                                {
                                    tmpStr += "::";
                                }
                                tmpStr += it;
                            }
                            Params += "		" + MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_DP_PARAM + "(" + loop + ", " + tmpStr + "::" + var.infoType.Name + ")";
                        }
                    }
                }
                if (item.Ret != null)
                {
                    tmpStr = "";
                    if (item.Ret.Outer != null)
                    {
                        foreach (string it in item.Ret.Outer)
                        {
                            if (tmpStr != "")
                            {
                                tmpStr += "::";
                            }
                            tmpStr += it;
                        }
                    }
                    if (tmpStr != "") tmpStr += "::";
                    tmpStr += item.Ret.Name;
                    ret += "    " + MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_DP_RET + "(" + tmpStr + ")\r\n    = ";
                }
                if (Params != "")
                {
                    ret += item.Name + "\r\n	(\r\n" + Params + "\r\n	);\r\n" + MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_END + "()";
                }
                else
                {
                    ret += item.Name + "();\r\n" + MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_END + "()";
                }
            }
            return ret;
        }

        public string ClassName = null;
        public string Outer1 = null;
        public string Outer2 = null;
        public bool InNameSpace = true;
        public List<InfoType> BaseTypes = new List<InfoType>();
        public List<InfoType> Intfs = new List<InfoType>();
        public List<InfoVar> MemVar = new List<InfoVar>();
        public List<InfoVar> StaticMemVar = new List<InfoVar>();
        public List<InfoFunc> MemFunc = new List<InfoFunc>();
        public List<InfoFunc> StaticMemFunc = new List<InfoFunc>();
        public List<InfoFunc> Constructor = new List<InfoFunc>();

        class FuncIndex
        {
            public string Name;
            public int Index;
        }
        class FuncIndexList : List<FuncIndex>
        {
            public int GetIndex(string FuncName)
            {
                if (FuncName == null) return -1;
                foreach (FuncIndex item in this)
                {
                    if (item.Name == FuncName)
                    {
                        return ++item.Index;
                    }
                }
                FuncIndex fi = new FuncIndex();
                fi.Name = FuncName;
                fi.Index = 0;
                this.Add(fi);
                return 0;
            }
        }

        /*.h*/
        private const string MACRO_CLASS_DEC_BEGIN = "MD_CLASS_TYPE_DECLARE_BEGIN";
        private const string MACRO_CLASS_DEC_DETAIL = "MD_CLASS_TYPE_DECLARE_DETAIL";
        private const string MACRO_CLASS_DEC_END = "MD_CLASS_TYPE_DECLARE_END";

        private const string MACRO_CLASS_BASE_CLASS_DEF = "MD_CLASS_TYPE_BASE_CLASS_DEF";

        private const string MACRO_CLASS_INTERFACE_DEF = "MD_CLASS_TYPE_INTERFACE_DEF";

        private const string MACRO_CLASS_CONS_WRAPPER_DEC = "MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE";
        private const string MACRO_CLASS_CONS_DEF = "MD_CLASS_TYPE_CONSTRUCTOR_DEF";
        private const string MACRO_CLASS_CONS_PARAM_DEF = "MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF";

        private const string MACRO_CLASS_MEM_FUNC_WRAPPER_DEC = "MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE";
        private const string MACRO_CLASS_MEM_FUNC_DEF = "MD_CLASS_TYPE_MEMBER_FUNC_DEF";
        private const string MACRO_CLASS_MEM_FUNC_PARAM_DEF = "MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF";
        private const string MACRO_CLASS_MEM_FUNC_RET_DEF = "MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF";

        private const string MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEC = "MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE";
        private const string MACRO_CLASS_STATIC_MEM_FUNC_DEF = "MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF";
        private const string MACRO_CLASS_STATIC_MEM_FUNC_PARAM_DEF = "MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF";
        private const string MACRO_CLASS_STATIC_MEM_FUNC_RET_DEF = "MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF";

        private const string MACRO_CLASS_MEM_VAR_DEF = "MD_CLASS_TYPE_MEMBER_VAR_DEF";

        private const string MACRO_CLASS_STATIC_MEM_VAR_DEF = "MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF";

        /*.meo*/
        private const string MACRO_CLASS_DEF = "MD_CLASS_TYPE_DEF";
        private const string MACRO_CLASS_IN_CLS_1_DEF = "MD_CLASS_TYPE_IN_CLS_1_DEF";
        private const string MACRO_CLASS_IN_CLS_2_DEF = "MD_CLASS_TYPE_IN_CLS_2_DEF";
        private const string MACRO_CLASS_IN_NS_1_DEF = "MD_CLASS_TYPE_IN_NS_1_DEF";
        private const string MACRO_CLASS_IN_NS_2_DEF = "MD_CLASS_TYPE_IN_NS_2_DEF";

        private const string MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_BEG = "MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_BEGIN";
        private const string MACRO_CLASS_CONSTRUCTOR_WRAPPER_1_DEF_BEG = "MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_1_DEF_BEGIN";
        private const string MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_PROC_CHECK = "MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_PROC_CHECK";
        private const string MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_DP_PARAM = "MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_DP_PARAM";
        private const string MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_NEW_OBJ = "MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_NEW_OBJ";
        private const string MACRO_CLASS_CONSTRUCTOR_WRAPPER_DEF_END = "MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_END";

        private const string MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_BEG = "MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN";
        private const string MACRO_CLASS_MEM_FUNC_WRAPPER_1_DEF_BEG = "MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_1_DEF_BEGIN";
        private const string MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_PROC_CHECK = "MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK";
        private const string MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_THIS = "MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_THIS";
        private const string MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_DP_PARAM = "MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM";
        private const string MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_DP_RET = "MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET";
        private const string MACRO_CLASS_MEM_FUNC_WRAPPER_DEF_END = "MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_END";

        private const string MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_BEG = "MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_BEGIN";
        private const string MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_1_DEF_BEG = "MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_1_DEF_BEGIN";
        private const string MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_PROC_CHECK = "MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK";
        private const string MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_DP_PARAM = "MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM";
        private const string MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_DP_RET = "MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_DP_RET";
        private const string MACRO_CLASS_STATIC_MEM_FUNC_WRAPPER_DEF_END = "MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_END";
    }
}
