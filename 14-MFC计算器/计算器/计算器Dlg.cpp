
// 计算器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "计算器.h"
#include "计算器Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C计算器Dlg 对话框




C计算器Dlg::C计算器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C计算器Dlg::IDD, pParent)
	, m_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void C计算器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_text);
}

BEGIN_MESSAGE_MAP(C计算器Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON14, &C计算器Dlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON13, &C计算器Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON5, &C计算器Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON15, &C计算器Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON1, &C计算器Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &C计算器Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &C计算器Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON16, &C计算器Dlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON3, &C计算器Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &C计算器Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &C计算器Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &C计算器Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON11, &C计算器Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON10, &C计算器Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON9, &C计算器Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON17, &C计算器Dlg::OnBnClickedButton17)
END_MESSAGE_MAP()


// C计算器Dlg 消息处理程序

BOOL C计算器Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C计算器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C计算器Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C计算器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C计算器Dlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("1");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("2");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("3");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("4");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("5");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("6");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("+");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton16()
{
	m_text += _T("7");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("8");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("9");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("-");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("*");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("/");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += _T("0");
	UpdateData(false);
}


void C计算器Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text = _T("0");
	UpdateData(false);
}
///////////////////////////////////////////////////////////////////////////

class Calculator
{
public:
	Calculator(){};
	int getResult(std::string);
private:
	bool can_do(char c);
	void exe_cacu();
	void set(std::string);
	std::string exp;
	std::stack<int> number;
	std::stack<char> op;
};
void Calculator::set(std::string s)
{
	exp = s;
	while(!number.empty())	number.pop();
	while(!op.empty()) op.pop();
}
bool Calculator::can_do(char c)
{
	if(op.empty()) return false;
	if(op.top() == '(')	return false;
	if(c == '+' || c == '-')	return true;
	if(c == '*' && (op.top() == '*' || op.top() == '/'))	return true;
	if(c == '/' && (op.top() == '*' || op.top() == '/'))	return true;
	return false;
}

void Calculator::exe_cacu()
{
	int b = number.top();
	number.pop();
	int a = number.top();number.pop();
	int result;
	switch(op.top())
	{
	case '+':
		result = a+b;
		break;
	case '-':
		result = a-b;
		break;
	case '*':
		result = a*b;
		break;
	case '/': {
		if (b == 0) {
			::MessageBoxA(NULL, "数字错误", "错误", MB_ICONERROR);
			exit(0);
		}
		result = a/b;
		}
		break;
	}
	number.push(result);
	op.pop();
}


int Calculator::getResult(std::string s)
{
	set(s);
	int temp = 0;
	for(unsigned int i=0; i<exp.length(); i++)
	{
		if(isdigit(exp[i]))
		{
			temp = temp*10 + exp[i]-'0';
			if(i+1 == exp.length() || !isdigit(exp[i+1]))
			{
				number.push(temp);
				temp = 0;
			}
		}
		else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
		{
			if(can_do(exp[i]))
				exe_cacu();
			op.push(exp[i]);
		}
		else if(exp[i] == '(')
			op.push(exp[i]);
		else
		{
			while(op.top() != '(')
				exe_cacu();
			op.pop();
		}
	}
	while(!op.empty())
		exe_cacu();

	return number.top();
}
 std::string WStringToString(const std::wstring &wstr)
 {
     std::string str(wstr.length(), ' ');
     std::copy(wstr.begin(), wstr.end(), str.begin());
     return str; 
 }

 std::wstring StringToWString(const std::string &str)
 {
     std::wstring wstr(str.length(),L' ');
     std::copy(str.begin(), str.end(), wstr.begin());
     return wstr; 
 }

void C计算器Dlg::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	std::wstring ws = m_text;
	m_text.ReleaseBuffer();
	std::string s;
	s = WStringToString(ws);
	char buff[100];
	Calculator calc;
	std::sprintf(buff, "%d", calc.getResult(s));
	m_text = buff;
	UpdateData(false);
}
