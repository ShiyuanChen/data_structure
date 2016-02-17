#pragma once
#include "afxwin.h"


// CDialogDelete 对话框

class CDialogDelete : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDelete)

public:
	CDialogDelete(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogDelete();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditRow;
	CEdit m_EditCol;
	CString m_Row;
	CString m_Col;
	afx_msg void OnBnClickedOk();
};
