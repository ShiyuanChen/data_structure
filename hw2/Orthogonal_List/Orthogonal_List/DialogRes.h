#pragma once


// CDialogRes �Ի���

class CDialogRes : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRes)

public:
	CDialogRes(COrthogonal_ListDoc* pDoc,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogRes();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_Row;
	int m_Col;
	int m_Data;
	CString m_Text;
	virtual INT_PTR DoModal();
	COrthogonal_ListDoc* pDoc;
};
