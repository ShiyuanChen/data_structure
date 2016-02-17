#pragma once
#include "afxwin.h"


// CDialogEntry 对话框

class CDialogEntry : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogEntry)

public:
	CDialogEntry(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogEntry();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditSx;
	CEdit m_EditSy;
	CEdit m_EditEx;
	CEdit m_EditEy;
	afx_msg void OnBnClickedOk();
	CString m_Sx;
	CString m_Ey;
	CString m_Sy;
	CString m_Ex;
	int m_Row;
	int m_Col;
};
