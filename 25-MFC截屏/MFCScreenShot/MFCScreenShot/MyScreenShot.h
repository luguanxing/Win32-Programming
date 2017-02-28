
class ScreenDlg;

class MyScreenShot {
	private:
		POINT pfirst, pnext;		//记录拖动的两个点
		POINT pstart;		//计算得到的左上角的顶点
		ScreenDlg *dlg;	//主窗口指针
	public:
		bool ispress;				//记录是否按下左键
		WCHAR path[255];		//保存路径
		MyScreenShot();			//初始化
		void SetDlg(ScreenDlg *wnddlg);		//设置主窗口指针
		void HideSelf();			//隐藏窗口
		void ShowSelf();			//显示窗口
		void SetWindowShape();			//设置窗口中间透明
		void DrawFrame();		//绘制框架
		void EraseFrame();		//擦去框架
		bool IsSamePoint(POINT pcheck);		//判断鼠标位置是否静止
		void UpdatePoint();		//更新鼠标位置
		void CheckPoint();		//计算鼠标位置
		void TakePic(char filename[]);	//截图
		void SavePic();				//保存图片
};
