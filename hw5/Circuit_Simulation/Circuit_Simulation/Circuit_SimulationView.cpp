
// Circuit_SimulationView.cpp : CCircuit_SimulationView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Circuit_Simulation.h"
#endif

#include "Circuit_SimulationDoc.h"
#include "Circuit_SimulationView.h"
#include "Node.h"
#include "Component.h"
#include "define.h"
#include "DialogNew.h"
#include "DialogSig.h"
#include "DialogEdit.h"
#include "DialogOsc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCircuit_SimulationView

IMPLEMENT_DYNCREATE(CCircuit_SimulationView, CScrollView)

	BEGIN_MESSAGE_MAP(CCircuit_SimulationView, CScrollView)
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCircuit_SimulationView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_WM_CREATE()
		//		ON_COMMAND(ID_NEW, &CCircuit_SimulationView::OnNew)
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONUP()
		ON_COMMAND(ID_FILE_NEW, &CCircuit_SimulationView::OnFileNew)
		ON_COMMAND(ID_REVERSE, &CCircuit_SimulationView::OnReverse)
		ON_COMMAND(ID_RE_NEW, &CCircuit_SimulationView::OnReNew)
		ON_COMMAND(ID_LI_NEW, &CCircuit_SimulationView::OnLiNew)
		ON_COMMAND(ID_CA_NEW, &CCircuit_SimulationView::OnCaNew)
		ON_COMMAND(ID_ES_NEW, &CCircuit_SimulationView::OnEsNew)
		ON_COMMAND(ID_IS_NEW, &CCircuit_SimulationView::OnIsNew)
		ON_WM_LBUTTONDOWN()
		ON_WM_MOUSEWHEEL()
		ON_WM_MBUTTONDOWN()
		ON_WM_MBUTTONUP()
		ON_WM_LBUTTONDBLCLK()
		ON_COMMAND(ID_SIGNAL_NEW, &CCircuit_SimulationView::OnSignalNew)
		ON_COMMAND(ID_SIGNALC_NEW, &CCircuit_SimulationView::OnSignalcNew)
		ON_COMMAND(ID_PARA_EDIT, &CCircuit_SimulationView::OnParaEdit)
		ON_COMMAND(ID_GRD_NEW, &CCircuit_SimulationView::OnGrdNew)
		ON_COMMAND(ID_PN_CHANGE, &CCircuit_SimulationView::OnPnChange)
		ON_COMMAND(ID_OSC_NEW, &CCircuit_SimulationView::OnOscNew)
		ON_UPDATE_COMMAND_UI(ID_CA_NEW, &CCircuit_SimulationView::OnUpdateCaNew)
		ON_UPDATE_COMMAND_UI(ID_ES_NEW, &CCircuit_SimulationView::OnUpdateEsNew)
		ON_UPDATE_COMMAND_UI(ID_GRD_NEW, &CCircuit_SimulationView::OnUpdateGrdNew)
		ON_UPDATE_COMMAND_UI(ID_IS_NEW, &CCircuit_SimulationView::OnUpdateIsNew)
		ON_UPDATE_COMMAND_UI(ID_LI_NEW, &CCircuit_SimulationView::OnUpdateLiNew)
		ON_UPDATE_COMMAND_UI(ID_OSC_NEW, &CCircuit_SimulationView::OnUpdateOscNew)
		ON_UPDATE_COMMAND_UI(ID_PARA_EDIT, &CCircuit_SimulationView::OnUpdateParaEdit)
		ON_UPDATE_COMMAND_UI(ID_PN_CHANGE, &CCircuit_SimulationView::OnUpdatePnChange)
		ON_UPDATE_COMMAND_UI(ID_RE_NEW, &CCircuit_SimulationView::OnUpdateReNew)
		ON_UPDATE_COMMAND_UI(ID_REVERSE, &CCircuit_SimulationView::OnUpdateReverse)
		ON_UPDATE_COMMAND_UI(ID_SIGNAL_NEW, &CCircuit_SimulationView::OnUpdateSignalNew)
		ON_UPDATE_COMMAND_UI(ID_SIGNALC_NEW, &CCircuit_SimulationView::OnUpdateSignalcNew)
		ON_COMMAND(ID_OSC_DELETE, &CCircuit_SimulationView::OnOscDelete)
		ON_UPDATE_COMMAND_UI(ID_OSC_DELETE, &CCircuit_SimulationView::OnUpdateOscDelete)
	END_MESSAGE_MAP()

	// CCircuit_SimulationView 构造/析构

	CCircuit_SimulationView::CCircuit_SimulationView()
		: m_pMemDC(NULL)
		, m_pBitmap(NULL)
		, isCreating(false)
		, newcomp(NULL)
		, pselect(NULL)
		, islinking(false)
		, linksx(0)
		, linksy(0)
		, linkpoint(NULL)
		, nowlink(NULL)
		, highlight(NULL)
		, rectangle(NULL)
		, lbuttondown(false)
		, isdragging(false)
		, startpos(NULL)
		, startmouse(NULL)
		, scale(1)
		, isscrolling(false)
		, curline(NULL)
		, ground(NULL)
		, oscNode(NULL)
		, init(false)
		, isplaying(false)
	{
		// TODO: 在此处添加构造代码
		m_pMemDC = new CDC();
		m_pBitmap = new CBitmap();
	}

	CCircuit_SimulationView::~CCircuit_SimulationView()
	{
	}

	BOOL CCircuit_SimulationView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CScrollView::PreCreateWindow(cs);
	}

	// CCircuit_SimulationView 绘制

	void CCircuit_SimulationView::OnDraw(CDC* pDC)
	{
		CCircuit_SimulationDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 在此处为本机数据添加绘制代码
		if(m_pBitmap != NULL,m_pMemDC != NULL)
		{
			CRect rc;
			GetClientRect(rc);
			CSize sizeTotal(MAXWIDTH * scale,MAXHEIGHT * scale);
			pDC->BitBlt(0,0,sizeTotal.cx,sizeTotal.cy,m_pMemDC,0,0,SRCCOPY);
			SetScrollSizes(MM_TEXT,sizeTotal);		
		}
	}

	void CCircuit_SimulationView::OnInitialUpdate()
	{
		CScrollView::OnInitialUpdate();

		CSize sizeTotal;
		// TODO: 计算此视图的合计大小
		sizeTotal.cx = sizeTotal.cy = 100;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}


	// CCircuit_SimulationView 打印


	void CCircuit_SimulationView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CCircuit_SimulationView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CCircuit_SimulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CCircuit_SimulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}

	void CCircuit_SimulationView::OnRButtonUp(UINT nFlags, CPoint point)
	{
		point += this->GetScrollPosition();
		ClientToScreen(&point);
		if(!isCreating && !islinking)
		{
			OnContextMenu(this, point);
		}
		else if(!islinking)
		{
			isCreating = false;
			newcomp = NULL;
			drawAll(m_pMemDC);
			Invalidate(false);
			//CScrollView::OnRButtonUp(nFlags, point);
		}
		else if(nowlink != NULL)
		{
			for(unsigned int k = 1;k < nowlink->points.size();k ++)
			{
				delete nowlink->points.at(k);
			}
			delete nowlink;
			nowlink= NULL;
			islinking = false;
			drawAll(m_pMemDC);
			Invalidate(false);
		}
	}

	void CCircuit_SimulationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CCircuit_SimulationView 诊断

