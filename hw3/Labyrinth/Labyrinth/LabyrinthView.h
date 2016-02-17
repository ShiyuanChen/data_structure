
// LabyrinthView.h : CLabyrinthView 类的接口
//

#pragma once


class CLabyrinthView : public CScrollView
{
protected: // 仅从序列化创建
	CLabyrinthView();
	DECLARE_DYNCREATE(CLabyrinthView)

// 特性
public:
	CLabyrinthDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CLabyrinthView();
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
	double FrmWidth;
	double FrmHeight;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CDC *m_pMemDC;
	CBitmap *m_pBitmap;
	afx_msg void OnMapRand();
	void drawAll(CDC *pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMapRefresh();
	afx_msg void OnUpdateMapRefresh(CCmdUI *pCmdUI);
	afx_msg void OnMapNew();
	afx_msg void OnMapResize();
	int type;
	afx_msg void OnWidthPrior();
	afx_msg void OnDepthPrior();
	afx_msg void OnMapEntry();
	afx_msg void OnMapRatio();
	afx_msg void OnSearchStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int rate;
	int stepcount;
	void searchProc(void);
	static int zx[8];
	static int zy[8];
	vector<CNode*>* trace;
	int front;
	int rear;
	afx_msg void OnSearchAnalysis();
	int searchStat1(void);
	void postInit(void);
	afx_msg void OnRateDown();
	afx_msg void OnRateUp();
	int validcount;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CNode *highlight;
	bool issearch;
	afx_msg void OnStartSet();
	afx_msg void OnEndSet();
	afx_msg void OnUpdateStartSet(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEndSet(CCmdUI *pCmdUI);
	CNode *block;
	afx_msg void OnFlagChange();
	afx_msg void OnUpdateFlagChange(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMapResize(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMapEntry(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMapRatio(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSearchStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSearchAnalysis(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRateDown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRateUp(CCmdUI *pCmdUI);
	afx_msg void OnSearchPause();
	afx_msg void OnUpdateSearchPause(CCmdUI *pCmdUI);
	bool ispause;
	afx_msg void OnUpdateWidthPrior(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDepthPrior(CCmdUI *pCmdUI);
	afx_msg void OnSearchStop();
	afx_msg void OnUpdateSearchStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMapNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMapRand(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMapDefault(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMapInput(CCmdUI *pCmdUI);
	int searchStat2(void);
//	vector<CNode *> * dfSearch(vector<vector<CNode*>> *map,vector<CNode*> *stack);
	void widthProc(void);
	void depthProc(void);
	afx_msg void OnDepthPrior2();
	afx_msg void OnUpdateDepthPrior2(CCmdUI *pCmdUI);
	void depthProc2(void);
	afx_msg void OnAstarSearch();
	afx_msg void OnUpdateAstarSearch(CCmdUI *pCmdUI);
	int searchStat3(void);
	void astarProc(void);
	CNode *aptr;
	afx_msg void OnMapDefault();
	void loadRefresh(void);
	afx_msg void OnMapInput();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileNew();
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // LabyrinthView.cpp 中的调试版本
inline CLabyrinthDoc* CLabyrinthView::GetDocument() const
   { return reinterpret_cast<CLabyrinthDoc*>(m_pDocument); }
#endif

