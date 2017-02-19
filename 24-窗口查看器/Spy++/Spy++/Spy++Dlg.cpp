
// Spy++Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Spy++.h"
#include "Spy++Dlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"

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


// CSpyDlg 对话框




CSpyDlg::CSpyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpyDlg::IDD, pParent)
	, m_cs_process(_T(""))
	, m_cs_hwnd(_T(""))
	, m_cs_title(_T(""))
	, m_cs_class(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CURSOR, m_pic);
	DDX_Text(pDX, IDC_EDIT_PROCESS, m_cs_process);
	DDX_Text(pDX, IDC_EDIT_HWND, m_cs_hwnd);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_cs_title);
	DDX_Text(pDX, IDC_EDIT_CLASS, m_cs_class);
	DDX_Control(pDX, IDC_CHECK_HIDE, m_btn_hide);
}

BEGIN_MESSAGE_MAP(CSpyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_HIDE, &CSpyDlg::OnBnClickedCheckHide)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSpyDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CSpyDlg::OnBnClickedButtonHelp)
END_MESSAGE_MAP()


// CSpyDlg 消息处理程序
HCURSOR hcready, hcempty;
BOOL CSpyDlg::OnInitDialog()
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
	hcready = (HCURSOR)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_CURSOR_CHOOSE),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE) ;
	hcempty = (HCURSOR)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_CURSOR_WAIT),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE) ;
	m_pic.SetCursor(hcready);
	m_bhide = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSpyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSpyDlg::OnPaint()
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
HCURSOR CSpyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSpyDlg::OnBnClickedCheckHide()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bhide = !m_bhide;
}


BOOL CSpyDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pos;   
	GetCursorPos(&pos);  //获取当前鼠标位置   

	CRect rc;
	CWnd *bkg=GetDlgItem(IDC_STATIC_CURSOR);
	bkg->GetWindowRect(&rc);
	if (rc.PtInRect(pos)) 
	{   
		SetCursor(LoadCursor(NULL, IDC_HAND));
		return true;
	}   
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}



void CSpyDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pos;   
	GetCursorPos(&pos);  //获取当前鼠标位置   
	CRect rc;
	CWnd *bkg=GetDlgItem(IDC_STATIC_CURSOR);
	bkg->GetWindowRect(&rc);

	if (m_bhide) {
		ShowWindow(SW_HIDE);
	}

	if (rc.PtInRect(pos))   //鼠标位置在图标内
	{   
		HCURSOR hp; 
		hp= (HCURSOR)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_CURSOR_POINT),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE) ;
		::SetCursor(hp);
		::SetCapture(m_hWnd);	//保持焦点状态
		m_pic.SetCursor(hcempty);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSpyDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HCURSOR hp;
	hp= (HCURSOR)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_ARROW),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE) ;
	::SetCursor(hp);
	::ReleaseCapture();
	m_pic.SetCursor(hcready);
	EraseFrame(holdwnd);

	ShowWindow(SW_SHOW);

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CSpyDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pos;   
	GetCursorPos(&pos);  //获取当前鼠标位置   
	CRect rc;
	CWnd *bkg=AfxGetApp()->GetMainWnd();
	bkg->GetWindowRect(&rc);
	if (rc.PtInRect(pos))   //鼠标位置在图标内
		return;

	::ClientToScreen(m_hWnd, &point);	//取鼠标坐标
	HWND hwnd = ::WindowFromPoint(point);	//找鼠标对应的窗口
	if ( hwnd == holdwnd)	//不一直画相同窗口和自己
		return;

	EraseFrame(holdwnd);
	DrawFrame(hwnd);
	GetInfo(hwnd);
	holdwnd = hwnd;
	CDialogEx::OnMouseMove(nFlags, point);
}


void CSpyDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CSpyDlg::OnBnClickedButtonHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	::MessageBox(NULL, L"点击并拖动标志移动到要查询的窗口即可显示信息", L"帮助信息", MB_ICONINFORMATION);
}


void CSpyDlg::DrawFrame(HWND hwnd)
{
	HDC hdc = ::GetWindowDC(hwnd);
	RECT rect;
	::GetWindowRect(hwnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	HPEN hpen = ::CreatePen(PS_SOLID, 5, RGB(255,0,0));
	HPEN holdpen = (HPEN)::SelectObject(hdc, hpen);

	::MoveToEx(hdc, 0, 0, NULL);
	::LineTo(hdc, width, 0);
	::LineTo(hdc, width, height);
	::LineTo(hdc, 0, height);
	::LineTo(hdc, 0, 0);

	::SelectObject(hdc, holdpen);
	::DeleteObject(hpen);
	::ReleaseDC(hwnd, hdc);
}


void CSpyDlg::EraseFrame(HWND hwnd)
{
	::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	HWND hparent = ::GetParent(hwnd);
	if (::IsWindow(hparent)) {
		::RedrawWindow(hparent, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
	}
}


void CSpyDlg::GetInfo(HWND hwnd)
{
	WCHAR wbuff[255];
	::GetWindowText(hwnd, wbuff, sizeof(wbuff));	//标题
	m_cs_title = wbuff;

	::GetClassName(hwnd, wbuff, sizeof(wbuff));		//类名
	m_cs_class = wbuff;

	wsprintf(wbuff, L"%x", hwnd);			//窗口句柄
	m_cs_hwnd = wbuff;

	DWORD pid;		//进程名字
	::GetWindowThreadProcessId(hwnd, &pid);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, pid);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return;
	bool bFound=false;
	PROCESSENTRY32 pe32 = {sizeof(pe32)};
	if (::Process32First(hProcessSnap, &pe32)) {
		do {
			if (pe32.th32ProcessID == pid) {
				bFound = true;
				break;
			}
		} while(::Process32Next(hProcessSnap, &pe32));
	}
	if (bFound) {
			wsprintf(wbuff, pe32.szExeFile);
	} else {
			wsprintf(wbuff, L"找不到进程");
	}
	m_cs_process = wbuff;
	UpdateData(false);
}
