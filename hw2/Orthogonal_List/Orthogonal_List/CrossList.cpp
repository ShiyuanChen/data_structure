#include "stdafx.h"
#include "CrossList.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include"DrawUnit.h"
using namespace std;


CCrossList::CCrossList():row(0),col(0),scale(0),assist(){InitHead = new CDrawUnit(0,0,L"");}
CCrossList::CCrossList(int row,int col):row(row),col(col),scale(max(row,col))
{
	InitHead = new CDrawUnit(0,0,L"");
	for(int i = 0;i < min(row,col);i ++)
	{
		assist.push_back(new VecNode(i+1,i+1,new Node(i+1,0),new Node(0,i+1)));
	}
	if(row >= col)
	{
		for(int j = 0;j < row - col;j++)
			assist.push_back(new VecNode(j + col+1,j + col+1,new Node(col + j + 1,0),NULL));
	}
	else
	{
		for(int j = 0;j < col - row;j++)
			assist.push_back(new VecNode(j + row+1,j + row+1,NULL,new Node(0,row + j + 1)));
	}
	initHead();
}
CCrossList::CCrossList(const CCrossList& s):row(s.row),col(s.col),scale(s.scale)
{
	InitHead = new CDrawUnit(0,0,L"");
	for(int i = 0;i<max(s.row,s.col);i++)
	{
		Node *temphhead = NULL;
		Node *tempvhead = NULL;
		if(s.assist.at(i)->Hhead!=NULL)
			temphhead = new Node(0,i+1);
		if(s.assist.at(i)->Vhead!=NULL)
			tempvhead = new Node(i+1,0);
		VecNode *temp = new VecNode(i+1,i+1,tempvhead,temphhead);
		assist.push_back(temp);
	}
	initHead();
	for(int i = 1;i <= row;i++)
	{
		for(int j = 1;j <= col;j++)
		{
			if(s.existNode(i,j))
			{
				insertNode(i,j,s.findNode(i,j)->data);
			}
		}
	}
}
CCrossList::~CCrossList()
{
	for(int i = 0;i < min(row,col);i ++)
	{
		delete assist.at(i)->Hhead;
		delete assist.at(i)->Vhead;
	}
	if(row >= col)
	{
		for(int j = 0;j < row - col;j++)
			delete assist.at(j + col)->Vhead;
	}
	else
	{
		for(int j = 0;j < col - row;j++)
			delete assist.at(j + row)->Hhead;
	}
	assist.~vector();
}
void CCrossList::initHead()
{
	for(int i = 1;i <= row;i++)
	{
		if(assist.at(i - 1)->Vhead->right == NULL)
		{
			assist.at(i - 1)->Vhead->right = assist.at(i - 1)->Vhead;
		}
	}
	for(int j = 1;j <= col;j++)
	{
		if(assist.at(j - 1)->Hhead->down == NULL)
		{
			assist.at(j - 1)->Hhead->down = assist.at(j - 1)->Hhead;
		}
	}
}
vector<VecNode*> * CCrossList::expandVec(int ROW,int COL)    //扩充辅助向量，添加头节点
{
	if(ROW > scale)
	{
		if(scale > row)
		{
			for(int i = 0;i < scale - row;i ++)
			{
				assist.at(i + row)->Vhead = new Node(row + i + 1,0);
			}
		}
		for(int i = 0;i < ROW - scale;i ++)
		{
			assist.push_back(new VecNode(i + scale +1,i + scale +1,new Node(i + scale +1,0),NULL));
		}
		scale = ROW;
		row = ROW;
	}
	else if(ROW > row)
	{
		for(int i = 0;i < ROW - row;i ++)
		{
			assist.at(i + row)->Vhead = new Node(row + i + 1,0);
		}
		row = ROW;
	}
	if(COL > scale)
	{
		if(scale > col)
		{
			for(int i = 0;i < scale - col;i ++)
			{
				assist.at(i + col)->Hhead = new Node(0,col + i + 1);
			}
		}
		for(int i = 0;i < COL - scale;i ++)
		{
			assist.push_back(new VecNode(i + scale +1,i + scale +1,NULL,new Node(0,i + scale +1)));
		}
		scale = COL;
		col = COL;
	}
	else if(COL > col)
	{
		for(int i = 0;i < COL - col;i ++)
		{
			assist.at(i + col)->Hhead = new Node(0,col + i + 1);
		}
		col = COL;
	}
	initHead();
	return &assist;
}
bool CCrossList::existNode(int ROW,int COL) const
{
	if(ROW > row || COL > col || ROW == 0 || COL == 0)
		return false;
	else
	{
		Node * nodeptr = assist.at(COL - 1)->Hhead->down;
		while(nodeptr->row <= ROW)
		{
			if(nodeptr->row == ROW)
				return true;
			if(nodeptr->down == assist.at(COL - 1)->Hhead)
				break;
			nodeptr = nodeptr->down;
		}
		return false;
	}
}
Node * CCrossList:: insertNode(int ROW,int COL,CString DATA)
{
	if(!existNode(ROW,COL) && ROW != 0 && COL != 0) 
	{
		int prerow = row;
		expandVec(ROW,COL);
		Node * nodeptr = assist.at(COL - 1)->Hhead;
		while(nodeptr->down->row < ROW && nodeptr->down->row != 0)
		{
			nodeptr = nodeptr->down;
		}
		Node *newnode = new Node(ROW,COL,DATA,NULL,nodeptr->down);
		nodeptr->down = newnode;

		nodeptr = assist.at(ROW - 1)->Vhead;

		while(nodeptr->right->col < COL && nodeptr->right->col != 0)
		{
			nodeptr = nodeptr->right;
		}
		newnode->right = nodeptr->right;
		nodeptr->right = newnode;
		return newnode;
	}
	else
		return NULL;
}

