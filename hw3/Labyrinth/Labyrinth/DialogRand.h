#pragma once
#include "afxwin.h"


// CDialogRand �Ի���

class CDialogRand : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRand)

public:
	CDialogRand(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogRand();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

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
