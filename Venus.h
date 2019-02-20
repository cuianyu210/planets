#if !defined(AFX_VENUS_H__379DA5D5_AEEB_4D65_9887_0C539EB09BF8__INCLUDED_)
#define AFX_VENUS_H__379DA5D5_AEEB_4D65_9887_0C539EB09BF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Venus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVenus window

class CVenus : public CWnd
{
// Construction
public:
	CVenus();

// Attributes
public:
private:

	static double venusL0[368][3];
	static double venusL1[216][3];
	static double venusL2[71][3];
	static double venusL3[10][3];
	static double venusL4[6][3];
	static double venusL5[6][3];
	static double venusB0[211][3];
	static double venusB1[134][3];
	static double venusB2[60][3];
	static double venusB3[16][3];
	static double venusB4[6][3];
	static double venusB5[5][3];
	static double venusR0[331][3];
	static double venusR1[181][3];
	static double venusR2[64][3];
	static double venusR3[8][3];
	static double venusR4[4][3];
	static double venusR5[3][3];

// Operations
public:
	void heliocentricSphericalVenus(double julDay, double &venusL,
		 double &venusB, double &venusR);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVenus)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVenus();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVenus)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VENUS_H__379DA5D5_AEEB_4D65_9887_0C539EB09BF8__INCLUDED_)
