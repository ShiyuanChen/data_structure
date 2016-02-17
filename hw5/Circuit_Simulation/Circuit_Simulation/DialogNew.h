#pragma once
#include "afxwin.h"


// CDialogNew 对话框

class CDialogNew : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogNew)

public:
	CDialogNew(int TYPE,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogNew();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combobox;
	CEdit m_EditText;
	CString m_Text;
	CString m_Unit;
	int type;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
