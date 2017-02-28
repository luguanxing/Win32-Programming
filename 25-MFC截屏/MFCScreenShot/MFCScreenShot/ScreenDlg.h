#pragma once


// ScreenDlg 对话框

class ScreenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ScreenDlg)

public:
	ScreenDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ScreenDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
};
