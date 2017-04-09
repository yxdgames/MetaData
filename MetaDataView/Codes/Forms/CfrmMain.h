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
			this->SuspendLayout();
			// 
			// tvClass
			// 
			this->tvClass->Dock = System::Windows::Forms::DockStyle::Left;
			this->tvClass->Location = System::Drawing::Point(0, 0);
			this->tvClass->Name = L"tvClass";
			this->tvClass->Size = System::Drawing::Size(230, 452);
			this->tvClass->TabIndex = 0;
			// 
			// splitter1
			// 
			this->splitter1->Location = System::Drawing::Point(230, 0);
			this->splitter1->Name = L"splitter1";
			this->splitter1->Size = System::Drawing::Size(3, 452);
			this->splitter1->TabIndex = 1;
			this->splitter1->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(233, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(579, 452);
			this->panel1->TabIndex = 2;
			// 
			// CfrmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(812, 452);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->splitter1);
			this->Controls->Add(this->tvClass);
			this->Name = L"CfrmMain";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"元数据";
			this->Shown += gcnew System::EventHandler(this, &CfrmMain::CfrmMain_Shown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void CfrmMain_Shown(System::Object^  sender, System::EventArgs^  e) {
				 InitClassView(*MetaDataGlobalSpace());
			 }
};
}
