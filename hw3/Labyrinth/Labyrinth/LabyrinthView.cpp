
// LabyrinthView.cpp : CLabyrinthView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Labyrinth.h"
#endif

#include "Node.h"
#include "LabyrinthDoc.h"
#include "LabyrinthView.h"
#include "DialogRand.h"
#include "DialogNew.h"
#include "DialogResize.h"
#include "DialogEntry.h"
#include "DialogRatio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#ifndef _MAXWIDTH
#define MAXWIDTH 2000;
#define MAXHEIGHT 1000;
#define _MAXWIDTH
#endif

// CLabyrinthView

IMPLEMENT_DYNCREATE(CLabyrinthView, CScrollView)

	BEGIN_MESSAGE_MAP(CLabyrinthView, CScrollView)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_WM_CREATE()
		ON_COMMAND(ID_MAP_RAND, &CLabyrinthView::OnMapRand)
		ON_WM_SIZE()
		ON_COMMAND(ID_MAP_REFRESH, &CLabyrinthView::OnMapRefresh)
		ON_UPDATE_COMMAND_UI(ID_MAP_REFRESH, &CLabyrinthView::OnUpdateMapRefresh)
		ON_COMMAND(ID_MAP_NEW, &CLabyrinthView::OnMapNew)
		ON_COMMAND(ID_MAP_RESIZE, &CLabyrinthView::OnMapResize)
		ON_COMMAND(ID_WIDTH_PRIOR, &CLabyrinthView::OnWidthPrior)
		ON_COMMAND(ID_DEPTH_PRIOR, &CLabyrinthView::OnDepthPrior)
		ON_COMMAND(ID_MAP_ENTRY, &CLabyrinthView::OnMapEntry)
		ON_COMMAND(ID_MAP_RATIO, &CLabyrinthView::OnMapRatio)
		ON_COMMAND(ID_SEARCH_START, &CLabyrinthView::OnSearchStart)
		ON_WM_TIMER()
		ON_COMMAND(ID_SEARCH_ANALYSIS, &CLabyrinthView::OnSearchAnalysis)
		ON_COMMAND(ID_RATE_DOWN, &CLabyrinthView::OnRateDown)
		ON_COMMAND(ID_RATE_UP, &CLabyrinthView::OnRateUp)
		ON_WM_MOUSEMOVE()
		ON_COMMAND(ID_START_SET, &CLabyrinthView::OnStartSet)
		ON_COMMAND(ID_END_SET, &CLabyrinthView::OnEndSet)
		ON_UPDATE_COMMAND_UI(ID_START_SET, &CLabyrinthView::OnUpdateStartSet)
		ON_UPDATE_COMMAND_UI(ID_END_SET, &CLabyrinthView::OnUpdateEndSet)
		//		ON_COMMAND(ID_TYPE_CHANGE, &CLabyrinthView::OnTypeChange)
		//		ON_UPDATE_COMMAND_UI(ID_TYPE_CHANGE, &CLabyrinthView::OnUpdateTypeChange)
		ON_COMMAND(ID_FLAG_CHANGE, &CLabyrinthView::OnFlagChange)
		ON_UPDATE_COMMAND_UI(ID_FLAG_CHANGE, &CLabyrinthView::OnUpdateFlagChange)
		//ON_UPDATE_COMMAND_UI(ID_MAP_EDIT, &CLabyrinthView::OnUpdateMapEdit)
		ON_UPDATE_COMMAND_UI(ID_MAP_RESIZE, &CLabyrinthView::OnUpdateMapResize)
		ON_UPDATE_COMMAND_UI(ID_MAP_ENTRY, &CLabyrinthView::OnUpdateMapEntry)
		ON_UPDATE_COMMAND_UI(ID_MAP_RATIO, &CLabyrinthView::OnUpdateMapRatio)
		ON_UPDATE_COMMAND_UI(ID_SEARCH_START, &CLabyrinthView::OnUpdateSearchStart)
		ON_UPDATE_COMMAND_UI(ID_SEARCH_ANALYSIS, &CLabyrinthView::OnUpdateSearchAnalysis)
		ON_UPDATE_COMMAND_UI(ID_RATE_DOWN, &CLabyrinthView::OnUpdateRateDown)
		ON_UPDATE_COMMAND_UI(ID_RATE_UP, &CLabyrinthView::OnUpdateRateUp)
		ON_COMMAND(ID_SEARCH_PAUSE, &CLabyrinthView::OnSearchPause)
		ON_UPDATE_COMMAND_UI(ID_SEARCH_PAUSE, &CLabyrinthView::OnUpdateSearchPause)
		ON_UPDATE_COMMAND_UI(ID_WIDTH_PRIOR, &CLabyrinthView::OnUpdateWidthPrior)
		ON_UPDATE_COMMAND_UI(ID_DEPTH_PRIOR, &CLabyrinthView::OnUpdateDepthPrior)
		ON_COMMAND(ID_SEARCH_STOP, &CLabyrinthView::OnSearchStop)
		ON_UPDATE_COMMAND_UI(ID_SEARCH_STOP, &CLabyrinthView::OnUpdateSearchStop)
		ON_UPDATE_COMMAND_UI(ID_MAP_NEW, &CLabyrinthView::OnUpdateMapNew)
		ON_UPDATE_COMMAND_UI(ID_MAP_RAND, &CLabyrinthView::OnUpdateMapRand)
		ON_UPDATE_COMMAND_UI(ID_MAP_DEFAULT, &CLabyrinthView::OnUpdateMapDefault)
		ON_UPDATE_COMMAND_UI(ID_MAP_INPUT, &CLabyrinthView::OnUpdateMapInput)
		ON_COMMAND(ID_DEPTH_PRIOR2, &CLabyrinthView::OnDepthPrior2)
		ON_UPDATE_COMMAND_UI(ID_DEPTH_PRIOR2, &CLabyrinthView::OnUpdateDepthPrior2)
		ON_COMMAND(ID_ASTAR_SEARCH, &CLabyrinthView::OnAstarSearch)
		ON_UPDATE_COMMAND_UI(ID_ASTAR_SEARCH, &CLabyrinthView::OnUpdateAstarSearch)
		ON_COMMAND(ID_MAP_DEFAULT, &CLabyrinthView::OnMapDefault)
		ON_COMMAND(ID_MAP_INPUT, &CLabyrinthView::OnMapInput)
		ON_COMMAND(ID_FILE_OPEN, &CLabyrinthView::OnFileOpen)
		ON_COMMAND(ID_FILE_SAVE, &CLabyrinthView::OnFileSave)
		ON_COMMAND(ID_FILE_NEW, &CLabyrinthView::OnFileNew)
		ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CLabyrinthView::OnUpdateFileOpen)
		ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CLabyrinthView::OnUpdateFileNew)
	END_MESSAGE_MAP()

	// CLabyrinthView 构造/析构

	CLabyrinthView::CLabyrinthView()
		: FrmWidth(0)
		, FrmHeight(0)
		, m_pMemDC(NULL)
		, m_pBitmap(NULL)
		, type(0)
		, rate(300)
		, stepcount(0)
		, trace(NULL)
		, front(0)
		, rear(0)
		, validcount(0)
		, highlight(NULL)
		, issearch(false)
		, block(NULL)
		, ispause(false)
		, aptr(NULL)
	{
		// TODO: 在此处添加构造代码
		m_pMemDC = new CDC();
		m_pBitmap = new CBitmap();
		trace = new vector<CNode*>;
	}
	int CLabyrinthView::zx[8] = {1,1,0,-1,-1,-1,0,1};
	int CLabyrinthView::zy[8] = {0,1,1,1,0,-1,-1,-1};

	CLabyrinthView::~CLabyrinthView()
	{
		m_pMemDC->DeleteDC();
		m_pBitmap->DeleteObject();
		delete m_pMemDC;
		delete m_pBitmap;
	}

	BOOL CLabyrinthView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CScrollView::PreCreateWindow(cs);
	}

	// CLabyrinthView 绘制

	void CLabyrinthView::OnDraw(CDC* pDC)
	{
		CLabyrinthDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 在此处为本机数据添加绘制代码
		if(m_pBitmap != NULL,m_pMemDC != NULL)
		{
			CRect rc;
			GetClientRect(rc);
			pDC->BitBlt(0,0,rc.Width(),rc.Height(),m_pMemDC,0,0,SRCCOPY); 
		}

	}

	void CLabyrinthView::OnInitialUpdate()
	{
		CScrollView::OnInitialUpdate();

		CSize sizeTotal;
		// TODO: 计算此视图的合计大小
		sizeTotal.cx = sizeTotal.cy = 100;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}

	void CLabyrinthView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void CLabyrinthView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CLabyrinthView 诊断

