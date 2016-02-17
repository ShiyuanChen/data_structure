// DialogGrade.cpp : 实现文件
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "DialogGrade.h"
#include "afxdialogex.h"


// CDialogGrade 对话框

IMPLEMENT_DYNAMIC(CDialogGrade, CDialogEx)

	CDialogGrade::CDialogGrade(bool ISID,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogGrade::IDD, pParent)
	, m_Text(_T(""))
	, isID(ISID)
	, m_Static(_T(""))
{
	if(isID)
		m_Static = L"请输入学号：";
	else
		m_Static = L"请输入姓名：";
}

CDialogGrade::~CDialogGrade()
{
}

void CDialogGrade::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditText);
	DDX_Text(pDX, IDC_STATIC10, m_Static);
}


BEGIN_MESSAGE_MAP(CDialogGrade, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogGrade::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogGrade 消息处理程序

void CDialogGrade::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditText.GetWindowTextW(m_Text);
	if(m_Text == "0" || m_Text == ""|| (isID && 
		m_Text.SpanIncluding( _T("0123456789"))!= m_Text))
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_Text = "";
	}
	else
	{
		CDialogEx::OnOK();
	}
}