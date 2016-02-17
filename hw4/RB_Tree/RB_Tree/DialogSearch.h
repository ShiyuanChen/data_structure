#pragma once
#include "afxwin.h"


// CDialogSearch 对话框

class CDialogSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSearch)

public:
	CDialogSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogSearch();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit1;
	CEdit m_Edit2;
	CString m_from;
	CString m_to;
	afx_msg void OnBnClickedOk();
};
