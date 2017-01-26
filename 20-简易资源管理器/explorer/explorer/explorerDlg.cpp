
// explorerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "explorer.h"
#include "explorerDlg.h"
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


// CexplorerDlg 对话框




CexplorerDlg::CexplorerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CexplorerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CexplorerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, tree);
	DDX_Control(pDX, IDC_LIST1, files);
}

BEGIN_MESSAGE_MAP(CexplorerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, &CexplorerDlg::OnTvnItemexpandingTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CexplorerDlg::OnTvnSelchangedTree1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CexplorerDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CexplorerDlg 消息处理程序

BOOL CexplorerDlg::OnInitDialog()
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
/////////////////////////////////////////////////////////////
	HTREEITEM hrootc= tree.InsertItem(L"C:");
	HTREEITEM hrootd= tree.InsertItem(L"D:");
	HTREEITEM hroote= tree.InsertItem(L"E:");
	HTREEITEM hrootf= tree.InsertItem(L"F:");
	HTREEITEM hrootg= tree.InsertItem(L"G:");
	imglist.Create(16,16, ILC_MASK | ILC_COLOR32, 0, 0);
	tree.SetImageList(&imglist, TVSIL_NORMAL);
	dfs(L"C://*.*", hrootc, 2);
	dfs(L"D://*.*", hrootd, 2);
	dfs(L"E://*.*", hroote, 2);
	dfs(L"F://*.*", hrootf, 2);
	dfs(L"G://*.*", hrootg, 2);
/////////////////////////////////////////////////////////////
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CexplorerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CexplorerDlg::OnPaint()
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
HCURSOR CexplorerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CexplorerDlg::dfs(CString path, HTREEITEM hroot, int next)		//向后代遍历两层并插入，以便显示展开按钮(重复的在遍历前应删除)
{
	if(path.Right(4) != L"/*.*")
		path+=L"//*.*";
	CFileFind cfile;
	BOOL ret = cfile.FindFile(path);
	while (ret && next) {
		ret = cfile.FindNextFile();
		if (!cfile.IsDots() && cfile.IsDirectory()) {

			SHFILEINFO psfi;
			memset(&psfi,0,sizeof(psfi));
			::SHGetFileInfo(cfile.GetFilePath(), 0, &psfi, sizeof(psfi), SHGFI_ICON | SHGFI_TYPENAME );
			 
			HTREEITEM hnew = tree.InsertItem(cfile.GetFileName(), hroot); 
			TRACE(">>>>>>>>>");
			TRACE(cfile.GetFileName());
			TRACE("\n");
			tree.SetItemImage(hnew, imglist.Add(psfi.hIcon), 0);
			dfs(cfile.GetFilePath(), hnew, next-1);
		}
	}
}


void CexplorerDlg::OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	HTREEITEM hSubItem = pNMTreeView->itemNew.hItem;

	HTREEITEM hson = tree.GetChildItem(hSubItem);		//删除重复
	while (hson != NULL) {
		tree.DeleteItem(hson);
		hson = tree.GetChildItem(hSubItem);
	}

	HTREEITEM hp =  tree.GetParentItem(hSubItem);
	CString path = tree.GetItemText(hSubItem);
	while (hp != NULL) {
		CString temp = tree.GetItemText(hp);
		path = temp +"\\"+path;
		hp =  tree.GetParentItem(hp);
	}
	dfs(path, hSubItem, 2);		//由根结构得到路径
}


void CexplorerDlg::showfiles(CString filepath)
{
	CFileFind cfindfile;
	imglist2.Create(32, 32, ILC_COLOR32|ILC_MASK, 0, 0);
	BOOL ret = cfindfile.FindFile(filepath);
	while (ret) {
		ret = cfindfile.FindNextFile();	//必须在调用之前 GetFilePath至少一个调用 FindNextFile
		WCHAR path[255];
		wcscpy(path, cfindfile.GetFilePath().GetBuffer(255));

		SHFILEINFO psfi;
		memset(&psfi,0,sizeof(psfi));
		::SHGetFileInfo(path, 0, &psfi, sizeof(psfi), SHGFI_ICON);

		if (cfindfile.GetFileName() == "." || cfindfile.GetFileName() == "..")
			continue;

		imglist2.Add(psfi.hIcon);
		int sum = files.GetItemCount();
		files.InsertItem(sum, cfindfile.GetFileName(), sum);
	}
	files.SetImageList(&imglist2, LVSIL_NORMAL);

	cfindfile.Close();
}


void CexplorerDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hSubItem = tree.GetSelectedItem();
	HTREEITEM hp =  tree.GetParentItem(hSubItem);
	CString path = tree.GetItemText(hSubItem);
	while (hp != NULL) {
		CString temp = tree.GetItemText(hp);
		path = temp +"\\"+path;
		hp =  tree.GetParentItem(hp);
	}
	TRACE(path);
	TRACE("\n");
	files.DeleteAllItems();   //删除内容
	showfiles(path+L"//*.*");

	*pResult = 0;
}


void CexplorerDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = files.GetFirstSelectedItemPosition();
	if (pos) {
		int index = files.GetNextSelectedItem(pos);
		CString filename = files.GetItemText(index, 0);

		HTREEITEM hSubItem = tree.GetSelectedItem();
		HTREEITEM hp =  tree.GetParentItem(hSubItem);
		CString path = tree.GetItemText(hSubItem);
		while (hp != NULL) {
			CString temp = tree.GetItemText(hp);
			path = temp +"\\"+path;
			hp =  tree.GetParentItem(hp);
		}

		CString file = path + "\\" + filename;
		::ShellExecute(0, 0, file, 0, 0, SW_SHOWNORMAL);
	}
	*pResult = 0;
}
