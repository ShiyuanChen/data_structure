#pragma once
#include "afxwin.h"


// CDialogNew �Ի���

class CDialogNew : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogNew)

public:
	CDialogNew(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogNew();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditID;
	CEdit m_EditName;
	CEdit m_EditGrade;
	CString m_ID;
	CString m_Name;
	CString m_Grade;
	afx_msg void OnBnClickedOk();
};
