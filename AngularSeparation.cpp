// AngularSeparation.cpp : implementation file
//

#include "stdafx.h"
#include "AngularSeparation.h"
#include "astrocalc.h"
#include "convert.h"
#include "StarData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAngularSeparation dialog


CAngularSeparation::CAngularSeparation(CWnd* pParent /*=NULL*/)
	: CDialog(CAngularSeparation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAngularSeparation)
	m_sAngSep = _T("");
	m_bGeocentric = TRUE;
	m_bHeliocentric = FALSE;
	m_bPlanets1 = TRUE;
	m_bStars1 = FALSE;
	m_bPlanets2 = TRUE;
	m_bStars2 = FALSE;
	//}}AFX_DATA_INIT
	m_bChangedHelio = false;
}

CAngularSeparation::CAngularSeparation(CTimeLocation* dick)
{
	m_pTimeLocation = dick;
	m_sAngSep = _T("");
	m_bGeocentric = TRUE;
	m_bHeliocentric = FALSE;
	m_bPlanets1 = TRUE;
	m_bStars1 = FALSE;
	m_bPlanets2 = TRUE;
	m_bStars2 = FALSE;
	m_bChangedHelio = false;
}


void CAngularSeparation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAngularSeparation)
	DDX_Control(pDX, IDC_BODY2, m_sBody2);
	DDX_Control(pDX, IDC_BODY1, m_sBody1);
	DDX_Text(pDX, IDC_ANG_SEP, m_sAngSep);
	DDX_Check(pDX, IDC_GEOCENTRIC, m_bGeocentric);
	DDX_Check(pDX, IDC_HELIOCENTRIC, m_bHeliocentric);
	DDX_Check(pDX, IDC_PLANETS1, m_bPlanets1);
	DDX_Check(pDX, IDC_STARS1, m_bStars1);
	DDX_Check(pDX, IDC_PLANETS1, m_bPlanets2);
	DDX_Check(pDX, IDC_STARS1, m_bStars2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAngularSeparation, CDialog)
	//{{AFX_MSG_MAP(CAngularSeparation)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, OnRun)
	ON_BN_CLICKED(IDC_PLANETS1, OnPlanets1)
	ON_BN_CLICKED(IDC_STARS1, OnStars1)
	ON_BN_CLICKED(IDC_HELIOCENTRIC, OnHeliocentric)
	ON_LBN_SELCHANGE(IDC_BODY1, OnSelchangeBody1)
	ON_LBN_SELCHANGE(IDC_BODY2, OnSelchangeBody2)
	ON_BN_CLICKED(IDC_GEOCENTRIC, OnGeocentric)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAngularSeparation message handlers

BOOL CAngularSeparation::OnInitDialog() 
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAngularSeparation::OnClose() 
{
	CAngularSeparation::WriteProfiles();	
	CDialog::OnClose();
}

void CAngularSeparation::OnDestroy() 
{
	CDialog::OnDestroy();
	CAngularSeparation::WriteProfiles();
}

void CAngularSeparation::WriteProfiles()
{
	CWinApp* pApp = AfxGetApp();
	CRect winRect;
	CButton* geo;
	CButton* helio;
	CButton* planets1;
	CButton* stars1;
	CListBox* box1;
	CListBox* box2;
	int iGeo, iHelio, iBox1, iBox2;
	int iPlanets1, iStars1;

	box1 = (CListBox*)this->GetDlgItem(IDC_BODY1);
	box2 = (CListBox*)this->GetDlgItem(IDC_BODY2);
	iBox1 = box1->GetCurSel();
	iBox2 = box2->GetCurSel();

	geo = (CButton*)this->GetDlgItem(IDC_GEOCENTRIC);
	helio = (CButton*)this->GetDlgItem(IDC_HELIOCENTRIC);
	planets1 = (CButton*)this->GetDlgItem(IDC_PLANETS1);
	stars1 = (CButton*)this->GetDlgItem(IDC_STARS1);
	iGeo = geo->GetCheck();
	iHelio = helio->GetCheck();
	iPlanets1 = planets1->GetCheck();
	iStars1 = stars1->GetCheck();
	GetWindowRect(&winRect);

	pApp->WriteProfileInt( _T ("AngularSeparation"), _T ("box1"), iBox1);
	pApp->WriteProfileInt( _T ("AngularSeparation"), _T ("box2"), iBox2);
	pApp->WriteProfileInt( _T ("AngularSeparation"), _T ("geo"), iGeo);
	pApp->WriteProfileInt( _T ("AngularSeparation"), _T ("helio"), iHelio);
	pApp->WriteProfileInt( _T ("AngularSeparation"), _T ("planets1"), iPlanets1);
	pApp->WriteProfileInt( _T ("AngularSeparation"), _T ("stars1"), iStars1);
	pApp->WriteProfileInt( _T ("AngularSeparation"), _T ("top"), winRect.top);
	pApp->WriteProfileInt( _T ("AngularSeparation"), _T ("left"), winRect.left);
}

