// 计算器Dlg.h : 头文件
//

#pragma once


// C计算器Dlg 对话框
class C计算器Dlg : public CDialog
{
// 构造
public:
	C计算器Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

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
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedOk2();
public:
	afx_msg void OnBnClickedCancel();
public:
	CString m_text;
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton4();
public:
	afx_msg void OnBnClickedButton5();
public:
	afx_msg void OnBnClickedButton6();
public:
	afx_msg void OnBnClickedButton7();
public:
	afx_msg void OnBnClickedButton8();
public:
	afx_msg void OnBnClickedButton9();
public:
	afx_msg void OnBnClickedButton13();
public:
	afx_msg void OnBnClickedButton11();
public:
	afx_msg void OnBnClickedButton12();
public:
	afx_msg void OnBnClickedButton10();
public:
	afx_msg void OnEnChangeEdit1();
public:
	afx_msg void OnBnClickedButton14();
};
