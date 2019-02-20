#if !defined(AFX_SATURN_H__815ACA3D_C78D_435A_B3BA_5CFF33CBC9A0__INCLUDED_)
#define AFX_SATURN_H__815ACA3D_C78D_435A_B3BA_5CFF33CBC9A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Saturn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaturn window

class CSaturn : public CWnd
{
// Construction
public:
	CSaturn();

// Attributes
public:
private:

	static double saturnL0[1153][3];
	static double saturnL1[643][3];
	static double saturnL2[322][3];
	static double saturnL3[149][3];
	static double saturnL4[69][3];
	static double saturnL5[28][3];
	static double saturnB0[501][3];
	static double saturnB1[261][3];
	static double saturnB2[112][3];
	static double saturnB3[59][3];
	static double saturnB4[27][3];
	static double saturnB5[12][3];
	static double saturnR0[1206][3];
	static double saturnR1[640][3];
	static double saturnR2[343][3];
	static double saturnR3[158][3];
	static double saturnR4[65][3];
	static double saturnR5[29][3];


// Operations
public:
	void heliocentricSphericalSaturn(double julDay, double &saturnL,
		 double &saturnB, double &saturnR);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaturn)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSaturn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSaturn)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SATURN_H__815ACA3D_C78D_435A_B3BA_5CFF33CBC9A0__INCLUDED_)
