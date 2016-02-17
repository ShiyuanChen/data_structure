
// RB_TreeView.cpp : CRB_TreeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "RB_Tree.h"
#endif

#include "Tree.h"
#include "Node.h"

#include "RB_TreeDoc.h"
#include "RB_TreeView.h"
#include "DialogDelete.h"
#include "DialogGrade.h"
#include "DialogNew.h"
#include "DialogSearch.h"
#include "DialogRes.h"
#include "DialogSection.h"
#include <vector>
#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRB_TreeView

IMPLEMENT_DYNCREATE(CRB_TreeView, CScrollView)

	BEGIN_MESSAGE_MAP(CRB_TreeView, CScrollView)
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRB_TreeView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_WM_CREATE()
		ON_COMMAND(ID_NODE_INSERT, &CRB_TreeView::OnNodeInsert)
		ON_WM_SIZE()
		ON_COMMAND(ID_NODE_DELETE, &CRB_TreeView::OnNodeDelete)
		ON_COMMAND(ID_FILE_SAVE, &CRB_TreeView::OnFileSave)
		ON_COMMAND(ID_FILE_OPEN, &CRB_TreeView::OnFileOpen)
		ON_COMMAND(ID_GRADE_STAT, &CRB_TreeView::OnGradeStat)
		ON_COMMAND(ID_STUDENT_STAT, &CRB_TreeView::OnStudentStat)
		ON_COMMAND(ID_LEVEL_TRAVERSAL, &CRB_TreeView::OnLevelTraversal)
		ON_COMMAND(ID_INORDER_TRAVERSAL, &CRB_TreeView::OnInorderTraversal)
		ON_COMMAND(ID_NO_SEARCH, &CRB_TreeView::OnNoSearch)
		ON_COMMAND(ID_NAME_SEARCH, &CRB_TreeView::OnNameSearch)
		ON_COMMAND(ID_SECTION_SEARCH, &CRB_TreeView::OnSectionSearch)
		ON_COMMAND(ID_GRADE_SEARCH, &CRB_TreeView::OnGradeSearch)
		ON_WM_MOUSEMOVE()
		ON_WM_TIMER()
		ON_COMMAND(ID_FILE_NEW, &CRB_TreeView::OnFileNew)
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_UPDATE_COMMAND_UI(ID_NODE_INSERT, &CRB_TreeView::OnUpdateNodeInsert)
		ON_UPDATE_COMMAND_UI(ID_NODE_DELETE, &CRB_TreeView::OnUpdateNodeDelete)
		ON_UPDATE_COMMAND_UI(ID_INORDER_TRAVERSAL, &CRB_TreeView::OnUpdateInorderTraversal)
		ON_UPDATE_COMMAND_UI(ID_LEVEL_TRAVERSAL, &CRB_TreeView::OnUpdateLevelTraversal)
		ON_UPDATE_COMMAND_UI(ID_NO_SEARCH, &CRB_TreeView::OnUpdateNoSearch)
		ON_UPDATE_COMMAND_UI(ID_NAME_SEARCH, &CRB_TreeView::OnUpdateNameSearch)
		ON_UPDATE_COMMAND_UI(ID_SECTION_SEARCH, &CRB_TreeView::OnUpdateSectionSearch)
		ON_UPDATE_COMMAND_UI(ID_GRADE_SEARCH, &CRB_TreeView::OnUpdateGradeSearch)
		ON_UPDATE_COMMAND_UI(ID_STUDENT_STAT, &CRB_TreeView::OnUpdateStudentStat)
		ON_UPDATE_COMMAND_UI(ID_GRADE_STAT, &CRB_TreeView::OnUpdateGradeStat)
		ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CRB_TreeView::OnUpdateFileNew)
		ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CRB_TreeView::OnUpdateFileSave)
	END_MESSAGE_MAP()

	// CRB_TreeView 构造/析构

	CRB_TreeView::CRB_TreeView()
		: isdragging(false)
		, Radius(0)
		, xdelta(0)
		, ydelta(0)
		, highlight(NULL)
		, xnum(0)
		, ynum(0)
		, moveflag(0)
		, moveptr(0)
		, incase(0)
		, innode(NULL)
		, ismoving(false)
		, nullnode(NULL)
		, deletenode(NULL)
		, isfloating(false)
		, tnode(NULL)
		, pnode(NULL)
	{
		// TODO: 在此处添加构造代码
		m_pMemDC = new CDC();
		m_pBitmap = new CBitmap();
	}

	CRB_TreeView::~CRB_TreeView()
	{
	}

	BOOL CRB_TreeView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CScrollView::PreCreateWindow(cs);
	}

	// CRB_TreeView 绘制

	void CRB_TreeView::OnDraw(CDC* pDC)
	{
		CRB_TreeDoc* pDoc = GetDocument();
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

	void CRB_TreeView::OnInitialUpdate()
	{
		CScrollView::OnInitialUpdate();

		CSize sizeTotal;
		// TODO: 计算此视图的合计大小
		sizeTotal.cx = sizeTotal.cy = 100;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}


	// CRB_TreeView 打印


	void CRB_TreeView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CRB_TreeView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CRB_TreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CRB_TreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}

	void CRB_TreeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void CRB_TreeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CRB_TreeView 诊断

