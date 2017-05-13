class CDiskHiderDlg;

class DiskMgr {
	private:
		CDiskHiderDlg *dlg;
		CString DiskNames[100];
		CString DosPaths[100];
	public:
		DiskMgr(CDiskHiderDlg* dlg);
		void Getinformation();
		void ShowDisks();
		bool HideVolume(WCHAR *Disk);
		void ShowAllVolume();
		bool ShowVolume(LPWSTR lpDriveLetter, LPWSTR lpDevice);
};