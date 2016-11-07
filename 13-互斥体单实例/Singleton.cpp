#include <windows.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main() {

	HANDLE hobj = ::CreateMutex(NULL, false, "test-object");

	if (::GetLastError() == ERROR_ALREADY_EXISTS) {
		::MessageBox(NULL, "不能运行多个实例", "错误", MB_OK);
		exit(0);
	}

	while (1) {
		cout << "正常运行中." << endl;
		::Sleep(1000);
		system("cls");
		cout << "正常运行中.." << endl;
		::Sleep(1000);
		system("cls");
		cout << "正常运行中..." << endl;
		::Sleep(1000);
		system("cls");
	}

	::CloseHandle(hobj);

	return 0;
}