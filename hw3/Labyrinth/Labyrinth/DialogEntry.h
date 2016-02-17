#pragma once
#include "afxwin.h"


// CDialogEntry �Ի���

class CDialogEntry : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogEntry)

public:
	CDialogEntry(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogEntry();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditSx;
	CEdit m_EditSy;
	CEdit m_EditEx;
	CEdit m_EditEy;
	afx_msg void OnBnClickedOk();
	CString m_Sx;
	CString m_Ey;
	CString m_Sy;
	CString m_Ex;
	int m_Row;
	int m_Col;
};
