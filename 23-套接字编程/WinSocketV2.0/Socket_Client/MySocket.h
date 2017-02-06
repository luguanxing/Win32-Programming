#pragma once

// CMySocket ÃüÁîÄ¿±ê
class CSocket_ClientDlg;

class CMySocket : public CSocket
{
public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	void SetDlg(CSocket_ClientDlg *dest);
private:
	CSocket_ClientDlg *m_pdlg;
};


