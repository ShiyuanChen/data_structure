
// Orthogonal_ListView.cpp : COrthogonal_ListView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Orthogonal_List.h"
#endif

#include "Orthogonal_ListDoc.h"
#include "Orthogonal_ListView.h"
#include "DialogNew.h"
#include "DialogInsert.h"
#include "DialogDelete.h"
#include "DialogSearchIn.h"
#include "DialogSearchKey.h"
#include "DialogRes.h"
#include "DialogChange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COrthogonal_ListView

IMPLEMENT_DYNCREATE(COrthogonal_ListView, CScrollView)

	BEGIN_MESSAGE_MAP(COrthogonal_ListView, CScrollView)
		ON_COMMAND(ID_NODE_INSERT, &COrthogonal_ListView::OnNodeInsert)
		ON_COMMAND(ID_NODE_DELETE, &COrthogonal_ListView::OnNodeDelete)
		ON_COMMAND(ID_SEARCH_INDEX, &COrthogonal_ListView::OnSearchIndex)
		ON_COMMAND(ID_SEARCH_KEY, &COrthogonal_ListView::OnSearchKey)
		ON_COMMAND(ID_FILE_NEW, &COrthogonal_ListView::OnFileNew)
		ON_UPDATE_COMMAND_UI(ID_NODE_INSERT, &COrthogonal_ListView::OnUpdateNodeInsert)
		ON_UPDATE_COMMAND_UI(ID_NODE_DELETE, &COrthogonal_ListView::OnUpdateNodeDelete)
		ON_UPDATE_COMMAND_UI(ID_SEARCH_INDEX, &COrthogonal_ListView::OnUpdateSearchIndex)
		ON_UPDATE_COMMAND_UI(ID_SEARCH_KEY, &COrthogonal_ListView::OnUpdateSearchKey)
		ON_COMMAND(ID_NODE_SUM, &COrthogonal_ListView::OnNodeSum)
		ON_UPDATE_COMMAND_UI(ID_NODE_SUM, &COrthogonal_ListView::OnUpdateNodeSum)
		ON_WM_VSCROLL()
		ON_WM_HSCROLL()
		//		ON_WM_CREATE()
		ON_WM_CREATE()
		ON_WM_TIMER()
		ON_WM_MOUSEMOVE()
		//		ON_WM_RBUTTONUP()
		ON_WM_CONTEXTMENU()
		ON_COMMAND(ID_POPUP_INSERT, &COrthogonal_ListView::OnPopupInsert)
		ON_COMMAND(ID_POPUP_DELETE, &COrthogonal_ListView::OnPopupDelete)
		ON_COMMAND(ID_POPUP_CHANGE, &COrthogonal_ListView::OnPopupChange)
		ON_UPDATE_COMMAND_UI(ID_POPUP_INSERT, &COrthogonal_ListView::OnUpdatePopupInsert)
	END_MESSAGE_MAP()

	// COrthogonal_ListView 构造/析构

	COrthogonal_ListView::COrthogonal_ListView()
		: m_ImgVScrollPos(0)
		, m_ImgHScrollPos(0)
		, HRange(0)
		, VRange(0)
		, m_pMemDC(NULL)
		, m_pBitmap(NULL)
		, delay_flag(0)
		, highlight(NULL)
		, insertMode(false)
	{
		// TODO: 在此处添加构造代码
		searchArray = NULL;
		m_pMemDC = new CDC();
		m_pBitmap = new CBitmap();
		m_outNewRow = _T("");
		m_outNewCol = _T("");
		m_outNewData = _T("");
	}

	COrthogonal_ListView::~COrthogonal_ListView()
	{
		delete m_pMemDC;
		delete m_pBitmap;
	}

	BOOL COrthogonal_ListView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CScrollView::PreCreateWindow(cs);
	}

	// COrthogonal_ListView 绘制

	void COrthogonal_ListView::OnDraw(CDC* pDC)
	{
		COrthogonal_ListDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 在此处为本机数据添加绘制代码 
		CRect rc;
		GetClientRect(rc);


		VRange = pDoc->ClObj->assist.at(pDoc->ClObj->getRow() - 1)->Vhead->drawunit->get_Y() + pDoc->ClObj->InitHead->Height * 2;
		HRange = pDoc->ClObj->assist.at(pDoc->ClObj->getCol() - 1)->Hhead->drawunit->get_X() + pDoc->ClObj->InitHead->Width * 2;
		
		pDC->BitBlt(rc.left,rc.top,HRange,VRange,m_pMemDC,(rc.left+m_ImgHScrollPos),(rc.top+m_ImgVScrollPos),SRCCOPY);
		CSize sizeTotal(HRange,VRange);
		SetScrollSizes(MM_TEXT,sizeTotal);
	}

	void COrthogonal_ListView::OnInitialUpdate()
	{
		CScrollView::OnInitialUpdate();

		CSize sizeTotal;
		// TODO: 计算此视图的合计大小
		sizeTotal.cx = sizeTotal.cy = 100;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}


	// COrthogonal_ListView 诊断

#ifdef _DEBUG
	void COrthogonal_ListView::AssertValid() const
	{
		CScrollView::AssertValid();
	}

	void COrthogonal_ListView::Dump(CDumpContext& dc) const
	{
		CScrollView::Dump(dc);
	}

	COrthogonal_ListDoc* COrthogonal_ListView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COrthogonal_ListDoc)));
		return (COrthogonal_ListDoc*)m_pDocument;
	}
