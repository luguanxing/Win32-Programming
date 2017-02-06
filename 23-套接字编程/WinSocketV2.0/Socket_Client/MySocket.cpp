// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Socket_Client.h"
#include "MySocket.h"
#include "Socket_ClientDlg.h"

// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket 成员函数，类内成员调用主窗口函数便于窗口显示数据
// CMySocket 成员函数，类内成员调用主窗口函数便于窗口显示数据
void CMySocket::OnClose(int nErrorCode) {
	if (nErrorCode == 0) {
		TRACE("客户端关闭套接字\n");
		m_pdlg->OnClose();		//转到主窗口成员
	}
}
void CMySocket::OnReceive(int nErrorCode) {
	if (nErrorCode == 0) {
		TRACE("客户端收到服务端消息\n");
		m_pdlg->OnReceive();		//转到主窗口成员
	}
}
void CMySocket::SetDlg(CSocket_ClientDlg *dest) {
	this->m_pdlg = dest;
}
