#pragma once


// CDialogRes �Ի���

class CDialogRes : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRes)

public:
	CDialogRes(CRB_TreeDoc *pDoc,bool INORDER,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogRes();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
