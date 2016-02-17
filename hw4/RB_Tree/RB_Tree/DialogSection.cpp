// DialogSection.cpp : 实现文件
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "DialogSection.h"
#include "afxdialogex.h"


// CDialogSection 对话框

IMPLEMENT_DYNAMIC(CDialogSection, CDialogEx)

CDialogSection::CDialogSection(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogSection::IDD, pParent)
	, m_Sec(_T(""))
{

}

CDialogSection::~CDialogSection()
{
}

void CDialogSection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditText);
}


BEGIN_MESSAGE_MAP(CDialogSection, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogSection::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogSection 消息处理程序

void CDialogSection::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditText.GetWindowTextW(m_Sec);
	if( m_Sec != L"E" && 
		m_Sec != L"D" &&
		m_Sec != L"C" &&
		m_Sec != L"C+" &&
		m_Sec != L"B-" &&
		m_Sec != L"B" &&
		m_Sec != L"B+" &&
		m_Sec != L"A" &&
		m_Sec != L"AA" &&
		m_Sec != L"AA+")
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_Sec = "";
	}
	else
	{
		CDialogEx::OnOK();
	}
}