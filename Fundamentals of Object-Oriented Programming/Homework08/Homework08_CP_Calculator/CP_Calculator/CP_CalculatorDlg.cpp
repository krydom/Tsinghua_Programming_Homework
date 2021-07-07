
// CP_CalculatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CP_Calculator.h"
#include "CP_CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCPCalculatorDlg 对话框



CCPCalculatorDlg::CCPCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CP_CALCULATOR_DIALOG, pParent)
	, m_operator(_T(""))
	, m_result(0)
	, m_number1(0)
	, m_number2(0)
	, m_result2(0)
	, m_formula(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCPCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_COMBO_Operator, m_operator);
	//  DDX_Text(pDX, IDC_EDIT_Num1, m_number1);
	//  DDX_Text(pDX, IDC_EDIT_Num2, m_number2);
	//  DDX_Text(pDX, IDC_EDIT_Result, m_result);
	DDX_CBString(pDX, IDC_COMBO_Operator, m_operator);
	DDX_Text(pDX, IDC_EDIT_Result, m_result);
	DDX_Text(pDX, IDC_EDIT_Num1, m_number1);
	DDX_Text(pDX, IDC_EDIT_Num2, m_number2);
	DDX_Text(pDX, IDC_EDIT_Result2, m_result2);
	DDX_Text(pDX, IDC_EDIT1, m_formula);
}

BEGIN_MESSAGE_MAP(CCPCalculatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_Operator, &CCPCalculatorDlg::OnCbnSelchangeComboOperator)
	ON_BN_CLICKED(IDC_Result, &CCPCalculatorDlg::OnBnClickedResult)
	ON_EN_CHANGE(IDC_EDIT_Num1, &CCPCalculatorDlg::OnEnChangeEditNum1)
	ON_EN_UPDATE(IDC_EDIT_Num1, &CCPCalculatorDlg::OnEnUpdateEditNum1)
	ON_EN_CHANGE(IDC_EDIT_Num2, &CCPCalculatorDlg::OnEnChangeEditNum2)
	ON_EN_UPDATE(IDC_EDIT_Num2, &CCPCalculatorDlg::OnEnUpdateEditNum2)
	ON_BN_CLICKED(IDC_Result2, &CCPCalculatorDlg::OnBnClickedResult2)
END_MESSAGE_MAP()


// CCPCalculatorDlg 消息处理程序

BOOL CCPCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCPCalculatorDlg::OnPaint()
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
HCURSOR CCPCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCPCalculatorDlg::OnCbnSelchangeComboOperator()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCPCalculatorDlg::OnBnClickedResult()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_operator == "") return; // 还没有进行选择
	if (m_number1 != (int)m_number1 && m_number1 != (int)m_number1 + 1) // 输入的数溢出int
	{
		MessageBox(_T("请输入一个属于[-2147483648,2147483647]的整数"), _T("错误"), MB_OK | MB_ICONWARNING);
		return;
	}
	if (m_number2 != (int)m_number2 && m_number2 != (int)m_number2 + 1)
	{
		MessageBox(_T("请输入一个属于[-2147483648,2147483647]的整数"), _T("错误"), MB_OK | MB_ICONWARNING);
		return;
	}
	int m1 = (int)m_number1, m2 = (int)m_number2, ms = 0;
	if (m1 != m_number1) ++m1;
	if (m2 != m_number2) ++m2;
	if (m_operator == "+") m_result = m_number1 + m_number2, ms = m1 + m2;
	if (m_operator == "-") m_result = m_number1 - m_number2, ms = m1 - m2;
	if (m_operator == "*") m_result = m_number1 * m_number2, ms = m1 * m2;
	if (m_operator == "/")
	{
		if (m2 == 0)
		{
			MessageBox(_T("除数不能为0"), _T("错误"), MB_OK | MB_ICONWARNING);
			return;
		}
		m_result = m1 / m2;
		UpdateData(FALSE);
		return;
	}
	else if (m_result != ms) MessageBox(_T("运算结果溢出"), _T("错误"), MB_OK | MB_ICONWARNING); // 运算结果溢出int
	m_result = ms;
	UpdateData(FALSE);
}


void CCPCalculatorDlg::OnEnChangeEditNum1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//OnBnClickedResult();
}


void CCPCalculatorDlg::OnEnUpdateEditNum1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//OnBnClickedResult();
}


void CCPCalculatorDlg::OnEnChangeEditNum2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//OnBnClickedResult();
}


void CCPCalculatorDlg::OnEnUpdateEditNum2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//OnBnClickedResult();
}

class resultPair
{
public:
	double result;
	bool fl;
	resultPair() : result(0), fl(0) {}
	resultPair(double x, bool y) : result(x), fl(y) {}
};

