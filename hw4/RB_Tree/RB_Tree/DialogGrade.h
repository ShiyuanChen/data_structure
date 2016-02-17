#pragma once
#include "afxwin.h"


// CDialogGrade 对话框

class CDialogGrade : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogGrade)

public:
	CDialogGrade(bool ISID,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogGrade();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditText;
	CString m_Text;
	bool isID;
	CString m_Static;
	afx_msg void OnBnClickedOk();
};
