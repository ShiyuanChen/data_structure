#include "stdafx.h"
#include <vector>
#include "Node.h"


CNode::CNode(void):key(1),color(false),left(NULL),right(NULL),parent(NULL),x(0),y(0),prex(0),prey(0),nextx(0),nexty(0),index(0),delta(0)
{
	setSection(key);
}
CNode::CNode(int KEY,bool COLOR):key(KEY),color(COLOR),left(NULL),right(NULL),parent(NULL),x(0),y(0),prex(0),prey(0),nextx(0),nexty(0),index(0),delta(0)
{
	setSection(KEY);
}
CNode::~CNode(void)
{
}
void CNode::setSection(int KEY)
{
	//if(key != KEY)
	//key = KEY;
	switch(KEY)
	{
	case 1 :
		section = L"E";
		break;
	case 2:
		section = L"D";
		break;
	case 3 :
		section = L"C";
		break;
	case 4:
		section = L"C+";
		break;
	case 5 :
		section = L"B-";
		break;
	case 6:
		section = L"B";
		break;
	case 7 :
		section = L"B+";
		break;
	case 8:
		section = L"A";
		break;
	case 9 :
		section = L"AA";
		break;
	case 10:
		section = L"AA+";
		break;
	default:
		break;
	}
}

void CNode::setColor(bool COLOR){	color = COLOR;}
void CNode::setRad(int RADIUS){	radius = RADIUS;}
void CNode::setPosition(int xx,int yy)
{
	x = xx;
	y = yy;
}
void CNode::draw(int xx,int yy,CDC * pDC)
{
	x = xx;
	y = yy;
	CPen *pe = new CPen(PS_SOLID,2,RGB(200,200,200));//锯齿消弱
	CBrush *br;
	if(color == RED)
		br = new CBrush(RGB(255,0,0));
	else
		br = new CBrush(RGB(0,0,0));
	CPen * oldpen =  pDC->SelectObject(pe);
	pDC->Ellipse(xx - radius,yy - radius,xx + radius,yy + radius);
	pDC->SelectObject(oldpen);
	pe->DeleteObject();
	CBrush * oldBrush = pDC->SelectObject(br);
	pDC->Ellipse(xx - radius,yy - radius,xx + radius,yy + radius);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	CString str;
	str.Format(TEXT("%d"),stu.size());

	CFont font;   
	LOGFONT lf;   
	memset(&lf,0,sizeof(LOGFONT));   
	lf.lfHeight = int(radius / 1.1);
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(&font);

	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
	pDC->TextOutW(xx,yy - int(radius / 8),section);
	font.DeleteObject();
	lf.lfHeight = int(radius / 1.3); 
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(&font);
	pDC->SetTextAlign(TA_CENTER | TA_TOP);
	pDC->TextOutW(xx,yy+int(radius / 8),str);
	pDC->SelectObject(oldBrush);
	font.DeleteObject();
	br->DeleteObject();
}
void CNode::draw(bool COLOR,CDC * pDC)
{
	color = COLOR;
	CPen *pe = new CPen(PS_SOLID,2,RGB(200,200,200));//锯齿消弱
	CBrush *br;
	if(color == RED)
		br = new CBrush(RGB(255,0,0));
	else
		br = new CBrush(RGB(0,0,0));
	CPen * oldpen =  pDC->SelectObject(pe);
	pDC->Ellipse(x - radius,y - radius,x + radius,y + radius);
	pDC->SelectObject(oldpen);
	pe->DeleteObject();
	CBrush * oldBrush = pDC->SelectObject(br);
	pDC->Ellipse(x - radius,y - radius,x + radius,y + radius);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	CString str;
	str.Format(TEXT("%d"),stu.size());

	CFont font;   
	LOGFONT lf;   
	memset(&lf,0,sizeof(LOGFONT));   
	lf.lfHeight = int(radius / 1.1);
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(&font);

	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
	pDC->TextOutW(x,y - int(radius / 8),section);
	font.DeleteObject();
	lf.lfHeight = int(radius / 1.3); 
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(&font);
	pDC->SetTextAlign(TA_CENTER | TA_TOP);
	pDC->TextOutW(x,y+int(radius / 8),str);
	pDC->SelectObject(oldBrush);
	br->DeleteObject();
}
void CNode::draw(CDC * pDC)
{
	CPen *pe = new CPen(PS_SOLID,2,RGB(200,200,200));//锯齿消弱
	CBrush *br;
	if(color == RED)
		br = new CBrush(RGB(255,0,0));
	else
		br = new CBrush(RGB(0,0,0));
	CPen * oldpen =  pDC->SelectObject(pe);
	pDC->Ellipse(x - radius,y - radius,x + radius,y + radius);
	pDC->SelectObject(oldpen);
	pe->DeleteObject();
	CBrush * oldBrush = pDC->SelectObject(br);
	pDC->Ellipse(x - radius,y - radius,x + radius,y + radius);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	CString str;
	str.Format(TEXT("%d"),stu.size());

	CFont font;   
	LOGFONT lf;   
	memset(&lf,0,sizeof(LOGFONT));   
	lf.lfHeight = int(radius / 1.1);
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(&font);

	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
	pDC->TextOutW(x,y - int(radius / 8),section);
	font.DeleteObject();
	lf.lfHeight = int(radius / 1.3); 
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(&font);
	pDC->SetTextAlign(TA_CENTER | TA_TOP);
	pDC->TextOutW(x,y+int(radius / 8),str);
	pDC->SelectObject(oldBrush);
	br->DeleteObject();
}
void CNode::addStu(Stu * S){	stu.push_back(S);}
Stu * CNode::addStu(CString ID,CString NAME,int GRADE)
{
	Stu * stuptr = new Stu(ID,NAME,GRADE);
	stu.push_back(stuptr);
	return stuptr;
}
void CNode::deleteStu(CString ID)
{
	for(unsigned int k = 0;k < stu.size();k++)
	{
		if(stu.at(k)->ID == ID)
		{
			stu.erase(stu.begin() + k);
			return;
		}
	}
}
int CNode::radius = 0;
