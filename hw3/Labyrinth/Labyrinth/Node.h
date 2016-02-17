#pragma once
class CNode
{
public:
	int x;
	int y;
	int pre;
	int flag;
	int f,g,h;
	static double width;
	static double height;
	CNode(void);
	CNode(int X,int Y,int FLAG);
	CNode(const CNode &node);
	~CNode(void);
	void setFlag(int FLAG);
	int getFlag(void);
	void setf(int G,int H);
	void Draw(int FLAG,CDC * pDC);//-1±ß½ç,
	void Draw(CDC * pDC);//-1±ß½ç,
	bool lessthan (const CNode* node) const  
    {  
        return f > node->f;
    }  
};

class Compare  
{  
public:  
    bool operator () (CNode *node1,CNode *node2)  
    {  
        return node1->lessthan(node2);  
    }  
};  