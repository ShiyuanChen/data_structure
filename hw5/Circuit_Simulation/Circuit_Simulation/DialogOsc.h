#pragma once
#include "afxwin.h"


// CDialogOsc �Ի���

class CDialogOsc : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogOsc)

public:
	CDialogOsc(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogOsc();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combobox1;
	CString m_type;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
