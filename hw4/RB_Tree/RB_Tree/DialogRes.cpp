// DialogRes.cpp : 实现文件
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "RB_TreeDoc.h"
#include "DialogRes.h"
#include "afxdialogex.h"


// CDialogRes 对话框

IMPLEMENT_DYNAMIC(CDialogRes, CDialogEx)

	CDialogRes::CDialogRes(CRB_TreeDoc *pDoc,bool INORDER,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogRes::IDD, pParent)
	, m_Text(_T(""))
	, m_Node(0)
	, m_Stu(0)
	, pDoc(pDoc)
	, isinorder(INORDER)
{

}

CDialogRes::~CDialogRes()
{
}

void CDialogRes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, 1001, m_Node);
	DDX_Text(pDX, 1002, m_Stu);
	DDX_Text(pDX, 1000, m_Text);
}


BEGIN_MESSAGE_MAP(CDialogRes, CDialogEx)
END_MESSAGE_MAP()


// CDialogRes 消息处理程序


INT_PTR CDialogRes::DoModal()
{
	// TODO: 在此添加专用代码和/或调用基类
	int index = 0;
	if(isinorder)
	{
		inorder(pDoc->tree.root,index);
		m_Stu = index;
		m_Node = pDoc->tree.num;
	}
	else
	{
		vector<CNode *> *queue = new vector<CNode *>;
		int front = 0;
		int rear = 0;
		CNode * ptr = pDoc->tree.root;
		CString str0("、学号: ");
		CString str1(" ,    姓名：");
		CString str2(" ,    成绩: ");
		CString str3;
		CString trans;
		if(ptr != NULL)
		{

			queue->push_back(ptr);
			while(front <= rear)
			{
				for(unsigned int i = 0;i < queue->at(front)->stu.size();i ++)
				{
					index ++;
					trans.Format(TEXT("%d"),index);
					str3 = trans + str0;
					trans = queue->at(front)->stu.at(i)->ID;
					str3 += trans;
					trans = queue->at(front)->stu.at(i)->name;
					str3 += str1 + trans;
					trans.Format(TEXT("%d"),queue->at(front)->stu.at(i)->grade);
					str3 += str2 + trans + L"\r\n";
					m_Text.Append(str3);	
				}
				if(queue->at(front)->left != NULL)
				{
					rear++;
					queue->push_back(queue->at(front)->left);
				}
				if(queue->at(front)->right != NULL)
				{
					rear++;
					queue->push_back(queue->at(front)->right);
				}

				front ++;
			}
			queue->clear();
			m_Stu = index;
			m_Node = pDoc->tree.num;
		}
	}

	return CDialogEx::DoModal();
}


void CDialogRes::inorder(CNode * subtree,int &index)
{
	if(!subtree)
		return;
	CString str0("、学号: ");
	CString str1(" ,    姓名：");
	CString str2(" ,    成绩: ");
	CString str3;
	CString trans;
	inorder(subtree->left,index);
	for(unsigned int i = 0;i < subtree->stu.size();i ++)
	{
		index ++;
		trans.Format(TEXT("%d"),index);
		str3 = trans + str0;
		trans = subtree->stu.at(i)->ID;
		str3 += trans;
		trans = subtree->stu.at(i)->name;
		str3 += str1 + trans;
		trans.Format(TEXT("%d"),subtree->stu.at(i)->grade);
		str3 += str2 + trans + L"\r\n";
		m_Text.Append(str3);	
	}
	inorder(subtree->right,index);
}
