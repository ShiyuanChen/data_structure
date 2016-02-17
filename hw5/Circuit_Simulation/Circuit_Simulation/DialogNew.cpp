// DialogNew.cpp : 实现文件
//

#include "stdafx.h"
#include "Circuit_Simulation.h"
#include "DialogNew.h"
#include "afxdialogex.h"
#include "Node.h"


// CDialogNew 对话框

IMPLEMENT_DYNAMIC(CDialogNew, CDialogEx)

CDialogNew::CDialogNew(int TYPE,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogNew::IDD, pParent)
	, m_Text(_T(""))
	, m_Unit(_T(""))
	, type(TYPE)
{
}

CDialogNew::~CDialogNew()
{
}

void CDialogNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Combobox);
	DDX_Control(pDX, IDC_EDIT1, m_EditText);
}


BEGIN_MESSAGE_MAP(CDialogNew, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogNew::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogNew 消息处理程序
void CDialogNew::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditText.GetWindowTextW(m_Text);
	if(m_Text == "0" || m_Text == ""|| m_Text.SpanIncluding( _T(".0123456789"))!= m_Text)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_Text = "";
	}
	else
	{
		int nIndex = m_Combobox.GetCurSel();
		m_Combobox.GetLBText(nIndex,m_Unit);
		CDialogEx::OnOK();
	}
}

BOOL CDialogNew::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	switch (type)
	{
	case RE:
		m_Combobox.InsertString(0,L"GΩ");
		m_Combobox.InsertString(1,L"MΩ");
		m_Combobox.InsertString(2,L"kΩ");
		m_Combobox.InsertString(3,L"Ω");
		m_Combobox.InsertString(4,L"mΩ");
		m_Combobox.SetCurSel(3);
		break;
	case CA:
		m_Combobox.InsertString(0,L"F");
		m_Combobox.InsertString(1,L"mF");
		m_Combobox.InsertString(2,L"μF");
		m_Combobox.InsertString(3,L"nF");
		m_Combobox.InsertString(4,L"pF");
		m_Combobox.InsertString(5,L"fF");
		m_Combobox.SetCurSel(0);
		break;
	case LI:
		m_Combobox.InsertString(0,L"MH");
		m_Combobox.InsertString(1,L"kH");
		m_Combobox.InsertString(2,L"H");
		m_Combobox.InsertString(3,L"mH");
		m_Combobox.InsertString(4,L"μH");
		m_Combobox.InsertString(5,L"nH");
		m_Combobox.SetCurSel(2);
		break;
	case ES:
		m_Combobox.InsertString(0,L"GV");
		m_Combobox.InsertString(1,L"MV");
		m_Combobox.InsertString(2,L"kV");
		m_Combobox.InsertString(3,L"V");
		m_Combobox.InsertString(4,L"mV");
		m_Combobox.InsertString(5,L"μV");
		m_Combobox.InsertString(6,L"nV");
		m_Combobox.InsertString(7,L"pV");
		m_Combobox.SetCurSel(3);
		break;
	case IS:
		m_Combobox.InsertString(0,L"GA");
		m_Combobox.InsertString(1,L"MA");
		m_Combobox.InsertString(2,L"kA");
		m_Combobox.InsertString(3,L"A");
		m_Combobox.InsertString(4,L"mA");
		m_Combobox.InsertString(5,L"μA");
		m_Combobox.InsertString(6,L"nA");
		m_Combobox.InsertString(7,L"pA");
		m_Combobox.SetCurSel(3);
		break;
	default:
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
