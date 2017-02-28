
// MFCScreenShotDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCScreenShot.h"
#include "MFCScreenShotDlg.h"
#include "afxdialogex.h"
#include "ScreenDlg.h"

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


// CMFCScreenShotDlg 对话框




CMFCScreenShotDlg::CMFCScreenShotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCScreenShotDlg::IDD, pParent)
	, m_cs_path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCScreenShotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cs_path);
	DDX_Control(pDX, IDC_BUTTON_START, m_btn_start);
}

BEGIN_MESSAGE_MAP(CMFCScreenShotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CMFCScreenShotDlg::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMFCScreenShotDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_START, &CMFCScreenShotDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CMFCScreenShotDlg 消息处理程序
BOOL CMFCScreenShotDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCScreenShotDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCScreenShotDlg::OnPaint()
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
HCURSOR CMFCScreenShotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


WCHAR savedir[255];
void CMFCScreenShotDlg::OnBnClickedButtonFile()
{
	BROWSEINFO bi; 

	LPITEMIDLIST pidl; 
	LPMALLOC pMalloc = NULL;  
	ZeroMemory(&bi, sizeof(bi));      
	bi.hwndOwner = GetSafeHwnd(); 
	bi.pszDisplayName = savedir; 
	bi.lpszTitle = _T("\n请选择截图保存路径:"); 
	bi.ulFlags = BIF_RETURNONLYFSDIRS;  
	pidl = SHBrowseForFolder(&bi); 

	if (pidl) { 
		SHGetPathFromIDList(pidl, savedir); 
		m_cs_path = savedir;
		UpdateData(false);
		m_btn_start.EnableWindow(true);
	} else {
		if (savedir[0] == '\0')
			::MessageBox(NULL, _T("未选择路径"), _T("错误"), MB_ICONERROR);
	}
}


void CMFCScreenShotDlg::OnBnClickedButtonExit()
{
	exit(0);
}

ScreenDlg screendlg;
void CMFCScreenShotDlg::OnBnClickedButtonStart()
{
	if (screendlg.m_hWnd==0)
	{
		screendlg.Create(IDD_DIALOG_SCREEN,this);
	}
	screendlg.ShowWindow(SW_SHOW);
}
