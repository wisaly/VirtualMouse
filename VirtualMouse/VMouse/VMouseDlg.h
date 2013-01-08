// VMouseDlg.h : 头文件
//

#pragma once
#include "Ntray.h"


// CVMouseDlg 对话框
class CVMouseDlg : public CDialog
{
// 构造
public:
	CVMouseDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VMOUSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CTrayNotifyIcon m_trayIcon;
	
	// 工作模式
	BOOL m_bActive;
	// 滚动模式
	BOOL m_bScrollPressed;
	// 锁屏模式
	BOOL m_bLocked;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT OnTrayNotification( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnKeyEvent(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTrayShow();
	afx_msg void OnTrayExit();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnBnClickedHide();
};
