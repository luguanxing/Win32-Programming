#include <windows.h>
#define Dllfunciton extern "C" __declspec(dllexport)

Dllfunciton void infect();
Dllfunciton DWORD WINAPI inject(LPVOID);

void infect() {
	char filename[250];
	char msg[250] = "DLL Injected!";
	::GetModuleFileName(NULL, filename, 250);
	while (true) {
		::MessageBox(NULL, msg, filename, MB_OK);
		Sleep(5000);
	}
}

DWORD WINAPI inject(LPVOID) {		//在新线中程执行作弊
	infect();
	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,  DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch(ul_reason_for_call) {
		case DLL_PROCESS_ATTACH: {
			::DisableThreadLibraryCalls(hModule);	//创建线程包含死循环，为防死锁必须设置
			CreateThread(NULL, 0, inject, NULL, 0, NULL);
		}
		break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
		default:;
	}
    return true;
}
