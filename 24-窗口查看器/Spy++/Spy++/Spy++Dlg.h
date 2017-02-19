
// Spy++Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CSpyDlg 对话框
class CSpyDlg : public CDialogEx
{
// 构造
public:
	CSpyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SPY_DIALOG };

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
	CButton m_btnHide;
	CStatic m_pic;
	CString m_cs_process;
	CString m_cs_hwnd;
	CString m_cs_title;
	CString m_cs_class;
	CButton m_btn_hide;
	afx_msg void OnBnClickedCheckHide();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonHelp();
	void DrawFrame(HWND hwnd);
	void EraseFrame(HWND hwnd);
	void GetInfo(HWND hwnd);
	HWND holdwnd;
	bool m_bhide;
};
