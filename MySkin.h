// MySkin.h: interface for the CMySkin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSKIN_H__0E0A6B9D_538E_46EB_B118_8D5BF51BE996__INCLUDED_)
#define AFX_MYSKIN_H__0E0A6B9D_538E_46EB_B118_8D5BF51BE996__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkinDialog.h"

// 重载一个CSkinDialog以便使用我们自己的渐变背景
class CMySkin : public CSkinDialog  
{
public:
	CMySkin();
	virtual ~CMySkin();

	// 我们重载这个函数以便使用我们自己的背景.
	virtual void DoGradientFill(CDC *pDC, CRect rect);
};

#endif // !defined(AFX_MYSKIN_H__0E0A6B9D_538E_46EB_B118_8D5BF51BE996__INCLUDED_)
