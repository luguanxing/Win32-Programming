#pragma once


// CDllDialog 对话框

class CDllDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDllDialog)

public:
	CDllDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDllDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
