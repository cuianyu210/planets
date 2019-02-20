// RiseTransitSet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "RiseTransitSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRiseTransitSet dialog


//CRiseTransitSet::CRiseTransitSet(CWnd* pParent /*=NULL*/)
//	: CDialog(CRiseTransitSet::IDD, pParent)
CRiseTransitSet::CRiseTransitSet(class CTimeLocation* dick)
{
	m_pCTimeLocation = dick;
	//{{AFX_DATA_INIT(CRiseTransitSet)
	m_cJupiter2 = _T("");
	m_cJupiterRise = _T("");
	m_cJupiterSet = _T("");
	m_cJupiterTransit = _T("");
	m_cJupiterUp = _T("");
	m_cMars2 = _T("");
	m_cMarsRise = _T("");
	m_cMarsSet = _T("");
	m_cMarsTransit = _T("");
	m_cMarsUp = _T("");
	m_cMercury2 = _T("");
	m_cMercuryRise = _T("");
	m_cMercurySet = _T("");
	m_cMercuryTransit = _T("");
	m_cMercuryUp = _T("");
	m_cMoon2 = _T("");
	m_cMoonRise = _T("");
	m_cMoonSet = _T("");
	m_cMoonTransit = _T("");
	m_cMoonUp = _T("");
	m_cNeptune2 = _T("");
	m_cNeptuneRise = _T("");
	m_cNeptuneSet = _T("");
	m_cNeptuneTransit = _T("");
	m_cNeptuneUp = _T("");
	m_cPluto2 = _T("");
	m_cPlutoRise = _T("");
	m_cPlutoSet = _T("");
	m_cPlutoTransit = _T("");
	m_cPlutoUp = _T("");
	m_cDate = _T("");
	m_cLat = _T("");
	m_cLon = _T("");
	m_cSaturn2 = _T("");
	m_cSaturnRise = _T("");
	m_cSaturnSet = _T("");
	m_cSaturnTransit = _T("");
	m_cSaturnUp = _T("");
	m_cSun2 = _T("");
	m_cSunRise = _T("");
	m_cSunSet = _T("");
	m_cSunTransit = _T("");
	m_cSunUp = _T("");
	m_cUranus2 = _T("");
	m_cUranusRise = _T("");
	m_cUranusSet = _T("");
	m_cUranusTransit = _T("");
	m_cUranusUp = _T("");
	m_cVenus2 = _T("");
	m_cVenusRise = _T("");
	m_cVenusSet = _T("");
	m_cVenusTransit = _T("");
	m_cVenusUp = _T("");
	m_cTimeStyle = _T("");
	//}}AFX_DATA_INIT
}


void CRiseTransitSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRiseTransitSet)
	DDX_Text(pDX, IDC_JUPITER_2, m_cJupiter2);
	DDX_Text(pDX, IDC_JUPITER_RISE, m_cJupiterRise);
	DDX_Text(pDX, IDC_JUPITER_SET, m_cJupiterSet);
	DDX_Text(pDX, IDC_JUPITER_TRANSIT, m_cJupiterTransit);
	DDX_Text(pDX, IDC_JUPITER_UP, m_cJupiterUp);
	DDX_Text(pDX, IDC_MARS_2, m_cMars2);
	DDX_Text(pDX, IDC_MARS_RISE, m_cMarsRise);
	DDX_Text(pDX, IDC_MARS_SET, m_cMarsSet);
	DDX_Text(pDX, IDC_MARS_TRANSIT, m_cMarsTransit);
	DDX_Text(pDX, IDC_MARS_UP, m_cMarsUp);
	DDX_Text(pDX, IDC_MERCURY_2, m_cMercury2);
	DDX_Text(pDX, IDC_MERCURY_RISE, m_cMercuryRise);
	DDX_Text(pDX, IDC_MERCURY_SET, m_cMercurySet);
	DDX_Text(pDX, IDC_MERCURY_TRANSIT, m_cMercuryTransit);
	DDX_Text(pDX, IDC_MERCURY_UP, m_cMercuryUp);
	DDX_Text(pDX, IDC_MOON_2, m_cMoon2);
	DDX_Text(pDX, IDC_MOON_RISE, m_cMoonRise);
	DDX_Text(pDX, IDC_MOON_SET, m_cMoonSet);
	DDX_Text(pDX, IDC_MOON_TRANSIT, m_cMoonTransit);
	DDX_Text(pDX, IDC_MOON_UP, m_cMoonUp);
	DDX_Text(pDX, IDC_NEPTUNE_2, m_cNeptune2);
	DDX_Text(pDX, IDC_NEPTUNE_RISE, m_cNeptuneRise);
	DDX_Text(pDX, IDC_NEPTUNE_SET, m_cNeptuneSet);
	DDX_Text(pDX, IDC_NEPTUNE_TRANSIT, m_cNeptuneTransit);
	DDX_Text(pDX, IDC_NEPTUNE_UP, m_cNeptuneUp);
	DDX_Text(pDX, IDC_PLUTO_2, m_cPluto2);
	DDX_Text(pDX, IDC_PLUTO_RISE, m_cPlutoRise);
	DDX_Text(pDX, IDC_PLUTO_SET, m_cPlutoSet);
	DDX_Text(pDX, IDC_PLUTO_TRANSIT, m_cPlutoTransit);
	DDX_Text(pDX, IDC_PLUTO_UP, m_cPlutoUp);
	DDX_Text(pDX, IDC_RTS_DATE, m_cDate);
	DDX_Text(pDX, IDC_RTS_LAT, m_cLat);
	DDX_Text(pDX, IDC_RTS_LONG, m_cLon);
	DDX_Text(pDX, IDC_SATURN_2, m_cSaturn2);
	DDX_Text(pDX, IDC_SATURN_RISE, m_cSaturnRise);
	DDX_Text(pDX, IDC_SATURN_SET, m_cSaturnSet);
	DDX_Text(pDX, IDC_SATURN_TRANSIT, m_cSaturnTransit);
	DDX_Text(pDX, IDC_SATURN_UP, m_cSaturnUp);
	DDX_Text(pDX, IDC_SUN_2, m_cSun2);
	DDX_Text(pDX, IDC_SUN_RISE, m_cSunRise);
	DDX_Text(pDX, IDC_SUN_SET, m_cSunSet);
	DDX_Text(pDX, IDC_SUN_TRANSIT, m_cSunTransit);
	DDX_Text(pDX, IDC_SUN_UP, m_cSunUp);
	DDX_Text(pDX, IDC_URANUS_2, m_cUranus2);
	DDX_Text(pDX, IDC_URANUS_RISE, m_cUranusRise);
	DDX_Text(pDX, IDC_URANUS_SET, m_cUranusSet);
	DDX_Text(pDX, IDC_URANUS_TRANSIT, m_cUranusTransit);
	DDX_Text(pDX, IDC_URANUS_UP, m_cUranusUp);
	DDX_Text(pDX, IDC_VENUS_2, m_cVenus2);
	DDX_Text(pDX, IDC_VENUS_RISE, m_cVenusRise);
	DDX_Text(pDX, IDC_VENUS_SET, m_cVenusSet);
	DDX_Text(pDX, IDC_VENUS_TRANSIT, m_cVenusTransit);
	DDX_Text(pDX, IDC_VENUS_UP, m_cVenusUp);
	DDX_Text(pDX, IDC_TIME_STYLE, m_cTimeStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRiseTransitSet, CDialog)
	//{{AFX_MSG_MAP(CRiseTransitSet)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRiseTransitSet message handlers

void CRiseTransitSet::OnDestroy() 
{
	CDialog::OnDestroy();
	
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T ("RiseTransitSet"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("RiseTransitSet"), _T ("left"), winRect.left);
}

void CRiseTransitSet::OnClose() 
{
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T ("RiseTransitSet"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("RiseTransitSet"), _T ("left"), winRect.left);
	
	CDialog::OnClose();
}

void CRiseTransitSet::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}
