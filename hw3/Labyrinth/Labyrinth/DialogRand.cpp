// DialogRand.cpp : 实现文件
//

#include "stdafx.h"
#include "Labyrinth.h"
#include "DialogRand.h"
#include "afxdialogex.h"


// CDialogRand 对话框

IMPLEMENT_DYNAMIC(CDialogRand, CDialogEx)

CDialogRand::CDialogRand(CWnd* pParent /*=NULL*/)
: CDialogEx(CDialogRand::IDD, pParent)
, m_Row(_T(""))
, m_Col(_T(""))
{

}

CDialogRand::~CDialogRand()
{
}

void CDialogRand::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditRow);
	DDX_Control(pDX, IDC_EDIT2, m_EditCol);
}


BEGIN_MESSAGE_MAP(CDialogRand, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogRand::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogRand 消息处理程序


void CDialogRand::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditRow.GetWindowTextW(m_Row);
	m_EditCol.GetWindowTextW(m_Col);
	if (m_Row == "" || m_Col == "" || m_Row.SpanIncluding(_T("0123456789")) != m_Row || m_Col.SpanIncluding(_T("0123456789")) != m_Col)
	{
		CString str1("输入格式不正确，请重新输入！");
		CString str2("提示");
		MessageBox(str1, str2);
		m_Row = "";
		m_Col = "";
	}
	else
	{
		int row = _ttoi(m_Row);
		int col = _ttoi(m_Col);
		if (row > 100 || col > 100 || row < 2 || col < 2)
		{
			CString str1("超过界限，请重新输入！");
			CString str2("提示");
			MessageBox(str1, str2);
			m_Row = "";
			m_Col = "";
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
	MSG msg;
	while (true)
	{
		while (PeekMessage(&msg, -1, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		int iii = 3 * 5;
	}
}
