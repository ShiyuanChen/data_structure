#pragma once
#include "afxwin.h"


// CDialogRatio �Ի���

class CDialogRatio : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRatio)

public:
	CDialogRatio(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogRatio();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditRatio;
	afx_msg void OnBnClickedOk();
	CString m_Ratio;
};
