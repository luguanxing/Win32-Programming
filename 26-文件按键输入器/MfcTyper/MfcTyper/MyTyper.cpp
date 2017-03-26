#include "stdafx.h"
#include "MfcTyper.h"
#include "MyTyper.h"
#include "MfcTyperDlg.h"
#include <atlconv.h>
#include <iostream>
#include <fstream>

CMfcTyperDlg *g_pdlg;
MyTyper *pmt;
MyTyper::MyTyper() {
	pdlg = NULL;
	pmt = this;
}

void MyTyper::SetDlg(CMfcTyperDlg *wnddlg) {
	pdlg = wnddlg;
	g_pdlg = pdlg;
}


int left_time = 0;
DWORD WINAPI CountDown(LPVOID lpParam) {
	left_time = 3;
	WCHAR cs_btn_old[300];
	g_pdlg->btn_start.GetWindowText(cs_btn_old, 300);
	g_pdlg->btn_start.EnableWindow(false);
	while (left_time >= 0) {
		WCHAR buff[300];
		WCHAR bufft[5];
		std::swprintf(buff, cs_btn_old);
		std::swprintf(bufft, L"(%d)", left_time);
		std::wcscat(buff, bufft);
		g_pdlg->btn_start.SetWindowText(buff);
		left_time--;
		::Sleep(1000);
	}
	g_pdlg->btn_start.SetWindowText(cs_btn_old);
	pmt->StartPrint();
	return 0;
}

void MyTyper::Init() {
	if (pdlg->cs_path != "") {
		USES_CONVERSION;
		std::ifstream in(W2A(pdlg->cs_path));
		if(!in) {
			::MessageBoxA(NULL, "打开文件失败", "错误", MB_ICONERROR);
			return;
		} else {
			in.close();
			CreateThread(NULL, 0, CountDown, NULL, 0, NULL);
		}
	} else {
			::MessageBoxA(NULL, "未选择文件", "错误", MB_ICONERROR);
			return;
	}
}


BYTE scan_code(DWORD pKey) {
    const DWORD result = MapVirtualKey(pKey, 0);
    return static_cast<BYTE>(result);
}

