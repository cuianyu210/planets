#if !defined(AFX_ASTRONOMICALDATA_H__881A5DB3_9B8F_4CE0_8DA1_7A48959E9701__INCLUDED_)
#define AFX_ASTRONOMICALDATA_H__881A5DB3_9B8F_4CE0_8DA1_7A48959E9701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AstronomicalData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAstronomicalData dialog

class CAstronomicalData : public CDialog
{
// Construction
public:
	CAstronomicalData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAstronomicalData)
	enum { IDD = IDD_ASTRONOMICAL_DATA };
	double	m_dAppSiderealDeg;
	double	m_dDeltaT;
	double	m_dEccentricity;
	double	m_dJulianDayEphemeris;
	double	m_dJulianDay2;
	CString	m_cLocalTime;
	double	m_dLongitudePerihelion;
	double	m_dMeanAnomaly;
	double	m_dMeanObliquityEcliptic;
	double	m_dMeanSiderealDeg;
	double	m_dTrueObliquityEcliptic;
	CString	m_cUT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstronomicalData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAstronomicalData)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASTRONOMICALDATA_H__881A5DB3_9B8F_4CE0_8DA1_7A48959E9701__INCLUDED_)
