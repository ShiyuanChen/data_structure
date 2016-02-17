#include "stdafx.h"
#include "Node.h"
#include "Tree.h"
#include <vector>
#include "define.h"
using namespace std;


CTree::CTree(void)
	:root(NULL)
	,num(0)
	,depth(0)
	,xdelta(0)
	,ydelta(0)
	,rootpos(0)
{
}


CTree::~CTree(void)
{
}
CNode* CTree::grandparent(CNode *NODE)
{
	if(NODE->parent != NULL)
		return NODE->parent->parent;
	else
		return NULL;
}

CNode* CTree::uncle(CNode *NODE)
{
	if(grandparent(NODE) != NULL)
	{
		if (NODE->parent == grandparent(NODE)->left)
			return grandparent(NODE)->right;
		else
			return grandparent(NODE)->left;
	}
	else
		return NULL;
}
CNode* CTree::sibling(CNode *NODE)
{
	if(NODE->parent != NULL)
	{
		if (NODE == NODE->parent->left)
			return NODE->parent->right;
		else
			return NODE->parent->left;
	}
	else
		return NULL;
}

int CTree::grade2key(int grade)
{
	if(grade < 50)
		return 1;
	else if(grade < 60)
		return 2;
	else if(grade < 65)
		return 3;
	else if(grade < 70)
		return 4;
	else if(grade < 75)
		return 5;
	else if(grade < 80)
		return 6;
	else if(grade < 85)
		return 7;
	else if(grade < 90)
		return 8;
	else if(grade < 95)
		return 9;
	else if(grade <= 100)
		return 10;
	else
		return 1;
}
int CTree::section2key(CString section)
{
	if(section == L"E")
		return 1;
	else if(section == L"D")
		return 2;
	else if(section == L"C")
		return 3;
	else if(section == L"C+")
		return 4;
	else if(section == L"B-")
		return 5;
	else if(section == L"B")
		return 6;
	else if(section == L"B+")
		return 7;
	else if(section == L"A")
		return 8;
	else if(section == L"AA")
		return 9;
	else if(section == L"AA+")
		return 10;
	else
		return 1;
}
void CTree::rotate_right(CNode * NODE)
{
	CNode * lchild = NODE->left;

	movelist.push_back(new act(lchild,lchild->x,lchild->y,NODE->x,NODE->y));
	lchild->delta = NODE->delta;
	lchild->nextx = NODE->x;
	lchild->nexty = NODE->y;

	NODE->left = lchild->right;
	lchild->right = NODE;
	if(NODE->parent == NULL)
	{
		root = lchild;
		lchild->parent = NULL;
	}
	else if(NODE->parent->left == NULL || NODE->parent->left->key < NODE->key)
	{
		NODE->parent->right = lchild;
		lchild->parent = NODE->parent;
	}
	else
	{
		NODE->parent->left = lchild;
		lchild->parent = NODE->parent;
	}
	NODE->parent = lchild;
	if(NODE->left != NULL)
		NODE->left->parent = NODE;
	setPosition(&movelist);
}
void CTree::rotate_left(CNode * NODE)
{
	CNode * rchild = NODE->right;

	movelist.push_back(new act(rchild,rchild->x,rchild->y,NODE->x,NODE->y));
	rchild->delta = NODE->delta;
	rchild->nextx = NODE->x;
	rchild->nexty = NODE->y;

	NODE->right = rchild->left;
	rchild->left = NODE;
	if(NODE->parent == NULL)
	{
		root = rchild;
		rchild->parent = NULL;
	}
	else if(NODE->parent->left == NULL || NODE->parent->left->key < NODE->key)
	{
		NODE->parent->right = rchild;
		rchild->parent = NODE->parent;
	}
	else
	{
		NODE->parent->left = rchild;
		rchild->parent = NODE->parent;
	}
	NODE->parent = rchild;
	if(NODE->right != NULL)
		NODE->right->parent = NODE;
	setPosition(&movelist);
}

