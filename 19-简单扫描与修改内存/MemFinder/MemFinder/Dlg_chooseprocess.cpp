// Dlg_chooseprocess.cpp : 实现文件
//

#include "stdafx.h"
#include "MemFinder.h"
#include "Dlg_chooseprocess.h"
#include "afxdialogex.h"
///////////////////////////////////////////////////////////////////
#include <tlhelp32.h>
#include "MemFinderClass.h"
extern WCHAR g_processname[255];
extern DWORD g_processid;
extern CString *text_processname;
extern CDialogEx *g_dlg;
extern CMemFinder ce;
int nameup = -1;
int idup = -1;
CListCtrl *listctrl;
///////////////////////////////////////////////////////////////////
// CDlg_chooseprocess 对话框

IMPLEMENT_DYNAMIC(CDlg_chooseprocess, CDialogEx)

CDlg_chooseprocess::CDlg_chooseprocess(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg_chooseprocess::IDD, pParent)
{

}

CDlg_chooseprocess::~CDlg_chooseprocess()
{
}

void CDlg_chooseprocess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list_process);
}


BEGIN_MESSAGE_MAP(CDlg_chooseprocess, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CDlg_chooseprocess::OnLvnColumnclickList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlg_chooseprocess::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlg_chooseprocess::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlg_chooseprocess 消息处理程序

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

BOOL CDlg_chooseprocess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	listctrl = &list_process;

	list_process.InsertColumn(0, _T("进程名称"),  0, 100);
	list_process.InsertColumn(1, _T("进程ID号"),  0, 75);
	list_process.SetExtendedStyle(LVS_EX_FULLROWSELECT);

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
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlg_chooseprocess::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
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


void CDlg_chooseprocess::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlg_chooseprocess::OnCancel();
}


void CDlg_chooseprocess::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int selectitem = list_process.GetSelectionMark();
	if (selectitem == -1) {
		::MessageBox(NULL, _T("未选中目标"), _T("错误"), MB_ICONERROR);
		return;
	}
	list_process.GetItemText(list_process.GetSelectionMark(), 0, g_processname, sizeof(g_processname));
	WCHAR buff[250];
	list_process.GetItemText(list_process.GetSelectionMark(), 1, buff, sizeof(buff));
	g_processid = _wtoi(buff);
	*text_processname = g_processname;
	g_dlg->UpdateData(false);
	ce.set(g_processid);
	::MessageBox(NULL, _T("已选中目标"), _T("成功"), MB_ICONINFORMATION);
	CDlg_chooseprocess::OnCancel();
}
