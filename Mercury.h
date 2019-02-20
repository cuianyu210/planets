#if !defined(AFX_MERCURY_H__9FE87A31_64DA_4403_8D3C_20D213648636__INCLUDED_)
#define AFX_MERCURY_H__9FE87A31_64DA_4403_8D3C_20D213648636__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mercury.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMercury window

class CMercury : public CWnd
{
// Construction
public:
	CMercury();

// Attributes
public:
private:

	static double mercuryL0[1381][3];
	static double mercuryL1[840][3];
	static double mercuryL2[396][3];
	static double mercuryL3[154][3];
	static double mercuryL4[29][3];
	static double mercuryL5[14][3];
	static double mercuryB0[819][3];
	static double mercuryB1[495][3];
	static double mercuryB2[231][3];
	static double mercuryB3[54][3];
	static double mercuryB4[16][3];
	static double mercuryB5[11][3];
	static double mercuryR0[1216][3];
	static double mercuryR1[712][3];
	static double mercuryR2[327][3];
	static double mercuryR3[120][3];
	static double mercuryR4[19][3];
	static double mercuryR5[11][3];

// Operations
public:
	void heliocentricSphericalMercury(double julDay, double &mercuryL,
		 double &mercuryB, double &mercuryR);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMercury)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMercury();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMercury)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MERCURY_H__9FE87A31_64DA_4403_8D3C_20D213648636__INCLUDED_)
