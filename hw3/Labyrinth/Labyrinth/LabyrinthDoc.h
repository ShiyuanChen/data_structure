
// LabyrinthDoc.h : CLabyrinthDoc 类的接口
//


#pragma once
#include "Node.h"
#include<vector>
#include<queue>

using namespace std;

class CLabyrinthDoc : public CDocument
{
protected: // 仅从序列化创建
	CLabyrinthDoc();
	DECLARE_DYNCREATE(CLabyrinthDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CLabyrinthDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int row;
	int col;
	double ratio;
	CNode *start;
	CNode *end;
	vector<vector<CNode *>> *map;
	void createMap(int ROW, int COL, double RATIO);
	void randRefresh(void);
	void setGoal(int sx, int sy, int ex, int ey);
	void setGoal(void);
	vector<CNode*>* queue;
	vector<CNode *> *stack;
	priority_queue<CNode*,vector<CNode*>,Compare> *pq;
	vector<CNode*> close;
	void createModel(void);
	void loadFile(LPCTSTR lpszPathName);
	void saveFile(LPCTSTR lpszPathName);
};
