// DialogSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "DialogSearch.h"
#include "afxdialogex.h"


// CDialogSearch 对话框

IMPLEMENT_DYNAMIC(CDialogSearch, CDialogEx)

	CDialogSearch::CDialogSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogSearch::IDD, pParent)
	, m_from(_T(""))
	, m_to(_T(""))
{

}

CDialogSearch::~CDialogSearch()
{
}

void CDialogSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
}


BEGIN_MESSAGE_MAP(CDialogSearch, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogSearch::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogSearch 消息处理程序

void CDialogSearch::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Edit1.GetWindowTextW(m_from);
	m_Edit2.GetWindowTextW(m_to);
	if(m_from == "" || m_to == "" ||
		m_from.SpanIncluding( _T("0123456789"))!= m_from || m_to.SpanIncluding( _T("0123456789"))!= m_to)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_from = "";
		m_to = "";
	}
	else
	{
		int from = _ttoi(m_from);
		int to = _ttoi(m_to);
		if(from > 100 || to > 100 || from > to)
		{
			CString str1("分数超过界限，请重新输入！");
			CString str2("提示");
			MessageBox(str1,str2);
			m_from = "";
			m_to = "";
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
}