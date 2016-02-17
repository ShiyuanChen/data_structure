// DialogNew.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "DialogNew.h"
#include "afxdialogex.h"


// CDialogNew �Ի���

IMPLEMENT_DYNAMIC(CDialogNew, CDialogEx)

CDialogNew::CDialogNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogNew::IDD, pParent)
{

	m_ID = _T("");
	m_Name = _T("");
	m_Grade = _T("");
}

CDialogNew::~CDialogNew()
{
}

void CDialogNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditID);
	DDX_Control(pDX, IDC_EDIT2, m_EditName);
	DDX_Control(pDX, IDC_EDIT3, m_EditGrade);
}


BEGIN_MESSAGE_MAP(CDialogNew, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogNew::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogNew ��Ϣ�������

void CDialogNew::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_EditID.GetWindowTextW(m_ID);
	m_EditName.GetWindowTextW(m_Name);
	m_EditGrade.GetWindowTextW(m_Grade);
	if(m_ID == "0" || m_ID == "" || m_Name == "" || m_Grade == "" ||
		m_ID.SpanIncluding( _T("0123456789"))!= m_ID || m_Grade.SpanIncluding( _T("0123456789"))!= m_Grade)
	{
		CString str1("�����ʽ����ȷ�����������룡");
		CString str2("��ʾ");
		MessageBox(str1,str2);
		m_ID = "";
		m_Name = "";
		m_Grade = "";
	}
	else
	{
		int grade = _ttoi(m_Grade);
		if(grade > 100)
		{
			CString str1("�����������ޣ����������룡");
			CString str2("��ʾ");
			MessageBox(str1,str2);
			m_ID = "";
			m_Name = "";
			m_Grade = "";
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
}