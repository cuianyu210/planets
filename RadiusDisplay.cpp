// RadiusDisplay.cpp : implementation file
//
#include "stdafx.h"
#include "RadiusDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadiusDisplay dialog


//CRadiusDisplay::CRadiusDisplay(CPlanetsDoc* bob)
//	: CDialog(CRadiusDisplay::IDD, pParent)
CRadiusDisplay::CRadiusDisplay(CTimeLocation* dick)
//CRadiusDisplay::CRadiusDisplay(CWnd* pParent /*=NULL*/)
//	: CDialog(CRadiusDisplay::IDD, pParent)
{
	m_pCTimeLocation = dick;
	//{{AFX_DATA_INIT(CRadiusDisplay)
	m_cRadiusDisplayTime = _T("");
	m_cRadiusDisplayLambda1 = _T("");
	m_cRadiusDisplayBeta1 = _T("");
	m_cRadiusDisplayBeta2 = _T("");
	m_cRadiusDisplayLambda2 = _T("");
	m_cRadiusDisplayRadius1 = _T("");
	m_cRadiusDisplayRadius2 = _T("");
	m_cDisplayTitle = _T("");
	m_cDegreeStyle = _T("decimal degrees");
	m_cJupiterRetrograde = _T("");
	m_cMarsRetrograde = _T("");
	m_cMercuryRetrograde = _T("");
	m_cNeptuneRetrograde = _T("");
	m_cPlutoRetrograde = _T("");
	m_cSaturnRetrograde = _T("");
	m_cUranusRetrograde = _T("");
	m_cVenusRetrograde = _T("");
	m_sEarthBeta = _T("");
	m_sJupiterBeta = _T("");
	m_sMarsBeta = _T("");
	m_sMercuryBeta = _T("");
	m_sMoonBeta = _T("");
	m_sNeptuneBeta = _T("");
	m_sPlutoBeta = _T("");
	m_sSaturnBeta = _T("");
	m_sSunBeta = _T("");
	m_sUranusBeta = _T("");
	m_sVenusBeta = _T("");
	m_sEarthLambda = _T("");
	m_sJupiterLambda = _T("");
	m_sMarsLambda = _T("");
	m_sMercuryLambda = _T("");
	m_sMoonLambda = _T("");
	m_sNeptuneLambda = _T("");
	m_sPlutoLambda = _T("");
	m_sSaturnLambda = _T("");
	m_sSunLambda = _T("");
	m_sUranusLambda = _T("");
	m_sVenusLambda = _T("");
	m_sEarthRadius = _T("");
	m_sJupiterRadius = _T("");
	m_sMarsRadius = _T("");
	m_sMercuryRadius = _T("");
	m_sMoonRadius = _T("");
	m_sNeptuneRadius = _T("");
	m_sPlutoRadius = _T("");
	m_sSaturnRadius = _T("");
	m_sSunRadius = _T("");
	m_sUranusRadius = _T("");
	m_sVenusRadius = _T("");
	m_sLat = _T("");
	m_sLon = _T("");
	m_sJupiterDur = _T("");
	m_sMarsDur = _T("");
	m_sMercuryDur = _T("");
	m_sMoonDur = _T("");
	m_sNeptuneDur = _T("");
	m_sPlutoDur = _T("");
	m_sSaturnDur = _T("");
	m_sSunDur = _T("");
	m_sUranusDur = _T("");
	m_sVenusDur = _T("");
	m_sPositionTitle = _T("");
	m_sAbove = _T("");
	m_sHorizon = _T("");
	m_sMoonQuarter = _T("");
	//}}AFX_DATA_INIT
}


void CRadiusDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadiusDisplay)
	DDX_Text(pDX, IDC_RADIUS_DISPLAY_TIME, m_cRadiusDisplayTime);
	DDX_Text(pDX, IDC_RADIUS_DISPLAY_LAMBDA1, m_cRadiusDisplayLambda1);
	DDX_Text(pDX, IDC_RADIUS_DISPLAY_BETA1, m_cRadiusDisplayBeta1);
	DDX_Text(pDX, IDC_RADIUS_DISPLAY_BETA2, m_cRadiusDisplayBeta2);
	DDX_Text(pDX, IDC_RADIUS_DISPLAY_LAMBDA2, m_cRadiusDisplayLambda2);
	DDX_Text(pDX, IDC_RADIUS_DISPLAY_RADIUS1, m_cRadiusDisplayRadius1);
	DDX_Text(pDX, IDC_RADIUS_DISPLAY_RADIUS2, m_cRadiusDisplayRadius2);
	DDX_Text(pDX, IDC_DISPLAY_TITLE, m_cDisplayTitle);
	DDX_Text(pDX, IDC_DEGREE_STYLE, m_cDegreeStyle);
	DDX_Text(pDX, IDC_JUPITER_RETROGRADE, m_cJupiterRetrograde);
	DDX_Text(pDX, IDC_MARS_RETROGRADE, m_cMarsRetrograde);
	DDX_Text(pDX, IDC_MERCURY_RETROGRADE, m_cMercuryRetrograde);
	DDX_Text(pDX, IDC_NEPTUNE_RETROGRADE, m_cNeptuneRetrograde);
	DDX_Text(pDX, IDC_PLUTO_RETROGRADE, m_cPlutoRetrograde);
	DDX_Text(pDX, IDC_SATURN_RETROGRADE, m_cSaturnRetrograde);
	DDX_Text(pDX, IDC_URANUS_RETROGRADE, m_cUranusRetrograde);
	DDX_Text(pDX, IDC_VENUS_RETROGRADE, m_cVenusRetrograde);
	DDX_Text(pDX, IDC_EARTH_BETA, m_sEarthBeta);
	DDX_Text(pDX, IDC_JUPITER_BETA, m_sJupiterBeta);
	DDX_Text(pDX, IDC_MARS_BETA, m_sMarsBeta);
	DDX_Text(pDX, IDC_MERCURY_BETA, m_sMercuryBeta);
	DDX_Text(pDX, IDC_MOON_BETA, m_sMoonBeta);
	DDX_Text(pDX, IDC_NEPTUNE_BETA, m_sNeptuneBeta);
	DDX_Text(pDX, IDC_PLUTO_BETA, m_sPlutoBeta);
	DDX_Text(pDX, IDC_SATURN_BETA, m_sSaturnBeta);
	DDX_Text(pDX, IDC_SUN_BETA, m_sSunBeta);
	DDX_Text(pDX, IDC_URANUS_BETA, m_sUranusBeta);
	DDX_Text(pDX, IDC_VENUS_BETA, m_sVenusBeta);
	DDX_Text(pDX, IDC_EARTH_LAMBDA, m_sEarthLambda);
	DDX_Text(pDX, IDC_JUPITER_LAMBDA, m_sJupiterLambda);
	DDX_Text(pDX, IDC_MARS_LAMBDA, m_sMarsLambda);
	DDX_Text(pDX, IDC_MERCURY_LAMBDA, m_sMercuryLambda);
	DDX_Text(pDX, IDC_MOON_LAMBDA, m_sMoonLambda);
	DDX_Text(pDX, IDC_NEPTUNE_LAMBDA, m_sNeptuneLambda);
	DDX_Text(pDX, IDC_PLUTO_LAMBDA, m_sPlutoLambda);
	DDX_Text(pDX, IDC_SATURN_LAMBDA, m_sSaturnLambda);
	DDX_Text(pDX, IDC_SUN_LAMBDA, m_sSunLambda);
	DDX_Text(pDX, IDC_URANUS_LAMBDA, m_sUranusLambda);
	DDX_Text(pDX, IDC_VENUS_LAMBDA, m_sVenusLambda);
	DDX_Text(pDX, IDC_EARTH_RADIUS, m_sEarthRadius);
	DDX_Text(pDX, IDC_JUPITER_RADIUS, m_sJupiterRadius);
	DDX_Text(pDX, IDC_MARS_RADIUS, m_sMarsRadius);
	DDX_Text(pDX, IDC_MERCURY_RADIUS, m_sMercuryRadius);
	DDX_Text(pDX, IDC_MOON_RADIUS, m_sMoonRadius);
	DDX_Text(pDX, IDC_NEPTUNE_RADIUS, m_sNeptuneRadius);
	DDX_Text(pDX, IDC_PLUTO_RADIUS, m_sPlutoRadius);
	DDX_Text(pDX, IDC_SATURN_RADIUS, m_sSaturnRadius);
	DDX_Text(pDX, IDC_SUN_RADIUS, m_sSunRadius);
	DDX_Text(pDX, IDC_URANUS_RADIUS, m_sUranusRadius);
	DDX_Text(pDX, IDC_VENUS_RADIUS, m_sVenusRadius);
	DDX_Text(pDX, IDC_LAT, m_sLat);
	DDX_Text(pDX, IDC_LON, m_sLon);
	DDX_Text(pDX, IDC_JUPITER_DUR, m_sJupiterDur);
	DDX_Text(pDX, IDC_MARS_DUR, m_sMarsDur);
	DDX_Text(pDX, IDC_MERCURY_DUR, m_sMercuryDur);
	DDX_Text(pDX, IDC_MOON_DUR, m_sMoonDur);
	DDX_Text(pDX, IDC_NEPTUNE_DUR, m_sNeptuneDur);
	DDX_Text(pDX, IDC_PLUTO_DUR, m_sPlutoDur);
	DDX_Text(pDX, IDC_SATURN_DUR, m_sSaturnDur);
	DDX_Text(pDX, IDC_SUN_DUR, m_sSunDur);
	DDX_Text(pDX, IDC_URANUS_DUR, m_sUranusDur);
	DDX_Text(pDX, IDC_VENUS_DUR, m_sVenusDur);
	DDX_Text(pDX, IDC_POSITION_TITLE, m_sPositionTitle);
	DDX_Text(pDX, IDC_RADIUS_DISPLAY_ABOVE, m_sAbove);
	DDX_Text(pDX, IDC_RADIUS_DISPLAY_HORIZON, m_sHorizon);
	DDX_Text(pDX, IDC_MOON_QUART, m_sMoonQuarter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadiusDisplay, CDialog)
	//{{AFX_MSG_MAP(CRadiusDisplay)
	ON_BN_CLICKED(IDC_SHOW, OnShow)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadiusDisplay message handlers

void CRadiusDisplay::OnShow() 
{
	class CPlanetsView* pCView;
	class CMainFrame* pCMainFrame;
	class CChildFrame* pChildFrame;

	UpdateData(true);

//	Only show if it is spherical data
	if(		m_pCTimeLocation->m_sCalcType == "Cartesian" 
		||	m_pCTimeLocation->m_sCalcType == "Data" )
	{
	}
	else
	{
		pCMainFrame = (CMainFrame*)GetOwner();
		pChildFrame = (CChildFrame*)pCMainFrame->MDIGetActive();
		pCView = (CPlanetsView*)pChildFrame->GetActiveView();

//   No longer used  //
		//		pCView->DrawPlanets(this, m_pCTimeLocation);
	}
}

void CRadiusDisplay::OnClose() 
{
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T ("RadiusDisplay"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("RadiusDisplay"), _T ("left"), winRect.left);
	
	CDialog::OnClose();
}

void CRadiusDisplay::OnDestroy() 
{
	CDialog::OnDestroy();
	
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T ("RadiusDisplay"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("RadiusDisplay"), _T ("left"), winRect.left);
}

void CRadiusDisplay::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}