void CAngularSeparation::OnRun() 
{
	convert Convert;

	double angSep, L1, L2, B2, B1, temp, julDay;
	UINT outputStyle;

	m_iBody1 = m_sBody1.GetCurSel();
	m_iBody2 = m_sBody2.GetCurSel();

	UpdateData(true);
	if(		m_bGeocentric 
		&& (m_iBody1 == 4 || m_iBody2 == 4))
	{
		angSep = 0;
	}
	else if(	m_bHeliocentric
			&&	(m_iBody1 > 10 || m_iBody2 > 10))
	{
		angSep = 0;
	}
	else if(m_bGeocentric)
	{
		julDay = m_pTimeLocation->m_sTimeEntered.m_dJulianDay;
		CAngularSeparation::CalculatePositionsGeocentric(julDay, m_iBody1, m_iBody2,
														 L1, L2, B1, B2);
		angSep = CAngularSeparation::CalculateAngularSeparation(L1, L2, B1, B2);
	}
	else
	{
		julDay = m_pTimeLocation->m_sTimeEntered.m_dJulianDay;
		CAngularSeparation::CalculatePositionsHelioentric(julDay, m_iBody1, m_iBody2,
														 L1, L2, B1, B2);
		angSep = CAngularSeparation::CalculateAngularSeparation(L1, L2, B1, B2);
	}

	outputStyle = m_pTimeLocation->m_cOutputStyle;

	if(outputStyle == IDS_RADIAN)
	{
		m_sAngSep = Convert.DecimalToString(angSep, m_pTimeLocation->m_iPrecision);
	}
	else if(outputStyle == IDS_DECIMAL)
	{
		m_sAngSep = Convert.DecimalToString(Convert.radianToDegree(angSep), m_pTimeLocation->m_iPrecision);
	}
	else if(outputStyle == IDS_DEGREE)
	{
		temp = Convert.degreeToDMS(Convert.radianToDegree(angSep));
		m_sAngSep = Convert.HMSToString(temp, "d", m_pTimeLocation->m_iPrecision);
	}
	UpdateData(false);
}

void CAngularSeparation::CalculatePositionsGeocentric(double julDay, 
													  int body1, int body2,
													  double &L1, double &L2,
													  double &B1, double &B2)
{
	convert Convert;
	CPlanet body;
	CStarData pStar;
	astrocalc Astrocalc;
	double R1, R2, alpha, delta;
	int iStar;

	if(body1 < 11)
	{
		m_pTimeLocation->getBody(body, body1);
		body.geocentricSphericalAppPlanet(julDay, L1, B1, R1);
	}
	else
	{
		iStar = m_iStarPlace.GetAt(body1-11);
		pStar.equatorialApp(julDay,
		Convert.degreeToRadian(Convert.HMSToDegree(pStar.m_dConstellationAlpha[iStar])),
		Convert.degreeToRadian(Convert.DMSToDegree(pStar.m_dConstellationDelta[iStar])),
							alpha,
							delta);
		Astrocalc.equatorialToEcliptic(julDay, alpha, delta, L1, B1); 
	}
	if(body2 < 11)
	{
		m_pTimeLocation->getBody(body, body2);
		body.geocentricSphericalAppPlanet(julDay, L2, B2, R2);
	}
	else
	{
		iStar = m_iStarPlace.GetAt(body2-11);
		pStar.equatorialApp(julDay,
		Convert.degreeToRadian(Convert.HMSToDegree(pStar.m_dConstellationAlpha[iStar])),
		Convert.degreeToRadian(Convert.DMSToDegree(pStar.m_dConstellationDelta[iStar])),
							alpha,
							delta);
		Astrocalc.equatorialToEcliptic(julDay, alpha, delta, L2, B2); 
	}
}

