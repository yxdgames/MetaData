#pragma once

#include "..\CommonFunction.h"
#include "..\..\..\Codes\MetaData\include\MetaData.h"
#include "..\..\..\Codes\MetaData\include\MetaDataVariable.h"
#include "..\..\..\Codes\MetaData\include\MetaDataCustomTypeMemberVar.h"
#include "..\..\..\Codes\MetaData\include\MetaDataFunction.h"

namespace MetaDataView {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// CfrmMain 摘要
	/// </summary>
	public ref class CfrmMain : public System::Windows::Forms::Form
	{
	public:
		CfrmMain(void) : m_hCurModule(nullptr)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	private:
		void InitClassView(const CMetaData &md)
		{
			tvClass->BeginUpdate();
			try
			{
				tvClass->Nodes->Clear();
				DoInitClassView(md, "Global Space", tvClass->Nodes);
				tvClass->ExpandAll();
				if (tvClass->Nodes->Count)
				{
					tvClass->SelectedNode = tvClass->Nodes[0];
					tvClass->TopNode = tvClass->Nodes[0];
				}
			}
			finally
			{
				tvClass->EndUpdate();
			}
		}
		void DoInitClassView(const CMetaData &md, String ^name, TreeNodeCollection ^Nodes)
		{
			if (!Nodes) return;
			const CMetaData *pMD;
			TreeNode ^tree_node;
			tree_node = Nodes->Add(name ? name : gcnew String(md.GetName()));
			tree_node->Tag = gcnew IntPtr(reinterpret_cast<void*>(const_cast<CMetaData*>(&md)));
			for (unsigned int i = 0; i < md.GetChildrenCount(); ++i)
			{
				pMD = md.GetChild(i);
				switch (pMD->GetTypeID())
				{
				case D_META_DATA_TYPE_ID_GLOBAL_SPACE:
				case D_META_DATA_TYPE_ID_NAME_SPACE:
				case D_META_DATA_TYPE_ID_CLASS_TYPE:
				case D_META_DATA_TYPE_ID_INTERFACE:
				case D_META_DATA_TYPE_ID_INNER_TYPE:
					DoInitClassView(*pMD, nullptr, tree_node->Nodes);
					break;
				default:
					break;
				}
			}
		}
		void InitDetailView(CMetaData *pMD)
		{
			dtDetail->Tables[0]->BeginLoadData();
			try
			{
				dtDetail->Tables[0]->Clear();
				lvMDDetail->Items->Clear();
				if (!pMD) return;
				String ^str, ^str1;
				const CMetaData *pChild;
				const CMetaDataVariable *pMDVar;
				const CMetaDataCustomTypeMemberVar *pMDMVar;
				const CMetaDataFunction *pMDFunc;
				unsigned int index;
				int idx;
				String ^strMember, ^strRemark;
				DataRow ^pRow;
				ListViewItem ^vitem;
				for (unsigned int i = 0; i < pMD->GetChildrenCount(); ++i)
				{
					pChild = pMD->GetChild(i);
					strMember = strRemark = nullptr;
					switch(pChild->GetTypeID())
					{
					case D_META_DATA_TYPE_ID_VARIABLE:
						pMDVar = reinterpret_cast<const CMetaDataVariable *>(pChild);
						if (pMD->GetTypeID() == D_META_DATA_TYPE_ID_CLASS_TYPE
							|| pMD->GetTypeID() == D_META_DATA_TYPE_ID_INTERFACE)
						{
							strMember = "static " + gcnew String(pMDVar->GetMDType()->GetName()) + " ";
							str1 = "";
							for (idx = 0; idx < pMDVar->GetPtrLevel(); ++idx)
							{
								str1 += "*";
							}
							strMember += str1 + gcnew String(pMDVar->GetName());
							strRemark = "静态成员变量";
						}
						else
						{
							strMember = gcnew String(pMDVar->GetMDType()->GetName()) + " ";
							str1 = "";
							for (idx = 0; idx < pMDVar->GetPtrLevel(); ++idx)
							{
								str1 += "*";
							}
							strMember += str1 + gcnew String(pMDVar->GetName());
							strRemark = "变量";
						}

						pRow = dtDetail->Tables[0]->NewRow();
						pRow[dtDetail->Tables[0]->Columns["member"]] = strMember;
						pRow[dtDetail->Tables[0]->Columns["remark"]] = strRemark;
						dtDetail->Tables[0]->Rows->Add(pRow);

						vitem = gcnew ListViewItem(strMember);
						vitem->SubItems->Add(strRemark);
						lvMDDetail->Items->Add(vitem);
						break;
					case D_META_DATA_TYPE_ID_CUSTOM_TYPE_MEMBER_VAR:
						pMDMVar = reinterpret_cast<const CMetaDataCustomTypeMemberVar *>(pChild);
						strMember = gcnew String(pMDMVar->GetMDType()->GetName()) + " ";
						str1 = "";
						for (idx = 0; idx < pMDMVar->GetPtrLevel(); ++idx)
						{
							str1 += "*";
						}
						strMember += str1 + gcnew String(pMDMVar->GetName());
						strRemark = "成员变量";

						pRow = dtDetail->Tables[0]->NewRow();
						pRow[dtDetail->Tables[0]->Columns["member"]] = strMember;
						pRow[dtDetail->Tables[0]->Columns["remark"]] = strRemark;
						dtDetail->Tables[0]->Rows->Add(pRow);

						vitem = gcnew ListViewItem(strMember);
						vitem->SubItems->Add(strRemark);
						lvMDDetail->Items->Add(vitem);
						break;
					case D_META_DATA_TYPE_ID_FUNCTION:
						pMDFunc = reinterpret_cast<const CMetaDataFunction *>(pChild);
						if ((pMD->GetTypeID() == D_META_DATA_TYPE_ID_CLASS_TYPE || pMD->GetTypeID() == D_META_DATA_TYPE_ID_INTERFACE))
						{
							if (strcmp(pMD->GetName(), pMDFunc->GetName()) == 0)
							{
								str = "";
								strRemark = "构造函数";
							}
							else if (pMDFunc->GetName()[0] == '~' && strcmp(pMD->GetName(), pMDFunc->GetName() + 1) == 0)
							{
								str = "";
								strRemark = "析构函数";
							}
							else
							{
								if (pMDFunc->GetParamCount() > 0 && strcmp(pMDFunc->GetParam(0)->GetName(), "this") == 0)
								{
									str = "";
									strRemark = "成员函数";
								}
								else
								{
									str = "static ";
									strRemark = "静态成员函数";
								}
								if (pMDFunc->ReturnIsVoid())
									str += "void ";
								else
								{
									str += gcnew String(pMDFunc->GetReturnInfo()->GetMDType()->GetName()) + " ";
									for (idx = 0; idx < pMDFunc->GetReturnInfo()->GetPtrLevel(); ++idx)
									{
										str += "*";
									}
								}
							}
						}
						else
						{
							if (pMDFunc->ReturnIsVoid())
								str = "void ";
							else
							{
								str = gcnew String(pMDFunc->GetReturnInfo()->GetMDType()->GetName()) + " ";
								for (idx = 0; idx < pMDFunc->GetReturnInfo()->GetPtrLevel(); ++idx)
								{
									str += "*";
								}
							}
							strRemark = "函数";
						}
						str += gcnew String(pMDFunc->GetName()) + "(";
						str1 = "";
						for (index = 0; index < pMDFunc->GetParamCount(); ++index)
						{
							if (strcmp(pMDFunc->GetParam(index)->GetName(), "this") == 0) continue;
							if (str1 != "") str1 += ", ";
							str1 += gcnew String(pMDFunc->GetParam(index)->GetMDType()->GetName())
								+ " ";
							for (idx = 0; idx < pMDFunc->GetParam(index)->GetPtrLevel(); ++idx)
							{
								str1 += "*";
							}
							str1 += gcnew String(pMDFunc->GetParam(index)->GetName());
						}
						if (str1 != "")
						{
							str += str1;
						}
						else
						{
							str += "void";
						}
						str += ")";
						strMember = str;

						pRow = dtDetail->Tables[0]->NewRow();
						pRow[dtDetail->Tables[0]->Columns["member"]] = strMember;
						pRow[dtDetail->Tables[0]->Columns["remark"]] = strRemark;
						dtDetail->Tables[0]->Rows->Add(pRow);

						vitem = gcnew ListViewItem(strMember);
						vitem->SubItems->Add(strRemark);
						lvMDDetail->Items->Add(vitem);
						break;
					default:
						break;
					}
				}
			}
			finally
			{
				dtDetail->Tables[0]->EndLoadData();
			}
		}
		HMODULE LoadModuleHandle(String ^ModuleName)
		{
			FreeModuleHandle();
			pin_ptr<const wchar_t> pStr = PtrToStringChars(ModuleName);
			m_hCurModule = ::LoadLibrary(pStr);
			return m_hCurModule;
		}
		void FreeModuleHandle(void)
		{
			if (m_hCurModule)
			{
				::FreeLibrary(m_hCurModule);
				m_hCurModule = nullptr;
			}
		}
	private: System::Data::DataSet^  dtDetail;
	private: System::Data::DataTable^  dataTable1;
	private: System::Data::DataColumn^  dataColumn1;
	private: System::Data::DataColumn^  dataColumn2;
private: System::Windows::Forms::ListView^ lvMDDetail;

private: System::Windows::Forms::ColumnHeader^ colMember;
private: System::Windows::Forms::ColumnHeader^ colRemark;







	private:
		HMODULE m_hCurModule;
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~CfrmMain()
		{
			if (components)
			{
				delete components;
			}

			FreeModuleHandle();
		}
	private: System::Windows::Forms::TreeView^  tvClass;
	private: System::Windows::Forms::Splitter^  splitter1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiFile;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiViewMetaData;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiViewMDKernel;
	protected: 

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->tvClass = (gcnew System::Windows::Forms::TreeView());
			this->splitter1 = (gcnew System::Windows::Forms::Splitter());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->lvMDDetail = (gcnew System::Windows::Forms::ListView());
			this->colMember = (gcnew System::Windows::Forms::ColumnHeader());
			this->colRemark = (gcnew System::Windows::Forms::ColumnHeader());
			this->dtDetail = (gcnew System::Data::DataSet());
			this->dataTable1 = (gcnew System::Data::DataTable());
			this->dataColumn1 = (gcnew System::Data::DataColumn());
			this->dataColumn2 = (gcnew System::Data::DataColumn());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->tsmiFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiViewMetaData = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiViewMDKernel = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dtDetail))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTable1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tvClass
			// 
			this->tvClass->Dock = System::Windows::Forms::DockStyle::Left;
			this->tvClass->Location = System::Drawing::Point(0, 28);
			this->tvClass->Margin = System::Windows::Forms::Padding(4);
			this->tvClass->Name = L"tvClass";
			this->tvClass->Size = System::Drawing::Size(305, 537);
			this->tvClass->TabIndex = 0;
			this->tvClass->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CfrmMain::tvClass_AfterSelect);
			// 
			// splitter1
			// 
			this->splitter1->Location = System::Drawing::Point(305, 28);
			this->splitter1->Margin = System::Windows::Forms::Padding(4);
			this->splitter1->Name = L"splitter1";
			this->splitter1->Size = System::Drawing::Size(4, 537);
			this->splitter1->TabIndex = 1;
			this->splitter1->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->lvMDDetail);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(309, 28);
			this->panel1->Margin = System::Windows::Forms::Padding(4);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(774, 537);
			this->panel1->TabIndex = 2;
			// 
			// lvMDDetail
			// 
			this->lvMDDetail->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->colMember, this->colRemark });
			this->lvMDDetail->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lvMDDetail->FullRowSelect = true;
			this->lvMDDetail->GridLines = true;
			this->lvMDDetail->HideSelection = false;
			this->lvMDDetail->Location = System::Drawing::Point(0, 0);
			this->lvMDDetail->Name = L"lvMDDetail";
			this->lvMDDetail->Size = System::Drawing::Size(774, 537);
			this->lvMDDetail->TabIndex = 0;
			this->lvMDDetail->UseCompatibleStateImageBehavior = false;
			this->lvMDDetail->View = System::Windows::Forms::View::Details;
			// 
			// colMember
			// 
			this->colMember->Text = L"成员";
			this->colMember->Width = 456;
			// 
			// colRemark
			// 
			this->colRemark->Text = L"说明";
			this->colRemark->Width = 74;
			// 
			// dtDetail
			// 
			this->dtDetail->DataSetName = L"NewDataSet";
			this->dtDetail->Tables->AddRange(gcnew cli::array< System::Data::DataTable^  >(1) { this->dataTable1 });
			// 
			// dataTable1
			// 
			this->dataTable1->Columns->AddRange(gcnew cli::array< System::Data::DataColumn^  >(2) { this->dataColumn1, this->dataColumn2 });
			this->dataTable1->TableName = L"tbDetail";
			// 
			// dataColumn1
			// 
			this->dataColumn1->Caption = L"成员";
			this->dataColumn1->ColumnName = L"member";
			// 
			// dataColumn2
			// 
			this->dataColumn2->Caption = L"备注";
			this->dataColumn2->ColumnName = L"remark";
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->tsmiFile });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1083, 28);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// tsmiFile
			// 
			this->tsmiFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->tsmiViewMetaData,
					this->tsmiViewMDKernel
			});
			this->tsmiFile->Name = L"tsmiFile";
			this->tsmiFile->Size = System::Drawing::Size(53, 24);
			this->tsmiFile->Text = L"文件";
			// 
			// tsmiViewMetaData
			// 
			this->tsmiViewMetaData->Name = L"tsmiViewMetaData";
			this->tsmiViewMetaData->Size = System::Drawing::Size(197, 26);
			this->tsmiViewMetaData->Text = L"查看元数据...";
			this->tsmiViewMetaData->Click += gcnew System::EventHandler(this, &CfrmMain::tsmiViewMetaData_Click);
			// 
			// tsmiViewMDKernel
			// 
			this->tsmiViewMDKernel->Name = L"tsmiViewMDKernel";
			this->tsmiViewMDKernel->Size = System::Drawing::Size(197, 26);
			this->tsmiViewMDKernel->Text = L"核心元数据视图";
			this->tsmiViewMDKernel->Click += gcnew System::EventHandler(this, &CfrmMain::tsmiViewMDKernel_Click);
			// 
			// CfrmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1083, 565);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->splitter1);
			this->Controls->Add(this->tvClass);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"CfrmMain";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"元数据";
			this->Shown += gcnew System::EventHandler(this, &CfrmMain::CfrmMain_Shown);
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dtDetail))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTable1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void CfrmMain_Shown(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void tsmiViewMetaData_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Windows::Forms::OpenFileDialog dlgOpen;
			 dlgOpen.Filter = "动态库(*.dll)|*.dll|全部文件(*.*)|*.*";
			 if (dlgOpen.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 HMODULE hModule = LoadModuleHandle(dlgOpen.FileName);
				 if (hModule)
				 {
					 typedef const void *(__stdcall *TpFunc)(void);
					 TpFunc pFunc;
					 pFunc = reinterpret_cast<TpFunc>(::GetProcAddress(hModule, "GetMetaDataGlobalSpace"));
					 if (pFunc)
					 {
						InitClassView(*reinterpret_cast<const CMetaData*>(pFunc()));
					 }
					 else throw gcnew Exception("无法解析元数据！");
				 }
				 else throw gcnew Exception("载入DLL失败！");
			 }
		 }
private: System::Void tsmiViewMDKernel_Click(System::Object^  sender, System::EventArgs^  e) {
			 InitClassView(*MetaDataGlobalSpace());
		 }
private: System::Void tvClass_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 IntPtr pointer = static_cast<IntPtr>(e->Node->Tag);
			 CMetaData *pMD = reinterpret_cast<CMetaData*>((static_cast<void*>(pointer)));
			 InitDetailView(pMD);
		 }
};
}
