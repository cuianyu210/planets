#if !defined(AFX_NEPTUNE_H__04F06ADA_5FA6_490B_B83E_FB914B2C885B__INCLUDED_)
#define AFX_NEPTUNE_H__04F06ADA_5FA6_490B_B83E_FB914B2C885B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Neptune.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNeptune window

class CNeptune : public CWnd
{
// Construction
public:
	CNeptune();

// Attributes
public:
private:

	static double neptuneL0[424][3];
	static double neptuneL1[184][3];
	static double neptuneL2[58][3];
	static double neptuneL3[16][3];
	static double neptuneL4[3][3];
	static double neptuneL5[2][3];
	static double neptuneB0[173][3];
	static double neptuneB1[83][3];
	static double neptuneB2[26][3];
	static double neptuneB3[10][3];
	static double neptuneB4[2][3];
	static double neptuneB5[2][3];
	static double neptuneR0[608][3];
	static double neptuneR1[251][3];
	static double neptuneR2[73][3];
	static double neptuneR3[23][3];
	static double neptuneR4[8][3];


// Operations
public:
	void heliocentricSphericalNeptune(double julDay, double &neptuneL,
		 double &neptuneB, double &neptuneR);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNeptune)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNeptune();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNeptune)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEPTUNE_H__04F06ADA_5FA6_490B_B83E_FB914B2C885B__INCLUDED_)
