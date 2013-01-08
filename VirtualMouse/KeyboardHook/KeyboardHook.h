// KeyboardHook.h : KeyboardHook DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#define DllExport __declspec(dllexport)


// CKeyboardHookApp
// 有关此类实现的信息，请参阅 KeyboardHook.cpp
//


class CKeyboardHookApp : public CWinApp
{
public:
	CKeyboardHookApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

DllExport void WINAPI InstallKbHook(HWND hWnd,UINT msg);