
// Orthogonal_List.h : Orthogonal_List Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// COrthogonal_ListApp:
// �йش����ʵ�֣������ Orthogonal_List.cpp
//

class COrthogonal_ListApp : public CWinApp
{
public:
	COrthogonal_ListApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COrthogonal_ListApp theApp;
