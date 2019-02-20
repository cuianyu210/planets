#if !defined(AFX_EARTH_H__DE38BDAD_33B7_48C1_9584_F2997A7ABF4E__INCLUDED_)
#define AFX_EARTH_H__DE38BDAD_33B7_48C1_9584_F2997A7ABF4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Earth.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEarth window

class CEarth : public CWnd
{

// Construction
public:
	CEarth();

// Attributes
public:
	static double earthL0[560][3];
	static double earthL1[342][3];
	static double earthL2[143][3];
	static double earthL3[23][3];
	static double earthL4[12][3];
	static double earthL5[6][3];
	static double earthB0[185][3];
	static double earthB1[100][3];
	static double earthB2[50][3];
	static double earthB3[12][3];
	static double earthB4[6][3];
	static double earthR0[527][3];
	static double earthR1[293][3];
	static double earthR2[140][3];
	static double earthR3[28][3];
	static double earthR4[11][3];
	static double earthR5[4][3];

private:


// Operations
public:
	void heliocentricSphericalEarth(double julDay, double &earthL,
		 double &earthB, double &earthR);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEarth)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEarth();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEarth)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EARTH_H__DE38BDAD_33B7_48C1_9584_F2997A7ABF4E__INCLUDED_)
