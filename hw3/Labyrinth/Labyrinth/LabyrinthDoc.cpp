
// LabyrinthDoc.cpp : CLabyrinthDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Labyrinth.h"
#include <ctime>
#include <cstdlib>

#endif

#include "LabyrinthDoc.h"
#include "LabyrinthView.h"
#include "MainFrm.h"

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<queue>

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CLabyrinthDoc

IMPLEMENT_DYNCREATE(CLabyrinthDoc, CDocument)

	BEGIN_MESSAGE_MAP(CLabyrinthDoc, CDocument)
	END_MESSAGE_MAP()


	// CLabyrinthDoc 构造/析构

	CLabyrinthDoc::CLabyrinthDoc()
		: row(0)
		, col(0)
		, map(NULL)
		, ratio(0)
		, start(NULL)
		, end(NULL)
		, queue(NULL)
		, stack(NULL)
		, pq(NULL)
	{
		// TODO: 在此添加一次性构造代码

	}

	CLabyrinthDoc::~CLabyrinthDoc()
	{
	}

	BOOL CLabyrinthDoc::OnNewDocument()
	{
		if (!CDocument::OnNewDocument())
			return FALSE;

		// TODO: 在此添加重新初始化代码
		// (SDI 文档将重用该文档)
		SetTitle(L"迷宫");
		return TRUE;
	}




	// CLabyrinthDoc 序列化

	void CLabyrinthDoc::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			// TODO: 在此添加存储代码
			if(map != NULL)
			{
				int n = 0;
				for(int i = 1;i <= col;i++)
				{
					for(int j = 1;j <= row;j++)
					{
						if(map->at(i).at(j)->flag == 1)
							n++;
					}
				}
				ar << n << row << col << ratio << start->x << start->y << end->x << end->y;
				for(int i = 1;i <= col;i++)
				{
					for(int j = 1;j <= row;j++)
					{
						if(map->at(i).at(j)->flag == 1)
							ar << i << j;
					}
				}
			}

		}
		else
		{
			// TODO: 在此添加加载代码
			int n;
			ar >> n >> row >> col;
			createMap(row,col,0);
			ar >> ratio;
			int sx,sy,ex,ey;
			ar >> sx >> sy >> ex >> ey;
			setGoal(sx,sy,ex,ey);
			for(int i = 0;i < n; i++)
			{
				ar >> sx >> sy;
				map->at(sx).at(sy)->setFlag(1);
			}
			CMainFrame *m_pfm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			CLabyrinthView *m_pView = (CLabyrinthView*)m_pfm->GetActiveView();
			m_pView->loadRefresh();
		}
	}

#ifdef SHARED_HANDLERS

	// 缩略图的支持
	void CLabyrinthDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
	void CLabyrinthDoc::InitializeSearchContent()
	{
		CString strSearchContent;
		// 从文档数据设置搜索内容。
		// 内容部分应由“;”分隔

		// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
		SetSearchContent(strSearchContent);
	}

	void CLabyrinthDoc::SetSearchContent(const CString& value)
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

	// CLabyrinthDoc 诊断

#ifdef _DEBUG
	void CLabyrinthDoc::AssertValid() const
	{
		CDocument::AssertValid();
	}

	void CLabyrinthDoc::Dump(CDumpContext& dc) const
	{
		CDocument::Dump(dc);
	}
