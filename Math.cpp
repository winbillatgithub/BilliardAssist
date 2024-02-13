#include "stdafx.h"
#include <math.h>
#include "Math.h"

CMath::CMath(void)
{
}

CMath::~CMath(void)
{
}

/**
* Function Name:GetCrossPoint
* Usage:
* 计算白球预定轨迹圆和圆心与光标所在直线的交点
* 也就是计算白球预定轨迹点的位置
* Param:
* ptCenter: 目标球的中心点
* nRadius:  预定轨迹的直径
* ptCursor: 光标的任意位置
* ptCross:  交叉点
*/
/*
BOOL CMath::GetCrossPoint(CPoint ptCenter, int nRadius, CPoint ptCursor, CPoint* ptCross)
{
// (x-a)^2+(y-b)^2=r^2
// (y-b)(x-m)=(x-a)(y-n)
float a = (float) ptCenter.x;
float b = (float)ptCenter.y;
float m = (float)ptCursor.x;
float n = (float)ptCursor.y;
float r = (float)nRadius;
if (n-b == 0) {
return FALSE;
}

float k = (m-a)/(n-b);
float h = (a*n-b*m)/(n-b);
float i = (2*a*(m-a))/(n-b);
float j = 2*a*(a*n-b*m)/(n-b);
float e = k*k+1;
float f = 2*k*h-i-2*b;
float g = h*h-j+a*a+b*b-r*r;

float s = sqrt(f*f-4*e*g);
float y1 = (f+s)/2*e;
float x1 = ((m-a)*y1+(a*n-b*m))/(n-b);
float y2 = (f-s)/2*e;
float x2 = ((m-a)*y2+(a*n-b*m))/(n-b);

float x, y;
if (m == a) {
// 第一、二象限边界
if (n >= b) {
if (y1 >= b) {
x = x1;
y = y1;
} else {
x = x2;
y = y2;
}
// 第三、四象限边界
} else {
if (y1 < b) {
x = x1;
y = y1;
} else {
x = x2;
y = y2;
}
}
} else if (m > a) {
// 第一象限
// 第四象限
if (x1 >= a) {
x = x1;
y = y1;
} else {
x = x2;
y = y2;
}
} else {
// 第二象限
// 第三象限
if (x1 < a) {
x = x1;
y = y1;
} else {
x = x2;
y = y2;
}
}

ptCross->x = abs((int)(x + 0.5));
ptCross->y = abs((int)(y + 0.5));

return TRUE;
}
*/

/**
* Function Name:GetCrossPoint
* Usage:
* 计算白球预定轨迹圆和圆心与光标所在直线的交点
* 也就是计算白球预定轨迹点的位置
* Param:
* ptCenter: 目标球的中心点
* nRadius:  预定轨迹的直径
* ptCursor: 光标的任意位置
* ptCross:  交叉点
*/
BOOL CMath::GetCrossPoint(CPoint ptCenter, int nRadius, CPoint ptCursor, CPoint* ptCross)
{
	int cx = ptCenter.x;
	int cy = ptCenter.y;
	int r = nRadius;
	int stx = ptCenter.x;
	int sty = ptCenter.y;
	int edx = ptCursor.x;
	int edy = ptCursor.y;

	// 目标球圆心和光标重合，不可计算
	if (ptCenter == ptCursor) {
		return FALSE;
	}
	if (edx == stx) {
		if (edy > sty) {
			ptCross->x = cx;
			ptCross->y = cy + r;
		} else {
			ptCross->x = cx;
			ptCross->y = cy - r;
		}
		return TRUE;
	}
	//(x - cx )^2 + (y - cy)^2 = r^2
	//y = kx +b

	//求得直线方程
	double k = ((double)(edy - sty) ) / (edx - stx);
	double b = edy - k*edx;

	//列方程
	/*
	(1 + k^2)*x^2 - x*(2*cx -2*k*(b -cy) ) + cx*cx + ( b - cy)*(b - cy) - r*r = 0
	*/
	double x1,y1,x2,y2;
	double c = cx*cx + (b - cy)*(b- cy) -r*r;
	double a = (1 + k*k);
	double b1 = (2*cx - 2*k*(b - cy));
	//得到下面的简化方程
	// a*x^2 - b1*x + c = 0;
	double tmp = sqrt(b1*b1 - 4*a*c);
	x1 = ( b1 + tmp )/(2*a);
	y1 = k*x1 + b;
	x2 = (b1 - tmp)/(2*a);
	y2 = k*x2 + b;

	//判断求出的点是否在圆上
	double x, y;
	if (edx == cx) {
		// 第一、二象限边界
		if (edy >= cy) {
			if (y1 >= cy) {
				x = x1;
				y = y1;
			} else {
				x = x2;
				y = y2;
			}
			// 第三、四象限边界
		} else {
			if (y1 < cy) {
				x = x1;
				y = y1;
			} else {
				x = x2;
				y = y2;
			}
		}
	} else if (edx > cx) {
		// 第一象限
		// 第四象限
		if (x1 >= cx) {
			x = x1;
			y = y1;
		} else {
			x = x2;
			y = y2;
		}
	} else {
		// 第二象限
		// 第三象限
		if (x1 < cx) {
			x = x1;
			y = y1;
		} else {
			x = x2;
			y = y2;
		}
	}

	ptCross->x = (int) x;
	ptCross->y = (int) y;

	//判断求出的点是否在圆上
	double res = (x -cx)*(x -cx) + (y - cy)*(y -cy);
	if( res <= r*r + 1 && res >= r*r - 1) {
		return TRUE;
	}

	return FALSE;
}
