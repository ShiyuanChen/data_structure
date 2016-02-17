// DialogNew.cpp : 实现文件
//

#include "stdafx.h"
#include "Labyrinth.h"
#include "DialogNew.h"
#include "afxdialogex.h"


// CDialogNew 对话框

IMPLEMENT_DYNAMIC(CDialogNew, CDialogEx)

	CDialogNew::CDialogNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogNew::IDD, pParent)
{

	m_Row = _T("");
	m_Col = _T("");
	m_Sx = _T("");
	m_Ey = _T("");
	m_Sy = _T("");
	m_Ex = _T("");
	m_Ratio = _T("");
}

CDialogNew::~CDialogNew()
{
}

void CDialogNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditRow);
	DDX_Control(pDX, IDC_EDIT2, m_EditCol);
	DDX_Control(pDX, IDC_EDIT3, m_EditSx);
	DDX_Control(pDX, IDC_EDIT4, m_EditSy);
	DDX_Control(pDX, IDC_EDIT5, m_EditEx);
	DDX_Control(pDX, IDC_EDIT6, m_EditEy);
	DDX_Control(pDX, IDC_EDIT7, m_EditRatio);
}


BEGIN_MESSAGE_MAP(CDialogNew, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogNew::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogNew 消息处理程序


void CDialogNew::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditRow.GetWindowTextW(m_Row);
	m_EditCol.GetWindowTextW(m_Col);
	m_EditSx.GetWindowTextW(m_Sx);
	m_EditSy.GetWindowTextW(m_Sy);
	m_EditEx.GetWindowTextW(m_Ex);
	m_EditEy.GetWindowTextW(m_Ey);
	m_EditRatio.GetWindowTextW(m_Ratio);
	if(m_Row == "0" || m_Col == "0" || m_Sx == "0" || m_Sy == "0" ||m_Ex == "0" || m_Ey == "0" ||m_Ratio == "0" ||
		m_Row == "" || m_Col == "" || m_Sx == "" || m_Sy == "" ||m_Ex == "" || m_Ey == "" ||m_Ratio == "" ||
		m_Row.SpanIncluding( _T("0123456789"))!= m_Row || m_Col.SpanIncluding( _T("0123456789"))!= m_Col||
		m_Sx.SpanIncluding( _T("0123456789"))!= m_Sx || m_Sy.SpanIncluding( _T("0123456789"))!= m_Sy||
		m_Ex.SpanIncluding( _T("0123456789"))!= m_Ex || m_Ey.SpanIncluding( _T("0123456789"))!= m_Ey|| m_Ratio.SpanIncluding( _T(".0123456789"))!= m_Ratio)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1,str2);
		m_Row = "";
		m_Col = "";
		m_Sx = "";
		m_Sy = "";
		m_Ex = "";
		m_Ey = "";
		m_Ratio = "";
	}
	else
	{
		int row = _ttoi(m_Row);
		int col = _ttoi(m_Col);
		int sx = _ttoi(m_Sx);
		int sy = _ttoi(m_Sy);
		int ex = _ttoi(m_Ex);
		int ey = _ttoi(m_Ey);
		double ratio = _wtof(m_Ratio);
		if(row > 100 || col > 100 || row < 2 || col < 2 || sx > col || sy > row || ex > col || ey > row ||ratio > 0.8 ||
			sx < 1 || sy < 1 || ex < 1 || ey < 1 || ratio < 0)
		{
			CString str1("超过界限，请重新输入！");
			CString str2("提示");
			MessageBox(str1,str2);
			m_Row = "";
			m_Col = "";
			m_Sx = "";
			m_Sy = "";
			m_Ex = "";
			m_Ey = "";
			m_Ratio = "";
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
