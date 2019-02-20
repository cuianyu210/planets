#if !defined(AFX_TIMELOCATION_H__F01C8271_72EB_4923_92F8_5A45E4035A00__INCLUDED_)
#define AFX_TIMELOCATION_H__F01C8271_72EB_4923_92F8_5A45E4035A00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeLocation.h : header file
//
#include "PlanetTime.h"
#include "RadiusDisplay.h"
#include "AstronomicalData.h"
#include "Hor.h"


/////////////////////////////////////////////////////////////////////////////
// CTimeLocation dialog
class CTimeLocation : public CDialog
{
// Construction
public:
//	CTimeLocation(CWnd* pParent = NULL);   // standard constructor
	CTimeLocation(class CPlanetsDoc* bob);   // standard constructor
	CPlanetsDoc* m_pPlanetDoc;

// Dialog Data
	//{{AFX_DATA(CTimeLocation)
	enum { IDD = IDD_TIME_LOCATION };
	CString	m_cAmpm;
	CString	m_cDst;
	CString	m_cLatitude_NS;
	CString	m_cLongitude_WE;
	int		m_iPrecision;
	int		m_iDate;
	double	m_dHour;
	double	m_dTimeZone;
	int		m_iYear;
	CString	m_sMonth;
	CString	m_sLocation;
	CString	m_sLatitude;
	CString	m_sLongitude;
	//}}AFX_DATA
	UINT m_cOutputStyle;
	int m_iMonth;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeLocation)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateDataTL();
	void ProcessData();

	afx_msg void OnDoAll();
	afx_msg void OnNow();
	afx_msg void OnSelchangeLocation();

	void WhichPlanets(CTimeLocation* pTLBox, int pPlanetSet[11]);
	void getBody(class CPlanet &body, int p);
	int CountPlanets();
	void WhichConstellations(CArray<int, int> *iArray);

	int m_pPlanetSet[11];
	double m_pValues[11][4];//	General holder for all values

	CString m_sCalcMethod;
	CString m_sCalcType;

	int m_iRectTop;
	int m_iRectLeft;

	class CPlanetTime m_sTimeEntered;

	CString	m_cLatitude;
	CString	m_cLongitude;

private:
	CString m_sDurValues[11];//	General holder for all duration values
	double *m_pDataDisplayValues[11][2];
	double *m_pRadiusDisplayValues[11][3];
	CString *m_pModelessValues[11][4];
	int *m_pModelessHorInts[11];
	int m_iSpecialFlag[11];

	CString m_cMercRetro, m_cVenRetro, m_cMarRetro, m_cJupRetro, m_cSatRetro;
	CString m_cUranRetro, m_cNepRetro, m_cPlutRetro;
	CString m_cMagneticVariation;
	CString m_cMagneticDip;
	CString m_cMagneticHorizonatal;
	CString m_cMagneticNorth;
	CString m_cMagneticEast;
	CString m_cMagneticVertical;
	CString m_cMagneticTotal;
	double m_dMagneticVariation;
	double m_dMagneticDip;
	double m_dMagneticHorizontal;
	double m_dMagneticNorth;
	double m_dMagneticEast;
	double m_dMagneticVertical;
	double m_dMagneticTotal;

