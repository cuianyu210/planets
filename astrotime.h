#if !defined(AFX_ASTROTIME_H__0243CCB5_845A_4E6F_AB67_AFF5A176E407__INCLUDED_)
#define AFX_ASTROTIME_H__0243CCB5_845A_4E6F_AB67_AFF5A176E407__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// astrotime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// astrotime window

class astrotime : public CWnd
{
// Construction
public:
	astrotime();

// Attributes
public:

// Operations
public:
	double calcJulianDay(double year, double month, double day);
	double calcJulianDayEphemeris(double julDay);
	double calcJulianDays2000(double julDay);
	double calcJulianYears2000(double julDay);
	double calcJulianCenturies2000(double julDay);
	double calcJulianMillenia2000(double julDay);
	double deltaT(double julDay);
	double calcJulianDayFromJDE(double JDE);
	void calcYearMonthDay(double JD, double &year, double &month,
						  double &day);
	CString TimeDisplayUT(double m_dYear, double m_dMonth,
									 double m_dDate, double m_dHour,
									 int precision);
	double calcDecimalYearFromJulianDay(double julDay);
	double calcDecimalYearFromYearMonthDay(double year,
										   double month,
										   double day);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(astrotime)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~astrotime();

	// Generated message map functions
protected:
	//{{AFX_MSG(astrotime)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASTROTIME_H__0243CCB5_845A_4E6F_AB67_AFF5A176E407__INCLUDED_)
