// DialogSearchKey.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Orthogonal_List.h"
#include "DialogSearchKey.h"
#include "afxdialogex.h"


// CDialogSearchKey �Ի���

IMPLEMENT_DYNAMIC(CDialogSearchKey, CDialogEx)

CDialogSearchKey::CDialogSearchKey(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogSearchKey::IDD, pParent)
	, m_Data(_T(""))
{

}

CDialogSearchKey::~CDialogSearchKey()
{
}

void CDialogSearchKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditData);
}


BEGIN_MESSAGE_MAP(CDialogSearchKey, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogSearchKey::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogSearchKey ��Ϣ�������


void CDialogSearchKey::OnBnClickedOk()
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
