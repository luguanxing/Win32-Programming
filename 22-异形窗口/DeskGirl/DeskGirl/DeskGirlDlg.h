
// DeskGirlDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CDeskGirlDlg 对话框
class CDeskGirlDlg : public CDialogEx
{
// 构造
public:
	CDeskGirlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DESKGIRL_DIALOG };

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CStatic m_girl;
//	afx_msg void OnBnClickedButtonTest();
};
