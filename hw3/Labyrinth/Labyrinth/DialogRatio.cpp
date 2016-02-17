// DialogRatio.cpp : 实现文件
//

#include "stdafx.h"
#include "Labyrinth.h"
#include "DialogRatio.h"
#include "afxdialogex.h"


// CDialogRatio 对话框

IMPLEMENT_DYNAMIC(CDialogRatio, CDialogEx)

CDialogRatio::CDialogRatio(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogRatio::IDD, pParent)
{
	m_Ratio = _T("");
}

CDialogRatio::~CDialogRatio()
{
}

void CDialogRatio::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditRatio);
}


BEGIN_MESSAGE_MAP(CDialogRatio, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogRatio::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogRatio 消息处理程序

void CDialogRatio::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditRatio.GetWindowTextW(m_Ratio);

	if(m_Ratio == "0" || m_Ratio == "" ||
		m_Ratio.SpanIncluding( _T(".0123456789"))!= m_Ratio)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_Ratio = "";
	}
	else
	{
		double ratio = _wtof(m_Ratio);
		if(ratio > 0.8 || ratio < 0)
		{
			CString str1("超过界限，请重新输入！");
			CString str2("提示");
			MessageBox(str1,str2);
			m_Ratio = "";
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
}