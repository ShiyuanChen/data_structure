// DialogDelete.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "DialogDelete.h"
#include "afxdialogex.h"


// CDialogDelete �Ի���

IMPLEMENT_DYNAMIC(CDialogDelete, CDialogEx)

CDialogDelete::CDialogDelete(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogDelete::IDD, pParent)
{

	m_ID = _T("");
}

CDialogDelete::~CDialogDelete()
{
}

void CDialogDelete::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditID);
}


BEGIN_MESSAGE_MAP(CDialogDelete, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogDelete::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogDelete ��Ϣ�������


void CDialogDelete::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_EditID.GetWindowTextW(m_ID);
	if(m_ID == "0" || m_ID == "" ||	m_ID.SpanIncluding( _T("0123456789"))!= m_ID)
	{
		CString str1("�����ʽ����ȷ�����������룡");
		CString str2("��ʾ");
		MessageBox(str1,str2);
		m_ID = "";
	}
	else
	{
		CDialogEx::OnOK();
	}
}