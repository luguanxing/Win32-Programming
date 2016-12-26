#include <windows.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#define MAX 500

HKEY hkey = NULL;
char src[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";	//win7可用

/*
64位目录:"HKEY_LOCAL_MACHINE\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
32位目录:"HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run"
如果你是32位系统这么写没有问题，如果你是64位系统那就写进前一个目录里面去了。
推荐的做法RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE | KEY_WOW64_64KEY, &hKey);
*/


char tar[MAX];

int autostart() {
	::GetModuleFileName(NULL, tar, MAX);	//获取自身路径

	LONG ret1 = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, src, 0, KEY_ALL_ACCESS, &hkey);	//打开注册表
	if (ret1 != ERROR_SUCCESS)
		return 1;

	LONG ret2 = ::RegSetValueEx(hkey, "test", 0, REG_SZ, (const unsigned char*)tar, MAX);	//修改注册表
	if (ret2 != ERROR_SUCCESS)
		return 2;

	return 0;
}

int main () {
	autostart();
	return 0;
};
