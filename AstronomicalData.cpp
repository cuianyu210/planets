// AstronomicalData.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AstronomicalData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstronomicalData dialog


CAstronomicalData::CAstronomicalData(CWnd* pParent /*=NULL*/)
	: CDialog(CAstronomicalData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAstronomicalData)
	m_dAppSiderealDeg = 0.0;
	m_dDeltaT = 0.0;
	m_dEccentricity = 0.0;
	m_dJulianDayEphemeris = 0.0;
	m_dJulianDay2 = 0.0;
	m_cLocalTime = _T("");
	m_dLongitudePerihelion = 0.0;
	m_dMeanAnomaly = 0.0;
	m_dMeanObliquityEcliptic = 0.0;
	m_dMeanSiderealDeg = 0.0;
	m_dTrueObliquityEcliptic = 0.0;
	m_cUT = _T("");
	//}}AFX_DATA_INIT
}


void CAstronomicalData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAstronomicalData)
	DDX_Text(pDX, IDC_APP_SIDEREAL_DEG, m_dAppSiderealDeg);
	DDX_Text(pDX, IDC_DELTA_T, m_dDeltaT);
	DDX_Text(pDX, IDC_ECCENTRICITY, m_dEccentricity);
	DDX_Text(pDX, IDC_JULIAN_DAY_EPHEMERIS, m_dJulianDayEphemeris);
	DDX_Text(pDX, IDC_JULIAN_DAY2, m_dJulianDay2);
	DDX_Text(pDX, IDC_LOCAL_TIME, m_cLocalTime);
	DDX_Text(pDX, IDC_LONGITUDE_PERIHELION, m_dLongitudePerihelion);
	DDX_Text(pDX, IDC_MEAN_ANOMALY, m_dMeanAnomaly);
	DDX_Text(pDX, IDC_MEAN_OBLIQUITY_ECLIPTIC, m_dMeanObliquityEcliptic);
	DDX_Text(pDX, IDC_MEAN_SIDEREAL_DEG, m_dMeanSiderealDeg);
	DDX_Text(pDX, IDC_TRUE_OBLIQUITY_ECLIPTIC, m_dTrueObliquityEcliptic);
	DDX_Text(pDX, IDC_UT, m_cUT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAstronomicalData, CDialog)
	//{{AFX_MSG_MAP(CAstronomicalData)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstronomicalData message handlers

void CAstronomicalData::OnClose() 
{
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T ("AstronomicalData"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("AstronomicalData"), _T ("left"), winRect.left);
	
	CDialog::OnClose();
}

void CAstronomicalData::OnDestroy() 
{
	CDialog::OnDestroy();
	
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T ("AstronomicalData"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("AstronomicalData"), _T ("left"), winRect.left);
	
}

void CAstronomicalData::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}
