// DialogSearchIn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Orthogonal_List.h"
#include "DialogSearchIn.h"
#include "afxdialogex.h"


// CDialogSearchIn �Ի���

IMPLEMENT_DYNAMIC(CDialogSearchIn, CDialogEx)

CDialogSearchIn::CDialogSearchIn(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogSearchIn::IDD, pParent)
	, m_Row(_T(""))
	, m_Col(_T(""))
{

}

CDialogSearchIn::~CDialogSearchIn()
{
}

void CDialogSearchIn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditRow);
	DDX_Control(pDX, IDC_EDIT2, m_EditCol);
}


BEGIN_MESSAGE_MAP(CDialogSearchIn, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogSearchIn::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogSearchIn ��Ϣ�������


void CDialogSearchIn::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_EditRow.GetWindowTextW(m_Row);
	m_EditCol.GetWindowTextW(m_Col);
	if(m_Row == "" || m_Col == "" || m_Row.SpanIncluding( _T("0123456789"))!= m_Row || m_Col.SpanIncluding( _T("0123456789"))!= m_Col)
	{
		CString str1("�����ʽ����ȷ�����������룡");
		CString str2("��ʾ");
		MessageBox(str1,str2);
		m_Row = "";
		m_Col = "";
	}
	else
	{
		CDialogEx::OnOK();
	}
}
