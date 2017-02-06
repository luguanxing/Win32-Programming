
// Socket_ServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MySocket.h"

// CSocket_ServerDlg 对话框
class CSocket_ServerDlg : public CDialogEx
{
// 构造
public:
	CSocket_ServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SOCKET_SERVER_DIALOG };

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
	CEdit m_editIP;
	CString m_csIP;
	CEdit m_editPORT;
	UINT m_nPORT;
	CString m_csMESSAGE;
	CEdit m_editMESSAGE;
	CListBox m_listSEND;
	CListBox m_listRECV;
	CButton m_btnLISTEN;
	CButton m_btnSEND;
	CButton m_btnCLOSE;
	afx_msg void OnBnClickedButtonListen();
	CMySocket m_ServerSocket;	//服务端套接字
	CMySocket m_ClientSocket;	//新链接套接字

	void OnClose();		//主窗口成员，由类成员函数转来
	void OnReceive();		//主窗口成员，由类成员函数转来
	void OnAccept();		//主窗口成员，由类成员函数转来
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClose();
};
