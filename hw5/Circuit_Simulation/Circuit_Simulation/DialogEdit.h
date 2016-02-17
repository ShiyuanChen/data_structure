#pragma once
#include "afxwin.h"


// CDialogEdit 对话框

class CDialogEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogEdit)

public:
	CDialogEdit(int ISVS,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogEdit();

	// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combobox1;
	CComboBox m_Combobox2;
	CEdit m_EditText1;
	CEdit m_EditText2;
	CString m_Freq;
	CString m_Max;
	CString m_Unit1;
	CString m_Unit2;
	int isvs;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
