
// Circuit_SimulationView.h : CCircuit_SimulationView 类的接口
//

#pragma once


class CCircuit_SimulationView : public CScrollView
{
protected: // 仅从序列化创建
	CCircuit_SimulationView();
	DECLARE_DYNCREATE(CCircuit_SimulationView)

// 特性
public:
	CCircuit_SimulationDoc* GetDocument() const;

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
	virtual ~CCircuit_SimulationView();
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CDC *m_pMemDC;
	CBitmap *m_pBitmap;
	bool isCreating;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	Component *newcomp;
	afx_msg void OnFileNew();
	void drawAll(CDC * pDC);
	Point * pselect;
	bool islinking;
	int linksx;
	int linksy;
	Point *linkpoint;
	void linkLine(int cx, int cy, CDC * pDC);
	void drawline(line * l, CDC * pDC);
	line * nowlink;
	void drawjunct(Point * JUNCTION, CDC * pDC);
	afx_msg void OnReverse();
	afx_msg void OnReNew();
	afx_msg void OnLiNew();
	afx_msg void OnCaNew();
	afx_msg void OnEsNew();
	afx_msg void OnIsNew();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void unitConvert(double &VAL, CString UNIT);
	Component *highlight;
	line *rectangle;
	void drawRect(line * RECT, CDC * pDC);
	bool toHighlight(int cx, int cy);
	bool lbuttondown;
	bool isdragging;
	Point *startpos;
	Point *startmouse;
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	float scale;
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	bool isscrolling;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	bool toLsegment(int cx, int cy);
	line *curline;
	void drawsqr(line * lineptr, CDC * pDC);

	afx_msg void OnSignalNew();
	afx_msg void OnSignalcNew();
	afx_msg void OnParaEdit();
	afx_msg void OnGrdNew();
	afx_msg void OnPnChange();
	Node *ground;
	afx_msg void OnOscNew();
	vector<Component *> Osclist;
	Node *oscNode;
	afx_msg void OnUpdateCaNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEsNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGrdNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIsNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLiNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOscNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateParaEdit(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePnChange(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReverse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSignalNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSignalcNew(CCmdUI *pCmdUI);
	bool init;
	bool isplaying;
	afx_msg void OnOscDelete();
	afx_msg void OnUpdateOscDelete(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // Circuit_SimulationView.cpp 中的调试版本
inline CCircuit_SimulationDoc* CCircuit_SimulationView::GetDocument() const
   { return reinterpret_cast<CCircuit_SimulationDoc*>(m_pDocument); }
#endif

