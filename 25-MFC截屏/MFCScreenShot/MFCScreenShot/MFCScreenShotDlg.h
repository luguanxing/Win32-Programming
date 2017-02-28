
// MFCScreenShotDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMFCScreenShotDlg 对话框
class CMFCScreenShotDlg : public CDialogEx
{
// 构造
public:
	CMFCScreenShotDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCSCREENSHOT_DIALOG };

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
	CString m_cs_path;
	CButton m_btn_start;
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonStart();
};
