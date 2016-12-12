
// FileMonitorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileMonitor.h"
#include "FileMonitorDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE hmonitor = NULL;
WCHAR  dirname[MAX_PATH+50]; 
CListBox *mylistbox;
void setlistbox(int size);
bool start = false;
WCHAR timebuff[MAX_PATH+50];

void gettime(bool style = true) {
	CTime time = CTime::GetCurrentTime();///构造CTime对象
	int m_nYear = time.GetYear();///年
	int m_nMonth = time.GetMonth();///月
	int m_nDay = time.GetDay();///日
	int m_nHour = time.GetHour();///小时
	int m_nMinute = time.GetMinute();///分钟
	int m_nSecond = time.GetSecond();///秒
	CString m_strTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	if (!style)
		m_strTime = time.Format(_T("%Y-%m-%d %H;%M;%S"));
	WCHAR *buff = m_strTime.GetBuffer(MAX_PATH+50);
	std::wcscpy(timebuff, buff);
	m_strTime.ReleaseBuffer();
}

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


// CFileMonitorDlg 对话框




CFileMonitorDlg::CFileMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileMonitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTBOX, listbox);
	DDX_Control(pDX, IDC_BUTTON_START, button_start);
}

BEGIN_MESSAGE_MAP(CFileMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSEFILE, &CFileMonitorDlg::OnBnClickedButtonChoosefile)
	ON_BN_CLICKED(IDC_BUTTON_START, &CFileMonitorDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CFileMonitorDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CFileMonitorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CFileMonitorDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()


DWORD WINAPI monitor(LPVOID) {
	bool once = true;
	BOOL bRet = FALSE;
	BYTE Buffer[1024] = {0};

	FILE_NOTIFY_INFORMATION *pBuffer = (FILE_NOTIFY_INFORMATION *)Buffer;
	DWORD dwByteReturn = 0;
	HANDLE hFile = ::CreateFile(dirname, FILE_LIST_DIRECTORY, 
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if(INVALID_HANDLE_VALUE == hFile) {
		::MessageBox(NULL, _T("打开文件目录错误"), _T("错误"), MB_ICONERROR);
		return 1;
	}
	while(TRUE) {
		::ZeroMemory(Buffer, sizeof(Buffer));
		bRet = ::ReadDirectoryChangesW(hFile, 
			&Buffer,
			sizeof(Buffer),
			TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME |			// 修改文件名
			FILE_NOTIFY_CHANGE_ATTRIBUTES |			// 修改文件属性
			FILE_NOTIFY_CHANGE_LAST_WRITE,			// 最后一次写入
			&dwByteReturn, NULL, NULL);				
		if(TRUE == bRet) {
			char szFileName[MAX_PATH+50] = {0};

			// 款字符转换为多字节
			::WideCharToMultiByte(CP_ACP,
				0,
				pBuffer->FileName,
				(pBuffer->FileNameLength / 2),
				szFileName,
				MAX_PATH+50,
				NULL,
				NULL);
			switch(pBuffer->Action) {
				case FILE_ACTION_ADDED:
					{
						once = true;
						WCHAR buff[MAX_PATH+50];
						gettime();
						std::wcscpy(buff, timebuff);
						std::wcscat(buff, _T("     \t"));
						std::wcscat(buff, _T("添加: "));
						std::wcscat(buff, pBuffer->FileName);
						setlistbox(wcslen(buff));
						mylistbox->AddString(buff);
						break;
					}
				case FILE_ACTION_REMOVED:
					{
						WCHAR buff[MAX_PATH+50]; 
						gettime();
						std::wcscpy(buff, timebuff);
						std::wcscat(buff, _T("     \t"));
						std::wcscat(buff, _T("删除: "));
						std::wcscat(buff, pBuffer->FileName);
						setlistbox(wcslen(buff));
						mylistbox->AddString(buff);
						break;
					}
				case FILE_ACTION_MODIFIED:
					{
						if (!once) {
							once = !once;
							break;
						}
						once = !once;
						WCHAR buff[MAX_PATH+50]; 
						gettime();
						std::wcscpy(buff, timebuff);
						std::wcscat(buff, _T("     \t"));
						std::wcscat(buff, _T("修改: "));
						std::wcscat(buff, pBuffer->FileName);
						setlistbox(wcslen(buff));
						mylistbox->AddString(buff);
						break;
					}
				case FILE_ACTION_RENAMED_OLD_NAME:
					{
						once = false;	//防止重复记录
						WCHAR buff[MAX_PATH+50]; 
						gettime();
						std::wcscpy(buff, timebuff);
						std::wcscat(buff, _T("     \t"));
						std::wcscat(buff, _T("重命名: "));
						std::wcscat(buff, pBuffer->FileName);
						if(0 != pBuffer->NextEntryOffset) {
							FILE_NOTIFY_INFORMATION *tmpBuffer = (FILE_NOTIFY_INFORMATION *)
								((DWORD)pBuffer + pBuffer->NextEntryOffset);
							switch(tmpBuffer->Action)
								{
									case FILE_ACTION_RENAMED_NEW_NAME:
										{
												::ZeroMemory(szFileName, MAX_PATH+50);
												::WideCharToMultiByte(CP_ACP,
													0,
													tmpBuffer->FileName,
													(tmpBuffer->FileNameLength / 2),
													szFileName,
													MAX_PATH+50,
													NULL,
													NULL);
												std::wcscat(buff, _T(" -> "));
												std::wcscat(buff, tmpBuffer->FileName);
												setlistbox(wcslen(buff));
												mylistbox->AddString(buff);
												break;
										}
								}
						}
						break;
					}
				case FILE_ACTION_RENAMED_NEW_NAME:
					{
						WCHAR buff[MAX_PATH+50]; 
						gettime();
						std::wcscpy(buff, timebuff);
						std::wcscat(buff, _T("     \t"));
						std::wcscat(buff, _T("重命名: "));
						std::wcscat(buff, pBuffer->FileName);
						setlistbox(wcslen(buff));
						mylistbox->AddString(buff);
						break;
					}
				}
		}
	}


	return 0;
}

// CFileMonitorDlg 消息处理程序
BOOL CFileMonitorDlg::OnInitDialog()
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
	mylistbox = &listbox;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFileMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileMonitorDlg::OnPaint()
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
HCURSOR CFileMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int max = 0;
void setlistbox(int oldsize) {
	int size = oldsize * 8.5;
	if (size > max) {
		max = size;
		mylistbox->SetHorizontalExtent(max);
	}
}


void CFileMonitorDlg::OnBnClickedButtonChoosefile()
{
	// TODO: 在此添加控件通知处理程序代码
	bool pause = false;
	if (hmonitor != NULL) {
		OnBnClickedButtonStart();
		pause = true;
	}

	BROWSEINFO bi; 

	LPITEMIDLIST pidl; 
	LPMALLOC pMalloc = NULL;  
	ZeroMemory(&bi, sizeof(bi));      
	bi.hwndOwner = GetSafeHwnd(); 
	bi.pszDisplayName = dirname; 
	bi.lpszTitle = _T("\n请选择监视目录:"); 
	bi.ulFlags = BIF_RETURNONLYFSDIRS;  
	pidl = SHBrowseForFolder(&bi); 
	CString sPath;

	if (pidl) { 
		SHGetPathFromIDList(pidl, dirname); 
		sPath = dirname; 
	} else {
		if (dirname[0] == '\0')
			::MessageBox(NULL, _T("未选择目录"), _T("错误"), MB_ICONERROR);
		//memset(dirname, 0, MAX_PATH+50);
	}
	if (dirname[0] != '\0') {
		WCHAR buff[MAX_PATH+50]; 
		std::wcscpy(buff, _T("已选择目录: "));
		std::wcscat(buff, dirname);
		setlistbox(wcslen(buff));
		listbox.AddString(buff);
	}

	if (pause) {
		OnBnClickedButtonStart();
	}
}

void CFileMonitorDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (dirname[0] == '\0') {
		::MessageBox(NULL, _T("选择目录错误"), _T("错误"), MB_ICONERROR);
		return;
	}
	if (!start) {
		button_start.SetWindowTextW(_T("关闭监视"));
		hmonitor = ::CreateThread(NULL, 0, monitor, NULL, 0, NULL);
		listbox.EnableWindow(true);
	} else {
		button_start.SetWindowTextW(_T("开始监视"));
		::TerminateThread(hmonitor, 0);
		listbox.EnableWindow(false);
	}
	start = !start;
}


WCHAR  exportdir[MAX_PATH+50]; 
WCHAR filetxt[5000000];
char filetxt2[5000000];
std::ofstream of;

void createfile() {

	WCHAR name[MAX_PATH+50];
	std::wcscpy(name, exportdir);
	std::wcscat(name, _T("\\"));
	gettime(false);
	std::wcscat(name, timebuff);
	std::wcscat(name, _T("目录修改记录.txt"));

	char openname[MAX_PATH+50]; 
	WideCharToMultiByte(CP_OEMCP, NULL, name, -1, openname, sizeof(name), NULL, false);
	of.open(openname,  std::ofstream::out | std::ios::app);
	if (!of) {
		::MessageBox(NULL, _T("创建错误"), _T("错误"), MB_ICONERROR);
		return;
	}
	WideCharToMultiByte(CP_OEMCP, NULL, filetxt, -1, filetxt2, sizeof(filetxt), NULL, false);
	of << filetxt2;
}

void closefile() {
	of.close();
}

void CFileMonitorDlg::OnBnClickedButtonExport()
{
	// TODO: 在此添加控件通知处理程序代码
	BROWSEINFO bi; 

	LPITEMIDLIST pidl; 
	LPMALLOC pMalloc = NULL;  
	ZeroMemory(&bi, sizeof(bi));      
	bi.hwndOwner = GetSafeHwnd(); 
	bi.pszDisplayName = exportdir; 
	bi.lpszTitle = _T("\n请选择导出文件目录:"); 
	bi.ulFlags = BIF_RETURNONLYFSDIRS;  
	pidl = SHBrowseForFolder(&bi); 
	CString sPath;

	if (pidl) { 
		SHGetPathFromIDList(pidl, exportdir); 
		sPath = exportdir; 

		::memset(filetxt, 0 , sizeof(filetxt));
		::memset(filetxt2, 0 , sizeof(filetxt));
		WCHAR mybuff[MAX_PATH+50];
		::memset(mybuff, 0 , sizeof(mybuff));
		for (int i = 0; i < listbox.GetCount(); i++) {
			listbox.GetText(i, mybuff);
			std::wcscat(filetxt, mybuff);
			std::wcscat(filetxt, _T("\r\n"));
		}

		createfile();
		closefile();
		::MessageBox(NULL, exportdir, _T("成功导出到"), MB_ICONINFORMATION);
	}
}


void CFileMonitorDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	mylistbox->SetHorizontalExtent(0);
	listbox.ResetContent();
}


void CFileMonitorDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}
