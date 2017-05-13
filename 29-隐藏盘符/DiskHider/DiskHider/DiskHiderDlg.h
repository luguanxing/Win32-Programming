
// DiskHiderDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CDiskHiderDlg 对话框
class CDiskHiderDlg : public CDialogEx
{
// 构造
public:
	CDiskHiderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DISKHIDER_DIALOG };

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
	CComboBox m_disks;
	afx_msg void OnCbnSelchangeDisks();
	afx_msg void OnBnClickedButtonHide();
	afx_msg void OnBnClickedButtonRestore();
};
