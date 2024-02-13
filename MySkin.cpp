// MySkin.cpp: implementation of the CMySkin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Billiard.h"
#include "MySkin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMySkin::CMySkin()
{

}

CMySkin::~CMySkin()
{

}

void CMySkin::DoGradientFill(CDC *pDC, CRect rect)
{
	CBitmap			BackgroundBitmap;
	CDC				BackgroundDC;
	CBitmap			*pOldBitmap=NULL;
	int				Width=0;
	int				Height=0;
	BITMAP			BitMapStruct={NULL};
	
	// 准备好一个背景DC
	BackgroundBitmap.LoadBitmap(IDB_BITMAP_BACKGROUND);
	
	BackgroundDC.CreateCompatibleDC(pDC);
	pOldBitmap=BackgroundDC.SelectObject(&BackgroundBitmap);
	
	// 获取背景图的大小.
	BackgroundBitmap.GetBitmap(&BitMapStruct);
	Width=BitMapStruct.bmWidth;
	Height=BitMapStruct.bmHeight;


	// 这个渐变的背景，如果放大不会出现任何问题，但如果被压缩，会出现一些奇怪的线条。
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&BackgroundDC,0,0,Width,min(Height,rect.Height()),SRCCOPY);

}
