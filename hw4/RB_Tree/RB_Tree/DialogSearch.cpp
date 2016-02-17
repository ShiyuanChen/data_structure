// DialogSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "DialogSearch.h"
#include "afxdialogex.h"


// CDialogSearch �Ի���

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


// CDialogSearch ��Ϣ�������

void CDialogSearch::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Edit1.GetWindowTextW(m_from);
	m_Edit2.GetWindowTextW(m_to);
	if(m_from == "" || m_to == "" ||
		m_from.SpanIncluding( _T("0123456789"))!= m_from || m_to.SpanIncluding( _T("0123456789"))!= m_to)
	{
		CString str1("�����ʽ����ȷ�����������룡");
		CString str2("��ʾ");
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
			CString str1("�����������ޣ����������룡");
			CString str2("��ʾ");
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