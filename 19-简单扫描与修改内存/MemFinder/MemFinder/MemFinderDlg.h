
// MemFinderDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMemFinderDlg 对话框
class CMemFinderDlg : public CDialogEx
{
// 构造
public:
	CMemFinderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MEMFINDER_DIALOG };

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
	CButton radios_type;
	BOOL radios_value;
	afx_msg void OnBnClickedButtonChooseprocess();
	afx_msg void OnBnClickedButtonSearch();
	CString edit_processname;
	afx_msg void OnBnClickedButtonModify();
	CListCtrl list_memories;
	CString cs_value;
	afx_msg void OnBnClickedButtonSearch2();
};
