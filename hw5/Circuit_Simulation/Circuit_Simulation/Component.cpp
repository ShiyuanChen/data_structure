#include "stdafx.h"
#include "Component.h"
#include "define.h"

Component::Component(int TYPE,CString LABEL,CString INFO,double VALUE):type(TYPE),label(LABEL),info(INFO),value(VALUE),frequency(0),reverse(false),x(0),y(0),labelx(0),labely(0),infox(0),infoy(0)
{
	lp = new Point(true);
	lp->parent = this;
	rp = new Point(false);
	rp->parent = this;
}

Component::Component(int TYPE,CString LABEL,CString INFO,double VALUE,double FREQ):type(TYPE),label(LABEL),info(INFO),value(VALUE),frequency(FREQ),reverse(false),x(0),y(0),labelx(0),labely(0),infox(0),infoy(0)
{
	lp = new Point(true);
	lp->parent = this;
	rp = new Point(false);
	rp->parent = this;
}
Component::~Component()
{
	delete lp;
	delete rp;
}
bool Component::isoverlap(int cx,int cy)
{
	if(!reverse)
	{
		if(cx <= x + length && cx >=  x - length && cy <= y + length / 2 && cy >= y - length/2)
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		if(cx <= x + length/2 && cx >=  x - length/2 && cy <= y + length && cy >= y - length)
		{
			return true;
		}
		else
			return false;
	}
}

