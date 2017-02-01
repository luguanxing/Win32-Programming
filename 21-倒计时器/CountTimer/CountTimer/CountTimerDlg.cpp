
// CountTimerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CountTimer.h"
#include "CountTimerDlg.h"
#include "afxdialogex.h"
#define WM_USER_UPDATEDTA WM_USER+1

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


// CCountTimerDlg 对话框




CCountTimerDlg::CCountTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCountTimerDlg::IDD, pParent)
	, cs_time(_T(""))
	, cs_counttime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCountTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, start);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, pause);
	DDX_Control(pDX, IDC_BUTTON_STOP, stop);
	DDX_Text(pDX, IDC_EDIT2, cs_time);
	DDX_Text(pDX, IDC_EDIT1, cs_counttime);
}

BEGIN_MESSAGE_MAP(CCountTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CCountTimerDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CCountTimerDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CCountTimerDlg::OnBnClickedButtonPause)
END_MESSAGE_MAP()


// CCountTimerDlg 消息处理程序
CString *pcs_counttime;
CButton *pstart;
CButton *ppause;
CButton *pstop;
BOOL CCountTimerDlg::OnInitDialog()
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
	start.EnableWindow(true);
	stop.EnableWindow(false);
	pause.EnableWindow(false);
	pcs_counttime = &cs_counttime;
	cs_counttime.Format(L"0.0");
	pstart = &start;
	ppause = &pause;
	pstop = &stop;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCountTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCountTimerDlg::OnPaint()
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
HCURSOR CCountTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

float f_time = 0;
float f_oldtime = 0;
bool bpause = false;
HANDLE hcountdown = NULL;
DWORD WINAPI countdown(LPVOID lpParam) {
	while (f_time>=0) {
		HWND hwnd = AfxGetApp()->m_pMainWnd->m_hWnd;
		HDC hdc = ::GetDC(hwnd);
		float percent = f_time/f_oldtime; 
		::Rectangle(hdc, 65,20,65+(173-65)*percent,45);
		ReleaseDC(hwnd, hdc);
		f_time -= 0.005;
		Sleep(5);
		AfxGetApp()->m_pMainWnd->SendMessage(WM_USER_UPDATEDTA, 0, 0);
	}
	f_time = 0;
	bpause = false;
	pstart->EnableWindow(true);
	pstop->EnableWindow(false);
	ppause->EnableWindow(false);
	pcs_counttime->Format(L"0.0");
	AfxGetApp()->m_pMainWnd->SendMessage(WM_USER_UPDATEDTA, 0, 0);
	return 0;
}

void CCountTimerDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!bpause) {
		UpdateData(true);
		float count = _tstof(cs_time);
		if (!count) {
			::MessageBox(NULL, L"数据不正确或格式有误", L"错误", MB_ICONERROR);
			return;
		} else {
			f_time = count;
			f_oldtime = f_time;
			hcountdown = CreateThread(NULL, 0, countdown, NULL, 0, NULL);
			start.EnableWindow(false);
			stop.EnableWindow(true);
			pause.EnableWindow(true);
		}
	} else {
		start.SetWindowText(L"开始");
		::ResumeThread(hcountdown);
		start.EnableWindow(false);
		stop.EnableWindow(true);
		pause.EnableWindow(true);
	}
}


LRESULT CCountTimerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (message == WM_USER_UPDATEDTA) {
		cs_counttime.Format(L"%.2f", f_time);
		this->UpdateData(false);
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CCountTimerDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwExitCode;
	GetExitCodeThread(hcountdown, &dwExitCode);
	if (dwExitCode==STILL_ACTIVE) {
		::TerminateThread(hcountdown, 0);

		CDC *pdc = GetDC();
		float percent = f_time/f_oldtime; 
		pdc->Rectangle( 65,20,65+(173-65)*percent,45);
		for (; percent >=0; percent-=0.005) {
			pdc->Rectangle( 65,20,65+(173-65)*percent,45);
		}
		ReleaseDC(pdc);

		start.EnableWindow(true);
		stop.EnableWindow(false);
		pause.EnableWindow(false);
		cs_counttime.Format(L"0.0");
		bpause = false;
		this->UpdateData(false);
	} else {
		::MessageBox(NULL, L"倒计时已经结束", L"错误", MB_ICONERROR);
	}
}


void CCountTimerDlg::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwExitCode;
	GetExitCodeThread(hcountdown, &dwExitCode);
	if (dwExitCode==STILL_ACTIVE) {
		::SuspendThread(hcountdown);
		start.SetWindowText(L"继续");
		start.EnableWindow(true);
		stop.EnableWindow(false);
		pause.EnableWindow(false);
		this->UpdateData(false);
		bpause = true;
	} else {
		::MessageBox(NULL, L"倒计时已经结束", L"错误", MB_ICONERROR);
	}
}
