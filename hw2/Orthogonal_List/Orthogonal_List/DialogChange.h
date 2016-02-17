#pragma once
#include "afxwin.h"


// CDialogChange 对话框

class CDialogChange : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogChange)

public:
	CDialogChange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogChange();

// 对话框数据
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditData;
	afx_msg void OnBnClickedOk();
	CString m_Data;
};
