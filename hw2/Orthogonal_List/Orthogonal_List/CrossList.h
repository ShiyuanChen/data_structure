#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include"DrawUnit.h"
using namespace std;

struct Node
{
	int row;
	int col;
	int rowpos;
	CString data;
	Node * right;
	Node * down;
	CDrawUnit * drawunit;
	Node(int row = 0,int col = 0,CString data = L"",Node* right = NULL,Node* down = NULL):row(row),col(col),data(data),right(right),down(down)
	{
		rowpos = row;
		drawunit = new CDrawUnit(row,col,data);
	}
};
struct VecNode
{
	int row;
	int col;
	Node * Vhead;
	Node * Hhead;
	VecNode(int row = 0,int col = 0,Node* vhead = NULL,Node* hhead = NULL):row(row),col(col),Vhead(vhead),Hhead(hhead){}
};

class CCrossList
{
	int row,col,scale;
public:
	vector<VecNode*> assist;
	CDrawUnit * InitHead;
	CCrossList();
	CCrossList(const CCrossList& s);
	CCrossList(int row,int col);
	~CCrossList();
	void initHead();
	vector<VecNode*> *expandVec(int ROW,int COL);
	bool existNode(int ROW,int COL) const;
	Node *insertNode(int ROW,int COL,CString DATA);
	Node *deleteNode(int ROW,int COL);
	Node *changeData(int ROW,int COL,CString DATA);

	Node *findNode(int ROW,int COL) const;
	vector<Node*> *findNode(CString DATA) const;

	void changeFlag(int ROW,int COL,int FLAG);
	void deleteAll();
	vector<Node*> *searchNode(int ROW,int COL);
	vector<vector<Node*>*> *searchNode(CString DATA);
	vector<VecNode*> *getVector();
	int getRow() const;
	int getCol() const;
	int getScale() const;
};

