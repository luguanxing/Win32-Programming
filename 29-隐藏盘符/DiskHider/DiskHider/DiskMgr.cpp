#include "StdAfx.h"
#include "DiskHider.h"
#include "DiskMgr.h"
#include "DiskHiderDlg.h"

DiskMgr::DiskMgr(CDiskHiderDlg* dlg) {
	this->dlg = dlg;
	ShowDisks();
	Getinformation();
}

void DiskMgr::Getinformation() {
	int disknum = dlg->m_disks.GetCount();
	for (int i = 0; i < disknum; i++) {
		CString DiskName;
		WCHAR DosPath[MAX_PATH];  
		dlg->m_disks.GetLBText(i, DiskName);
		QueryDosDevice(DiskName.Left(DiskName.GetLength()-1), DosPath, MAX_PATH);
		DiskNames[i] = DiskName.Left(DiskName.GetAllocLength()-1);
		DosPaths[i] = DosPath;
	}
}

void DiskMgr::ShowDisks() {
	WCHAR buff[MAX_PATH];
	CString cs_disks;
	DWORD len;
	len = ::GetLogicalDriveStrings(MAX_PATH, buff);
	for (int i = 0; i < len; i++) {
		if (buff[i] == 0 ) {
			if (buff[i+1] == 0 ) {
				break;
			} else {
				dlg->m_disks.AddString(cs_disks);
				cs_disks = "";
			}
		} else {
			cs_disks += buff[i];
		}
	}
	dlg->m_disks.SetCurSel(0);
}

bool DiskMgr::HideVolume(WCHAR *Disk) {
	// 先备份信息
	//SaveInformation(Disk);
	// 将盘符和Dos设备路径移除
	WCHAR szDeviceName[MAX_PATH] = {0};
	::lstrcpy(szDeviceName, Disk);
	szDeviceName[2] = '\0';
	if (!::DefineDosDevice(DDD_REMOVE_DEFINITION, szDeviceName, NULL)) {
		return FALSE;
	}
	// 卸载卷加载点
	if (!::DeleteVolumeMountPoint(Disk)) {
		return FALSE;
	}
	return TRUE;
}

void DiskMgr::ShowAllVolume() {
	int disknum = dlg->m_disks.GetCount();
	for (int i = 0; i < disknum; i++) {
		ShowVolume(DiskNames[i].GetBuffer(), DosPaths[i].GetBuffer());
	}
}

bool DiskMgr::ShowVolume(LPWSTR lpwDeviceName, LPWSTR lpwDosPath) {  
	if(!::DefineDosDevice(DDD_RAW_TARGET_PATH, lpwDeviceName, lpwDosPath)) {
		return FALSE;
	}

	WCHAR szUniqueVolumeName[MAX_PATH] = {0};
	CString DiskName = lpwDeviceName;
	DiskName.Append(L"\\");
	// 获取装载点名
	if (!GetVolumeNameForVolumeMountPoint(DiskName, szUniqueVolumeName, MAX_PATH))
	{
		szUniqueVolumeName[0] = 0;
	}
	
	// 将盘符和Dos设备路径附加
	if (!::DefineDosDevice(DDD_RAW_TARGET_PATH | DDD_REMOVE_DEFINITION |DDD_EXACT_MATCH_ON_REMOVE, lpwDeviceName, lpwDosPath)) {
		return FALSE;
	}

	// 设置卷装载点
	//	::MessageBox(NULL, szUniqueVolumeName, szDriver, MB_OK);
	/* 注意在使用SetVolumeMountPoint的时候，挂载点目录必须存在，而且必须为空目录，否则程序会运行失败 */
	::SetVolumeMountPoint(DiskName, szUniqueVolumeName);
}