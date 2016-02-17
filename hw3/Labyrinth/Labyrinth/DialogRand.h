#pragma once
#include "afxwin.h"


// CDialogRand 对话框

class CDialogRand : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRand)

public:
	CDialogRand(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogRand();

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
