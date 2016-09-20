#include <windows.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#define MAX 500

HKEY hkey = NULL;
char src[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char tar[MAX];

int autostart() {
	::GetModuleFileName(NULL, tar, MAX);

	LONG ret1 = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, src, 0, KEY_ALL_ACCESS, &hkey);
	if (ret1 != ERROR_SUCCESS)
		return 1;

	LONG ret2 = ::RegSetValueEx(hkey, "test", 0, REG_SZ, (const unsigned char*)tar, MAX);
	if (ret2 != ERROR_SUCCESS)
		return 2;

	return 0;
}

int main () {

	autostart();

	return 0;
};