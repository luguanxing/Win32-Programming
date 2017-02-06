
// Socket_ClientDlg.h : 头文件
//
#include "MySocket.h"
#pragma once


// CSocket_ClientDlg 对话框
class CSocket_ClientDlg : public CDialogEx
{
// 构造
public:
	CSocket_ClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SOCKET_CLIENT_DIALOG };

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
	CString m_csIP;
	UINT m_nPORT;
	CMySocket m_ClientSocket;
	CButton m_btnCONNECT;
	CButton m_btnSEND;
	CButton m_btnCLOSE;
	void OnClose();		//主窗口成员，由类成员函数转来
	void OnReceive();		//主窗口成员，由类成员函数转来
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	CString m_csMESSAGE;
	CListBox m_listSEND;
	CListBox m_listRECV;
	afx_msg void OnBnClickedButtonClose();
};
