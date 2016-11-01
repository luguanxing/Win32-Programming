#include <windows.h>
#include <iostream>
using namespace std;

typedef HANDLE (WINAPI* OldOpenProcess)(DWORD, BOOL, DWORD);	//原API地址
OldOpenProcess openprocess=NULL;	//指向原函数的指针  
FARPROC pfOldOpenProcess=NULL;  //指向函数的远指针
BYTE OldCode[5];	//原函数前5字节  
BYTE NewCode[5]; 	//假函数前5字节  
HANDLE hprocess;	//进程句柄 
HANDLE hprocess2;	//自身进程句柄备份
void unhookapi();
void hookapi();


HANDLE WINAPI fakeOpenProcess(DWORD, BOOL, DWORD )  {		//假API定义
	unhookapi();
	//因为MessageBox会引发OpenProcess，故要先恢复HOOK,否则还是调用假函数，从而造成堆栈溢出，程序崩溃
	::MessageBox(NULL, "OpenProcess已被HOOK", "无法使用", MB_OK);
	hookapi();
    return NULL;
}  

void getapi() {		//获取原API地址
	  HMODULE hmodule=::LoadLibrary("kernel32.dll");
	  openprocess=(OldOpenProcess)::GetProcAddress(hmodule, "OpenProcess");  
	  pfOldOpenProcess=(FARPROC)openprocess; 
}

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
	hprocess=OpenProcess(PROCESS_ALL_ACCESS,0, ::GetCurrentProcessId());
	WriteProcessMemory(hprocess, pfOldOpenProcess, NewCode, 5, 0);  //修改API函数入口前5个字节为jmp xxxxxx  
}

void unhookapi() {
	hprocess=hprocess2;		//恢复当前进程句柄，不能用OpenProcess了
	WriteProcessMemory(hprocess, pfOldOpenProcess, OldCode, 5, 0);  //修改API函数入口前5个字节为jmp xxxxxx    
}

void test() {
    HWND h = ::FindWindow(NULL, "新建 文本文档.txt - 记事本");  //  寻找并打开进程
    DWORD processid = 0;
    GetWindowThreadProcessId(h, &processid);
    hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
	cout << "进程句柄" << hprocess << endl;
}

int main() {
	getapi();
	savecode();

	test();		//hook前用OpenProcess打开记事本

	hookapi();
	hprocess2=hprocess;		//保存当前进程句柄
	test();		//hook后用OpenProcess打开记事本

	unhookapi();
	test();		//恢复hook后用OpenProcess打开记事本

	return 0;
}