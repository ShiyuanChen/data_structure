#pragma once
#include "afxwin.h"


// CDialogResize �Ի���

class CDialogResize : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogResize)

public:
	CDialogResize(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogResize();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditRow;
	CEdit m_EditCol;
	afx_msg void OnBnClickedOk();
	CString m_Row;
	CString m_Col;
};
