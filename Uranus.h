#if !defined(AFX_URANUS_H__8C98BF95_249E_48D0_BF59_53879E2E7081__INCLUDED_)
#define AFX_URANUS_H__8C98BF95_249E_48D0_BF59_53879E2E7081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Uranus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUranus window

class CUranus : public CWnd
{
// Construction
public:
	CUranus();

// Attributes
public:
private:

	static double uranusL0[948][3];
	static double uranusL1[427][3];
	static double uranusL2[152][3];
	static double uranusL3[47][3];
	static double uranusL4[8][3];
	static double uranusL5[2][3];
	static double uranusB0[284][3];
	static double uranusB1[155][3];
	static double uranusB2[61][3];
	static double uranusB3[17][3];
	static double uranusB4[3][3];
	static double uranusR0[1125][3];
	static double uranusR1[515][3];
	static double uranusR2[193][3];
	static double uranusR3[56][3];
	static double uranusR4[12][3];


// Operations
public:
	void heliocentricSphericalUranus(double julDay, double &uranusL,
		 double &uranusB, double &uranusR);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUranus)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUranus();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUranus)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_URANUS_H__8C98BF95_249E_48D0_BF59_53879E2E7081__INCLUDED_)
