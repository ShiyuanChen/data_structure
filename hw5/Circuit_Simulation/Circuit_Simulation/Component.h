#pragma once
#include "Node.h"
class Component
{
public:
	CString label;
	CString info;
	int type;//0,R;1,C;2,L;3,E;4,I,;5,sin;6,sqr;7,saw;8,grd
	double value;

	double frequency;
	//double ratio;

	Point *lp;
	Point *rp;
	bool reverse;
	int x,y;
	int labelx,labely,infox,infoy;
	static int length;
	Component(int TYPE,CString LABEL,CString INFO,double VALUE);
	Component(int TYPE,CString LABEL,CString INFO,double VALUE,double FREQ);
	~Component();
	bool isoverlap(int cx,int cy);
	void draw(CDC *pDC);
	void draw(int X,int Y,CDC *pDC);
	void drawHArrow(int x, int y, int length, int factor, CDC * pDC);
	void drawVArrow(int x, int y, int length, int factor, CDC * pDC);
};

