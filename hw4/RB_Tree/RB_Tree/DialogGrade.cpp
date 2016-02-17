// DialogGrade.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "DialogGrade.h"
#include "afxdialogex.h"


// CDialogGrade �Ի���

IMPLEMENT_DYNAMIC(CDialogGrade, CDialogEx)

	CDialogGrade::CDialogGrade(bool ISID,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogGrade::IDD, pParent)
	, m_Text(_T(""))
	, isID(ISID)
	, m_Static(_T(""))
{
	if(isID)
		m_Static = L"������ѧ�ţ�";
	else
		m_Static = L"������������";
}

CDialogGrade::~CDialogGrade()
{
}

void CDialogGrade::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditText);
	DDX_Text(pDX, IDC_STATIC10, m_Static);
}


BEGIN_MESSAGE_MAP(CDialogGrade, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogGrade::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogGrade ��Ϣ�������

void CDialogGrade::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_EditText.GetWindowTextW(m_Text);
	if(m_Text == "0" || m_Text == ""|| (isID && 
		m_Text.SpanIncluding( _T("0123456789"))!= m_Text))
	{
		CString str1("�����ʽ����ȷ�����������룡");
		CString str2("��ʾ");
		MessageBox(str1,str2);
		m_Text = "";
	}
	else
	{
		CDialogEx::OnOK();
	}
}