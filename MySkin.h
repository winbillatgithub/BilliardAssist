// MySkin.h: interface for the CMySkin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSKIN_H__0E0A6B9D_538E_46EB_B118_8D5BF51BE996__INCLUDED_)
#define AFX_MYSKIN_H__0E0A6B9D_538E_46EB_B118_8D5BF51BE996__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkinDialog.h"

// ����һ��CSkinDialog�Ա�ʹ�������Լ��Ľ��䱳��
class CMySkin : public CSkinDialog  
{
public:
	CMySkin();
	virtual ~CMySkin();

	// ����������������Ա�ʹ�������Լ��ı���.
	virtual void DoGradientFill(CDC *pDC, CRect rect);
};

#endif // !defined(AFX_MYSKIN_H__0E0A6B9D_538E_46EB_B118_8D5BF51BE996__INCLUDED_)
