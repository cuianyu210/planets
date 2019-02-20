// MoonDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MoonDialog.h"
#include "convert.h"
#include "astrotime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoonDialog dialog


CMoonDialog::CMoonDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMoonDialog::IDD, pParent)
{
	m_iMoonDay = 0;
	m_sMoonDST = _T("");
	m_dTimeZone = 0.0;
	m_iMoonMonth = 0;
	m_iMoonYear = 0;
}

CMoonDialog::CMoonDialog(CTimeLocation* pTimeL)
	: CDialog(CMoonDialog::IDD, pTimeL)
{
	m_pTL = pTimeL;
	//{{AFX_DATA_INIT(CMoonDialog)
	m_iMoonDay = 0;
	m_sMoonDST = _T("");
	m_iMoonYear = 0;
	m_iMoonMonth = 0;
	m_sNextFull = _T("");
	m_sNextNew = _T("");
	m_sNextQuarter = _T("");
	m_sPreviousQuarter = _T("");
	m_sNextQtr = _T("");
	m_sPrevQtr = _T("");
	m_dTimeZone = 0.0;
	m_sTimeType = _T("Local Time");
	//}}AFX_DATA_INIT
}


void CMoonDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoonDialog)
	DDX_Text(pDX, IDC_MOON_DAY, m_iMoonDay);
	DDX_Text(pDX, IDC_MOON_DST, m_sMoonDST);
	DDX_Text(pDX, IDC_MOON_YEAR, m_iMoonYear);
	DDX_Text(pDX, IDC_MOON_MONTH, m_iMoonMonth);
	DDX_Text(pDX, IDC_NEXT_FULL, m_sNextFull);
	DDX_Text(pDX, IDC_NEXT_NEW, m_sNextNew);
	DDX_Text(pDX, IDC_NEXT_QUARTER, m_sNextQuarter);
	DDX_Text(pDX, IDC_PREVIOUS_QUARTER, m_sPreviousQuarter);
	DDX_Text(pDX, IDC_NEXT_QTR, m_sNextQtr);
	DDX_Text(pDX, IDC_PREV_QTR, m_sPrevQtr);
	DDX_Text(pDX, IDC_MOON_HOUR, m_dTimeZone);
	DDX_Text(pDX, IDC_TIME_TYPE, m_sTimeType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoonDialog, CDialog)
	//{{AFX_MSG_MAP(CMoonDialog)
	ON_BN_CLICKED(IDC_MOON_PHASE_ALL, OnMoonPhaseAll)
	ON_BN_CLICKED(IDC_MOON_PHASE_CLEAR, OnMoonPhaseClear)
	ON_BN_CLICKED(IDC_UT_BTN, OnUtBtn)
	ON_BN_CLICKED(IDC_MOON_DO_YEAR, OnMoonDoYear)
	ON_EN_KILLFOCUS(IDC_MOON_HOUR, OnKillfocusMoonHour)
	ON_EN_KILLFOCUS(IDC_MOON_DST, OnKillfocusMoonDst)
	ON_BN_CLICKED(IDC_NEXT_QUARTER_BTN, OnNextQuarterBtn)
	ON_BN_CLICKED(IDC_NEXT_NEW_BTN, OnNextNewBtn)
	ON_BN_CLICKED(IDC_NEXT_FULL_BTN, OnNextFullBtn)
	ON_BN_CLICKED(IDC_PREVIOUS_QTR_BTN, OnPreviousQtrBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoonDialog message handlers

void CMoonDialog::OnNextQuarterBtn() 
{
	ULONG uPHASE;

	m_sNextQuarter = FindTime(NEXT_QUARTER, &uPHASE);

	switch ( uPHASE )
	{
	case NEW_MOON :
		m_sNextQtr = "New";
		break;
	case FIRST_QUARTER :
		m_sNextQtr = "First";
		break;
	case FULL_MOON :
		m_sNextQtr = "Full";
		break;
	case THIRD_QUARTER :
		m_sNextQtr = "Third";
		break;
	}
	UpdateData(false);
}

void CMoonDialog::OnNextNewBtn() 
{
	ULONG uPHASE;

	m_sNextNew = FindTime(NEW_MOON, &uPHASE);
	UpdateData(false);
}

void CMoonDialog::OnNextFullBtn() 
{
	ULONG uPHASE;

	m_sNextFull = FindTime(FULL_MOON, &uPHASE);
	UpdateData(false);
}

void CMoonDialog::OnPreviousQtrBtn() 
{
	ULONG uPHASE;

	m_sPreviousQuarter = FindTime(PREVIOUS_QUARTER, &uPHASE);
	switch ( uPHASE )
	{
	case NEW_MOON :
		m_sPrevQtr = "New";
		break;
	case FIRST_QUARTER :
		m_sPrevQtr = "First";
		break;
	case FULL_MOON :
		m_sPrevQtr = "Full";
		break;
	case THIRD_QUARTER :
		m_sPrevQtr = "Third";
		break;
	}
	UpdateData(false);
}

void CMoonDialog::StartUp()
{
	OnNextQuarterBtn();
	OnNextNewBtn();
	OnNextFullBtn();
	OnPreviousQtrBtn();
}


CString CMoonDialog::FindTime(ULONG uPhase, ULONG *PHASE)
{
	double phaseDate;
	UpdateDataMD();
	CString sTime;

	phaseDate = pMoon->phase2(m_dJulDay, uPhase, PHASE);
	phaseDate -= m_dTZone / 24.;
	if( m_sMoonDST == "y")phaseDate += 1./24.;
	sTime = MakeTimeString(phaseDate);

	return sTime;
}

void CMoonDialog::UpdateDataMD()
{
	astrotime Astrotime;

	UpdateData(true);

	m_dYear = (double)m_iMoonYear;
	m_dMonth = (double)m_iMoonMonth;
	m_dDay = (double)m_iMoonDay;
	m_dTZone= m_dTimeZone;
	m_sDST = m_sMoonDST;

	m_dJulDay = Astrotime.calcJulianDay(m_dYear,
									m_dMonth,
									m_dDay);
}

BOOL CMoonDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	pMoon = new CMoonPhase();
	
	m_iMoonYear = (int)m_pTL->m_sTimeEntered.m_dYear;
	m_iMoonMonth = (int)m_pTL->m_sTimeEntered.m_dMonth;
	m_iMoonDay = (int)m_pTL->m_sTimeEntered.m_dDay;
	m_dTimeZone = m_pTL->m_sTimeEntered.m_dTimeZone;
	m_sMoonDST = m_pTL->m_sTimeEntered.m_sDst;
	m_sLocalDST = m_sMoonDST;
	m_dLocalTimeZone = m_dTimeZone;

	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMoonDialog::OnOK() 
{
	OnCancel();
}

CString CMoonDialog::MakeTimeString(double julDay)
{
	astrotime Astrotime;
	convert Convert;
	double year, month, day;
	double decimalHour, date;
	CString result;

	Astrotime.calcYearMonthDay(julDay, year, month, day);
	decimalHour = 24. * Convert.LSmodf(day, &date);
	result = Astrotime.TimeDisplayUT(year,
								 month,
								 date,
								 decimalHour,
								 m_pTL->m_iPrecision);
								 
	return result;
}

void CMoonDialog::OnMoonPhaseAll() 
{
	StartUp();
}

void CMoonDialog::OnMoonPhaseClear() 
{
	m_sNextFull.Empty();
	m_sNextNew.Empty();
	m_sNextQuarter.Empty();
	m_sPreviousQuarter.Empty();
	m_sNextQtr.Empty();
	m_sPrevQtr.Empty();

	UpdateData(false);
}

void CMoonDialog::OnUtBtn() 
{
	CButton* utBut = (CButton*)this->GetDlgItem(IDC_TIME_TYPE);
	CEdit* dstEdit = (CEdit*)this->GetDlgItem(IDC_MOON_DST);
	CEdit* timezoneEdit = (CEdit*)this->GetDlgItem(IDC_MOON_HOUR);//trust me
	UpdateData(true);

	if("UT" == m_sTimeType)
	{
		dstEdit->SendMessage(EM_SETREADONLY, FALSE, 0);
		timezoneEdit->SendMessage(EM_SETREADONLY, FALSE, 0);
		m_sTimeType = "Local Time";
		m_sMoonDST = m_sLocalDST;
		m_dTimeZone = m_dLocalTimeZone;
	}
	else
	{
		m_sTimeType = "UT";
		m_sMoonDST = _T("n");
		m_dTimeZone = 0.0;
		dstEdit->SendMessage(EM_SETREADONLY, TRUE, 0);
		timezoneEdit->SendMessage(EM_SETREADONLY, TRUE, 0);
	}

	UpdateData(false);
	StartUp();
}

void CMoonDialog::OnMoonDoYear() 
{
	astrotime Astrotime;

	UpdateData(true);

	m_dYear = (double)m_iMoonYear;
	m_dMonth = 1.;
	m_dDay = 1.;
	m_dTZone= m_dTimeZone;
	m_sDST = m_sMoonDST;

	m_dJulDay = Astrotime.calcJulianDay(m_dYear,
									m_dMonth,
									m_dDay);
	pMoon->WholeYear(this, m_dJulDay);
}

void CMoonDialog::PostNcDestroy() 
{
	delete pMoon;
	delete this;
	
	CDialog::PostNcDestroy();
}

void CMoonDialog::OnCancel() 
{
	DestroyWindow();
}

void CMoonDialog::OnKillfocusMoonHour() 
{
	UpdateData(true);
	m_dLocalTimeZone = m_dTimeZone;
}

void CMoonDialog::OnKillfocusMoonDst() 
{
	UpdateData(true);
	m_sLocalDST = m_sMoonDST;
}
