#if !defined(AFX_RISETRANSITSET_H__84336234_49A4_4A2B_A8E9_3C0EC1F7B365__INCLUDED_)
#define AFX_RISETRANSITSET_H__84336234_49A4_4A2B_A8E9_3C0EC1F7B365__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RiseTransitSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRiseTransitSet dialog

class CRiseTransitSet : public CDialog
{
// Construction
public:
//	CRiseTransitSet(CWnd* pParent = NULL);   // standard constructor
	CRiseTransitSet(class CTimeLocation* dick);
	class CTimeLocation* m_pCTimeLocation;

// Dialog Data
	//{{AFX_DATA(CRiseTransitSet)
	enum { IDD = IDD_RISE_TRANSIT_SET };
	CString	m_cJupiter2;
	CString	m_cJupiterRise;
	CString	m_cJupiterSet;
	CString	m_cJupiterTransit;
	CString	m_cJupiterUp;
	CString	m_cMars2;
	CString	m_cMarsRise;
	CString	m_cMarsSet;
	CString	m_cMarsTransit;
	CString	m_cMarsUp;
	CString	m_cMercury2;
	CString	m_cMercuryRise;
	CString	m_cMercurySet;
	CString	m_cMercuryTransit;
	CString	m_cMercuryUp;
	CString	m_cMoon2;
	CString	m_cMoonRise;
	CString	m_cMoonSet;
	CString	m_cMoonTransit;
	CString	m_cMoonUp;
	CString	m_cNeptune2;
	CString	m_cNeptuneRise;
	CString	m_cNeptuneSet;
	CString	m_cNeptuneTransit;
	CString	m_cNeptuneUp;
	CString	m_cPluto2;
	CString	m_cPlutoRise;
	CString	m_cPlutoSet;
	CString	m_cPlutoTransit;
	CString	m_cPlutoUp;
	CString	m_cDate;
	CString	m_cLat;
	CString	m_cLon;
	CString	m_cSaturn2;
	CString	m_cSaturnRise;
	CString	m_cSaturnSet;
	CString	m_cSaturnTransit;
	CString	m_cSaturnUp;
	CString	m_cSun2;
	CString	m_cSunRise;
	CString	m_cSunSet;
	CString	m_cSunTransit;
	CString	m_cSunUp;
	CString	m_cUranus2;
	CString	m_cUranusRise;
	CString	m_cUranusSet;
	CString	m_cUranusTransit;
	CString	m_cUranusUp;
	CString	m_cVenus2;
	CString	m_cVenusRise;
	CString	m_cVenusSet;
	CString	m_cVenusTransit;
	CString	m_cVenusUp;
	CString	m_cTimeStyle;
	//}}AFX_DATA

	CString	m_cEarth2;
	CString	m_cEarthRise;
	CString	m_cEarthSet;
	CString	m_cEarthTransit;
	CString	m_cEarthUp;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRiseTransitSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRiseTransitSet)
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RISETRANSITSET_H__84336234_49A4_4A2B_A8E9_3C0EC1F7B365__INCLUDED_)
