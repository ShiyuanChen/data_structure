// DialogInsert.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Orthogonal_List.h"
#include "DialogInsert.h"
#include "afxdialogex.h"




// CDialogInsert �Ի���

IMPLEMENT_DYNAMIC(CDialogInsert, CDialogEx)

CDialogInsert::CDialogInsert(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogInsert::IDD, pParent)
	, m_Row(_T(""))
	, m_Col(_T(""))
	, m_Data(_T(""))
{

}

CDialogInsert::~CDialogInsert()
{
}

void CDialogInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Row);
	DDX_Text(pDX, IDC_EDIT2, m_Col);
	DDX_Text(pDX, IDC_EDIT3, m_Data);
	DDX_Control(pDX, IDC_EDIT1, m_EditRow);
	DDX_Control(pDX, IDC_EDIT2, m_EditCol);
	DDX_Control(pDX, IDC_EDIT3, m_EditData);
}


BEGIN_MESSAGE_MAP(CDialogInsert, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogInsert::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogInsert ��Ϣ�������


void CDialogInsert::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_EditRow.GetWindowTextW(m_Row);
	m_EditCol.GetWindowTextW(m_Col);
	m_EditData.GetWindowTextW(m_Data);
	if(m_Row == "" || m_Col == "" || m_Data == "" || m_Row.SpanIncluding( _T("0123456789"))!= m_Row || m_Col.SpanIncluding( _T("0123456789"))!= m_Col || m_Data.SpanIncluding( _T("0123456789"))!= m_Data)
	{
		CString str1("�����ʽ����ȷ�����������룡");
		CString str2("��ʾ");
		MessageBox(str1,str2);
		m_Row = "";
		m_Col = "";
		m_Data = "";

	}
	else
	{
		CDialogEx::OnOK();
	}
}



//INT_PTR CDialogInsert::DoModal()
//{
//	// TODO: �ڴ����ר�ô����/����û���
//	return CDialogEx::DoModal();
//}

