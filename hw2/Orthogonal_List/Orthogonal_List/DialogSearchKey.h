#pragma once
#include "afxwin.h"


// CDialogSearchKey �Ի���

class CDialogSearchKey : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSearchKey)

public:
	CDialogSearchKey(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogSearchKey();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditData;
	CString m_Data;
	afx_msg void OnBnClickedOk();
};
