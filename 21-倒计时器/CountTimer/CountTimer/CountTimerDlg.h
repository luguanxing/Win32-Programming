
// CountTimerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CCountTimerDlg 对话框
class CCountTimerDlg : public CDialogEx
{
// 构造
public:
	CCountTimerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COUNTTIMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton start;
	CButton pause;
	CButton stop;
	afx_msg void OnBnClickedButtonStart();
	CString cs_time;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	CString cs_counttime;
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonPause();
};
