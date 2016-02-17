#pragma once


// CDialogRes 对话框

class CDialogRes : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRes)

public:
	CDialogRes(CRB_TreeDoc *pDoc,bool INORDER,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogRes();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Text;
	int m_Node;
	int m_Stu;
	CRB_TreeDoc *pDoc;
	virtual INT_PTR DoModal();
	bool isinorder;
	void inorder(CNode * subtree,int &index);
};
