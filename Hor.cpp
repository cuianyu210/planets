// Hor.cpp : implementation file
//

#include "stdafx.h"
#include "Hor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHor dialog


//CHor::CHor(CWnd* pParent /*=NULL*/)
//	: CDialog(CHor::IDD, pParent)
CHor::CHor(class CTimeLocation* dick)
{
	m_pCTimeLocation = dick;
	//{{AFX_DATA_INIT(CHor)
	m_iAscNodeHouse = 0;
	m_iJupiterHouse = 0;
	m_iMarsHouse = 0;
	m_iMercuryHouse = 0;
	m_iMoonHouse = 0;
	m_iNeptuneHouse = 0;
	m_iPlutoHouse = 0;
	m_iSaturnHouse = 0;
	m_iSunHouse = 0;
	m_iUranusHouse = 0;
	m_iVenusHouse = 0;
	m_sVenusSign = _T("");
	m_sUranusSign = _T("");
	m_sSunSign = _T("");
	m_sSaturnSign = _T("");
	m_sPlutoSign = _T("");
	m_sNeptuneSign = _T("");
	m_sMoonSign = _T("");
	m_sMercurySign = _T("");
	m_sMarsSign = _T("");
	m_sJupiterSign = _T("");
	m_sAscNodeSign = _T("");
	m_sAscNodePos = _T("");
	m_sBirthPlace = _T("");
	m_sBirthTime = _T("");
	m_sJupRet = _T("");
	m_sJupiterPos = _T("");
	m_sMarRet = _T("");
	m_sMarsPos = _T("");
	m_sMercRet = _T("");
	m_sMercuryPos = _T("");
	m_sMoonPos = _T("");
	m_sName = _T("");
	m_sNepRet = _T("");
	m_sNeptunePos = _T("");
	m_sPlutRet = _T("");
	m_sPlutoPos = _T("");
	m_sSatRet = _T("");
	m_sSaturnPos = _T("");
	m_sSunPos = _T("");
	m_sUranRet = _T("");
	m_sUranusPos = _T("");
	m_sVenRet = _T("");
	m_sVenusPos = _T("");
	//}}AFX_DATA_INIT
}


void CHor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHor)
	DDX_Text(pDX, IDC_ASC_NODE_HOUSE, m_iAscNodeHouse);
	DDX_Text(pDX, IDC_JUPITER_HOUSE, m_iJupiterHouse);
	DDX_Text(pDX, IDC_MARS_HOUSE, m_iMarsHouse);
	DDX_Text(pDX, IDC_MERCURY_HOUSE, m_iMercuryHouse);
	DDX_Text(pDX, IDC_MOON_HOUSE, m_iMoonHouse);
	DDX_Text(pDX, IDC_NEPTUNE_HOUSE, m_iNeptuneHouse);
	DDX_Text(pDX, IDC_PLUTO_HOUSE, m_iPlutoHouse);
	DDX_Text(pDX, IDC_SATURN_HOUSE, m_iSaturnHouse);
	DDX_Text(pDX, IDC_SUN_HOUSE, m_iSunHouse);
	DDX_Text(pDX, IDC_URANUS_HOUSE, m_iUranusHouse);
	DDX_Text(pDX, IDC_VENUS_HOUSE, m_iVenusHouse);
	DDX_Text(pDX, IDC_VENUS_SIGN, m_sVenusSign);
	DDX_Text(pDX, IDC_URANUS_SIGN, m_sUranusSign);
	DDX_Text(pDX, IDC_SUN_SIGN, m_sSunSign);
	DDX_Text(pDX, IDC_SATURN_SIGN, m_sSaturnSign);
	DDX_Text(pDX, IDC_PLUTO_SIGN, m_sPlutoSign);
	DDX_Text(pDX, IDC_NEPTUNE_SIGN, m_sNeptuneSign);
	DDX_Text(pDX, IDC_MOON_SIGN, m_sMoonSign);
	DDX_Text(pDX, IDC_MERCURY_SIGN, m_sMercurySign);
	DDX_Text(pDX, IDC_MARS_SIGN, m_sMarsSign);
	DDX_Text(pDX, IDC_JUPITER_SIGN, m_sJupiterSign);
	DDX_Text(pDX, IDC_ASC_NODE_SIGN, m_sAscNodeSign);
	DDX_Text(pDX, IDC_ASC_NODE_POS, m_sAscNodePos);
	DDX_Text(pDX, IDC_BIRTH_PLACE, m_sBirthPlace);
	DDX_Text(pDX, IDC_BIRTH_TIME, m_sBirthTime);
	DDX_Text(pDX, IDC_JUP_RETROGRADE, m_sJupRet);
	DDX_Text(pDX, IDC_JUPITER_POS, m_sJupiterPos);
	DDX_Text(pDX, IDC_MAR_RETROGRADE, m_sMarRet);
	DDX_Text(pDX, IDC_MARS_POS, m_sMarsPos);
	DDX_Text(pDX, IDC_MERC_RETROGRADE, m_sMercRet);
	DDX_Text(pDX, IDC_MERCURY_POS, m_sMercuryPos);
	DDX_Text(pDX, IDC_MOON_POS, m_sMoonPos);
	DDX_Text(pDX, IDC_NAME, m_sName);
	DDX_Text(pDX, IDC_NEP_RETROGRADE, m_sNepRet);
	DDX_Text(pDX, IDC_NEPTUNE_POS, m_sNeptunePos);
	DDX_Text(pDX, IDC_PLUT_RETROGRADE, m_sPlutRet);
	DDX_Text(pDX, IDC_PLUTO_POS, m_sPlutoPos);
	DDX_Text(pDX, IDC_SAT_RETROGRADE, m_sSatRet);
	DDX_Text(pDX, IDC_SATURN_POS, m_sSaturnPos);
	DDX_Text(pDX, IDC_SUN_POS, m_sSunPos);
	DDX_Text(pDX, IDC_URAN_RETROGRADE, m_sUranRet);
	DDX_Text(pDX, IDC_URANUS_POS, m_sUranusPos);
	DDX_Text(pDX, IDC_VEN_RETROGRADE, m_sVenRet);
	DDX_Text(pDX, IDC_VENUS_POS, m_sVenusPos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHor, CDialog)
	//{{AFX_MSG_MAP(CHor)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, OnShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHor message handlers

void CHor::OnClose() 
{
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T ("Hor"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("Hor"), _T ("left"), winRect.left);
	
	
	CDialog::OnClose();
}

void CHor::OnDestroy() 
{
	CDialog::OnDestroy();
	
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T ("Hor"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("Hor"), _T ("left"), winRect.left);
}

void CHor::OnShow() 
{
	class CMainFrame* pCMainFrame;
	class CChildFrame* pChildFrame;
	class CPlanetsView* pCView;

//	Load all data members from dialog box
	UpdateData(true);

	pCMainFrame = (CMainFrame*)GetOwner();

//	if no child window, make one by calling File New from theApp
	if(!(pChildFrame = (CChildFrame*)pCMainFrame->MDIGetActive()))
	{
		CPlanetsApp* pApp = (CPlanetsApp*)AfxGetApp();
		pApp->OnNewFile();
		pChildFrame = (CChildFrame*)pCMainFrame->MDIGetActive();
		pCView = (CPlanetsView*)pChildFrame->GetActiveView();
	}
	else // we have a window, so get the view
	{
		pCView = (CPlanetsView*)pChildFrame->GetActiveView();
	}

//	Draw the chart
	pCView->DrawChart(this, m_pCTimeLocation);

}

void CHor::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}
