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
	using namespace DevExpress::XtraGrid::Views::Grid;

	using DevExpress::XtraGrid::Views::Grid::ViewInfo::GridGroupRowInfo;

	/// <summary>
	/// CfrmMain ժҪ
	/// </summary>
	public ref class CfrmMain : public System::Windows::Forms::Form
	{
	public:
		CfrmMain(void) : m_hCurModule(nullptr)
		{
			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
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
			if (name)
				tree_node = Nodes->Add(name);
			else tree_node = Nodes->Add(gcnew String(md.GetName()));
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
				if (!pMD) return;
				String ^str, ^str1, ^str_filter1;
				const CMetaData *pChild;
				const CMetaDataVariable *pMDVar;
				const CMetaDataCustomTypeMemberVar *pMDMVar;
				const CMetaDataFunction *pMDFunc;
				int index, idx;
				DataRow ^pRow;
				for (unsigned int i = 0; i < pMD->GetChildrenCount(); ++i)
				{
					pChild = pMD->GetChild(i);
					switch(pChild->GetTypeID())
					{
					case D_META_DATA_TYPE_ID_VARIABLE:
						pMDVar = reinterpret_cast<const CMetaDataVariable *>(pChild);
						pRow = dtDetail->Tables[0]->NewRow();
						if (pMD->GetTypeID() == D_META_DATA_TYPE_ID_CLASS_TYPE
							|| pMD->GetTypeID() == D_META_DATA_TYPE_ID_INTERFACE)
						{
							pRow[dtDetail->Tables[0]->Columns["member"]] = "static " + gcnew String(pMDVar->GetMDType()->GetName()) + " ";
							str1 = "";
							for (idx = 0; idx < pMDVar->GetPtrLevel(); ++idx)
							{
								str1 += "*";
							}
							pRow[dtDetail->Tables[0]->Columns["member"]] += str1 + gcnew String(pMDVar->GetName());

							pRow[dtDetail->Tables[0]->Columns["filter1"]] = "��̬��Ա����";
						}
						else
						{
							pRow[dtDetail->Tables[0]->Columns["member"]] = gcnew String(pMDVar->GetMDType()->GetName()) + " ";
							str1 = "";
							for (idx = 0; idx < pMDVar->GetPtrLevel(); ++idx)
							{
								str1 += "*";
							}
							pRow[dtDetail->Tables[0]->Columns["member"]] += str1 + gcnew String(pMDVar->GetName());
							pRow[dtDetail->Tables[0]->Columns["filter1"]] = "����";
						}
						dtDetail->Tables[0]->Rows->Add(pRow);
						break;
					case D_META_DATA_TYPE_ID_CUSTOM_TYPE_MEMBER_VAR:
						pMDMVar = reinterpret_cast<const CMetaDataCustomTypeMemberVar *>(pChild);
						pRow = dtDetail->Tables[0]->NewRow();
						pRow[dtDetail->Tables[0]->Columns["member"]] = gcnew String(pMDMVar->GetMDType()->GetName()) + " ";
						str1 = "";
						for (idx = 0; idx < pMDMVar->GetPtrLevel(); ++idx)
						{
							str1 += "*";
						}
						pRow[dtDetail->Tables[0]->Columns["member"]] += str1 + gcnew String(pMDMVar->GetName());
						pRow[dtDetail->Tables[0]->Columns["filter1"]] = "��Ա����";
						dtDetail->Tables[0]->Rows->Add(pRow);
						break;
					case D_META_DATA_TYPE_ID_FUNCTION:
						pMDFunc = reinterpret_cast<const CMetaDataFunction *>(pChild);
						if ((pMD->GetTypeID() == D_META_DATA_TYPE_ID_CLASS_TYPE || pMD->GetTypeID() == D_META_DATA_TYPE_ID_INTERFACE))
						{
							if (strcmp(pMD->GetName(), pMDFunc->GetName()) == 0)
							{
								str = "";
								str_filter1 = "���캯��";
							}
							else if (pMDFunc->GetName()[0] == '~' && strcmp(pMD->GetName(), pMDFunc->GetName() + 1) == 0)
							{
								str = "";
								str_filter1 = "��������";
							}
							else
							{
								if (pMDFunc->GetParamCount() > 0 && strcmp(pMDFunc->GetParam(0)->GetName(), "this") == 0)
								{
									str = "";
									str_filter1 = "��Ա����";
								}
								else
								{
									str = "static ";
									str_filter1 = "��̬��Ա����";
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
							str_filter1 = "����";
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
						pRow = dtDetail->Tables[0]->NewRow();
						pRow[dtDetail->Tables[0]->Columns["member"]] = str;
						pRow[dtDetail->Tables[0]->Columns["filter1"]] = str_filter1;
						dtDetail->Tables[0]->Rows->Add(pRow);
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
	private: DevExpress::XtraGrid::GridControl^  grdcDetail;
	private: DevExpress::XtraGrid::Views::Grid::GridView^  grdvDetail;
	private: System::Data::DataSet^  dtDetail;
	private: System::Data::DataTable^  dataTable1;
	private: System::Data::DataColumn^  dataColumn1;





	private: DevExpress::XtraGrid::Columns::GridColumn^  gridColumn1;
private: System::Data::DataColumn^  dataColumn2;
private: DevExpress::XtraGrid::Columns::GridColumn^  gridColumn2;




	private:
		HMODULE m_hCurModule;
	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
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
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			this->tvClass = (gcnew System::Windows::Forms::TreeView());
			this->splitter1 = (gcnew System::Windows::Forms::Splitter());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->grdcDetail = (gcnew DevExpress::XtraGrid::GridControl());
			this->dtDetail = (gcnew System::Data::DataSet());
			this->dataTable1 = (gcnew System::Data::DataTable());
			this->dataColumn1 = (gcnew System::Data::DataColumn());
			this->dataColumn2 = (gcnew System::Data::DataColumn());
			this->grdvDetail = (gcnew DevExpress::XtraGrid::Views::Grid::GridView());
			this->gridColumn1 = (gcnew DevExpress::XtraGrid::Columns::GridColumn());
			this->gridColumn2 = (gcnew DevExpress::XtraGrid::Columns::GridColumn());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->tsmiFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiViewMetaData = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiViewMDKernel = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->grdcDetail))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dtDetail))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataTable1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->grdvDetail))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tvClass
			// 
			this->tvClass->Dock = System::Windows::Forms::DockStyle::Left;
			this->tvClass->Location = System::Drawing::Point(0, 25);
			this->tvClass->Name = L"tvClass";
			this->tvClass->Size = System::Drawing::Size(230, 427);
			this->tvClass->TabIndex = 0;
			this->tvClass->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CfrmMain::tvClass_AfterSelect);
			// 
			// splitter1
			// 
			this->splitter1->Location = System::Drawing::Point(230, 25);
			this->splitter1->Name = L"splitter1";
			this->splitter1->Size = System::Drawing::Size(3, 427);
			this->splitter1->TabIndex = 1;
			this->splitter1->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->grdcDetail);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(233, 25);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(579, 427);
			this->panel1->TabIndex = 2;
			// 
			// grdcDetail
			// 
			this->grdcDetail->Cursor = System::Windows::Forms::Cursors::Default;
			this->grdcDetail->DataMember = L"tbDetail";
			this->grdcDetail->DataSource = this->dtDetail;
			this->grdcDetail->Dock = System::Windows::Forms::DockStyle::Fill;
			this->grdcDetail->Location = System::Drawing::Point(0, 0);
			this->grdcDetail->MainView = this->grdvDetail;
			this->grdcDetail->Name = L"grdcDetail";
			this->grdcDetail->Size = System::Drawing::Size(579, 427);
			this->grdcDetail->TabIndex = 0;
			this->grdcDetail->ViewCollection->AddRange(gcnew cli::array< DevExpress::XtraGrid::Views::Base::BaseView^  >(1) {this->grdvDetail});
			// 
			// dtDetail
			// 
			this->dtDetail->DataSetName = L"NewDataSet";
			this->dtDetail->Tables->AddRange(gcnew cli::array< System::Data::DataTable^  >(1) {this->dataTable1});
			// 
			// dataTable1
			// 
			this->dataTable1->Columns->AddRange(gcnew cli::array< System::Data::DataColumn^  >(2) {this->dataColumn1, this->dataColumn2});
			this->dataTable1->TableName = L"tbDetail";
			// 
			// dataColumn1
			// 
			this->dataColumn1->Caption = L"��Ա";
			this->dataColumn1->ColumnName = L"member";
			// 
			// dataColumn2
			// 
			this->dataColumn2->Caption = L"����1";
			this->dataColumn2->ColumnName = L"filter1";
			// 
			// grdvDetail
			// 
			this->grdvDetail->Columns->AddRange(gcnew cli::array< DevExpress::XtraGrid::Columns::GridColumn^  >(2) {this->gridColumn1, 
				this->gridColumn2});
			this->grdvDetail->GridControl = this->grdcDetail;
			this->grdvDetail->GroupCount = 1;
			this->grdvDetail->Name = L"grdvDetail";
			this->grdvDetail->OptionsBehavior->ReadOnly = true;
			this->grdvDetail->OptionsView->ShowGroupPanel = false;
			this->grdvDetail->SortInfo->AddRange(gcnew cli::array< DevExpress::XtraGrid::Columns::GridColumnSortInfo^  >(1) {(gcnew DevExpress::XtraGrid::Columns::GridColumnSortInfo(this->gridColumn2, 
				DevExpress::Data::ColumnSortOrder::Ascending))});
			this->grdvDetail->CustomDrawGroupRow += gcnew DevExpress::XtraGrid::Views::Base::RowObjectCustomDrawEventHandler(this, &CfrmMain::grdvDetail_CustomDrawGroupRow);
			// 
			// gridColumn1
			// 
			this->gridColumn1->Caption = L"��Ա";
			this->gridColumn1->FieldName = L"member";
			this->gridColumn1->Name = L"gridColumn1";
			this->gridColumn1->OptionsColumn->AllowEdit = false;
			this->gridColumn1->Visible = true;
			this->gridColumn1->VisibleIndex = 0;
			// 
			// gridColumn2
			// 
			this->gridColumn2->Caption = L"����1";
			this->gridColumn2->FieldName = L"filter1";
			this->gridColumn2->Name = L"gridColumn2";
			this->gridColumn2->OptionsColumn->AllowEdit = false;
			this->gridColumn2->Visible = true;
			this->gridColumn2->VisibleIndex = 1;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsmiFile});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(812, 25);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// tsmiFile
			// 
			this->tsmiFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tsmiViewMetaData, 
				this->tsmiViewMDKernel});
			this->tsmiFile->Name = L"tsmiFile";
			this->tsmiFile->Size = System::Drawing::Size(44, 21);
			this->tsmiFile->Text = L"�ļ�";
			// 
			// tsmiViewMetaData
			// 
			this->tsmiViewMetaData->Name = L"tsmiViewMetaData";
			this->tsmiViewMetaData->Size = System::Drawing::Size(160, 22);
			this->tsmiViewMetaData->Text = L"�鿴Ԫ����...";
			this->tsmiViewMetaData->Click += gcnew System::EventHandler(this, &CfrmMain::tsmiViewMetaData_Click);
			// 
			// tsmiViewMDKernel
			// 
			this->tsmiViewMDKernel->Name = L"tsmiViewMDKernel";
			this->tsmiViewMDKernel->Size = System::Drawing::Size(160, 22);
			this->tsmiViewMDKernel->Text = L"����Ԫ������ͼ";
			this->tsmiViewMDKernel->Click += gcnew System::EventHandler(this, &CfrmMain::tsmiViewMDKernel_Click);
			// 
			// CfrmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(812, 452);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->splitter1);
			this->Controls->Add(this->tvClass);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"CfrmMain";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Ԫ����";
			this->Shown += gcnew System::EventHandler(this, &CfrmMain::CfrmMain_Shown);
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->grdcDetail))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dtDetail))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataTable1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->grdvDetail))->EndInit();
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
			 dlgOpen.Filter = "��̬��(*.dll)|*.dll|ȫ���ļ�(*.*)|*.*";
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
					 else throw gcnew Exception("�޷�����Ԫ���ݣ�");
				 }
				 else throw gcnew Exception("����DLLʧ�ܣ�");
			 }
		 }
private: System::Void tsmiViewMDKernel_Click(System::Object^  sender, System::EventArgs^  e) {
			 InitClassView(*MetaDataGlobalSpace());
		 }
private: System::Void tvClass_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 IntPtr pointer = static_cast<IntPtr>(e->Node->Tag);
			 CMetaData *pMD = reinterpret_cast<CMetaData*>((static_cast<void*>(pointer)));
			 InitDetailView(pMD);
			 grdvDetail->ExpandAllGroups();
		 }
private: System::Void grdvDetail_CustomDrawGroupRow(System::Object^  sender, DevExpress::XtraGrid::Views::Base::RowObjectCustomDrawEventArgs^  e) {
			 GridGroupRowInfo ^Info(static_cast<GridGroupRowInfo^>(e->Info));
			 GridView ^grdView(static_cast<GridView^>(sender));
			 if (grdView && Info)
			 {
				 int row = grdView->GetDataRowHandleByGroupRowHandle(e->RowHandle);
				 Info->GroupText = grdView->GetRowCellValue(row, "filter1")->ToString();
			 }
			 
		 }
};
}
