// DialogOsc.cpp : 实现文件
//

#include "stdafx.h"
#include "Circuit_Simulation.h"
#include "DialogOsc.h"
#include "afxdialogex.h"
#include "Node.h"


// CDialogOsc 对话框

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


// CDialogOsc 消息处理程序
void CDialogOsc::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex1 = m_Combobox1.GetCurSel();
	m_Combobox1.GetLBText(nIndex1,m_type);

	CDialogEx::OnOK();
}
BOOL CDialogOsc::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Combobox1.InsertString(0,L"电压");
	m_Combobox1.InsertString(1,L"电流");
	m_Combobox1.InsertString(2,L"幅频曲线");
	m_Combobox1.InsertString(3,L"相频曲线");
	m_Combobox1.SetCurSel(0);
	return TRUE; 
}