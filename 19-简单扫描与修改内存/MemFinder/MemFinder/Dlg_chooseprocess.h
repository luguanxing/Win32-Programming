#pragma once
#include "afxcmn.h"


// CDlg_chooseprocess 对话框

class CDlg_chooseprocess : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_chooseprocess)

public:
	CDlg_chooseprocess(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_chooseprocess();

// 对话框数据
	enum { IDD = IDD_CHOOSEPROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl list_process;
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
