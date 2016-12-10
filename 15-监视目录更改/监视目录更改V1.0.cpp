#include <Windows.h>
#include <iostream>
using namespace std;

char src[] = "C:\\Users\\Administrator\\Desktop\\新建文件夹";

int main() {
	while (true) {
		HANDLE hcheck = ::FindFirstChangeNotification(src, true, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE);
		if (hcheck == INVALID_HANDLE_VALUE) {
			cout << "create thread failed!" << endl;
			return -1;		
		}
		DWORD ret = ::WaitForSingleObject(hcheck, INFINITE);
		if (ret == WAIT_FAILED)
			cout << "failed" << endl;
		else
			cout << "changed" << endl;
	}
	return 0;
}

