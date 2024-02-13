// Billiard.h : main header file for the BILLIARD application
//

#if !defined(AFX_BILLIARD_H__4E471510_EC21_462D_B118_0566C467582F__INCLUDED_)
#define AFX_BILLIARD_H__4E471510_EC21_462D_B118_0566C467582F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBilliardApp:
// See Billiard.cpp for the implementation of this class
//

class CBilliardApp : public CWinApp
{
public:
	CBilliardApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBilliardApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBilliardApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BILLIARD_H__4E471510_EC21_462D_B118_0566C467582F__INCLUDED_)
