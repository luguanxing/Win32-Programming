
// Socket_ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Socket_Client.h"
#include "Socket_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSocket_ClientDlg 对话框




CSocket_ClientDlg::CSocket_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocket_ClientDlg::IDD, pParent)
	, m_csIP(_T(""))
	, m_nPORT(0)
	, m_csMESSAGE(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocket_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPORT);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btnCONNECT);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSEND);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnCLOSE);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_csMESSAGE);
	DDX_Control(pDX, IDC_LIST_SEND, m_listSEND);
	DDX_Control(pDX, IDC_LIST_RECV, m_listRECV);
}

BEGIN_MESSAGE_MAP(CSocket_ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSocket_ClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSocket_ClientDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSocket_ClientDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CSocket_ClientDlg 消息处理程序

BOOL CSocket_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_nPORT = 1234;
	m_csIP = _T("127.0.0.1");
	UpdateData(false);
	m_ClientSocket.SetDlg(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSocket_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSocket_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSocket_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSocket_ClientDlg::OnClose() {		//主窗口成员，由类成员函数转来
	m_ClientSocket.Close();
	m_btnCONNECT.EnableWindow(true);
	m_btnSEND.EnableWindow(false);
	m_btnCLOSE.EnableWindow(false);
}
void CSocket_ClientDlg::OnReceive() {		//主窗口成员，由类成员函数转来
	char buff[256] = {0};
	int retnum = m_ClientSocket.Receive(buff, 256);
	if (retnum) {			//受到返回字节数目大于0
		CString cs;
		cs.Format(L"%s", buff);
		m_listRECV.AddString(cs);
		UpdateData(false);
	}
}

void CSocket_ClientDlg::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_ClientSocket.Create()) {
		if (m_ClientSocket.Connect(m_csIP, m_nPORT)) {
			TRACE("连接成功\n");
			m_btnCONNECT.EnableWindow(false);
			m_btnSEND.EnableWindow(true);
			m_btnCLOSE.EnableWindow(true);
		} else {
			m_ClientSocket.Close();
		}
	}
}


void CSocket_ClientDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (!m_csMESSAGE.IsEmpty()) {
		int sendlen = m_ClientSocket.Send(m_csMESSAGE,m_csMESSAGE.GetLength()*2);
		if (sendlen > 0) {
			TRACE("客户端成功发送%d 字节\n",sendlen);
			m_listSEND.AddString(m_csMESSAGE);
			m_csMESSAGE.Empty();
		}
	}
	UpdateData(false);
}


void CSocket_ClientDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	OnClose();
}
