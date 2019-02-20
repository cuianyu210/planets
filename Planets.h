// Planets.h : main header file for the PLANETS application
//

#if !defined(AFX_PLANETS_H__2784212B_2910_4D5A_BD48_4BEC22351284__INCLUDED_)
#define AFX_PLANETS_H__2784212B_2910_4D5A_BD48_4BEC22351284__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPlanetsApp:
// See Planets.cpp for the implementation of this class
//
#define IDS_NUM_NON_CON_STARS 2479
#define IDS_NUM_CON_STARS 698
class CPlanetsApp : public CWinApp
{
public:
	CPlanetsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlanetsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPlanetsApp)
	afx_msg void OnAppAbout();
	afx_msg void OnNewFile();
	afx_msg void OnHelpFinder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLANETS_H__2784212B_2910_4D5A_BD48_4BEC22351284__INCLUDED_)
