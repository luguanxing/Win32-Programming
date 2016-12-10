
// html-toolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "html-tool.h"
#include "html-toolDlg.h"
#include "afxdialogex.h"
#include "iostream"
#include "deque"
#define WM_UPDATEDATA  10000+1

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


// ChtmltoolDlg 对话框

ChtmltoolDlg::ChtmltoolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChtmltoolDlg::IDD, pParent)
	, m_red(_T(""))
	, m_green(_T(""))
	, m_blue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ChtmltoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RED, m_red);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_green);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_blue);
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_BUTTON_OPACITY, button_opacity);
	DDX_Control(pDX, IDC_BUTTON_FRESH, m_fresh);
	DDX_Control(pDX, IDC_BUTTON_CHOOSEFILE, m_choosefile);
}

BEGIN_MESSAGE_MAP(ChtmltoolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(10001, &ChtmltoolDlg::OnUpdatedata)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER, &ChtmltoolDlg::OnTRBNThumbPosChangingSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, &ChtmltoolDlg::OnNMReleasedcaptureSlider)
	ON_BN_CLICKED(IDC_BUTTON_OPACITY, &ChtmltoolDlg::OnBnClickedButtonOpacity)
	ON_BN_CLICKED(IDC_BUTTON_FRESH, &ChtmltoolDlg::OnBnClickedButtonFresh)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSEFILE, &ChtmltoolDlg::OnBnClickedButtonChoosefile)
END_MESSAGE_MAP()


int x,y;
int red, green, blue;
COLORREF color;
POINT point;
HWND hwnd;
HWND hdlg;
CString *red_text,*green_text, *blue_text ;

DWORD WINAPI getcolor(LPVOID) {
	while(true) {
		GetCursorPos(&point);
		color = ::GetPixel(::GetDC(hwnd), point.x, point.y);
		red = GetRValue(color);
		green = GetGValue(color);
		blue = GetBValue(color);
		char redbuff[5];
		char greenbuff[5];
		char bluebuff[5];
		std::sprintf(redbuff, "%d", red);
		std::sprintf(greenbuff, "%d", green);
		std::sprintf(bluebuff, "%d", blue);
		*red_text = redbuff;
		*green_text = greenbuff;
		*blue_text = bluebuff;
		::SendMessage(hdlg, WM_UPDATEDATA, FALSE, 0);
		::Sleep(10);
	}
    return 0;
}

std::deque<HWND> hwnds;
DWORD lwa_alpha = LWA_ALPHA;
BYTE value;
CSliderCtrl *slider;
bool opacity = true;
DWORD WINAPI savewindow(LPVOID) {
	while (true) {
		if (!opacity) {
			::Sleep(10);
			continue;
		}
		HWND h = ::GetForegroundWindow();
		WCHAR windowname[250];
		::GetWindowText(h, windowname, 250);
		bool ispushed = false;
		for (auto it = hwnds.begin(); it != hwnds.end();) {
			if (h == *it) {
				it = hwnds.erase(it);
				hwnds.push_back(h);
				ispushed = true;
				if (h != hdlg) {
					GetLayeredWindowAttributes(h, NULL, &value, &lwa_alpha);
					slider->SetPos(value);
				}
				break;
			} else
				it++;
		}
		if (h && !ispushed)
			hwnds.push_back(h);
		::Sleep(10);
	}
	return 0;
}


HWND hchrome = NULL;
void refreshchrome() {	//更新chrome网页
	hchrome = NULL;
	hchrome=FindWindow(_T("Chrome_WidgetWin_1"), NULL);
		if (hchrome != NULL) {
		hchrome=GetParent(hchrome);		//要从浏览器子窗口句柄找到父窗口句柄
		::SetForegroundWindow(hchrome);
		Sleep(5);
		::SendMessage(hchrome, WM_KEYDOWN, VK_F5, 0);
		::SendMessage(hchrome, WM_KEYUP, VK_F5, 0);
	}
}