#ifdef _DEBUG
	void CLabyrinthView::AssertValid() const
	{
		CScrollView::AssertValid();
	}

	void CLabyrinthView::Dump(CDumpContext& dc) const
	{
		CScrollView::Dump(dc);
	}

	CLabyrinthDoc* CLabyrinthView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLabyrinthDoc)));
		return (CLabyrinthDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CLabyrinthView 消息处理程序


	int CLabyrinthView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CScrollView::OnCreate(lpCreateStruct) == -1)
			return -1;
		// TODO:  在此添加您专用的创建代码
		CDC* pDC=GetDC();
		m_pMemDC->CreateCompatibleDC(pDC);
		return 0;
	}


	void CLabyrinthView::OnMapRand()
	{
		// TODO: 在此添加命令处理程序代码
		CLabyrinthDoc *pDoc = GetDocument();
		CDialogRand randdlg;
		int result = randdlg.DoModal();
		if(result == IDOK)
		{
			int x = MAXWIDTH;
			int y = MAXHEIGHT;
			int trow = _ttoi(randdlg.m_Row);
			int tcol = _ttoi(randdlg.m_Col);
			CRect rc;
			GetWindowRect(rc);

			pDoc->createMap(trow,tcol,0.5);
			pDoc->setGoal();
			FrmHeight  = double(rc.Height()) / (pDoc->row + 2);
			FrmWidth = double(rc.Width()) / (pDoc->col + 2);
			CDC* pDC=GetDC();
			if(m_pMemDC != NULL)
				m_pMemDC->DeleteDC();
			if(m_pBitmap != NULL)
				m_pBitmap->DeleteObject();
			m_pMemDC->CreateCompatibleDC(pDC);
			m_pBitmap->CreateCompatibleBitmap(pDC,x,y);
			m_pMemDC->SelectObject(m_pBitmap);

			drawAll(m_pMemDC);
			Invalidate();
		}
	}


	void CLabyrinthView::drawAll(CDC *pDC)
	{
		CLabyrinthDoc *pDoc = GetDocument();
		int x = MAXWIDTH;
		int y = MAXHEIGHT;
		m_pMemDC->FillSolidRect(0, 0,x,y,RGB(255,255,255));
		if(pDoc->row != 0 && pDoc->col != 0)
		{
			CNode::height = FrmHeight;
			CNode::width = FrmWidth;
			for(int i = 0;i < pDoc->col + 2;i++)
			{
				for(int j = 0;j < pDoc->row + 2;j++)
				{
					pDoc->map->at(i).at(j)->Draw(pDC);
				}
			}
		}
	}


	void CLabyrinthView::OnSize(UINT nType, int cx, int cy)
	{
		CScrollView::OnSize(nType, cx, cy);

		//TODO: 在此处添加消息处理程序代码
		CLabyrinthDoc *pDoc = GetDocument();

		if(pDoc->row != 0)
		{
			FrmHeight  = double(cy) / (pDoc->row + 2);
			FrmWidth = double(cx) / (pDoc->col + 2);

			drawAll(m_pMemDC);

			this->Invalidate(0);

		}
	}


	void CLabyrinthView::OnMapRefresh()
	{
		// TODO: 在此添加命令处理程序代码
		CLabyrinthDoc * pDoc = GetDocument();
		pDoc->randRefresh();
		pDoc->setGoal();
		drawAll(m_pMemDC);
		Invalidate(false);

	}


	void CLabyrinthView::OnMapNew()
	{
		// TODO: 在此添加命令处理程序代码
		CLabyrinthDoc *pDoc = GetDocument();
		CDialogNew newddlg;
		int result = newddlg.DoModal();
		if(result == IDOK)
		{
			int x = MAXWIDTH;
			int y = MAXHEIGHT;
			int trow = _ttoi(newddlg.m_Row);
			int tcol = _ttoi(newddlg.m_Col);
			double tratio = _wtof(newddlg.m_Ratio);
			int sx = _ttoi(newddlg.m_Sx);
			int sy = _ttoi(newddlg.m_Sy);
			int ex = _ttoi(newddlg.m_Ex);
			int ey = _ttoi(newddlg.m_Ey);
			CRect rc;
			GetWindowRect(rc);

			pDoc->createMap(trow,tcol,tratio);
			pDoc->setGoal(sx,sy,ex,ey);
			FrmHeight  = double(rc.Height()) / (pDoc->row + 2);
			FrmWidth = double(rc.Width()) / (pDoc->col + 2);
			CDC* pDC=GetDC();
			if(m_pMemDC != NULL)
				m_pMemDC->DeleteDC();
			if(m_pBitmap != NULL)
				m_pBitmap->DeleteObject();
			m_pMemDC->CreateCompatibleDC(pDC);
			m_pBitmap->CreateCompatibleBitmap(pDC,x,y);
			m_pMemDC->SelectObject(m_pBitmap);

			drawAll(m_pMemDC);
			Invalidate();
		}
	}


	void CLabyrinthView::OnMapResize()
	{
		// TODO: 在此添加命令处理程序代码
		CLabyrinthDoc *pDoc = GetDocument();
		CDialogResize randdlg;
		int result = randdlg.DoModal();
		if(result == IDOK)
		{
			int x = MAXWIDTH;
			int y = MAXHEIGHT;
			int trow = _ttoi(randdlg.m_Row);
			int tcol = _ttoi(randdlg.m_Col);
			CRect rc;
			GetWindowRect(rc);

			pDoc->createMap(trow,tcol,pDoc->ratio);
			pDoc->setGoal();
			FrmHeight  = double(rc.Height()) / (pDoc->row + 2);
			FrmWidth = double(rc.Width()) / (pDoc->col + 2);

			drawAll(m_pMemDC);
			Invalidate();
		}
	}


	void CLabyrinthView::OnWidthPrior()
	{
		// TODO: 在此添加命令处理程序代码
		type = 0;
	}


	void CLabyrinthView::OnDepthPrior()
	{
		// TODO: 在此添加命令处理程序代码
		type = 1;
	}


	void CLabyrinthView::OnDepthPrior2()
	{
		// TODO: 在此添加命令处理程序代码
		type = 2;
	}


	void CLabyrinthView::OnAstarSearch()
	{
		// TODO: 在此添加命令处理程序代码
		type = 3;
	}


	void CLabyrinthView::OnMapEntry()
	{
		// TODO: 在此添加命令处理程序代码
		CLabyrinthDoc *pDoc = GetDocument();
		CDialogEntry entrydlg;
		entrydlg.m_Row = pDoc->row;
		entrydlg.m_Col = pDoc->col;
		int result = entrydlg.DoModal();
		if(result == IDOK)
		{
			int x = MAXWIDTH;
			int y = MAXHEIGHT;
			int sx = _ttoi(entrydlg.m_Sx);
			int sy = _ttoi(entrydlg.m_Sy);
			int ex = _ttoi(entrydlg.m_Ex);
			int ey = _ttoi(entrydlg.m_Ey);

			pDoc->start->setFlag(0);
			pDoc->start->Draw(m_pMemDC);
			pDoc->end->setFlag(0);
			pDoc->end->Draw(m_pMemDC);

			pDoc->setGoal(sx,sy,ex,ey);
			pDoc->start->Draw(m_pMemDC);
			pDoc->end->Draw(m_pMemDC);
			//drawAll(m_pMemDC);
			Invalidate(false);
		}
	}


	void CLabyrinthView::OnMapRatio()
	{
		// TODO: 在此添加命令处理程序代码
		CLabyrinthDoc *pDoc = GetDocument();
		CDialogRatio newdlg;
		int result = newdlg.DoModal();
		if(result == IDOK)
		{
			int x = MAXWIDTH;
			int y = MAXHEIGHT;
			double tratio = _wtof(newdlg.m_Ratio);

			pDoc->createMap(pDoc->row,pDoc->col,tratio);
			pDoc->setGoal();

			drawAll(m_pMemDC);
			Invalidate();
		}
	}


	void CLabyrinthView::OnSearchStart()
	{
		// TODO: 在此添加命令处理程序代码
		SetTimer(1,rate,NULL);
		if(highlight != NULL)
		{
			highlight->setFlag(0);
			highlight = NULL;
		}
		issearch = true;
		ispause = false;

	}


	void CLabyrinthView::OnSearchPause()
	{
		// TODO: 在此添加命令处理程序代码
		KillTimer(1);
		ispause = true;
	}


	void CLabyrinthView::OnSearchStop()
	{
		// TODO: 在此添加命令处理程序代码
		KillTimer(1);
		postInit();
		drawAll(m_pMemDC);
		Invalidate(false);
	}


	void CLabyrinthView::OnTimer(UINT_PTR nIDEvent)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		switch(nIDEvent)
		{
		case 1:
			searchProc();
			break;
		}

		CScrollView::OnTimer(nIDEvent);
	}


	void CLabyrinthView::searchProc(void)
	{

		if(type == 0)
		{
			widthProc();
		}
		else if(type == 1)
		{
			depthProc();
		}
		else if(type == 2)
		{
			depthProc2();
		}
		else if(type == 3)
		{
			astarProc();
		}
		Invalidate(false);
	}


	void CLabyrinthView::widthProc(void)
	{
		CLabyrinthDoc *pDoc = GetDocument();
		vector<vector<CNode*>> *map = pDoc->map;
		vector<CNode*> *queue = pDoc->queue;
		CNode *startn = pDoc->start;
		CNode *endn = pDoc->end;
		int row = pDoc->row;
		int col = pDoc->col;
		int x,y,i,j;
		if(front == rear && rear == 0)
			queue->push_back(startn);
		while(front <= rear)
		{
			int incount = stepcount % 8;
			x = queue->at(front)->x;
			y = queue->at(front)->y;

			i = x + zx[incount];
			j = y + zy[incount];
			if(map->at(i).at(j)->flag == 0)
			{
				rear ++;
				map->at(i).at(j)->flag = 2;
				map->at(i).at(j)->pre = front;
				queue->push_back(map->at(i).at(j));
				map->at(i).at(j)->Draw(m_pMemDC);
				validcount++;
				break;
			}
			if(map->at(i).at(j) == endn)
			{
				rear ++;
				map->at(i).at(j)->pre = front;
				queue->push_back(map->at(i).at(j));
				validcount++;

				i = rear;
				j=0;

				while(i)
				{
					trace->push_back(queue->at(i));
					if(i != rear)
					{
						queue->at(i)->setFlag(3);
						queue->at(i)->Draw(m_pMemDC);
					}
					i = queue->at(i)->pre;
					j++;
				}
				KillTimer(1);
				Invalidate(false);
				CString str1,str2,str3;
				str3 = L"宽度优先";
				str1.Format(TEXT("%d"),validcount);
				str1 = L"搜索步数： " + str1;
				str2.Format(TEXT("%d"),j);
				str2 = L"路径步数： " + str2;
				MessageBox(str1 + L"\n" + str2,str3);
				//issearch = false;
				postInit();
				drawAll(m_pMemDC);
				break;
			}
			if(incount == 7)
			{
				if(front != 0)
				{
					queue->at(front)->setFlag(-3);
					queue->at(front)->Draw(m_pMemDC);
				}
				front ++;
			}

			stepcount ++;

		}
		if(front > rear)
		{
			KillTimer(1);
			CString str1,str2,str3;
			str3 = L"宽度优先";
			str1 = L"未找到出路！";
			str2.Format(TEXT("%d"),validcount);
			str2 = L"当前搜索步数： " + str2;
			MessageBox(str1 + L"\n" + str2,str3);
			//issearch = false;
			postInit();
			drawAll(m_pMemDC);
		}
	}


	void CLabyrinthView::depthProc(void)
	{
		CLabyrinthDoc *pDoc = GetDocument();
		vector<vector<CNode*>> *map = pDoc->map;
		vector<CNode*> *stack = pDoc->stack;
		CNode *startn = pDoc->start;
		CNode *endn = pDoc->end;
		int row = pDoc->row;
		int col = pDoc->col;
		int x,y,i,j;
		if(stack->size() == 0)
		{
			stack->push_back(startn);
			trace->push_back(startn);
		}
		while(trace->size() != 0)
		{
			int incount = stepcount % 8;
			x = trace->back()->x;
			y = trace->back()->y;

			i = x + zx[incount];
			j = y + zy[incount];
			if(map->at(i).at(j)->flag == 0)
			{
				stepcount = 0;
				map->at(i).at(j)->flag = 2;
				stack->push_back(map->at(i).at(j));
				trace->push_back(map->at(i).at(j));
				map->at(i).at(j)->Draw(m_pMemDC);
				validcount ++;
				break;
			}
			else if(map->at(i).at(j) != endn && incount == 7)
			{
				if(trace->back() != startn)
				{
					trace->back()->setFlag(-3);
					trace->back()->Draw(m_pMemDC);
				}
				stepcount = 0;
				trace->pop_back();
				break;
			}
			if(map->at(i).at(j) == endn)
			{
				stack->push_back(map->at(i).at(j));
				trace->push_back(map->at(i).at(j));
				validcount ++;

				for(unsigned int k = 0;k < trace->size();k++)
				{
					if(k != trace->size() - 1 && k != 0)
					{
						trace->at(k)->setFlag(3);
						trace->at(k)->Draw(m_pMemDC);
					}
				}
				KillTimer(1);
				Invalidate(false);
				CString str1,str2,str3;
				str3 = L"深度优先";
				str1.Format(TEXT("%d"),validcount);
				str1 = L"搜索步数： " + str1;
				str2.Format(TEXT("%d"),trace->size()- 1);
				str2 = L"路径步数： " + str2;
				MessageBox(str1 + L"\n" + str2,str3);
				//issearch = false;
				postInit();
				drawAll(m_pMemDC);
				break;
			}
			stepcount ++;
		}
		if(trace->size() == 0 && stack->size() != NULL)
		{
			KillTimer(1);
			CString str1,str2,str3;
			str3 = L"深度优先";
			str1 = L"未找到出路！";
			str2.Format(TEXT("%d"),validcount);
			str2 = L"当前搜索步数： " + str2;
			MessageBox(str1 + L"\n" + str2,str3);
			//issearch = false;
			postInit();
			drawAll(m_pMemDC);
		}
	}

	void CLabyrinthView::depthProc2(void)
	{
		CLabyrinthDoc *pDoc = GetDocument();
		vector<vector<CNode*>> *map = pDoc->map;
		vector<CNode*> *stack = pDoc->stack;
		CNode *startn = pDoc->start;
		CNode *endn = pDoc->end;
		int row = pDoc->row;
		int col = pDoc->col;
		int x,y,i,j;
		int offset = 0;
		if(stack->size() == 0)
		{
			stack->push_back(startn);
			trace->push_back(startn);
		}

		while(trace->size() != 0)
		{
			int incount = stepcount % 8;
			x = trace->back()->x;
			y = trace->back()->y;
			if(x < endn->x)
			{
				if(y < endn->y)
					offset = 0;
				else if(y > endn->y)
					offset = 7;
				else
					offset = 0;
			}
			else if(x == endn->x )
			{
				if(y < endn->y)
					offset = 2;
				else
					offset = 6;
			}
			else
			{
				if(y < endn->y)
					offset = 3;
				else if(y > endn->y)
					offset = 4;
				else
					offset = 4;
			}

			int cc = (incount + offset)%8;
			i = x + zx[cc];
			j = y + zy[cc];
			if(map->at(i).at(j)->flag == 0)
			{
				stepcount = 0;
				map->at(i).at(j)->flag = 2;
				stack->push_back(map->at(i).at(j));
				trace->push_back(map->at(i).at(j));
				map->at(i).at(j)->Draw(m_pMemDC);
				validcount ++;
				break;
			}
			else if(map->at(i).at(j) != endn && incount == 7)
			{
				if(trace->back() != startn)
				{
					trace->back()->setFlag(-3);
					trace->back()->Draw(m_pMemDC);
				}
				stepcount = 0;
				trace->pop_back();
				break;
			}
			if(map->at(i).at(j) == endn)
			{
				stack->push_back(map->at(i).at(j));
				trace->push_back(map->at(i).at(j));
				validcount ++;

				for(unsigned int k = 0;k < trace->size();k++)
				{
					if(k != trace->size() - 1 && k != 0)
					{
						trace->at(k)->setFlag(3);
						trace->at(k)->Draw(m_pMemDC);
					}
				}
				KillTimer(1);
				Invalidate(false);
				CString str1,str2,str3;
				str3 = L"改进型深度优先";
				str1.Format(TEXT("%d"),validcount);
				str1 = L"搜索步数： " + str1;
				str2.Format(TEXT("%d"),trace->size()- 1);
				str2 = L"路径步数： " + str2;
				MessageBox(str1 + L"\n" + str2,str3);
				//issearch = false;
				postInit();
				drawAll(m_pMemDC);
				break;
			}

			stepcount ++;

		}
		if(trace->size() == 0 && stack->size() != NULL)
		{
			KillTimer(1);
			CString str1,str2,str3;
			str3 = L"改进型深度优先";
			str1 = L"未找到出路！";
			str2.Format(TEXT("%d"),validcount);
			str2 = L"当前搜索步数： " + str2;
			MessageBox(str1 + L"\n" + str2,str3);
			//issearch = false;
			postInit();
			drawAll(m_pMemDC);
		}
	}

	void CLabyrinthView::astarProc(void)
	{
		CLabyrinthDoc *pDoc = GetDocument();
		vector<vector<CNode*>> *map = pDoc->map;
		priority_queue<CNode*,vector<CNode*>,Compare> *pq = pDoc->pq;

		CNode *startn = pDoc->start;
		CNode *endn = pDoc->end;
		int row = pDoc->row;
		int col = pDoc->col;
		int x,y,i,j;
		if(pDoc->close.size() == 0)
		{
			startn->setf(0,10 * max( abs(startn->x - endn->x),abs(startn->y - endn->y)));
			startn->pre = -1;
			pq->push(startn);
		}
		while(pq->size() != 0 || stepcount % 8 != 0)
		{
			int incount = stepcount % 8;
			if(incount == 0)
			{
				aptr = pq->top();
				pq->pop();
				if(aptr != startn)
				{
					aptr->flag = -3;
					aptr->Draw(m_pMemDC);
				}
				//Invalidate(false);
				pDoc->close.push_back(aptr);
			}
			x = aptr->x;
			y = aptr->y;
			i = x + zx[incount];
			j = y + zy[incount];
			if(map->at(i).at(j)->flag == 0 || map->at(i).at(j)->flag == 2)
			{
				if(map->at(i).at(j)->flag == 0)
				{
					map->at(i).at(j)->flag = 2;
					map->at(i).at(j)->pre = pDoc->close.size() - 1;
					if(incount % 2 == 1)
						map->at(i).at(j)->setf(aptr->g + 14,10 * ( abs(map->at(i).at(j)->x - endn->x)+abs(map->at(i).at(j)->y - endn->y)));
					else
						map->at(i).at(j)->setf(aptr->g + 10,10 * ( abs(map->at(i).at(j)->x - endn->x)+abs(map->at(i).at(j)->y - endn->y)));
					pq->push(map->at(i).at(j));
					map->at(i).at(j)->Draw(m_pMemDC);
					validcount ++;
					stepcount ++;
					break;
				}
				else if((incount % 2 == 0 && map->at(i).at(j)->g > aptr->g + 10) || (incount % 2 == 1 && map->at(i).at(j)->g > aptr->g + 14))
				{

					vector<CNode *>nodeptr;
					while(pq->top() != map->at(i).at(j))
					{
						nodeptr.push_back(pq->top());
						pq->pop();
					}
					nodeptr.push_back(pq->top());
					pq->pop();

					if(incount % 2 == 1)
						map->at(i).at(j)->setf(aptr->g + 14,10 * ( abs(map->at(i).at(j)->x - endn->x)+abs(map->at(i).at(j)->y - endn->y)));
					else
						map->at(i).at(j)->setf(aptr->g + 10,10 * ( abs(map->at(i).at(j)->x - endn->x)+abs(map->at(i).at(j)->y - endn->y)));
					map->at(i).at(j)->pre = pDoc->close.size() - 1;
					for(unsigned int k = 0;k < nodeptr.size();k++)
					{
						pq->push(nodeptr.at(k));
					}
					nodeptr.clear();
					/*CNode newnode = *map->at(i).at(j);
					newnode.setf(nptr->g + 1,max( abs(map->at(i).at(j)->x - endn->x),abs(map->at(i).at(j)->y - endn->y)));
					newnode.pre = pDoc->close.size() - 1;
					pq->push(&newnode);*/
				}
			}
			else if(map->at(i).at(j) == endn)
			{
				if(incount % 2 == 1)
					endn->setf(aptr->g + 14,0);
				else
					endn->setf(aptr->g + 10,0);
				endn->pre = pDoc->close.size() - 1;
				pDoc->close.push_back(endn);
				validcount ++;
				aptr = endn;
				j = 1;
				while(aptr->pre > 0)
				{
					aptr = pDoc->close.at(aptr->pre);
					aptr->setFlag(3);
					aptr->Draw(m_pMemDC);
					j++;	
				}
				KillTimer(1);
				Invalidate(false);
				CString str1,str2,str3;
				str3 = L"A*算法";
				str1.Format(TEXT("%d"),validcount);
				str1 = L"搜索步数： " + str1;
				str2.Format(TEXT("%d"),j);
				str2 = L"路径步数： " + str2;
				MessageBox(str1 + L"\n" + str2,str3);
				//issearch = false;
				postInit();
				drawAll(m_pMemDC);

				aptr = NULL;
				break;
			}
			stepcount ++;
		}
		if(stepcount % 8 == 0 && stepcount != 0 && pq->size() == 0 && pDoc->close.size() != 0)
		{
			KillTimer(1);
			CString str1,str2,str3;
			str3 = L"A*搜索";
			str1 = L"未找到出路！";
			str2.Format(TEXT("%d"),validcount);
			str2 = L"当前搜索步数： " + str2;
			MessageBox(str1 + L"\n" + str2,str3);
			//issearch = false;
			postInit();
			drawAll(m_pMemDC);
		}
	}

	void CLabyrinthView::OnSearchAnalysis()
	{
		// TODO: 在此添加命令处理程序代码
		int lroute = searchStat1();

		CString str1,str2,str3,str4,str5,str6,str7;
		if(lroute == -1)
		{
			str2 = L"搜索结果";
			str1 = L"未找到出路";
			MessageBox(str1,str2);
		}
		else
		{
			str5 = L"搜索结果";
			str1.Format(TEXT("%d"),lroute);
			str2.Format(TEXT("%d"),validcount);
			postInit();
			lroute = searchStat2();

			str3.Format(TEXT("%d"),lroute);
			str4.Format(TEXT("%d"),validcount);
			postInit();
			lroute = searchStat3();

			str6.Format(TEXT("%d"),lroute);
			str7.Format(TEXT("%d"),validcount);
			MessageBox(L"宽度优先路径步数: " +  str1 + L"\n宽度优先搜索总数："+ str2 + L"\n深度优先路径步数：" + str3+ L"\n深度优先搜索总数：" + str4 + L"\nA*路径步数：" + str6+ L"\nA*搜索总数：" + str7,str5);
		}
		postInit();

	}

	int CLabyrinthView::searchStat1(void)
	{
		CLabyrinthDoc *pDoc = GetDocument();
		vector<vector<CNode*>> *map = pDoc->map;
		vector<CNode*> *queue = pDoc->queue;
		CNode *startn = pDoc->start;
		CNode *endn = pDoc->end;
		int row = pDoc->row;
		int col = pDoc->col;
		int x,y,i,j,v;
		if(highlight != NULL)
		{
			highlight->setFlag(0);
			highlight = NULL;
		}
		queue->push_back(startn);
		while(front <= rear)
		{
			x = queue->at(front)->x;
			y = queue->at(front)->y;
			for(v = 0;v < 8;v++)
			{
				i = x + zx[v];
				j = y + zy[v];
				if(map->at(i).at(j)->flag == 0) //|| map->at(i).at(j)->flag == -2)
				{
					rear ++;
					map->at(i).at(j)->flag = -3;
					map->at(i).at(j)->pre = front;
					queue->push_back(map->at(i).at(j));
					validcount ++;
				}
				if(map->at(i).at(j) == endn)
				{
					rear ++;
					map->at(i).at(j)->pre = front;
					queue->push_back(map->at(i).at(j));
					validcount ++;

					i = rear;
					j=0;

					while(i)
					{
						trace->push_back(queue->at(i));
						i = queue->at(i)->pre;
						j++;
					}
					return j;
				}
			}
			front ++;
		}
		return -1;
	}


	int CLabyrinthView::searchStat2(void)
	{
		CLabyrinthDoc *pDoc = GetDocument();
		vector<vector<CNode*>> *map = pDoc->map;
		vector<CNode*> *stack = pDoc->stack;
		CNode *startn = pDoc->start;
		CNode *endn = pDoc->end;
		int row = pDoc->row;
		int col = pDoc->col;
		int x,y,i,j,v;
		if(GetDocument()->stack->size() == 0)
		{
			if(highlight != NULL)
			{
				highlight->setFlag(0);
				highlight = NULL;
			}
			stack->push_back(startn);
			trace->push_back(startn);
		}
		x = trace->back()->x;
		y = trace->back()->y;
		for(v = 0;v < 8;v++)
		{
			i = x + zx[v];
			j = y + zy[v];
			if(map->at(i).at(j)->flag == 0)
			{
				map->at(i).at(j)->flag = -3;
				stack->push_back(map->at(i).at(j));
				trace->push_back(map->at(i).at(j));
				validcount ++;
				int re = searchStat2();	
				if(re != -1)
					return re;
			}
			if(map->at(i).at(j) != endn && v == 7)
			{
				trace->pop_back();
				return -1;
			}
			if(map->at(i).at(j) == endn)
			{
				stack->push_back(map->at(i).at(j));
				trace->push_back(map->at(i).at(j));
				validcount ++;
				return (trace->size() - 1);
			}
		}
		return -1;
	}


	int CLabyrinthView::searchStat3(void)
	{
		CLabyrinthDoc *pDoc = GetDocument();
		vector<vector<CNode*>> *map = pDoc->map;
		priority_queue<CNode*,vector<CNode*>,Compare> *pq = pDoc->pq;

		CNode *startn = pDoc->start;
		CNode *endn = pDoc->end;
		CNode *nptr = NULL;
		int row = pDoc->row;
		int col = pDoc->col;
		int x,y,i,j,v;
		if(highlight != NULL)
		{
			highlight->setFlag(0);
			highlight = NULL;
		}

		startn->setf(0,10 * max( abs(startn->x - endn->x),abs(startn->y - endn->y)));
		startn->pre = -1;
		pq->push(startn);
		while(pq->size() != 0)
		{
			nptr = pq->top();
			pq->pop();
			if(nptr != startn)
			{
				nptr->flag = -3;
			}
			pDoc->close.push_back(nptr);
			x = nptr->x;
			y = nptr->y;
			for(v = 0;v < 8;v++)
			{
				i = x + zx[v];
				j = y + zy[v];
				if(map->at(i).at(j)->flag == 0 || map->at(i).at(j)->flag == 2)
				{
					if(map->at(i).at(j)->flag == 0)
					{
						map->at(i).at(j)->flag = 2;
						map->at(i).at(j)->pre = pDoc->close.size() - 1;
						if(v % 2 == 1)
							map->at(i).at(j)->setf(nptr->g + 14,10 * ( abs(map->at(i).at(j)->x - endn->x)+abs(map->at(i).at(j)->y - endn->y)));
						else
							map->at(i).at(j)->setf(nptr->g + 10,10 * ( abs(map->at(i).at(j)->x - endn->x)+abs(map->at(i).at(j)->y - endn->y)));
						pq->push(map->at(i).at(j));
						validcount ++;
					}
					else if((v % 2 == 0 && map->at(i).at(j)->g > nptr->g + 10) || (v % 2 == 1 && map->at(i).at(j)->g > nptr->g + 14))
					{

						vector<CNode *>nodeptr;
						while(pq->top() != map->at(i).at(j))
						{
							nodeptr.push_back(pq->top());
							pq->pop();
						}
						nodeptr.push_back(pq->top());
						pq->pop();

						if(v % 2 == 1)
							map->at(i).at(j)->setf(nptr->g + 14,10 * ( abs(map->at(i).at(j)->x - endn->x)+abs(map->at(i).at(j)->y - endn->y)));
						else
							map->at(i).at(j)->setf(nptr->g + 10,10 * ( abs(map->at(i).at(j)->x - endn->x)+abs(map->at(i).at(j)->y - endn->y)));
						map->at(i).at(j)->pre = pDoc->close.size() - 1;
						for(unsigned int k = 0;k < nodeptr.size();k++)
						{
							pq->push(nodeptr.at(k));
						}
						nodeptr.clear();
						/*CNode newnode = *map->at(i).at(j);
						newnode.setf(nptr->g + 1,max( abs(map->at(i).at(j)->x - endn->x),abs(map->at(i).at(j)->y - endn->y)));
						newnode.pre = pDoc->close.size() - 1;
						pq->push(&newnode);*/
					}
				}
				else if(map->at(i).at(j) == endn)//if
				{
					if(v % 2 == 1)
						endn->setf(nptr->g + 14,0);
					else
						endn->setf(nptr->g + 10,0);
					endn->pre = pDoc->close.size() - 1;
					pDoc->close.push_back(endn);
					validcount ++;
					nptr = endn;
					j = 1;
					while(nptr->pre > 0)
					{
						nptr = pDoc->close.at(nptr->pre);
						nptr->setFlag(3);
						j++;
					}
					return j;
				}
			}
		}
		return -1;
	}


	void CLabyrinthView::postInit(void)
	{
		CLabyrinthDoc *pDoc = GetDocument();
		vector<vector<CNode*>> *map = pDoc->map;
		front = 0;
		rear = 0;
		stepcount = 0;
		validcount = 0;

		if((pDoc->pq->size() == 0 && issearch == false && pDoc->close.size() == 0)|| (type != 3 && issearch == true))
		{
			issearch = false;
			ispause = false;
			vector<CNode*> *container = pDoc->queue;
			if(pDoc->queue->size() == 0)
				container = pDoc->stack;
			unsigned int length = container->size();

			container->at(0)->setFlag(-1);

			for(unsigned int i = 1;i < length;i++)
			{
				if(container->at(i) != pDoc->end)
					container->at(i)->setFlag(0);
			}
			container->clear();
			trace->clear();
		}
		else
		{
			issearch = false;
			ispause = false;
			unsigned int temp = pDoc->pq->size();
			for(unsigned int i = 0;i < temp;i++)
			{
				pDoc->pq->top()->setf(0,0);
				pDoc->pq->top()->pre = 0;
				pDoc->pq->top()->setFlag(0);
				pDoc->pq->pop();
			}
			pDoc->close.at(0)->setf(0,0);
			pDoc->close.at(0)->pre = 0;;

			for(unsigned int j = 1;j < pDoc->close.size();j++)
			{
				pDoc->close.at(j)->setf(0,0);
				pDoc->close.at(j)->pre = 0;
				if(pDoc->close.at(j)->flag != -2)
					pDoc->close.at(j)->setFlag(0);
			}
			pDoc->close.clear();
		}
	}


	void CLabyrinthView::OnRateDown()
	{
		// TODO: 在此添加命令处理程序代码
		if(rate < 1000)
		{
			rate += 200;
			SetTimer(1,rate,NULL);
		}
	}


	void CLabyrinthView::OnRateUp()
	{
		// TODO: 在此添加命令处理程序代码
		if(rate > 50)
		{
			rate -= 100;
			SetTimer(1,rate,NULL);
		}
	}


	void CLabyrinthView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		point += this->GetScrollPosition();
		CLabyrinthDoc *pDoc = GetDocument();
		vector<vector<CNode *>> *map = pDoc->map;
		if(map != NULL)
		{
			CNode * startn = pDoc->start;
			CNode * endn = pDoc->end;
			int curx = int(point.x / FrmWidth);
			int cury = int(point.y / FrmHeight);
			if(curx <= pDoc->col && cury <= pDoc->row && map->at(curx).at(cury)->getFlag() != 4)
			{
				if(issearch == false && map->at(curx).at(cury)->getFlag() == 0)
				{
					if(highlight != NULL && highlight != map->at(curx).at(cury))
					{
						highlight->setFlag(0);
						highlight->Draw(m_pMemDC);
					}
					if(highlight != map->at(curx).at(cury))
					{
						highlight = map->at(curx).at(cury);
						highlight->setFlag(4);
						highlight->Draw(m_pMemDC);
						Invalidate(false);
					}
					if(block != NULL)
						block = NULL;

				}
				else if(issearch == false && map->at(curx).at(cury)->getFlag() != 0)
				{
					if(highlight !=NULL)
					{
						highlight->setFlag(0);
						highlight->Draw(m_pMemDC);
						Invalidate(false);
						highlight = NULL;
					}
					if(block != map->at(curx).at(cury) && curx > 0 && cury > 0 && curx <= pDoc->col && cury <= pDoc->row && map->at(curx).at(cury)->getFlag() == 1)
					{
						block = map->at(curx).at(cury);
					}
				}
			}
		}
		CScrollView::OnMouseMove(nFlags, point);
	}


	void CLabyrinthView::OnStartSet()
	{
		// TODO: 在此添加命令处理程序代码
		if(highlight != NULL)
		{
			CLabyrinthDoc *pDoc = GetDocument();
			CNode *startn = pDoc->start;
			startn->setFlag(0);
			startn->Draw(m_pMemDC);
			pDoc->start = highlight;
			startn = pDoc->start;
			startn->setFlag(-1);
			startn->Draw(m_pMemDC);
			Invalidate(false);
			highlight = NULL;
		}
	}


	void CLabyrinthView::OnEndSet()
	{
		// TODO: 在此添加命令处理程序代码
		if(highlight != NULL)
		{
			CLabyrinthDoc *pDoc = GetDocument();
			CNode *endn = pDoc->end;
			endn->setFlag(0);
			endn->Draw(m_pMemDC);
			pDoc->end = highlight;
			endn = pDoc->end;
			endn->setFlag(-2);
			endn->Draw(m_pMemDC);
			Invalidate(false);
			highlight = NULL;
		}
	}

	void CLabyrinthView::OnFlagChange()
	{
		// TODO: 在此添加命令处理程序代码
		CLabyrinthDoc *pDoc = GetDocument();
		if(highlight != NULL)
		{
			highlight->setFlag(1);
			highlight->Draw(m_pMemDC);
			highlight = NULL;
		}
		else if(block != NULL)
		{
			block->setFlag(0);
			block->Draw(m_pMemDC);
		}
		Invalidate(false);
	}



	void CLabyrinthView::OnUpdateStartSet(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(highlight == NULL)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateEndSet(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(highlight == NULL)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateFlagChange(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(highlight == NULL && block == NULL)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateMapResize(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->map == NULL || issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateMapEntry(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->map == NULL || issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateMapRatio(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->map == NULL || issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateSearchStart(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->map == NULL || (ispause == false && issearch == true))
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateSearchPause(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->map == NULL || ispause == true || issearch == false)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateSearchAnalysis(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->map == NULL || issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateRateDown(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->map == NULL || issearch == false || ispause == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateRateUp(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->map == NULL || issearch == false || ispause == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateWidthPrior(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateDepthPrior(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateDepthPrior2(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateAstarSearch(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateSearchStop(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->map == NULL || issearch == false)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateMapRefresh(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->map == NULL || issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateMapNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateMapRand(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateMapDefault(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateMapInput(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateFileOpen(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(issearch == true)
			pCmdUI->Enable(false);
	}


	void CLabyrinthView::OnUpdateFileNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(issearch == true)
			pCmdUI->Enable(false);
	}


	//	vector<CNode *> * CLabyrinthView::dfSearch(vector<vector<CNode*>> *map,vector<CNode*> *stack)
	//	{
	//
	//		return NULL;
	//	}


	void CLabyrinthView::OnMapDefault()
	{
		// TODO: 在此添加命令处理程序代码
		CLabyrinthDoc *pDoc = GetDocument();
		CRect rc;
		GetWindowRect(rc);
		pDoc->createModel();
		int x = MAXWIDTH;
		int y = MAXHEIGHT;
		FrmHeight  = double(rc.Height()) / (pDoc->row + 2);
		FrmWidth = double(rc.Width()) / (pDoc->col + 2);
		CDC* pDC=GetDC();
		if(m_pMemDC != NULL)
			m_pMemDC->DeleteDC();
		if(m_pBitmap != NULL)
			m_pBitmap->DeleteObject();
		m_pMemDC->CreateCompatibleDC(pDC);
		m_pBitmap->CreateCompatibleBitmap(pDC,x,y);
		m_pMemDC->SelectObject(m_pBitmap);

		drawAll(m_pMemDC);
		Invalidate();
	}

	void CLabyrinthView::loadRefresh(void)
	{
		CLabyrinthDoc *pDoc = GetDocument();
		CRect rc;
		GetWindowRect(rc);
		int x = MAXWIDTH;
		int y = MAXHEIGHT;
		FrmHeight  = double(rc.Height()) / (pDoc->row + 2);
		FrmWidth = double(rc.Width()) / (pDoc->col + 2);
		CDC* pDC=GetDC();
		if(m_pMemDC != NULL)
			m_pMemDC->DeleteDC();
		if(m_pBitmap != NULL)
			m_pBitmap->DeleteObject();
		m_pMemDC->CreateCompatibleDC(pDC);
		m_pBitmap->CreateCompatibleBitmap(pDC,x,y);
		m_pMemDC->SelectObject(m_pBitmap);

		drawAll(m_pMemDC);
		Invalidate();
	}


	void CLabyrinthView::OnMapInput()
	{
		// TODO: 在此添加命令处理程序代码
		OnFileOpen();
	}


	void CLabyrinthView::OnFileOpen()
	{
		// TODO: 在此添加命令处理程序代码
		LPCTSTR filters = L"迷宫文件(*.maze)|*.maze|全部文件(*.*)|*.*||";
		CFileDialog filedlg(true,L"*.maze",NULL,NULL,filters);
		int result = filedlg.DoModal();
		CString filename;
		if(result == IDOK)
		{
			filename = filedlg.GetPathName();
			GetDocument()->loadFile(filename);
		}
	}


	void CLabyrinthView::OnFileSave()
	{
		// TODO: 在此添加命令处理程序代码
		if(GetDocument()->map != NULL)
		{
			LPCTSTR filters = L"迷宫文件(*.maze)|*.maze|全部文件(*.*)|*.*||";
			CFileDialog filedlg(false,L"*.maze",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filters);
			int result = filedlg.DoModal();
			CString filename;
			if(result == IDOK)
			{
				filename = filedlg.GetPathName();
				GetDocument()->saveFile(filename);
			}
		}
	}


	void CLabyrinthView::OnFileNew()
	{
		// TODO: 在此添加命令处理程序代码
		OnMapDefault();
	}
