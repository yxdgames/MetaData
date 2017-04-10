#pragma once

#include "..\CommonFunction.h"
#include "..\..\..\Codes\MetaData\include\MetaData.h"

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
		CfrmMain(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	private:
		void InitClassView(CMetaData &md)
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
		void DoInitClassView(CMetaData &md, String ^name, TreeNodeCollection ^Nodes)
		{
			if (!Nodes) return;
			TreeNode ^tree_node;
			if (name)
				tree_node = Nodes->Add(name);
			else tree_node = Nodes->Add(gcnew String(md.GetName()));
			for (unsigned int i = 0; i < md.GetChildrenCount(); ++i)
			{
				DoInitClassView(*const_cast<CMetaData*>(md.GetChild(i)), nullptr, tree_node->Nodes);
			}
		}
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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->tsmiFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiViewMetaData = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiViewMDKernel = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(233, 25);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(579, 427);
			this->panel1->TabIndex = 2;
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
			this->tsmiFile->Text = L"文件";
			// 
			// tsmiViewMetaData
			// 
			this->tsmiViewMetaData->Name = L"tsmiViewMetaData";
			this->tsmiViewMetaData->Size = System::Drawing::Size(160, 22);
			this->tsmiViewMetaData->Text = L"查看元数据...";
			this->tsmiViewMetaData->Click += gcnew System::EventHandler(this, &CfrmMain::tsmiViewMetaData_Click);
			// 
			// tsmiViewMDKernel
			// 
			this->tsmiViewMDKernel->Name = L"tsmiViewMDKernel";
			this->tsmiViewMDKernel->Size = System::Drawing::Size(160, 22);
			this->tsmiViewMDKernel->Text = L"核心元数据视图";
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
			this->Text = L"元数据";
			this->Shown += gcnew System::EventHandler(this, &CfrmMain::CfrmMain_Shown);
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
			 if (dlgOpen.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 System::String ^str = dlgOpen.FileName;
				 pin_ptr<const wchar_t> pStr = PtrToStringChars(str);
				 HMODULE hModule = ::LoadLibrary(pStr);
				 if (hModule)
				 {
					 typedef void *(__stdcall *TpFunc)(void);
					 TpFunc pFunc;
					 pFunc = reinterpret_cast<TpFunc>(::GetProcAddress(hModule, "GetMetaDataGlobalSpace"));
					 if (pFunc)
					 {
						InitClassView(*reinterpret_cast<CMetaData*>(pFunc()));
					 }
					 ::FreeLibrary(hModule);
				 }
			 }
		 }
private: System::Void tsmiViewMDKernel_Click(System::Object^  sender, System::EventArgs^  e) {
			 InitClassView(*MetaDataGlobalSpace());
		 }
};
}
