// Main.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Codes\Forms\CfrmMain.h"
#include <Windows.h>

using namespace System;
using namespace System::Windows::Forms;

using namespace MetaDataView;

static void AppDomain_UnhandledException(Object ^sender, UnhandledExceptionEventArgs ^e);
static void Application_ThreadException(Object ^sender, System::Threading::ThreadExceptionEventArgs ^e);

[STAThreadAttribute] //���߳��л��漰��COM�����ʹ�ã���Ҫʹ���������������main�������ڵ��߳����ԡ�
extern "C" int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CfrmMain frmMain;
	//�쳣����
	AppDomain::CurrentDomain->UnhandledException += gcnew UnhandledExceptionEventHandler(AppDomain_UnhandledException);
	Application::ThreadException += gcnew System::Threading::ThreadExceptionEventHandler(Application_ThreadException);
	//����
	Application::Run(%frmMain);

	return 0;
}

static void AppDomain_UnhandledException(Object ^sender, UnhandledExceptionEventArgs ^e)
{
	MessageBox::Show(e->ExceptionObject->ToString(), "����", MessageBoxButtons::OK, MessageBoxIcon::Error);
}

static void Application_ThreadException(Object ^sender, System::Threading::ThreadExceptionEventArgs ^e)
{
	MessageBox::Show(e->Exception->Message, "����", MessageBoxButtons::OK, MessageBoxIcon::Error);
}