
// MemFinderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemFinder.h"
#include "MemFinderDlg.h"
#include "afxdialogex.h"

#include "Dlg_chooseprocess.h"
#include "MemFinderClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////
CDlg_chooseprocess dlg_cp;
WCHAR g_processname[255];
DWORD g_processid;
CString *text_processname;
CDialogEx *g_dlg;
CMemFinder ce;
///////////////////////////////////////////////////////////////////////////

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


// CMemFinderDlg 对话框




CMemFinderDlg::CMemFinderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMemFinderDlg::IDD, pParent)
	, radios_value(FALSE)
	, edit_processname(_T(""))
	, cs_value(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMemFinderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, radios_type);
	DDX_Radio(pDX, IDC_RADIO1, radios_value);
	DDX_Text(pDX, IDC_EDIT1, edit_processname);
	DDX_Control(pDX, IDC_LIST1, list_memories);
	DDX_Text(pDX, IDC_EDIT2, cs_value);
}

BEGIN_MESSAGE_MAP(CMemFinderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSEPROCESS, &CMemFinderDlg::OnBnClickedButtonChooseprocess)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CMemFinderDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CMemFinderDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH2, &CMemFinderDlg::OnBnClickedButtonSearch2)
END_MESSAGE_MAP()


// CMemFinderDlg 消息处理程序

BOOL CMemFinderDlg::OnInitDialog()
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
	list_memories.InsertColumn(0, _T("内存地址"),  0, 180);
	radios_value = 0;
	UpdateData(false);
	text_processname = &edit_processname;
	g_dlg = this;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMemFinderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMemFinderDlg::OnPaint()
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
HCURSOR CMemFinderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMemFinderDlg::OnBnClickedButtonChooseprocess()
{
	// TODO: 在此添加控件通知处理程序代码
	if (dlg_cp.m_hWnd==0)
	{
		dlg_cp.Create(IDD_CHOOSEPROCESS,this);
	}
	
	dlg_cp.ShowWindow(SW_SHOW);

}

void CMemFinderDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	if (ce.m_hprocess == NULL) {
		::MessageBox(NULL, _T("未打开进程"), _T("错误"), MB_ICONERROR);
		return;
	}
	UpdateData(true);
	WCHAR *ws = cs_value.GetBuffer(20);
	DWORD value = _wtoi(ws);
	if (value || cs_value == "0") {
		ce.FindFirst(value);		//一次搜索
		for (int i = 0; i < ce.m_dwlistnum; i++) {
			list_memories.InsertItem(i, _T("0"));
			CString buff;
			buff.Format(_T("%08x"), ce.m_dwlist[i]);
			list_memories.SetItemText(i, 0, buff);
 		}
		int i = 123;
	} else {
		::MessageBox(NULL, _T("数值格式有误"), _T("错误"), MB_ICONERROR);	
	}
}


void CMemFinderDlg::OnBnClickedButtonModify()
{
	// TODO: 在此添加控件通知处理程序代码
	int selectitem = list_memories.GetSelectionMark();
	if (selectitem == -1) {
		::MessageBox(NULL, _T("未选中目标"), _T("错误"), MB_ICONERROR);
		return;
	}
	UpdateData(true);
	WCHAR *ws = cs_value.GetBuffer(20);
	DWORD value = _wtoi(ws);
	if (value || cs_value == "0") {
		ce.modify(ce.m_dwlist[selectitem], value);
		::MessageBox(NULL, _T("修改完成"), _T("成功"), MB_ICONINFORMATION);
	} else {
		::MessageBox(NULL, _T("数值格式有误"), _T("错误"), MB_ICONERROR);	
	}
}


void CMemFinderDlg::OnBnClickedButtonSearch2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (ce.m_hprocess == NULL) {
		::MessageBox(NULL, _T("未打开进程"), _T("错误"), MB_ICONERROR);
		return;
	}
	UpdateData(true);
	WCHAR *ws = cs_value.GetBuffer(20);
	DWORD value = _wtoi(ws);
	if (value || cs_value == "0") {
		ce.FindNext(value);		//二次搜索
		list_memories.DeleteAllItems();
		for (int i = 0; i < ce.m_dwlistnum; i++) {
			CString buff;
			buff.Format(_T("%08x"), ce.m_dwlist[i]);
			list_memories.InsertItem(i, _T("0"));
			list_memories.SetItemText(i, 0, buff);
		}
	} else {
		::MessageBox(NULL, _T("数值格式有误"), _T("错误"), MB_ICONERROR);	
	}
}
