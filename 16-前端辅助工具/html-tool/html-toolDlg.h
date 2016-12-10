
// html-toolDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// ChtmltoolDlg 对话框
class ChtmltoolDlg : public CDialogEx
{
// 构造
public:
	ChtmltoolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HTMLTOOL_DIALOG };

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
	CString m_red;
	CString m_green;
	CString m_blue;
protected:
	afx_msg LRESULT OnUpdatedata(WPARAM wParam, LPARAM lParam);
public:
	CSliderCtrl m_slider;
	afx_msg void OnTRBNThumbPosChangingSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult);
	CButton button_opacity;
	afx_msg void OnBnClickedButtonOpacity();
	CButton m_fresh;
	afx_msg void OnBnClickedButtonFresh();
	CButton m_choosefile;
	afx_msg void OnBnClickedButtonChoosefile();
};
