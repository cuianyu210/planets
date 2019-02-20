#if !defined(AFX_PLANETTIME_H__7DD0902C_A31F_4FE1_9BA5_0323AB8595A4__INCLUDED_)
#define AFX_PLANETTIME_H__7DD0902C_A31F_4FE1_9BA5_0323AB8595A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlanetTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlanetTime window

class CPlanetTime : public CWnd
{
// Construction
public:
	CPlanetTime();

// Attributes
public:
	double m_dYear;//				2002			whole
	double m_dMonth;//				1 - 12			whole
	double m_dDay;//				1 - 31			whole
	double m_dHour;//				0 - 24			whole
	double m_dDeciHour;//			.0 - .99999		real
	double m_dMinute;//				0 - 59			whole
	double m_dSecond;//				0 - 59			whole
	double m_dDeciSecond;//			.0 - .99999		real
	double m_dTimeZone;//			-12 - 12		real
	double m_dJulianDay;//			0 -				real
	double m_dJulianDayEphemeris;//	0 -				real
	double m_dDate;//				0.0 - 23.9999	real
	double m_dFractionJulianDay;
	double m_dLatitude;//			-1.57 - 1.57	real (radians)
	double m_dLongitude;//			-3.14 - 3.14	real (radians)

	CString m_sYear;//				2002
	CString m_sMonth;//				1 - 12
	CString m_sMonthName;//			"January" - "December"
	CString m_sDay;//				1 - 31
	CString m_sHour;//				0 - 24
	CString m_sMinute;//			0 - 59
	CString m_sSecond;//			0 - 59
	CString m_sDeciSecond;//		.0 - .99999
	CString m_sAmPm;//				"a" or "p"
	CString m_sDst;//				"n" or "y"
	CString m_sTimeZone;//			-12 - 12
	CString m_sDate;//				0.0 - 23.9999
	CString m_sLatitude;//			0 - 90
	CString m_sLongitude;//			0 - 180

	CString m_sHourLongString;//	"00h 00m 00.0s"
	CString sDateLongString;//		"00h 00m 00.0s" am 21 July 1946
	CString sDateShortString;//		"21 July 1946

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlanetTime)
	//}}AFX_VIRTUAL

// Implementation
public:
	void convertToDoubleGMT(int precision);
	void makeGMTHour();
	void calcJulianDay();
	void calcMonthName();
	CString DateLongString();
	CString DateShortString();
	virtual ~CPlanetTime();
	void FractionOfJulianDay();
	void hourAdjust(double &dYear, double &dMonth, double &dDay, double &dHour);
	void ProcessLatLon();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlanetTime)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLANETTIME_H__7DD0902C_A31F_4FE1_9BA5_0323AB8595A4__INCLUDED_)