Node * CCrossList:: deleteNode(int ROW,int COL)
{
	if(!existNode(ROW,COL))
		return NULL;
	else
	{
		Node * deletenode = findNode(ROW,COL);
		Node * nodeptr = assist.at(COL - 1)->Hhead;
		while(nodeptr->down->row < ROW)
		{
			nodeptr = nodeptr->down;
		}
		nodeptr->down = deletenode->down;

		nodeptr = assist.at(ROW - 1)->Vhead;
		while(nodeptr->right->col < COL)
		{
			nodeptr = nodeptr->right;
		}
		nodeptr->right = deletenode->right;

		while(COL != 0 && COL == col && assist.at(COL - 1)->Hhead->down == assist.at(COL - 1)->Hhead)
		{
			if(row >= col)
			{
				delete assist.at(COL - 1)->Hhead;
				assist.at(COL - 1)->Hhead = NULL;
				col --;
			}
			else
			{
				delete assist.at(COL - 1)->Hhead;
				VecNode *tempvec = assist.back();
				assist.pop_back();
				delete tempvec;
				col --;
				scale --;
			}
			COL--;
		}
		while(ROW != 0 && ROW == row && assist.at(ROW - 1)->Vhead->right == assist.at(ROW - 1)->Vhead)
		{
			if(col >= row)
			{
				delete assist.at(ROW - 1)->Vhead;
				assist.at(ROW - 1)->Vhead = NULL;
				row --;
			}
			else
			{
				delete assist.at(ROW - 1)->Vhead;
				VecNode *tempvec = assist.back();
				assist.pop_back();
				delete tempvec;
				row --;
				scale --;
			}
			ROW --;
		}

		return deletenode;
	}

}
Node * CCrossList:: changeData(int ROW,int COL,CString DATA)
{
	if(!existNode(ROW,COL))
		return NULL;
	else if(ROW == 0 || COL == 0)
	{
		return findNode(ROW,COL);
	}
	else
	{
		Node * changenode = findNode(ROW,COL);
		changenode->data = DATA;
		changenode->drawunit->set_Data(DATA);
		return changenode;
	}
}

Node * CCrossList:: findNode(int ROW,int COL) const
{
	if(!existNode(ROW,COL))
		return NULL;
	else
	{
		Node * nodeptr = assist.at(COL - 1)->Hhead->down;
		while(nodeptr->row <= ROW)
		{
			if(nodeptr->row == ROW)
				return nodeptr;
			if(nodeptr->down == assist.at(COL - 1)->Hhead)
				break;
			nodeptr = nodeptr->down;
		}
		return NULL;
	}
}
vector<Node*> * CCrossList:: findNode(CString DATA) const
{
	vector<Node*> *nodelist = new vector<Node*>;
	for(int i = 0;i < col;i++)
	{
		Node * nodeptr = assist.at(i)->Hhead->down;
		while(nodeptr != assist.at(i)->Hhead)
		{
			if(nodeptr->data == DATA)
			{
				nodelist->push_back(nodeptr);
			}
			nodeptr = nodeptr->down;
		}
	}
	return nodelist;
}

void CCrossList:: changeFlag(int ROW,int COL,int FLAG)
{
	Node * nodeptr = findNode(ROW,COL);
	if(FLAG == 0)
		nodeptr->drawunit->unset_Flag();
	else if(FLAG == 1)
		nodeptr->drawunit->set_Flag();
	else
		nodeptr->drawunit->check_Flag();
}

void CCrossList:: deleteAll()
{
	for(int i = 1;i <= row; i++)
	{
		for(int j = 1;j <= col; j++)
		{
			deleteNode(i,j);
		}
	}
	assist.clear();
}

vector<Node*> * CCrossList:: searchNode(int ROW,int COL)
{
	if(!existNode(ROW,COL))
		return NULL;
	else
	{
		vector<Node*> *nodelist = new vector<Node*>;
		for(int i = 0;i < COL;i++)
			nodelist->push_back(assist.at(i)->Hhead);
		Node * nodeptr = assist.at(COL - 1)->Hhead->down;
		while(nodeptr->row <= ROW)
		{
			nodelist->push_back(nodeptr);
			if(nodeptr->row == ROW)
				return nodelist;
			if(nodeptr->down == assist.at(COL - 1)->Hhead)
				break;
			nodeptr = nodeptr->down;
		}
		return NULL;
	}
}

vector<vector<Node*>*> * CCrossList:: searchNode(CString DATA)
{
	vector<vector<Node*>*> * tracelist = new vector<vector<Node*>*>;
	vector<Node*> *check = findNode(DATA);
	if(check->size() == 0)
		return NULL;
	else
	{
		for(unsigned int i = 0;i < check->size();i ++)
		{
			Node * tptr = check->at(i);
			tracelist->push_back(searchNode(tptr->row,tptr->col));
		}
		return tracelist;
	}
}

vector<VecNode*> * CCrossList:: getVector()
{
	return &assist;
}
int CCrossList:: getRow() const
{
	return row;
}

int CCrossList:: getCol() const
{
	return col;
}
int CCrossList:: getScale() const
{
	return scale;
}