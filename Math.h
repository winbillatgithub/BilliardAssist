#pragma once

class CMath
{
public:
	CMath(void);
	~CMath(void);
	static BOOL GetCrossPoint(CPoint ptCenter, int nRadius, CPoint ptCursor, CPoint* ptCross);
};
