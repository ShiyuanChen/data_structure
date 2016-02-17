#pragma once
#include "Node.h"

struct act
{
	CNode * node;
	int sx,sy,ex,ey;
	act(CNode * NODE,int SX,int SY,int EX,int EY):node(NODE),sx(SX),sy(SY),ex(EX),ey(EY){}
};
struct shuffle
{
	CNode * node;
	bool scolor,ecolor;
	shuffle(CNode * NODE,bool SCOLOR,bool ECOLOR):node(NODE),scolor(SCOLOR),ecolor(ECOLOR){}
};
class CTree
{
public:
	CNode *root;
	int num;
	int depth;
	int xdelta,ydelta;
	int rootpos;
	vector<act*> movelist;
	vector<shuffle *> colorlist;
	vector<Stu *> stulist;
	CTree(void);
	~CTree(void);
	CNode* grandparent(CNode *NODE);
	CNode* uncle(CNode *NODE);
	CNode* sibling(CNode *NODE);
	int grade2key(int grade);
	int section2key(CString section);
	CNode* findInsert(CNode * newnode,CNode * f,CNode * subtree);
	CNode* find(int key,CNode * f,CNode * subtree);
	Stu * find(CString ID);
	Stu * search(CString ID,CNode * subtree,Stu * &result);
	//void insertNode(int key);
	CNode * insertNode(CString ID,CString NAME,int grade);
	CNode * deleteNode(Stu * stu);
	void rotate_right(CNode * NODE);
	void rotate_left(CNode * NODE);
	void setDepth();
	void draw(CDC * pDC);
	void movedraw(CDC * pDC);
	void setPosition();
	void setPosition(vector<act *> * sublist);
};

