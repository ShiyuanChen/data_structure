// DialogRatio.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Labyrinth.h"
#include "DialogRatio.h"
#include "afxdialogex.h"


// CDialogRatio �Ի���

IMPLEMENT_DYNAMIC(CDialogRatio, CDialogEx)

CDialogRatio::CDialogRatio(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogRatio::IDD, pParent)
{
	m_Ratio = _T("");
}

CDialogRatio::~CDialogRatio()
{
}

void CDialogRatio::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditRatio);
}


BEGIN_MESSAGE_MAP(CDialogRatio, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogRatio::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogRatio ��Ϣ�������

void CDialogRatio::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_EditRatio.GetWindowTextW(m_Ratio);

	if(m_Ratio == "0" || m_Ratio == "" ||
		m_Ratio.SpanIncluding( _T(".0123456789"))!= m_Ratio)
	{
		CString str1("�����ʽ����ȷ�����������룡");
		CString str2("��ʾ");
		MessageBox(str1,str2);
		m_Ratio = "";
	}
	else
	{
		double ratio = _wtof(m_Ratio);
		if(ratio > 0.8 || ratio < 0)
		{
			CString str1("�������ޣ����������룡");
			CString str2("��ʾ");
			MessageBox(str1,str2);
			m_Ratio = "";
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
}