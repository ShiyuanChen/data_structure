
// Orthogonal_List.h : Orthogonal_List 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// COrthogonal_ListApp:
// 有关此类的实现，请参阅 Orthogonal_List.cpp
//

class COrthogonal_ListApp : public CWinApp
{
public:
	COrthogonal_ListApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COrthogonal_ListApp theApp;
