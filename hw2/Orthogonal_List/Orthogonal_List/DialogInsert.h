#pragma once
#include "afxwin.h"


// CDialogInsert 对话框

class CDialogInsert : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogInsert)

public:
	CDialogInsert(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogInsert();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_Row;
	CString m_Col;
	CString m_Data;
	CEdit m_EditRow;
	CEdit m_EditCol;
	CEdit m_EditData;
};
