#pragma once
#include "afxwin.h"


// CDialogRatio 对话框

class CDialogRatio : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRatio)

public:
	CDialogRatio(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogRatio();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditRatio;
	afx_msg void OnBnClickedOk();
	CString m_Ratio;
};
