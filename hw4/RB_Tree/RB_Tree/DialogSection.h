#pragma once
#include "afxwin.h"


// CDialogSection 对话框

class CDialogSection : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSection)

public:
	CDialogSection(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogSection();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditText;
	CString m_Sec;
	afx_msg void OnBnClickedOk();
};
