
// DriverLoaderDlg.h : 头文件
//

#pragma once


// CDriverLoaderDlg 对话框
class CDriverLoaderDlg : public CDialogEx
{
// 构造
public:
	CDriverLoaderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DRIVERLOADER_DIALOG };

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
	afx_msg void OnBnClickedButtonSrc();
	CString cs_src;
	afx_msg void OnBnClickedButtonLoad();
	CString m_drivername;
	CString m_driverpath;
	bool LoadDriver(void);
	afx_msg void OnBnClickedButtonUnload();
	bool UnloadDriver(void);
};
