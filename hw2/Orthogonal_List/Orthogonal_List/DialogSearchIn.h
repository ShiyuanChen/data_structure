#pragma once
#include "afxwin.h"


// CDialogSearchIn 对话框

class CDialogSearchIn : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSearchIn)

public:
	CDialogSearchIn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogSearchIn();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

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