void CAngularSeparation::CalculatePositionsHelioentric(double julDay, 
													   int body1, int body2,
													   double &L1, double &L2,
													   double &B1, double &B2)
{
	CPlanet body;
	
	double R1, R2;

	m_pTimeLocation->getBody(body, body1);
	body.primaryBodyLocation(julDay, L1, B1, R1);

	m_pTimeLocation->getBody(body, body2);
	body.primaryBodyLocation(julDay, L2, B2, R2);
}

//	See Meeus p. 105 (16.1) or (16.2)
double CAngularSeparation::CalculateAngularSeparation(double alpha1, double alpha2,
													double delta1, double delta2)
{
	double cosd, d, avgDelta, deltaAlpha, deltaDelta, temp;
	
	cosd = sin(delta1) * sin(delta2) +
		   cos(delta1) * cos (delta2) * cos(alpha1 - alpha2);
	if(cosd > .999999)
	{
		avgDelta = (delta1 + delta2) / (double)2;
		deltaAlpha = alpha1 - alpha2;
		deltaDelta = delta1 - delta2;
		temp = deltaAlpha * cos(avgDelta);

		d = sqrt( temp * temp + deltaDelta * deltaDelta);
	}
	else
	{
		d = acos(cosd);
	}
	return d;
}

//	All Constellation stars
void CAngularSeparation::OnPlanets1() 
{
	FillBodyBox(1);
}

//	Named stars
void CAngularSeparation::OnStars1() 
{
	FillBodyBox(2);
}

void CAngularSeparation::OnGeocentric() 
{
	CListBox *pBox1;
	CListBox *pBox2;
	CButton* geocentric;
	CButton* heliocentric;
	int iBox1, iBox2;

	pBox1 = (CListBox*)this->GetDlgItem(IDC_BODY1);
	pBox2 = (CListBox*)this->GetDlgItem(IDC_BODY2);
	geocentric = (CButton*)this->GetDlgItem(IDC_GEOCENTRIC);
	heliocentric = (CButton*)this->GetDlgItem(IDC_HELIOCENTRIC);

	iBox1 = pBox1->GetCurSel();
	iBox2 = pBox2->GetCurSel();

	if(		iBox1 == 4
		||
			iBox2 == 4)
	{
		geocentric->SetCheck(0);
		heliocentric->SetCheck(1);
	}
}

void CAngularSeparation::OnHeliocentric() 
{
	CListBox *pBox1;
	CListBox *pBox2;
	CButton* geocentric;
	CButton* heliocentric;
	int iBox1, iBox2;

	pBox1 = (CListBox*)this->GetDlgItem(IDC_BODY1);
	pBox2 = (CListBox*)this->GetDlgItem(IDC_BODY2);
	geocentric = (CButton*)this->GetDlgItem(IDC_GEOCENTRIC);
	heliocentric = (CButton*)this->GetDlgItem(IDC_HELIOCENTRIC);

	iBox1 = pBox1->GetCurSel();
	iBox2 = pBox2->GetCurSel();

	if(		iBox1 > 10
		||
			iBox2 > 10)
	{
		geocentric->SetCheck(1);
		heliocentric->SetCheck(0);
	}
}

//	1 = All Constellation Stars
//	2 = Named Stars
void CAngularSeparation::FillBodyBox(int iWhich)
{
	m_sBody1.ResetContent();
	m_sBody2.ResetContent();
	SetBodyPlanet();
	switch(iWhich)
	{
	case 1:
		SetBodyConstellationStars();
		break;
	case 2:
		SetBodyNamedStars();
		break;
	}
}

void CAngularSeparation::SetBodyPlanet()
{
	m_sBody1.InsertString(0, _T ("sun"));
	m_sBody1.InsertString(1, _T ("moon"));
	m_sBody1.InsertString(2, _T ("mercury"));
	m_sBody1.InsertString(3, _T ("venus"));
	m_sBody1.InsertString(4, _T ("earth"));
	m_sBody1.InsertString(5, _T ("mars"));
	m_sBody1.InsertString(6, _T ("jupiter"));
	m_sBody1.InsertString(7, _T ("saturn"));
	m_sBody1.InsertString(8, _T ("uranus"));
	m_sBody1.InsertString(9, _T ("neptune"));
	m_sBody1.InsertString(10, _T ("pluto"));

	m_sBody2.InsertString(0, _T ("sun"));
	m_sBody2.InsertString(1, _T ("moon"));
	m_sBody2.InsertString(2, _T ("mercury"));
	m_sBody2.InsertString(3, _T ("venus"));
	m_sBody2.InsertString(4, _T ("earth"));
	m_sBody2.InsertString(5, _T ("mars"));
	m_sBody2.InsertString(6, _T ("jupiter"));
	m_sBody2.InsertString(7, _T ("saturn"));
	m_sBody2.InsertString(8, _T ("uranus"));
	m_sBody2.InsertString(9, _T ("neptune"));
	m_sBody2.InsertString(10, _T ("pluto"));
}

