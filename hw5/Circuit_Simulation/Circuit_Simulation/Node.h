#pragma once
#include <vector>

#define RE 0
#define CA 1
#define LI 2
#define ES 3
#define IS 4
#define SINV 5
#define SQRV 6
#define SAWV 7
#define SINC 8
#define SQRC 9
#define SAWC 10
#define GRD 11
#define OSC 12
#define AREA 5
using namespace std;

class Component;
class Node;
class line;

class Point
{
public:
	Component *parent;
	//line *prior1;
	//line *prior2;
	Node * pnode;
	bool isleft;
	bool positive;
	int x,y;
	Point(bool ISLEFT):isleft(ISLEFT),pnode(NULL),parent(NULL),positive(false){}
	Point(int X,int Y):isleft(false),pnode(NULL),parent(NULL),positive(false),x(X),y(Y){}
	void drawcircle(CDC *pDC);
};

class line
{
public:
	vector<Point *> points;
	//vector<Point *> junctions;
	line(Point *P1)
	{
		points.push_back(P1);
	}
	~line()
	{
		for(unsigned int i = 0;i < points.size();i ++)
		{
			if(points.at(i)->parent == NULL && points.at(i)->pnode == NULL)
				delete points.at(i);
		}
		points.clear();
	}
};

class Node
{
public:
	int index;
	bool ground;
	vector<Point *> points;
	vector<line *> lines;
	vector<Point *> junctions;
	Node(int INDEX):index(INDEX),ground(false){}
};