#ifdef _DEBUG
	void CRB_TreeView::AssertValid() const
	{
		CScrollView::AssertValid();
	}

	void CRB_TreeView::Dump(CDumpContext& dc) const
	{
		CScrollView::Dump(dc);
	}

	CRB_TreeDoc* CRB_TreeView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRB_TreeDoc)));
		return (CRB_TreeDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CRB_TreeView 消息处理程序


	int CRB_TreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CScrollView::OnCreate(lpCreateStruct) == -1)
			return -1;
		// TODO:  在此添加您专用的创建代码
		CDC* pDC=GetDC();
		m_pMemDC->CreateCompatibleDC(pDC);
		return 0;
	}

	void CRB_TreeView::OnNodeInsert()
	{
		// TODO: 在此添加命令处理程序代码
		CRB_TreeDoc *pDoc = GetDocument();
		CDialogNew newdlg;
		int result = newdlg.DoModal();
		if(result == IDOK)
		{
			CString ID = newdlg.m_ID;
			CString name = newdlg.m_Name;
			int grade = _ttoi(newdlg.m_Grade);
			int prenum = pDoc->tree.num;
			//Stu * stuptr = pDoc->tree.insertNode(ID,name,grade);
			innode = pDoc->tree.insertNode(ID,name,grade);

			if(innode == NULL)
			{
				CString str1("插入失败！\n已存在该学生。");
				CString str2("提示");
				MessageBox(str1,str2);
			}
			else
			{
				CDC* pDC=GetDC();
				if(prenum != pDoc->tree.num)
				{
					if(m_pMemDC != NULL)
						m_pMemDC->DeleteDC();
					if(m_pBitmap != NULL)
						m_pBitmap->DeleteObject();
					m_pMemDC->CreateCompatibleDC(pDC);
					m_pBitmap->CreateCompatibleBitmap(pDC,MAXWIDTH,MAXHEIGHT);
					m_pMemDC->SelectObject(m_pBitmap);

					setPosition();
					pDoc->tree.movelist.push_back(new act(innode,XMARGIN,YMARGIN,innode->x,innode->y));
					incase = 0;
					//pDoc->tree.insert_case1(node);
					ismoving = true;
					SetTimer(1,DELAY_MOVE,NULL);
				}
				else
				{
					innode->draw(m_pMemDC);
					Invalidate(false);
					innode = NULL;
				}
			}
		}
	}
	void CRB_TreeView::OnNodeDelete()
	{
		// TODO: 在此添加命令处理程序代码
		CRB_TreeDoc *pDoc = GetDocument();
		CDialogDelete deletedlg;
		int result = deletedlg.DoModal();
		if(result == IDOK)
		{
			CString ID = deletedlg.m_ID;
			Stu * stuptr = pDoc->tree.find(ID);
			if(stuptr == NULL)
			{
				CString str1("删除失败！\n未找到该学生。");
				CString str2("提示");
				MessageBox(str1,str2);
			}
			else
			{
				innode = pDoc->tree.deleteNode(stuptr);
				if(innode != NULL)
				{
					incase = 0;
					ismoving = true;
					innode->draw(m_pMemDC);
					Invalidate(false);
					SetTimer(3,DELAY_MOVE,NULL);
				}
				else
				{
					drawAll(m_pMemDC);
					Invalidate(false);
				}
			}
		}//
	}

	void CRB_TreeView::OnSize(UINT nType, int cx, int cy)
	{
		CScrollView::OnSize(nType, cx, cy);

		// TODO: 在此处添加消息处理程序代码
		CRB_TreeDoc *pDoc = GetDocument();
		if(pDoc->tree.root != NULL)
		{
			drawAll(m_pMemDC);
			this->Invalidate(false);
		}
	}

	void CRB_TreeView::drawAll(CDC * pDC)
	{
		CRB_TreeDoc *pDoc = GetDocument();	
		if(pDoc->tree.root != NULL)
		{
			m_pMemDC->FillSolidRect(0, 0,MAXWIDTH,MAXHEIGHT,RGB(255,255,255));
			int sum = pDoc->tree.num;
			ynum = pDoc->tree.depth;
			xnum = 1;
			for(int k = 1;k < ynum;k++)
				xnum *= 2;

			CRect rc;
			GetWindowRect(rc);
			xdelta = rc.Width() / 2;
			if(ynum <= 1)
				ydelta = rc.Height();
			else
				ydelta = rc.Height() / ynum;
			if(xnum <= 1)
				Radius = rc.Height() / 8;
			else
				Radius = min((rc.Width() - XMARGIN * 2) / (xnum - 1) / 4,ydelta / 5);
			CNode::radius = Radius;
			pDoc->tree.rootpos = ydelta / 2;
			pDoc->tree.xdelta = xdelta;
			pDoc->tree.ydelta = ydelta;
			pDoc->tree.draw(pDC);
		}
	}

	void CRB_TreeView::moveDraw(CDC * pDC)
	{
		CRB_TreeDoc *pDoc = GetDocument();
		if(pDoc->tree.root != NULL)
		{
			m_pMemDC->FillSolidRect(0, 0,MAXWIDTH,MAXHEIGHT,RGB(255,255,255));
			pDoc->tree.movedraw(pDC);
		}
	}

	void CRB_TreeView::setPosition(void)
	{
		CRB_TreeDoc *pDoc = GetDocument();
		if(pDoc->tree.root != NULL)
		{
			int sum = pDoc->tree.num;
			ynum = pDoc->tree.depth;
			xnum = 1;
			for(int k = 1;k < ynum;k++)
				xnum *= 2;

			CRect rc;
			GetWindowRect(rc);
			xdelta = rc.Width() / 2;
			if(ynum <= 1)
				ydelta = rc.Height();
			else
				ydelta = rc.Height() / ynum;
			if(xnum <= 1)
				Radius = rc.Height() / 8;
			else
				Radius = min((rc.Width() - XMARGIN * 2) / (xnum - 1) / 4,ydelta / 5);
			CNode::radius = Radius;
			pDoc->tree.rootpos = ydelta / 2;
			pDoc->tree.xdelta = xdelta;
			pDoc->tree.ydelta = ydelta;
			pDoc->tree.setPosition();
		}
	}

	void CRB_TreeView::OnFileSave()
	{
		// TODO: 在此添加命令处理程序代码
		if(GetDocument()->tree.root != NULL)
		{
			LPCTSTR filters = L"红黑树文件(*.rbt)|*.rbt|全部文件(*.*)|*.*||";
			CFileDialog filedlg(false,L"*.rbt",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filters);
			int result = filedlg.DoModal();
			CString filename;
			if(result == IDOK)
			{
				filename = filedlg.GetPathName();
				GetDocument()->saveFile(filename);
			}
		}
	}

	void CRB_TreeView::OnFileOpen()
	{
		// TODO: 在此添加命令处理程序代码
		LPCTSTR filters = L"红黑树文件(*.rbt)|*.rbt|全部文件(*.*)|*.*||";
		CFileDialog filedlg(true,L"*.rbt",NULL,NULL,filters);
		int result = filedlg.DoModal();
		CString filename;
		if(result == IDOK)
		{
			filename = filedlg.GetPathName();
			GetDocument()->loadFile(filename);
		}
	}

	void CRB_TreeView::OnGradeStat()
	{
		// TODO: 在此添加命令处理程序代码
		CTree *tree = &(GetDocument()->tree);
		int total = 0;
		int high = 0;
		int low = 100;
		for(unsigned int i = 0;i < tree->stulist.size();i ++)
		{
			total += tree->stulist.at(i)->grade;
			if(high < tree->stulist.at(i)->grade)
				high = tree->stulist.at(i)->grade;
			if(low > tree->stulist.at(i)->grade)
				low = tree->stulist.at(i)->grade;
		}
		double average = 0;
		if(tree->stulist.size() != 0)
			average = double(total) / tree->stulist.size();
		else
			low = 0;
		CString str0;
		str0.Format(TEXT("%.1lf"),average);
		CString str1("学生分数均值为： ");
		CString str2("\n最高分为：       ");
		CString str3("\n最低分为：       ");
		CString str4("\n成绩方差为：     ");
		str1 += str0;
		str0.Format(TEXT("%d"),high);
		str2 += str0;
		str0.Format(TEXT("%d"),low);
		str3 += str0;
		double var = 0;
		if(tree->stulist.size() != 0)
		{
			for(unsigned int i = 0;i < tree->stulist.size();i ++)
			{
				var += (tree->stulist.at(i)->grade - average) * (tree->stulist.at(i)->grade - average);
			}
			var /= tree->stulist.size();
		}
		str0.Format(TEXT("%.2lf"),var);
		str4 += str0;
		CString str5("分数统计");
		MessageBox(str1 + str2 + str3 + str4, str5);
	}

	void CRB_TreeView::OnStudentStat()
	{
		// TODO: 在此添加命令处理程序代码
		CTree *tree = &(GetDocument()->tree);
		int total = tree->stulist.size();
		CString str0;
		str0.Format(TEXT("%d"),total);
		CString str1("学生总数为： ");
		CString str2("人数统计");
		MessageBox(str1 + str0, str2);
	}

	void CRB_TreeView::drawPopup(CNode * node,bool left, bool top, CDC *pDC)
	{
		if(node != NULL)
		{
			CBrush *br = new CBrush(RGB(0,255,0));
			CBrush * oldBrush = pDC->SelectObject(br);
			CFont font;   
			LOGFONT lf;   
			memset(&lf,0,sizeof(LOGFONT));   
			lf.lfHeight = int(xdelta / 25);
			font.CreateFontIndirect(&lf);
			pDC->SelectObject(&font);
			unsigned int row = node->stu.size();
			int length = 0;
			CSize width = 0;
			CString str0,str2;
			vector<CString> str1;
			for(unsigned int j = 0;j < row;j++)
			{
				str2.Format(TEXT("%d"),node->stu.at(j)->grade);
				str0 = L" 学号: " + node->stu.at(j)->ID + L"  姓名: " + node->stu.at(j)->name + L"  成绩: " + str2 + L"  ";
				if(str0.GetLength() > length)
				{
					length = str0.GetLength();
					width = pDC->GetTextExtent(str0);
				}
				str1.push_back(str0);
			}
			int xfactor = 1,yfactor = 1;
			if(left)
			{
				xfactor = -1;
			}
			if(top)
			{
				yfactor = -1;
			}
			pDC->BeginPath();
			pDC->MoveTo(node->x,node->y);
			pDC->LineTo(node->x + Radius * xfactor,node->y - Radius * yfactor);
			pDC->LineTo(node->x + (Radius + width.cx ) * xfactor,node->y - Radius * yfactor);
			pDC->LineTo(node->x + (Radius + width.cx ) * xfactor,node->y + int(row * lf.lfHeight - Radius / 2) * yfactor);
			pDC->LineTo(node->x + Radius * xfactor,node->y + int(row * lf.lfHeight - Radius / 2) * yfactor);
			pDC->LineTo(node->x + Radius * xfactor,node->y - Radius / 5 * yfactor);
			pDC->LineTo(node->x,node->y);
			//pDC->AngleArc(250,250, 50, 0, 60);
			pDC->EndPath();
			//CRgn rgn;
			//rgn.CreateFromPath(pDC);
			//pDC->InvertRgn(&rgn);
			pDC->FillPath();
			int printx = node->x + Radius * xfactor;
			int printy = node->y - Radius * 3 / 4 * yfactor;
			if(top)
				printy = printy - int(row * lf.lfHeight);
			if(left)
				printx = printx - width.cx;
			pDC->SetTextAlign(TA_LEFT | TA_TOP);
			pDC->SetTextColor(RGB(0,0,0));
			for(unsigned int k = 0;k < str1.size(); k++)
			{
				pDC->TextOutW(printx,printy + k * lf.lfHeight,str1.at(k));
			}
			str1.clear();
			pDC->SelectObject(oldBrush);
			font.DeleteObject();
			br->DeleteObject();
		}
	}

	void CRB_TreeView::OnLevelTraversal()
	{
		// TODO: 在此添加命令处理程序代码
		CDialogRes resdlg(GetDocument(),false);
		int result = resdlg.DoModal();
		if(result == IDOK)
		{
			Invalidate();
		}
	}

	void CRB_TreeView::OnInorderTraversal()
	{
		// TODO: 在此添加命令处理程序代码
		CDialogRes resdlg(GetDocument(),true);
		int result = resdlg.DoModal();
		if(result == IDOK)
		{
			Invalidate();
		}
	}

	void CRB_TreeView::loadRefresh(void)
	{
		CRB_TreeDoc *pDoc = GetDocument();
		CDC* pDC=GetDC();
		if(m_pMemDC != NULL)
			m_pMemDC->DeleteDC();
		if(m_pBitmap != NULL)
			m_pBitmap->DeleteObject();
		m_pMemDC->CreateCompatibleDC(pDC);
		m_pBitmap->CreateCompatibleBitmap(pDC,MAXWIDTH,MAXHEIGHT);
		m_pMemDC->SelectObject(m_pBitmap);

		drawAll(m_pMemDC);
		Invalidate();
	}

	void CRB_TreeView::OnNoSearch()
	{
		// TODO: 在此添加命令处理程序代码
		CRB_TreeDoc *pDoc = GetDocument();
		CDialogGrade newdlg(true);
		int result = newdlg.DoModal();
		if(result == IDOK)
		{
			CString ID = newdlg.m_Text;
			Stu *stuptr = NULL;
			stuptr = pDoc->tree.search(ID,pDoc->tree.root,stuptr);
			if(stuptr != NULL)
			{
				CString str0;
				str0.Format(TEXT("%d"),stuptr->grade);
				CString str1("该学生的成绩为： ");
				CString str2("成绩查询");
				MessageBox(str1 + str0, str2);
			}
			else
			{
				CString str1("未找到该学生！");
				CString str2("成绩查询");
				MessageBox(str1, str2);
			}

		}
	}

	void CRB_TreeView::OnNameSearch()
	{
		// TODO: 在此添加命令处理程序代码
		CRB_TreeDoc *pDoc = GetDocument();
		CDialogGrade newdlg(false);
		int result = newdlg.DoModal();
		if(result == IDOK)
		{
			CString name = newdlg.m_Text;
			vector<CString> ID;
			for(unsigned int i = 0;i < pDoc->tree.stulist.size();i++)
			{
				if(pDoc->tree.stulist.at(i)->name == name)
				{
					ID.push_back(pDoc->tree.stulist.at(i)->ID);
				}
			}
			if(ID.size() > 0)
			{
				Stu *stuptr;
				CString str0;
				CString str1("");
				CString str2("成绩查询");
				for(unsigned int k = 0;k < ID.size();k++)
				{
					stuptr = NULL;
					stuptr = pDoc->tree.search(ID.at(k),pDoc->tree.root,stuptr);
					str0.Format(TEXT("%d"),stuptr->grade);
					str1 += L"学生 ";
					str1 = str1 + ID.at(k) + L" 的成绩为： " + str0 + L"\n";
				}
				MessageBox(str1, str2);
			}
			else
			{
				CString str1("未找到该学生！");
				CString str2("成绩查询");
				MessageBox(str1, str2);
			}
		}
	}

	void CRB_TreeView::OnSectionSearch()
	{
		// TODO: 在此添加命令处理程序代码
		CRB_TreeDoc *pDoc = GetDocument();
		CDialogSection newdlg;
		int result = newdlg.DoModal();
		if(result == IDOK)
		{
			CString Sec = newdlg.m_Sec;
			int key = pDoc->tree.section2key(Sec);
			CNode * nodeptr = pDoc->tree.find(key,NULL,pDoc->tree.root);
			if(nodeptr != NULL)
			{
				CString str0("");
				CString str1("该成绩段的学生有");
				CString str2("学生查询");
				CString str3;
				str3.Format(TEXT("%d"),nodeptr->stu.size());
				for(unsigned int k = 0;k < nodeptr->stu.size();k++)
				{
					str0 += (L"\n    " + nodeptr->stu.at(k)->name);
				}
				str1 += str3 + L"名：";
				MessageBox(str1 + str0, str2);
			}
			else
			{
				CString str1("该成绩段没有学生！");
				CString str2("学生查询");
				MessageBox(str1, str2);
			}
		}
	}

	void CRB_TreeView::OnGradeSearch()
	{
		// TODO: 在此添加命令处理程序代码
		CRB_TreeDoc *pDoc = GetDocument();
		CDialogSearch newdlg;
		int result = newdlg.DoModal();
		if(result == IDOK)
		{
			int from = _ttoi(newdlg.m_from);
			int to = _ttoi(newdlg.m_to);
			int keyf = pDoc->tree.grade2key(from);
			int keyt = pDoc->tree.grade2key(to);
			CNode *nodeptr = NULL;
			int total = 0;
			CString str0("");
			CString str1("该成绩区间的学生有");
			CString str2("学生查询");
			CString str3;
			for(int j = keyf;j <= keyt;j++)
			{
				CNode * nodeptr1 = pDoc->tree.find(j,NULL,pDoc->tree.root);
				if(nodeptr1 != NULL)
				{
					nodeptr = nodeptr1;
					for(unsigned int k = 0;k < nodeptr->stu.size();k++)
					{
						if( nodeptr->stu.at(k)->grade >= from && nodeptr->stu.at(k)->grade <= to)
						{
							str0 += (L"\n    " + nodeptr->stu.at(k)->name);
							total++;
						}
					}
				}
			}
			str3.Format(TEXT("%d"),total);
			str1 += str3 + L"名：";
			if(nodeptr != NULL)
			{
				MessageBox(str1 + str0, str2);
			}
			else
			{
				CString str1("该成绩区间没有学生！");
				CString str2("学生查询");
				MessageBox(str1, str2);
			}
		}
	}

	void CRB_TreeView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		point += this->GetScrollPosition();
		CRB_TreeDoc *pDoc = GetDocument();
		CTree *tree = &(pDoc->tree);
		if(tree->root != NULL && !ismoving)
		{
			if(!isdragging && !isfloating)
			{
				if(tree->root != NULL)
				{
					int yindex = (point.y - tree->rootpos + Radius) / ydelta + 1;
					int curxdelta = xdelta;
					if(yindex == 1)
					{
						curxdelta = xdelta;
					}
					else
					{
						for(int i = 1;i < yindex;i ++)
						{
							curxdelta /= 2;
						}

					}
					int xindex = (point.x - curxdelta + Radius) / (2 * curxdelta) + 1;
					int xl = -1,yl = -1;
					if((point.y - tree->rootpos) % ydelta < Radius)
						yl = (point.y - tree->rootpos) % ydelta;
					else if((point.y - tree->rootpos) % ydelta > ydelta - Radius)
						yl = ydelta - (point.y - tree->rootpos) % ydelta;
					if((point.x - curxdelta) % (2 * curxdelta) < Radius)
						xl = (point.x - curxdelta) % (2 * curxdelta);
					else if((point.x - curxdelta) % (2 * curxdelta) > 2 * curxdelta - Radius)
						xl = 2 * curxdelta - (point.x - curxdelta) % (2 * curxdelta);
					if(highlight == NULL && xl != -1 && yl != -1 && xl * xl + yl * yl < Radius * Radius)
					{
						CNode * curnode = tree->root;
						for(int k = 1;k < yindex;k++)
						{
							if(curnode->x < point.x)
								curnode = curnode->right;
							else
								curnode = curnode->left;
						}
						if(curnode != NULL && ((curnode->x - point.x) * (curnode->x - point.x) + (curnode->y - point.y) * (curnode->y - point.y) < Radius * Radius))
						{
							highlight = curnode;
							CRect rc;
							GetWindowRect(rc);
							bool left = false;
							bool top = false;
							if(highlight->x > rc.Width() / 2)
								left = true;
							if(highlight->y >= rc.Height() / 2)
								top = true;
							drawPopup(highlight,left,top,m_pMemDC);
							Invalidate(false);
						}

					}
					else if(highlight != NULL && (xl == -1 || yl == -1 || xl * xl + yl * yl >= Radius * Radius))
					{
						highlight =NULL;
						drawAll(m_pMemDC);
						Invalidate(false);				
					}
				}
			}
			else if(isdragging == true)
			{
				CRB_TreeDoc * pDoc = GetDocument();
				highlight->x = point.x;
				highlight->y = point.y;
				highlight->nextx = point.x;
				highlight->nexty = point.y;
				moveDraw(m_pMemDC);
				Invalidate(false);
				pDoc->tree.movelist.push_back(new act(highlight,point.x,point.y,point.x,point.y));
				pDoc->tree.setPosition(&(pDoc->tree.movelist));
				moveflag = 0;
				SetTimer(4,DELAY_MOVE,NULL);

			}
		}
		CScrollView::OnMouseMove(nFlags, point);
	}

	void CRB_TreeView::OnTimer(UINT_PTR nIDEvent)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CRB_TreeDoc *pDoc = GetDocument();
		switch(nIDEvent)
		{
		case 1:
			if(incase == -1 && pDoc->tree.movelist.size() == 0)
			{
				moveptr = 0;
				moveflag = 0;
				pDoc->tree.movelist.clear();
				KillTimer(1);
				innode = NULL;
				incase = 0;
				SetTimer(2,DELAY_SHUFFLE,NULL);
			}
			else
			{
				while(incase != -1 && 0 == pDoc->tree.movelist.size())
					doInsert(innode);
				doMove(DELAY_MOVE);
			}
			break;
		case 2:
			if(pDoc->tree.colorlist.size()== 0)
			{
				moveptr = 0;
				moveflag = 0;
				//pDoc->tree.colorlist.clear();
				KillTimer(2);
				pDoc->tree.setDepth();
				m_pMemDC->FillSolidRect(0, 0,MAXWIDTH,MAXHEIGHT,RGB(255,255,255));
				drawAll(m_pMemDC);
				Invalidate(false);
				ismoving = false;
			}
			else
			{
				doShuffle(DELAY_SHUFFLE);
			}
			break;
		case 3:
			if(incase == -1 && 0 == pDoc->tree.movelist.size())
			{
				moveptr = 0;
				moveflag = 0;
				pDoc->tree.movelist.clear();
				KillTimer(3);
				delete deletenode;
				deletenode = NULL;
				if(nullnode != NULL && (nullnode->right == nullnode || nullnode->left == nullnode))
				{
					if(nullnode->parent != NULL)
					{
						if(nullnode == nullnode->parent->left)
							nullnode->parent->left = NULL;
						else
							nullnode->parent->right = NULL;
					}
					else
						pDoc->tree.root = NULL;
					delete nullnode;
					nullnode = NULL;
				}
				innode = NULL;
				incase = 0;
				SetTimer(2,DELAY_SHUFFLE,NULL);
			}
			else
			{
				while(incase != -1 && 0 == pDoc->tree.movelist.size())
					doDelete(innode);
				doMove(DELAY_MOVE);
			}
			break;
		case 4:
			if(pDoc->tree.movelist.size() == 0)
			{
				moveptr = 0;
				moveflag = 0;
				KillTimer(4);

			}
			else
			{
				doMove(DELAY_MOVE);
			}
			break;
		case 5:
			if(pDoc->tree.movelist.size() == 0)
			{
				KillTimer(5);
				isfloating = false;
			}
			else
			{
				doMove(DELAY_MOVE);
			}
			break;
		}
		CScrollView::OnTimer(nIDEvent);
	}

	void CRB_TreeView::doMove(int dt)
	{
		CRB_TreeDoc *pDoc = GetDocument();
		vector<act *> * curlist = &(pDoc->tree.movelist);
		double PI = acos(-1.0);
		double factor;
		if ((double)moveflag * COS_W > PI)
			factor = 1.0;
		else
		{
			factor = (1 - cos((double)moveflag * COS_W)) / 2.0;
		}
		CNode * node;

		for(unsigned int i = 0;i < curlist->size();i++)
		{
			node = curlist->at(i)->node;
			node->x = curlist->at(i)->sx + int((curlist->at(i)->ex - curlist->at(i)->sx) * factor);
			node->y = curlist->at(i)->sy + int((curlist->at(i)->ey - curlist->at(i)->sy) * factor);
		}
		moveDraw(m_pMemDC);
		if(deletenode != NULL)
			deletenode->draw(m_pMemDC);
		if(tnode != NULL)
			tnode->draw(m_pMemDC);
		Invalidate(false);
		moveflag += dt;
		if(factor >= 1.0)
		{
			moveflag = 0;
			unsigned int size = curlist->size();
			for(unsigned int j = 0;j < size;j ++)
			{
				delete curlist->back();
				curlist->pop_back();
			}
			curlist->clear();
		}
	}

	void CRB_TreeView::doShuffle(int dt)
	{
		CRB_TreeDoc *pDoc = GetDocument();
		double PI = acos(-1.0);
		double factor;
		if ((double)moveflag * COS_W > PI)
			factor = -1.0;
		else
		{
			factor = cos((double)moveflag * COS_W);
		}
		CNode * node;
		CBrush * br;
		if(factor > 0)
		{
			for(unsigned int i = 0;i < pDoc->tree.colorlist.size();i++)
			{
				node = pDoc->tree.colorlist.at(i)->node;
				if(pDoc->tree.colorlist.at(i)->scolor != pDoc->tree.colorlist.at(i)->ecolor)
				{
					br = new CBrush(RGB(255,255,255));
					CPen * pe = new CPen(PS_SOLID,2,RGB(255,255,255));
					CPen * oldPen = m_pMemDC->SelectObject(pe);
					CBrush * oldBrush = m_pMemDC->SelectObject(br);
					m_pMemDC->Ellipse(node->x - Radius,node->y - Radius,node->x + Radius,node->y + Radius);
					m_pMemDC->SelectObject(oldBrush);
					br->DeleteObject();
					m_pMemDC->SelectObject(oldPen);
					pe->DeleteObject();
					if(pDoc->tree.colorlist.at(i)->scolor == RED)
						br = new CBrush(RGB(255,0,0));
					else
						br = new CBrush(RGB(0,0,0));
					m_pMemDC->SelectObject(br);
					m_pMemDC->Ellipse(node->x - int(factor * Radius),node->y - Radius,node->x + int(factor * Radius),node->y + Radius);
					m_pMemDC->SelectObject(oldBrush);
					br->DeleteObject();
				}
			}
		}
		else
		{
			for(unsigned int i = 0;i < pDoc->tree.colorlist.size();i++)
			{
				node = pDoc->tree.colorlist.at(i)->node;
				if(pDoc->tree.colorlist.at(i)->scolor != pDoc->tree.colorlist.at(i)->ecolor)
				{
					if(pDoc->tree.colorlist.at(i)->ecolor == RED)
						br = new CBrush(RGB(255,0,0));
					else
						br = new CBrush(RGB(0,0,0));
					CBrush * oldBrush = m_pMemDC->SelectObject(br);
					m_pMemDC->Ellipse(node->x - int(factor * Radius),node->y - Radius,node->x + int(factor * Radius),node->y + Radius);
					m_pMemDC->SelectObject(oldBrush);
					br->DeleteObject();
				}
			}
		}
		Invalidate(false);
		moveflag += dt;
		if(factor <= -1.0)
		{
			moveflag = 0;
			unsigned int size = pDoc->tree.colorlist.size();
			for(unsigned int j = 0;j < size;j ++)
			{
				pDoc->tree.colorlist.back()->node->color = pDoc->tree.colorlist.back()->ecolor;
				delete pDoc->tree.colorlist.back();
				pDoc->tree.colorlist.pop_back();
			}
			KillTimer(2);
			pDoc->tree.setDepth();
			drawAll(m_pMemDC);
			Invalidate(false);
			ismoving = false;
		}
	}

	void CRB_TreeView::doInsert(CNode * NODE)
	{
		if(moveflag == 0)
		{
			CRB_TreeDoc * pDoc = GetDocument();
			CTree * tree = &(pDoc->tree);
			switch (incase)
			{
			case 0:
				incase = 1;
				break;
			case 1:
				{
					if(NODE->parent == NULL)
					{
						shuffle * sh = NULL;
						for(unsigned int i = 0;i < tree->colorlist.size();i++)
						{
							if(tree->colorlist.at(i)->node == NODE)
							{
								sh = tree->colorlist.at(i);
								sh->ecolor = BLACK;
								break;
							}
						}
						if(sh == NULL)
						{
							sh = new shuffle(NODE,NODE->color,BLACK);
							tree->colorlist.push_back(sh);
						}	
						NODE->color = BLACK;
						//NODE->index = 0;
						for(unsigned int j = 0;j < tree->colorlist.size();j++)
						{
							tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
						}
						incase = -1;
					}
					else
					{
						innode = NODE;
						incase = 2;
					}
					break;
				}
			case 2:
				{
					if (NODE->parent->color == BLACK)
					{
						for(unsigned int j = 0;j < tree->colorlist.size();j++)
						{
							tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
						}
						incase = -1;
					}
					else
					{
						innode = NODE;
						incase = 3;
					}
					break;
				}
			case 3:
				{
					if (tree->uncle(NODE) != NULL && tree->uncle(NODE)->color == RED)
					{
						shuffle * sh1 = NULL;
						shuffle * sh2 = NULL;
						shuffle * sh3 = NULL;
						for(unsigned int i = 0;i < tree->colorlist.size();i++)
						{
							if(tree->colorlist.at(i)->node == NODE->parent)
							{
								sh1 = tree->colorlist.at(i);
								sh1->ecolor = BLACK;
							}
							else if(tree->colorlist.at(i)->node == tree->uncle(NODE))
							{
								sh2 = tree->colorlist.at(i);
								sh2->ecolor = BLACK;
							}
							else if(tree->colorlist.at(i)->node == tree->grandparent(NODE))
							{
								sh3 = tree->colorlist.at(i);
								sh3->ecolor = RED;
							}
						}
						if(sh1 == NULL)
						{
							sh1 = new shuffle(NODE->parent,NODE->parent->color,BLACK);
							tree->colorlist.push_back(sh1);
						}
						if(sh2 == NULL)
						{
							sh2 = new shuffle(tree->uncle(NODE),tree->uncle(NODE)->color,BLACK);
							tree->colorlist.push_back(sh2);
						}
						if(sh3 == NULL)
						{
							sh3 = new shuffle(tree->grandparent(NODE),tree->grandparent(NODE)->color,RED);
							tree->colorlist.push_back(sh3);
						}
						NODE->parent->color = BLACK;
						tree->uncle(NODE)->color = BLACK;
						tree->grandparent(NODE)->color = RED;
						incase = 1;
						innode = tree->grandparent(NODE);
					}
					else
					{
						incase = 4;
						innode = NODE;
					}
					break;
				}
			case 4:
				{
					if (NODE == NODE->parent->right && NODE->parent == tree->grandparent(NODE)->left)
					{
						tree->rotate_left(NODE->parent);
						NODE = NODE->left;
					} 
					else if (NODE == NODE->parent->left && NODE->parent == tree->grandparent(NODE)->right)
					{
						tree->rotate_right(NODE->parent);
						NODE = NODE->right;
					}
					incase = 5;
					innode = NODE;
					break;
				}
			case 5:
				{
					shuffle * sh1 = NULL;
					shuffle * sh2 = NULL;
					for(unsigned int i = 0;i < tree->colorlist.size();i++)
					{
						if(tree->colorlist.at(i)->node == NODE->parent)
						{
							sh1 = tree->colorlist.at(i);
							sh1->ecolor = BLACK;
						}
						else if(tree->colorlist.at(i)->node == tree->grandparent(NODE))
						{
							sh2 = tree->colorlist.at(i);
							sh2->ecolor = RED;
						}
					}
					if(sh1 == NULL)
					{
						sh1 = new shuffle(NODE->parent,NODE->parent->color,BLACK);
						tree->colorlist.push_back(sh1);
					}
					if(sh2 == NULL)
					{
						sh2 = new shuffle(tree->grandparent(NODE),tree->grandparent(NODE)->color,RED);
						tree->colorlist.push_back(sh2);
					}

					NODE->parent->color = BLACK;
					tree->grandparent(NODE)->color = RED;
					if (NODE == NODE->parent->left && NODE->parent == tree->grandparent(NODE)->left)
					{
						tree->rotate_right(tree->grandparent(NODE));
					}
					else if (NODE == NODE->parent->right && NODE->parent == tree->grandparent(NODE)->right)
					{
						tree->rotate_left(tree->grandparent(NODE));
					}
					for(unsigned int j = 0;j < tree->colorlist.size();j++)
					{
						tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
					}
					incase = -1;
					break;
				}
			default:
				break;
			}
		}
	}

	void CRB_TreeView::doDelete(CNode * NODE)
	{
		if(moveflag == 0)
		{
			CRB_TreeDoc * pDoc = GetDocument();
			CTree * tree = &(pDoc->tree);
			switch (incase)
			{
			case 0:
				{
					if(NODE->left != NULL && NODE->right != NULL)
					{
						CNode * curnode = NODE->left;
						while(curnode->right != NULL)
						{
							curnode = curnode->right;
						}
						NODE->key = curnode->key;
						///////////////////////
						innode = curnode;

						pnode = NODE;
						tnode = new CNode(curnode->key,curnode->color);
						tnode->stu = curnode->stu;
						tnode->x = curnode->x;
						tnode->y = curnode->y;
						tree->movelist.push_back(new act(tnode,tnode->x,tnode->y,NODE->x,NODE->y));					
					}
					incase = 1;
					break;
				}
			case 1:
				{
					if(tnode != NULL)
					{
						pnode->section = innode->section;
						pnode->stu = innode->stu;
						delete tnode;
						tnode = NULL;
						pnode = NULL;
					}
					CNode * child;
					if(NODE->left == NULL && NODE->right == NULL)
					{
						//////////////////
						child = new CNode(NODE->key - 1,BLACK);
						child->parent = NODE;
						child->left = child;
						child->right = child;
						NODE->left = child;
						child->section = "ERE";
						nullnode = child;
					}
					else
					{
						if(NODE->left == NULL)
							child = NODE->right;
						else
							child = NODE->left;

						tree->movelist.push_back(new act(child,child->x,child->y,child->parent->x,child->parent->y));
						child->delta = child->parent->delta;
						child->nextx = child->parent->x;
						child->nexty = child->parent->y;
					}
					child->parent = NODE->parent;
					if(child->parent != NULL)
					{
						if(NODE->parent->left == NODE)
							NODE->parent->left = child;
						else
							NODE->parent->right = child;
					}
					else
					{
						tree->root = child;
					}
					tree->setPosition(&(tree->movelist));
					if (NODE->color == BLACK) 
					{  
						if (child->color == RED)
						{
							shuffle * sh = NULL;
							for(unsigned int i = 0;i < tree->colorlist.size();i++)
							{
								if(tree->colorlist.at(i)->node == child)
								{
									sh = tree->colorlist.at(i);
									sh->ecolor = BLACK;
									break;
								}
							}
							if(sh == NULL)
							{
								sh = new shuffle(child,child->color,BLACK);
								tree->colorlist.push_back(sh);
							}
							child->color = BLACK;
							for(unsigned int j = 0;j < tree->colorlist.size();j++)
							{
								tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
							}
							incase = -1;
						}
						else  
						{
							innode = child;
							incase = 2;	
							for(unsigned int j = 0;j < tree->colorlist.size();j++)
							{
								tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
							}////////////
						}
					}
					else
					{
						for(unsigned int j = 0;j < tree->colorlist.size();j++)
						{
							tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
						}
						incase = -1;
					}
					//tree->movelist.push_back(new act(NODE,NODE->x,NODE->y,NODE->x,MAXHEIGHT));
					deletenode =  NODE;
					tree->movelist.push_back(new act(deletenode,deletenode->x,deletenode->y,deletenode->x,MAXHEIGHT));
					break;
				}
			case 2:
				{
					if (NODE->parent != NULL)  
					{
						innode = NODE;
						incase = 3;
					}
					else
					{
						for(unsigned int j = 0;j < tree->colorlist.size();j++)
						{
							tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
						}
						incase = -1;
					}
					break;
				}
			case 3:
				{
					CNode *s = tree->sibling(NODE);
					if (s->color == RED)
					{
						shuffle * sh1 = NULL;
						shuffle * sh2 = NULL;
						for(unsigned int i = 0;i < tree->colorlist.size();i++)
						{
							if(tree->colorlist.at(i)->node == NODE->parent)
							{
								sh1 = tree->colorlist.at(i);
								sh1->ecolor = RED;
							}
							else if(tree->colorlist.at(i)->node == s)
							{
								sh2 = tree->colorlist.at(i);
								sh2->ecolor = BLACK;
							}
						}
						if(sh1 == NULL)
						{
							sh1 = new shuffle(NODE->parent,NODE->parent->color,RED);
							tree->colorlist.push_back(sh1);
						}
						if(sh2 == NULL)
						{
							sh2 = new shuffle(s,s->color,BLACK);
							tree->colorlist.push_back(sh2);
						}
						NODE->parent->color = RED;
						s->color = BLACK;
						if (NODE == NODE->parent->left)
							tree->rotate_left(NODE->parent);
						else
							tree->rotate_right(NODE->parent);
					}
					innode = NODE;
					incase = 4;
					break;
				}
			case 4:
				{
					CNode *s = tree->sibling(NODE);
					if(NODE->left != NODE && NODE->right != NODE)
					{
						if ((NODE->parent->color == BLACK) &&
							(s->color == BLACK) &&
							(s->left->color == BLACK) &&
							(s->right->color == BLACK)) 
						{
							shuffle * sh = NULL;
							for(unsigned int i = 0;i < tree->colorlist.size();i++)
							{
								if(tree->colorlist.at(i)->node == s)
								{
									sh = tree->colorlist.at(i);
									sh->ecolor = RED;
									break;
								}
							}
							if(sh == NULL)
							{
								sh = new shuffle(s,s->color,RED);
								tree->colorlist.push_back(sh);
							}
							s->color = RED;
							innode = NODE->parent;
							incase = 2;
							break;
						} 
						else
						{
							innode = NODE;
							incase = 5;
							break;
						}
					}
					else
					{
						if((NODE->parent->color == BLACK) &&
							(s->color == BLACK) &&
							(s->left == NULL) &&
							(s->right == NULL))
						{
							shuffle * sh = NULL;
							for(unsigned int i = 0;i < tree->colorlist.size();i++)
							{
								if(tree->colorlist.at(i)->node == s)
								{
									sh = tree->colorlist.at(i);
									sh->ecolor = RED;
									break;
								}
							}
							if(sh == NULL)
							{
								sh = new shuffle(s,s->color,RED);
								tree->colorlist.push_back(sh);
							}
							s->color = RED;
							innode = NODE->parent;
							incase = 2;
							break;
						}
						else
						{
							innode = NODE;
							incase = 5;
							break;
						}
					}
				}
			case 5:
				{
					CNode *s = tree->sibling(NODE);

					if(NODE->left != NODE && NODE->right != NODE)
					{
						if ((NODE->parent->color == RED) &&
							(s->color == BLACK) &&
							(s->left->color == BLACK) &&
							(s->right->color == BLACK))
						{
							shuffle * sh1 = NULL;
							shuffle * sh2 = NULL;
							for(unsigned int i = 0;i < tree->colorlist.size();i++)
							{
								if(tree->colorlist.at(i)->node == NODE->parent)
								{
									sh1 = tree->colorlist.at(i);
									sh1->ecolor = BLACK;
								}
								else if(tree->colorlist.at(i)->node == s)
								{
									sh2 = tree->colorlist.at(i);
									sh2->ecolor = RED;
								}
							}
							if(sh1 == NULL)
							{
								sh1 = new shuffle(NODE->parent,NODE->parent->color,BLACK);
								tree->colorlist.push_back(sh1);
							}
							if(sh2 == NULL)
							{
								sh2 = new shuffle(s,s->color,RED);
								tree->colorlist.push_back(sh2);
							}
							s->color = RED;
							NODE->parent->color = BLACK;
							for(unsigned int j = 0;j < tree->colorlist.size();j++)
							{
								tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
							}
							incase = -1;
							break;
						}
						else
						{
							innode = NODE;
							incase = 6;
							break;
						}
					}
					else
					{
						if ((NODE->parent->color == RED) &&
							(s->color == BLACK) &&
							(s->left == NULL) &&
							(s->right == NULL))
						{
							shuffle * sh1 = NULL;
							shuffle * sh2 = NULL;
							for(unsigned int i = 0;i < tree->colorlist.size();i++)
							{
								if(tree->colorlist.at(i)->node == NODE->parent)
								{
									sh1 = tree->colorlist.at(i);
									sh1->ecolor = BLACK;
								}
								else if(tree->colorlist.at(i)->node == s)
								{
									sh2 = tree->colorlist.at(i);
									sh2->ecolor = RED;
								}
							}
							if(sh1 == NULL)
							{
								sh1 = new shuffle(NODE->parent,NODE->parent->color,BLACK);
								tree->colorlist.push_back(sh1);
							}
							if(sh2 == NULL)
							{
								sh2 = new shuffle(s,s->color,RED);
								tree->colorlist.push_back(sh2);
							}
							s->color = RED;
							NODE->parent->color = BLACK;
							for(unsigned int j = 0;j < tree->colorlist.size();j++)
							{
								tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
							}
							incase = -1;
							break;
						}
						else
						{
							innode = NODE;
							incase = 6;
							break;
						}
					}
				}
			case 6:
				{
					CNode *s = tree->sibling(NODE);

					if  (s->color == BLACK)
					{
						if ((NODE == NODE->parent->left) &&
							((s->right == NULL) || (s->right->color == BLACK)) &&
							((s->left != NULL) && (s->left->color == RED)))
						{ 
							shuffle * sh1 = NULL;
							shuffle * sh2 = NULL;
							for(unsigned int i = 0;i < tree->colorlist.size();i++)
							{
								if(tree->colorlist.at(i)->node == s->left)
								{
									sh1 = tree->colorlist.at(i);
									sh1->ecolor = BLACK;
								}
								else if(tree->colorlist.at(i)->node == s)
								{
									sh2 = tree->colorlist.at(i);
									sh2->ecolor = RED;
								}
							}
							if(sh1 == NULL)
							{
								sh1 = new shuffle(s->left,s->left->color,BLACK);
								tree->colorlist.push_back(sh1);
							}
							if(sh2 == NULL)
							{
								sh2 = new shuffle(s,s->color,RED);
								tree->colorlist.push_back(sh2);
							}
							s->color = RED;
							s->left->color = BLACK;
							tree->rotate_right(s);
						}
						else if ((NODE == NODE->parent->right) &&
							((s->left == NULL) || (s->left->color == BLACK)) &&
							((s->right != NULL) && (s->right->color == RED)))
						{
							shuffle * sh1 = NULL;
							shuffle * sh2 = NULL;
							for(unsigned int i = 0;i < tree->colorlist.size();i++)
							{
								if(tree->colorlist.at(i)->node == s->right)
								{
									sh1 = tree->colorlist.at(i);
									sh1->ecolor = BLACK;
								}
								else if(tree->colorlist.at(i)->node == s)
								{
									sh2 = tree->colorlist.at(i);
									sh2->ecolor = RED;
								}
							}
							if(sh1 == NULL)
							{
								sh1 = new shuffle(s->right,s->right->color,BLACK);
								tree->colorlist.push_back(sh1);
							}
							if(sh2 == NULL)
							{
								sh2 = new shuffle(s,s->color,RED);
								tree->colorlist.push_back(sh2);
							}
							s->color = RED;
							s->right->color = BLACK;
							tree->rotate_left(s);
						}
					}
					innode = NODE;
					incase = 7;
					for(unsigned int j = 0;j < tree->colorlist.size();j++)
					{
						tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
					}
					break;
				}
			case 7:
				{
					CNode *s = tree->sibling(NODE);

					bool color = NODE->parent->color;
					shuffle * sh1 = NULL;
					shuffle * sh2 = NULL;
					for(unsigned int i = 0;i < tree->colorlist.size();i++)
					{
						if(tree->colorlist.at(i)->node == NODE->parent)
						{
							sh1 = tree->colorlist.at(i);
							sh1->ecolor = BLACK;
						}
						else if(tree->colorlist.at(i)->node == s)
						{
							sh2 = tree->colorlist.at(i);
							sh2->ecolor = color;
						}
					}
					if(sh1 == NULL)
					{
						sh1 = new shuffle(NODE->parent,NODE->parent->color,BLACK);
						tree->colorlist.push_back(sh1);
					}
					if(sh2 == NULL)
					{
						sh2 = new shuffle(s,s->color,color);
						tree->colorlist.push_back(sh2);
					}
					s->color = color;
					NODE->parent->color = BLACK;

					if (NODE == NODE->parent->left)
					{
						if(s->right != NULL)
						{
							shuffle * sh3 = NULL;
							for(unsigned int i = 0;i < tree->colorlist.size();i++)
							{
								if(tree->colorlist.at(i)->node == s->right)
								{
									sh3 = tree->colorlist.at(i);
									sh3->ecolor = BLACK;
									break;
								}
							}
							if(sh3 == NULL)
							{
								sh3 = new shuffle(s->right,s->right->color,BLACK);
								tree->colorlist.push_back(sh3);
							}
							s->right->color = BLACK;
						}
						tree->rotate_left(NODE->parent);
					}
					else
					{
						if(s->left != NULL)
						{
							shuffle * sh3 = NULL;
							for(unsigned int i = 0;i < tree->colorlist.size();i++)
							{
								if(tree->colorlist.at(i)->node == s->left)
								{
									sh3 = tree->colorlist.at(i);
									sh3->ecolor = BLACK;
									break;
								}
							}
							if(sh3 == NULL)
							{
								sh3 = new shuffle(s->left,s->left->color,BLACK);
								tree->colorlist.push_back(sh3);
							}
							s->left->color = BLACK;
						}
						tree->rotate_right(NODE->parent);
					}
					for(unsigned int j = 0;j < tree->colorlist.size();j++)
					{
						tree->colorlist.at(j)->node->color = tree->colorlist.at(j)->scolor;
					}
					incase = -1;
					break;
				}
			default:
				break;
			}
		}
	}

	void CRB_TreeView::OnFileNew()
	{
		// TODO: 在此添加命令处理程序代码
		CRB_TreeDoc * pDoc = GetDocument();
		for(unsigned int i = 0;i < pDoc->tree.stulist.size();i++)
		{
			delete pDoc->tree.stulist.at(i);
		}
		pDoc->tree.stulist.clear();
		vector<CNode *> *queue = new vector<CNode *>;
		int front = 0;
		int rear = 0;
		CNode * ptr = pDoc->tree.root;
		if(pDoc->tree.root == NULL)
			return;
		else
		{
			queue->push_back(pDoc->tree.root);
			while(front <= rear)
			{
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
				queue->at(front)->stu.clear();
				queue->at(front)->parent = NULL;
				queue->at(front)->right = NULL;
				queue->at(front)->left = NULL;
				delete queue->at(front);
				front ++;
			}
			queue->clear();
		}
		pDoc->tree.num = 0;
		pDoc->tree.depth = 0;
		pDoc->tree.root = NULL;
		m_pMemDC->FillSolidRect(0, 0,MAXWIDTH,MAXHEIGHT,RGB(255,255,255));
		Invalidate(false);
	}


	void CRB_TreeView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CRB_TreeDoc * pDoc = GetDocument();
		if(pDoc->tree.root != NULL && !ismoving && !isfloating)
		{
			if(highlight != NULL)
			{
				isfloating = true;
				isdragging = true;
			}
		}
		CScrollView::OnLButtonDown(nFlags, point);
	}


	void CRB_TreeView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CRB_TreeDoc * pDoc = GetDocument();
		if(pDoc->tree.root != NULL && isdragging == true)
		{
			highlight = NULL;
			isdragging = false;
			KillTimer(4);
			pDoc->tree.movelist.clear();
			moveflag = 0;
			pDoc->tree.root->nextx = xdelta;
			pDoc->tree.root->nexty = pDoc->tree.rootpos;
			pDoc->tree.movelist.push_back(new act(pDoc->tree.root,pDoc->tree.root->x,pDoc->tree.root->y,pDoc->tree.root->nextx,pDoc->tree.root->nexty));
			pDoc->tree.setPosition(&(pDoc->tree.movelist));
			SetTimer(5,DELAY_MOVE,NULL);
		}
		CScrollView::OnLButtonUp(nFlags, point);
	}


	void CRB_TreeView::OnUpdateNodeInsert(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateNodeDelete(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateInorderTraversal(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateLevelTraversal(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateNoSearch(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateNameSearch(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateSectionSearch(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateGradeSearch(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateStudentStat(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateGradeStat(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateFileNew(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}


	void CRB_TreeView::OnUpdateFileSave(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		if(ismoving == true)
			pCmdUI->Enable(false);
	}