void CAngularSeparation::SetBodyConstellationStars()
{
	CStarData pStarData;
	int i;

	m_iStarPlace.SetSize(0, 100);

	m_iStarArraySize = pStarData.m_iConArraySize;
	for(i=0; i<m_iStarArraySize; i++)
	{
		m_sBody1.InsertString(i+11, pStarData.m_sConstellationFullName[i]);
		m_sBody2.InsertString(i+11, pStarData.m_sConstellationFullName[i]);
		m_iStarPlace.Add(i);
	}
}

void CAngularSeparation::SetBodyNamedStars()
{
	int i;

	GetStarNames();
	SortStarNames();

	for(i=0; i<m_iStarArraySize; i++)
	{
		m_sBody1.InsertString(i+11, m_sStarShortNames.GetAt(i));
		m_sBody2.InsertString(i+11, m_sStarShortNames.GetAt(i));
	}
}

void CAngularSeparation::GetStarNames()
{
	CStarData pStarData;
	int i, j, iArraySize;
	CString sTemp;
	CString sEmpty;

	m_iStarPlace.SetSize(0, 100);
	m_sStarShortNames.SetSize(0, 100);

	sEmpty = "";

	iArraySize = pStarData.m_iConArraySize;
	j = 0;
	for(i=0; i<iArraySize; i++)
	{
		sTemp = pStarData.m_sConstellationShortName[i];
		if(!(sTemp == sEmpty))
		{
			m_sStarShortNames.Add(sTemp);
			m_iStarPlace.Add(i);
		}
	}
	m_iStarArraySize = m_iStarPlace.GetSize();
}

void CAngularSeparation::SortStarNames()
{
	bool swap;
	int i, iTemp, iTemp2;
	CString sTemp1;
	CString sTemp2;

	do
	{
		swap = false;
		for (i=0; i<m_iStarArraySize-1; i++)
		{
			sTemp1 = m_sStarShortNames.GetAt(i);
			sTemp2 = m_sStarShortNames.GetAt(i+1);
			if (sTemp1 > sTemp2 )
			{
				m_sStarShortNames.SetAt(i, sTemp2);
				m_sStarShortNames.SetAt(i+1, sTemp1);
				swap = true;

				iTemp = m_iStarPlace[i];
				iTemp2 = m_iStarPlace[i+1];
				m_iStarPlace.SetAt(i, iTemp2);
				m_iStarPlace.SetAt(i+1, iTemp);
			}
		}
	} while (swap);
}

void CAngularSeparation::OnSelchangeBody1() 
{
	NoHelioWithStars();
}

void CAngularSeparation::OnSelchangeBody2() 
{
	NoHelioWithStars();
}

//	Do not calculate Heliocentric coordinates for stars
//	Do not calculate geocentric if earth chosen
void CAngularSeparation::NoHelioWithStars()
{
	CListBox* pBox1;
	CListBox* pBox2;
	CButton* geo;
	CButton* helio;
	int itemNumber1, itemNumber2;

	pBox1 = (CListBox*)this->GetDlgItem(IDC_BODY1);
	pBox2 = (CListBox*)this->GetDlgItem(IDC_BODY2);
	geo = (CButton*)this->GetDlgItem(IDC_GEOCENTRIC);
	helio = (CButton*)this->GetDlgItem(IDC_HELIOCENTRIC);

	itemNumber1 = pBox1->GetCurSel();
	itemNumber2 = pBox2->GetCurSel();

	if(		itemNumber1 > 10
		||
			itemNumber2 > 10)
	{
		geo->SetCheck(1);
		helio->SetCheck(0);
	}
	if(		itemNumber1 == 4
		||
			itemNumber2 == 4)
	{
		geo->SetCheck(0);
		helio->SetCheck(1);
	}
}

void CAngularSeparation::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}