bool isNum(CString s) // 判断字符串是否是数字
{
	int len = s.GetLength();
	bool Point = 0;
	for (int i = 0; i < len; ++i)
	{
		char c = s.GetAt(i);
		if (c >= '0' && c <= '9') continue;
		if (c == '.')
		{
			if (!Point) Point = 1; else return 0;
		}
		else return 0;
	}
	return 1;
}

resultPair getNum(CString s) // 将字符串转化为数字
{
	int len = s.GetLength();
	bool Point = 0;
	double ans = 0, now = 1;
	for (int i = 0; i < len; ++i)
	{
		char c = s.GetAt(i);
		if (c >= '0' && c <= '9')
		{
			if (!Point) ans = ans * 10 + c - '0';
			else
			{
				now /= 10.0;
				ans += (c - '0') * now;
			}
		}
		else Point = 1;
	}
	resultPair Ans(ans, 0);
	return Ans;
}

bool checkFail(CString s)
{
	int len = s.GetLength();
	if (len == 0) return 1; // 空字符串不合法，处理某个运算符没有左右运算的情况
	bool number = 1; // 判断是否只有数字和小数点
	for (int i = 0; i < len; ++i)
	{
		char c = s.GetAt(i);
		if (c != '.' && c != '(' && c != ')' && c != '+' && c != '-' && c != '*' && c != '/' && (c < '0' || c > '9')) return 1; // 不是数字、运算符、小数点、括号，不合法
		if (c != '.' && (c < '0' || c > '9')) number = 0;
	}
	if (number)
	{
		int tot = 0; // 小数点的个数
		for (int i = 0; i < len; ++i)
			if (s.GetAt(i) == '.') ++tot;
		if (tot > 1) return 1; // 数字最多只有1个小数点
	}
	return 0;
}

resultPair cal(CString s)
{
	int len = s.GetLength();   // 删除最外层的括号
	while (len >= 2 && s.GetAt(0) == '(' && s.GetAt(len - 1) == ')')
	{
		int tmp = 0;
		for (int i = 1; i < len - 1; ++i)
		{
			if (s.GetAt(i) == '(') ++tmp;
			if (s.GetAt(i) == ')') --tmp;
			if (tmp < 0) break;
		}
		if (tmp < 0) break;
		else
		{
			s.Delete(len - 1, 1);
			s.Delete(0, 1);
			len -= 2;
		}
	}

	resultPair Ans(0, 1); // 初始化为不合法
	if (checkFail(s)) return Ans;

	if (isNum(s)) return getNum(s); // 如果表达式是数字返回数字

	int leftNumber = 0; //当前所在的括号数
	int minOperator = -1;  // 优先级最小的运算符的位置
	for (int i = 0; i < len; ++i)   // 找到优先级最小的运算符
	{
		char c = s.GetAt(i);
		if (c == '(') leftNumber++;
		if (c == ')') leftNumber--;
		if (leftNumber < 0) return Ans; // 括号不匹配1
		if (leftNumber == 0)
		{
			if (c != '+' && c != '-' && c != '*' && c != '/') continue;
			if (c == '+' || c == '-') minOperator = i;
			else if (minOperator == -1) minOperator = i;
		}
	}
	if (leftNumber > 0) return Ans; // 括号不匹配2

	if (minOperator == 0 && (s.GetAt(0) == '+' || s.GetAt(0) == '-')) // 正号和负号的特判
	{
		resultPair n = cal(s.Right(len - 1));
		if (s.GetAt(0) == '-') n.result = -n.result;
		return n;
	}

	resultPair n1 = cal(s.Left(minOperator));            // 获取左值
	resultPair n2 = cal(s.Right(len - minOperator - 1)); // 获取右值
	if (n1.fl == 1 || n2.fl == 1) return Ans;
	Ans.fl = 0;
	if (s.GetAt(minOperator) == '+') Ans.result = n1.result + n2.result;
	if (s.GetAt(minOperator) == '-') Ans.result = n1.result - n2.result;
	if (s.GetAt(minOperator) == '*') Ans.result = n1.result * n2.result;
	if (s.GetAt(minOperator) == '/') Ans.result = n1.result / n2.result;
	return Ans;

}


void CCPCalculatorDlg::OnBnClickedResult2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	resultPair Ans = cal(m_formula);
	if (Ans.fl)
	{
		MessageBox(_T("请输入一个合法的算式"), _T("错误"), MB_OK | MB_ICONWARNING);
	}
	else
	{
		m_result2 = Ans.result;
	}
	UpdateData(FALSE);
}
