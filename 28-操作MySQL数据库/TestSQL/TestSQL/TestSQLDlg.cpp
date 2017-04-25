
// TestSQLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSQL.h"
#include "TestSQLDlg.h"
#include "afxdialogex.h"
#include "mysql.h"

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


// CTestSQLDlg 对话框




CTestSQLDlg::CTestSQLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestSQLDlg::IDD, pParent)
	, cs_sql(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SQL, cs_sql);
}

BEGIN_MESSAGE_MAP(CTestSQLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CTestSQLDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_EXE, &CTestSQLDlg::OnBnClickedButtonExe)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CTestSQLDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CTestSQLDlg 消息处理程序

BOOL CTestSQLDlg::OnInitDialog()
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

void CTestSQLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestSQLDlg::OnPaint()
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
HCURSOR CTestSQLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestSQLDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CTestSQLDlg::OnBnClickedButtonExe()
{
	//初始化数据库连接
	MYSQL mysql;
	mysql_init(&mysql);
    if (!mysql_real_connect(&mysql,"localhost","root","root","db_mfc",3306,NULL,0))  {  
		MessageBox(L"无法连接到数据库", L"错误", MB_ICONERROR);
		return;
    }

	//执行数据库操作， 注意mysql_query()的返回值份很多情形， 进行判断使要注意
	UpdateData(true);
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,cs_sql,-1,NULL,NULL,0,NULL);
	char *sql = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP,NULL,cs_sql,-1,sql,dwNum,0,NULL);
	mysql_query(&mysql, "set names 'utf8'");
	if ( mysql_query(&mysql, sql )==0 ) {
		MessageBox(L"执行数据库操作成功", L"成功", MB_ICONINFORMATION);
	} else {
		MessageBox(L"执行数据库操作失败", L"失败", MB_ICONERROR);
	}

	//关闭数据库连接
	mysql_close(&mysql);
	UpdateData(false);
}


void CTestSQLDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	cs_sql = L"";
	UpdateData(false);
}
