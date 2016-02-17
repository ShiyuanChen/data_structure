#include "stdafx.h"
#include "Node.h"

void Point::drawcircle(CDC *pDC)
{
	CPen *pe = new CPen(PS_SOLID,1,RGB(0,0,0));
	CPen * oldpen =  pDC->SelectObject(pe);
	pDC->Ellipse(x-AREA,y-AREA,x+AREA,y+AREA);
	pDC->SelectObject(oldpen);
	pe->DeleteObject();
}