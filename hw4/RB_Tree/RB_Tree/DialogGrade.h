#pragma once
#include "afxwin.h"


// CDialogGrade �Ի���

class CDialogGrade : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogGrade)

public:
	CDialogGrade(bool ISID,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogGrade();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditText;
	CString m_Text;
	bool isID;
	CString m_Static;
	afx_msg void OnBnClickedOk();
};
