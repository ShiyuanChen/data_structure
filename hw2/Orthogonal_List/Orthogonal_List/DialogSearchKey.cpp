// DialogSearchKey.cpp : 实现文件
//

#include "stdafx.h"
#include "Orthogonal_List.h"
#include "DialogSearchKey.h"
#include "afxdialogex.h"


// CDialogSearchKey 对话框

IMPLEMENT_DYNAMIC(CDialogSearchKey, CDialogEx)

CDialogSearchKey::CDialogSearchKey(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogSearchKey::IDD, pParent)
	, m_Data(_T(""))
{

}

CDialogSearchKey::~CDialogSearchKey()
{
}

void CDialogSearchKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditData);
}


BEGIN_MESSAGE_MAP(CDialogSearchKey, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogSearchKey::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogSearchKey 消息处理程序


void CDialogSearchKey::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditData.GetWindowTextW(m_Data);
	if(m_Data == "" || m_Data.SpanIncluding( _T("0123456789"))!= m_Data)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_Data = "";
	}
	else
	{
		CDialogEx::OnOK();
	}
}