CNode* CTree::findInsert(CNode * newnode,CNode * f,CNode * subtree)
{
	if(!subtree)
	{	
		subtree=newnode;
		subtree->left=NULL;
		subtree->right=NULL;
		if(!f)
		{
			root = subtree;
			return subtree;
		}
		else
			subtree->parent = f;
		if(subtree->key < f->key)
		{
			f->left=subtree;
			//subtree->index = 2 * f->index + 1;
		}
		else
		{
			f->right=subtree;
			//subtree->index = 2 * f->index + 2;
		}
		return subtree;
	}
	else
	{
		if(newnode->key < subtree->key)
			return findInsert(newnode,subtree,subtree->left);
		else if(newnode->key > subtree->key)
			return findInsert(newnode,subtree,subtree->right);
		else
			return NULL;
	}
}
CNode* CTree::find(int key,CNode * f,CNode * subtree)
{
	if(!subtree)
	{	
		return NULL;
	}
	else
	{
		if(key < subtree->key)
			return find(key,subtree,subtree->left);
		else if(key > subtree->key)
			return find(key,subtree,subtree->right);
		else
			return subtree;
	}
}
Stu * CTree::find(CString ID)
{
	for(unsigned int i = 0;i < stulist.size();i++)
	{
		if(stulist.at(i)->ID == ID)
			return stulist.at(i);
	}
	return NULL;
}
Stu * CTree::search(CString ID,CNode * subtree,Stu * &result)
{
	if(!subtree)
	{	
		return NULL;
	}
	else
	{
		if(result != NULL)
			return result;
		else
		{
			for(unsigned int i = 0;i < subtree->stu.size();i++)
			{
				if(subtree->stu.at(i)->ID == ID)
				{
					result = subtree->stu.at(i);
					return result;
				}
			}
			search(ID,subtree->left,result);
			search(ID,subtree->right,result);
			return result;
		}
	}
}
CNode * CTree::insertNode(CString ID,CString NAME,int grade)
{
	for(unsigned int k = 0;k < stulist.size();k ++)
	{
		if(stulist.at(k)->ID == ID)
			return NULL;
	}
	int key = grade2key(grade);
	CNode *newnode = new CNode(key,RED);
	if(findInsert(newnode,NULL,root) != NULL)
	{
		num ++;
		//insert_case1(newnode);
		setDepth();
	}
	else
	{
		newnode = find(key,NULL,root);
	}
	Stu * stuptr = newnode->addStu(ID,NAME,grade);
	stulist.push_back(stuptr);
	return newnode;
}
CNode * CTree::deleteNode(Stu * stu)
{
	int key = grade2key(stu->grade);
	for(unsigned int i = 0;i < stulist.size();i++)
	{
		if(stulist.at(i)->ID == stu->ID)
		{
			stulist.erase(stulist.begin() + i);
			break;
		}
	}
	CNode * nodeptr = find(key,NULL,root);
	nodeptr->deleteStu(stu->ID);
	if(nodeptr->stu.size() == 0)
	{
		//deleteNode(nodeptr);
		num --;
		return nodeptr;
	}
	else
		return NULL;
}

void CTree::setDepth()
{
	vector<CNode *> *queue = new vector<CNode *>;
	int front = 0;
	int rear = 0;
	int cur1 = 0;
	int cur2 = 0;
	depth = 0;
	CNode * ptr = root;
	if(root == NULL)
		return;
	else
	{
		queue->push_back(root);
		cur1 = 1;
		depth = 1;
		while(front <= rear)
		{
			if(cur1 == 0)
			{
				cur1 = cur2;
				cur2 = 0;
				depth ++;
			}
			if(queue->at(front)->left != NULL)
			{
				rear++;
				cur2 ++;
				queue->push_back(queue->at(front)->left);
			}
			if(queue->at(front)->right != NULL)
			{
				rear++;
				cur2 ++;
				queue->push_back(queue->at(front)->right);
			}

			front ++;
			cur1 --;
		}
		queue->clear();
	}
}

