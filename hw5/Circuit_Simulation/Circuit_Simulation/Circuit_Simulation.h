
// Circuit_Simulation.h : Circuit_Simulation Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCircuit_SimulationApp:
// �йش����ʵ�֣������ Circuit_Simulation.cpp
//

class CCircuit_SimulationApp : public CWinAppEx
{
public:
	CCircuit_SimulationApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCircuit_SimulationApp theApp;