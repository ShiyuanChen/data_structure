
// Orthogonal_ListDoc.cpp : COrthogonal_ListDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Orthogonal_List.h"
#endif

#include "CrossList.h"
#include "DrawUnit.h"
#include "Orthogonal_ListDoc.h"

#include "Orthogonal_ListView.h"
#include "MainFrm.h"

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COrthogonal_ListDoc

IMPLEMENT_DYNCREATE(COrthogonal_ListDoc, CDocument)

	BEGIN_MESSAGE_MAP(COrthogonal_ListDoc, CDocument)
	END_MESSAGE_MAP()


	// COrthogonal_ListDoc 构造/析构

	COrthogonal_ListDoc::COrthogonal_ListDoc()
	{
		// TODO: 在此添加一次性构造代码
		ClObj = NULL;
	}

	COrthogonal_ListDoc::~COrthogonal_ListDoc()
	{
	}

	BOOL COrthogonal_ListDoc::OnNewDocument()
	{
		if (!CDocument::OnNewDocument())
			return FALSE;

		// TODO: 在此添加重新初始化代码
		// (SDI 文档将重用该文档)
		SetTitle(L"十字链表");
		return TRUE;
	}




	// COrthogonal_ListDoc 序列化

	void COrthogonal_ListDoc::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			// TODO: 在此添加存储代码
			if(ClObj != NULL)
			{
				int n = 0;
				for(int i = 0;i < ClObj->getCol();i++)
				{
					Node * nodeptr = ClObj->assist.at(i)->Hhead->down;
					while(nodeptr != ClObj->assist.at(i)->Hhead)
					{
						n++;
						nodeptr = nodeptr->down;
					}
				}
				ar << n;
				for(int i = 0;i < ClObj->getCol();i++)
				{
					Node * nodeptr = ClObj->assist.at(i)->Hhead->down;
					while(nodeptr != ClObj->assist.at(i)->Hhead)
					{
						ar << nodeptr->row << nodeptr->col << _ttoi(nodeptr->data);
						nodeptr = nodeptr->down;
					}
				}
			}
		}
		else
		{
			// TODO: 在此添加加载代码
			delete ClObj;
			ClObj = new CCrossList(0,0);
			int n;
			int row,col,data;
			CString str;
			ar >> n;
			for(int i = 0;i < n; i++)
			{
				ar >> row >> col >> data;
				str.Format(TEXT("%d"),data);
				ClObj->insertNode(row,col,str);
			}
			CMainFrame *m_pfm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			COrthogonal_ListView *m_pView = (COrthogonal_ListView*)m_pfm->GetActiveView();
			m_pView->loadRefresh();
		}
	}

#ifdef SHARED_HANDLERS

	// 缩略图的支持
	void COrthogonal_ListDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
	{
		// 修改此代码以绘制文档数据
		dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

		CString strText = _T("TODO: implement thumbnail drawing here");
		LOGFONT lf;

		CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
		pDefaultGUIFont->GetLogFont(&lf);
		lf.lfHeight = 36;

		CFont fontDraw;
		fontDraw.CreateFontIndirect(&lf);

		CFont* pOldFont = dc.SelectObject(&fontDraw);
		dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
		dc.SelectObject(pOldFont);
	}

	// 搜索处理程序的支持
	void COrthogonal_ListDoc::InitializeSearchContent()
	{
		CString strSearchContent;
		// 从文档数据设置搜索内容。
		// 内容部分应由“;”分隔

		// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
		SetSearchContent(strSearchContent);
	}

	void COrthogonal_ListDoc::SetSearchContent(const CString& value)
	{
		if (value.IsEmpty())
		{
			RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
		}
		else
		{
			CMFCFilterChunkValueImpl *pChunk = NULL;
			ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
			if (pChunk != NULL)
			{
				pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
				SetChunkValue(pChunk);
			}
		}
	}

#endif // SHARED_HANDLERS

	// COrthogonal_ListDoc 诊断

#ifdef _DEBUG
	void COrthogonal_ListDoc::AssertValid() const
	{
		CDocument::AssertValid();
	}

	void COrthogonal_ListDoc::Dump(CDumpContext& dc) const
	{
		CDocument::Dump(dc);
	}
#endif //_DEBUG


	// COrthogonal_ListDoc 命令


	CCrossList * COrthogonal_ListDoc::NewCrossList(int ROW, int COL)
	{
		ClObj = new CCrossList(ROW,COL);
		Node * nodeptr = NULL;
		CString tempdata;

		if(ROW < COL)
		{
			for(int i = 0;i < ROW;i++)
			{		
				tempdata.Format(TEXT("%d"),(i+1)*11);
				nodeptr = ClObj->insertNode(i+1,i+1,tempdata);
			}
			for(int j = 0;j < COL-ROW;j++)
			{
				tempdata.Format(TEXT("%d"),ROW*11+j+1);
				nodeptr = ClObj->insertNode(ROW,j+1+ROW,tempdata);
			}
		}
		else
		{
			for(int i = 0;i < COL;i++)
			{
				tempdata.Format(TEXT("%d"),(i+1)*11);
				nodeptr = ClObj->insertNode(i+1,i+1,tempdata);
			}
			for(int j = 0;j < ROW-COL;j++)
			{
				tempdata.Format(TEXT("%d"),COL*11+j+1);
				nodeptr = ClObj->insertNode(j+1+COL,COL,tempdata);
			}
		}
		CCrossList *clptr = ClObj;
		return clptr;
	}

