
// Orthogonal_ListDoc.cpp : COrthogonal_ListDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


	// COrthogonal_ListDoc ����/����

	COrthogonal_ListDoc::COrthogonal_ListDoc()
	{
		// TODO: �ڴ����һ���Թ������
		ClObj = NULL;
	}

	COrthogonal_ListDoc::~COrthogonal_ListDoc()
	{
	}

	BOOL COrthogonal_ListDoc::OnNewDocument()
	{
		if (!CDocument::OnNewDocument())
			return FALSE;

		// TODO: �ڴ�������³�ʼ������
		// (SDI �ĵ������ø��ĵ�)
		SetTitle(L"ʮ������");
		return TRUE;
	}




	// COrthogonal_ListDoc ���л�

	void COrthogonal_ListDoc::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			// TODO: �ڴ���Ӵ洢����
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
			// TODO: �ڴ���Ӽ��ش���
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

	// ����ͼ��֧��
	void COrthogonal_ListDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
	{
		// �޸Ĵ˴����Ի����ĵ�����
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

	// ������������֧��
	void COrthogonal_ListDoc::InitializeSearchContent()
	{
		CString strSearchContent;
		// ���ĵ����������������ݡ�
		// ���ݲ���Ӧ�ɡ�;���ָ�

		// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

	// COrthogonal_ListDoc ���

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


	// COrthogonal_ListDoc ����


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