#endif //_DEBUG


	// COrthogonal_ListView 消息处理程序


	void COrthogonal_ListView::OnNodeInsert()
	{
		// TODO: 在此添加命令处理程序代码
		CDialogInsert insertdlg;
		if(insertMode == true)
		{
			insertdlg.m_Row = m_outNewRow;
			insertdlg.m_Col = m_outNewCol;
		}

		int result = insertdlg.DoModal();
		if(result == IDOK)
		{
			m_outNewRow = insertdlg.m_Row;
			m_outNewCol = insertdlg.m_Col;
			m_outNewData = insertdlg.m_Data;
			COrthogonal_ListDoc *pDoc = GetDocument();
			Node * nodeptr = pDoc->ClObj->insertNode(_ttoi(m_outNewRow),_ttoi(m_outNewCol),m_outNewData);
			if(nodeptr == NULL)
			{
				CString str1("插入失败！");
				CString str2("提示");
				MessageBox(str1,str2);
			}
			else
			{
				VRange = pDoc->ClObj->assist.at(pDoc->ClObj->getRow() - 1)->Vhead->drawunit->get_Y() + pDoc->ClObj->InitHead->Height * 2;
				HRange = pDoc->ClObj->assist.at(pDoc->ClObj->getCol() - 1)->Hhead->drawunit->get_X() + pDoc->ClObj->InitHead->Width * 2;
				if(pDoc->ClObj->assist.at(_ttoi(m_outNewRow)-1)->Vhead->right->right == pDoc->ClObj->assist.at(_ttoi(m_outNewRow)-1)->Vhead)
					VRange = pDoc->ClObj->assist.at(pDoc->ClObj->getRow() - 1)->Vhead->drawunit->get_Y() + pDoc->ClObj->InitHead->Height * 4;
				if(pDoc->ClObj->assist.at(_ttoi(m_outNewCol)-1)->Hhead->down->down == pDoc->ClObj->assist.at(_ttoi(m_outNewCol)-1)->Hhead)
					HRange = pDoc->ClObj->assist.at(pDoc->ClObj->getCol() - 1)->Hhead->drawunit->get_X() + pDoc->ClObj->InitHead->Width * 4;
				CDC* pDC=GetDC();
				if(m_pMemDC != NULL)
					m_pMemDC->DeleteDC();
				if(m_pBitmap != NULL)
					m_pBitmap->DeleteObject();
				m_pMemDC->CreateCompatibleDC(pDC);
				m_pBitmap->CreateCompatibleBitmap(pDC,HRange,VRange);
				m_pMemDC->SelectObject(m_pBitmap);
				//ReleaseDC(pDC); 
				CBrush brush;
				brush.CreateStockObject(WHITE_BRUSH);
				CBrush* poldbrush=m_pMemDC->SelectObject(&brush); 
				m_pMemDC->PatBlt(0,0,HRange,VRange,PATCOPY);
				m_pMemDC->SelectObject(poldbrush);
				drawList(pDoc->ClObj,m_pMemDC);
				Invalidate();
				searchArray = pDoc->ClObj->searchNode(_ttoi(m_outNewRow),_ttoi(m_outNewCol));
				delay_flag = 0;
				SetTimer(1, 500, NULL);

				SetScrollPos(SB_HORZ,0);
				SetScrollPos(SB_VERT,0);
			}
		}
	}


	void COrthogonal_ListView::OnNodeDelete()
	{
		// TODO: 在此添加命令处理程序代码
		CDialogDelete deletedlg;
		int result = deletedlg.DoModal();
		if(result == IDOK)
		{
			m_outNewRow = deletedlg.m_Row;
			m_outNewCol = deletedlg.m_Col;
			COrthogonal_ListDoc *pDoc = GetDocument();
			vector<Node*> * nodeptr = pDoc->ClObj->searchNode(_ttoi(m_outNewRow),_ttoi(m_outNewCol));
			if(nodeptr == NULL)////////////////////////////////////////////
			{
				CString str1("删除失败！");
				CString str2("提示");
				MessageBox(str1,str2);
			}
			else
			{
				searchArray = nodeptr;
				delay_flag = 0;
				SetTimer(3, 500, NULL);
				SetScrollPos(SB_HORZ,0);
				SetScrollPos(SB_VERT,0);
			}
		}
	}


	void COrthogonal_ListView::OnSearchIndex()
	{
		// TODO: 在此添加命令处理程序代码
		CDialogSearchIn indexdlg;
		int result = indexdlg.DoModal();
		if(result == IDOK)
		{
			m_outNewRow = indexdlg.m_Row;
			m_outNewCol = indexdlg.m_Col;
			COrthogonal_ListDoc *pDoc = GetDocument();
			vector<Node*> * nodeptr = pDoc->ClObj->searchNode(_ttoi(m_outNewRow),_ttoi(m_outNewCol));
			if(nodeptr == NULL)
			{
				CString str1("未找到该节点！");
				CString str2("提示");
				MessageBox(str1,str2);
			}
			else
			{
				searchArray = nodeptr;
				delay_flag = 0;
				SetTimer(2, 500, NULL);
				SetScrollPos(SB_HORZ,0);
				SetScrollPos(SB_VERT,0);
			}
		}
	}


	void COrthogonal_ListView::OnSearchKey()
	{
		// TODO: 在此添加命令处理程序代码
		CDialogSearchKey keydlg;
		int result = keydlg.DoModal();
		if(result == IDOK)
		{
			m_outNewData = keydlg.m_Data;
			COrthogonal_ListDoc *pDoc = GetDocument();
			vector<vector<Node*>*> * nodeptr = pDoc->ClObj->searchNode(m_outNewData);
			if(nodeptr == NULL)
			{
				CString str1("未找到该节点！");
				CString str2("提示");
				MessageBox(str1,str2);
			}
			else
			{
				CString str4("节点行列数:\n");
				CString str5("检索结果");
				for(unsigned int j = 0;j < nodeptr->size();j++)
				{
					for(unsigned int i = 0;i < nodeptr->at(j)->size() - 1;i ++)
					{
						nodeptr->at(j)->at(i)->drawunit->set_Flag();
						nodeptr->at(j)->at(i)->drawunit->unit_Draw(nodeptr->at(j)->at(i)->drawunit->get_Rowpos(),nodeptr->at(j)->at(i)->drawunit->get_Colpos(),m_pMemDC);
					}
				}
				for(unsigned int j = 0;j < nodeptr->size();j++)
				{
					nodeptr->at(j)->at(nodeptr->at(j)->size() - 1)->drawunit->check_Flag();
					nodeptr->at(j)->at(nodeptr->at(j)->size() - 1)->drawunit->unit_Draw(nodeptr->at(j)->at(nodeptr->at(j)->size() - 1)->drawunit->get_Rowpos(),nodeptr->at(j)->at(nodeptr->at(j)->size() - 1)->drawunit->get_Colpos(),m_pMemDC);
				}
				pDoc->ClObj->InitHead->set_Flag();
				pDoc->ClObj->InitHead->unit_Draw(0,0,m_pMemDC);
				CRect rc;
				GetWindowRect(&rc);
				if(rc.Width() < HRange)
				{
					int hpos = nodeptr->at(0)->at(nodeptr->at(0)->size() - 1)->drawunit->get_X() + pDoc->ClObj->InitHead->Width - rc.Width() / 2;
					if(hpos < 0)
						hpos = 0;
					else if(hpos >HRange - rc.Width() / 2)
						hpos = HRange - rc.Width() / 2;
					SetScrollPos(SB_HORZ,hpos);
				}
				if(rc.Height() < VRange)
				{
					int vpos = nodeptr->at(0)->at(nodeptr->at(0)->size() - 1)->drawunit->get_Y() + pDoc->ClObj->InitHead->Height - rc.Height() / 2;
					if(vpos < 0)
						vpos = 0;
					else if(vpos >VRange - rc.Height() / 2)
						vpos = VRange - rc.Height() / 2;
					SetScrollPos(SB_VERT,vpos);
				}
				Invalidate(false);
				CString str1,str2,str3;
				for(unsigned int j = 0;j < nodeptr->size();j++)
				{
					str2.Format(TEXT("%d"),nodeptr->at(j)->at(nodeptr->at(j)->size()-1)->row);
					str3.Format(TEXT("%d"),nodeptr->at(j)->at(nodeptr->at(j)->size()-1)->col);
					str1 += ('(' + str2  + ' ' + ',' + ' ' + str3 + ')' + '\n');
				}
				MessageBox(str4 + str1,str5);
				for(unsigned int j = 0;j < nodeptr->size();j++)
				{
					for(unsigned int i = 0;i < nodeptr->at(j)->size();i ++)
					{
						nodeptr->at(j)->at(i)->drawunit->unset_Flag();
						nodeptr->at(j)->at(i)->drawunit->unit_Draw(nodeptr->at(j)->at(i)->drawunit->get_Rowpos(),nodeptr->at(j)->at(i)->drawunit->get_Colpos(),m_pMemDC);
					}
				}
				pDoc->ClObj->InitHead->unset_Flag();
				pDoc->ClObj->InitHead->unit_Draw(0,0,m_pMemDC);
				Invalidate();
			}
		}
	}


	void COrthogonal_ListView::OnFileNew()
	{
		// TODO: 在此添加命令处理程序代码
		CDialogNew newdlg;
		int result = newdlg.DoModal();
		if(result == IDOK)
		{
			m_outNewRow = newdlg.m_Row;
			m_outNewCol = newdlg.m_Col;	
			COrthogonal_ListDoc *pDoc = GetDocument();
			pDoc->NewCrossList(_ttoi(m_outNewRow),_ttoi(m_outNewCol));
			CSize sizeTotal(0,0);
			SetScrollSizes(MM_TEXT,sizeTotal);

			VRange = pDoc->ClObj->assist.at(pDoc->ClObj->getRow() - 1)->Vhead->drawunit->get_Y() + pDoc->ClObj->InitHead->Height * 2;
			HRange = pDoc->ClObj->assist.at(pDoc->ClObj->getCol() - 1)->Hhead->drawunit->get_X() + pDoc->ClObj->InitHead->Width * 2;
			CDC* pDC=GetDC();
			if(m_pMemDC != NULL)
				m_pMemDC->DeleteDC();
			if(m_pBitmap != NULL)
				m_pBitmap->DeleteObject();
			m_pMemDC->CreateCompatibleDC(pDC);
			m_pBitmap->CreateCompatibleBitmap(pDC,HRange,VRange);
			m_pMemDC->SelectObject(m_pBitmap);
			CBrush brush;
			brush.CreateStockObject(WHITE_BRUSH);
			CBrush* poldbrush=m_pMemDC->SelectObject(&brush); 
			m_pMemDC->PatBlt(0,0,HRange,VRange,PATCOPY);
			m_pMemDC->SelectObject(poldbrush);
			drawList(pDoc->ClObj,m_pMemDC);
			Invalidate();
		}
	}

	void COrthogonal_ListView::OnNodeSum()
	{
		// TODO: 在此添加命令处理程序代码
		CDialogRes resdlg(GetDocument());
		int result = resdlg.DoModal();
		if(result == IDOK)
		{
			Invalidate();
		}
	}


	void COrthogonal_ListView::OnUpdateNodeInsert(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->ClObj == NULL)
			pCmdUI->Enable(false);
	}


	void COrthogonal_ListView::OnUpdateNodeDelete(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->ClObj == NULL)
			pCmdUI->Enable(false);
	}


	void COrthogonal_ListView::OnUpdateSearchIndex(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->ClObj == NULL)
			pCmdUI->Enable(false);
	}


	void COrthogonal_ListView::OnUpdateSearchKey(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->ClObj == NULL)
			pCmdUI->Enable(false);
	}

	void COrthogonal_ListView::OnUpdateNodeSum(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->ClObj == NULL)
			pCmdUI->Enable(false);
	}

	void COrthogonal_ListView::drawList(CCrossList * crosslist, CDC * pDC)
	{
		int iter1 = 1;
		int iter2 = 1;
		vector<VecNode *> vecptr = crosslist->assist;
		for(int i = 0;i < crosslist->getRow();i++)
		{		
			if(vecptr.at(i)->Vhead != NULL && vecptr.at(i)->Vhead->right != vecptr.at(i)->Vhead)
			{
				vecptr.at(i)->Vhead->drawunit->unit_Draw(iter2,0,pDC);
				vecptr.at(i)->Vhead->rowpos = iter2;
				iter2++;
			}
		}
		for(int i = 0;i < crosslist->getCol();i++)
		{		
			if(vecptr.at(i)->Hhead != NULL && vecptr.at(i)->Hhead->down != vecptr.at(i)->Hhead)
			{
				vecptr.at(i)->Hhead->drawunit->unit_Draw(0,iter1,pDC);
				Node*ptr = vecptr.at(i)->Hhead->down;
				while(ptr != vecptr.at(i)->Hhead)
				{
					ptr->drawunit->unit_Draw(vecptr.at(ptr->row - 1)->Vhead->rowpos,iter1,pDC);
					ptr = ptr->down;
				}
				iter1++;
			}	
		}
		crosslist->InitHead->unit_Draw(0,0,pDC);
		drawLines(crosslist,pDC);
	}


	void COrthogonal_ListView::drawLines(CCrossList * crosslist, CDC * pDC)
	{
		vector<VecNode *> vecptr = crosslist->assist;
		CPen *pe;
		CPen * oldpen = new CPen(PS_SOLID,1,RGB(0,0,0));
		pe = new CPen(PS_DOT,1,RGB(0,0,0));
		pDC->SelectObject(pe);
		pDC->MoveTo(*crosslist->InitHead->arrowRight());
		Node * curptr = NULL;
		for(int i = 0;i < crosslist->getCol();i ++)
		{
			if(vecptr.at(i)->Hhead->down != vecptr.at(i)->Hhead)
			{
				curptr = vecptr.at(i)->Hhead;
				break;
			}
		}
		if(curptr != NULL)
		{

			pDC->LineTo(* curptr->drawunit->arrowLeft());
			drawHArrow(curptr->drawunit->arrowLeft()->x-curptr->drawunit->Width / 12,curptr->drawunit->arrowLeft()->y,curptr->drawunit->Width  / 12,pDC);
			Node * nextptr = NULL;
			while(curptr->col < crosslist->getCol())
			{

				for(int k = curptr->col;k < crosslist->getCol();k++)
				{
					if(vecptr.at(k)->Hhead->down != vecptr.at(k)->Hhead)
					{
						nextptr = vecptr.at(k)->Hhead;
						break;
					}
				}
				if(nextptr == NULL)
					break;
				else
				{
					pDC->MoveTo(*curptr->drawunit->arrowRight());
					pDC->LineTo(*nextptr->drawunit->arrowLeft());
					drawHArrow(nextptr->drawunit->arrowLeft()->x-nextptr->drawunit->Width / 12,nextptr->drawunit->arrowLeft()->y,nextptr->drawunit->Width  / 12,pDC);
					curptr = nextptr;
					nextptr = NULL;
				}
			}
		}
		pDC->MoveTo(*curptr->drawunit->arrowRight());
		pDC->LineTo(curptr->drawunit->arrowRight()->x + curptr->drawunit->Width/6,curptr->drawunit->arrowRight()->y);
		pDC->LineTo(curptr->drawunit->arrowRight()->x + curptr->drawunit->Width/6,curptr->drawunit->arrowRight()->y + curptr->drawunit->Height * 2 /3);
		pDC->LineTo(crosslist->InitHead->arrowLeft()->x - crosslist->InitHead->Width/6,crosslist->InitHead->arrowLeft()->y + crosslist->InitHead->Height * 2 /3);
		pDC->LineTo(crosslist->InitHead->arrowLeft()->x - crosslist->InitHead->Width/6,crosslist->InitHead->arrowLeft()->y);
		pDC->LineTo(*crosslist->InitHead->arrowLeft());
		drawHArrow(crosslist->InitHead->arrowLeft()->x-crosslist->InitHead->Width / 12,crosslist->InitHead->arrowLeft()->y,crosslist->InitHead->Width  / 12,pDC);

		for(int i = 0;i < crosslist->getScale();i++)
		{
			if(vecptr.at(i)->Vhead != NULL)
			{
				pe = new CPen(PS_SOLID,1,RGB(0,0,0));
				pDC->SelectObject(pe);
				Node * nodeptr = vecptr.at(i)->Vhead;
				while(nodeptr->right != vecptr.at(i)->Vhead)
				{
					pDC->MoveTo(*nodeptr->drawunit->arrowRight());
					pDC->LineTo(*nodeptr->right->drawunit->arrowLeft());
					drawHArrow(nodeptr->right->drawunit->arrowLeft()->x-nodeptr->right->drawunit->Width / 12,nodeptr->right->drawunit->arrowLeft()->y,nodeptr->right->drawunit->Width  / 12,pDC);
					nodeptr = nodeptr->right;
				}
				if(nodeptr != vecptr.at(i)->Vhead)
				{
					pDC->MoveTo(*nodeptr->drawunit->arrowRight());
					pDC->LineTo(nodeptr->drawunit->arrowRight()->x + nodeptr->drawunit->Width/6,nodeptr->drawunit->arrowRight()->y);
					pDC->LineTo(nodeptr->drawunit->arrowRight()->x + nodeptr->drawunit->Width/6,nodeptr->drawunit->arrowRight()->y + nodeptr->drawunit->Height * 2 /3);
					pDC->LineTo(nodeptr->right->drawunit->arrowLeft()->x - nodeptr->right->drawunit->Width/6,nodeptr->right->drawunit->arrowLeft()->y + nodeptr->right->drawunit->Height * 2 /3);
					pDC->LineTo(nodeptr->right->drawunit->arrowLeft()->x - nodeptr->right->drawunit->Width/6,nodeptr->right->drawunit->arrowLeft()->y);
					pDC->LineTo(*nodeptr->right->drawunit->arrowLeft());
					drawHArrow(nodeptr->right->drawunit->arrowLeft()->x-nodeptr->right->drawunit->Width / 12,nodeptr->right->drawunit->arrowLeft()->y,nodeptr->right->drawunit->Width  / 12,pDC);
				}

			}

			if(vecptr.at(i)->Hhead != NULL)
			{
				pe = new CPen(PS_SOLID,1,RGB(0,0,0));
				pDC->SelectObject(pe);
				Node * nodeptr = vecptr.at(i)->Hhead;
				while(nodeptr->down != vecptr.at(i)->Hhead)
				{
					pDC->MoveTo(*nodeptr->drawunit->arrowDown());
					pDC->LineTo(*nodeptr->down->drawunit->arrowUp());
					drawVArrow(nodeptr->down->drawunit->arrowUp()->x,nodeptr->down->drawunit->arrowUp()->y-nodeptr->down->drawunit->Width / 12,nodeptr->down->drawunit->Width  / 12,pDC);
					nodeptr = nodeptr->down;
				}
				if(nodeptr != vecptr.at(i)->Hhead)
				{
					pDC->MoveTo(*nodeptr->drawunit->arrowDown());
					pDC->LineTo(nodeptr->drawunit->arrowDown()->x,nodeptr->drawunit->arrowDown()->y + nodeptr->drawunit->Height/6);
					pDC->LineTo(nodeptr->drawunit->arrowDown()->x - nodeptr->drawunit->Width * 2 /3,nodeptr->drawunit->arrowDown()->y + nodeptr->drawunit->Height/6);
					pDC->LineTo(nodeptr->down->drawunit->arrowUp()->x - nodeptr->down->drawunit->Width * 2 /3,nodeptr->down->drawunit->arrowUp()->y - nodeptr->down->drawunit->Height /4);
					pDC->LineTo(nodeptr->down->drawunit->arrowUp()->x,nodeptr->down->drawunit->arrowUp()->y - nodeptr->down->drawunit->Height / 4);
					pDC->LineTo(*nodeptr->down->drawunit->arrowUp());
					drawVArrow(nodeptr->down->drawunit->arrowUp()->x,nodeptr->down->drawunit->arrowUp()->y-nodeptr->down->drawunit->Width / 12,nodeptr->down->drawunit->Width  / 12,pDC);
				}
			}
		}
		pDC->SelectObject(oldpen);
	}


	void COrthogonal_ListView::drawHArrow(int x, int y, int length, CDC * pDC)
	{
		CBrush *brush1=CBrush::FromHandle((HBRUSH)CreateSolidBrush(RGB(0,0,0)));   
		pDC->SelectObject(brush1);  

		pDC->BeginPath();
		pDC->MoveTo(x,y);
		pDC->LineTo(x,y - length / 2);
		pDC->LineTo(x + length,y);
		pDC->LineTo(x,y + length / 2);
		pDC->LineTo(x,y);
		pDC->EndPath();
		pDC->FillPath();
	}


	void COrthogonal_ListView::drawVArrow(int x, int y, int length, CDC * pDC)
	{
		CBrush *brush1=CBrush::FromHandle((HBRUSH)CreateSolidBrush(RGB(0,0,0)));   
		pDC->SelectObject(brush1);  
		pDC->BeginPath();
		pDC->MoveTo(x,y);
		pDC->LineTo(x - length / 2,y);
		pDC->LineTo(x,y + length);
		pDC->LineTo(x + length / 2,y);
		pDC->LineTo(x,y);
		pDC->EndPath();
		pDC->FillPath();
	}

	void COrthogonal_ListView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		SCROLLINFO si; 
		GetScrollInfo(SB_VERT, &si, SIF_ALL); 
		//m_ImgVScrollPos = si.nPos; 
		//Invalidate(false); 
		CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	}


	void COrthogonal_ListView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		SCROLLINFO si; 
		GetScrollInfo(SB_HORZ, &si, SIF_ALL); 
		//m_ImgHScrollPos = si.nPos; 
		//Invalidate(false); 
		CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	}

	int COrthogonal_ListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CScrollView::OnCreate(lpCreateStruct) == -1)
			return -1;
		// TODO:  在此添加您专用的创建代码
		CDC* pDC=GetDC();
		m_pMemDC->CreateCompatibleDC(pDC);
		return 0;
	}


	void COrthogonal_ListView::OnTimer(UINT_PTR nIDEvent)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		switch(nIDEvent)
		{
		case 1:
			searchMove(searchArray,1,delay_flag);
			delay_flag ++;
			break;
		case 2:
			searchMove(searchArray,2,delay_flag);
			delay_flag ++;
			break;
		case 3:
			searchMove(searchArray,3,delay_flag);
			delay_flag ++;
			break;
		}

		CScrollView::OnTimer(nIDEvent);
	}


	void COrthogonal_ListView::searchMove(vector<Node*> * vecptr,int mode,unsigned int &delay_flag)
	{
		CRect rc;
		GetWindowRect(&rc);
		int hpos = 0;
		int vpos = 0;
		COrthogonal_ListDoc *pDoc = GetDocument();
		int index = delay_flag - 1;
		if(delay_flag == 0)
		{
			GetDocument()->ClObj->InitHead->set_Flag();
			GetDocument()->ClObj->InitHead->unit_Draw(0,0,m_pMemDC);

		}
		else if(delay_flag < vecptr->size())
		{
			while(vecptr->at(index)->down == vecptr->at(index))
			{
				index ++;
				delay_flag ++;
			}
			if(rc.Width() < HRange)
			{
				int hpos = vecptr->at(index)->drawunit->get_X() + pDoc->ClObj->InitHead->Width - rc.Width() / 2;
				if(hpos < 0)
					hpos = 0;
				else if(hpos >HRange - rc.Width() / 2)
					hpos = HRange - rc.Width() / 2;
				SetScrollPos(SB_HORZ,hpos);
			}
			if(rc.Height() < VRange)
			{
				int vpos = vecptr->at(index)->drawunit->get_Y() + pDoc->ClObj->InitHead->Height - rc.Height() / 2;
				if(vpos < 0)
					vpos = 0;
				else if(vpos >VRange - rc.Height() / 2)
					vpos = VRange - rc.Height() / 2;
				SetScrollPos(SB_VERT,vpos);
			}
			vecptr->at(index)->drawunit->set_Flag();
			vecptr->at(index)->drawunit->unit_Draw(vecptr->at(index)->drawunit->get_Rowpos(),vecptr->at(index)->drawunit->get_Colpos(),m_pMemDC);
			Invalidate(false);
		}
		else
		{
			if(rc.Width() < HRange)
			{
				int hpos = vecptr->at(index)->drawunit->get_X() + pDoc->ClObj->InitHead->Width - rc.Width() / 2;
				if(hpos < 0)
					hpos = 0;
				else if(hpos >HRange - rc.Width() / 2)
					hpos = HRange - rc.Width() / 2;
				SetScrollPos(SB_HORZ,hpos);
			}
			if(rc.Height() < VRange)
			{
				int vpos = vecptr->at(index)->drawunit->get_Y() + pDoc->ClObj->InitHead->Height - rc.Height() / 2;
				if(vpos < 0)
					vpos = 0;
				else if(vpos >VRange - rc.Height() / 2)
					vpos = VRange - rc.Height() / 2;
				SetScrollPos(SB_VERT,vpos);
			}
			vecptr->at(index)->drawunit->check_Flag();
			vecptr->at(index)->drawunit->unit_Draw(vecptr->at(index)->drawunit->get_Rowpos(),vecptr->at(index)->drawunit->get_Colpos(),m_pMemDC);
			Invalidate(false);

			switch(mode)
			{
			case 1:
				{	
					KillTimer(1);
					CString str2("插入成功！该节点的值为：");
					CString str3("插入结果");
					MessageBox(str2 + vecptr->at(vecptr->size()-1)->data,str3);
					for(unsigned int i = 0;i < vecptr->size();i ++)
					{
						vecptr->at(i)->drawunit->unset_Flag();
						vecptr->at(i)->drawunit->unit_Draw(vecptr->at(i)->drawunit->get_Rowpos(),vecptr->at(i)->drawunit->get_Colpos(),m_pMemDC);
					}
					GetDocument()->ClObj->InitHead->unset_Flag();
					GetDocument()->ClObj->InitHead->unit_Draw(0,0,m_pMemDC);
					Invalidate();
					break;
				}
			case 2:
				{
					KillTimer(2);
					CString str2("该节点的值为：");
					CString str3("检索结果");
					CString str1(vecptr->at(vecptr->size()-1)->data + L"\n检索路径为:\n");
					CString tmpstrx;
					CString tmpstry;
					for(unsigned int i = 0;i < vecptr->size();i ++)
					{
						tmpstrx.Format(TEXT("%d"),vecptr->at(i)->row);
						tmpstry.Format(TEXT("%d"),vecptr->at(i)->col);
						str1 += L"    ( " + tmpstrx + L" ,  " + tmpstry + L" );\n";
					}
					MessageBox(str2 + str1,str3);
					for(unsigned int i = 0;i < vecptr->size();i ++)
					{
						vecptr->at(i)->drawunit->unset_Flag();
						vecptr->at(i)->drawunit->unit_Draw(vecptr->at(i)->drawunit->get_Rowpos(),vecptr->at(i)->drawunit->get_Colpos(),m_pMemDC);
					}
					GetDocument()->ClObj->InitHead->unset_Flag();
					GetDocument()->ClObj->InitHead->unit_Draw(0,0,m_pMemDC);
					Invalidate();
					break;
				}
			case 3:
				{
					KillTimer(3);
					CString str2("删除成功！该节点的值为：");
					CString str3("删除结果");

					COrthogonal_ListDoc * pDoc = GetDocument();
					Node * nodeptr = pDoc->ClObj->findNode(_ttoi(m_outNewRow),_ttoi(m_outNewCol));
					MessageBox(str2 + nodeptr->data,str3);
					if(pDoc->ClObj->getScale() != 0)
					{
						for(unsigned int i = 0;i < vecptr->size();i ++)
						{
							vecptr->at(i)->drawunit->unset_Flag();
							vecptr->at(i)->drawunit->unit_Draw(vecptr->at(i)->drawunit->get_Rowpos(),vecptr->at(i)->drawunit->get_Colpos(),m_pMemDC);
						}
						GetDocument()->ClObj->InitHead->unset_Flag();
						Node * nodeptr = pDoc->ClObj->deleteNode(_ttoi(m_outNewRow),_ttoi(m_outNewCol));
						if(pDoc->ClObj->getScale() != 0)
						{
							VRange = pDoc->ClObj->assist.at(pDoc->ClObj->getRow() - 1)->Vhead->drawunit->get_Y() + pDoc->ClObj->InitHead->Height * 2;
							HRange = pDoc->ClObj->assist.at(pDoc->ClObj->getCol() - 1)->Hhead->drawunit->get_X() + pDoc->ClObj->InitHead->Width * 2;
							CDC* pDC=GetDC();
							if(m_pMemDC != NULL)
								m_pMemDC->DeleteDC();
							if(m_pBitmap != NULL)
								m_pBitmap->DeleteObject();
							m_pMemDC->CreateCompatibleDC(pDC);
							m_pBitmap->CreateCompatibleBitmap(pDC,HRange,VRange);
							m_pMemDC->SelectObject(m_pBitmap);
							//ReleaseDC(pDC); 
							CBrush brush;
							brush.CreateStockObject(WHITE_BRUSH);
							CBrush* poldbrush=m_pMemDC->SelectObject(&brush); 
							m_pMemDC->PatBlt(0,0,HRange,VRange,PATCOPY);
							m_pMemDC->SelectObject(poldbrush);

							drawList(pDoc->ClObj,m_pMemDC);

							Invalidate();
						}
						else
						{
							VRange = 0;
							HRange = 0;
							CDC* pDC=GetDC();
							if(m_pMemDC != NULL)
								m_pMemDC->DeleteDC();
							if(m_pBitmap != NULL)
								m_pBitmap->DeleteObject();
							m_pMemDC->CreateCompatibleDC(pDC);
							m_pBitmap->CreateCompatibleBitmap(pDC,HRange,VRange);
							m_pMemDC->SelectObject(m_pBitmap);
							//ReleaseDC(pDC); 
							CBrush brush;
							brush.CreateStockObject(WHITE_BRUSH);
							CBrush* poldbrush=m_pMemDC->SelectObject(&brush); 
							m_pMemDC->PatBlt(0,0,HRange,VRange,PATCOPY);
							m_pMemDC->SelectObject(poldbrush);

							//drawList(pDoc->ClObj,m_pMemDC);

							Invalidate();
						}
						break;
					}
				}
			}

		}
	}


	void COrthogonal_ListView::loadRefresh(void)
	{
		COrthogonal_ListDoc *pDoc = GetDocument();
		CSize sizeTotal(0,0);
		SetScrollSizes(MM_TEXT,sizeTotal);
		VRange = pDoc->ClObj->assist.at(pDoc->ClObj->getRow() - 1)->Vhead->drawunit->get_Y() + pDoc->ClObj->InitHead->Height * 2;
		HRange = pDoc->ClObj->assist.at(pDoc->ClObj->getCol() - 1)->Hhead->drawunit->get_X() + pDoc->ClObj->InitHead->Width * 2;
		CDC* pDC=GetDC();
		if(m_pMemDC != NULL)
			m_pMemDC->DeleteDC();
		if(m_pBitmap != NULL)
			m_pBitmap->DeleteObject();
		m_pMemDC->CreateCompatibleDC(pDC);
		m_pBitmap->CreateCompatibleBitmap(pDC,HRange,VRange);
		m_pMemDC->SelectObject(m_pBitmap);
		//ReleaseDC(pDC); 
		CBrush brush;
		brush.CreateStockObject(WHITE_BRUSH);
		CBrush* poldbrush=m_pMemDC->SelectObject(&brush); 
		m_pMemDC->PatBlt(0,0,HRange,VRange,PATCOPY);
		m_pMemDC->SelectObject(poldbrush);
		drawList(pDoc->ClObj,m_pMemDC);

		Invalidate();
	}


	void COrthogonal_ListView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		point += this->GetScrollPosition();
		COrthogonal_ListDoc *pDoc = GetDocument();
		int initX = CDrawUnit::x0 + 2 * CDrawUnit::Width;
		int initY = CDrawUnit::y0 + 2 * CDrawUnit::Height;
		bool isfound = false;
		if(!insertMode)
		{
			if(point.x > initX && point.x < HRange && point.y > initY && point.y < VRange && ((point.x - initX)%(2 * CDrawUnit::Width) <= CDrawUnit::Width) && ((point.y - initY)%(2 * CDrawUnit::Height) <= CDrawUnit::Height))
			{
				int indexX = (point.x - initX)/(2 * CDrawUnit::Width);
				int temp = 0;
				int temp1 = 0;
				for(int i = 0;i < pDoc->ClObj->getCol();i++)
				{
					if(pDoc->ClObj->assist.at(i)->Hhead->down != pDoc->ClObj->assist.at(i)->Hhead)
					{
						if(temp == indexX)
						{
							int indexY = (point.y - initY)/(2 * CDrawUnit::Height);
							for(int j = 0;j < pDoc->ClObj->getRow();j++)
							{
								if(pDoc->ClObj->assist.at(j)->Vhead->right != pDoc->ClObj->assist.at(j)->Vhead)
								{
									if(temp1 == indexY)
									{
										indexY = j;
										break;
									}
									temp1 ++;
								}
							}
							Node * current = pDoc->ClObj->assist.at(i)->Hhead->down;
							while(current != pDoc->ClObj->assist.at(i)->Hhead)
							{
								if(current->row == indexY + 1)
								{
									current->drawunit->isselected = 1;
									current->drawunit->unit_Draw(current->drawunit->get_Rowpos(),current->drawunit->get_Colpos(),m_pMemDC);
									highlight = current;
									Invalidate(false);
									isfound = true;
									break;
								}
								else if(current->row > indexY + 1)
									break;
								current = current->down;
							}
							break;
						}
						temp ++;
					}
				}
			}
			if(highlight != NULL && isfound == false)
			{
				highlight->drawunit->isselected = 0;
				highlight->drawunit->unit_Draw(highlight->drawunit->get_Rowpos(),highlight->drawunit->get_Colpos(),m_pMemDC);
				highlight = NULL;
				Invalidate(false);
			}
		}
		else
		{
			int insertrow = (point.y - initY)/(2 * CDrawUnit::Height) + 1;
			int insertcol = (point.x - initX)/(2 * CDrawUnit::Width) + 1;
			if(insertcol == 0)
				insertcol = 1;
			if(insertrow == 0)
				insertrow = 1;
			int temp = 1;
			Node * tmpnode = NULL;
			CString str;
			
			str.Format(TEXT("%d"),insertrow);
			m_outNewRow = str;
			str.Format(TEXT("%d"),insertcol);
			m_outNewCol = str;
			int width = pDoc->ClObj->InitHead->Width;
			int height = pDoc->ClObj->InitHead->Height;
			int xx = point.x - width /2;
			int yy = point.y - height / 2;
			CBrush *br = new CBrush(RGB(255,255,255));
			m_pMemDC->SelectObject(br);
			m_pMemDC->Rectangle(xx,yy,xx+width,yy+height);
			m_pMemDC->MoveTo(xx+ int(width / 3),yy);
			m_pMemDC->LineTo(xx+ int(width / 3),yy+ int(height / 2));
			m_pMemDC->MoveTo(xx+ int(width * 2 / 3),yy);
			m_pMemDC->LineTo(xx+ int(width  * 2 / 3),yy+ int(height / 2));
			m_pMemDC->MoveTo(xx+ int(width / 2),yy+ int(height / 2));
			m_pMemDC->LineTo(xx+ int(width / 2),yy+ height);
			m_pMemDC->MoveTo(xx,yy+ int(height / 2));
			m_pMemDC->LineTo(xx+ width,yy+ int(height / 2));
			Invalidate(false);
			OnNodeInsert();
			insertMode = false;

			m_pMemDC->SelectObject(br);
			m_pMemDC->PatBlt(0,0,HRange,VRange,PATCOPY);
			drawList(pDoc->ClObj,m_pMemDC);
			Invalidate(false);
		}

		CScrollView::OnMouseMove(nFlags, point);
	}

	void COrthogonal_ListView::OnContextMenu(CWnd* pWnd, CPoint point)
	{
		// TODO: 在此处添加消息处理程序代码
		CMenu popMenu;
		popMenu.LoadMenu(IDR_SUBMENU1); //载入菜单
		CMenu *pPopup;
		pPopup=popMenu.GetSubMenu(0); //获得子菜单指针
		if(highlight == NULL)
		{
			pPopup->EnableMenuItem(ID_POPUP_INSERT,MF_BYCOMMAND|MF_ENABLED);
			pPopup->EnableMenuItem(ID_POPUP_CHANGE,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED); 
			pPopup->EnableMenuItem(ID_POPUP_DELETE,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED); 
		}
		else
		{
			pPopup->EnableMenuItem(ID_POPUP_CHANGE,MF_BYCOMMAND|MF_ENABLED);
			pPopup->EnableMenuItem(ID_POPUP_DELETE,MF_BYCOMMAND|MF_ENABLED); 
			pPopup->EnableMenuItem(ID_POPUP_INSERT,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED); 
		}
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this); //显示弹出菜单，参数依次为(鼠标在菜单左边|跟踪右键，x，y，this)
		pPopup->Detach();
		popMenu.DestroyMenu();
	}


	void COrthogonal_ListView::OnPopupInsert()
	{
		// TODO: 在此添加命令处理程序代码
		if(GetDocument()->ClObj == NULL)
			MessageBox(L"请先初始化",L"提示");
		else
			insertMode = true;
	}


	void COrthogonal_ListView::OnPopupDelete()
	{
		// TODO: 在此添加命令处理程序代码
		COrthogonal_ListDoc *pDoc = GetDocument();
		CString str;
		str.Format(TEXT("%d"),highlight->row);
		m_outNewRow = str;
		str.Format(TEXT("%d"),highlight->col);
		m_outNewCol = str;
		vector<Node*> * nodeptr = pDoc->ClObj->searchNode(_ttoi(m_outNewRow),_ttoi(m_outNewCol));
		searchArray = nodeptr;
		delay_flag = 0;
		SetTimer(3, 500, NULL);
	}


	void COrthogonal_ListView::OnPopupChange()
	{
		// TODO: 在此添加命令处理程序代码
		CDialogChange changedlg;
		int result = changedlg.DoModal();
		if(result == IDOK)
		{
			m_outNewData = changedlg.m_Data;
			CString str;
			str.Format(TEXT("%d"),highlight->row);
			m_outNewRow = str;
			str.Format(TEXT("%d"),highlight->col);
			m_outNewCol = str;
			GetDocument()->ClObj->changeData(highlight->row,highlight->col,m_outNewData);
			highlight->drawunit->unit_Draw(highlight->drawunit->get_Rowpos(),highlight->drawunit->get_Colpos(),m_pMemDC);
			Invalidate(false);//////////////////
		}
	}


	void COrthogonal_ListView::OnUpdatePopupInsert(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(GetDocument()->ClObj == NULL)
			pCmdUI->Enable(false);
	}
