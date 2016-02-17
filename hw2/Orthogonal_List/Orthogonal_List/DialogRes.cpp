// DialogRes.cpp : 实现文件
//

#include "stdafx.h"
#include "Orthogonal_List.h"
#include "Orthogonal_ListDoc.h"
#include "DialogRes.h"
#include "afxdialogex.h"


// CDialogRes 对话框

IMPLEMENT_DYNAMIC(CDialogRes, CDialogEx)

	CDialogRes::CDialogRes(COrthogonal_ListDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogRes::IDD, pParent)
	, m_Row(0)
	, m_Col(0)
	, m_Data(0)
	, m_Text(_T(""))
	, pDoc(pDoc)
{

}

CDialogRes::~CDialogRes()
{
}

void CDialogRes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, 1001, m_Row);
	DDX_Text(pDX, 1002, m_Col);
	DDX_Text(pDX, IDC_EDIT4, m_Data);
	DDX_Text(pDX, 1000, m_Text);
}


BEGIN_MESSAGE_MAP(CDialogRes, CDialogEx)
END_MESSAGE_MAP()


// CDialogRes 消息处理程序


INT_PTR CDialogRes::DoModal()
{
	// TODO: 在此添加专用代码和/或调用基类
	CCrossList *clptr = pDoc->ClObj;
	if (clptr != NULL) {
		m_Row = clptr->getRow();
		m_Col = clptr->getCol();
		int sum = 0;
		Node *nodeptr;
		for (int i = 0; i < clptr->getRow(); ++i) 
		{
			nodeptr = clptr->assist.at(i)->Vhead;
			while (nodeptr->right != clptr->assist.at(i)->Vhead) 
			{
				sum++;
				nodeptr = nodeptr->right;
			}
		}
		m_Data = sum;

		for(int i = 0; i < m_Row; ++i) 
		{
			CString str;
			CString trans;
			if (clptr->assist.at(i)->Vhead->right != clptr->assist.at(i)->Vhead)
			{
				Node *node = clptr->assist.at(i)->Vhead->right;
				for (int j = 1; j <= m_Col; ++j) 
				{
					if (j == node->col) 
					{
						trans.Format(TEXT("%5d"),_ttoi(node->data));
						node = node->right;
					}
					else
					{
						trans.Format(TEXT("%5d"),0);
					}
					str.Append(trans);
				}

			} 
			else 
			{
				for (int j = 0; j < m_Col; ++j) 
				{
					trans.Format(TEXT("%5d"),0);
					str.Append(trans);
				}
			}
			m_Text.Append(str);
			m_Text.Append(L"\r\n");
		}
	}

	return CDialogEx::DoModal();
}
