#include "stdafx.h"
#include "MFCScreenshot.h"
#include "MyScreenShot.h"
#include "ScreenDlg.h"
#include <atlconv.h>
extern WCHAR savedir[255];

MyScreenShot::MyScreenShot() {
	dlg = NULL;
	ispress = false;
}
void MyScreenShot::SetDlg(ScreenDlg *wnddlg) {
	this->dlg = wnddlg;
}
void MyScreenShot::HideSelf() {
	SetWindowLong(dlg->GetParent()->m_hWnd,GWL_EXSTYLE, 0x80000);
	::SetLayeredWindowAttributes(dlg->GetParent()->m_hWnd, NULL, 0, LWA_ALPHA);
	SetWindowLong(dlg->m_hWnd,GWL_EXSTYLE, 0x80000);
	::SetLayeredWindowAttributes(dlg->m_hWnd, NULL, 150, LWA_ALPHA);
	SendMessage(dlg->m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);
	SetWindowPos(dlg->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
}
void MyScreenShot::ShowSelf() {
	SetWindowLong(dlg->GetParent()->m_hWnd,GWL_EXSTYLE, 0x80000);
	::SetLayeredWindowAttributes(dlg->GetParent()->m_hWnd, NULL, 255, LWA_ALPHA);
}
void MyScreenShot::SetWindowShape() {
		CRgn rgndlg, rgnout;
		RECT rectdlg;
		dlg->GetWindowRect(&rectdlg);
		if (ispress) {
			int dlgwidth = rectdlg.right - rectdlg.left;
			int dlgheight = rectdlg.bottom - rectdlg.top;
			int outwidth = abs(pfirst.x - pnext.x);
			int outheight = abs(pfirst.y - pnext.y);
			CheckPoint();
			rgndlg.CreateRectRgn(rectdlg.left, rectdlg.top, rectdlg.right,rectdlg.bottom);
			rgnout.CreateRectRgn(pstart.x, pstart.y, pstart.x+outwidth, pstart.y+outheight);
			//合并
			rgndlg.CombineRgn(&rgndlg,&rgnout,RGN_DIFF);
			dlg->SetWindowRgn(rgndlg, true);
		} else {
			dlg->SetWindowRgn(rgndlg, true);
		}
		rgndlg.DeleteObject();
		rgnout.DeleteObject();
}
void MyScreenShot::DrawFrame() {
	HDC hdc = ::GetWindowDC(dlg->m_hWnd);
	HPEN hpen = ::CreatePen(PS_SOLID, 5, RGB(255,0,0));
	HPEN holdpen = (HPEN)::SelectObject(hdc, hpen);

	::MoveToEx(hdc, pfirst.x, pfirst.y, NULL);
	::LineTo(hdc, pnext.x, pfirst.y);
	::LineTo(hdc, pnext.x, pnext.y);
	::LineTo(hdc, pfirst.x, pnext.y);
	::LineTo(hdc, pfirst.x, pfirst.y);
	SetWindowShape();

	::SelectObject(hdc, holdpen);
	::DeleteObject(hpen);
	::ReleaseDC(dlg->m_hWnd, hdc);
}
void MyScreenShot::EraseFrame() {
	dlg->RedrawWindow();
}
bool MyScreenShot::IsSamePoint(POINT pcheck) {
	return (pcheck.x == pnext.x && pcheck.y == pnext.y);
}
void MyScreenShot::UpdatePoint() {
	if (ispress)
		::GetCursorPos(&pnext);
	else
		::GetCursorPos(&pfirst);
}
void MyScreenShot::CheckPoint() {
	if (pnext.x <= pfirst.x && pnext.y <= pfirst.y) {			//右下拖到左上
		pstart.x = pnext.x;
		pstart.y = pnext.y;
	} else if (pnext.x > pfirst.x && pnext.y <= pfirst.y) {	//左下拖到右上
		pstart.x = pfirst.x;
		pstart.y = pnext.y;
	} else if (pnext.x > pfirst.x && pnext.y > pfirst.y) {		//左上拖到右下
		pstart.x = pfirst.x;
		pstart.y = pfirst.y;
	} else {				//右上拖到左下
		pstart.x = pnext.x;
		pstart.y = pfirst.y;
	}
}
void MyScreenShot::TakePic(char filename[]) {
    CDC *pDC;//屏幕DC
    pDC = CDC::FromHandle(GetDC(NULL));//获取当前整个屏幕DC
    int BitPerPixel = pDC->GetDeviceCaps(BITSPIXEL);//获得颜色模式
	int Width = abs(pfirst.x-pnext.x);
    int Height = abs(pfirst.y-pnext.y);
    CDC memDC;//内存DC
    memDC.CreateCompatibleDC(pDC);
    
	CheckPoint();

    CBitmap memBitmap, *oldmemBitmap;//建立和屏幕兼容的bitmap
    memBitmap.CreateCompatibleBitmap(pDC, Width, Height);
    oldmemBitmap = memDC.SelectObject(&memBitmap);//将memBitmap选入内存DC
    memDC.BitBlt(0, 0, Width, Height, pDC, pstart.x, pstart.y, SRCCOPY);//复制屏幕图像到内存DC

    //以下代码保存memDC中的位图到文件
    BITMAP bmp;
    memBitmap.GetBitmap(&bmp);//获得位图信息  
    FILE *fp = fopen(filename, "w+b");

    BITMAPINFOHEADER bih = {0};//位图信息头
    bih.biBitCount = bmp.bmBitsPixel;//每个像素字节大小
    bih.biCompression = BI_RGB;
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//图像数据大小
    bih.biWidth = bmp.bmWidth;//宽度
    bih.biHeight = bmp.bmHeight;//高度

    BITMAPFILEHEADER bfh = {0};//位图文件头
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//到位图数据的偏移量
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//文件总的大小
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//写入位图文件头 
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//写入位图信息头    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//申请内存保存位图数据
    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, Height, p, 
        (LPBITMAPINFO) &bih, DIB_RGB_COLORS);//获取位图数据
    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);//写入位图数据
    delete [] p;
    fclose(fp);
    memDC.SelectObject(oldmemBitmap);
}

void MyScreenShot::SavePic() {
	SetWindowLong(dlg->m_hWnd,GWL_EXSTYLE, 0x80000);
	::SetLayeredWindowAttributes(dlg->m_hWnd, NULL, 0, LWA_ALPHA);

	time_t t;
	time(&t);
	tm *timeinfo=localtime(&t);
	WCHAR wbuff[500];
	WCHAR wtime[500];
	wsprintf(wbuff, savedir);
	wsprintf(wtime, L"\\[截图]%02d年%02d月%02d日%02d时%02d分%02d秒.bmp",timeinfo->tm_year+1900,timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
	wcscat(wbuff, wtime);
	USES_CONVERSION ;
	TakePic(W2A(wbuff));

	SetWindowLong(dlg->m_hWnd,GWL_EXSTYLE, 0x80000);
	::SetLayeredWindowAttributes(dlg->m_hWnd, NULL, 100, LWA_ALPHA);
}