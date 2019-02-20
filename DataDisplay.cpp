// DataDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "DataDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DataDisplay dialog


//CDataDisplay::CDataDisplay(CWnd* pParent /*=NULL*/)
//	: CDialog(CDataDisplay::IDD, pParent)
CDataDisplay::CDataDisplay(class CTimeLocation* dick)
{
	m_pCTimeLocation = dick;
	//{{AFX_DATA_INIT(CDataDisplay)
	m_cDataTitle = _T("");
	m_cADegreeStyle = _T("decimal degrees");
	m_dJulianDate = 0.0;
	m_cJupiterRetrograde = _T("");
	m_cMarsRetrograde = _T("");
	m_cMercuryRetrograde = _T("");
	m_cNeptuneRetrograde = _T("");
	m_cPlutoRetrograde = _T("");
	m_cSaturnRetrograde = _T("");
	m_cUranusRetrograde = _T("");
	m_cVenusRetrograde = _T("");
	m_sJupiterAltitude = _T("");
	m_sJupiterAzimuth = _T("");
	m_sMarsAltitude = _T("");
	m_sMercuryAltitude = _T("");
	m_sMoonAltitude = _T("");
	m_sNeptuneAltitude = _T("");
	m_sPlutoAltitude = _T("");
	m_sSaturnAltitude = _T("");
	m_sSunAltitude = _T("");
	m_sUranusAltitude = _T("");
	m_sVenusAltitude = _T("");
	m_sMarsAzimuth = _T("");
	m_sMercuryAzimuth = _T("");
	m_sMoonAzimuth = _T("");
	m_sNeptuneAzimuth = _T("");
	m_sPlutoAzimuth = _T("");
	m_sSaturnAzimuth = _T("");
	m_sSunAzimuth = _T("");
	m_sUranusAzimuth = _T("");
	m_sVenusAzimuth = _T("");
	m_cDataDisplayLat = _T("");
	m_cDataDisplayLon = _T("");
	m_sMoonQuarter = _T("");
	//}}AFX_DATA_INIT
}


void CDataDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataDisplay)
	DDX_Text(pDX, IDC_DATA_TITLE, m_cDataTitle);
	DDX_Text(pDX, IDC_A_DEGREE_STYLE, m_cADegreeStyle);
	DDX_Text(pDX, IDC_JULIAN_DATE, m_dJulianDate);
	DDX_Text(pDX, IDC_JUPITER_RETROGRADE, m_cJupiterRetrograde);
	DDX_Text(pDX, IDC_MARS_RETROGRADE, m_cMarsRetrograde);
	DDX_Text(pDX, IDC_MERCURY_RETROGRADE, m_cMercuryRetrograde);
	DDX_Text(pDX, IDC_NEPTUNE_RETROGRADE, m_cNeptuneRetrograde);
	DDX_Text(pDX, IDC_PLUTO_RETROGRADE, m_cPlutoRetrograde);
	DDX_Text(pDX, IDC_SATURN_RETROGRADE, m_cSaturnRetrograde);
	DDX_Text(pDX, IDC_URANUS_RETROGRADE, m_cUranusRetrograde);
	DDX_Text(pDX, IDC_VENUS_RETROGRADE, m_cVenusRetrograde);
	DDX_Text(pDX, IDC_JUPITER_ALTITUDE, m_sJupiterAltitude);
	DDX_Text(pDX, IDC_JUPITER_AZIMUTH, m_sJupiterAzimuth);
	DDX_Text(pDX, IDC_MARS_ALTITUDE, m_sMarsAltitude);
	DDX_Text(pDX, IDC_MERCURY_ALTITUDE, m_sMercuryAltitude);
	DDX_Text(pDX, IDC_MOON_ALTITUDE, m_sMoonAltitude);
	DDX_Text(pDX, IDC_NEPTUNE_ALTITUDE, m_sNeptuneAltitude);
	DDX_Text(pDX, IDC_PLUTO_ALTITUDE, m_sPlutoAltitude);
	DDX_Text(pDX, IDC_SATURN_ALTITUDE, m_sSaturnAltitude);
	DDX_Text(pDX, IDC_SUN_ALTITUDE, m_sSunAltitude);
	DDX_Text(pDX, IDC_URANUS_ALTITUDE, m_sUranusAltitude);
	DDX_Text(pDX, IDC_VENUS_ALTITUDE, m_sVenusAltitude);
	DDX_Text(pDX, IDC_MARS_AZIMUTH, m_sMarsAzimuth);
	DDX_Text(pDX, IDC_MERCURY_AZIMUTH, m_sMercuryAzimuth);
	DDX_Text(pDX, IDC_MOON_AZIMUTH, m_sMoonAzimuth);
	DDX_Text(pDX, IDC_NEPTUNE_AZIMUTH, m_sNeptuneAzimuth);
	DDX_Text(pDX, IDC_PLUTO_AZIMUTH, m_sPlutoAzimuth);
	DDX_Text(pDX, IDC_SATURN_AZIMUTH, m_sSaturnAzimuth);
	DDX_Text(pDX, IDC_SUN_AZIMUTH, m_sSunAzimuth);
	DDX_Text(pDX, IDC_URANUS_AZIMUTH, m_sUranusAzimuth);
	DDX_Text(pDX, IDC_VENUS_AZIMUTH, m_sVenusAzimuth);
	DDX_Text(pDX, IDC_DATA_DISPLAY_LAT, m_cDataDisplayLat);
	DDX_Text(pDX, IDC_DATA_DISPLAY_LON, m_cDataDisplayLon);
	DDX_Text(pDX, IDC_MOON_QUARTER, m_sMoonQuarter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataDisplay, CDialog)
	//{{AFX_MSG_MAP(CDataDisplay)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_DD_SHOW, OnShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DataDisplay message handlers

void CDataDisplay::OnClose() 
{
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T ("DataDisplay"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T("DataDisplay"), _T ("left"), winRect.left);
	
	CDialog::OnClose();
}

void CDataDisplay::OnDestroy() 
{
	CDialog::OnDestroy();
	
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T ("DataDisplay"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("DataDisplay"), _T ("left"), winRect.left);
	
}

void CDataDisplay::OnShow() 
{
	class CPlanetsView* pCView;
	class CMainFrame* pCMainFrame;
	class CChildFrame* pChildFrame;

	UpdateData(true);
	pCMainFrame = (CMainFrame*)GetOwner();
	pChildFrame = (CChildFrame*)pCMainFrame->MDIGetActive();
	pCView = (CPlanetsView*)pChildFrame->GetActiveView();

//   No longer used
//	pCView->DrawAzAltPlanets(this, m_pCTimeLocation);

}

void CDataDisplay::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}
