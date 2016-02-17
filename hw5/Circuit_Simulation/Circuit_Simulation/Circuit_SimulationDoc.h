
// Circuit_SimulationDoc.h : CCircuit_SimulationDoc ��Ľӿ�
//


#pragma once
#include <vector>
#include "Node.h"
#include "Component.h"
using namespace std;

class CCircuit_SimulationDoc : public CDocument
{
protected: // �������л�����
	CCircuit_SimulationDoc();
	DECLARE_DYNCREATE(CCircuit_SimulationDoc)

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
	virtual ~CCircuit_SimulationDoc();
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
	vector<Point *> points;
	vector<Component *> re;
	vector<Component *> ca;
	vector<Component *> li;
	vector<Component *> es;
	vector<Component *> is;
	vector<Node *> nodes;
};
