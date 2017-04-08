// Main.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Codes\Forms\CfrmMain.h"
#include <Windows.h>

using namespace System;
using namespace System::Windows::Forms;

using namespace MetaDataView;

static void AppDomain_UnhandledException(Object ^sender, UnhandledExceptionEventArgs ^e);
static void Application_ThreadException(Object ^sender, System::Threading::ThreadExceptionEventArgs ^e);

[STAThreadAttribute] //主线程中会涉及到COM对象的使用，需要使用这个属性来定义main函数所在的线程属性。
extern "C" int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CfrmMain frmMain;
	//异常处理
	AppDomain::CurrentDomain->UnhandledException += gcnew UnhandledExceptionEventHandler(AppDomain_UnhandledException);
	Application::ThreadException += gcnew System::Threading::ThreadExceptionEventHandler(Application_ThreadException);
	//启动
	Application::Run(%frmMain);

	return 0;
}

static void AppDomain_UnhandledException(Object ^sender, UnhandledExceptionEventArgs ^e)
{
	MessageBox::Show(e->ExceptionObject->ToString(), "错误", MessageBoxButtons::OK, MessageBoxIcon::Error);
}

static void Application_ThreadException(Object ^sender, System::Threading::ThreadExceptionEventArgs ^e)
{
	MessageBox::Show(e->Exception->Message, "错误", MessageBoxButtons::OK, MessageBoxIcon::Error);
}