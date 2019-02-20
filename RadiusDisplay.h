//#include "PlanetsView.h"

#if !defined(AFX_RADIUSDISPLAY_H__161D1DE2_A006_4705_9775_AEFDA07D8920__INCLUDED_)
#define AFX_RADIUSDISPLAY_H__161D1DE2_A006_4705_9775_AEFDA07D8920__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadiusDisplay.h : header file
//
#include "Planets.h"
#include "MainFrm.h"
#include "PlanetsView.h"
/////////////////////////////////////////////////////////////////////////////
// CRadiusDisplay dialog

class CRadiusDisplay : public CDialog
{
// Construction
public:
	CRadiusDisplay(class CTimeLocation* dick);
//	CRadiusDisplay(CWnd* pParent=NULL);   // standard constructor
	CWnd* m_pParent;
	class CTimeLocation* m_pCTimeLocation;
// Dialog Data
	//{{AFX_DATA(CRadiusDisplay)
	enum { IDD = IDD_RADIUS_DISPLAY };
	CString	m_cRadiusDisplayTime;
	CString	m_cRadiusDisplayLambda1;
	CString	m_cRadiusDisplayBeta1;
	CString	m_cRadiusDisplayBeta2;
	CString	m_cRadiusDisplayLambda2;
	CString	m_cRadiusDisplayRadius1;
	CString	m_cRadiusDisplayRadius2;
	CString	m_cDisplayTitle;
	CString	m_cDegreeStyle;
	CString	m_cJupiterRetrograde;
	CString	m_cMarsRetrograde;
	CString	m_cMercuryRetrograde;
	CString	m_cNeptuneRetrograde;
	CString	m_cPlutoRetrograde;
	CString	m_cSaturnRetrograde;
	CString	m_cUranusRetrograde;
	CString	m_cVenusRetrograde;
	CString	m_sEarthBeta;
	CString	m_sJupiterBeta;
	CString	m_sMarsBeta;
	CString	m_sMercuryBeta;
	CString	m_sMoonBeta;
	CString	m_sNeptuneBeta;
	CString	m_sPlutoBeta;
	CString	m_sSaturnBeta;
	CString	m_sSunBeta;
	CString	m_sUranusBeta;
	CString	m_sVenusBeta;
	CString	m_sEarthLambda;
	CString	m_sJupiterLambda;
	CString	m_sMarsLambda;
	CString	m_sMercuryLambda;
	CString	m_sMoonLambda;
	CString	m_sNeptuneLambda;
	CString	m_sPlutoLambda;
	CString	m_sSaturnLambda;
	CString	m_sSunLambda;
	CString	m_sUranusLambda;
	CString	m_sVenusLambda;
	CString	m_sEarthRadius;
	CString	m_sJupiterRadius;
	CString	m_sMarsRadius;
	CString	m_sMercuryRadius;
	CString	m_sMoonRadius;
	CString	m_sNeptuneRadius;
	CString	m_sPlutoRadius;
	CString	m_sSaturnRadius;
	CString	m_sSunRadius;
	CString	m_sUranusRadius;
	CString	m_sVenusRadius;
	CString	m_sLat;
	CString	m_sLon;
	CString	m_sJupiterDur;
	CString	m_sMarsDur;
	CString	m_sMercuryDur;
	CString	m_sMoonDur;
	CString	m_sNeptuneDur;
	CString	m_sPlutoDur;
	CString	m_sSaturnDur;
	CString	m_sSunDur;
	CString	m_sUranusDur;
	CString	m_sVenusDur;
	CString	m_sPositionTitle;
	CString	m_sAbove;
	CString	m_sHorizon;
	CString	m_sMoonQuarter;
	//}}AFX_DATA
	double	m_dEarthBeta;
	double	m_dJupiterBeta;
	double	m_dMarsBeta;
	double	m_dMercuryBeta;
	double	m_dMoonBeta;
	double	m_dNeptuneBeta;
	double	m_dPlutoBeta;
	double	m_dSaturnBeta;
	double	m_dSunBeta;
	double	m_dUranusBeta;
	double	m_dVenusBeta;
	double	m_dEarthLambda;
	double	m_dJupiterLambda;
	double	m_dMarsLambda;
	double	m_dMercuryLambda;
	double	m_dMoonLambda;
	double	m_dNeptuneLambda;
	double	m_dPlutoLambda;
	double	m_dSaturnLambda;
	double	m_dSunLambda;
	double	m_dUranusLambda;
	double	m_dVenusLambda;
	double	m_dEarthRadius;
	double	m_dJupiterRadius;
	double	m_dMarsRadius;
	double	m_dMercuryRadius;
	double	m_dMoonRadius;
	double	m_dNeptuneRadius;
	double	m_dPlutoRadius;
	double	m_dSaturnRadius;
	double	m_dSunRadius;
	double	m_dUranusRadius;
	double	m_dVenusRadius;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadiusDisplay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRadiusDisplay)
	afx_msg void OnShow();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADIUSDISPLAY_H__161D1DE2_A006_4705_9775_AEFDA07D8920__INCLUDED_)
