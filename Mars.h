#if !defined(AFX_MARS_H__B1C6249D_F16F_4B9A_800C_E1BE96E2C3B5__INCLUDED_)
#define AFX_MARS_H__B1C6249D_F16F_4B9A_800C_E1BE96E2C3B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mars.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMars window

class CMars : public CWnd
{
// Construction
public:
	CMars();

// Attributes
public:
private:

	static double marsL0[1218][3];
	static double marsL1[687][3];
	static double marsL2[311][3];
	static double marsL3[130][3];
	static double marsL4[37][3];
	static double marsL5[16][3];
	static double marsB0[442][3];
	static double marsB1[288][3];
	static double marsB2[131][3];
	static double marsB3[42][3];
	static double marsB4[12][3];
	static double marsB5[6][3];
	static double marsR0[1119][3];
	static double marsR1[597][3];
	static double marsR2[314][3];
	static double marsR3[112][3];
	static double marsR4[29][3];
	static double marsR5[10][3];


// Operations
public:
	void heliocentricSphericalMars(double julDay, double &marsL,
		 double &marsB, double &marsR);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMars)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMars();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMars)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARS_H__B1C6249D_F16F_4B9A_800C_E1BE96E2C3B5__INCLUDED_)
