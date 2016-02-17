// DialogOsc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Circuit_Simulation.h"
#include "DialogOsc.h"
#include "afxdialogex.h"
#include "Node.h"


// CDialogOsc �Ի���

IMPLEMENT_DYNAMIC(CDialogOsc, CDialogEx)

	CDialogOsc::CDialogOsc(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogOsc::IDD, pParent)
	, m_type(_T(""))
{

}

CDialogOsc::~CDialogOsc()
{
}

void CDialogOsc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Combobox1);
}


BEGIN_MESSAGE_MAP(CDialogOsc, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogOsc::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogOsc ��Ϣ�������
void CDialogOsc::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex1 = m_Combobox1.GetCurSel();
	m_Combobox1.GetLBText(nIndex1,m_type);

	CDialogEx::OnOK();
}
BOOL CDialogOsc::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Combobox1.InsertString(0,L"��ѹ");
	m_Combobox1.InsertString(1,L"����");
	m_Combobox1.InsertString(2,L"��Ƶ����");
	m_Combobox1.InsertString(3,L"��Ƶ����");
	m_Combobox1.SetCurSel(0);
	return TRUE; 
}