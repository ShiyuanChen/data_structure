#pragma once

#define BLACK false
#define RED true
#include <vector>
using namespace std;
struct Stu
{
	int grade;
	CString ID;
	CString name;
	Stu(CString ID,CString NAME,int GRADE):ID(ID),name(NAME),grade(GRADE){}
};

class CNode
{
public:
	int key;//³É¼¨¶Î
	vector<Stu *> stu;
	CString section;
	bool color;
	CNode *left;
	CNode *right;
	CNode *parent;
	int delta;
	int x;
	int y;
	int prex;
	int prey;
	int nextx;
	int nexty;
	int index;
	static int radius;

	CNode(void);
	CNode(int KEY,bool COLOR);
	~CNode(void);
	void setSection(int KEY);
	void setPosition(int xx,int yy);
	void draw(int xx,int yy,CDC * pDC);
	void draw(bool COLOR,CDC * pDC);
	void draw(CDC *pDC);
	void setColor(bool COLOR);
	void setRad(int RADIUS);
	void addStu(Stu * S);
	void deleteStu(CString ID);
	Stu * addStu(CString ID,CString NAME,int GRADE);
};

