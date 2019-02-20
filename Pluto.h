#if !defined(AFX_PLUTO_H__F27BB3F9_FE41_40C2_8AFF_D2CD4AA31B8C__INCLUDED_)
#define AFX_PLUTO_H__F27BB3F9_FE41_40C2_8AFF_D2CD4AA31B8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pluto.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPluto window

class CPluto : public CWnd
{
// Construction
public:
	CPluto();

// Attributes
public:
private:

	static double FQ1[83];
	static double FQ2[20];
	static double FQ3[6];
	static double AX[5];
	static double AY[5];
	static double AZ[5];
	static double CXSX1[83][2];
	static double CXSX2[20][2];
	static double CXSX3[6][2];
	static double CYSY1[83][2];
	static double CYSY2[20][2];
	static double CYSY3[6][2];
	static double CZSZ1[83][2];
	static double CZSZ2[20][2];
	static double CZSZ3[6][2];


// Operations
public:
	void heliocentricSphericalPluto(double julDay, double &plutoL,
		 double &plutoB, double &plutoR);
	void heliocentricCartesianPluto(double julDay, double &plutoX,
		 double &plutoY, double &plutoZ);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPluto)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPluto();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPluto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLUTO_H__F27BB3F9_FE41_40C2_8AFF_D2CD4AA31B8C__INCLUDED_)
