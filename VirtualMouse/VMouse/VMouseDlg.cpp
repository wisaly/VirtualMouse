// VMouseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VMouse.h"
#include "VMouseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVMouseDlg 对话框
#define MSG_TRAYICON	WM_USER + 1
#define MSG_KEYEVENT	WM_USER + 811


CVMouseDlg::CVMouseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVMouseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_bActive = FALSE;
	m_bScrollPressed = FALSE;
	m_bLocked = FALSE;
}

void CVMouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVMouseDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(MSG_KEYEVENT,OnKeyEvent)
	//}}AFX_MSG_MAP
	ON_MESSAGE(MSG_TRAYICON,OnTrayNotification)
	ON_WM_MEASUREITEM()
	ON_COMMAND(ID__SHOW,OnTrayShow)
	ON_COMMAND(ID__EXIT,OnTrayExit)
	ON_BN_CLICKED(ID_HIDE, &CVMouseDlg::OnBnClickedHide)
END_MESSAGE_MAP()


// CVMouseDlg 消息处理程序

BOOL CVMouseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	BOOL bRes = m_trayIcon.Create(this, IDR_MENU_TRAY, "VMouse", 
		m_hIcon, 
		MSG_TRAYICON);

	m_trayIcon.ShowBallonText("VMouse启动了喵~   =u=");

	InstallKbHook(m_hWnd,MSG_KEYEVENT);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVMouseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVMouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#pragma region Alpha Keys Define

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A
#pragma endregion Alpha Keys Define


