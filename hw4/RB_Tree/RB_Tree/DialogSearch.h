#pragma once
#include "afxwin.h"


// CDialogSearch �Ի���

class CDialogSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSearch)

public:
	CDialogSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogSearch();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit1;
	CEdit m_Edit2;
	CString m_from;
	CString m_to;
	afx_msg void OnBnClickedOk();
};
