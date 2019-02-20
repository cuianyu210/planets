#if !defined(AFX_JUPITER_H__3D606FBC_3833_4532_952B_277F43972E49__INCLUDED_)
#define AFX_JUPITER_H__3D606FBC_3833_4532_952B_277F43972E49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Jupiter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJupiter window

class CJupiter : public CWnd
{
// Construction
public:
	CJupiter();

// Attributes
public:
private:
	static double jupiterL0[761][3];
	static double jupiterL1[370][3];
	static double jupiterL2[192][3];
	static double jupiterL3[110][3];
	static double jupiterL4[46][3];
	static double jupiterL5[11][3];
	static double jupiterB0[250][3];
	static double jupiterB1[142][3];
	static double jupiterB2[82][3];
	static double jupiterB3[43][3];
	static double jupiterB4[13][3];
	static double jupiterB5[6][3];
	static double jupiterR0[746][3];
	static double jupiterR1[382][3];
	static double jupiterR2[191][3];
	static double jupiterR3[99][3];
	static double jupiterR4[47][3];
	static double jupiterR5[10][3];


// Operations
public:
	void heliocentricSphericalJupiter(double julDay, double &jupiterL,
		 double &jupiterB, double &jupiterR);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJupiter)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJupiter();

	// Generated message map functions
protected:
	//{{AFX_MSG(CJupiter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUPITER_H__3D606FBC_3833_4532_952B_277F43972E49__INCLUDED_)
