#pragma once
#include "afxwin.h"


// CDialogSig �Ի���

class CDialogSig : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSig)

public:
	CDialogSig(bool ISVS,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogSig();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combobox1;
	CComboBox m_Combobox2;
	CComboBox m_Combobox3;
	CEdit m_EditText1;
	CEdit m_EditText2;
	CString m_Freq;
	CString m_Max;
	CString m_Unit1;
	CString m_Unit2;
	CString m_type;
	bool isvs;
	int type;
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo3();
	virtual BOOL OnInitDialog();
};