void CTree::draw(CDC * pDC)
{
	vector<CNode *> *queue = new vector<CNode *>;
	int front = 0;
	int rear = 0;
	CNode * ptr = root;
	if(root == NULL)
		return;
	else
	{
		queue->push_back(root);
		queue->at(front)->delta = xdelta;
		queue->at(front)->draw(xdelta,rootpos,pDC);

		CPen *pe = new CPen(PS_SOLID,2,RGB(0,0,0));
		CPen * oldpen =  pDC->SelectObject(pe);
		while(front <= rear)
		{
			if(queue->at(front)->left != NULL)
			{
				rear++;
				queue->at(front)->left->delta = queue->at(front)->delta / 2;
				queue->at(front)->left->prex = 0;
				queue->at(front)->left->prey = 0;
				queue->at(front)->left->nextx = 0;
				queue->at(front)->left->nexty = 0;
				pDC->MoveTo(queue->at(front)->x,queue->at(front)->y);
				pDC->LineTo(queue->at(front)->x - queue->at(front)->left->delta,queue->at(front)->y + ydelta);
				queue->at(front)->draw(queue->at(front)->x,queue->at(front)->y,pDC);
				queue->at(front)->left->draw(queue->at(front)->x - queue->at(front)->left->delta,queue->at(front)->y + ydelta,pDC);

				queue->push_back(queue->at(front)->left);
			}
			if(queue->at(front)->right != NULL)
			{
				rear++;
				queue->at(front)->right->delta = queue->at(front)->delta / 2;
				queue->at(front)->right->prex = 0;
				queue->at(front)->right->prey = 0;
				queue->at(front)->right->nextx = 0;
				queue->at(front)->right->nexty = 0;
				pDC->MoveTo(queue->at(front)->x,queue->at(front)->y);
				pDC->LineTo(queue->at(front)->x + queue->at(front)->right->delta,queue->at(front)->y + ydelta);
				queue->at(front)->draw(queue->at(front)->x,queue->at(front)->y,pDC);
				queue->at(front)->right->draw(queue->at(front)->x + queue->at(front)->right->delta,queue->at(front)->y + ydelta,pDC);

				queue->push_back(queue->at(front)->right);
			}

			front ++;
		}
		queue->clear();
		pe->DeleteObject();
	}
}
void CTree::movedraw(CDC * pDC)
{
	vector<CNode *> *queue = new vector<CNode *>;
	int front = 0;
	int rear = 0;
	CNode * ptr = root;
	if(root == NULL)
		return;
	else
	{
		queue->push_back(root);
		queue->at(front)->delta = xdelta;
		if(queue->at(front)->left != queue->at(front) && queue->at(front)->right != queue->at(front))
		{
			queue->at(front)->draw(pDC);
		}

		CPen *pe = new CPen(PS_SOLID,2,RGB(0,0,0));
		CPen * oldpen =  pDC->SelectObject(pe);
		while(front <= rear)
		{
			if(queue->at(front)->left != queue->at(front) && queue->at(front)->right != queue->at(front))
			{
				if(queue->at(front)->left != NULL && queue->at(front)->left->left != queue->at(front)->left && queue->at(front)->left->right != queue->at(front)->left)
				{
					rear++;
					pDC->MoveTo(queue->at(front)->x,queue->at(front)->y);
					pDC->LineTo(queue->at(front)->left->x,queue->at(front)->left->y);
					queue->at(front)->draw(pDC);
					queue->at(front)->left->draw(pDC);

					queue->push_back(queue->at(front)->left);
				}
				if(queue->at(front)->right != NULL && queue->at(front)->right->left != queue->at(front)->right && queue->at(front)->right->right != queue->at(front)->right)
				{
					rear++;
					pDC->MoveTo(queue->at(front)->x,queue->at(front)->y);
					pDC->LineTo(queue->at(front)->right->x,queue->at(front)->right->y);
					queue->at(front)->draw(pDC);
					queue->at(front)->right->draw(pDC);

					queue->push_back(queue->at(front)->right);
				}
			}
			front ++;
		}
		queue->clear();
		pe->DeleteObject();
	}
}
void CTree::setPosition()
{
	vector<CNode *> *queue = new vector<CNode *>;
	int front = 0;
	int rear = 0;
	CNode * ptr = root;
	if(root == NULL)
		return;
	else
	{
		queue->push_back(root);
		queue->at(front)->delta = xdelta;
		queue->at(front)->setPosition(xdelta,rootpos);
		while(front <= rear)
		{
			if(queue->at(front)->left != queue->at(front) && queue->at(front)->right != queue->at(front))
			{
				if(queue->at(front)->left != NULL && queue->at(front)->left->left != queue->at(front)->left && queue->at(front)->left->right != queue->at(front)->left)
				{
					rear++;
					queue->at(front)->left->delta = queue->at(front)->delta / 2;
					queue->at(front)->left->setPosition(queue->at(front)->x - queue->at(front)->left->delta,queue->at(front)->y + ydelta);
					queue->push_back(queue->at(front)->left);
				}
				if(queue->at(front)->right != NULL && queue->at(front)->right->left != queue->at(front)->right && queue->at(front)->right->right != queue->at(front)->right)
				{
					rear++;
					queue->at(front)->right->delta = queue->at(front)->delta / 2;
					queue->at(front)->right->setPosition(queue->at(front)->x + queue->at(front)->right->delta,queue->at(front)->y + ydelta);
					queue->push_back(queue->at(front)->right);
				}
			}
			front ++;
		}
		queue->clear();
	}
}

void CTree::setPosition(vector<act *> * sublist)
{
	vector<CNode *> *queue = new vector<CNode *>;
	int front = 0;
	int rear = 0;

	if(sublist->size() == 0)
		return;
	else
	{
		CNode * node = sublist->at(0)->node;
		queue->push_back(node);
		while(front <= rear)
		{
			if(queue->at(front)->left != queue->at(front) && queue->at(front)->right != queue->at(front))
			{
				if(queue->at(front)->left != NULL && queue->at(front)->left->left != queue->at(front)->left && queue->at(front)->left->right != queue->at(front)->left)
				{
					rear++;

					queue->at(front)->left->delta = queue->at(front)->delta / 2;
					queue->at(front)->left->nextx = queue->at(front)->nextx - queue->at(front)->left->delta;
					queue->at(front)->left->nexty = queue->at(front)->nexty + ydelta;
					sublist->push_back(new act(queue->at(front)->left,queue->at(front)->left->x,queue->at(front)->left->y,queue->at(front)->left->nextx,queue->at(front)->left->nexty));

					queue->push_back(queue->at(front)->left);
				}
				if(queue->at(front)->right != NULL && queue->at(front)->right->left != queue->at(front)->right && queue->at(front)->right->right != queue->at(front)->right)
				{
					rear++;

					queue->at(front)->right->delta = queue->at(front)->delta / 2;
					queue->at(front)->right->nextx = queue->at(front)->nextx + queue->at(front)->right->delta;
					queue->at(front)->right->nexty = queue->at(front)->nexty + ydelta;
					sublist->push_back(new act(queue->at(front)->right,queue->at(front)->right->x,queue->at(front)->right->y,queue->at(front)->right->nextx,queue->at(front)->right->nexty));

					queue->push_back(queue->at(front)->right);
				}
			}
			front ++;
		}
		queue->clear();
	}
}
