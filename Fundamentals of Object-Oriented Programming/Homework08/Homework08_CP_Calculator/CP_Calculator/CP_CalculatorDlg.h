
// CP_CalculatorDlg.h: 头文件
//

#pragma once


// CCPCalculatorDlg 对话框
class CCPCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCPCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CP_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnCbnSelchangeComboOperator();
//	CComboBox m_operator;
	// 进行运算的第1个数
//	int m_number1;
	// 进行运算的第2个数
//	int m_number2;
	// 运算结果
//	int m_result;
	afx_msg void OnBnClickedResult();
	afx_msg void OnEnChangeEditNum1();
	afx_msg void OnEnUpdateEditNum1();
	afx_msg void OnEnChangeEditNum2();
	afx_msg void OnEnUpdateEditNum2();
	// 运算符
	CString m_operator;
	// 运算结果
	double m_result;
	// 参与运算的第1个数
	double m_number1;
	// 参与运算的第2个数
	double m_number2;
	// 运算结果2
	double m_result2;
	// 运算公式
	CString m_formula;
	afx_msg void OnBnClickedResult2();
};
