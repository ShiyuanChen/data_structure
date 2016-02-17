// DialogSection.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "DialogSection.h"
#include "afxdialogex.h"


// CDialogSection �Ի���

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


// CDialogSection ��Ϣ�������

void CDialogSection::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		CString str1("�����ʽ����ȷ�����������룡");
		CString str2("��ʾ");
		MessageBox(str1,str2);
		m_Sec = "";
	}
	else
	{
		CDialogEx::OnOK();
	}
}