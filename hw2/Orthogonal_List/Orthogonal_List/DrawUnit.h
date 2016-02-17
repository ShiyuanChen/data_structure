#pragma once
class CDrawUnit
{
	int x;
	int y;
	int row;
	int col;
	int rowpos;
	int colpos;
	CString data;
public:
	static int Height;
	static int Width;
	static int x0;
	static int y0;
	unsigned int isselected;
	CDrawUnit(void);
	CDrawUnit(CString ROW,CString COL,CString DATA);
	CDrawUnit(int ROW,int COL,CString DATA);
	CDrawUnit(CString ROW,CString COL,CString DATA,int X,int Y);
	~CDrawUnit(void);
	void set_X(int X);
	void set_Y(int Y);
	int get_X();
	int get_Y();
	void set_Rowpos(CString ROW);
	void set_Colpos(CString COL);
	int get_Rowpos();
	int get_Colpos();
	CString get_Data();
	void set_Data(CString DATA);
	void set_Flag();
	void unset_Flag();
	void check_Flag();
	void unit_Draw(int ROWPOS,int COLPOS,CDC* pDC);
	CPoint * arrowRight();
	CPoint * arrowLeft();
	CPoint * arrowUp();
	CPoint * arrowDown();

};

