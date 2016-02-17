
// LabyrinthDoc.h : CLabyrinthDoc ��Ľӿ�
//


#pragma once
#include "Node.h"
#include<vector>
#include<queue>

using namespace std;

class CLabyrinthDoc : public CDocument
{
protected: // �������л�����
	CLabyrinthDoc();
	DECLARE_DYNCREATE(CLabyrinthDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CLabyrinthDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
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
