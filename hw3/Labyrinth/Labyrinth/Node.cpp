#include "stdafx.h"
#include "Node.h"


CNode::CNode(void):x(0),y(0),pre(0),flag(0),f(0),g(0),h(0)
{
}
CNode::CNode(int X,int Y,int FLAG):x(X),y(Y),pre(0),flag(FLAG),f(0),g(0),h(0)
{
}
CNode::CNode(const CNode &node)
{
	x = node.x;
	y = node.y;
	pre = node.pre;
	flag = node.flag;
	f = node.f;
	g = node.g;
	h = node.h;
}

CNode::~CNode(void)
{
}

void CNode::setFlag(int FLAG)
{
	flag = FLAG;
}
int CNode::getFlag()
{
	return flag;
}
void CNode::setf(int G,int H)
{
	g = G;
	h = H;
	f = g + h;
}

void CNode::Draw(int FLAG,CDC * pDC)
{
	CBrush *br;
	CString str;
	flag = FLAG;
	if(FLAG == -3 || FLAG == 0 || FLAG == 2 || FLAG == 3|| FLAG == 4)
	{
		if(FLAG == 2 || FLAG == 4)
			br = new CBrush(RGB(255,255,0));
		else if(FLAG == 3)
			br = new CBrush(RGB(0,255,0));
		else if(FLAG == 0)
			br = new CBrush(RGB(255,255,255));
		else
			br = new CBrush(RGB(150,150,150));
		str = L"";//"0";
	}
	else
	{
		if(flag == 1)
		{
			br = new CBrush(RGB(0,0,0));
			str = L"";
		}
		else if(flag == -1)
		{
			br = new CBrush(RGB(255,0,0));
			str = L"Start";
		}
		else
		{
			br = new CBrush(RGB(255,0,0));
			str = L"End";
		}
		//else
		//br = new CBrush(RGB(255,255,255));

	}
	CBrush * oldBrush = pDC->SelectObject(br);
	int xx = int(x * width);
	int yy = int(y * height);
	int xz = int((x+1) * width);
	int yz = int((y+1) * height);
	pDC->Rectangle(xx,yy,xz,yz);
	pDC->SetBkMode(TRANSPARENT);
	if(flag == -1 || flag == -2)
		pDC->TextOutW(xx+int(width / 5),yy+int(height / 5),str);
	else
		pDC->TextOutW(xx+int(width / 3),yy+int(height / 3),str);
	pDC->SelectObject(oldBrush);
	br->DeleteObject();
}
void CNode::Draw(CDC * pDC)
{
	CBrush *br;
	CString str;
	if(flag == -3 || flag == 0 || flag == 2 || flag == 3|| flag == 4)
	{
		if(flag == 2 || flag == 4)
			br = new CBrush(RGB(255,255,0));
		else if(flag == 3)
			br = new CBrush(RGB(0,255,0));
		else if(flag == 0)
			br = new CBrush(RGB(255,255,255));
		else
			br = new CBrush(RGB(150,150,150));
		str = L"";//"0";
	}
	else
	{
		if(flag == 1)
		{
			br = new CBrush(RGB(0,0,0));
			str = L"";
		}
		else if(flag == -1)
		{
			br = new CBrush(RGB(255,0,0));
			str = L"Start";
		}
		else
		{
			br = new CBrush(RGB(255,0,0));
			str = L"End";
		}

	}
	CBrush * oldBrush = pDC->SelectObject(br);
	int xx = int(x * width);
	int yy = int(y * height);
	int xz = int((x+1) * width);
	int yz = int((y+1) * height);
	pDC->Rectangle(xx,yy,xz,yz);
	pDC->SetBkMode(TRANSPARENT);
	if(flag == -1 || flag == -2)
		pDC->TextOutW(xx+int(width / 2) - 13,yy+int(height / 2) - 7,str);
	else
		pDC->TextOutW(xx+int(width / 2) - 4,yy+int(height / 2) - 7,str);
	pDC->SelectObject(oldBrush);
	br->DeleteObject();
}
double CNode:: width = 0;
double CNode:: height = 0;