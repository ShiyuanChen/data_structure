#include "stdafx.h"
#include "DrawUnit.h"
#include "Orthogonal_ListDoc.h"
#include "Orthogonal_ListView.h"


CDrawUnit::CDrawUnit(void):x(0),y(0),row(0),col(0),data(""),isselected(0){}
CDrawUnit::CDrawUnit(CString ROW,CString COL,CString DATA):row(_ttoi(ROW)),col(_ttoi(COL)),data(DATA),isselected(0)
{
	x = col * 2 * Width + x0;
	y = row * 2 * Height + y0;
}
CDrawUnit::CDrawUnit(int ROW,int COL,CString DATA):row(ROW),col(COL),data(DATA),isselected(0)
{
	x = col * 2 * Width + x0;
	y = row * 2 * Height + y0;
}
CDrawUnit::CDrawUnit(CString ROW,CString COL,CString DATA,int X,int Y):row(_ttoi(ROW)),col(_ttoi(COL)),data(DATA),x(X),y(Y),isselected(0){rowpos = row;colpos = col;}
CDrawUnit::~CDrawUnit(void){}

void CDrawUnit::set_X(int X){x = X;}
void CDrawUnit::set_Y(int Y){y = Y;}
int CDrawUnit::get_X(){	return x;}
int CDrawUnit::get_Y(){	return y;}
void CDrawUnit::set_Rowpos(CString ROWPOS){rowpos = _ttoi(ROWPOS);y = rowpos * 2 * Height + y0;}
void CDrawUnit::set_Colpos(CString COLPOS){colpos = _ttoi(COLPOS);x = colpos * 2 * Width + x0;}
int CDrawUnit::get_Rowpos(){	return rowpos;}
int CDrawUnit::get_Colpos(){	return colpos;}
CString CDrawUnit::get_Data(){	return data;}
void CDrawUnit::set_Data(CString DATA){	data = DATA;}
void CDrawUnit::set_Flag(){isselected = 1;}
void CDrawUnit::unset_Flag(){isselected = 0;}
void CDrawUnit::check_Flag(){isselected = 2;}
void CDrawUnit::unit_Draw(int ROWPOS,int COLPOS,CDC* pDC)
{
	rowpos = ROWPOS;
	colpos= COLPOS;
	CBrush *br;
	if(isselected == 1)
	{
		br = new CBrush(RGB(255,255,0));
	}
	else if(isselected == 0)
	{
		if(col == 0 || row == 0)
			br = new CBrush(RGB(120,120,120));
		else
			br = new CBrush(RGB(200,200,200));
	}
	else
	{
		br = new CBrush(RGB(0,255,0));
	}
	CBrush * oldBrush = pDC->SelectObject(br);
	CString s;
	x = COLPOS * 2 * Width + x0;
	y = ROWPOS * 2 * Height + y0;
	pDC->Rectangle(x,y,x+Width,y+Height);
	pDC->MoveTo(x+ int(Width / 3),y);
	pDC->LineTo(x+ int(Width / 3),y+ int(Height / 2));
	pDC->MoveTo(x+ int(Width * 2 / 3),y);
	pDC->LineTo(x+ int(Width  * 2 / 3),y+ int(Height / 2));
	pDC->MoveTo(x+ int(Width / 2),y+ int(Height / 2));
	pDC->LineTo(x+ int(Width / 2),y+ Height);
	pDC->MoveTo(x,y+ int(Height / 2));
	pDC->LineTo(x+ Width,y+ int(Height / 2));
	s.Format(TEXT("%d"), row);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER);
	pDC->TextOut(x+ int(Width / 6),y+ int(Height / 9),s);
	s.Format(TEXT("%d"), col);
	pDC->TextOut(x+ int(Width / 2),y+ int(Height / 9),s);
	//s.Format(TEXT("%d"), data);
	pDC->TextOut(x+ int(Width * 5 / 6),y+ int(Height / 9),data);
	CString s1("down");
	pDC->TextOut(x+ int(Width  / 4),y+ int(Height * 3 / 5),s1);
	CString s2("right");
	pDC->TextOut(x+ int(Width * 3 / 4),y+ int(Height * 3 / 5),s2);

	pDC->SelectObject(oldBrush);
}
CPoint * CDrawUnit::arrowRight()
{
	x = colpos * 2 * Width + x0;
	y = rowpos * 2 * Height + y0;
	CPoint *p = new CPoint(x+ Width,y+ int(Height * 3 / 4));
	return p;
}

CPoint * CDrawUnit::arrowLeft()
{
	x = colpos * 2 * Width + x0;
	y = rowpos * 2 * Height + y0;
	CPoint *p = new CPoint(x,y+ int(Height * 3 / 4));
	return p;
}

CPoint * CDrawUnit::arrowUp()
{
	x = colpos * 2 * Width + x0;
	y = rowpos * 2 * Height + y0;
	CPoint *p = new CPoint(x+ int(Width  / 4),y);
	return p;
}

CPoint * CDrawUnit::arrowDown()
{
	x = colpos * 2 * Width + x0;
	y = rowpos * 2 * Height + y0;
	CPoint *p = new CPoint(x+ int(Width  / 4),y+ Height);
	return p;
}



int CDrawUnit::x0 = 120;
int CDrawUnit::y0 = 70;
int CDrawUnit::Height = 48;
int CDrawUnit::Width = 90;