protected:

	CWnd* m_pParent;
	class CDataDisplay* m_pModeless;
	class CRadiusDisplay* m_pModelessRadius;
	class CRiseTransitSet* m_pModelessRTS;
	CAstronomicalData* m_pModelessAstro;
	class CAngularSeparation* m_pModelessAngSep;
	class CHor* m_pModelessHor;
	class CVariationBox* m_pModelessVar;
	CString m_sDummy1, m_sDummy2;
	CString m_sDisTypeDMS;
	CString m_sDisTypeHMS;

	CString DataDisplayLatLon(CString type, CString value, CString nswe);
	void assignModelessArray();
	void assignModelessRadiusArray();
	void assignModelessRadiusValues();
	void assignModelessRTSArray();
	void assignModelessRTSValues();
	void AssignModelessHorArray();
	void zeroAllValues();
	void calcAzimuthAltitude();
	void assignAzAltValues();
	void calcHeliocentricSpherical();
	void assignHelioSphericalValues();
	void calcEquatorialApparent();
	void assignEquatorialApparentValues();
	void calcGeocentricCartesian();
	void assignGeocentricCartesianValues();
	void calcGeocentricSpherical();
	void assignGeocentricSphericalValues();
	void calcGeocentricSphericalTrue();
	void assignGeocentricSphericalTrueValues();
	void calcHeliolcentricCartesian();
	void assignHelioCartesianValues();
	void calcRiseSetTransit();
	void assignRiseSetTransitValues();
	int calcMagneticVariation();
	void assignMagneticVariationValues();
	void calcHeliocentricSphericalRetrograde();
	void calcGHADec();
	void assignGHADecValues(double julDay);
	void KeepValues();
	void WriteValues();
	void calcHor(class CChart *pChart);
	void assignHorValues(class CChart *pChart);
	void LoadRetroArray();
	CString CalculateMoonsQuarter();
	
	CDialog* m_pCDialog;
	CButton* m_pDoAll;
	CButton* m_pNow;
	CButton* m_pSunCheckBox;
	CButton* m_pMoonCheckBox;
	CButton* m_pMercuryCheckBox;
	CButton* m_pVenusCheckBox;
	CButton* m_pEarthCheckBox;
	CButton* m_pMarsCheckBox;
	CButton* m_pJupiterCheckBox;
	CButton* m_pSaturnCheckBox;
	CButton* m_pUranusCheckBox;
	CButton* m_pNeptuneCheckBox;
	CButton* m_pPlutoCheckBox;
	CButton* m_pStarsCheckBox;
	CButton* m_pKeepValues;

	// Generated message map functions
	//{{AFX_MSG(CTimeLocation)
	afx_msg void OnAzimuthAltitude();
	afx_msg void OnHeliocentricSpherical();
	afx_msg void OnEquatorialApparent();
	afx_msg void OnGeocentricCartesian();
	afx_msg void OnGeocentricSphericalApp();
	afx_msg void OnGeocentricSphericalTrue();
	afx_msg void OnHeliocentricCartesian();
	afx_msg void OnRiseSetTransit();
	afx_msg void OnAstronomicalData();
	afx_msg void OnButtonDst();
	afx_msg void OnButtonAmpm();
	afx_msg void OnButtonNs();
	afx_msg void OnButtonWe();
	afx_msg void OnOutputGroup();
	afx_msg void OnGhaDec();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnAngularSeparation();
	afx_msg void OnHor();
	afx_msg void OnDeltaposSpinMonth(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusMonth();
	afx_msg void OnKillfocusLatitude();
	afx_msg void OnKillfocusLongitude();
	afx_msg void OnKillfocusAmpm();
	afx_msg void OnKillfocusDate();
	afx_msg void OnKillfocusDaylightSt();
	afx_msg void OnKillfocusHour();
	afx_msg void OnKillfocusLatitudeNs();
	afx_msg void OnKillfocusLongitudeWe();
	afx_msg void OnKillfocusTimeZone();
	afx_msg void OnKillfocusYear();
	afx_msg void OnChangeMonth();
	afx_msg void OnAddPlace();
	afx_msg void OnPlaceDelete();
	afx_msg void OnStars();
	afx_msg void OnMagneticVariation();
	afx_msg void OnMoonPhaseBtn();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnCbnEditchangeLocation1();
//	afx_msg void OnCbnSetfocusLocation1();
//	afx_msg void OnCbnSelchangeLocation1();
//	afx_msg void OnCbnSetfocusLocation();
//	afx_msg void OnCbnEditchangeLocation();
//	afx_msg void OnCbnSetfocusLocation();
	afx_msg void OnBnClickedStarsPrint();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMELOCATION_H__F01C8271_72EB_4923_92F8_5A45E4035A00__INCLUDED_)
