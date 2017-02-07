// DllDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcDLL.h"
#include "DllDialog.h"
#include "afxdialogex.h"


// CDllDialog 对话框

IMPLEMENT_DYNAMIC(CDllDialog, CDialogEx)

CDllDialog::CDllDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDllDialog::IDD, pParent)
{

}

CDllDialog::~CDllDialog()
{
}

void CDllDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDllDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDllDialog::OnBnClickedButton1)
END_MESSAGE_MAP()

// CDllDialog 消息处理程序


void CDllDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	::MessageBox(NULL, L"对话框", L"DLL对话框", MB_ICONINFORMATION);
}
