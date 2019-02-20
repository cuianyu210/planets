#if !defined(AFX_ALMANAC_H__5125CE17_070F_4334_BD28_3E7307288A3C__INCLUDED_)
#define AFX_ALMANAC_H__5125CE17_070F_4334_BD28_3E7307288A3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Almanac.h : header file
//
#include "PlanetTime.h"
#include "Planet.h"

/////////////////////////////////////////////////////////////////////////////
// CAlmanac dialog

class CAlmanac : public CDialog
{
// Construction
public:
	CAlmanac(CWnd* pParent = NULL);   // standard constructor
	CAlmanac(class CPlanetsDoc* bob);
	afx_msg void OnDoAll();
	afx_msg void OnAlmanac();

// Dialog Data
	//{{AFX_DATA(CAlmanac)
	enum { IDD = IDD_ALMANAC };
	int		m_iNoRuns;
	CString	m_sProgress;
	int		m_iPrecision;
	int		m_iDayIn;
	int		m_iDayInc;
	int		m_iDayOut;
	int		m_iHourIn;
	int		m_iHourInc;
	int		m_iHourOut;
	int		m_iMinuteInc;
	int		m_iMonthIn;
	int		m_iMonthInc;
	int		m_iMonthOut;
	int		m_iSecondInc;
	int		m_iYearIn;
	int		m_iYearInc;
	int		m_iYearOut;
	CString	m_cLatEndNS;
	CString	m_cLatStartNS;
	CString	m_cLonEndEW;
	CString	m_cLonStartEW;
	double	m_dTimeZone;
	int		m_iLatRuns;
	int		m_iLonRuns;
	int		m_iWhichCalc;
	CString	m_sLatEnd;
	CString	m_sLatInc;
	CString	m_sLatStart;
	CString	m_sLonEnd;
	CString	m_sLonInc;
	CString	m_sLonStart;
	//}}AFX_DATA

	double m_dAries;
	double m_dVenusGHA;
	double m_dVenusDec;
	double m_dMarsGHA;
	double m_dMarsDec;
	double m_dJupiterGHA;
	double m_dJupiterDec;
	double m_dSaturnGHA;
	double m_dSaturnDec;
	double m_dSunGHA;
	double m_dSunDec;
	double m_dMoonGHA;
	double m_dMoonDec;
	double m_dAlpha;
	double m_dDelta;
	double m_dLatEnd;
	double m_dLatInc;
	double m_dLatStart;
	double m_dLonEnd;
	double m_dLonInc;
	double m_dLonStart;

	CString m_sAlpha;
	CString m_sDelta;
	CString m_sAries;
	double *m_dDisplayValues[7][3];
	CString *m_sValues[7][3];
	double m_pValues[7][3];
	CString m_sAngSepType;
	void  MakeString(double value, CString &retString,
					 UINT type, int iPrecision);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlmanac)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	class CPlanetTime m_sTimeIn;
	class CPlanetTime m_sTimeInc;
	class CPlanetTime m_sTimeOut;
	void  UpdateDataTL();
	void  ProcessData();
	void  CalculateValues();
	void  WhichPlanets(CAlmanac* pAlBox, int pValueSet[12]);
	void  PrintTitles(int method);
	void  WriteProfiles();
	int	  ConvertValue(int value);
	int	  m_iValueSet[12];
	CString RiseSetOutputString(double value, UINT cOutputStyle);
//////////////////////////////////////////////////////////
	int m_iCalc;//	Calculation method as below			//
//			0 = "Azimuth Altitude";						//
//			1 = "Equatorial Apparent";					//
//			2 = "Ecliptic Apparent Spherical";			//
//			3 = "Ecliptic True Spherical";				//
//			4 = "Ecliptic True Cartesian";				//
//			5 = "Heliocentric Spherical";				//
//			6 = "Heliocentric Cartesian";				//
//			7 = "Rise, Set, Transit";					//
//			8 = "GHA and Dec";							//
//			9 = "Angular Separation";					//
//////////////////////////////////////////////////////////
	CString m_sFileName;//	Save file name
	CDialog* m_pCDialog;
	CButton* m_pDoAll;
	CButton* m_pDoAlmanac;
	CButton* m_pAriesCheckBox;
	CButton* m_pVenusCheckBox;
	CButton* m_pMarsCheckBox;
	CButton* m_pJupiterCheckBox;
	CButton* m_pSaturnCheckBox;
	CButton* m_pSunCheckBox;
	CButton* m_pMoonCheckBox;
	CButton* m_pMercuryCheckBox;
	CButton* m_pEarthCheckBox;
	CButton* m_pUranusCheckBox;
	CButton* m_pNeptuneCheckBox;
	CButton* m_pPlutoCheckBox;
	CListBox* m_pWhichCalc;
	UINT m_cOutputStyle;

	// Generated message map functions
	//{{AFX_MSG(CAlmanac)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnAlmOutput();
	afx_msg void OnSelchangeAlmanacList();
	afx_msg void OnAngSepGroup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALMANAC_H__5125CE17_070F_4334_BD28_3E7307288A3C__INCLUDED_)