#endif //_DEBUG


	// CLabyrinthDoc 命令


	void CLabyrinthDoc::createMap(int ROW, int COL, double RATIO)
	{
		if(map != NULL)
		{
			map ->clear();
			delete map;
		}
		row = ROW;
		col = COL;
		ratio = RATIO;
		int flag = 0;
		int sum = row * col;
		int block = int(sum * ratio);
		int *xpos,*ypos;
		xpos = new int [block];
		ypos = new int [block];
		srand((unsigned)time( NULL ));
		map = new vector<vector<CNode*>>;
		for(int i = 0;i < col + 2;i++)
		{
			vector<CNode*> tempvec;
			for(int j = 0;j < row + 2;j++)
			{
				tempvec.push_back(new CNode(i,j,0));
			}
			map->push_back(tempvec);
		}
		for(int i = 0;i < block;i++)
		{
			xpos[i] = rand() % col + 1;
			ypos[i] = rand() % row + 1;
			map->at(xpos[i]).at(ypos[i])->setFlag(1);
		}
		for(int i = 0;i < col + 2;i ++)
		{
			map->at(i).at(0)->setFlag(1);
			map->at(i).at(row + 1)->setFlag(1);
		}
		for(int i = 1;i < row + 1;i ++)
		{
			map->at(0).at(i)->setFlag(1);
			map->at(col + 1).at(i)->setFlag(1);
		}

		queue = new vector<CNode*>;
		stack = new vector<CNode*>;
		pq = new priority_queue<CNode*,vector<CNode*>,Compare>;
	}


	void CLabyrinthDoc::randRefresh(void)
	{
		int sum = row * col;
		int block = int(sum * ratio);
		int *xpos,*ypos;
		xpos = new int [block];
		ypos = new int [block];
		srand((unsigned)time( NULL ));
		for(int i = 1;i < col + 1;i++)
		{
			vector<CNode*> tempvec = map->at(i);
			for(int j = 1;j < row + 1;j++)
			{
				tempvec.at(j)->setFlag(0);
			}
		}
		for(int i = 0;i < block;i++)
		{
			xpos[i] = rand() % col + 1;
			ypos[i] = rand() % row + 1;
			map->at(xpos[i]).at(ypos[i])->setFlag(1);
		}
	}


	void CLabyrinthDoc::setGoal(int sx, int sy, int ex, int ey)
	{
		start = map->at(sx).at(sy);
		start->setFlag(-1);
		end = map->at(ex).at(ey);
		end->setFlag(-2);
	}


	void CLabyrinthDoc::setGoal(void)
	{
		//srand((unsigned)time( NULL ));
		int sx,sy,ex,ey;
		bool flag = false;
		for(int i = 1;i < row + 1;i++)
		{
			sy = i;
			for(int j = 1;j < col + 1;j++)
			{
				sx = j;
				if(map->at(sx).at(sy)->getFlag() == 0)
				{
					start = map->at(sx).at(sy);
					start->setFlag(-1);
					flag = true;
					break;
				}
			}
			if(flag)
				break;
		}
		flag = false;
		for(int i = row;i > 0;i--)
		{
			ey = i;
			for(int j = col;j > 0;j--)
			{
				ex = j;
				if(map->at(ex).at(ey)->getFlag() == 0)
				{
					end = map->at(ex).at(ey);
					end->setFlag(-2);
					flag = true;
					break;
				}
			}
			if(flag)
				break;
		}
	}

	void CLabyrinthDoc::createModel(void)
	{
		if(map != NULL)
			map ->clear();
		row = 10;
		col = 10;
		ratio = 0.5;
		int flag = 0;
		int sum = row * col;
		int block[] = {4,6,7,8,9,10,12,14,15,16,18,19,
			21,22,24,25,26,27,29,32,37,39,40,41,42,45,
			46,49,51,56,57,58,59,64,65,67,72,74,76,78,
			79,82,85,86,87,96};

		map = new vector<vector<CNode*>>;
		for(int i = 0;i < col + 2;i++)
		{
			vector<CNode*> tempvec;
			for(int j = 0;j < row + 2;j++)
			{
				tempvec.push_back(new CNode(i,j,0));
			}
			map->push_back(tempvec);
		}
		for(int i = 0;i < 46;i++)
		{
			map->at((block[i]- 1) % 10 + 1).at((block[i] - 1) / 10 + 1)->setFlag(1);
		}
		for(int i = 0;i < col + 2;i ++)
		{
			map->at(i).at(0)->setFlag(1);
			map->at(i).at(row + 1)->setFlag(1);
		}
		for(int i = 1;i < row + 1;i ++)
		{
			map->at(0).at(i)->setFlag(1);
			map->at(col + 1).at(i)->setFlag(1);
		}

		queue = new vector<CNode*>;
		stack = new vector<CNode*>;
		pq = new priority_queue<CNode*,vector<CNode*>,Compare>;
		start = map->at(1).at(1);
		start->setFlag(-1);
		end = map->at(9).at(9);
		end->setFlag(-2);
	}


	void CLabyrinthDoc::loadFile(LPCTSTR lpszPathName)
	{
		CFileException fe;
		CFile* pFile = GetFile(lpszPathName,
			CFile::modeRead|CFile::shareDenyWrite, &fe);
		if (pFile == NULL)
		{
			ReportSaveLoadException(lpszPathName, &fe,
				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			return;
		}

		DeleteContents();
		SetModifiedFlag();  // dirty during de-serialize

		CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
		loadArchive.m_pDocument = this;
		loadArchive.m_bForceFlat = FALSE;
		TRY
		{
			CWaitCursor wait;
			if (pFile->GetLength() != 0)
				Serialize(loadArchive);     // load me
			loadArchive.Close();
			ReleaseFile(pFile, FALSE);
		}
		CATCH_ALL(e)
		{
			ReleaseFile(pFile, TRUE);
			DeleteContents();   // remove failed contents

			TRY
			{
				ReportSaveLoadException(lpszPathName, e,
					FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			}
			END_TRY
				return;
		}
		END_CATCH_ALL

			SetModifiedFlag(FALSE);     // start off with unmodified

		return;
	}


	void CLabyrinthDoc::saveFile(LPCTSTR lpszPathName)
	{
		CFileException fe;
		CFile* pFile = GetFile(lpszPathName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive, &fe);

		if (pFile == NULL)
		{
			ReportSaveLoadException(lpszPathName, &fe,
				TRUE, AFX_IDP_INVALID_FILENAME);
			return;
		}

		CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
		saveArchive.m_pDocument = this;
		saveArchive.m_bForceFlat = FALSE;
		TRY
		{
			CWaitCursor wait;
			Serialize(saveArchive);     // save me
			saveArchive.Close();
			ReleaseFile(pFile, FALSE);
		}
		CATCH_ALL(e)
		{
			ReleaseFile(pFile, TRUE);

			TRY
			{
				ReportSaveLoadException(lpszPathName, e,
					TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
			}
			END_TRY
				return;
		}
		END_CATCH_ALL
			SetModifiedFlag(FALSE);     // back to unmodified
		return;   
	}
