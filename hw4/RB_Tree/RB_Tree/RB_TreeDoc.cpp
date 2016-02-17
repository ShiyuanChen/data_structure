
// RB_TreeDoc.cpp : CRB_TreeDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "RB_Tree.h"
#endif

#include "Tree.h"
#include "RB_TreeDoc.h"
#include "RB_TreeView.h"
#include "MainFrm.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRB_TreeDoc

IMPLEMENT_DYNCREATE(CRB_TreeDoc, CDocument)

	BEGIN_MESSAGE_MAP(CRB_TreeDoc, CDocument)
	END_MESSAGE_MAP()


	// CRB_TreeDoc 构造/析构

	CRB_TreeDoc::CRB_TreeDoc()
	{
		// TODO: 在此添加一次性构造代码

	}

	CRB_TreeDoc::~CRB_TreeDoc()
	{
	}

	BOOL CRB_TreeDoc::OnNewDocument()
	{
		if (!CDocument::OnNewDocument())
			return FALSE;

		// TODO: 在此添加重新初始化代码
		// (SDI 文档将重用该文档)

		return TRUE;
	}




	// CRB_TreeDoc 序列化

	void CRB_TreeDoc::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			// TODO: 在此添加存储代码
			if(tree.root != NULL)
			{
				ar << tree.num << tree.depth;

				vector<CNode *> *queue = new vector<CNode *>;
				int front = 0;
				int rear = 0;
				CNode * ptr = tree.root;
				if(ptr != NULL)
				{

					queue->push_back(ptr);
					while(front <= rear)
					{
						ar << queue->at(front)->key;
						if(queue->at(front)->color == BLACK)
							ar << 0;
						else
							ar << 1;
						ar << queue->at(front)->stu.size();
						for(unsigned int i = 0;i < queue->at(front)->stu.size();i ++)
						{
							ar << queue->at(front)->stu.at(i)->grade << queue->at(front)->stu.at(i)->ID << queue->at(front)->stu.at(i)->name;
						}
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

						front ++;
					}
					queue->clear();
				}
			}
		}
		else
		{
			// TODO: 在此添加加载代码
			if(tree.root != NULL)
			{
				for(unsigned int i = 0;i < tree.stulist.size();i++)
				{
					delete tree.stulist.at(tree.stulist.size() - i - 1);
				}
				tree.stulist.clear();
				tree.root = NULL;
			}
			int n,depth;
			ar >> n >> depth;
			tree.num = n;
			tree.depth = depth;
			int key,color;
			for(int i = 0;i < tree.num;i ++)
			{
				ar >> key >> color;
				CNode *newnode = NULL;
				if(color == 0)
					newnode = new CNode(key,BLACK);
				else
					newnode = new CNode(key,RED);
				tree.findInsert(newnode,NULL,tree.root);
				int GRADE;
				CString	ID;
				CString NAME;
				ar >> n;
				for(int j = 0;j < n;j++)
				{
					ar >> GRADE >> ID >> NAME;
					Stu * stuptr = newnode->addStu(ID,NAME,GRADE);
					tree.stulist.push_back(stuptr);
				}
			}
			CMainFrame *m_pfm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			CRB_TreeView *m_pView = (CRB_TreeView*)m_pfm->GetActiveView();
			m_pView->loadRefresh();
		}
	}

#ifdef SHARED_HANDLERS

	// 缩略图的支持
	void CRB_TreeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
	{
		// 修改此代码以绘制文档数据
		dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

		CString strText = _T("TODO: implement thumbnail drawing here");
		LOGFONT lf;

		CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
		pDefaultGUIFont->GetLogFont(&lf);
		lf.lfHeight = 36;

		CFont fontDraw;
		fontDraw.CreateFontIndirect(&lf);

		CFont* pOldFont = dc.SelectObject(&fontDraw);
		dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
		dc.SelectObject(pOldFont);
	}

	// 搜索处理程序的支持
	void CRB_TreeDoc::InitializeSearchContent()
	{
		CString strSearchContent;
		// 从文档数据设置搜索内容。
		// 内容部分应由“;”分隔

		// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
		SetSearchContent(strSearchContent);
	}

	void CRB_TreeDoc::SetSearchContent(const CString& value)
	{
		if (value.IsEmpty())
		{
			RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
		}
		else
		{
			CMFCFilterChunkValueImpl *pChunk = NULL;
			ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
			if (pChunk != NULL)
			{
				pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
				SetChunkValue(pChunk);
			}
		}
	}

#endif // SHARED_HANDLERS

	// CRB_TreeDoc 诊断

#ifdef _DEBUG
	void CRB_TreeDoc::AssertValid() const
	{
		CDocument::AssertValid();
	}

	void CRB_TreeDoc::Dump(CDumpContext& dc) const
	{
		CDocument::Dump(dc);
	}
#endif //_DEBUG


	// CRB_TreeDoc 命令


	void CRB_TreeDoc::loadFile(LPCTSTR lpszPathName)
	{
		CFileException fe;
		CFile* pFile = GetFile(lpszPathName,
			CFile::modeRead|CFile::shareDenyWrite, &fe);
		if (pFile == NULL)
		{
			ReportSaveLoadException(lpszPathName, &fe,
				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			return;
		}

		DeleteContents();
		SetModifiedFlag();  // dirty during de-serialize

		CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
		loadArchive.m_pDocument = this;
		loadArchive.m_bForceFlat = FALSE;
		TRY
		{
			CWaitCursor wait;
			if (pFile->GetLength() != 0)
				Serialize(loadArchive);     // load me
			loadArchive.Close();
			ReleaseFile(pFile, FALSE);
		}
		CATCH_ALL(e)
		{
			ReleaseFile(pFile, TRUE);
			DeleteContents();   // remove failed contents

			TRY
			{
				ReportSaveLoadException(lpszPathName, e,
					FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			}
			END_TRY
				return;
		}
		END_CATCH_ALL

			SetModifiedFlag(FALSE);     // start off with unmodified

		return;
	}


	void CRB_TreeDoc::saveFile(LPCTSTR lpszPathName)
	{
		CFileException fe;
		CFile* pFile = GetFile(lpszPathName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive, &fe);

		if (pFile == NULL)
		{
			ReportSaveLoadException(lpszPathName, &fe,
				TRUE, AFX_IDP_INVALID_FILENAME);
			return;
		}

		CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
		saveArchive.m_pDocument = this;
		saveArchive.m_bForceFlat = FALSE;
		TRY
		{
			CWaitCursor wait;
			Serialize(saveArchive);     // save me
			saveArchive.Close();
			ReleaseFile(pFile, FALSE);
		}
		CATCH_ALL(e)
		{
			ReleaseFile(pFile, TRUE);

			TRY
			{
				ReportSaveLoadException(lpszPathName, e,
					TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
			}
			END_TRY
				return;
		}
		END_CATCH_ALL
			SetModifiedFlag(FALSE);     // back to unmodified
		return;
	}
