#pragma once
#include "afxwin.h"


// CDialogNew �Ի���

class CDialogNew : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogNew)

public:
	CDialogNew(int TYPE,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogNew();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combobox;
	CEdit m_EditText;
	CString m_Text;
	CString m_Unit;
	int type;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
