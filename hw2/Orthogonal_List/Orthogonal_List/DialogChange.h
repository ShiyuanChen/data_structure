#pragma once
#include "afxwin.h"


// CDialogChange �Ի���

class CDialogChange : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogChange)

public:
	CDialogChange(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogChange();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditData;
	afx_msg void OnBnClickedOk();
	CString m_Data;
};
