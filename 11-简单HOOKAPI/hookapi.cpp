#include <windows.h>
#include <iostream>
using namespace std;

typedef HANDLE (WINAPI* OldOpenProcess)(DWORD, BOOL, DWORD);	//原API地址
OldOpenProcess openprocess=NULL;	//指向原函数的指针  
FARPROC pfOldOpenProcess=NULL;  //指向函数的远指针

HANDLE WINAPI fakeOpenProcess(DWORD, BOOL, DWORD )  {		//假API定义
	::MessageBox(NULL, "123", "123", MB_OK);
    return NULL;
}  

void getapi() {		//获取原API地址
	  HMODULE hmodule=::LoadLibrary("kernel32.dll");
	  openprocess=(OldOpenProcess)::GetProcAddress(hmodule, "OpenProcess");  
	  pfOldOpenProcess=(FARPROC)openprocess; 
}

BYTE OldCode[5];
BYTE NewCode[5]; 
void savecode() {
	_asm  {		// 将原API的入口前5个字节代码保存到OldCode[]  
		lea edi,OldCode //获取OldCode数组的地址,放到edi  
		mov esi,pfOldOpenProcess //获取原API入口地址，放到esi  
		cld    //方向标志位，为以下两条指令做准备  
		movsd //复制原API入口前4个字节到OldCode数组  
		movsb //复制原API入口第5个字节到OldCode数组  
	}

	_asm  {	//获取fakeOpenProcess的相对地址,为Jmp做准备,5个字节 
		lea eax,fakeOpenProcess //获取假API的fakeOpenProcess函数地址  
		mov ebx,pfOldOpenProcess  //原系统API函数地址  
		sub eax,ebx           //int nAddr = UserFunAddr - SysFunAddr  
		sub eax,5             //nAddr=nAddr-5  
		mov dword ptr [NewCode+1],eax //一个函数地址占4个字节,将算出的地址nAddr保存到NewCode后面4个字节
	}
	NewCode[0]=0xe9; //NewCode第一个字节为JMP
}

void hookapi() {
	DWORD dwTemp=0;  
	DWORD dwOldProtect=0;
	DWORD dwPid=::GetCurrentProcessId();
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,0,dwPid);
	VirtualProtectEx(hProcess, pfOldOpenProcess, 5, PAGE_READWRITE, &dwOldProtect);    //改变在自身内存区域的保护属性
	WriteProcessMemory(hProcess, pfOldOpenProcess, NewCode, 5, 0);  //修改API函数入口前5个字节为jmp xxxxxx  
	VirtualProtectEx(hProcess, pfOldOpenProcess, 5, dwOldProtect, &dwTemp);  
}

void test() {
    HWND h = ::FindWindow(NULL, "C:\Documents and Settings\Administrator\桌面\hookapi\Debug\1.exe");  //  寻找并打开进程
    DWORD processid = 0;
    GetWindowThreadProcessId(h, &processid);
    HANDLE hprocess = 0;
    hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
}

void unhookapi() {   
	DWORD dwTemp=0;  
	DWORD dwOldProtect=0;
	DWORD dwPid=::GetCurrentProcessId();
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,0,dwPid);
	VirtualProtectEx(hProcess, pfOldOpenProcess, 5, PAGE_READWRITE, &dwOldProtect);    //改变在自身内存区域的保护属性
	WriteProcessMemory(hProcess, pfOldOpenProcess, OldCode, 5, 0);  //修改API函数入口前5个字节为jmp xxxxxx  
	VirtualProtectEx(hProcess, pfOldOpenProcess, 5, dwOldProtect, &dwTemp);     
}  

int main() {
	getapi();
	savecode();
	unhookapi();
	hookapi();
	test();
	unhookapi();
	test();
	return 0;

}