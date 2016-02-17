#pragma once
#include "afxwin.h"


// CDialogResize 对话框

class CDialogResize : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogResize)

public:
	CDialogResize(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogResize();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

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
