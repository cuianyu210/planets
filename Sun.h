#if !defined(AFX_SUN_H__1F86EBA5_321F_49B1_88C4_49EE325CC3EB__INCLUDED_)
#define AFX_SUN_H__1F86EBA5_321F_49B1_88C4_49EE325CC3EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSun window

class CSun : public CWnd
{
// Construction
public:
	CSun();

// Attributes
public:

// Operations
public:
	void geocentricLongitudeSun(double julDay, double &sunL);
	void geocentricLatitudeSun(double julDay, double &sunB);
	void geocentricRadiusSun(double julDay, double &sunR);
	void geocentricSphericalTrueSun(double julDay, double &sunLambda,
			  double &sunBeta, double &sunRadius);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSun)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSun();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSun)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUN_H__1F86EBA5_321F_49B1_88C4_49EE325CC3EB__INCLUDED_)
