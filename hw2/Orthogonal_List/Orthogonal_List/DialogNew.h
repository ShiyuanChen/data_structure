#pragma once
#include "afxwin.h"


// CDialogNew 对话框

class CDialogNew : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogNew)

public:
	CDialogNew(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogNew();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditRow;
	CEdit m_EditCol;
	afx_msg void OnBnClickedOk();
	CString m_Row;
	CString m_Col;
};
