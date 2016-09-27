#include <windows.h>
#include <winable.h> 
#include <string>
#include <fstream>
#include <iostream>
#define MAX 250
using namespace std;

char src[MAX] = "C:\\Users\\Administrator\\Desktop\\test";		//加锁文件目录
char files[MAX];	//文件列表目录
char cmd[MAX];
char file[MAX];

void encrypte() {
	char c;
	std::string filetxt = "";
	FILE *rf = fopen(file, "rb");
	while(!feof(rf)) {
		c = fgetc(rf);
		filetxt += c;
	}
	fclose(rf);
	int i = 0;
	FILE *wf = fopen(file, "wb");
	while(i < filetxt.size() - 1) 
		fputc(filetxt[i++] ^ 2, wf);	//简单进行异或加密
	fclose(wf);
}

void encrypte_files() {
	string dir = src;
	dir += "\\fileslist.txt";		//文件列表目录为fileslist.txt
	sprintf(files, dir.c_str());
	sprintf(cmd, "cmd /c dir %s\\*.* /a-d /b /s >%s", src, files);	//将src目录下所有文件路径输出保存到文件列表目录fileslist.txt
	system(cmd);

	ifstream in(files);		//逐个文件加密

	cout << "以下文件已上锁/解锁:" << endl;
	while (!in.eof()) { 
		in.getline(file, MAX);
		if (strcmp(file, "")==0)	//结束加密
			break;
		if (file == dir)	//自身不加密
			continue;
		cout << file << endl;
		encrypte();
	}
}

int main () {
	cin >> src;
	encrypte_files();
	return 0;
};
