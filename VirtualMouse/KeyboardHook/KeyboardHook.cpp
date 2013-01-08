// KeyboardHook.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "KeyboardHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CKeyboardHookApp

BEGIN_MESSAGE_MAP(CKeyboardHookApp, CWinApp)
END_MESSAGE_MAP()


// CKeyboardHookApp 构造

CKeyboardHookApp::CKeyboardHookApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CKeyboardHookApp 对象

CKeyboardHookApp theApp;


// CKeyboardHookApp 初始化


// void SaveLog(char* c)
// {
// 	CTime tm=CTime::GetCurrentTime();
// 	CString name;
// 	name.Format("c:\\Key_%d_%d.log",tm.GetMonth(),tm.GetDay());
// 	CFile file;
// 	if(!file.Open(name,CFile::modeReadWrite))
// 	{
// 		file.Open(name,CFile::modeCreate|CFile::modeReadWrite);
// 	}
// 	file.SeekToEnd();
// 	file.Write(c,1);
// 	file.Close();
// }
HHOOK g_hHook = NULL;
HWND g_hWnd = NULL;
UINT g_nMsg = 0;
BOOL g_bActive = FALSE;

LRESULT CALLBACK LauncherHook(int nCode,WPARAM wParam,LPARAM lParam)
{
	if(nCode==HC_ACTION)
	{
		if(SendMessage(g_hWnd,g_nMsg,wParam,lParam) != 0)
		{
			return 1;
		}
	}
 	return CallNextHookEx(g_hHook,nCode,wParam,lParam);
}
DllExport void WINAPI InstallKbHook(HWND hWnd,UINT msg)
{
	g_hHook=(HHOOK)SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)LauncherHook,theApp.m_hInstance,0);

	g_hWnd = hWnd;
	g_nMsg = msg;
}

BOOL CKeyboardHookApp::InitInstance()
{
	CWinApp::InitInstance();
	return TRUE;
}

int CKeyboardHookApp::ExitInstance()
{
	if (g_hHook != NULL)
	{
		UnhookWindowsHookEx(g_hHook);
	}

	return CWinApp::ExitInstance();
}
