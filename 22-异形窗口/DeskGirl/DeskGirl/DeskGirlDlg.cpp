
// DeskGirlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DeskGirl.h"
#include "DeskGirlDlg.h"
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


// CDeskGirlDlg 对话框




CDeskGirlDlg::CDeskGirlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeskGirlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeskGirlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GIRL, m_girl);
}

BEGIN_MESSAGE_MAP(CDeskGirlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


int flag = 0;
CStatic *pgirl;
CBitmap mybitmap1;
CBitmap mybitmap2;
CBitmap mybitmap3;
#define MY_TIMER 1234
VOID CALLBACK eyes(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime) {
	if (flag == 0) {
		pgirl->SetBitmap(mybitmap1);
	} else if (flag == 14) {
		pgirl->SetBitmap(mybitmap2);
	} else if (flag == 15) {
		pgirl->SetBitmap(mybitmap3);
	}
	flag = (flag+1)%16;
}


// CDeskGirlDlg 消息处理程序

BOOL CDeskGirlDlg::OnInitDialog()
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
	pgirl = &m_girl;
	CBitmap bmpdlg;
	bmpdlg.LoadBitmap(IDB_BITMAP_DLG);

	CDC *pdc=GetWindowDC();
	CDC cdc;
	cdc.CreateCompatibleDC(pdc);
	cdc.SelectObject(&bmpdlg);

	CRect rect;
	CRgn rgn, temprgn;
	GetClientRect(&rect);
	rgn.CreateRectRgnIndirect(rect);
	int width = rect.Width();
	int height = rect.Height();
	COLORREF del = cdc.GetPixel(0, 0);
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++) {
			if (cdc.GetPixel(x, y)==del) {
				temprgn.CreateRectRgn(x,y,x+1,y+1);
				rgn.CombineRgn(&rgn, &temprgn, RGN_XOR);
				temprgn.DeleteObject();
			}
		}
	SetWindowRgn(rgn, true);
	mybitmap1.LoadBitmap(IDB_BITMAP2);
	mybitmap2.LoadBitmap(IDB_BITMAP3);
	mybitmap3.LoadBitmap(IDB_BITMAP4);
	::SetTimer(NULL, MY_TIMER, 150, eyes);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDeskGirlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDeskGirlDlg::OnPaint()
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
HCURSOR CDeskGirlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDeskGirlDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}

