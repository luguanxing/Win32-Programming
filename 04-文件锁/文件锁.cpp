#include <windows.h>
#include <winable.h> 
#include <string>
#include <fstream>
#include <iostream>
#define MAX 250
using namespace std;

char src[MAX] = "C:\\Users\\Administrator\\Desktop\\test";		//加锁文件目录
char files[MAX] = "C:\\Users\\Administrator\\Desktop\\out.txt";		//文件列表目录
char cmd[MAX];

int main () {

	sprintf(cmd, "cmd /c dir %s\\*.* /a-d /b /s >%s", src, files);	//遍历src目录下所有文件路径输出保存到files
	system(cmd);

	ifstream in(files);

	char file[MAX];	
	cout << "以下文件已上锁:" << endl;
	while (!in.eof()) { 
		in.getline(file, MAX);
		cout << file << endl;
		HANDLE hfile = ::CreateFile(file, GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		::LockFile(hfile, 0, 0, 0, 0);	//锁住文件
		BlockInput(true);	//未加锁完之前阻塞鼠标和键盘
	}
	BlockInput(false);
	system("pause");

	return 0;
};