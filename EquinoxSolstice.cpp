// EquinoxSolstice.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EquinoxSolstice.h"
#include "astrocalc.h"
#include "astrotime.h"
#include "convert.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEquinoxSolstice dialog


CEquinoxSolstice::CEquinoxSolstice(CPlanetsDoc* bob)
//CEquinoxSolstice::CEquinoxSolstice(CWnd* pParent /*=NULL*/)
//	: CDialog(CEquinoxSolstice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEquinoxSolstice)
	m_iESYear = 0;
	m_sAutEqui = _T("");
	m_sSumSol = _T("");
	m_sVerEqui = _T("");
	m_sWinSol = _T("");
	m_dAEDuration = 0.0;
	m_dSSDuration = 0.0;
	m_dVEDuration = 0.0;
	m_dWSDuration = 0.0;
	m_iPrecision = 5;
	//}}AFX_DATA_INIT
}


void CEquinoxSolstice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEquinoxSolstice)
	DDX_Text(pDX, IDC_ES_YEAR, m_iESYear);
	DDX_Text(pDX, IDC_AUT_EQUI, m_sAutEqui);
	DDX_Text(pDX, IDC_SUM_SOL, m_sSumSol);
	DDX_Text(pDX, IDC_VER_EQUI, m_sVerEqui);
	DDX_Text(pDX, IDC_WIN_SOL, m_sWinSol);
	DDX_Text(pDX, IDC_AE_DUR, m_dAEDuration);
	DDX_Text(pDX, IDC_SS_DUR, m_dSSDuration);
	DDX_Text(pDX, IDC_VE_DUR, m_dVEDuration);
	DDX_Text(pDX, IDC_WS_DUR, m_dWSDuration);
	DDX_Text(pDX, IDC_PRECISION, m_iPrecision);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEquinoxSolstice, CDialog)
	//{{AFX_MSG_MAP(CEquinoxSolstice)
	ON_BN_CLICKED(IDC_RUN, OnRun)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEquinoxSolstice message handlers

void CEquinoxSolstice::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

//	Calculates the season cusps and their duration
void CEquinoxSolstice::OnRun() 
{
	
	astrocalc Astrocalc;
	astrotime Astrotime;
	convert Convert;

	double year, verEqui, sumSol, autEqui, winSol;
	double verEqui2;
	double dDay, dHour, junk;
	double dYear, dMonth;

	UpdateData(true);	//Bring in values from dialog
	year = m_iESYear;
//	Find time of each cusp
	Astrocalc.equinoxSolstice(year, verEqui, sumSol, autEqui, winSol, verEqui2);
//	Calculate duration of each season
	m_dVEDuration = sumSol - verEqui;
	m_dSSDuration = autEqui - sumSol;
	m_dAEDuration = winSol - autEqui;
	m_dWSDuration = verEqui2 - winSol;

//	For each cusp, convert julian day to year, month, day and day into
//	24 hour time, then make a string from this data
	Astrotime.calcYearMonthDay(verEqui, dYear, dMonth, dDay);
	dHour = 24 * Convert.LSmodf(dDay, &junk);
	m_sVerEqui = Astrotime.TimeDisplayUT(dYear, dMonth, dDay, dHour, m_iPrecision);
	
	Astrotime.calcYearMonthDay(sumSol, dYear, dMonth, dDay);
	dHour = 24 * Convert.LSmodf(dDay, &junk);
	m_sSumSol = Astrotime.TimeDisplayUT(dYear, dMonth, dDay, dHour, m_iPrecision);

	Astrotime.calcYearMonthDay(autEqui, dYear, dMonth, dDay);
	dHour = 24 * Convert.LSmodf(dDay, &junk);
	m_sAutEqui = Astrotime.TimeDisplayUT(dYear, dMonth, dDay, dHour, m_iPrecision);

	Astrotime.calcYearMonthDay(winSol, dYear, dMonth, dDay);
	dHour = 24 * Convert.LSmodf(dDay, &junk);
	m_sWinSol = Astrotime.TimeDisplayUT(dYear, dMonth, dDay, dHour, m_iPrecision);

	UpdateData(false);

}

void CEquinoxSolstice::OnYear()
{
	time_t osBinaryTime;  // C run-time time (defined in <time.h>)
	time( &osBinaryTime ) ;  // Get the current time from the 
		                     // operating system.
	int m_iNowYear, err;
	struct tm m_pNow;
//	m_pNow = 0;

//	DLAS 18Feb9
//	m_pNow = localtime( &osBinaryTime ); // Convert to local time.
	err = localtime_s(&m_pNow, &osBinaryTime);
	if (err) {
		printf("Invalid argument to _localtime64_s.");
		exit(1);
	}

	m_iNowYear = m_pNow.tm_year + 1900;

	m_iESYear = m_iNowYear;
	this->UpdateData(FALSE);

}

void CEquinoxSolstice::OnDestroy() 
{
    CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);

	pApp->WriteProfileInt(_T ("EquinoxSolstice"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("EquinoxSolstice"), _T ("left"), winRect.left);
	CDialog::OnDestroy();
}

void CEquinoxSolstice::OnClose() 
{
    CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);

	pApp->WriteProfileInt(_T ("EquinoxSolstice"), _T ("top"), winRect.top);
	pApp->WriteProfileInt(_T ("EquinoxSolstice"), _T ("left"), winRect.left);
	
	CDialog::OnClose();
}

BOOL CEquinoxSolstice::OnInitDialog() 
{
	CWinApp* pApp = AfxGetApp();

	CDialog::OnInitDialog();
	
	m_iPrecision = pApp->GetProfileInt(_T ("TimeLocation"), _T ("precision"), 5);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEquinoxSolstice::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}
