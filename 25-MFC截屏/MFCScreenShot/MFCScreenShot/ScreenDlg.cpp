// ScreenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCScreenShot.h"
#include "ScreenDlg.h"
#include "afxdialogex.h"
#include "MyScreenShot.h"

// ScreenDlg 对话框

IMPLEMENT_DYNAMIC(ScreenDlg, CDialogEx)

ScreenDlg::ScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ScreenDlg::IDD, pParent)
{

}

ScreenDlg::~ScreenDlg()
{
}

void ScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ScreenDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ScreenDlg 消息处理程序

MyScreenShot mss;
BOOL ScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mss.SetDlg(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ScreenDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	// TODO: 在此处添加消息处理程序代码
	mss.HideSelf();

	CDialogEx::OnShowWindow(bShow, nStatus);
}


void ScreenDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!mss.ispress) {
		::SetCapture(m_hWnd);
		mss.UpdatePoint();
		mss.ispress = true;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void ScreenDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mss.ispress) {
		mss.ispress = false;
		::ReleaseCapture();
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void ScreenDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACE("OnMouseMove\n");
	if (mss.ispress)  {
		POINT pcheck;
		GetCursorPos(&pcheck);
		if (!mss.IsSamePoint(pcheck)) {
			mss.EraseFrame();
			mss.UpdatePoint();
			mss.DrawFrame();
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL ScreenDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN ) {
		if (pMsg->wParam == VK_ESCAPE) {
			mss.ShowSelf();
			mss.SetWindowShape();
		} else if (pMsg->wParam == VK_RETURN) {
			mss.SavePic();
			mss.ShowSelf();
			mss.SetWindowShape();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void ScreenDlg::OnPaint()
{
	CRect rect; 
	CPaintDC dc(this); 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(100,100,100));
}