void Component::draw(CDC *pDC)
{
	CPen *pe = new CPen(PS_SOLID,2,RGB(0,0,0));
	CPen * oldpen =  pDC->SelectObject(pe);
	int factor;
	if(type >= ES && type <= SAWC)
	{
		if(lp->positive)
			factor = 1;
		else
			factor = -1;
	}
	const double PI = acos(-1);
	if(!reverse)
	{
		switch(type)
		{
		case RE:
			pDC->Rectangle(x-length/4,y - length /8,x + length/4,y + length /8);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			break;
		case CA:
			pDC->MoveTo(x - length / 12, y - length / 5);
			pDC->LineTo(x - length / 12, y + length / 5);
			pDC->MoveTo(x + length / 12, y - length / 5);
			pDC->LineTo(x + length / 12, y + length / 5);
			pDC->MoveTo(x - length / 12,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length / 12,y);
			pDC->LineTo(x + length/2,y);
			break;
		case LI:
			pDC->Arc(x - length / 4,y - length / 10,x - length / 8,y + length / 10,x - length / 8,y,x - length / 4,y);
			pDC->Arc(x - length / 8,y - length / 10,x,y + length / 10,x,y,x - length / 8,y);
			pDC->Arc(x,y - length / 10,x + length / 8,y + length / 10,x + length / 8,y,x,y);
			pDC->Arc(x + length / 8,y -length / 10,x + length / 4,y + length / 10,x + length / 4,y,x + length / 8,y);
			pDC->MoveTo(x - length / 4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length / 4,y);
			pDC->LineTo(x + length/2,y);
			break;
		case ES:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x - length/2,y);
			pDC->LineTo(x + length/2,y);
			pDC->MoveTo(x - factor * length * 10/32,y - length / 12);
			pDC->LineTo(x - factor * length * 12/32,y - length / 12);
			pDC->MoveTo(x - factor * length * 11/32,y - length / 12 - length /16);
			pDC->LineTo(x - factor * length * 11/32,y - length / 12 + length /16);
			pDC->MoveTo(x + factor * length * 10/32,y - length / 12);
			pDC->LineTo(x + factor * length * 12/32,y - length / 12);
			break;
		case IS:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y + length/4);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			pDC->MoveTo(x - factor * length * 10/32,y - length / 12);
			pDC->LineTo(x - factor * length * 12/32,y - length / 12);
			pDC->MoveTo(x - factor * length * 11/32,y - length / 12 - length /16);
			pDC->LineTo(x - factor * length * 11/32,y - length / 12 + length /16);
			pDC->MoveTo(x + factor * length * 10/32,y - length / 12);
			pDC->LineTo(x + factor * length * 12/32,y - length / 12);
			break;
		case SINV:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->Arc(x - length / 10,y,x + length / 10,y + length / 7,x,y,x,y + length / 7);
			pDC->Arc(x - length / 10,y - length / 7,x + length / 10,y,x,y,x,y - length / 7);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			pDC->MoveTo(x - factor * length * 5/32,y);
			pDC->LineTo(x - factor * length * 7/32,y);
			pDC->MoveTo(x - factor * length * 6/32,y - length /16);
			pDC->LineTo(x - factor * length * 6/32,y + length /16);
			pDC->MoveTo(x + factor * length * 6/32,y - length /16);
			pDC->LineTo(x + factor * length * 6/32,y + length /16);
			break;
		case SQRV:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y + length / 7);
			pDC->LineTo(x - length / 10,y + length / 7);
			pDC->LineTo(x - length / 10,y);
			pDC->LineTo(x + length / 10,y);
			pDC->LineTo(x + length / 10,y - length / 7);
			pDC->LineTo(x,y - length / 7);
			pDC->MoveTo(x - factor * length * 5/32,y);
			pDC->LineTo(x - factor * length * 7/32,y);
			pDC->MoveTo(x - factor * length * 6/32,y - length /16);
			pDC->LineTo(x - factor * length * 6/32,y + length /16);
			pDC->MoveTo(x + factor * length * 6/32,y - length /16);
			pDC->LineTo(x + factor * length * 6/32,y + length /16);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			break;
		case SAWV:
			pDC->Ellipse(x - length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y + length / 7);
			pDC->LineTo(x - length / 10,y + length / 7);
			pDC->LineTo(x + length / 10,y - length / 7);
			pDC->LineTo(x,y - length / 7);
			pDC->MoveTo(x - factor * length * 5/32,y);
			pDC->LineTo(x - factor * length * 7/32,y);
			pDC->MoveTo(x - factor * length * 6/32,y - length /16);
			pDC->LineTo(x - factor * length * 6/32,y + length /16);
			pDC->MoveTo(x + factor * length * 6/32,y - length /16);
			pDC->LineTo(x + factor * length * 6/32,y + length /16);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			break;
		case SINC:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->Arc(x - length / 10,y,x + length / 10,y + length / 7,x,y,x,y + length / 7);
			pDC->Arc(x - length / 10,y - length / 7,x + length / 10,y,x,y,x,y - length / 7);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);

			pDC->MoveTo(x + factor * length * 3/16,y);
			pDC->LineTo(x - factor * (length * 3/16 - length / 14),y);
			drawHArrow(x - factor * (length * 3/16 - length / 14),y,length / 10,factor,pDC);
			break;
		case SQRC:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y + length / 7);
			pDC->LineTo(x - length / 10,y + length / 7);
			pDC->LineTo(x - length / 10,y);
			pDC->LineTo(x + length / 10,y);
			pDC->LineTo(x + length / 10,y - length / 7);
			pDC->LineTo(x,y - length / 7);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			pDC->MoveTo(x + factor * length * 3/16,y);
			pDC->LineTo(x - factor * (length * 3/16 - length / 14),y);
			drawHArrow(x - factor * (length * 3/16 - length / 14),y,length / 10,factor,pDC);
			break;
		case SAWC:
			pDC->Ellipse(x - length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y + length / 7);
			pDC->LineTo(x - length / 10,y + length / 7);
			pDC->LineTo(x + length / 10,y - length / 7);
			pDC->LineTo(x,y - length / 7);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			pDC->MoveTo(x + factor * length * 3/16,y);
			pDC->LineTo(x - factor * (length * 3/16 - length / 14),y);
			drawHArrow(x - factor * (length * 3/16 - length / 14),y,length / 10,factor,pDC);
			break;
		case OSC:
			CBrush * br = new CBrush(RGB(190,220,190));
			CBrush * oldb = pDC->SelectObject(br);
			pDC->Rectangle(x-length *3 /4,y - length * 9 /4,x + length *2,y - length /4);
			br->DeleteObject();
			br = new CBrush(RGB(170,170,170));
			pDC->SelectObject(br);
			pDC->Ellipse(x - length/2 - CHECK * 3 /4,y - length / 2 - CHECK * 3 /4,x - length/2 + CHECK * 3 /4,y - length / 2 + CHECK * 3 /4);
			pDC->Ellipse(x + length/2 - CHECK * 3 /4,y - length / 2 - CHECK * 3 /4,x + length/2 + CHECK * 3 /4,y - length / 2 + CHECK * 3 /4);
			pe = new CPen(PS_SOLID,1,RGB(230,230,230));
			CPen * oldpen2 =  pDC->SelectObject(pe);
			pDC->Rectangle(x - length *3 /4 + length / 9,y - length * 9 /4 + length / 9,x + length * 4 / 3,y - length / 2 - length * 2 / 7);
			pDC->SelectObject(oldpen2);
			pe->DeleteObject();
			br->DeleteObject();
			br = new CBrush(RGB(0,0,0));
			pDC->SelectObject(br);
			pDC->Ellipse(x - length/2 - CHECK / 3,y - length / 2 - CHECK / 3,x - length/2 + CHECK / 3,y - length / 2 + CHECK / 3);
			pDC->Ellipse(x + length/2 - CHECK / 3,y - length / 2 - CHECK / 3,x + length/2 + CHECK / 3,y - length / 2 + CHECK / 3);
			pDC->MoveTo(x - length/2,y - length / 2);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/2,y - length / 2);
			pDC->LineTo(x + length/2,y);
			pDC->SelectObject(oldb);
			br->DeleteObject();
			break;
		}
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
		pDC->TextOutW(labelx,labely - length /4,label);
		pDC->SetTextAlign(TA_CENTER | TA_TOP);
		pDC->TextOutW(infox,infoy + length /4,info);
	}
	else
	{
		switch(type)
		{
		case RE:
			pDC->Rectangle(x-length/8,y - length /4,x + length/8,y + length /4);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			break;
		case CA:
			pDC->MoveTo(x - length / 5, y - length / 12);
			pDC->LineTo(x + length / 5, y - length / 12);
			pDC->MoveTo(x - length / 5, y + length / 12);
			pDC->LineTo(x + length / 5, y + length / 12);
			pDC->MoveTo(x,y - length / 12);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length / 12);
			pDC->LineTo(x,y + length/2);
			break;
		case LI:
			pDC->Arc(x - length / 10,y + length / 8,x + length / 10,y + length / 4,x,y + length / 8,x,y + length / 4);
			pDC->Arc(x - length / 10,y,x + length / 10,y + length / 8,x,y,x,y + length / 8);
			pDC->Arc(x - length / 10,y - length / 8,x + length / 10,y,x,y - length / 8,x,y);
			pDC->Arc(x - length / 10,y -length / 4,x + length / 10,y - length / 8,x,y - length / 4,x,y - length / 8);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			break;
		case ES:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y - length/2);
			pDC->LineTo(x,y + length/2);
			pDC->MoveTo(x + length / 12,y + factor * length * 10/32);
			pDC->LineTo(x + length / 12,y + factor * length * 12/32);
			pDC->MoveTo(x + length / 12 - length /16,y + factor * length * 11/32);
			pDC->LineTo(x + length / 12 + length /16,y + factor * length * 11/32);
			pDC->MoveTo(x + length / 12 - length /16,y - factor * length * 11/32);
			pDC->LineTo(x + length / 12 + length /16,y - factor * length * 11/32);
			break;
		case IS:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x + length/4,y);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			pDC->MoveTo(x + length / 12,y + factor * length * 10/32);
			pDC->LineTo(x + length / 12,y + factor * length * 12/32);
			pDC->MoveTo(x + length / 12 - length /16,y + factor * length * 11/32);
			pDC->LineTo(x + length / 12 + length /16,y + factor * length * 11/32);
			pDC->MoveTo(x + length / 12 - length /16,y - factor * length * 11/32);
			pDC->LineTo(x + length / 12 + length /16,y - factor * length * 11/32);
			break;
		case SINV:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->Arc(x,y - length / 10,x + length / 7,y + length / 10,x,y,x + length / 7,y);
			pDC->Arc(x - length / 7,y - length / 10,x,y + length / 10,x,y,x - length / 7,y);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			pDC->MoveTo(x,y + factor * length * 5/32);
			pDC->LineTo(x,y + factor * length * 7/32);
			pDC->MoveTo(x - length /16,y + factor * length * 6/32);
			pDC->LineTo(x + length /16,y + factor * length * 6/32);
			pDC->MoveTo(x - length /16,y - factor * length * 6/32);
			pDC->LineTo(x + length /16,y - factor * length * 6/32);
			break;
		case SQRV:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x + length / 7,y);
			pDC->LineTo(x + length / 7,y - length / 10);
			pDC->LineTo(x,y - length / 10);
			pDC->LineTo(x,y + length / 10);
			pDC->LineTo(x - length / 7,y + length / 10);
			pDC->LineTo(x - length / 7,y);
			pDC->MoveTo(x,y + factor * length * 5/32);
			pDC->LineTo(x,y + factor * length * 7/32);
			pDC->MoveTo(x - length /16,y + factor * length * 6/32);
			pDC->LineTo(x + length /16,y + factor * length * 6/32);
			pDC->MoveTo(x - length /16,y - factor * length * 6/32);
			pDC->LineTo(x + length /16,y - factor * length * 6/32);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			break;
		case SAWV:
			pDC->Ellipse(x - length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x + length / 7,y);
			pDC->LineTo(x + length / 7,y - length / 10);
			pDC->LineTo(x - length / 7,y + length / 10);
			pDC->LineTo(x - length / 7,y);
			pDC->MoveTo(x,y + factor * length * 5/32);
			pDC->LineTo(x,y + factor * length * 7/32);
			pDC->MoveTo(x - length /16,y + factor * length * 6/32);
			pDC->LineTo(x + length /16,y + factor * length * 6/32);
			pDC->MoveTo(x - length /16,y - factor * length * 6/32);
			pDC->LineTo(x + length /16,y - factor * length * 6/32);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			break;
		case SINC:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->Arc(x,y - length / 10,x + length / 7,y + length / 10,x,y,x + length / 7,y);
			pDC->Arc(x - length / 7,y - length / 10,x,y + length / 10,x,y,x - length / 7,y);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);

			pDC->MoveTo(x,y - factor * length * 3/16);
			pDC->LineTo(x,y + factor * (length * 3/16 - length / 14));
			drawVArrow(x,y + factor * (length * 3/16 - length / 14),length / 10,factor,pDC);
			break;
		case SQRC:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x + length / 7,y);
			pDC->LineTo(x + length / 7,y - length / 10);
			pDC->LineTo(x,y - length / 10);
			pDC->LineTo(x,y + length / 10);
			pDC->LineTo(x - length / 7,y + length / 10);
			pDC->LineTo(x - length / 7,y);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			pDC->MoveTo(x,y - factor * length * 3/16);
			pDC->LineTo(x,y + factor * (length * 3/16 - length / 14));
			drawVArrow(x,y + factor * (length * 3/16 - length / 14),length / 10,factor,pDC);
			break;
		case SAWC:
			pDC->Ellipse(x - length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x + length / 7,y);
			pDC->LineTo(x + length / 7,y - length / 10);
			pDC->LineTo(x - length / 7,y + length / 10);
			pDC->LineTo(x - length / 7,y);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			pDC->MoveTo(x,y - factor * length * 3/16);
			pDC->LineTo(x,y + factor * (length * 3/16 - length / 14));
			drawVArrow(x,y + factor * (length * 3/16 - length / 14),length / 10,factor,pDC);
			break;
		case GRD:
			pDC->MoveTo(x,y);
			pDC->LineTo(x,y - length/4);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x + length/4,y);
			pDC->MoveTo(x - length/6,y + length /12);
			pDC->LineTo(x + length/6,y + length /12);
			pDC->MoveTo(x - length/12,y + length /6);
			pDC->LineTo(x + length/12,y + length /6);
			break;
		}
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextAlign(TA_LEFT | TA_BASELINE);
		pDC->TextOutW(labelx + length / 4,labely - length /4,label);
		pDC->SetTextAlign(TA_LEFT | TA_BASELINE);
		pDC->TextOutW(infox + length / 4,infoy,info);
	}
	pDC->SelectObject(oldpen);
	pe->DeleteObject();
}
void Component::draw(int X,int Y,CDC *pDC)
{
	labelx += X - x;
	labely += Y - y;
	infox += X - x;
	infoy += Y - y;
	x = X;
	y = Y;
	CPen *pe = new CPen(PS_SOLID,2,RGB(0,0,0));
	CPen * oldpen =  pDC->SelectObject(pe);
	const double PI = acos(-1);
	int factor;
	if(type >= ES && type <= SAWC)
	{
		if(lp->positive)
			factor = 1;
		else
			factor = -1;
	}
	if(!reverse)
	{
		switch(type)
		{
		case RE:
			pDC->Rectangle(x-length/4,y - length /8,x + length/4,y + length /8);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			break;
		case CA:
			pDC->MoveTo(x - length / 12, y - length / 5);
			pDC->LineTo(x - length / 12, y + length / 5);
			pDC->MoveTo(x + length / 12, y - length / 5);
			pDC->LineTo(x + length / 12, y + length / 5);
			pDC->MoveTo(x - length / 12,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length / 12,y);
			pDC->LineTo(x + length/2,y);
			break;
		case LI:			
			pDC->Arc(x - length / 4,y - length / 10,x - length / 8,y + length / 10,x - length / 8,y,x - length / 4,y);
			pDC->Arc(x - length / 8,y - length / 10,x,y + length / 10,x,y,x - length / 8,y);
			pDC->Arc(x,y - length / 10,x + length / 8,y + length / 10,x + length / 8,y,x,y);
			pDC->Arc(x + length / 8,y -length / 10,x + length / 4,y + length / 10,x + length / 4,y,x + length / 8,y);
			pDC->MoveTo(x - length / 4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length / 4,y);
			pDC->LineTo(x + length/2,y);
			break;
		case ES:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x - length/2,y);
			pDC->LineTo(x + length/2,y);
			pDC->MoveTo(x - factor * length * 10/32,y - length / 12);
			pDC->LineTo(x - factor * length * 12/32,y - length / 12);
			pDC->MoveTo(x - factor * length * 11/32,y - length / 12 - length /16);
			pDC->LineTo(x - factor * length * 11/32,y - length / 12 + length /16);
			pDC->MoveTo(x + factor * length * 10/32,y - length / 12);
			pDC->LineTo(x + factor * length * 12/32,y - length / 12);
			break;
		case IS:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y + length/4);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			pDC->MoveTo(x - factor * length * 10/32,y - length / 12);
			pDC->LineTo(x - factor * length * 12/32,y - length / 12);
			pDC->MoveTo(x - factor * length * 11/32,y - length / 12 - length /16);
			pDC->LineTo(x - factor * length * 11/32,y - length / 12 + length /16);
			pDC->MoveTo(x + factor * length * 10/32,y - length / 12);
			pDC->LineTo(x + factor * length * 12/32,y - length / 12);
			break;
		case SINV:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->Arc(x - length / 10,y,x + length / 10,y + length / 7,x,y,x,y + length / 7);
			pDC->Arc(x - length / 10,y - length / 7,x + length / 10,y,x,y,x,y - length / 7);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			pDC->MoveTo(x - factor * length * 5/32,y);
			pDC->LineTo(x - factor * length * 7/32,y);
			pDC->MoveTo(x - factor * length * 6/32,y - length /16);
			pDC->LineTo(x - factor * length * 6/32,y + length /16);
			pDC->MoveTo(x + factor * length * 6/32,y - length /16);
			pDC->LineTo(x + factor * length * 6/32,y + length /16);
			break;
		case SQRV:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y + length / 7);
			pDC->LineTo(x - length / 10,y + length / 7);
			pDC->LineTo(x - length / 10,y);
			pDC->LineTo(x + length / 10,y);
			pDC->LineTo(x + length / 10,y - length / 7);
			pDC->LineTo(x,y - length / 7);
			pDC->MoveTo(x - factor * length * 5/32,y);
			pDC->LineTo(x - factor * length * 7/32,y);
			pDC->MoveTo(x - factor * length * 6/32,y - length /16);
			pDC->LineTo(x - factor * length * 6/32,y + length /16);
			pDC->MoveTo(x + factor * length * 6/32,y - length /16);
			pDC->LineTo(x + factor * length * 6/32,y + length /16);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			break;
		case SAWV:
			pDC->Ellipse(x - length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y + length / 7);
			pDC->LineTo(x - length / 10,y + length / 7);
			pDC->LineTo(x + length / 10,y - length / 7);
			pDC->LineTo(x,y - length / 7);
			pDC->MoveTo(x - factor * length * 5/32,y);
			pDC->LineTo(x - factor * length * 7/32,y);
			pDC->MoveTo(x - factor * length * 6/32,y - length /16);
			pDC->LineTo(x - factor * length * 6/32,y + length /16);
			pDC->MoveTo(x + factor * length * 6/32,y - length /16);
			pDC->LineTo(x + factor * length * 6/32,y + length /16);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			break;
		case SINC:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->Arc(x - length / 10,y,x + length / 10,y + length / 7,x,y,x,y + length / 7);
			pDC->Arc(x - length / 10,y - length / 7,x + length / 10,y,x,y,x,y - length / 7);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);

			pDC->MoveTo(x + factor * length * 3/16,y);
			pDC->LineTo(x - factor * (length * 3/16 - length / 14),y);
			drawHArrow(x - factor * (length * 3/16 - length / 14),y,length / 10,factor,pDC);
			break;
		case SQRC:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y + length / 7);
			pDC->LineTo(x - length / 10,y + length / 7);
			pDC->LineTo(x - length / 10,y);
			pDC->LineTo(x + length / 10,y);
			pDC->LineTo(x + length / 10,y - length / 7);
			pDC->LineTo(x,y - length / 7);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			pDC->MoveTo(x + factor * length * 3/16,y);
			pDC->LineTo(x - factor * (length * 3/16 - length / 14),y);
			drawHArrow(x - factor * (length * 3/16 - length / 14),y,length / 10,factor,pDC);
			break;
		case SAWC:
			pDC->Ellipse(x - length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y + length / 7);
			pDC->LineTo(x - length / 10,y + length / 7);
			pDC->LineTo(x + length / 10,y - length / 7);
			pDC->LineTo(x,y - length / 7);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/4,y);
			pDC->LineTo(x + length/2,y);
			pDC->MoveTo(x + factor * length * 3/16,y);
			pDC->LineTo(x - factor * (length * 3/16 - length / 14),y);
			drawHArrow(x - factor * (length * 3/16 - length / 14),y,length / 10,factor,pDC);
			break;
		case OSC:
			CBrush * br = new CBrush(RGB(190,220,190));
			CBrush * oldb = pDC->SelectObject(br);
			pDC->Rectangle(x-length *3 /4,y - length * 9 /4,x + length *2,y - length /4);
			br->DeleteObject();
			br = new CBrush(RGB(170,170,170));
			pDC->SelectObject(br);
			pDC->Ellipse(x - length/2 - CHECK * 3 /4,y - length / 2 - CHECK * 3 /4,x - length/2 + CHECK * 3 /4,y - length / 2 + CHECK * 3 /4);
			pDC->Ellipse(x + length/2 - CHECK * 3 /4,y - length / 2 - CHECK * 3 /4,x + length/2 + CHECK * 3 /4,y - length / 2 + CHECK * 3 /4);
			pe = new CPen(PS_SOLID,1,RGB(230,230,230));
			CPen * oldpen2 =  pDC->SelectObject(pe);
			pDC->Rectangle(x - length *3 /4 + length / 9,y - length * 9 /4 + length / 9,x + length * 4 / 3,y - length / 2 - length * 2 / 7);
			pDC->SelectObject(oldpen2);
			pe->DeleteObject();
			br->DeleteObject();
			br = new CBrush(RGB(0,0,0));
			pDC->SelectObject(br);
			pDC->Ellipse(x - length/2 - CHECK / 3,y - length / 2 - CHECK / 3,x - length/2 + CHECK / 3,y - length / 2 + CHECK / 3);
			pDC->Ellipse(x + length/2 - CHECK / 3,y - length / 2 - CHECK / 3,x + length/2 + CHECK / 3,y - length / 2 + CHECK / 3);
			pDC->MoveTo(x - length/2,y - length / 2);
			pDC->LineTo(x - length/2,y);
			pDC->MoveTo(x + length/2,y - length / 2);
			pDC->LineTo(x + length/2,y);
			pDC->SelectObject(oldb);
			br->DeleteObject();
			break;
		}
		rp->x = x + length / 2;
		rp->y = y;
		lp->x = x - length / 2;
		lp->y = y;
	}
	else
	{
		switch(type)
		{
		case RE:
			pDC->Rectangle(x-length/8,y - length /4,x + length/8,y + length /4);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			break;
		case CA:
			pDC->MoveTo(x - length / 5, y - length / 12);
			pDC->LineTo(x + length / 5, y - length / 12);
			pDC->MoveTo(x - length / 5, y + length / 12);
			pDC->LineTo(x + length / 5, y + length / 12);
			pDC->MoveTo(x,y - length / 12);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length / 12);
			pDC->LineTo(x,y + length/2);
			break;
		case LI:
			pDC->Arc(x - length / 10,y + length / 8,x + length / 10,y + length / 4,x,y + length / 8,x,y + length / 4);
			pDC->Arc(x - length / 10,y,x + length / 10,y + length / 8,x,y,x,y + length / 8);
			pDC->Arc(x - length / 10,y - length / 8,x + length / 10,y,x,y - length / 8,x,y);
			pDC->Arc(x - length / 10,y -length / 4,x + length / 10,y - length / 8,x,y - length / 4,x,y - length / 8);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			break;
		case ES:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x,y - length/2);
			pDC->LineTo(x,y + length/2);
			pDC->MoveTo(x + length / 12,y + factor * length * 10/32);
			pDC->LineTo(x + length / 12,y + factor * length * 12/32);
			pDC->MoveTo(x + length / 12 - length /16,y + factor * length * 11/32);
			pDC->LineTo(x + length / 12 + length /16,y + factor * length * 11/32);
			pDC->MoveTo(x + length / 12 - length /16,y - factor * length * 11/32);
			pDC->LineTo(x + length / 12 + length /16,y - factor * length * 11/32);
			break;
		case IS:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x + length/4,y);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			pDC->MoveTo(x + length / 12,y + factor * length * 10/32);
			pDC->LineTo(x + length / 12,y + factor * length * 12/32);
			pDC->MoveTo(x + length / 12 - length /16,y + factor * length * 11/32);
			pDC->LineTo(x + length / 12 + length /16,y + factor * length * 11/32);
			pDC->MoveTo(x + length / 12 - length /16,y - factor * length * 11/32);
			pDC->LineTo(x + length / 12 + length /16,y - factor * length * 11/32);
			break;
		case SINV:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->Arc(x,y - length / 10,x + length / 7,y + length / 10,x,y,x + length / 7,y);
			pDC->Arc(x - length / 7,y - length / 10,x,y + length / 10,x,y,x - length / 7,y);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			pDC->MoveTo(x,y + factor * length * 5/32);
			pDC->LineTo(x,y + factor * length * 7/32);
			pDC->MoveTo(x - length /16,y + factor * length * 6/32);
			pDC->LineTo(x + length /16,y + factor * length * 6/32);
			pDC->MoveTo(x - length /16,y - factor * length * 6/32);
			pDC->LineTo(x + length /16,y - factor * length * 6/32);
			break;
		case SQRV:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x + length / 7,y);
			pDC->LineTo(x + length / 7,y - length / 10);
			pDC->LineTo(x,y - length / 10);
			pDC->LineTo(x,y + length / 10);
			pDC->LineTo(x - length / 7,y + length / 10);
			pDC->LineTo(x - length / 7,y);
			pDC->MoveTo(x,y + factor * length * 5/32);
			pDC->LineTo(x,y + factor * length * 7/32);
			pDC->MoveTo(x - length /16,y + factor * length * 6/32);
			pDC->LineTo(x + length /16,y + factor * length * 6/32);
			pDC->MoveTo(x - length /16,y - factor * length * 6/32);
			pDC->LineTo(x + length /16,y - factor * length * 6/32);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			break;
		case SAWV:
			pDC->Ellipse(x - length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x + length / 7,y);
			pDC->LineTo(x + length / 7,y - length / 10);
			pDC->LineTo(x - length / 7,y + length / 10);
			pDC->LineTo(x - length / 7,y);
			pDC->MoveTo(x,y + factor * length * 5/32);
			pDC->LineTo(x,y + factor * length * 7/32);
			pDC->MoveTo(x - length /16,y + factor * length * 6/32);
			pDC->LineTo(x + length /16,y + factor * length * 6/32);
			pDC->MoveTo(x - length /16,y - factor * length * 6/32);
			pDC->LineTo(x + length /16,y - factor * length * 6/32);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			break;
		case SINC:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->Arc(x,y - length / 10,x + length / 7,y + length / 10,x,y,x + length / 7,y);
			pDC->Arc(x - length / 7,y - length / 10,x,y + length / 10,x,y,x - length / 7,y);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);

			pDC->MoveTo(x,y - factor * length * 3/16);
			pDC->LineTo(x,y + factor * (length * 3/16 - length / 14));
			drawVArrow(x,y + factor * (length * 3/16 - length / 14),length / 10,factor,pDC);
			break;
		case SQRC:
			pDC->Ellipse(x-length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x + length / 7,y);
			pDC->LineTo(x + length / 7,y - length / 10);
			pDC->LineTo(x,y - length / 10);
			pDC->LineTo(x,y + length / 10);
			pDC->LineTo(x - length / 7,y + length / 10);
			pDC->LineTo(x - length / 7,y);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			pDC->MoveTo(x,y - factor * length * 3/16);
			pDC->LineTo(x,y + factor * (length * 3/16 - length / 14));
			drawVArrow(x,y + factor * (length * 3/16 - length / 14),length / 10,factor,pDC);
			break;
		case SAWC:
			pDC->Ellipse(x - length/4,y - length /4,x + length/4,y + length /4);
			pDC->MoveTo(x + length / 7,y);
			pDC->LineTo(x + length / 7,y - length / 10);
			pDC->LineTo(x - length / 7,y + length / 10);
			pDC->LineTo(x - length / 7,y);
			pDC->MoveTo(x,y - length/4);
			pDC->LineTo(x,y - length/2);
			pDC->MoveTo(x,y + length/4);
			pDC->LineTo(x,y + length/2);
			pDC->MoveTo(x,y - factor * length * 3/16);
			pDC->LineTo(x,y + factor * (length * 3/16 - length / 14));
			drawVArrow(x,y + factor * (length * 3/16 - length / 14),length / 10,factor,pDC);
			break;
		case GRD:
			pDC->MoveTo(x,y);
			pDC->LineTo(x,y - length/4);
			pDC->MoveTo(x - length/4,y);
			pDC->LineTo(x + length/4,y);
			pDC->MoveTo(x - length/6,y + length /12);
			pDC->LineTo(x + length/6,y + length /12);
			pDC->MoveTo(x - length/12,y + length /6);
			pDC->LineTo(x + length/12,y + length /6);
			break;
		}
		if(type != GRD)
		{
			rp->x = x;
			rp->y = y - length / 2;
			lp->x = x;
			lp->y = y + length / 2;
		}
		else
		{
			rp->x = x;
			rp->y = y - length / 4;
		}
	}
	pDC->SelectObject(oldpen);
	pe->DeleteObject();
}
void Component::drawHArrow(int x, int y, int length, int factor, CDC * pDC)
{
	CBrush *brush1=CBrush::FromHandle((HBRUSH)CreateSolidBrush(RGB(0,0,0)));   
	CBrush *oldbr = pDC->SelectObject(brush1);  

	pDC->BeginPath();
	pDC->MoveTo(x,y);
	pDC->LineTo(x,y - length / 2);
	pDC->LineTo(x - factor * length,y);
	pDC->LineTo(x,y + length / 2);
	pDC->LineTo(x,y);
	pDC->EndPath();
	pDC->FillPath();

	pDC->SelectObject(oldbr);
	brush1->DeleteObject();
}

void Component::drawVArrow(int x, int y, int length, int factor, CDC * pDC)
{
	CBrush *brush1=CBrush::FromHandle((HBRUSH)CreateSolidBrush(RGB(0,0,0)));   
	CBrush *oldbr = pDC->SelectObject(brush1);  
	pDC->BeginPath();
	pDC->MoveTo(x,y);
	pDC->LineTo(x - length / 2,y);
	pDC->LineTo(x,y + factor * length);
	pDC->LineTo(x + length / 2,y);
	pDC->LineTo(x,y);
	pDC->EndPath();
	pDC->FillPath();

	pDC->SelectObject(oldbr);
	brush1->DeleteObject();
}
int Component::length = 6 * CHECK;

