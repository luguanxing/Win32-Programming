#include <windows.h>
#define Dllfunciton extern "C" __declspec(dllexport)

Dllfunciton void infect();

void infect() {
	char filename[250];
	char msg[250] = "DLL Injected!";
	::GetModuleFileName(NULL, filename, 250);
	while (true) {
		::MessageBox(NULL, msg, filename, MB_OK);
		Sleep(5000);
	}
}

BOOL APIENTRY DllMain( HANDLE hModule,  DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)	//进程加载DLL时进行感染
		infect();
	if (ul_reason_for_call == DLL_THREAD_ATTACH)	//线程加载DLL时进行感染
		infect();
    return TRUE;
}