WCHAR  dirname[MAX_PATH]; 
bool isfresh = true;
DWORD WINAPI checkfile(LPVOID) {
	while (true) {
		if (!isfresh || dirname[0] == 0) {
			::Sleep(10);
			continue;
		}
		HANDLE hcheck = ::FindFirstChangeNotification(dirname, true, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE);
		if (hcheck == INVALID_HANDLE_VALUE) {
			::MessageBox(NULL, _T("创建线程失败") , _T("失败"), MB_OK);
			return -1;		
		}
		DWORD ret = ::WaitForSingleObject(hcheck, INFINITE);
		if (ret == WAIT_FAILED)
			::MessageBox(NULL, _T("等待失败") , _T("失败"), MB_OK);
		else if (isfresh) {
			//::MessageBox(NULL, dirname , _T("文件改变"), MB_OK);
			refreshchrome();
		}
	}
	return 0;
}

BOOL ChtmltoolDlg::OnInitDialog()
{
	hdlg = this->m_hWnd;
	CDialogEx::OnInitDialog();

	// 创建显示颜色线程
	red_text = &m_red;
	green_text = &m_green;
	blue_text = &m_blue;
	CreateThread(NULL, 0, getcolor, NULL, 0, NULL);

	// 创建显示透明度线程
	slider = &m_slider;
	m_slider.SetRangeMax(255);
	m_slider.SetTicFreq(10);
	m_slider.SetLineSize(2);
	m_slider.SetPageSize(10);
	m_slider.SetPos(255);
	CreateThread(NULL, 0, savewindow, NULL, 0, NULL);

	// 创建监视文件线程
	CreateThread(NULL, 0, checkfile, NULL, 0, NULL);


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
	int sysX=GetSystemMetrics(SM_CXSCREEN);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, sysX-482, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ChtmltoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void ChtmltoolDlg::OnPaint()
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
HCURSOR ChtmltoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



afx_msg LRESULT ChtmltoolDlg::OnUpdatedata(WPARAM wParam, LPARAM lParam)
{
	UpdateData(false);
	return 0;
}


void ChtmltoolDlg::OnTRBNThumbPosChangingSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

DWORD arg = LWA_ALPHA;
HWND hset;
void ChtmltoolDlg::OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	if (!opacity)
		return;
	// TODO: 在此添加控件通知处理程序代码

	WCHAR windowname[250];

	HWND  hset;
	if (hwnds.size())
		hset = hwnds.back();
	if (hset == hdlg && hwnds.size() >= 2) {
		hset = hwnds[hwnds.size()-2];
		value = (*slider).GetPos();
		SetWindowLong(hset,GWL_EXSTYLE, 0x80000);
		::SetLayeredWindowAttributes(hset, NULL, value, LWA_ALPHA);
	}
}


void ChtmltoolDlg::OnBnClickedButtonOpacity()
{
	// TODO: 在此添加控件通知处理程序代码
	if (opacity) {
		slider->EnableWindow(false);
		button_opacity.SetWindowTextW(_T("开"));
	} else {
		slider->EnableWindow(true);
		button_opacity.SetWindowTextW(_T("关"));
	}
	opacity = !opacity;
}

void ChtmltoolDlg::OnBnClickedButtonFresh()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!isfresh) {
		m_fresh.SetWindowTextW(_T("关"));
		m_choosefile.EnableWindow(true);
		isfresh = true;
	} else {
		m_fresh.SetWindowTextW(_T("开"));
		m_choosefile.EnableWindow(false);
		isfresh = false;
	}
}

void ChtmltoolDlg::OnBnClickedButtonChoosefile()
{
	// TODO: 在此添加控件通知处理程序代码
	isfresh = false;
	BROWSEINFO bi; 

	LPITEMIDLIST pidl; 
	LPMALLOC pMalloc = NULL;  
	ZeroMemory(&bi, sizeof(bi));      
	bi.hwndOwner = GetSafeHwnd(); 
	bi.pszDisplayName = dirname; 
	bi.lpszTitle = _T("请选择目录,发现改动会刷新chrome浏览器:"); 
	bi.ulFlags = BIF_RETURNONLYFSDIRS;  
	pidl = SHBrowseForFolder(&bi); 
	CString sPath;

	if (pidl) { 
		SHGetPathFromIDList(pidl, dirname); // set the directory name. 
		sPath = dirname; // m_sPath是CString變量，最後結果在這兒。
	}
	//::MessageBox(NULL, dirname , _T("file"), MB_OK);
	isfresh = true;
}
