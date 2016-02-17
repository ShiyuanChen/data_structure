// DialogEntry.cpp : 实现文件
//

#include "stdafx.h"
#include "Labyrinth.h"
#include "DialogEntry.h"
#include "afxdialogex.h"


// CDialogEntry 对话框

IMPLEMENT_DYNAMIC(CDialogEntry, CDialogEx)

CDialogEntry::CDialogEntry(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogEntry::IDD, pParent)
	,m_Row(0)
	,m_Col(0)
{
	m_Sx = _T("");
	m_Ey = _T("");
	m_Sy = _T("");
	m_Ex = _T("");
}

CDialogEntry::~CDialogEntry()
{
}

void CDialogEntry::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, m_EditSx);
	DDX_Control(pDX, IDC_EDIT4, m_EditSy);
	DDX_Control(pDX, IDC_EDIT5, m_EditEx);
	DDX_Control(pDX, IDC_EDIT6, m_EditEy);
}


BEGIN_MESSAGE_MAP(CDialogEntry, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogEntry::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogEntry 消息处理程序

void CDialogEntry::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditSx.GetWindowTextW(m_Sx);
	m_EditSy.GetWindowTextW(m_Sy);
	m_EditEx.GetWindowTextW(m_Ex);
	m_EditEy.GetWindowTextW(m_Ey);
	if(m_Sx == "0" || m_Sy == "0" ||m_Ex == "0" || m_Ey == "0"|| m_Sx == "" || m_Sy == "" ||m_Ex == "" || m_Ey == ""||
		m_Sx.SpanIncluding( _T("0123456789"))!= m_Sx || m_Sy.SpanIncluding( _T("0123456789"))!= m_Sy||
		m_Ex.SpanIncluding( _T("0123456789"))!= m_Ex || m_Ey.SpanIncluding( _T("0123456789"))!= m_Ey)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_Sx = "";
		m_Sy = "";
		m_Ex = "";
		m_Ey = "";
	}
	else
	{
		int sx = _ttoi(m_Sx);
		int sy = _ttoi(m_Sy);
		int ex = _ttoi(m_Ex);
		int ey = _ttoi(m_Ey);
		if(sx > m_Col || sy > m_Row || ex > m_Col || ey > m_Row ||
			sx < 1 || sy < 1 || ex < 1 || ey < 1)
		{
			CString str1("超过界限，请重新输入！");
			CString str2("提示");
			MessageBox(str1,str2);
			m_Sx = "";
			m_Sy = "";
			m_Ex = "";
			m_Ey = "";
		}
		else if(sx == ex && sy == ey)
		{
			CString str1("起点与终点从重合，请重新输入！");
			CString str2("提示");
			MessageBox(str1,str2);
			m_Sx = "";
			m_Sy = "";
			m_Ex = "";
			m_Ey = "";
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
}