LRESULT CVMouseDlg::OnKeyEvent( WPARAM wParam,LPARAM lParam )
{
	KBDLLHOOKSTRUCT *Key_Info = (KBDLLHOOKSTRUCT*)lParam;

	if (WM_KEYDOWN == wParam || WM_SYSKEYDOWN == wParam )  //如果按键为按下状态
	{
		if (Key_Info->vkCode == VK_W)
		{
			if (GetKeyState (VK_CONTROL) < 0 && GetKeyState (VK_MENU) < 0 && GetKeyState(VK_SHIFT) < 0)
			{
				if (m_bLocked)
				{
					m_bLocked = FALSE;
					m_trayIcon.ShowBallonText("恢复了喵~    =u=");
				}
				else
				{
					m_bLocked = TRUE;
					m_trayIcon.ShowBallonText("锁屏了喵~   OuO");
				}
				return 1;
			}
		}
		if (m_bLocked)
		{
			m_trayIcon.ShowBallonText("屏幕锁住了喵!    =x=");
			return 1;
		}
		if (Key_Info->vkCode == VK_X)
		{
			if (GetKeyState(VK_CONTROL) < 0 && GetKeyState(VK_MENU) < 0 && GetKeyState(VK_SHIFT) < 0)
			{
				OnOK();
				return 1;
			}
		}
		if (Key_Info->vkCode == VK_D )
		{
			if (GetKeyState (VK_CONTROL) < 0 && GetKeyState (VK_MENU) < 0 )
			{
				if (m_bActive)
				{
					m_bActive = FALSE;
					m_trayIcon.ShowBallonText("休息了喵~    =u=");
				}
				else
				{
					m_bActive = TRUE;
					m_trayIcon.ShowBallonText("开始工作了喵~   ^u^");
				}
				return 1;
			}
		}
	}

	if (m_bActive)
	{

		if (WM_KEYDOWN == wParam || WM_SYSKEYDOWN == wParam )  //如果按键为按下状态
		{

			switch(Key_Info->vkCode)
			{
			case VK_SPACE:	// left button
				if (m_bScrollPressed)
				{
					mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0 );
				}
				else
				{
					mouse_event (MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
				}
				return 1;
			case VK_OEM_1:
				mouse_event (MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
				return 1;
			case VK_H:
				m_bScrollPressed = TRUE;
				return 1;
			case VK_Y:
				mouse_event(MOUSEEVENTF_XDOWN,0,0,XBUTTON1,0);
				return 1;
			case VK_B:
				mouse_event(MOUSEEVENTF_XDOWN,0,0,XBUTTON2,0);
				return 1;
			}

			// mouse move
			#pragma region Mouse move
			int nOffset = 10;

			if (GetKeyState(VK_SHIFT) < 0)
			{
				nOffset = 1;
			}
			else if (GetKeyState(VK_CONTROL) < 0)
			{
				nOffset = 30;
			}
			else if (GetKeyState(VK_MENU) < 0)
			{
				nOffset = 5;
			}
			POINT point;
			::GetCursorPos(&point);

			switch(Key_Info->vkCode)
			{
			case VK_J:	// left
				if (m_bScrollPressed)
				{
					mouse_event(MOUSEEVENTF_HWHEEL,0,0,WHEEL_DELTA,0);
					return 1;
				}
				point.x -= nOffset;
				break;
			case VK_L:	// right
				if (m_bScrollPressed)
				{
					mouse_event(MOUSEEVENTF_HWHEEL,0,0,-WHEEL_DELTA,0);
					return 1;
				}
				point.x += nOffset;
				break;
			case VK_I:	// up
				if (m_bScrollPressed)
				{
					mouse_event(MOUSEEVENTF_WHEEL,0,0,WHEEL_DELTA,0);
					return 1;
				}
				point.y -= nOffset;
				break;
			case VK_K:	// down
				if (m_bScrollPressed)
				{
					mouse_event(MOUSEEVENTF_WHEEL,0,0,-WHEEL_DELTA,0);
					return 1;
				}
				point.y += nOffset;
				break;
			case VK_U:	// left up
				point.x -= nOffset;
				point.y -= nOffset;
				break;
			case VK_O:	// right up
				point.x += nOffset;
				point.y -= nOffset;
				break;
			case VK_N:	// left down
				point.x -= nOffset;
				point.y += nOffset;
				break;
			case VK_M:	// right down
				point.x += nOffset;
				point.y += nOffset;
				break;
			default:
				return 0;
			}

			::SetCursorPos(point.x,point.y);
			#pragma endregion Mouse move
			return 1;
		}
		else if (WM_KEYUP == wParam || WM_SYSKEYUP == wParam )  //
		{
			switch(Key_Info->vkCode)
			{
			case VK_SPACE:	// left button
				if (m_bScrollPressed)
				{
					mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0 );
				}
				else
				{
					mouse_event (MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
				}
				return 1;
			case VK_OEM_1:
				mouse_event (MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
				return 1;
			case VK_H:
				m_bScrollPressed = FALSE;
				return 1;
			case VK_Y:
				mouse_event(MOUSEEVENTF_XUP,0,0,XBUTTON1,0);
				return 1;
			case VK_B:
				mouse_event(MOUSEEVENTF_XUP,0,0,XBUTTON2,0);
				return 1;
			}
		}
	}

	
	return 0;
}


LRESULT CVMouseDlg::OnTrayNotification( WPARAM wParam, LPARAM lParam )
{
	return m_trayIcon.OnTrayNotification(wParam,lParam);
}

void CVMouseDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(lpMeasureItemStruct->CtlType == ODT_MENU)
	{
		if(IsMenu((HMENU)lpMeasureItemStruct->itemID) 
			&& IsMenu((HMENU)lpMeasureItemStruct->itemID))
		{
			m_trayIcon.m_menu.MeasureItem(lpMeasureItemStruct);
		}
	}
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CVMouseDlg::OnTrayShow()
{
	ShowWindow(SW_SHOW);
}

void CVMouseDlg::OnTrayExit()
{
	if (m_bLocked)
	{
		m_trayIcon.ShowBallonText("屏幕锁住了喵!    =x=");
		return;
	}
	OnOK();
}

void CVMouseDlg::OnBnClickedHide()
{
	ShowWindow(SW_HIDE);
}
