
// Orthogonal_ListView.h : COrthogonal_ListView 类的接口
//

#pragma once


class COrthogonal_ListView : public CScrollView
{
protected: // 仅从序列化创建
	COrthogonal_ListView();
	DECLARE_DYNCREATE(COrthogonal_ListView)

// 特性
public:
	COrthogonal_ListDoc* GetDocument() const;

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
	virtual ~COrthogonal_ListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNodeInsert();
	afx_msg void OnNodeDelete();
	afx_msg void OnSearchIndex();
	afx_msg void OnSearchKey();
	CString m_outNewRow;
	CString m_outNewCol;
	CString m_outNewData;
	afx_msg void OnFileNew();
	afx_msg void OnUpdateNodeInsert(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNodeDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSearchIndex(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSearchKey(CCmdUI *pCmdUI);
	afx_msg void OnNodeSum();
	void drawList(CCrossList * crosslist, CDC * pDC);
	void drawLines(CCrossList * crosslist, CDC * pDC);
	void drawHArrow(int x, int y, int length, CDC * pDC);
	void drawVArrow(int x, int y, int length, CDC * pDC);
	afx_msg void OnUpdateNodeSum(CCmdUI *pCmdUI);
	int m_ImgVScrollPos;
	int m_ImgHScrollPos;
	int HRange;
	int VRange;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CDC *m_pMemDC;
	CBitmap *m_pBitmap;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	unsigned int delay_flag;
	void searchMove(vector<Node*> * nodeptr,int mode,unsigned int &index);
	vector<Node *> *searchArray;
	void loadRefresh(void);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	Node *highlight;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPopupInsert();
	bool insertMode;
	afx_msg void OnPopupDelete();
	afx_msg void OnPopupChange();
	afx_msg void OnUpdatePopupInsert(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // Orthogonal_ListView.cpp 中的调试版本
inline COrthogonal_ListDoc* COrthogonal_ListView::GetDocument() const
   { return reinterpret_cast<COrthogonal_ListDoc*>(m_pDocument); }
#endif

