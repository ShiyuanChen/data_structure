
// RB_TreeDoc.h : CRB_TreeDoc ��Ľӿ�
//


#pragma once
#include "Tree.h"

class CRB_TreeDoc : public CDocument
{
protected: // �������л�����
	CRB_TreeDoc();
	DECLARE_DYNCREATE(CRB_TreeDoc)

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
	virtual ~CRB_TreeDoc();
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
	CTree tree;
	void loadFile(LPCTSTR lpszPathName);
	void saveFile(LPCTSTR lpszPathName);
};