void PreessKey(char c) {
	if ('a' <= c && c <= 'z') {
		keybd_event(c+ 'A'-'a', scan_code(c+ 'A'-'a'), 0, 0);
		keybd_event(c+ 'A'-'a', scan_code(c+ 'A'-'a'), KEYEVENTF_KEYUP, 0);
	} else if (('A' <= c && c <= 'Z')) {
		keybd_event(VK_CAPITAL, scan_code(VK_CAPITAL), 0, 0);
		keybd_event(c, scan_code(c), 0, 0);
		keybd_event(c, scan_code(c), KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CAPITAL, scan_code(VK_CAPITAL), KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CAPITAL, scan_code(VK_CAPITAL), 0, 0);
		keybd_event(VK_CAPITAL, scan_code(VK_CAPITAL), KEYEVENTF_KEYUP, 0);
	} else if (('0' <= c && c <= '9')) {
		keybd_event(48+ c - '0', scan_code(48+ c - '0'), 0, 0);
		keybd_event(48+ c - '0', scan_code(48+ c - '0'), KEYEVENTF_KEYUP, 0);
	}  else {
		switch (c) {
			case 32: {
				keybd_event(VK_SPACE, scan_code(VK_SPACE), 0, 0);
				keybd_event(VK_SPACE, scan_code(VK_SPACE), KEYEVENTF_KEYUP, 0);
			 } break;
			case 9: {
				keybd_event(VK_TAB, scan_code(VK_TAB), 0, 0);
				keybd_event(VK_TAB, scan_code(VK_TAB), KEYEVENTF_KEYUP, 0);
			 } break;
			case '\r': {

			 } break;
			case '\n': {
				keybd_event(VK_RETURN, scan_code(VK_RETURN), 0, 0);
				keybd_event(VK_RETURN, scan_code(VK_RETURN), KEYEVENTF_KEYUP, 0);
			 } break;
			case '!': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event('1', scan_code('1'), 0, 0);
				keybd_event('1', scan_code('1'), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '@': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event('2', scan_code('2'), 0, 0);
				keybd_event('2', scan_code('2'), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '#': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event('3', scan_code('3'), 0, 0);
				keybd_event('3', scan_code('3'), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '$': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event('4', scan_code('4'), 0, 0);
				keybd_event('4', scan_code('4'), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '%': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event('5', scan_code('5'), 0, 0);
				keybd_event('5', scan_code('5'), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '^': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event('6', scan_code('6'), 0, 0);
				keybd_event('6', scan_code('6'), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '&': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event('7', scan_code('7'), 0, 0);
				keybd_event('7', scan_code('7'), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '*': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event('8', scan_code('8'), 0, 0);
				keybd_event('8', scan_code('8'), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '(': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event('9', scan_code('9'), 0, 0);
				keybd_event('9', scan_code('9'), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case ')': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event('0', scan_code('0'), 0, 0);
				keybd_event('0', scan_code('0'), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '[': {
				keybd_event(VK_OEM_4, scan_code(VK_OEM_4), 0, 0);
				keybd_event(VK_OEM_4, scan_code(VK_OEM_4), KEYEVENTF_KEYUP, 0);
			 } break;
			case ']': {
				keybd_event(VK_OEM_6, scan_code(VK_OEM_6), 0, 0);
				keybd_event(VK_OEM_6, scan_code(VK_OEM_6), KEYEVENTF_KEYUP, 0);
			 } break;
			case '-': {
				keybd_event(VK_OEM_MINUS, scan_code(VK_OEM_MINUS), 0, 0);
				keybd_event(VK_OEM_MINUS, scan_code(VK_OEM_MINUS), KEYEVENTF_KEYUP, 0);
			 } break;
			case '=': {
				keybd_event(VK_OEM_PLUS, scan_code(VK_OEM_PLUS), 0, 0);
				keybd_event(VK_OEM_PLUS, scan_code(VK_OEM_PLUS), KEYEVENTF_KEYUP, 0);
			 } break;
			case ';': {
				keybd_event(VK_OEM_1, scan_code(VK_OEM_1), 0, 0);
				keybd_event(VK_OEM_1, scan_code(VK_OEM_1), KEYEVENTF_KEYUP, 0);
			 } break;
			case '\'': {
				keybd_event(VK_OEM_7, scan_code(VK_OEM_7), 0, 0);
				keybd_event(VK_OEM_7, scan_code(VK_OEM_7), KEYEVENTF_KEYUP, 0);
			 } break;
			case '\\' : {
				keybd_event(VK_OEM_5, scan_code(VK_OEM_5), 0, 0);
				keybd_event(VK_OEM_5, scan_code(VK_OEM_5), KEYEVENTF_KEYUP, 0);
			 } break;
			case ',': {
				keybd_event(VK_OEM_COMMA, scan_code(VK_OEM_COMMA), 0, 0);
				keybd_event(VK_OEM_COMMA, scan_code(VK_OEM_COMMA), KEYEVENTF_KEYUP, 0);	
			 } break;
			case '.': {
				keybd_event(VK_OEM_PERIOD, scan_code(VK_OEM_PERIOD), 0, 0);
				keybd_event(VK_OEM_PERIOD, scan_code(VK_OEM_PERIOD), KEYEVENTF_KEYUP, 0);
			 } break;
			case '/' : {
				keybd_event(VK_OEM_2, scan_code(VK_OEM_2), 0, 0);
				keybd_event(VK_OEM_2, scan_code(VK_OEM_2), KEYEVENTF_KEYUP, 0);
			 } break;
			case '_': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event(VK_OEM_MINUS, scan_code(VK_OEM_MINUS), 0, 0);
				keybd_event(VK_OEM_MINUS, scan_code(VK_OEM_MINUS), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '+': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event(VK_OEM_PLUS, scan_code(VK_OEM_PLUS), 0, 0);
				keybd_event(VK_OEM_PLUS, scan_code(VK_OEM_PLUS), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '{': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event(VK_OEM_4, scan_code(VK_OEM_4), 0, 0);
				keybd_event(VK_OEM_4, scan_code(VK_OEM_4), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '}': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event(VK_OEM_6, scan_code(VK_OEM_6), 0, 0);
				keybd_event(VK_OEM_6, scan_code(VK_OEM_6), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;

			case ':': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event(VK_OEM_1, scan_code(VK_OEM_1), 0, 0);
				keybd_event(VK_OEM_1, scan_code(VK_OEM_1), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '"': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event(VK_OEM_7, scan_code(VK_OEM_7), 0, 0);
				keybd_event(VK_OEM_7, scan_code(VK_OEM_7), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '|': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event(VK_OEM_5, scan_code(VK_OEM_5), 0, 0);
				keybd_event(VK_OEM_5, scan_code(VK_OEM_5), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '<': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event(VK_OEM_COMMA, scan_code(VK_OEM_COMMA), 0, 0);
				keybd_event(VK_OEM_COMMA, scan_code(VK_OEM_COMMA), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '>': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event(VK_OEM_PERIOD, scan_code(VK_OEM_PERIOD), 0, 0);
				keybd_event(VK_OEM_PERIOD, scan_code(VK_OEM_PERIOD), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
			case '?': {
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), 0, 0);
				keybd_event(VK_OEM_2, scan_code(VK_OEM_2), 0, 0);
				keybd_event(VK_OEM_2, scan_code(VK_OEM_2), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SHIFT, scan_code(VK_SHIFT), KEYEVENTF_KEYUP, 0);
			 } break;
		}
	}
}

void MyTyper::StartPrint() {
	char c;
	USES_CONVERSION;
	FILE *rf = fopen(W2A(pdlg->cs_path), "rb");
	while(!feof(rf)) {
		char c =  (char)fgetc(rf);
		PreessKey(c);
		::Sleep(10);
	}
	pdlg->btn_start.EnableWindow(true);
}