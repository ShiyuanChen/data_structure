#pragma once
#include "afxwin.h"


// CDialogSearchIn �Ի���

class CDialogSearchIn : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSearchIn)

public:
	CDialogSearchIn(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogSearchIn();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditRow;
	CEdit m_EditCol;
	CString m_Row;
	CString m_Col;
	afx_msg void OnBnClickedOk();
};
