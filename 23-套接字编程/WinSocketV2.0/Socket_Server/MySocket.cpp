// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Socket_Server.h"
#include "MySocket.h"
#include "Socket_ServerDlg.h"

// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket 成员函数，类内成员调用主窗口函数便于窗口显示数据
void CMySocket::OnClose(int nErrorCode) {
	if (nErrorCode == 0) {
		TRACE("服务端发现客户关闭套接字\n");
		m_pdlg->OnClose();		//转到主窗口成员
	}
}
void CMySocket::OnReceive(int nErrorCode) {
	if (nErrorCode == 0) {
		TRACE("服务端收到客户消息\n");
		m_pdlg->OnReceive();		//转到主窗口成员
	}
}
void CMySocket::OnAccept( int nErrorCode ) {
	if (nErrorCode == 0) {
		TRACE("服务端发现客户连接\n");
		m_pdlg->OnAccept();		//转到主窗口成员
	}
}
void CMySocket::SetDlg(CSocket_ServerDlg *dest) {
	this->m_pdlg = dest;
}