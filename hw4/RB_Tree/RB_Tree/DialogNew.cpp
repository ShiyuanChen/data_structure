// DialogNew.cpp : 实现文件
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "DialogNew.h"
#include "afxdialogex.h"


// CDialogNew 对话框

IMPLEMENT_DYNAMIC(CDialogNew, CDialogEx)

CDialogNew::CDialogNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogNew::IDD, pParent)
{

	m_ID = _T("");
	m_Name = _T("");
	m_Grade = _T("");
}

CDialogNew::~CDialogNew()
{
}

void CDialogNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditID);
	DDX_Control(pDX, IDC_EDIT2, m_EditName);
	DDX_Control(pDX, IDC_EDIT3, m_EditGrade);
}


BEGIN_MESSAGE_MAP(CDialogNew, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogNew::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogNew 消息处理程序

void CDialogNew::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditID.GetWindowTextW(m_ID);
	m_EditName.GetWindowTextW(m_Name);
	m_EditGrade.GetWindowTextW(m_Grade);
	if(m_ID == "0" || m_ID == "" || m_Name == "" || m_Grade == "" ||
		m_ID.SpanIncluding( _T("0123456789"))!= m_ID || m_Grade.SpanIncluding( _T("0123456789"))!= m_Grade)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_ID = "";
		m_Name = "";
		m_Grade = "";
	}
	else
	{
		int grade = _ttoi(m_Grade);
		if(grade > 100)
		{
			CString str1("分数超过界限，请重新输入！");
			CString str2("提示");
			MessageBox(str1,str2);
			m_ID = "";
			m_Name = "";
			m_Grade = "";
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
}