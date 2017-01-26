
// explorerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CexplorerDlg 对话框
class CexplorerDlg : public CDialogEx
{
// 构造
public:
	CexplorerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXPLORER_DIALOG };

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
	CTreeCtrl tree;
	void dfs(CString path, HTREEITEM hroot, int next);
	CImageList imglist;
	afx_msg void OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl files;
	CImageList imglist2;
	void showfiles(CString filepath);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
