#pragma once
#include "afxwin.h"


// CDialogDelete �Ի���

class CDialogDelete : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDelete)

public:
	CDialogDelete(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogDelete();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

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
