
// taskmgrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "taskmgr.h"
#include "taskmgrDlg.h"
#include "afxdialogex.h"
#include <tlhelp32.h>

///////////////////////////////////////////////////////////////////////////
#include <vector>
#include <algorithm>

typedef  DWORD (WINAPI *SUSPENDPROCESS)(HANDLE);
typedef  DWORD (WINAPI *RESUMEPROCESS)(HANDLE);

SUSPENDPROCESS SuspendProcess;
RESUMEPROCESS ResumeProcess;

HINSTANCE InitDll() {
	HINSTANCE hDllInstance = LoadLibrary(_T("NTDLL.DLL"));	//加载nt.dll
	if (hDllInstance != NULL) {
		SuspendProcess = (SUSPENDPROCESS)GetProcAddress(hDllInstance, "ZwSuspendProcess");	//加载SuspendProcess
		if (NULL == SuspendProcess) {
			MessageBox(NULL, _T("ntdll.dll打不到函数ZwSuspendProcess"), _T("失败"), MB_ICONERROR);
			CloseHandle(hDllInstance);
			return NULL;
		}
		ResumeProcess = (RESUMEPROCESS)GetProcAddress(hDllInstance, "ZwResumeProcess");	//加载ResumeProcess
		if (NULL == ResumeProcess) {
			MessageBox(NULL, _T("ntdll.dll打不到函数ResumeProcess"), _T("失败"), MB_ICONERROR);
			CloseHandle(hDllInstance);
			return NULL;
		}
	} else  {
		MessageBox(NULL, _T("NTDll.dll文件丢失或装载失败, 程序功能无法实现"), _T("失败"), MB_ICONERROR);
		return NULL;
	}
	return hDllInstance;
}








////////////////////////////////////////////////////////////////////////////
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


// CtaskmgrDlg 对话框




CtaskmgrDlg::CtaskmgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtaskmgrDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtaskmgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list_process);
}

BEGIN_MESSAGE_MAP(CtaskmgrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FRESH, &CtaskmgrDlg::OnBnClickedButtonFresh)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CtaskmgrDlg::OnLvnColumnclickList1)
	ON_BN_CLICKED(IDC_BUTTON_KILL, &CtaskmgrDlg::OnBnClickedButtonKill)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CtaskmgrDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CtaskmgrDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CtaskmgrDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CtaskmgrDlg 消息处理程序
CListCtrl *listctrl;
BOOL CtaskmgrDlg::OnInitDialog()
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
	list_process.InsertColumn(0, _T("进程名称"),  0, 190);
	list_process.InsertColumn(1, _T("进程ID号"),  0, 100);
	list_process.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listctrl = &list_process;
	 InitDll();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtaskmgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtaskmgrDlg::OnPaint()
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
HCURSOR CtaskmgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtaskmgrDlg::OnBnClickedButtonFresh()
{
	// TODO: 在此添加控件通知处理程序代码
	list_process.DeleteAllItems();

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	HANDLE hpsnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);	//当前所有进程快照
	if (hpsnap == INVALID_HANDLE_VALUE)
		::MessageBox(NULL, _T("CreateToolhelp32Snapshot错误"),  _T("失败"), MB_ICONERROR);

	int i = 0;
	BOOL bnext = ::Process32First(hpsnap, &pe32);	//遍历当前进程快照
	while (bnext) {
		list_process.InsertItem(i, pe32.szExeFile);
		CString buff;
		buff.Format(_T("%d"), pe32.th32ProcessID);
		list_process.SetItemText(i, 1, buff);
		bnext = ::Process32Next(hpsnap, &pe32);
	}

	::CloseHandle(hpsnap);
}


int nameup = -1;
int idup = -1;

 int   CALLBACK   cmp(LPARAM   lParam1,   LPARAM   lParam2,   LPARAM   lParamSort) {
	 if (lParamSort == 0) {		//对进程名称排序
		 if (nameup == -1 || nameup == 1) {
			CString strItem1   =   listctrl->GetItemText(lParam1,   0);  
			CString strItem2   =   listctrl->GetItemText(lParam2,   0); 
			return wcscmp(strItem1, strItem2);
		 } else {
			CString strItem1   =   listctrl->GetItemText(lParam1,   0);  
			CString strItem2   =   listctrl->GetItemText(lParam2,   0); 
			return wcscmp(strItem2, strItem1);
		 }
	 } else {		//对进程ID排序
		 if (idup == -1 || idup == 1) {
			CString strItem1   =   listctrl->GetItemText(lParam1,   1);  
			CString strItem2   =   listctrl->GetItemText(lParam2,   1); 
			return _ttoi(strItem1) > _ttoi(strItem2);
		 } else {
			CString strItem1   =   listctrl->GetItemText(lParam1,   1);  
			CString strItem2   =   listctrl->GetItemText(lParam2,   1); 
			return _ttoi(strItem1) < _ttoi(strItem2);
		 }
	 }
	 return 0;
 }

void CtaskmgrDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int col = pNMLV->iItem;					//列索引
	int row = pNMLV->iSubItem;				//行索引

	if (col == -1) {
		CHeaderCtrl* pListHeader = list_process.GetHeaderCtrl();
		HDITEM hditem;
		enum   { sizeOfBuffer = 256 };
		TCHAR  lpBuffer[sizeOfBuffer];
		hditem.mask = HDI_TEXT;
		hditem.pszText = lpBuffer;
		hditem.cchTextMax = sizeOfBuffer;
		pListHeader->GetItem(0, &hditem);
		if (row == 0) {				//按进程名称排序
			for(int i=0;i<list_process.GetItemCount();i++)  
				list_process.SetItemData(i,i);
			list_process.SortItems(cmp, 0);

			if (nameup == -1 || nameup == 1) {
				hditem.pszText = _T("进程名称▲");
				pListHeader->SetItem(0, &hditem);
				nameup = 0;
			} else {
				hditem.pszText = _T("进程名称▼");
				pListHeader->SetItem(0, &hditem);
				nameup = 1;
			}
			hditem.pszText = _T("进程id号");
			pListHeader->SetItem(1, &hditem);
		} else if (row == 1) {	//按进程ID号排序
			for(int i=0;i<list_process.GetItemCount();i++)  
				list_process.SetItemData(i,i);
			list_process.SortItems(cmp, 1);

			pListHeader->GetItem(1, &hditem);
			if (idup == -1 || idup == 1) {
				hditem.pszText = _T("进程id号▲");
				pListHeader->SetItem(1, &hditem);
				idup = 0;
			 } else {
				hditem.pszText = _T("进程id号▼");
				pListHeader->SetItem(1, &hditem);
				idup = 1;
			 }
			hditem.pszText = _T("进程名称");
			pListHeader->SetItem(0, &hditem);
		}
	}
	*pResult = 0;
}

void CtaskmgrDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	WCHAR buff[250];
	TRACE("%d ", list_process.GetSelectionMark());
	list_process.GetItemText(list_process.GetSelectionMark(), 0, buff, sizeof(buff));
	TRACE(buff);
	TRACE(" ");
	list_process.GetItemText(list_process.GetSelectionMark(), 1, buff, sizeof(buff));
	TRACE(buff);
	TRACE("\n");
	*pResult = 0;
}


void CtaskmgrDlg::OnBnClickedButtonKill()
{
	// TODO: 在此添加控件通知处理程序代码
	int selectitem = list_process.GetSelectionMark();
	if (selectitem == -1) {
		::MessageBox(NULL, _T("未选中目标"), _T("错误"), MB_ICONERROR);
		return;
	}
	WCHAR buff[250];
	list_process.GetItemText(list_process.GetSelectionMark(), 1, buff, sizeof(buff));
	DWORD processid = _wtoi(buff);
	HANDLE hprocess = NULL;
    hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
	if (hprocess != NULL) {
		//终止进程
		BOOL ret = ::TerminateProcess(hprocess, 0);
		if (ret)
			::MessageBox(NULL, _T("已结束目标"), _T("成功"), MB_ICONINFORMATION);
		else
			::MessageBox(NULL, _T("无法结束目标"), _T("失败"), MB_ICONERROR);
	} else
		::MessageBox(NULL, _T("无法打开目标"), _T("错误"), MB_ICONERROR);
}

void CtaskmgrDlg::OnBnClickedButtonPause()
{
	 //TODO: 在此添加控件通知处理程序代码
	int selectitem = list_process.GetSelectionMark();
	if (selectitem == -1) {
		::MessageBox(NULL, _T("未选中目标"), _T("错误"), MB_ICONERROR);
		return;
	}
	WCHAR buff[250];
	list_process.GetItemText(list_process.GetSelectionMark(), 1, buff, sizeof(buff));
	DWORD processid = _wtoi(buff);
	HANDLE hprocess = NULL;
    hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
	if (hprocess != NULL) {	//冻结或恢复进程,这里好像不知道为何如果不连着冻结马上恢复的话就恢复不了
			SuspendProcess(hprocess);
			::MessageBox(NULL, _T("已冻结目标"), _T("成功"), MB_ICONINFORMATION);

			int ret = ::MessageBox(NULL,_T("如何处理选择目标进程?YES关闭NO恢复"), _T("确认"), MB_YESNO | MB_ICONQUESTION);
			if (ret ==IDYES ) {				 //关闭
				TerminateProcess(hprocess, 0);
				::MessageBox(NULL, _T("已关闭目标"), _T("成功"), MB_ICONINFORMATION);
			} else {									 //不关闭, 恢复挂起状态
				ResumeProcess(hprocess);
				::MessageBox(NULL, _T("已恢复目标"), _T("成功"), MB_ICONINFORMATION);
			}
	} else
		::MessageBox(NULL, _T("无法打开目标"), _T("错误"), MB_ICONERROR);
	CloseHandle(hprocess);
}


void CtaskmgrDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}
