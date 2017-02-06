#pragma once

// CMySocket 命令目标

class CSocket_ServerDlg; //提前声明CSocket_ServerDlg类

class CMySocket : public CSocket	//派生自己的套接字类
{
public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept( int nErrorCode );
	void SetDlg(CSocket_ServerDlg *dest);
private:
	CSocket_ServerDlg *m_pdlg;
};


