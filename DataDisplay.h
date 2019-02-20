#if !defined(AFX_CDATADISPLAY_H__81322E7B_23D4_4F64_B83E_D43C6B701A95__INCLUDED_)
#define AFX_CDATADISPLAY_H__81322E7B_23D4_4F64_B83E_D43C6B701A95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataDisplay.h : header file
//
#include "MainFrm.h"
#include "PlanetsView.h"

/////////////////////////////////////////////////////////////////////////////
// DataDisplay dialog

class CDataDisplay : public CDialog
{
// Construction
public:
//	CDataDisplay(CWnd* pParent = NULL);   // standard constructor
	CDataDisplay(class CTimeLocation* dick);
	class CTimeLocation* m_pCTimeLocation;

	// Dialog Data
	//{{AFX_DATA(CDataDisplay)
	enum { IDD = IDD_DATA_DISPLAY };
	CString	m_cDataTitle;
	CString	m_cADegreeStyle;
	double	m_dJulianDate;
	CString	m_cJupiterRetrograde;
	CString	m_cMarsRetrograde;
	CString	m_cMercuryRetrograde;
	CString	m_cNeptuneRetrograde;
	CString	m_cPlutoRetrograde;
	CString	m_cSaturnRetrograde;
	CString	m_cUranusRetrograde;
	CString	m_cVenusRetrograde;
	CString	m_sJupiterAltitude;
	CString	m_sJupiterAzimuth;
	CString	m_sMarsAltitude;
	CString	m_sMercuryAltitude;
	CString	m_sMoonAltitude;
	CString	m_sNeptuneAltitude;
	CString	m_sPlutoAltitude;
	CString	m_sSaturnAltitude;
	CString	m_sSunAltitude;
	CString	m_sUranusAltitude;
	CString	m_sVenusAltitude;
	CString	m_sMarsAzimuth;
	CString	m_sMercuryAzimuth;
	CString	m_sMoonAzimuth;
	CString	m_sNeptuneAzimuth;
	CString	m_sPlutoAzimuth;
	CString	m_sSaturnAzimuth;
	CString	m_sSunAzimuth;
	CString	m_sUranusAzimuth;
	CString	m_sVenusAzimuth;
	CString	m_cDataDisplayLat;
	CString	m_cDataDisplayLon;
	CString	m_sMoonQuarter;
	//}}AFX_DATA
	double	m_dSunAzimuth;
	double	m_dSunAltitude;
	double	m_dMoonAzimuth;
	double	m_dMoonAltitude;
	double	m_dMercuryAzimuth;
	double	m_dMercuryAltitude;
	double	m_dVenusAzimuth;
	double	m_dVenusAltitude;
	double	m_dMarsAzimuth;
	double	m_dMarsAltitude;
	double	m_dJupiterAzimuth;
	double	m_dJupiterAltitude;
	double	m_dSaturnAzimuth;
	double	m_dSaturnAltitude;
	double	m_dUranusAzimuth;
	double	m_dUranusAltitude;
	double	m_dNeptuneAzimuth;
	double	m_dNeptuneAltitude;
	double	m_dPlutoAzimuth;
	double	m_dPlutoAltitude;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataDisplay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataDisplay)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDATADISPLAY_H__81322E7B_23D4_4F64_B83E_D43C6B701A95__INCLUDED_)
