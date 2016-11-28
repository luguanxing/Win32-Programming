// 计算器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "计算器.h"
#include "计算器Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// C计算器Dlg 对话框




C计算器Dlg::C计算器Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C计算器Dlg::IDD, pParent)
	, m_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C计算器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_text);
}

BEGIN_MESSAGE_MAP(C计算器Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &C计算器Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &C计算器Dlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL, &C计算器Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &C计算器Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C计算器Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C计算器Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C计算器Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C计算器Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C计算器Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &C计算器Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &C计算器Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &C计算器Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON13, &C计算器Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON11, &C计算器Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &C计算器Dlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON10, &C计算器Dlg::OnBnClickedButton10)
	ON_EN_CHANGE(IDC_EDIT1, &C计算器Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON14, &C计算器Dlg::OnBnClickedButton14)
END_MESSAGE_MAP()


// C计算器Dlg 消息处理程序

BOOL C计算器Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
		CDialog::OnSysCommand(nID, lParam);
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

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR C计算器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}










///////////////////计算功能

double expr(char* str);
const int MAX=80;              //待处理的最大字符串长度
void eatspace(char* str){       //去掉空格 
    int i=0;
    int j=0;
    while(str[i]!='\0')
        if(str[i]==' '){                
            i++;
        }
        else{
            str[j]=str[i];
            i++; 
            j++;
        }
    str[j]='\0';

}
char* extract(char* str,int& index){        //返回括号之间的expr
    int count=1;
    char* substr=NULL;
    int substr_begin=index;
    int substr_end=index;
    char buffer[MAX];

    while(str[index]!='\0'){
        buffer[index-substr_begin]=str[index];

        switch(str[index++]){
        case '(': count++; break;
        case ')': 
            count--; 
            substr_end=index-1;
            int length=substr_end-substr_begin;
            if(0==count){
                 buffer[length]='\0';
                 substr=new char[length+1];
                 if(!substr){
					 ::MessageBox(NULL,"内存分配错误", "错误", MB_ICONERROR);
					exit(0);
                 }
                 else{
                     strcpy(substr,buffer);
                     return substr;
                 }
            }
           
            break;
        }
    }
    if(count>0){
		 ::MessageBox(NULL,"括号不匹配", "错误", MB_ICONERROR);
		exit(0);
    }

    
            
}
double number(char* str,int& index){       //返回number
    double value=0.0;
    double factor=1.0;
    if(str[index]=='('){
        char* psubstr=NULL;
        psubstr=extract(str,++index);
        value=expr(psubstr);
        delete[] psubstr;
        psubstr=NULL;
        return value;
    }

    if(!isdigit(str[index])){
		 ::MessageBox(NULL,"输入不合法", "错误", MB_ICONERROR);
		exit(0);
    }
    while(isdigit(str[index])){
        value=10*value+(str[index++]-'0');
    }
    if(str[index]!='.'){
        return value;
    }
    else{
        while(isdigit(str[++index])){
            factor*=0.1;
            value+=(str[index]-'0')*factor;
        }
    }

    return value;

}
double term(char* str,int& index){        //返回term
    double value=0.0;
    value=number(str,index);

    while(true){
        switch(str[index++]){
        case '*': value*=number(str,index);  break;
        case '/': value-=number(str,index);   break;
        default: index--; return value;
        }
    }

}
double expr(char* str){          //返回expr
    double value=0.0;    
    int index=0;

    value=term(str,index);
    while(true){
        switch(str[index++]){
        case '+': value+=term(str,index); break;
        case '-': value-=term(str,index); break;
        case '\0': return value;
		 ::MessageBox(NULL,"表达式错误", "错误", MB_OK);
        }
    }
    return value;

}

//////////////////////////////
#include <stdio.h>
void C计算器Dlg::OnBnClickedOk()
{
    char *buffer = m_text.GetBuffer();
    eatspace(buffer);
	int result = expr(buffer);
	char buff[250];
	sprintf(buff, "%d",  result);
	m_text = buff;
	UpdateData(false);
    //cout<<expr(buffer)<<endl;

	//char *exp = 
	//char postexp[MaxSize];
	//trans(exp, postexp);
	//int rtn = computevalue(postexp);
	//char buff[2500];
	//sprintf(buff, "%d",  rtn);
	//m_text = buff;
	//UpdateData(false);
}


void C计算器Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

void C计算器Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_text += L"1";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton2()
{
	m_text += L"2";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton3()
{
	m_text += L"3";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton4()
{
	m_text += L"4";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton5()
{
	m_text += L"5";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton6()
{
	m_text += L"6";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton7()
{
	m_text += L"7";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton8()
{
	m_text += L"8";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton9()
{
	m_text += L"9";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton13()
{
	m_text += L"+";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton11()
{
	m_text += L"-";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton12()
{
	m_text += L"*";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButton10()
{
	m_text += L"/";
	UpdateData(false);
}

void C计算器Dlg::OnBnClickedOk2()
{
	m_text = L"";
	UpdateData(false);
}



void C计算器Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void C计算器Dlg::OnBnClickedButton14()
{
	m_text += L"0";
	UpdateData(false);
}
