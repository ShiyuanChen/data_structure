// DialogDelete.cpp : 实现文件
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "DialogDelete.h"
#include "afxdialogex.h"


// CDialogDelete 对话框

IMPLEMENT_DYNAMIC(CDialogDelete, CDialogEx)

CDialogDelete::CDialogDelete(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogDelete::IDD, pParent)
{

	m_ID = _T("");
}

CDialogDelete::~CDialogDelete()
{
}

void CDialogDelete::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditID);
}


BEGIN_MESSAGE_MAP(CDialogDelete, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogDelete::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogDelete 消息处理程序


void CDialogDelete::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditID.GetWindowTextW(m_ID);
	if(m_ID == "0" || m_ID == "" ||	m_ID.SpanIncluding( _T("0123456789"))!= m_ID)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_ID = "";
	}
	else
	{
		CDialogEx::OnOK();
	}
}