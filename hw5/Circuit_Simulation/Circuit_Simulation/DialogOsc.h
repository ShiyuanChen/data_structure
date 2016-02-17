#pragma once
#include "afxwin.h"


// CDialogOsc 对话框

class CDialogOsc : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogOsc)

public:
	CDialogOsc(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogOsc();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combobox1;
	CString m_type;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
