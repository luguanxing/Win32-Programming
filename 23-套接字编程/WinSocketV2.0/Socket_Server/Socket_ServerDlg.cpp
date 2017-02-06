
// Socket_ServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Socket_Server.h"
#include "Socket_ServerDlg.h"
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


// CSocket_ServerDlg 对话框




CSocket_ServerDlg::CSocket_ServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocket_ServerDlg::IDD, pParent)
	, m_csIP(_T(""))
	, m_nPORT(0)
	, m_csMESSAGE(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocket_ServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_IP, m_editIP);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPORT);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPORT);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_csMESSAGE);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_editMESSAGE);
	DDX_Control(pDX, IDC_LIST_SEND, m_listSEND);
	DDX_Control(pDX, IDC_LIST_RECV, m_listRECV);
	DDX_Control(pDX, IDC_BUTTON_LISTEN, m_btnLISTEN);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSEND);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnCLOSE);
}

BEGIN_MESSAGE_MAP(CSocket_ServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CSocket_ServerDlg::OnBnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSocket_ServerDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSocket_ServerDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CSocket_ServerDlg 消息处理程序

BOOL CSocket_ServerDlg::OnInitDialog()
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
	m_ServerSocket.SetDlg(this);	//设置类内部m_pdlg指针指向主窗口
	m_ClientSocket.SetDlg(this);	//设置类内部m_pdlg指针指向主窗口

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSocket_ServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSocket_ServerDlg::OnPaint()
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
HCURSOR CSocket_ServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocket_ServerDlg::OnBnClickedButtonListen()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_ServerSocket.Create(m_nPORT)) {		//创建套接字,默认以TCP协议绑定本机
		TRACE("服务端创建套接字成功\n");
		if (m_ServerSocket.Listen()) {
			TRACE("服务端监听成功\n");
			m_btnLISTEN.EnableWindow(false);
			m_btnCLOSE.EnableWindow(true);
		}
	}
}

void CSocket_ServerDlg::OnClose() {
	//关闭客户端套接字
	m_ClientSocket.Close();
}

void CSocket_ServerDlg::OnReceive() {
	char buff[256] = {0};
	int retnum = m_ClientSocket.Receive(buff, 256);
	if (retnum) {			//受到返回字节数目大于0
		CString cs;
		cs.Format(L"%s", buff);
		m_listRECV.AddString(cs);
		UpdateData(false);
	}
}
void CSocket_ServerDlg::OnAccept() {
	m_ServerSocket.Accept(m_ClientSocket);	//初始化m_ClientSocket，方便与客户端收发消息
	m_btnSEND.EnableWindow(true);
	m_btnCLOSE.EnableWindow(true);
}


void CSocket_ServerDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (!m_csMESSAGE.IsEmpty()) {
		int sendlen = m_ClientSocket.Send(m_csMESSAGE,m_csMESSAGE.GetLength()*2);
		if (sendlen > 0) {
			TRACE("服务端成功发送%d 字节\n",sendlen);
			m_listSEND.AddString(m_csMESSAGE);
			m_csMESSAGE.Empty();
		}
	}
	UpdateData(false);
}


void CSocket_ServerDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ServerSocket.Close();
	OnClose();
	TRACE("服务端关闭");
	m_btnLISTEN.EnableWindow(true);
	m_btnSEND.EnableWindow(false);
	m_btnCLOSE.EnableWindow(false);
}
