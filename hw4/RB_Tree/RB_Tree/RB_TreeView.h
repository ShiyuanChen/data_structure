
// RB_TreeView.h : CRB_TreeView 类的接口
//

#pragma once
#include "Node.h"

class CRB_TreeView : public CScrollView
{
protected: // 仅从序列化创建
	CRB_TreeView();
	DECLARE_DYNCREATE(CRB_TreeView)

// 特性
public:
	CRB_TreeDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CRB_TreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CDC *m_pMemDC;
	CBitmap *m_pBitmap;
	CNode *highlight;
	bool isdragging;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int Radius;
	int xdelta;
	int ydelta;
	afx_msg void OnNodeInsert();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void drawAll(CDC * pDC);
	afx_msg void OnNodeDelete();
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnGradeStat();
	afx_msg void OnStudentStat();
	void drawPopup(CNode * node,bool left, bool top, CDC *pDC);
	afx_msg void OnLevelTraversal();
	afx_msg void OnInorderTraversal();
	void loadRefresh(void);
	afx_msg void OnNoSearch();
	afx_msg void OnNameSearch();
	afx_msg void OnSectionSearch();
	afx_msg void OnGradeSearch();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int xnum;
	int ynum;
	void setPosition(void);
	void moveDraw(CDC * pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void doMove(int dt);
	int moveflag;
	int moveptr;
	void doShuffle(int dt);
	void doInsert(CNode * NODE);
	int incase;
	CNode *innode;
	bool ismoving;
	void doDelete(CNode * NODE);
	CNode *nullnode;
	CNode *deletenode;
	afx_msg void OnFileNew();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	bool isfloating;
	afx_msg void OnUpdateNodeInsert(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNodeDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInorderTraversal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevelTraversal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNoSearch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNameSearch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSectionSearch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGradeSearch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStudentStat(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGradeStat(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	CNode *tnode;
	CNode *pnode;
};

#ifndef _DEBUG  // RB_TreeView.cpp 中的调试版本
inline CRB_TreeDoc* CRB_TreeView::GetDocument() const
   { return reinterpret_cast<CRB_TreeDoc*>(m_pDocument); }
#endif

