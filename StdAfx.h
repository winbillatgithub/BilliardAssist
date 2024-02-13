// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__93C5E45A_3831_4ECD_A35B_C23E4C436355__INCLUDED_)
#define AFX_STDAFX_H__93C5E45A_3831_4ECD_A35B_C23E4C436355__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_DEPRECATE 1 // For compile warnning

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "Resource.h"

// 这段代码将默认的按钮式样设成3DMark05的风格
//#define SKIN_BUTTON_INIT_MACRO		\
//	m_nNormalBitmapResID=IDB_BITMAPNOFOCUS;	\
//	m_nFocusBitmapResID=IDB_BITMAPFOCUS;	\
//	m_nHoverBitmapResID=IDB_BITMAPFOCUS;	\
//	m_nPressedBitmapResID=IDB_BITMAPFOCUSSELECTED;	\


// 这段代码将默认按钮式样设成XP风格.
#define SKIN_BUTTON_INIT_MACRO		\
	m_nNormalBitmapResID=IDB_BITMAP_XPNORMAL;	\
	m_nFocusBitmapResID=IDB_BITMAP_XPFOCUS;	\
	m_nHoverBitmapResID=IDB_BITMAP_XPHOVER;	\
	m_nPressedBitmapResID=IDB_BITMAP_XPDOWN;	\
	m_nXPos=3;									\
	m_nYPos=3;									\
	m_bEnableStretch=TRUE;						\


#define MAKE_3DMARK05STYLE_RED(Obj)	\
	Obj.m_nFocusBitmapResID=IDB_3DMARK_FOCUS;	\
	Obj.m_nHoverBitmapResID=0;					\
	Obj.m_nNormalBitmapResID=IDB_3DMARK_NORMAL;	\
	Obj.m_nPressedBitmapResID=IDB_3DMARK_DOWN;	\
	Obj.m_nXPos=10;	\
	Obj.m_nYPos=6;	\
	Obj.m_bEnableStretch=TRUE;	\


#define MAKE_3DMARK05STYLE_BLUE(obj)	\
	obj.m_nXPos=10;				\
	obj.m_nYPos=9;				\
	obj.m_nNormalBitmapResID=IDB_BITMAPNOFOCUS;	\
	obj.m_nFocusBitmapResID=IDB_BITMAPFOCUS;	\
	obj.m_nHoverBitmapResID=0;	\
	obj.m_nPressedBitmapResID=IDB_BITMAPFOCUSSELECTED;	\
	obj.m_bEnableStretch=TRUE;	\


#include "SkinDialog.h"
#include "MySkin.h"

// CMySkin是CSkinDialog的一个子类,目的是演示一下如何使用自己的渐变绘制函数.
// 可以使用以前的 CSkinDialog ,只要把CMySkin 换了就行了.
extern CMySkin					g_SkinDialog;			// 为了避免在每个cpp里都加上这句话,我们把它写在这里

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__93C5E45A_3831_4ECD_A35B_C23E4C436355__INCLUDED_)
