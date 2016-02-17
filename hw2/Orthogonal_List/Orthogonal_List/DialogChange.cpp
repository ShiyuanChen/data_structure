// DialogChange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Orthogonal_List.h"
#include "DialogChange.h"
#include "afxdialogex.h"


// CDialogChange �Ի���

IMPLEMENT_DYNAMIC(CDialogChange, CDialogEx)

CDialogChange::CDialogChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogChange::IDD, pParent)
	, m_Data(_T(""))
{

}

CDialogChange::~CDialogChange()
{
}

void CDialogChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditData);
}


BEGIN_MESSAGE_MAP(CDialogChange, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogChange::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogChange ��Ϣ�������


void CDialogChange::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_EditData.GetWindowTextW(m_Data);
	if(m_Data == "" || m_Data.SpanIncluding( _T("0123456789"))!= m_Data)
	{
		CString str1("�����ʽ����ȷ�����������룡");
		CString str2("��ʾ");
		MessageBox(str1,str2);
		m_Data = "";

	}
	else
	{
		CDialogEx::OnOK();
	}
}
