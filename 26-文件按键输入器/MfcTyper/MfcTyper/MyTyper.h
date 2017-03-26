
class CMfcTyperDlg;

class MyTyper {
	private:
		CMfcTyperDlg *pdlg;
	public:
		MyTyper();												//初始化
		void SetDlg(CMfcTyperDlg *wnddlg);	//设置对话框
		void Init();												//准备开始模拟按键
		void StartPrint();										//模拟按键
};
