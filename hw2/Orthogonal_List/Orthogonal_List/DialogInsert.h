#pragma once
#include "afxwin.h"


// CDialogInsert �Ի���

class CDialogInsert : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogInsert)

public:
	CDialogInsert(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogInsert();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_Row;
	CString m_Col;
	CString m_Data;
	CEdit m_EditRow;
	CEdit m_EditCol;
	CEdit m_EditData;
};
