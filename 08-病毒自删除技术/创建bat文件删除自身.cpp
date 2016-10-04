#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

HANDLE hfile;
char selfname[250];

void deleteself() {
	hfile = ::CreateFile("delself.cmd", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hfile == INVALID_HANDLE_VALUE)	//创建bat文件
		return;
	::GetModuleFileName(NULL, selfname, 250);
	string bat;
	bat = "del ";	//设置删除自身及bat文件的命令
	bat += selfname;
	bat += "\r\n del delself.cmd";
	DWORD dword;
	::WriteFile(hfile, bat.c_str(), bat.size()+1, &dword, NULL);	//写入bat文件
	::CloseHandle(hfile);
	WinExec("delself.cmd", SW_HIDE);	//应在程序接近结束时执行bat命令，避免程序还在内存中无法删除
}

int main() {
	deleteself();
	return 0;
}