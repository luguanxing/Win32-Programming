#include <Windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID lParam) {
	BOOL bRet = FALSE;
	BYTE Buffer[1024] = {0};

	FILE_NOTIFY_INFORMATION *pBuffer = (FILE_NOTIFY_INFORMATION *)Buffer;
	DWORD dwByteReturn = 0;
	HANDLE hFile = ::CreateFile("h:\\", FILE_LIST_DIRECTORY, 
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if(INVALID_HANDLE_VALUE == hFile) {
		printf("CreateFile Error!\n");
		return 1;
	}
	
	printf("monitoring...\r\n");

	while(TRUE) {
		::ZeroMemory(Buffer, sizeof(Buffer));
		bRet = ::ReadDirectoryChangesW(hFile, 
			&Buffer,
			sizeof(Buffer),
			TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME |			// 修改文件名
			FILE_NOTIFY_CHANGE_ATTRIBUTES |			// 修改文件属性
			FILE_NOTIFY_CHANGE_LAST_WRITE,			// 最后一次写入
			&dwByteReturn, NULL, NULL);				
		if(TRUE == bRet) {
			char szFileName[MAX_PATH] = {0};

			// 款字符转换为多字节
			::WideCharToMultiByte(CP_ACP,
				0,
				pBuffer->FileName,
				(pBuffer->FileNameLength / 2),
				szFileName,
				MAX_PATH,
				NULL,
				NULL);
			switch(pBuffer->Action) {
				case FILE_ACTION_ADDED:
					{
						printf("添加: %s\r\n", szFileName);
						break;
					}
				case FILE_ACTION_REMOVED:
					{
						printf("删除:%s\r\n", szFileName);
						break;
					}
				case FILE_ACTION_MODIFIED:
					{
						printf("修改:%s\r\n", szFileName);
						break;
					}
				case FILE_ACTION_RENAMED_OLD_NAME:
					{
						printf("重命名:%s", szFileName);
						if(0 != pBuffer->NextEntryOffset) {
							FILE_NOTIFY_INFORMATION *tmpBuffer = (FILE_NOTIFY_INFORMATION *)
								((DWORD)pBuffer + pBuffer->NextEntryOffset);
							switch(tmpBuffer->Action)
								{
									case FILE_ACTION_RENAMED_NEW_NAME:
										{
												::ZeroMemory(szFileName, MAX_PATH);
												::WideCharToMultiByte(CP_ACP,
													0,
													tmpBuffer->FileName,
													(tmpBuffer->FileNameLength / 2),
													szFileName,
													MAX_PATH,
													NULL,
													NULL);
												printf(" -> %s\r\n", szFileName);
												break;
										}
								}
						}
						break;
					}
				case FILE_ACTION_RENAMED_NEW_NAME:
					{
						printf("重命名(new):%s\r\n", szFileName);
						break;
					}
				}
		}
		::Sleep(5);
	}
	::CloseHandle(hFile);

	return 0;
}


int main() {
	HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	if(NULL == hThread) {
		printf("CreateThread Error!\n");
		return -1;
	}
	::WaitForSingleObject(hThread, INFINITE);
	::CloseHandle(hThread);
	return 0;
}