#ifdef _DEBUG
	void CCircuit_SimulationView::AssertValid() const
	{
		CScrollView::AssertValid();
	}

	void CCircuit_SimulationView::Dump(CDumpContext& dc) const
	{
		CScrollView::Dump(dc);
	}

	CCircuit_SimulationDoc* CCircuit_SimulationView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCircuit_SimulationDoc)));
		return (CCircuit_SimulationDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CCircuit_SimulationView 消息处理程序


	int CCircuit_SimulationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CScrollView::OnCreate(lpCreateStruct) == -1)
			return -1;
		// TODO:  在此添加您专用的创建代码
		CDC* pDC=GetDC();
		m_pMemDC->CreateCompatibleDC(pDC);
		return 0;
	}

	void CCircuit_SimulationView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值

		CCircuit_SimulationDoc *pDoc = GetDocument();

		if(isscrolling)
		{
			int cx,cy;
			cx = GetScrollPos(SB_HORZ);
			cy = GetScrollPos(SB_VERT);
			SetScrollPos(SB_HORZ,cx - point.x + startmouse->x);
			SetScrollPos(SB_VERT,cy - point.y + startmouse->y);
			startmouse->x = point.x;
			startmouse->y = point.y;
			Invalidate(false);
		}
		else
		{
			point += this->GetScrollPosition();
			int offset;
			if(point.x * 10000 % int(CHECK * scale * 10000) < int(CHECK * scale * 10000) / double(2))
				offset = 0;
			else
				offset = 1;
			int rx = int((point.x * 10000 / int(CHECK * scale * 10000) + offset)* CHECK);
			if(point.y * 10000 % int(CHECK * scale * 10000) < int(CHECK * scale * 10000) / double(2))
				offset = 0;
			else
				offset = 1;
			int ry = int((point.y * 10000 / int(CHECK * scale * 10000) + offset)* CHECK);
			if(highlight == NULL)
			{
				if(islinking)
				{
					drawAll(m_pMemDC);

					linkLine(rx,ry,m_pMemDC);
					Invalidate(false);
				}
				if(isCreating)
				{
					drawAll(m_pMemDC);
					XFORM xForm =  
					{ 
						1.0f, 0.0f, 
						0.0f, 1.0f,
						0.0f, 0.0f
					};
					xForm.eM11 = scale;
					xForm.eM22 = scale;
					m_pMemDC->SetWorldTransform(&xForm);
					newcomp->draw(rx,ry,m_pMemDC);
					xForm.eM11 = 1.0f;
					xForm.eM22 = 1.0f;
					m_pMemDC->SetWorldTransform(&xForm);
					Invalidate(false);
				}
				else
				{
					bool innode = false;
					for(unsigned int i = 0;i < pDoc->points.size();i++)
					{
						if(rx <= pDoc->points.at(i)->x + AREA && rx >=  pDoc->points.at(i)->x - AREA && ry <= pDoc->points.at(i)->y + AREA && ry >= pDoc->points.at(i)->y - AREA)
						{
							innode = true;
							pselect = pDoc->points.at(i);
							XFORM xForm =  
							{ 
								1.0f, 0.0f, 
								0.0f, 1.0f,
								0.0f, 0.0f
							};
							xForm.eM11 = scale;
							xForm.eM22 = scale;
							m_pMemDC->SetWorldTransform(&xForm);
							pDoc->points.at(i)->drawcircle(m_pMemDC);
							xForm.eM11 = 1.0f;
							xForm.eM22 = 1.0f;
							m_pMemDC->SetWorldTransform(&xForm);
							Invalidate(false);
							return;
						}
					}
					for(unsigned int i = 0;i < Osclist.size();i++)
					{
						if((rx <= Osclist.at(i)->lp->x + AREA && rx >=  Osclist.at(i)->lp->x - AREA && ry <= Osclist.at(i)->lp->y + AREA && ry >= Osclist.at(i)->lp->y - AREA)
							|| (rx <= Osclist.at(i)->rp->x + AREA && rx >=  Osclist.at(i)->rp->x - AREA && ry <= Osclist.at(i)->rp->y + AREA && ry >= Osclist.at(i)->rp->y - AREA))
						{
							Point * selectpoint;
							if((rx <= Osclist.at(i)->lp->x + AREA && rx >=  Osclist.at(i)->lp->x - AREA && ry <= Osclist.at(i)->lp->y + AREA && ry >= Osclist.at(i)->lp->y - AREA))
								selectpoint = Osclist.at(i)->lp;
							else
								selectpoint = Osclist.at(i)->rp;
							innode = true;
							pselect = selectpoint;
							XFORM xForm =  
							{ 
								1.0f, 0.0f, 
								0.0f, 1.0f,
								0.0f, 0.0f
							};
							xForm.eM11 = scale;
							xForm.eM22 = scale;
							m_pMemDC->SetWorldTransform(&xForm);
							selectpoint->drawcircle(m_pMemDC);
							xForm.eM11 = 1.0f;
							xForm.eM22 = 1.0f;
							m_pMemDC->SetWorldTransform(&xForm);
							Invalidate(false);
							return;
						}
					}
					if(pselect != NULL && !innode)
					{
						pselect = NULL;
						drawAll(m_pMemDC);
						Invalidate(false);
					}
				}
			}
			else
			{
				if(lbuttondown && highlight->lp->pnode == NULL && highlight->rp->pnode == NULL)
				{
					if(!isdragging && (abs(rx - startmouse->x) > CHECK || abs(ry - startmouse->y) > CHECK))
					{
						isdragging = true;
					}
					else if(isdragging)
					{
						highlight->draw(startpos->x + rx - startmouse->x,startpos->y + ry - startmouse->y,m_pMemDC);				
						delete rectangle;
						rectangle = NULL;
						drawAll(m_pMemDC);
						Invalidate(false);
					}
				}
			}
		}
		CScrollView::OnMouseMove(nFlags, point);
	}

	void CCircuit_SimulationView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		point += this->GetScrollPosition();
		if(isdragging)
		{
			isdragging = false;
			highlight = NULL;
		}
		lbuttondown = false;
		delete startpos;
		startpos = NULL;
		delete startmouse;
		startmouse = NULL;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		if(highlight == NULL)
		{
			if(isCreating)
			{
				curline = NULL;
				bool overlap = false;
				for(unsigned int i = 0;i < pDoc->re.size();i++)
				{
					if(pDoc->re.at(i)->isoverlap(point.x,point.y))
					{
						overlap = true;
						break;
					}
				}
				for(unsigned int i = 0;i < pDoc->ca.size();i++)
				{
					if(overlap || pDoc->ca.at(i)->isoverlap(point.x,point.y))
					{
						overlap = true;
						break;
					}
				}
				for(unsigned int i = 0;i < pDoc->li.size();i++)
				{
					if(overlap || pDoc->li.at(i)->isoverlap(point.x,point.y))
					{
						overlap = true;
						break;
					}
				}
				for(unsigned int i = 0;i < pDoc->es.size();i++)
				{
					if(overlap || pDoc->es.at(i)->isoverlap(point.x,point.y))
					{
						overlap = true;
						break;
					}
				}
				for(unsigned int i = 0;i < pDoc->is.size();i++)
				{
					if(overlap || pDoc->is.at(i)->isoverlap(point.x,point.y))
					{
						overlap = true;
						break;
					}
				}
				if(!overlap)
				{
					switch(newcomp->type)
					{
					case RE:
						pDoc->re.push_back(newcomp);
						break;
					case CA:
						pDoc->ca.push_back(newcomp);
						break;
					case LI:
						pDoc->li.push_back(newcomp);
						break;
					case ES:
					case SINV:
					case SQRV:
					case SAWV:
					case GRD:
						pDoc->es.push_back(newcomp);
						break;
					case IS:
					case SINC:
					case SQRC:
					case SAWC:
						pDoc->is.push_back(newcomp);
						break;
					case OSC:
						Osclist.push_back(newcomp);
						break;
					}
					if(newcomp->type != OSC)
					{
						pDoc->points.push_back(newcomp->lp);
						pDoc->points.push_back(newcomp->rp);
					}
					newcomp = NULL;
					isCreating = false;
					drawAll(m_pMemDC);
					Invalidate(false);
				}
			}
			else if(pselect != NULL && !islinking)
			{
				curline = NULL;
				linkpoint = pselect;
				islinking = true;
				nowlink = new line(linkpoint);
			}
			else if(pselect != NULL && islinking)
			{
				curline = NULL;
				Point * otherside;
				if(linkpoint == linkpoint->parent->lp)
					otherside = linkpoint->parent->rp;
				else
					otherside = linkpoint->parent->lp;
				Point * otherside1;
				if(pselect == pselect->parent->lp)
					otherside1 = pselect->parent->rp;
				else
					otherside1 = pselect->parent->lp;
				if(pselect->parent != linkpoint->parent && !(pselect->pnode != NULL && pselect->pnode == linkpoint->pnode) && 
					!(linkpoint->parent->type == OSC && otherside->pnode != NULL && otherside->pnode == pselect->pnode) &&
					!(pselect->parent->type == OSC && otherside1->pnode != NULL && otherside1->pnode == linkpoint->pnode) &&
					!(linkpoint->parent->type == OSC && pselect->pnode == NULL) &&
					!(pselect->parent->type == OSC && linkpoint->pnode == NULL))
				{
					Point * targetpoint = pselect;
					if(nowlink->points.back()->y != pselect->y)
					{
						Point * turnpoint = new Point(pselect->x,nowlink->points.back()->y);
						nowlink->points.push_back(turnpoint);
					}
					nowlink->points.push_back(targetpoint);
					if(pselect->parent->type != OSC && linkpoint->parent->type != OSC)
					{
						if(linkpoint->pnode == NULL && pselect->pnode == NULL)
						{
							if(linkpoint->parent->type == GRD || pselect->parent->type == GRD)
							{
								if(ground != NULL)
								{
									ground->points.push_back(linkpoint);
									ground->points.push_back(pselect);
									linkpoint->pnode = ground;
									pselect->pnode = ground;
									ground->lines.push_back(nowlink);
								}
								else
								{
									int index = pDoc->nodes.size();
									Node *newnode = new Node(index);
									newnode->points.push_back(linkpoint);
									newnode->points.push_back(pselect);

									linkpoint->pnode = newnode;
									pselect->pnode = newnode;
									newnode->lines.push_back(nowlink);
									newnode->ground = true;
									pDoc->nodes.push_back(newnode);
									ground = newnode;
								}
							}
							else
							{
								int index = pDoc->nodes.size();
								Node *newnode = new Node(index);
								newnode->points.push_back(linkpoint);
								newnode->points.push_back(pselect);

								linkpoint->pnode = newnode;
								pselect->pnode = newnode;
								newnode->lines.push_back(nowlink);
								pDoc->nodes.push_back(newnode);
							}
						}
						else if(linkpoint->pnode == NULL || pselect->pnode == NULL)
						{
							Point * detarget;
							Point * target;
							if(linkpoint->pnode == NULL)
							{
								target = pselect;
								detarget = linkpoint;
							}
							else
							{
								target = linkpoint;
								detarget = pselect;
							}
							if(target->parent->type == GRD)
							{
								target->pnode->points.push_back(detarget);
								detarget->pnode = target->pnode;
								target->pnode->lines.push_back(nowlink);
							}
							else if(target->parent->type != GRD && detarget->parent->type == GRD)
							{
								if(ground == NULL || ground == target->pnode)
								{
									target->pnode->points.push_back(detarget);
									detarget->pnode = target->pnode;
									target->pnode->lines.push_back(nowlink);
									target->pnode->ground = true;
									ground = target->pnode;
								}
								else if(ground != target->pnode)
								{
									ground->points.push_back(detarget);
									detarget->pnode = ground;
									ground->lines.push_back(nowlink);
									for(unsigned int j = 0;j < target->pnode->lines.size();j++)
									{
										ground->lines.push_back(target->pnode->lines.at(j));
									}
									for(unsigned int j = 0;j < target->pnode->points.size();j++)
									{
										target->pnode->points.at(j)->pnode = ground;
										ground->points.push_back(target->pnode->points.at(j));
									}
									for(unsigned int j = 0;j < target->pnode->junctions.size();j++)
									{
										target->pnode->junctions.at(j)->pnode = ground;
										ground->junctions.push_back(target->pnode->junctions.at(j));
									}
									target->pnode->lines.clear();
									target->pnode->points.clear();
									target->pnode->junctions.clear();
									bool isdelete = false;
									unsigned int size = pDoc->nodes.size();
									for(unsigned int k = 0;k < size;k++)
									{
										if(pDoc->nodes.at(k) == target->pnode)
										{
											pDoc->nodes.erase(pDoc->nodes.begin() + k);//删除电路节点
											size --;
											isdelete = true;//break;
										}
										if(k < size && isdelete)
										{
											pDoc->nodes.at(k)->index --;
										}
									}
								}
							}
							else
							{
								target->pnode->points.push_back(detarget);
								detarget->pnode = target->pnode;
								target->pnode->lines.push_back(nowlink);
							}
						}
						else
						{
							Node *target;
							Node *detarget;
							if(linkpoint->pnode == ground)
							{
								target = linkpoint->pnode;
								detarget = pselect->pnode;
							}
							else if(pselect->pnode == ground)
							{
								target = pselect->pnode;
								detarget = linkpoint->pnode;
							}
							else if(linkpoint->pnode->index <= pselect->pnode->index)
							{
								target = linkpoint->pnode;
								detarget = pselect->pnode;
							}
							else
							{
								target = pselect->pnode;
								detarget = linkpoint->pnode;
							}
							target->lines.push_back(nowlink);
							for(unsigned int j = 0;j < detarget->lines.size();j++)
							{
								target->lines.push_back(detarget->lines.at(j));
							}
							for(unsigned int j = 0;j < detarget->points.size();j++)
							{
								detarget->points.at(j)->pnode = target;
								target->points.push_back(detarget->points.at(j));
							}
							for(unsigned int j = 0;j < detarget->junctions.size();j++)
							{
								detarget->junctions.at(j)->pnode = target;
								target->junctions.push_back(detarget->junctions.at(j));
							}
							detarget->lines.clear();
							detarget->points.clear();
							detarget->junctions.clear();
							bool isdelete = false;
							unsigned int size = pDoc->nodes.size();
							for(unsigned int k = 0;k < size;k++)
							{
								if(pDoc->nodes.at(k) == detarget)
								{
									pDoc->nodes.erase(pDoc->nodes.begin() + k);//删除电路节点
									size --;
									isdelete = true;//break;
								}
								if(k < size && isdelete)
								{
									pDoc->nodes.at(k)->index --;
								}
							}
							//每次插入对节点进行重排
						}
						nowlink = NULL;
						islinking = false;
						linkpoint = NULL;
						drawAll(m_pMemDC);
						Invalidate(false);
					}
					else
					{
						Point * oscpoint;
						Point * deoscpoint;
						if(pselect->parent->type == OSC)
						{
							//pselect->pnode = linkpoint->pnode;
							oscpoint = pselect;
							deoscpoint = linkpoint;
						}
						else
						{
							//linkpoint->pnode = pselect->pnode;
							oscpoint = linkpoint;
							deoscpoint= pselect;
						}
						if(oscpoint == oscpoint->parent->lp)
							otherside = oscpoint->parent->rp;
						else
							otherside = oscpoint->parent->lp;
						if(oscpoint->pnode != NULL)
						{
							for(unsigned int k = 0;k < oscNode->lines.size();k++)
							{
								if(oscNode->lines.at(k)->points.back() == oscpoint || oscNode->lines.at(k)->points.front() == oscpoint)
								{
									delete oscNode->lines.at(k);
									oscNode->lines.erase(oscNode->lines.begin() + k);
									break;
								}
							}
							for(unsigned int k = 0;k < oscNode->junctions.size();k++)
							{
								if(oscNode->junctions.at(k)->pnode != otherside->pnode)
								{
									oscNode->junctions.erase(oscNode->junctions.begin() + k);
									k --;
								}
							}
						}
						oscpoint->pnode = deoscpoint->pnode;
						if(oscNode == NULL)
						{
							oscNode = new Node(-1);
						}
						oscNode->lines.push_back(nowlink);
						nowlink = NULL;
						islinking = false;
						linkpoint = NULL;
						drawAll(m_pMemDC);
						Invalidate(false);
					}

				}
				else
				{
					/*for(unsigned int k = 0;k < linklist.size();k ++)
					{
					delete linklist.at(k);
					}
					linklist.clear();*/
				}
			}
			else if(islinking)
			{
				curline = NULL;
				int offset;
				if(point.x * 10000 % int(CHECK * scale * 10000) < int(CHECK * scale * 10000) / double(2))
					offset = 0;
				else
					offset = 1;
				int rx = int((point.x * 10000 / int(CHECK * scale * 10000) + offset)* CHECK);
				if(point.y * 10000 % int(CHECK * scale * 10000) < int(CHECK * scale * 10000) / double(2))
					offset = 0;
				else
					offset = 1;
				int ry = int((point.y * 10000 / int(CHECK * scale * 10000) + offset)* CHECK);

				for(unsigned int j = 0;j < pDoc->nodes.size();j++)
				{
					for(unsigned int k = 0;k < pDoc->nodes.at(j)->lines.size();k++)
					{
						for(unsigned int i = 0;i < pDoc->nodes.at(j)->lines.at(k)->points.size() - 1;i++)
						{

							Point * ptr1 = pDoc->nodes.at(j)->lines.at(k)->points.at(i);
							Point * ptr2 = pDoc->nodes.at(j)->lines.at(k)->points.at(i + 1);
							if(rx <= max(ptr1->x,ptr2->x) && rx >= min(ptr1->x,ptr2->x) && ry <= max(ptr1->y,ptr2->y) && ry >= min(ptr1->y,ptr2->y))
							{
								Point * otherside;
								if(linkpoint == linkpoint->parent->lp)
									otherside = linkpoint->parent->rp;
								else
									otherside = linkpoint->parent->lp;
								if((pDoc->nodes.at(j)->lines.at(k)->points.at(0)->parent != linkpoint->parent && pDoc->nodes.at(j)->lines.at(k)->points.back()->parent != linkpoint->parent) && !(linkpoint != NULL && pDoc->nodes.at(j) == linkpoint->pnode) && 
									!(linkpoint->parent->type == OSC && otherside->pnode == pDoc->nodes.at(j)))
								{
									Point * targetpoint = new Point(rx,ry);							
									if(nowlink->points.back()->y != targetpoint->y)
									{
										Point * turnpoint = new Point(targetpoint->x,nowlink->points.back()->y);
										nowlink->points.push_back(turnpoint);
									}
									nowlink->points.push_back(targetpoint);
									if(linkpoint->parent->type != OSC)
									{
										targetpoint->pnode = pDoc->nodes.at(j);
										pDoc->nodes.at(j)->junctions.push_back(targetpoint);
										Node * targetnode = pDoc->nodes.at(j);
										targetnode->lines.at(k)->points.insert(targetnode->lines.at(k)->points.begin() + i + 1,targetpoint);
										line * breakline = new line(targetpoint);

										for(unsigned int n = i + 2;n < targetnode->lines.at(k)->points.size();n++)
										{
											breakline->points.push_back(targetnode->lines.at(k)->points.at(n));
										}
										int tempsize = targetnode->lines.at(k)->points.size();
										for(unsigned int n = 0;n < tempsize - i - 2;n++)
										{
											targetnode->lines.at(k)->points.pop_back();
										}
										targetnode->lines.push_back(breakline);
										if(targetnode != NULL)
										{
											if(linkpoint->pnode == NULL)
											{
												if(ground == NULL && linkpoint->parent->type == GRD)
												{
													targetnode->points.push_back(linkpoint);
													linkpoint->pnode = targetnode;
													targetnode->lines.push_back(nowlink);
													targetnode->ground = true;
													ground = targetnode;
												}
												else if(ground != NULL && ground != targetnode && linkpoint->parent->type == GRD)
												{
													ground->points.push_back(linkpoint);
													linkpoint->pnode = ground;
													ground->lines.push_back(nowlink);
													for(unsigned int j = 0;j < targetnode->lines.size();j++)
													{
														ground->lines.push_back(targetnode->lines.at(j));
													}
													for(unsigned int j = 0;j < targetnode->points.size();j++)
													{
														targetnode->points.at(j)->pnode = ground;
														ground->points.push_back(targetnode->points.at(j));
													}
													for(unsigned int j = 0;j < targetnode->junctions.size();j++)
													{
														targetnode->junctions.at(j)->pnode = ground;
														ground->junctions.push_back(targetnode->junctions.at(j));
													}
													targetnode->lines.clear();
													targetnode->points.clear();
													targetnode->junctions.clear();
													bool isdelete = false;
													unsigned int size = pDoc->nodes.size();
													for(unsigned int k = 0;k < size;k++)
													{
														if(pDoc->nodes.at(k) == targetnode)
														{
															pDoc->nodes.erase(pDoc->nodes.begin() + k);//删除电路节点
															size --;
															isdelete = true;//break;
														}
														if(k < size && isdelete)
														{
															pDoc->nodes.at(k)->index --;
														}
													}
												}
												else
												{
													targetnode->points.push_back(linkpoint);
													linkpoint->pnode = targetnode;
													targetnode->lines.push_back(nowlink);
												}
											}
											else if(linkpoint->pnode != NULL)
											{
												Node * detargetnode;
												if(ground == NULL || (ground != NULL && ground != targetnode && ground != linkpoint->pnode) || (ground != NULL && ground == targetnode))
												{
													detargetnode = linkpoint->pnode;
													targetnode->lines.push_back(nowlink);
												}
												else
												{
													Node * tempnode = targetnode;
													targetnode = linkpoint->pnode;
													detargetnode = tempnode;
													targetnode->lines.push_back(nowlink);
												}
												for(unsigned int j = 0;j < detargetnode->lines.size();j++)
												{
													targetnode->lines.push_back(detargetnode->lines.at(j));
												}
												for(unsigned int j = 0;j < detargetnode->points.size();j++)
												{
													detargetnode->points.at(j)->pnode = targetnode;
													targetnode->points.push_back(detargetnode->points.at(j));
												}
												for(unsigned int j = 0;j < detargetnode->junctions.size();j++)
												{
													detargetnode->junctions.at(j)->pnode = targetnode;
													targetnode->junctions.push_back(detargetnode->junctions.at(j));
												}
												detargetnode->lines.clear();
												detargetnode->points.clear();
												detargetnode->junctions.clear();
												bool isdelete = false;
												unsigned int size = pDoc->nodes.size();
												for(unsigned int k = 0;k < size;k++)
												{
													if(pDoc->nodes.at(k) == detargetnode)
													{
														pDoc->nodes.erase(pDoc->nodes.begin() + k);//删除电路节点
														size --;
														isdelete = true;//break;
													}
													if(k < size && isdelete)
													{
														pDoc->nodes.at(k)->index --;
													}
												}

											}
										}
										nowlink = NULL;
										islinking = false;
										linkpoint = NULL;
										drawAll(m_pMemDC);
										Invalidate(false);
										return;
									}
									else
									{
										if(linkpoint->pnode != NULL)
										{
											for(unsigned int k = 0;k < oscNode->lines.size();k++)
											{
												if(oscNode->lines.at(k)->points.back() == linkpoint || oscNode->lines.at(k)->points.front() == linkpoint)
												{
													delete oscNode->lines.at(k);
													oscNode->lines.erase(oscNode->lines.begin() + k);
													break;
												}
											}

											for(unsigned int k = 0;k < oscNode->junctions.size();k++)
											{
												if(oscNode->junctions.at(k)->pnode != otherside->pnode)
												{
													oscNode->junctions.erase(oscNode->junctions.begin() + k);
													k --;
												}
											}
										}
										linkpoint->pnode = pDoc->nodes.at(j);
										if(oscNode == NULL)
										{
											oscNode = new Node(-1);
										}
										oscNode->lines.push_back(nowlink);
										Point * newjunct = new Point(rx,ry);
										newjunct->pnode = linkpoint->pnode;
										oscNode->junctions.push_back(newjunct);
										nowlink = NULL;
										islinking = false;
										linkpoint = NULL;
										drawAll(m_pMemDC);
										Invalidate(false);
										return;
									}
								}
								else
									return;
							}

						}
					}
				}

				Point * targetpoint = new Point(rx,ry);
				if(nowlink->points.back()->y != ry)
				{
					Point * turnpoint = new Point(rx,nowlink->points.back()->y);
					nowlink->points.push_back(turnpoint);
				}
				nowlink->points.push_back(targetpoint);
			}
		}
		CScrollView::OnLButtonUp(nFlags, point);
	}

	void CCircuit_SimulationView::OnFileNew()
	{
		// TODO: 在此添加命令处理程序代码
		CCircuit_SimulationDoc *pDoc = GetDocument();
		CDC* pDC=GetDC();
		init = true;
		isplaying = false;
		if(m_pMemDC != NULL)
			m_pMemDC->DeleteDC();
		if(m_pBitmap != NULL)
			m_pBitmap->DeleteObject();
		m_pMemDC->CreateCompatibleDC(pDC);
		m_pBitmap->CreateCompatibleBitmap(pDC,MAXWIDTH * 3,MAXHEIGHT * 3);
		m_pMemDC->SelectObject(m_pBitmap);
		m_pMemDC->FillSolidRect(0, 0,MAXWIDTH * 3,MAXHEIGHT * 3,RGB(255,255,255));
		ground = NULL;
		pDoc->re.clear();
		pDoc->ca.clear();
		pDoc->li.clear();
		pDoc->es.clear();
		pDoc->is.clear();
		pDoc->points.clear();
		pDoc->nodes.clear();
		delete newcomp;
		newcomp = NULL;
		delete rectangle;
		rectangle = NULL;
		delete startpos;
		startpos = NULL;
		delete startmouse;
		startmouse = NULL;
		if(nowlink != NULL)
		{
			for(unsigned int k = 1;k < nowlink->points.size();k ++)
			{
				delete nowlink->points.at(k);
			}
			delete nowlink;
			nowlink= NULL;
		}
		pselect = NULL;
		linkpoint = NULL;
		curline = NULL;
		Osclist.clear();
		oscNode = NULL;
		isCreating = false;
		islinking = false;
		isdragging = false;
		isscrolling = false;
		lbuttondown = false;
		scale = 1;
		drawAll(m_pMemDC);
		Invalidate(false);
	}

	void CCircuit_SimulationView::drawAll(CDC * pDC)
	{
		CCircuit_SimulationDoc *pDoc = GetDocument();
		XFORM xForm =  
		{ 
			1.0f, 0.0f, 
			0.0f, 1.0f,
			0.0f, 0.0f
		};
		xForm.eM11 = scale;
		xForm.eM22 = scale;
		if(pDC != NULL)
		{
			pDC->SetGraphicsMode(GM_ADVANCED);
			if(isCreating || isdragging || islinking)
			{
				CRect rect;
				GetWindowRect(&rect);
				int cx,cy;
				cx = GetScrollPos(SB_HORZ);
				cy = GetScrollPos(SB_VERT);
				pDC->FillSolidRect(cx - Component::length,cy - Component::length,rect.Width() + Component::length * 2,rect.Height() + Component::length * 2,RGB(255,255,255));
			}
			else
				pDC->FillSolidRect(0,0,MAXWIDTH * scale,MAXHEIGHT * scale,RGB(255,255,255));
			pDC->SetWorldTransform(&xForm);
			//m_pMemDC->FillSolidRect(0, 0,MAXWIDTH,MAXHEIGHT,RGB(255,255,255));
			for(unsigned int i = 0;i < pDoc->re.size();i++)
			{
				pDoc->re.at(i)->draw(m_pMemDC);
			}
			for(unsigned int i = 0;i < pDoc->ca.size();i++)
			{
				pDoc->ca.at(i)->draw(m_pMemDC);
			}
			for(unsigned int i = 0;i < pDoc->li.size();i++)
			{
				pDoc->li.at(i)->draw(m_pMemDC);
			}
			for(unsigned int i = 0;i < pDoc->es.size();i++)
			{
				pDoc->es.at(i)->draw(m_pMemDC);
			}
			for(unsigned int i = 0;i < pDoc->is.size();i++)
			{
				pDoc->is.at(i)->draw(m_pMemDC);
			}
			for(unsigned int i = 0;i < Osclist.size();i++)
			{
				Osclist.at(i)->draw(m_pMemDC);
			}
			for(unsigned int i = 0;i < pDoc->nodes.size();i++)
			{
				for(unsigned int j = 0;j < pDoc->nodes.at(i)->lines.size();j++)
				{
					drawline(pDoc->nodes.at(i)->lines.at(j),m_pMemDC);
				}
				for(unsigned int j = 0;j < pDoc->nodes.at(i)->junctions.size();j++)
				{
					drawjunct(pDoc->nodes.at(i)->junctions.at(j),m_pMemDC);
				}
			}
			if(oscNode != NULL)
			{
				for(unsigned int i = 0;i < oscNode->lines.size();i++)
				{
					drawline(oscNode->lines.at(i),m_pMemDC);
				}
				for(unsigned int i = 0;i < oscNode->junctions.size();i++)
				{
					drawjunct(oscNode->junctions.at(i),m_pMemDC);
				}
			}
			if(highlight != NULL)
			{
				drawRect(rectangle,m_pMemDC);
			}
			if(curline != NULL)
			{
				drawsqr(curline,m_pMemDC);
			}
			xForm.eM11 = 1.0f;
			xForm.eM22 = 1.0f;
			pDC->SetWorldTransform(&xForm);
		}
	}

	void CCircuit_SimulationView::linkLine(int cx, int cy, CDC * pDC)
	{
		CPen *pe = new CPen(PS_SOLID,1,RGB(0,0,0));
		CPen * oldpen =  pDC->SelectObject(pe);
		if(nowlink != NULL)
		{
			XFORM xForm =  
			{ 
				1.0f, 0.0f, 
				0.0f, 1.0f,
				0.0f, 0.0f
			};
			xForm.eM11 = scale;
			xForm.eM22 = scale;
			pDC->SetWorldTransform(&xForm);

			pDC->MoveTo(nowlink->points.at(0)->x,nowlink->points.at(0)->y);
			for(unsigned int i = 0;i < nowlink->points.size();i++)
			{
				pDC->LineTo(nowlink->points.at(i)->x,nowlink->points.at(i)->y);
			}
			pDC->LineTo(cx,nowlink->points.back()->y);
			pDC->LineTo(cx,cy);
			xForm.eM11 = 1.0f;
			xForm.eM22 = 1.0f;
			pDC->SetWorldTransform(&xForm);
		}

		pDC->SelectObject(oldpen);
		pe->DeleteObject();
	}

	void CCircuit_SimulationView::drawline(line * l, CDC * pDC)
	{
		CPen *pe = new CPen(PS_SOLID,2,RGB(255,0,0));
		CPen * oldpen =  pDC->SelectObject(pe);
		pDC->MoveTo(l->points.at(0)->x,l->points.at(0)->y);
		for(unsigned int i = 1;i < l->points.size();i ++)
		{
			pDC->LineTo(l->points.at(i)->x,l->points.at(i)->y);
		}
		pDC->SelectObject(oldpen);
		pe->DeleteObject();
	}


	void CCircuit_SimulationView::drawjunct(Point * JUNCTION, CDC * pDC)
	{
		CPen *pe = new CPen(PS_SOLID,1,RGB(255,0,0));
		CPen * oldpen =  pDC->SelectObject(pe);
		CBrush *br = new CBrush(RGB(255,0,0));
		CBrush * oldbrush =  pDC->SelectObject(br);
		if(JUNCTION != NULL)
		{
			pDC->Ellipse(JUNCTION->x - 2,JUNCTION->y - 2,JUNCTION->x + 2,JUNCTION->y + 2);
		}

		pDC->SelectObject(oldbrush);
		br->DeleteObject();
		pDC->SelectObject(oldpen);
		pe->DeleteObject();
	}


	void CCircuit_SimulationView::OnReverse()
	{
		// TODO: 在此添加命令处理程序代码
		if(isCreating == true && newcomp != NULL && newcomp->type != GRD)
		{
			newcomp->reverse = !newcomp->reverse;
			//newcomp->draw(m_pMemDC);
			//Invalidate(false);
		}
		else if(highlight != NULL && highlight->type != GRD && highlight->lp->pnode == NULL && highlight->rp->pnode == NULL)
		{
			highlight->reverse = !highlight->reverse;
			drawAll(m_pMemDC);
			Invalidate(false);
		}
	}


	void CCircuit_SimulationView::OnReNew()
	{
		// TODO: 在此添加命令处理程序代码
		highlight = NULL;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		CDialogNew newdlg(RE);
		if(IDOK == newdlg.DoModal())
		{
			CString unit = newdlg.m_Unit;
			CString info = newdlg.m_Text + unit;
			double val = _ttof(newdlg.m_Text);		
			unitConvert(val,unit.Left(1));
			int index = -1;
			if(pDoc->re.size() != 0)
			{
				index = _ttoi(pDoc->re.back()->label.Mid(1));
			}
			CString label;
			label.Format(TEXT("%d"),++index);
			label = L"R" + label;
			isCreating = true;
			newcomp = new Component(RE,label,info,val);
		}
	}


	void CCircuit_SimulationView::OnLiNew()
	{
		// TODO: 在此添加命令处理程序代码
		highlight = NULL;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		CDialogNew newdlg(LI);
		if(IDOK == newdlg.DoModal())
		{
			CString unit = newdlg.m_Unit;
			CString info = newdlg.m_Text + unit;
			double val = _ttof(newdlg.m_Text);		
			unitConvert(val,unit.Left(1));
			int index = -1;
			if(pDoc->li.size() != 0)
			{
				index = _ttoi(pDoc->li.back()->label.Mid(1));
			}
			CString label;
			label.Format(TEXT("%d"),++index);
			label = L"L" + label;
			isCreating = true;
			newcomp = new Component(LI,label,info,val);
		}
	}


	void CCircuit_SimulationView::OnCaNew()
	{
		// TODO: 在此添加命令处理程序代码
		highlight = NULL;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		CDialogNew newdlg(CA);
		if(IDOK == newdlg.DoModal())
		{
			CString unit = newdlg.m_Unit;
			CString info = newdlg.m_Text + unit;
			double val = _ttof(newdlg.m_Text);		
			unitConvert(val,unit.Left(1));
			int index = -1;
			if(pDoc->ca.size() != 0)
			{
				index = _ttoi(pDoc->ca.back()->label.Mid(1));
			}
			CString label;
			label.Format(TEXT("%d"),++index);
			label = L"C" + label;
			isCreating = true;
			newcomp = new Component(CA,label,info,val);
		}
	}


	void CCircuit_SimulationView::OnEsNew()
	{
		// TODO: 在此添加命令处理程序代码
		highlight = NULL;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		CDialogNew newdlg(ES);
		if(IDOK == newdlg.DoModal())
		{
			CString unit = newdlg.m_Unit;
			CString info = newdlg.m_Text + unit;
			double val = _ttof(newdlg.m_Text);	
			unitConvert(val,unit.Left(1));
			int index = -1;
			if(pDoc->es.size() != 0)
			{
				index = _ttoi(pDoc->es.back()->label.Mid(1));
			}
			CString label;
			label.Format(TEXT("%d"),++index);
			label = L"E" + label;
			isCreating = true;
			newcomp = new Component(ES,label,info,val);
			newcomp->lp->positive = true;
		}
	}


	void CCircuit_SimulationView::OnIsNew()
	{
		// TODO: 在此添加命令处理程序代码
		highlight = NULL;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		CDialogNew newdlg(IS);
		if(IDOK == newdlg.DoModal())
		{
			CString unit = newdlg.m_Unit;
			CString info = newdlg.m_Text + unit;
			double val = _ttof(newdlg.m_Text);	
			unitConvert(val,unit.Left(1));
			int index = -1;
			if(pDoc->is.size() != 0)
			{
				index = _ttoi(pDoc->is.back()->label.Mid(1));
			}
			CString label;
			label.Format(TEXT("%d"),++index);
			label = L"I" + label;
			isCreating = true;
			newcomp = new Component(IS,label,info,val);
			newcomp->lp->positive = true;
		}
	}

	void CCircuit_SimulationView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		point += this->GetScrollPosition();
		lbuttondown = true;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		int offset;
		if(point.x * 10000 % int(CHECK * scale * 10000) < int(CHECK * scale * 10000) / double(2))
			offset = 0;
		else
			offset = 1;
		int rx = int((point.x * 10000 / int(CHECK * scale * 10000) + offset)* CHECK);
		if(point.y * 10000 % int(CHECK * scale * 10000) < int(CHECK * scale * 10000) / double(2))
			offset = 0;
		else
			offset = 1;
		int ry = int((point.y * 10000 / int(CHECK * scale * 10000) + offset)* CHECK);
		if(!isCreating && !islinking && pselect == NULL)
		{
			if(toHighlight(rx,ry) == false)
			{
				highlight = NULL;
				delete rectangle;
				rectangle = NULL;
				if(toLsegment(rx,ry) == false)
				{
					curline = NULL;
				}

				drawAll(m_pMemDC);
				Invalidate(false);
				return;
			}
			else
			{
				delete startmouse;
				startmouse = new Point(rx,ry);
				delete startpos;
				startpos = new Point(highlight->x,highlight->y);
				return;
			}
		}
		CScrollView::OnLButtonDown(nFlags, point);
	}

	void CCircuit_SimulationView::unitConvert(double &VAL, CString UNIT)
	{
		if(UNIT == L"f")
		{
			VAL = VAL / 1000000000000000;
		}
		else if(UNIT == L"p")
		{
			VAL = VAL / 1000000000000;
		}
		else if(UNIT == L"n")
		{
			VAL = VAL / 1000000000;
		}
		else if(UNIT == L"μ")
		{
			VAL = VAL / 1000000;
		}
		else if(UNIT == L"m")
		{
			VAL = VAL / 1000;
		}
		else if(UNIT == L"k")
		{
			VAL = VAL * 1000;
		}
		else if(UNIT == L"M")
		{
			VAL = VAL * 1000000;
		}
		else if(UNIT == L"G")
		{
			VAL = VAL * 1000000000;
		}
	}


	void CCircuit_SimulationView::drawRect(line * RECT, CDC * pDC)
	{
		if(RECT != NULL)
		{
			CPen *pe = new CPen(PS_DASH,1,RGB(0,0,255));
			CPen * oldpen =  pDC->SelectObject(pe);
			pDC->MoveTo(RECT->points.at(0)->x,RECT->points.at(0)->y);
			pDC->LineTo(RECT->points.at(1)->x,RECT->points.at(0)->y);
			pDC->LineTo(RECT->points.at(1)->x,RECT->points.at(1)->y);
			pDC->LineTo(RECT->points.at(0)->x,RECT->points.at(1)->y);
			pDC->LineTo(RECT->points.at(0)->x,RECT->points.at(0)->y);
			pDC->SelectObject(oldpen);
			pe->DeleteObject();
		}
	}


	bool CCircuit_SimulationView::toHighlight(int cx, int cy)
	{
		CCircuit_SimulationDoc *pDoc = GetDocument();
		CClientDC dc(this);
		for(unsigned int i = 0;i < pDoc->re.size();i++)
		{			
			CSize size1 = dc.GetTextExtent(pDoc->re.at(i)->label);
			CSize size2 = dc.GetTextExtent(pDoc->re.at(i)->info);
			if(!pDoc->re.at(i)->reverse)
			{
				int lrectx = min(pDoc->re.at(i)->x - Component::length / 2,min(pDoc->re.at(i)->labelx - size1.cx / 2,pDoc->re.at(i)->infox - size2.cx / 2)) - Component::length / 6;
				int rrectx = max(pDoc->re.at(i)->x + Component::length / 2,max(pDoc->re.at(i)->labelx + size1.cx / 2,pDoc->re.at(i)->infox + size2.cx / 2)) + Component::length / 6;
				int trecty = min(pDoc->re.at(i)->y - Component::length / 4,min(pDoc->re.at(i)->labely  - Component::length /4 - size1.cy,pDoc->re.at(i)->infoy  + Component::length /4));
				int brecty = max(pDoc->re.at(i)->y + Component::length / 4,max(pDoc->re.at(i)->labely  - Component::length /4,pDoc->re.at(i)->infoy  + Component::length /4 + size2.cy));
				if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
				{
					if(highlight != pDoc->re.at(i))
					{
						highlight = pDoc->re.at(i);
						delete rectangle;
						rectangle = new line(new Point(lrectx,trecty));
						rectangle->points.push_back(new Point(rrectx,brecty));
						drawAll(m_pMemDC);
						Invalidate(false);
						return true;
					}
					else
						return true;
				}
			}
			else
			{
				int lrectx = min(pDoc->re.at(i)->x - Component::length / 4,min(pDoc->re.at(i)->labelx  + Component::length / 4,pDoc->re.at(i)->infox + Component::length / 4));
				int rrectx = max(pDoc->re.at(i)->x + Component::length / 4,max(pDoc->re.at(i)->labelx  + Component::length / 4 + size1.cx,pDoc->re.at(i)->infox + Component::length / 4 + size2.cx));
				int trecty = min(pDoc->re.at(i)->y - Component::length / 2,min(pDoc->re.at(i)->labely  - Component::length /4 - size1.cy,pDoc->re.at(i)->infoy - size2.cy)) - Component::length / 6;
				int brecty = max(pDoc->re.at(i)->y + Component::length / 2,max(pDoc->re.at(i)->labely  - Component::length /4,pDoc->re.at(i)->infoy)) + Component::length / 6;
				if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
				{
					if(highlight != pDoc->re.at(i))
					{
						highlight = pDoc->re.at(i);
						delete rectangle;
						rectangle = new line(new Point(lrectx,trecty));
						rectangle->points.push_back(new Point(rrectx,brecty));
						drawAll(m_pMemDC);
						Invalidate(false);
						return true;
					}
					else
						return true;
				}
			}
		}
		for(unsigned int i = 0;i < pDoc->ca.size();i++)
		{		
			CSize size1 = dc.GetTextExtent(pDoc->ca.at(i)->label);
			CSize size2 = dc.GetTextExtent(pDoc->ca.at(i)->info);
			if(!pDoc->ca.at(i)->reverse)
			{
				int lrectx = min(pDoc->ca.at(i)->x - Component::length / 2,min(pDoc->ca.at(i)->labelx - size1.cx / 2,pDoc->ca.at(i)->infox - size2.cx / 2)) - Component::length / 6;
				int rrectx = max(pDoc->ca.at(i)->x + Component::length / 2,max(pDoc->ca.at(i)->labelx + size1.cx / 2,pDoc->ca.at(i)->infox + size2.cx / 2)) + Component::length / 6;
				int trecty = min(pDoc->ca.at(i)->y - Component::length / 4,min(pDoc->ca.at(i)->labely  - Component::length /4 - size1.cy,pDoc->ca.at(i)->infoy  + Component::length /4));
				int brecty = max(pDoc->ca.at(i)->y + Component::length / 4,max(pDoc->ca.at(i)->labely  - Component::length /4,pDoc->ca.at(i)->infoy  + Component::length /4 + size2.cy));
				if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
				{
					if(highlight != pDoc->ca.at(i))
					{
						highlight = pDoc->ca.at(i);
						delete rectangle;
						rectangle = new line(new Point(lrectx,trecty));
						rectangle->points.push_back(new Point(rrectx,brecty));
						drawAll(m_pMemDC);
						Invalidate(false);
						return true;
					}
					else
						return true;
				}
			}
			else
			{
				int lrectx = min(pDoc->ca.at(i)->x - Component::length / 4,min(pDoc->ca.at(i)->labelx  + Component::length / 4,pDoc->ca.at(i)->infox + Component::length / 4));
				int rrectx = max(pDoc->ca.at(i)->x + Component::length / 4,max(pDoc->ca.at(i)->labelx  + Component::length / 4 + size1.cx,pDoc->ca.at(i)->infox + Component::length / 4 + size2.cx));
				int trecty = min(pDoc->ca.at(i)->y - Component::length / 2,min(pDoc->ca.at(i)->labely  - Component::length /4 - size1.cy,pDoc->ca.at(i)->infoy - size2.cy)) - Component::length / 6;
				int brecty = max(pDoc->ca.at(i)->y + Component::length / 2,max(pDoc->ca.at(i)->labely  - Component::length /4,pDoc->ca.at(i)->infoy)) + Component::length / 6;
				if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
				{
					if(highlight != pDoc->ca.at(i))
					{
						highlight = pDoc->ca.at(i);
						delete rectangle;
						rectangle = new line(new Point(lrectx,trecty));
						rectangle->points.push_back(new Point(rrectx,brecty));
						drawAll(m_pMemDC);
						Invalidate(false);
						return true;
					}
					else
						return true;
				}
			}
		}
		for(unsigned int i = 0;i < pDoc->li.size();i++)
		{		
			CSize size1 = dc.GetTextExtent(pDoc->li.at(i)->label);
			CSize size2 = dc.GetTextExtent(pDoc->li.at(i)->info);
			if(!pDoc->li.at(i)->reverse)
			{
				int lrectx = min(pDoc->li.at(i)->x - Component::length / 2,min(pDoc->li.at(i)->labelx - size1.cx / 2,pDoc->li.at(i)->infox - size2.cx / 2)) - Component::length / 6;
				int rrectx = max(pDoc->li.at(i)->x + Component::length / 2,max(pDoc->li.at(i)->labelx + size1.cx / 2,pDoc->li.at(i)->infox + size2.cx / 2)) + Component::length / 6;
				int trecty = min(pDoc->li.at(i)->y - Component::length / 4,min(pDoc->li.at(i)->labely  - Component::length /4 - size1.cy,pDoc->li.at(i)->infoy  + Component::length /4));
				int brecty = max(pDoc->li.at(i)->y + Component::length / 4,max(pDoc->li.at(i)->labely  - Component::length /4,pDoc->li.at(i)->infoy  + Component::length /4 + size2.cy));
				if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
				{
					if(highlight != pDoc->li.at(i))
					{
						highlight = pDoc->li.at(i);
						delete rectangle;
						rectangle = new line(new Point(lrectx,trecty));
						rectangle->points.push_back(new Point(rrectx,brecty));
						drawAll(m_pMemDC);
						Invalidate(false);
						return true;
					}
					else
						return true;
				}
			}
			else
			{
				int lrectx = min(pDoc->li.at(i)->x - Component::length / 4,min(pDoc->li.at(i)->labelx  + Component::length / 4,pDoc->li.at(i)->infox + Component::length / 4));
				int rrectx = max(pDoc->li.at(i)->x + Component::length / 4,max(pDoc->li.at(i)->labelx  + Component::length / 4 + size1.cx,pDoc->li.at(i)->infox + Component::length / 4 + size2.cx));
				int trecty = min(pDoc->li.at(i)->y - Component::length / 2,min(pDoc->li.at(i)->labely  - Component::length /4 - size1.cy,pDoc->li.at(i)->infoy - size2.cy)) - Component::length / 6;
				int brecty = max(pDoc->li.at(i)->y + Component::length / 2,max(pDoc->li.at(i)->labely  - Component::length /4,pDoc->li.at(i)->infoy)) + Component::length / 6;
				if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
				{
					if(highlight != pDoc->li.at(i))
					{
						highlight = pDoc->li.at(i);
						delete rectangle;
						rectangle = new line(new Point(lrectx,trecty));
						rectangle->points.push_back(new Point(rrectx,brecty));
						drawAll(m_pMemDC);
						Invalidate(false);
						return true;
					}
					else
						return true;
				}
			}
		}
		for(unsigned int i = 0;i < pDoc->es.size();i++)
		{	
			CSize size1 = dc.GetTextExtent(pDoc->es.at(i)->label);
			CSize size2 = dc.GetTextExtent(pDoc->es.at(i)->info);
			if(!pDoc->es.at(i)->reverse)
			{
				int lrectx = min(pDoc->es.at(i)->x - Component::length / 2,min(pDoc->es.at(i)->labelx - size1.cx / 2,pDoc->es.at(i)->infox - size2.cx / 2)) - Component::length / 6;
				int rrectx = max(pDoc->es.at(i)->x + Component::length / 2,max(pDoc->es.at(i)->labelx + size1.cx / 2,pDoc->es.at(i)->infox + size2.cx / 2)) + Component::length / 6;
				int trecty = min(pDoc->es.at(i)->y - Component::length / 4,min(pDoc->es.at(i)->labely  - Component::length /4 - size1.cy,pDoc->es.at(i)->infoy  + Component::length /4));
				int brecty = max(pDoc->es.at(i)->y + Component::length / 4,max(pDoc->es.at(i)->labely  - Component::length /4,pDoc->es.at(i)->infoy  + Component::length /4 + size2.cy));
				if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
				{
					if(highlight != pDoc->es.at(i))
					{
						highlight = pDoc->es.at(i);
						delete rectangle;
						rectangle = new line(new Point(lrectx,trecty));
						rectangle->points.push_back(new Point(rrectx,brecty));
						drawAll(m_pMemDC);
						Invalidate(false);
						return true;
					}
					else
						return true;
				}
			}
			else
			{
				int lrectx = min(pDoc->es.at(i)->x - Component::length / 4,min(pDoc->es.at(i)->labelx  + Component::length / 4,pDoc->es.at(i)->infox + Component::length / 4));
				int rrectx = max(pDoc->es.at(i)->x + Component::length / 4,max(pDoc->es.at(i)->labelx  + Component::length / 4 + size1.cx,pDoc->es.at(i)->infox + Component::length / 4 + size2.cx));
				int trecty = min(pDoc->es.at(i)->y - Component::length / 2,min(pDoc->es.at(i)->labely  - Component::length /4 - size1.cy,pDoc->es.at(i)->infoy - size2.cy)) - Component::length / 6;
				int brecty = max(pDoc->es.at(i)->y + Component::length / 2,max(pDoc->es.at(i)->labely  - Component::length /4,pDoc->es.at(i)->infoy)) + Component::length / 6;
				if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
				{
					if(highlight != pDoc->es.at(i))
					{
						highlight = pDoc->es.at(i);
						delete rectangle;
						rectangle = new line(new Point(lrectx,trecty));
						rectangle->points.push_back(new Point(rrectx,brecty));
						drawAll(m_pMemDC);
						Invalidate(false);
						return true;
					}
					else
						return true;
				}
			}
		}
		for(unsigned int i = 0;i < pDoc->is.size();i++)
		{		
			CSize size1 = dc.GetTextExtent(pDoc->is.at(i)->label);
			CSize size2 = dc.GetTextExtent(pDoc->is.at(i)->info);
			if(!pDoc->is.at(i)->reverse)
			{
				int lrectx = min(pDoc->is.at(i)->x - Component::length / 2,min(pDoc->is.at(i)->labelx - size1.cx / 2,pDoc->is.at(i)->infox - size2.cx / 2)) - Component::length / 6;
				int rrectx = max(pDoc->is.at(i)->x + Component::length / 2,max(pDoc->is.at(i)->labelx + size1.cx / 2,pDoc->is.at(i)->infox + size2.cx / 2)) + Component::length / 6;
				int trecty = min(pDoc->is.at(i)->y - Component::length / 4,min(pDoc->is.at(i)->labely  - Component::length /4 - size1.cy,pDoc->is.at(i)->infoy  + Component::length /4));
				int brecty = max(pDoc->is.at(i)->y + Component::length / 4,max(pDoc->is.at(i)->labely  - Component::length /4,pDoc->is.at(i)->infoy  + Component::length /4 + size2.cy));
				if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
				{
					if(highlight != pDoc->is.at(i))
					{
						highlight = pDoc->is.at(i);
						delete rectangle;
						rectangle = new line(new Point(lrectx,trecty));
						rectangle->points.push_back(new Point(rrectx,brecty));
						drawAll(m_pMemDC);
						Invalidate(false);
						return true;
					}
					else
						return true;
				}
			}
			else
			{
				int lrectx = min(pDoc->is.at(i)->x - Component::length / 4,min(pDoc->is.at(i)->labelx  + Component::length / 4,pDoc->is.at(i)->infox + Component::length / 4));
				int rrectx = max(pDoc->is.at(i)->x + Component::length / 4,max(pDoc->is.at(i)->labelx  + Component::length / 4 + size1.cx,pDoc->is.at(i)->infox + Component::length / 4 + size2.cx));
				int trecty = min(pDoc->is.at(i)->y - Component::length / 2,min(pDoc->is.at(i)->labely  - Component::length /4 - size1.cy,pDoc->is.at(i)->infoy - size2.cy)) - Component::length / 6;
				int brecty = max(pDoc->is.at(i)->y + Component::length / 2,max(pDoc->is.at(i)->labely  - Component::length /4,pDoc->is.at(i)->infoy)) + Component::length / 6;
				if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
				{
					if(highlight != pDoc->is.at(i))
					{
						highlight = pDoc->is.at(i);
						delete rectangle;
						rectangle = new line(new Point(lrectx,trecty));
						rectangle->points.push_back(new Point(rrectx,brecty));
						drawAll(m_pMemDC);
						Invalidate(false);
						return true;
					}
					else
						return true;
				}
			}
		}

		for(unsigned int i = 0;i < Osclist.size();i++)
		{			
			CSize size1 = dc.GetTextExtent(Osclist.at(i)->label);
			CSize size2 = dc.GetTextExtent(Osclist.at(i)->info);
			int lrectx = min(Osclist.at(i)->x - Component::length,min(Osclist.at(i)->labelx - size1.cx / 2,Osclist.at(i)->infox - size2.cx / 2)) - Component::length / 6;
			int rrectx = max(Osclist.at(i)->x + Component::length *9 / 4,max(Osclist.at(i)->labelx + size1.cx / 2,Osclist.at(i)->infox + size2.cx / 2)) + Component::length / 6;
			int trecty = min(Osclist.at(i)->y - Component::length * 11 / 4,min(Osclist.at(i)->labely  - Component::length /4 - size1.cy,Osclist.at(i)->infoy  + Component::length /4));
			int brecty = max(Osclist.at(i)->y + Component::length / 3,max(Osclist.at(i)->labely  - Component::length /4,Osclist.at(i)->infoy  + Component::length /4 + size2.cy));
			if(cx < rrectx	&& cx > lrectx	&& cy < brecty	&& cy > trecty)
			{
				if(highlight != Osclist.at(i))
				{
					highlight = Osclist.at(i);
					delete rectangle;
					rectangle = new line(new Point(lrectx,trecty));
					rectangle->points.push_back(new Point(rrectx,brecty));
					drawAll(m_pMemDC);
					Invalidate(false);
					return true;
				}
				else
					return true;
			}
		}
		return false;
	}


	BOOL CCircuit_SimulationView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		ScreenToClient(&pt);
		pt += this->GetScrollPosition();
		CCircuit_SimulationDoc *pDoc = GetDocument();
		static float upLimit = 2.0f;
		static float downLinit = 0.6f;
		static float fUp = 1.25f;
		static float fDown = 0.8f;
		float prescale = scale;
		if(zDelta > 0 && scale < upLimit)
		{
			scale *= fUp;
		}
		else if(zDelta < 0 && scale > downLinit)
		{
			scale *= fDown;
		}	

		drawAll(m_pMemDC);		
		int cx,cy;
		cx = GetScrollPos(SB_HORZ);
		cy = GetScrollPos(SB_VERT);
		float xratio = pt.x / (MAXWIDTH * prescale);
		float yratio= pt.y / (MAXHEIGHT * prescale);
		CSize sizeTotal(MAXWIDTH * scale,MAXHEIGHT * scale);
		SetScrollSizes(MM_TEXT,sizeTotal);	
		SetScrollPos(SB_HORZ,xratio * MAXWIDTH * scale - (pt.x - cx));
		SetScrollPos(SB_VERT,yratio * MAXHEIGHT * scale - (pt.y - cy));
		this->Invalidate(false);
		return true;//CScrollView::OnMouseWheel(nFlags, zDelta, pt);
	}


	void CCircuit_SimulationView::OnMButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值

		isscrolling = true;
		if(nowlink != NULL)
		{
			for(unsigned int k = 1;k < nowlink->points.size();k ++)
			{
				delete nowlink->points.at(k);
			}
			delete nowlink;
			nowlink= NULL;
			islinking = false;

		}
		if(isdragging)
		{
			isdragging = false;
			highlight = NULL;

			lbuttondown = false;
			delete startpos;
			startpos = NULL;
			delete startmouse;
			startmouse = NULL;
		}
		if(isCreating)
		{
			isCreating = false;
			delete newcomp;
			newcomp = NULL;
		}
		startmouse = new Point(point.x,point.y);
		drawAll(m_pMemDC);
		Invalidate(false);
		point += this->GetScrollPosition();
		CScrollView::OnMButtonDown(nFlags, point);
	}


	void CCircuit_SimulationView::OnMButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		point += this->GetScrollPosition();
		isscrolling = false;
		delete startmouse;
		startmouse = NULL;
		CScrollView::OnMButtonUp(nFlags, point);
	}


	void CCircuit_SimulationView::OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		if(highlight != NULL)
		{
			if(highlight->type <= IS)
			{
				CCircuit_SimulationDoc *pDoc = GetDocument();
				CDialogNew newdlg(highlight->type);
				if(IDOK == newdlg.DoModal())
				{
					CString unit = newdlg.m_Unit;
					CString info = newdlg.m_Text + unit;
					double val = _ttof(newdlg.m_Text);		
					unitConvert(val,unit.Left(1));
					highlight->value = val;
					highlight->info = info;
					drawAll(m_pMemDC);
					Invalidate(false);
				}
			}
			else if(highlight->type <= SAWC)
			{
				CCircuit_SimulationDoc *pDoc = GetDocument();
				CDialogEdit newdlg(highlight->type);
				if(IDOK == newdlg.DoModal())
				{
					CString unit1 = newdlg.m_Unit1;
					CString unit2 = newdlg.m_Unit2;
					CString info = newdlg.m_Freq + unit1;
					CString info1 = newdlg.m_Max + unit2;
					info = info1 + L"  " + info;
					double freq = _ttof(newdlg.m_Freq);	
					unitConvert(freq,unit1.Left(1));
					double val = _ttof(newdlg.m_Max);	
					unitConvert(val,unit2.Left(1));
					highlight->value = val;
					highlight->frequency = freq;
					highlight->info = info;
					drawAll(m_pMemDC);
					Invalidate(false);
				}
			}
			else if(highlight->type == OSC && isplaying)
			{
				CCircuit_SimulationDoc *pDoc = GetDocument();
				CDialogOsc newdlg;
				if(IDOK == newdlg.DoModal())
				{
					CString type = newdlg.m_type;
					if(type == L"电压")
					{
					}
					else if(type == L"电流")
					{
					}
					else if(type == L"幅频特性")
					{
					}
					else if(type == L"相频特性")
					{
					}
				}
			}
		}
		CScrollView::OnLButtonDblClk(nFlags, point);
	}


	bool CCircuit_SimulationView::toLsegment(int cx, int cy)
	{
		CCircuit_SimulationDoc *pDoc = GetDocument();
		CClientDC dc(this);
		for(unsigned int i = 0;i < pDoc->nodes.size();i++)
		{
			for(unsigned int j = 0;j < pDoc->nodes.at(i)->lines.size();j++)
			{
				for(unsigned int k = 0;k < pDoc->nodes.at(i)->lines.at(j)->points.size() - 1;k++)
				{
					Point * ptr1 = pDoc->nodes.at(i)->lines.at(j)->points.at(k);
					Point * ptr2 = pDoc->nodes.at(i)->lines.at(j)->points.at(k + 1);
					if(cx <= max(ptr1->x,ptr2->x) && cx >= min(ptr1->x,ptr2->x) && cy <= max(ptr1->y,ptr2->y) && cy >= min(ptr1->y,ptr2->y))
					{
						curline = pDoc->nodes.at(i)->lines.at(j);
						return true;
					}
				}
			}
		}
		return false;
	}

	void CCircuit_SimulationView::drawsqr(line * lineptr, CDC * pDC)
	{
		CPen *pe = new CPen(PS_SOLID,1,RGB(0,0,255));
		CPen * oldpen =  pDC->SelectObject(pe);
		CBrush *br = new CBrush(RGB(0,0,255));
		CBrush * oldbrush =  pDC->SelectObject(br);
		if(lineptr != NULL)
		{
			for(unsigned int i = 0;i < lineptr->points.size();i ++)
			{
				pDC->Rectangle(lineptr->points.at(i)->x - CHECK / 2,lineptr->points.at(i)->y - CHECK / 2,lineptr->points.at(i)->x + CHECK / 2,lineptr->points.at(i)->y + CHECK / 2);
			}
		}

		pDC->SelectObject(oldbrush);
		br->DeleteObject();
		pDC->SelectObject(oldpen);
		pe->DeleteObject();
	}


	void CCircuit_SimulationView::OnSignalNew()
	{
		// TODO: 在此添加命令处理程序代码
		highlight = NULL;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		CDialogSig newdlg(true);
		if(IDOK == newdlg.DoModal())
		{
			CString unit1 = newdlg.m_Unit1;
			CString info = newdlg.m_Freq + unit1;
			double freq = _ttof(newdlg.m_Freq);	
			unitConvert(freq,unit1.Left(1));
			CString unit2 = newdlg.m_Unit2;
			CString info1 = newdlg.m_Max + unit2;
			info = info1 + L"  " + info;
			double val = _ttof(newdlg.m_Max);	
			unitConvert(val,unit2.Left(1));
			int type = newdlg.type;
			int index = -1;
			if(pDoc->es.size() != 0)
			{
				index = _ttoi(pDoc->es.back()->label.Mid(1));
			}
			CString label;
			label.Format(TEXT("%d"),++index);
			label = L"E" + label;
			isCreating = true;
			newcomp = new Component(type,label,info,val,freq);
			newcomp->lp->positive = true;
		}
	}

	void CCircuit_SimulationView::OnSignalcNew()
	{
		// TODO: 在此添加命令处理程序代码
		highlight = NULL;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		CDialogSig newdlg(false);
		if(IDOK == newdlg.DoModal())
		{
			CString unit1 = newdlg.m_Unit1;
			CString info = newdlg.m_Freq + unit1;
			double freq = _ttof(newdlg.m_Freq);	
			unitConvert(freq,unit1.Left(1));
			CString unit2 = newdlg.m_Unit2;
			CString info1 = newdlg.m_Max + unit2;
			info = info1 + L"  " + info;
			double val = _ttof(newdlg.m_Max);	
			unitConvert(val,unit2.Left(1));
			int type = newdlg.type;
			int index = -1;
			if(pDoc->is.size() != 0)
			{
				index = _ttoi(pDoc->is.back()->label.Mid(1));
			}
			CString label;
			label.Format(TEXT("%d"),++index);
			label = L"I" + label;
			isCreating = true;
			newcomp = new Component(type,label,info,val,freq);
			newcomp->lp->positive = true;
		}
	}


	void CCircuit_SimulationView::OnParaEdit()
	{
		// TODO: 在此添加命令处理程序代码
		if(highlight != NULL)
		{
			if(highlight->type <= IS)
			{
				CCircuit_SimulationDoc *pDoc = GetDocument();
				CDialogNew newdlg(highlight->type);
				if(IDOK == newdlg.DoModal())
				{
					CString unit = newdlg.m_Unit;
					CString info = newdlg.m_Text + unit;
					double val = _ttof(newdlg.m_Text);		
					unitConvert(val,unit.Left(1));
					highlight->value = val;
					highlight->info = info;
					drawAll(m_pMemDC);
					Invalidate(false);
				}
			}
			else if(highlight->type <= SAWC)
			{
				CCircuit_SimulationDoc *pDoc = GetDocument();
				CDialogEdit newdlg(highlight->type);
				if(IDOK == newdlg.DoModal())
				{
					CString unit1 = newdlg.m_Unit1;
					CString unit2 = newdlg.m_Unit2;
					CString info = newdlg.m_Freq + unit1;
					CString info1 = newdlg.m_Max + unit2;
					info = info1 + L"  " + info;
					double freq = _ttof(newdlg.m_Freq);	
					unitConvert(freq,unit1.Left(1));
					double val = _ttof(newdlg.m_Max);	
					unitConvert(val,unit2.Left(1));
					highlight->value = val;
					highlight->frequency = freq;
					highlight->info = info;
					drawAll(m_pMemDC);
					Invalidate(false);
				}
			}
		}
	}


	void CCircuit_SimulationView::OnGrdNew()
	{
		// TODO: 在此添加命令处理程序代码
		highlight = NULL;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		isCreating = true;
		newcomp = new Component(GRD,L"",L"",-1);
		newcomp->reverse = true;
		newcomp->lp = newcomp->rp;
	}


	void CCircuit_SimulationView::OnPnChange()
	{
		// TODO: 在此添加命令处理程序代码
		if(highlight != NULL)
		{
			if(highlight->type >= ES && highlight->type <= SAWC)
			{
				CCircuit_SimulationDoc *pDoc = GetDocument();
				highlight->lp->positive = !highlight->lp->positive;
				highlight->rp->positive = !highlight->rp->positive;
				drawAll(m_pMemDC);
				Invalidate(false);
			}
		}
	}


	void CCircuit_SimulationView::OnOscNew()
	{
		// TODO: 在此添加命令处理程序代码
		highlight = NULL;
		CCircuit_SimulationDoc *pDoc = GetDocument();
		isCreating = true;
		newcomp = new Component(OSC,L"OSC",L"",-1);
	}


	void CCircuit_SimulationView::OnUpdateCaNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdateEsNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdateGrdNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdateIsNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdateLiNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdateOscNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdateParaEdit(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || highlight == NULL || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdatePnChange(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || highlight == NULL || highlight->type >SAWC || highlight->type < ES || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdateReNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdateReverse(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || (!isCreating && highlight == NULL) || !(highlight != NULL && highlight->lp->pnode == NULL && highlight->rp->pnode == NULL) 
			|| (highlight != NULL && highlight->type == OSC)|| isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdateSignalNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnUpdateSignalcNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || isplaying)
			pCmdUI->Enable(false);
	}


	void CCircuit_SimulationView::OnOscDelete()
	{
		// TODO: 在此添加命令处理程序代码
		int index;
		for(unsigned int i = 0;i < Osclist.size();i++)
		{
			if(Osclist.at(i) == highlight)
			{
				//Osclist.erase(Osclist.begin() + i);
				index = i;
				break;
			}
		}
		if(oscNode != NULL)
		{
			for(unsigned int i = 0; i < oscNode->junctions.size();i++)
			{
				if(oscNode->junctions.at(i)->pnode == Osclist.at(index)->lp->pnode || oscNode->junctions.at(i)->pnode == Osclist.at(index)->rp->pnode)
				{
					oscNode->junctions.erase(oscNode->junctions.begin() + i);
					i --;
				}
			}
			for(unsigned int i = 0; i < oscNode->lines.size();i++)
			{
				if(oscNode->lines.at(i)->points.front() == Osclist.at(index)->lp || oscNode->lines.at(i)->points.back() == Osclist.at(index)->lp
					|| oscNode->lines.at(i)->points.front() == Osclist.at(index)->rp || oscNode->lines.at(i)->points.back() == Osclist.at(index)->rp)
				{
					oscNode->lines.erase(oscNode->lines.begin() + i);
					i --;
				}
			}
		}
		Osclist.erase(Osclist.begin() + index);
		highlight = NULL;
		drawAll(m_pMemDC);
		Invalidate(false);

	}

	void CCircuit_SimulationView::OnUpdateOscDelete(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(init == false || isplaying || highlight == NULL || (highlight != NULL && highlight->type != OSC))
			pCmdUI->Enable(false);
	}
