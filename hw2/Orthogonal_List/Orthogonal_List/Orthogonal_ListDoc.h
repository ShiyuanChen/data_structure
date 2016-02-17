
// Orthogonal_ListDoc.h : COrthogonal_ListDoc ��Ľӿ�
//


#pragma once
#include "CrossList.h"
#include "DrawUnit.h"

class COrthogonal_ListDoc : public CDocument
{
protected: // �������л�����
	COrthogonal_ListDoc();
	DECLARE_DYNCREATE(COrthogonal_ListDoc)

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
	virtual ~COrthogonal_ListDoc();
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
	CCrossList *ClObj;
	CCrossList * NewCrossList(int ROW, int COL);
};
