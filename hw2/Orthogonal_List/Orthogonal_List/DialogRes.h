#pragma once


// CDialogRes 对话框

class CDialogRes : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRes)

public:
	CDialogRes(COrthogonal_ListDoc* pDoc,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogRes();

// 对话框数据
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Row;
	int m_Col;
	int m_Data;
	CString m_Text;
	virtual INT_PTR DoModal();
	COrthogonal_ListDoc* pDoc;
};
