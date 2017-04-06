
// DriverLoaderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DriverLoader.h"
#include "DriverLoaderDlg.h"
#include "afxdialogex.h"
#include <winsvc.h>

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


// CDriverLoaderDlg 对话框




CDriverLoaderDlg::CDriverLoaderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDriverLoaderDlg::IDD, pParent)
	, cs_src(_T(""))
	, m_drivername(_T(""))
	, m_driverpath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDriverLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, cs_src);
}

BEGIN_MESSAGE_MAP(CDriverLoaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SRC, &CDriverLoaderDlg::OnBnClickedButtonSrc)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CDriverLoaderDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_UNLOAD, &CDriverLoaderDlg::OnBnClickedButtonUnload)
END_MESSAGE_MAP()


// CDriverLoaderDlg 消息处理程序

BOOL CDriverLoaderDlg::OnInitDialog()
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

void CDriverLoaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDriverLoaderDlg::OnPaint()
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
HCURSOR CDriverLoaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDriverLoaderDlg::OnBnClickedButtonSrc()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog sysFile(true, NULL, NULL, 0, L"驱动文件*.sys|*.sys|所有文件*.*|*.*|");
	if (IDOK == sysFile.DoModal()) {
		m_driverpath = sysFile.GetPathName();
		m_drivername = sysFile.GetFileName();
		cs_src = m_drivername;
		UpdateData(false);
	}
}

void CDriverLoaderDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!cs_src.IsEmpty()) {
		LoadDriver();
	} else {
		MessageBox(L"未选择驱动文件", L"错误", MB_ICONERROR);
	}
}

void CDriverLoaderDlg::OnBnClickedButtonUnload()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_drivername.IsEmpty() && !m_driverpath.IsEmpty()) {
		UnloadDriver();
	}
}

bool CDriverLoaderDlg::LoadDriver(void)
{
	bool bRet = false;
	SC_HANDLE hServiceMgr=NULL;		//SCM管理器的句柄
	SC_HANDLE hServiceDDK=NULL;	//NT驱动程序的服务句柄

	hServiceMgr =  ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);	//打开服务控制管理器
	if (hServiceMgr == NULL) {
		TRACE( "OpenSCManager()失败，原因=%d\n", GetLastError() );
		goto BExit;
	} else {
		TRACE( "OpenSCManager()成功\n");
	}

	hServiceDDK = ::CreateService(hServiceMgr, m_drivername,  m_drivername, SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, m_driverpath, NULL, NULL, NULL, NULL, NULL);	//创建驱动所对应的服务
	if (hServiceDDK == NULL) {
		DWORD dwRtn = GetLastError();
		if( dwRtn != ERROR_IO_PENDING && dwRtn != ERROR_SERVICE_EXISTS )  {  
			TRACE( "由于其他原因创建服务失败，原因=%d\n", GetLastError() );
			goto BExit;
		}  else  {
			TRACE( "CrateService() 服务创建失败，是由于服务已经创立过，原因=%d\n", GetLastError() );  
		}

		hServiceDDK = ::OpenService(hServiceMgr, m_drivername, SERVICE_ALL_ACCESS);		// 驱动程序已经加载，只需要打开  
		if (hServiceDDK == NULL) {
			TRACE( "OpenService()失败，原因=%d\n", GetLastError() );
			goto BExit;
		} else {
			TRACE( "OpenService()成功\n");
		}
	} else {
		TRACE( "CreateService()成功\n");
	}

	bool ret = ::StartService(hServiceDDK, NULL, NULL);	//开启此项服务
	if (ret == false) {
		TRACE( "StartService()失败，服务可能已经开启，原因=%d\n", GetLastError() );
	}
	bRet = true;

BExit:	//离开前相应处理
	if(hServiceDDK) {
		CloseServiceHandle(hServiceDDK);
	}
	if(hServiceMgr) {
		CloseServiceHandle(hServiceMgr);
	}
	return bRet;
}


bool CDriverLoaderDlg::UnloadDriver(void)
{
	bool bRet = false;
	SC_HANDLE hSCM=NULL;		//SCM管理器的句柄,用来存放OpenSCManager的返回值
	SC_HANDLE hService=NULL;	//NT驱动程序的服务句柄，用来存放OpenService的返回值
	SERVICE_STATUS SvrSta;

	hSCM = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );  //打开SCM管理器
	if( hSCM == NULL ) {
		TRACE( "OpenSCManager() 失败 %d ! \n", GetLastError());  
		goto BeforeLeave;
	} else {
		TRACE( "OpenSCManager() 成功 ! \n" );  
	}

	hService = OpenService( hSCM, m_drivername, SERVICE_ALL_ACCESS);  //打开驱动所对应的服务
	if( hService == NULL )  {
		TRACE( "OpenService() 失败 %d ! \n", GetLastError() );  
		goto BeforeLeave;
	} else {  
		TRACE( "OpenService() 成功 ! \n" );
	} 

	if( !ControlService( hService, SERVICE_CONTROL_STOP , &SvrSta ) ) {		//停止驱动程序，如果停止失败，只有重新启动才能，再动态加载
		TRACE( "用ControlService() 停止驱动程序失败 :%d !\n", GetLastError() );  
	}  else  {
		TRACE( "用ControlService() 停止驱动程序成功 !\n" );  
	}  
	
	if( !DeleteService( hService ) ) {		//动态卸载驱动服务。
		TRACE( "卸载失败:DeleteSrevice()错误号:%d !\n", GetLastError() );  
	}  else  {  
		TRACE ( "卸载成功 !\n" );  
	}  
	bRet = true;

BeforeLeave:		//离开前关闭打开的句柄
	if(hService>0) {
		CloseServiceHandle(hService);
	}
	if(hSCM>0) {
		CloseServiceHandle(hSCM);
	}
	return bRet;
}
