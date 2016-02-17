#pragma once
#include "afxwin.h"


// CDialogSearchKey 对话框

class CDialogSearchKey : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSearchKey)

public:
	CDialogSearchKey(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogSearchKey();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditData;
	CString m_Data;
	afx_msg void OnBnClickedOk();
};
