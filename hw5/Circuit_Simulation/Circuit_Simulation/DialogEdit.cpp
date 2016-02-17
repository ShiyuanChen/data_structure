// DialogEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "Circuit_Simulation.h"
#include "DialogEdit.h"
#include "afxdialogex.h"
#include "Node.h"


// CDialogEdit 对话框

IMPLEMENT_DYNAMIC(CDialogEdit, CDialogEx)

CDialogEdit::CDialogEdit(int ISVS,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogEdit::IDD, pParent)
	, m_Freq(_T(""))
	, m_Max(_T(""))
	, m_Unit1(_T(""))
	, m_Unit2(_T(""))
	, isvs(ISVS)
{

}

CDialogEdit::~CDialogEdit()
{
}

void CDialogEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Combobox1);
	DDX_Control(pDX, IDC_EDIT1, m_EditText1);
	DDX_Control(pDX, IDC_COMBO2, m_Combobox2);
	DDX_Control(pDX, IDC_EDIT2, m_EditText2);
}


BEGIN_MESSAGE_MAP(CDialogEdit, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogEdit::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogEdit 消息处理程序
void CDialogEdit::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditText1.GetWindowTextW(m_Freq);
	m_EditText2.GetWindowTextW(m_Max);
	if(m_Freq == "0" || m_Freq == ""|| m_Freq.SpanIncluding( _T(".0123456789"))!= m_Freq
		|| m_Max == "0" || m_Max == ""|| m_Max.SpanIncluding( _T(".0123456789"))!= m_Max)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_Freq = "";
		m_Max = "";
	}
	else
	{
		int nIndex1 = m_Combobox1.GetCurSel();
		m_Combobox1.GetLBText(nIndex1,m_Unit1);
		int nIndex2 = m_Combobox2.GetCurSel();
		m_Combobox2.GetLBText(nIndex2,m_Unit2);

		CDialogEx::OnOK();
	}
}
BOOL CDialogEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Combobox1.InsertString(0,L"GHz");
	m_Combobox1.InsertString(1,L"MHz");
	m_Combobox1.InsertString(2,L"kHz");
	m_Combobox1.InsertString(3,L"Hz");
	m_Combobox1.InsertString(4,L"mHz");
	m_Combobox1.InsertString(5,L"μHz");
	m_Combobox1.InsertString(6,L"nHz");
	m_Combobox1.InsertString(7,L"pHz");
	m_Combobox1.SetCurSel(3);
	if(isvs <= SAWV)
	{
		m_Combobox2.InsertString(0,L"GV");
		m_Combobox2.InsertString(1,L"MV");
		m_Combobox2.InsertString(2,L"kV");
		m_Combobox2.InsertString(3,L"V");
		m_Combobox2.InsertString(4,L"mV");
		m_Combobox2.InsertString(5,L"μV");
		m_Combobox2.InsertString(6,L"nV");
		m_Combobox2.InsertString(7,L"pV");
		m_Combobox2.SetCurSel(3);
	}
	else if(isvs <= SAWC)
	{
		m_Combobox2.InsertString(0,L"GA");
		m_Combobox2.InsertString(1,L"MA");
		m_Combobox2.InsertString(2,L"kA");
		m_Combobox2.InsertString(3,L"A");
		m_Combobox2.InsertString(4,L"mA");
		m_Combobox2.InsertString(5,L"μA");
		m_Combobox2.InsertString(6,L"nA");
		m_Combobox2.InsertString(7,L"pA");
		m_Combobox2.SetCurSel(3);
	}
	return TRUE; 
}