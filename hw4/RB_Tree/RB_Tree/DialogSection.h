#pragma once
#include "afxwin.h"


// CDialogSection �Ի���

class CDialogSection : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSection)

public:
	CDialogSection(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogSection();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditText;
	CString m_Sec;
	afx_msg void OnBnClickedOk();
};
