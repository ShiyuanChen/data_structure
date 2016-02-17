// DialogResize.cpp : 实现文件
//

#include "stdafx.h"
#include "Labyrinth.h"
#include "DialogResize.h"
#include "afxdialogex.h"


// CDialogResize 对话框

IMPLEMENT_DYNAMIC(CDialogResize, CDialogEx)

	CDialogResize::CDialogResize(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogResize::IDD, pParent)
	, m_Row(_T(""))
	, m_Col(_T(""))
{

}

CDialogResize::~CDialogResize()
{
}

void CDialogResize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditRow);
	DDX_Control(pDX, IDC_EDIT2, m_EditCol);
}


BEGIN_MESSAGE_MAP(CDialogResize, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogResize::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogResize 消息处理程序

void CDialogResize::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditRow.GetWindowTextW(m_Row);
	m_EditCol.GetWindowTextW(m_Col);
	if(m_Row == "" || m_Col == "" || m_Row.SpanIncluding( _T("0123456789"))!= m_Row || m_Col.SpanIncluding( _T("0123456789"))!= m_Col)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_Row = "";
		m_Col = "";
	}
	else
	{
		int row = _ttoi(m_Row);
		int col = _ttoi(m_Col);
		if(row > 100 || col > 100 || row < 2 || col < 2)
		{
			CString str1("超过界限，请重新输入！");
			CString str2("提示");
			MessageBox(str1,str2);
			m_Row = "";
			m_Col = "";
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
}