// TimeLocation.cpp : implementation file
//

#include "stdafx.h"
#include "TimeLocation.h"
#include "Star.h"
#include "variation.h"
#include "Validate.h"
#include "AngularSeparation.h"
#include "VariationBox.h"
#include "RiseTransitSet.h"
#include "MoonDialog.h"
#include "convert.h"
#include "astrotime.h"
#include "astrocalc.h"
#include "Error.h"
#include <fstream>
#include <stdlib.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeLocation dialog
CTimeLocation::CTimeLocation(CPlanetsDoc* pD)
//CTimeLocation::CTimeLocation(CWnd* pParent /*=NULL*/)
//	: CDialog(CTimeLocation::IDD, pParent)
{
	m_sDisTypeDMS = 'd';
	m_sDisTypeHMS = 'h';
	//{{AFX_DATA_INIT(CTimeLocation)
	m_cAmpm = _T("a"); //a
	m_cDst = _T("n");//n
	m_cLatitude_NS = _T("N");//n
	m_cLongitude_WE = _T("W");//w
	m_iPrecision = 5;
	m_iDate = 1;
	m_dHour = 0;
	m_dTimeZone = 0;
	m_iYear = 0;
	m_sMonth = _T("");
	m_sLocation = _T("");
	m_sLatitude = _T("");
	m_sLongitude = _T("");
	//}}AFX_DATA_INIT
}


void CTimeLocation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeLocation)
	DDX_Text(pDX, IDC_AMPM, m_cAmpm);
	DDV_MaxChars(pDX, m_cAmpm, 2);
	DDX_Text(pDX, IDC_DAYLIGHT_ST, m_cDst);
	DDV_MaxChars(pDX, m_cDst, 3);
	DDX_Text(pDX, IDC_LATITUDE_NS, m_cLatitude_NS);
	DDV_MaxChars(pDX, m_cLatitude_NS, 5);
	DDX_Text(pDX, IDC_LONGITUDE_WE, m_cLongitude_WE);
	DDV_MaxChars(pDX, m_cLongitude_WE, 4);
	DDX_Text(pDX, IDC_PRECISION, m_iPrecision);
	DDX_Text(pDX, IDC_DATE, m_iDate);
	DDV_MinMaxInt(pDX, m_iDate, 1, 31);
	DDX_Text(pDX, IDC_HOUR, m_dHour);
	DDV_MinMaxDouble(pDX, m_dHour, 0., 24.);
	DDX_Text(pDX, IDC_TIME_ZONE, m_dTimeZone);
	DDV_MinMaxDouble(pDX, m_dTimeZone, -12., 12.);
	DDX_Text(pDX, IDC_YEAR, m_iYear);
	DDX_Text(pDX, IDC_MONTH, m_sMonth);
	DDX_CBString(pDX, IDC_LOCATION, m_sLocation);
	DDX_Text(pDX, IDC_LATITUDE, m_sLatitude);
	DDX_Text(pDX, IDC_LONGITUDE, m_sLongitude);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeLocation, CDialog)
	//{{AFX_MSG_MAP(CTimeLocation)
	ON_BN_CLICKED(IDC_PLANET_POSITIONS, OnAzimuthAltitude)
	ON_BN_CLICKED(IDC_HELIOCENTRIC_SPHERICAL, OnHeliocentricSpherical)
	ON_BN_CLICKED(IDC_EQUATORIAL_APPARENT, OnEquatorialApparent)
	ON_BN_CLICKED(IDC_GEOCENTRIC_CARTESIAN, OnGeocentricCartesian)
	ON_BN_CLICKED(IDC_GEOCENTRIC_SPHERICAL_APP, OnGeocentricSphericalApp)
	ON_BN_CLICKED(IDC_GEOCENTRIC_SPHERICAL_TRUE, OnGeocentricSphericalTrue)
	ON_BN_CLICKED(IDC_HELIOCENTRIC_CARTESIAN, OnHeliocentricCartesian)
	ON_BN_CLICKED(IDC_RISE_SET_TRANSIT, OnRiseSetTransit)
	ON_BN_CLICKED(IDC_ASTRONOMICAL_DATA, OnAstronomicalData)
	ON_BN_CLICKED(IDC_BUTTON_DST, OnButtonDst)
	ON_BN_CLICKED(IDC_BUTTON_AMPM, OnButtonAmpm)
	ON_BN_CLICKED(IDC_BUTTON_NS, OnButtonNs)
	ON_BN_CLICKED(IDC_BUTTON_WE, OnButtonWe)
	ON_BN_CLICKED(IDC_OUTPUT_GROUP, OnOutputGroup)
	ON_BN_CLICKED(IDC_GHA_DEC, OnGhaDec)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_ANGULAR_SEPARATION, OnAngularSeparation)
	ON_BN_CLICKED(IDC_HOR, OnHor)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MONTH, OnDeltaposSpinMonth)
	ON_EN_KILLFOCUS(IDC_MONTH, OnKillfocusMonth)
	ON_EN_KILLFOCUS(IDC_LATITUDE, OnKillfocusLatitude)
	ON_EN_KILLFOCUS(IDC_LONGITUDE, OnKillfocusLongitude)
	ON_EN_KILLFOCUS(IDC_AMPM, OnKillfocusAmpm)
	ON_EN_KILLFOCUS(IDC_DATE, OnKillfocusDate)
	ON_EN_KILLFOCUS(IDC_DAYLIGHT_ST, OnKillfocusDaylightSt)
	ON_EN_KILLFOCUS(IDC_HOUR, OnKillfocusHour)
	ON_EN_KILLFOCUS(IDC_LATITUDE_NS, OnKillfocusLatitudeNs)
	ON_EN_KILLFOCUS(IDC_LONGITUDE_WE, OnKillfocusLongitudeWe)
	ON_EN_KILLFOCUS(IDC_TIME_ZONE, OnKillfocusTimeZone)
	ON_EN_KILLFOCUS(IDC_YEAR, OnKillfocusYear)
	ON_EN_CHANGE(IDC_MONTH, OnChangeMonth)
	ON_BN_CLICKED(IDC_PLACE_ADD, OnAddPlace)
	ON_BN_CLICKED(IDC_PLACE_DELETE, OnPlaceDelete)
	ON_BN_CLICKED(IDC_STARS, OnStars)
	ON_BN_CLICKED(IDC_MAGNETIC_VARIATION, OnMagneticVariation)
	ON_BN_CLICKED(IDC_MOON_PHASE_BTN, OnMoonPhaseBtn)
	ON_BN_CLICKED(IDC_NOW, OnNow)
	ON_BN_CLICKED(IDC_DO_ALL, OnDoAll)
	ON_WM_MOVE()
	ON_CBN_SELCHANGE(IDC_LOCATION, OnSelchangeLocation)
	ON_BN_CLICKED(IDOK, OnCancel)
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_STARS_PRINT, &CTimeLocation::OnBnClickedStarsPrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeLocation message handlers

void CTimeLocation::OnStars() 
{
	class CMainFrame* pCMainFrame;
	class CChildFrame* pChildFrame;
	class CPlanetsView* pCView;

	pCMainFrame = (CMainFrame*)this->GetOwner();

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
	// This starts a CStar
	pCView->StarsSetUp(this);	
	
	int iNumPlanets;
	CString dateString;
	CArray<int, int> iConnys;
	
	m_sCalcMethod = "GeocentricHorizontal";
	m_sCalcType = "Spherical";
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
//	Don't do Earth
	m_pPlanetSet[4] = 0;
	iNumPlanets = CTimeLocation::CountPlanets();

	if(iNumPlanets > 0)
	{
		CTimeLocation::calcAzimuthAltitude();
	}

	CTimeLocation::WhichConstellations(&iConnys);
	dateString = m_sTimeEntered.DateLongString();

	pCView->m_pCStar->doStars(iNumPlanets, m_sTimeEntered.m_dJulianDay,
			m_sTimeEntered.m_dLatitude, m_sTimeEntered.m_dLongitude,
			0, dateString, &iConnys);
}

//	"Geocentric Horizontal App Azimuth Altitude" button
void CTimeLocation::OnAzimuthAltitude() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top;
	
	m_sCalcMethod = "GeocentricHorizontal";
	m_sCalcType = "Spherical";
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
//	Don't do Earth
	m_pPlanetSet[4] = 0;

	CTimeLocation::calcAzimuthAltitude();
	CTimeLocation::calcHeliocentricSphericalRetrograde();

//	Create and display results box
	m_pModeless = new CDataDisplay(this);
	m_pModeless->Create((LPCTSTR) IDD_DATA_DISPLAY, NULL);

	left = pApp->GetProfileInt( _T ("DataDisplay"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("DataDisplay"), _T ("top"), 0);

	m_pModeless->MoveWindow(left, top, 365, 559, true);
	m_pModeless->ShowWindow(SW_SHOW);

//	Output data to dialog
	CTimeLocation::assignAzAltValues();
	if(m_pPlanetSet[1] == 1)
	{
		m_pModeless->m_sMoonQuarter = CTimeLocation::CalculateMoonsQuarter();
	}
	m_pModeless->UpdateData(false);
}

void CTimeLocation::WhichConstellations(CArray<int, int> *iArray)
{
	CListBox *pListBox;

	pListBox = (CListBox*)this->GetDlgItem(IDC_CONST_LIST);

	int nCount = pListBox->GetSelCount();

	iArray->SetSize(nCount);
	pListBox->GetSelItems(nCount, iArray->GetData()); 
}

//	Calculates the moon's quarter as a fraction.
//	0.00 = new moon
//	1.00 = 1st quarter
//	2.00 = full
//	3.00 = 3rd quarter
//	Displayed to 3 decimal places
CString CTimeLocation::CalculateMoonsQuarter()
{
	CPlanet pSun;
	CPlanet pMoon;
	convert Convert;

	CString s_Quarter, sTemp;
	double sunL, sunB, sunR, moonL, moonB, moonR;
	double dif, dPi, dPiOver2, difFract;

	dPi = Convert.Pi();
	dPiOver2 = dPi / (double)2;

	pSun.sun();
	pMoon.moon();

	pSun.geocentricSphericalAppPlanet(m_sTimeEntered.m_dJulianDay,sunL, sunB, sunR);
	pMoon.geocentricSphericalAppPlanet(m_sTimeEntered.m_dJulianDay,moonL, moonB, moonR);

	dif = Convert.radianPositiveValue(moonL - sunL);

	if(dif > 1.5 * dPi)
	{
		difFract = (double)3 + ((dif -  (1.5 * dPi))/ dPiOver2);
	}
	else if(dif > dPi)
	{
		difFract = (double)2 + ((dif - dPi) / dPiOver2);
	}
	else if(dif > dPiOver2)
	{
		difFract = (double)1 + ((dif - dPiOver2) / dPiOver2);
	}
	else
	{
		difFract = dif / dPiOver2;
	}

	sTemp = Convert.DecimalToString(difFract, 3);
	s_Quarter = "Q" + sTemp;

	return s_Quarter;
}

//	Calculate azimuth and altitude
void CTimeLocation::calcAzimuthAltitude()
{
	CPlanet body;

	CTimeLocation::zeroAllValues();
	int i;

	for(i=0; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1 )
		{
			CTimeLocation::getBody(body, i);

			body.azimuthAltitudePlanet(
									   m_sTimeEntered.m_dJulianDay,
									   m_sTimeEntered.m_dLatitude,
									   m_sTimeEntered.m_dLongitude,
									   m_pValues[i][0],
									   m_pValues[i][1]);
		}
	}
}

//	Assign values to variables for azimuth altitude
void CTimeLocation::assignAzAltValues()
{
	convert Convert;
	int i, j;
	double temp;
	CString sTemp;

	CTimeLocation::assignModelessArray();

	for (i=0; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1)
		{
			for(j=0; j<2; j++)
			{
				if(m_cOutputStyle == IDS_RADIAN)
				{
					*m_pDataDisplayValues[i][j] = m_pValues[i][j];
					*m_pModelessValues[i][j] = Convert.DecimalToString(m_pValues[i][j], m_iPrecision);
				}
				else if(m_cOutputStyle == IDS_DECIMAL)
				{
					*m_pDataDisplayValues[i][j] = m_pValues[i][j];
					*m_pModelessValues[i][j] = Convert.DecimalToString(Convert.radianToDegree(m_pValues[i][j]), m_iPrecision);
				}
				else if(m_cOutputStyle == IDS_DEGREE)
				{
					*m_pDataDisplayValues[i][j] = m_pValues[i][j];
					temp = Convert.degreeToDMS(Convert.radianToDegree(m_pValues[i][j]));
					*m_pModelessValues[i][j] = Convert.HMSToString(temp, m_sDisTypeDMS, m_iPrecision);
				}
			}
		}
		else
		{
			*m_pDataDisplayValues[i][0] = 0;
			*m_pDataDisplayValues[i][1] = 0;
			*m_pModelessValues[i][0] = "";
			*m_pModelessValues[i][1] = "";
		}
	}
	sTemp.LoadString(m_cOutputStyle);
	
	m_pModeless->m_cADegreeStyle = sTemp;
	m_pModeless->m_dJulianDate = m_sTimeEntered.m_dJulianDay;
	m_pModeless->m_cDataTitle = m_sTimeEntered.DateLongString();
	m_pModeless->m_cDataDisplayLat = CTimeLocation::DataDisplayLatLon(
		"Latitude", m_cLatitude, m_cLatitude_NS);
	m_pModeless->m_cDataDisplayLon = CTimeLocation::DataDisplayLatLon(
		"Longitude", m_cLongitude, m_cLongitude_WE);
	m_pModeless->m_cMercuryRetrograde = m_cMercRetro;
	m_pModeless->m_cVenusRetrograde = m_cVenRetro;
	m_pModeless->m_cMarsRetrograde = m_cMarRetro;
	m_pModeless->m_cJupiterRetrograde = m_cJupRetro;
	m_pModeless->m_cSaturnRetrograde = m_cSatRetro;
	m_pModeless->m_cUranusRetrograde = m_cUranRetro;
	m_pModeless->m_cNeptuneRetrograde = m_cNepRetro;
	m_pModeless->m_cPlutoRetrograde = m_cPlutRetro;
}

//	Give it "Latitude", 45.32 and "N" and you get "Latitude 45.32 N"
CString CTimeLocation::DataDisplayLatLon(CString type, CString value, CString nswe)
{
	value = type + " " + value + " " + nswe;
	return value;
}

//	Takes time values and produces GMT, and makes radian values for 
//	latitude and longitude 
void CTimeLocation::ProcessData()
{
	convert Convert;

	m_sTimeEntered.convertToDoubleGMT(m_iPrecision);

	if (m_cLatitude_NS.GetLength() != 0)
	{
		if(		m_cLatitude_NS[0] == 's'
		   ||	m_cLatitude_NS[0] == 'S')m_sTimeEntered.m_dLatitude *= (double)-1;
	}
	m_sTimeEntered.m_dLatitude = Convert.degreeToRadian(m_sTimeEntered.m_dLatitude);
	
	if (m_cLongitude_WE.GetLength() != 0)
	{
		if(		m_cLongitude_WE[0] == 'e'
		   ||	m_cLongitude_WE[0] == 'E')m_sTimeEntered.m_dLongitude *= (double)-1;
	}
	m_sTimeEntered.m_dLongitude = Convert.degreeToRadian(m_sTimeEntered.m_dLongitude);
	
}

//	Is apparent motion of body retrograde?  This uses the geometry of what it means
//	to be Retrograde to calculate retrograde-ness.  The angles are different for
//	inner and outer planets but the required result is the same:  if the body in
//	question appears to travel in a direction opposite to the Sun relative to the 
//	to the heavens thenit is considered retrograde motion.  I don't remember how I
//	figured all this out, so will have to reconstruct it.  It seems to be accurate 
//	compared to some tables I have for astrology.
///////////////////////////////////////////////////////////////////////////////////
//	That was the first method.  It employed fancy math that did not quite work.  It
//	started retrograde at the wrong time.  Anyway it is easier and more correct
//	to just use ecliptic spherical coordinates.  If the longitude decreases, the 
//	planet is retrograde.  Find longitude at time then add ten minutes and find again.
//	Subtract the difference.  voila
void CTimeLocation::calcHeliocentricSphericalRetrograde()
{
	CPlanet body;
	CPlanet ernie;

	double dBodyL, dBodyB, dBodyR, dBodyL2, dBodyB2, dBodyR2;
	int i;

	CString *strTemp=NULL;
	
	m_cMercRetro = m_cVenRetro = "";
	m_cMarRetro = m_cJupRetro = m_cSatRetro = "";
	m_cUranRetro = m_cNepRetro = m_cPlutRetro = "";

//	Now cycle through the bodies
	for(i=2; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1)
		{
			switch (i)
			{
			case 2:
				body.mercury();
				strTemp = &m_cMercRetro;
				break;
			case 3:
				body.venus();
				strTemp = &m_cVenRetro;
				break;
			case 5:
				body.mars();
				strTemp = &m_cMarRetro;
				break;
			case 6:
				body.jupiter();
				strTemp = &m_cJupRetro;
				break;
			case 7:
				body.saturn();
				strTemp = &m_cSatRetro;
				break;
			case 8:
				body.uranus();
				strTemp = &m_cUranRetro;
				break;
			case 9:
				body.neptune();
				strTemp = &m_cNepRetro;
				break;
			case 10:
				body.pluto();
				strTemp = &m_cPlutRetro;
				break;
			}// end of "switch"

			body.geocentricSphericalTruePlanet(m_sTimeEntered.m_dJulianDay, dBodyL, dBodyB, dBodyR);

			//	.0069444 = the fraction of a day that is 10 minutes
			body.geocentricSphericalTruePlanet(m_sTimeEntered.m_dJulianDay + 0.00694, dBodyL2, dBodyB2, dBodyR2);

			if((dBodyL2 - dBodyL) < 0.0) *strTemp = "R";

		}//end of "if(m_pPlanetSet[i] == 1)"
	}//end of "for(i=1, i<9, i++)"
}

//	"Heliocentric Spherical" button
void CTimeLocation::OnHeliocentricSpherical() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top;
	
	m_sCalcMethod = "HeliocentricSpherical";
	m_sCalcType = "Spherical";
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
//	Don't do the sun or for now moon
	m_pPlanetSet[0] = 0;
	m_pPlanetSet[1] = 0;

	CTimeLocation::calcHeliocentricSpherical();

//	Create and display results box
	m_pModelessRadius = new CRadiusDisplay(this);
	m_pModelessRadius->Create((LPCTSTR) IDD_RADIUS_DISPLAY, NULL);
	left = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("top"), 0);

	m_pModelessRadius->MoveWindow(left, top, 450, 568, true);
	m_pModelessRadius->ShowWindow(SW_SHOW);

//	Output data to dialog
	CTimeLocation::assignHelioSphericalValues();
	m_pModelessRadius->UpdateData(false);

}

//	Calculate Heliocentric Spherical positions
void CTimeLocation::calcHeliocentricSpherical()
{
	CPlanet body;

	CTimeLocation::zeroAllValues();
	int i;

	for(i=0; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1 )
		{
			CTimeLocation::getBody(body, i);
			body.primaryBodyLocation(m_sTimeEntered.m_dJulianDay, m_pValues[i][0],
									 m_pValues[i][1], m_pValues[i][2]);
		}
	}
}

//	Assign Heliocentric Spherical values
void CTimeLocation::assignHelioSphericalValues()
{
	CTimeLocation::assignModelessRadiusValues();

	m_pModelessRadius->m_cDegreeStyle.LoadString(m_cOutputStyle);
	m_pModelessRadius->m_cRadiusDisplayTime = m_sTimeEntered.DateLongString();
	m_pModelessRadius->m_sLat = CTimeLocation::DataDisplayLatLon(
		"Latitude", m_cLatitude, m_cLatitude_NS);
	m_pModelessRadius->m_sLon = CTimeLocation::DataDisplayLatLon(
		"Longitude", m_cLongitude, m_cLongitude_WE);
	m_pModelessRadius->m_cDisplayTitle = "Heliocentric Spherical Coordinates";
	m_pModelessRadius->m_cRadiusDisplayLambda1 = "Ecliptical";
	m_pModelessRadius->m_cRadiusDisplayLambda2 = "Longitude";
	m_pModelessRadius->m_cRadiusDisplayBeta1 = "Ecliptical";
	m_pModelessRadius->m_cRadiusDisplayBeta2 = "Latitude";
	m_pModelessRadius->m_cRadiusDisplayRadius1 = "Distance";
	m_pModelessRadius->m_cRadiusDisplayRadius2 = "From Sun";

}

//	The do all button sets all of the planets to calculate or not
//	calculate when turned off
void CTimeLocation::OnDoAll() 
{
	m_pDoAll = (CButton*)this->GetDlgItem(IDC_DO_ALL);
	m_pSunCheckBox = (CButton*)this->GetDlgItem(IDC_DO_SUN);
	m_pMoonCheckBox = (CButton*)this->GetDlgItem(IDC_DO_MOON);
	m_pMercuryCheckBox = (CButton*)this->GetDlgItem(IDC_DO_MERCURY);
	m_pVenusCheckBox = (CButton*)this->GetDlgItem(IDC_DO_VENUS);
	m_pEarthCheckBox = (CButton*)this->GetDlgItem(IDC_DO_EARTH);
	m_pMarsCheckBox = (CButton*)this->GetDlgItem(IDC_DO_MARS);
	m_pJupiterCheckBox = (CButton*)this->GetDlgItem(IDC_DO_JUPITER);
	m_pSaturnCheckBox = (CButton*)this->GetDlgItem(IDC_DO_SATURN);
	m_pUranusCheckBox = (CButton*)this->GetDlgItem(IDC_DO_URANUS);
	m_pNeptuneCheckBox = (CButton*)this->GetDlgItem(IDC_DO_NEPTUNE);
	m_pPlutoCheckBox = (CButton*)this->GetDlgItem(IDC_DO_PLUTO);

	if(m_pDoAll->GetCheck() == 1)
	{
		m_pSunCheckBox->SetCheck(1);
		m_pMoonCheckBox->SetCheck(1);
		m_pMercuryCheckBox->SetCheck(1);
		m_pVenusCheckBox->SetCheck(1);
		m_pEarthCheckBox->SetCheck(1);
		m_pMarsCheckBox->SetCheck(1);
		m_pJupiterCheckBox->SetCheck(1);
		m_pSaturnCheckBox->SetCheck(1);
		m_pUranusCheckBox->SetCheck(1);
		m_pNeptuneCheckBox->SetCheck(1);
		m_pPlutoCheckBox->SetCheck(1);
		
	}
	else
	{
		m_pSunCheckBox->SetCheck(0);
		m_pMoonCheckBox->SetCheck(0);
		m_pMercuryCheckBox->SetCheck(0);
		m_pVenusCheckBox->SetCheck(0);
		m_pEarthCheckBox->SetCheck(0);
		m_pMarsCheckBox->SetCheck(0);
		m_pJupiterCheckBox->SetCheck(0);
		m_pSaturnCheckBox->SetCheck(0);
		m_pUranusCheckBox->SetCheck(0);
		m_pNeptuneCheckBox->SetCheck(0);
		m_pPlutoCheckBox->SetCheck(0);
	}
}

//	"Geocentric Equatorial App Equatorial Apparent" button
void CTimeLocation::OnEquatorialApparent() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top;
	
	m_sCalcMethod = "GeocentricEquatorial";
	m_sCalcType = "Spherical";
	UpdateData(true);	//Bring in values from dialog
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
	m_pPlanetSet[4] = 0;
	CTimeLocation::calcEquatorialApparent();
	CTimeLocation::calcHeliocentricSphericalRetrograde();

//	Create and display results box
	m_pModelessRadius = new CRadiusDisplay(this);
	m_pModelessRadius->Create((LPCTSTR) IDD_RADIUS_DISPLAY, NULL);
	left = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("top"), 0);

	m_pModelessRadius->MoveWindow(left, top, 450, 568, true);
	m_pModelessRadius->ShowWindow(SW_SHOW);

//	Output data to dialog
	CTimeLocation::assignEquatorialApparentValues();
	if(m_pPlanetSet[1] == 1)
	{
		m_pModelessRadius->m_sMoonDur = CTimeLocation::CalculateMoonsQuarter();
	}
	m_pModelessRadius->UpdateData(false);
	
}

//	Calculate Equatorial Apparent
void CTimeLocation::calcEquatorialApparent()
{

	CPlanet body;

	CTimeLocation::zeroAllValues();
	int i;

	for(i=0; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1 )
		{
			CTimeLocation::getBody(body, i);
			body.equatorialAppPlanet(m_sTimeEntered.m_dJulianDay, m_pValues[i][0],
									 m_pValues[i][1], m_pValues[i][2]);
		}
	}
}

//	Assign values to variables for Equatorial Apparent
void CTimeLocation::assignEquatorialApparentValues()
{
	CTimeLocation::assignModelessRadiusValues();

	m_pModelessRadius->m_cDegreeStyle.LoadString(m_cOutputStyle);
	m_pModelessRadius->m_cRadiusDisplayTime = m_sTimeEntered.DateLongString();
	m_pModelessRadius->m_sLat = CTimeLocation::DataDisplayLatLon(
		"Latitude", m_cLatitude, m_cLatitude_NS);
	m_pModelessRadius->m_sLon = CTimeLocation::DataDisplayLatLon(
		"Longitude", m_cLongitude, m_cLongitude_WE);
	m_pModelessRadius->m_cDisplayTitle = "Geocentric Equatorial Apparent Coordinates";
	m_pModelessRadius->m_cRadiusDisplayLambda1 = "App Right";
	m_pModelessRadius->m_cRadiusDisplayLambda2 = "Ascension";
	m_pModelessRadius->m_cRadiusDisplayBeta1 = "Apparent";
	m_pModelessRadius->m_cRadiusDisplayBeta2 = "Declination";
	m_pModelessRadius->m_cRadiusDisplayRadius1 = "Distance";
	m_pModelessRadius->m_cRadiusDisplayRadius2 = "From Earth";
	m_pModelessRadius->m_sMercuryDur = m_cMercRetro;
	m_pModelessRadius->m_sVenusDur = m_cVenRetro;
	m_pModelessRadius->m_sMarsDur = m_cMarRetro;
	m_pModelessRadius->m_sJupiterDur = m_cJupRetro;
	m_pModelessRadius->m_sSaturnDur = m_cSatRetro;
	m_pModelessRadius->m_sUranusDur = m_cUranRetro;
	m_pModelessRadius->m_sNeptuneDur = m_cNepRetro;
	m_pModelessRadius->m_sPlutoDur = m_cPlutRetro;

}

//	"Geocentric Ecliptic True Cartesian" button
void CTimeLocation::OnGeocentricCartesian() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top;
	
	m_sCalcMethod = "GeocentricEcliptic";
	m_sCalcType = "Cartesian";
	UpdateData(true);	//Bring in values from dialog
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
	m_pPlanetSet[4] = 0;
	CTimeLocation::calcGeocentricCartesian();
	CTimeLocation::calcHeliocentricSphericalRetrograde();

//	Create and display results box
	m_pModelessRadius = new CRadiusDisplay(this);
	m_pModelessRadius->Create((LPCTSTR) IDD_RADIUS_DISPLAY, NULL);
	left = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("top"), 0);

	m_pModelessRadius->MoveWindow(left, top, 450, 568, true);
	m_pModelessRadius->ShowWindow(SW_SHOW);

//	Output data to dialog
	CTimeLocation::assignGeocentricCartesianValues();
	if(m_pPlanetSet[1] == 1)
	{
		m_pModelessRadius->m_sMoonDur = CTimeLocation::CalculateMoonsQuarter();
	}
	m_pModelessRadius->UpdateData(false);

}

//	Calculate Geocentric Cartesian
void CTimeLocation::calcGeocentricCartesian()
{
	CPlanet body;

	CTimeLocation::zeroAllValues();
	int i;

	for(i=0; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1 )
		{
			CTimeLocation::getBody(body, i);
			body.geocentricCartesianTruePlanet(m_sTimeEntered.m_dJulianDay, m_pValues[i][0],
											 m_pValues[i][1], m_pValues[i][2]);
		}
	}
}

//	Assign values to variables for Geocentric Cartesian
void CTimeLocation::assignGeocentricCartesianValues()
{
	CTimeLocation::assignModelessRadiusValues();
	
	m_pModelessRadius->m_cRadiusDisplayTime = m_sTimeEntered.DateLongString();
	m_pModelessRadius->m_sLat = CTimeLocation::DataDisplayLatLon(
		"Latitude", m_cLatitude, m_cLatitude_NS);
	m_pModelessRadius->m_sLon = CTimeLocation::DataDisplayLatLon(
		"Longitude", m_cLongitude, m_cLongitude_WE);
	m_pModelessRadius->m_cDisplayTitle = "Geocentric Ecliptic Cartesian Coordinates";
	m_pModelessRadius->m_cDegreeStyle = "astronomical units";
	m_pModelessRadius->m_cRadiusDisplayLambda1 = "";
	m_pModelessRadius->m_cRadiusDisplayLambda2 = "X";
	m_pModelessRadius->m_cRadiusDisplayBeta1 = "";
	m_pModelessRadius->m_cRadiusDisplayBeta2 = "Y";
	m_pModelessRadius->m_cRadiusDisplayRadius1 = "";
	m_pModelessRadius->m_cRadiusDisplayRadius2 = "Z";
	m_pModelessRadius->m_sMercuryDur = m_cMercRetro;
	m_pModelessRadius->m_sVenusDur = m_cVenRetro;
	m_pModelessRadius->m_sMarsDur = m_cMarRetro;
	m_pModelessRadius->m_sJupiterDur = m_cJupRetro;
	m_pModelessRadius->m_sSaturnDur = m_cSatRetro;
	m_pModelessRadius->m_sUranusDur = m_cUranRetro;
	m_pModelessRadius->m_sNeptuneDur = m_cNepRetro;
	m_pModelessRadius->m_sPlutoDur = m_cPlutRetro;

}

//	"Geocentric Ecliptic App Spherical" button
void CTimeLocation::OnGeocentricSphericalApp() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top;
	
	m_sCalcMethod = "GeocentricEcliptic";
	m_sCalcType = "Spherical";
	UpdateData(true);	//Bring in values from dialog
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
	m_pPlanetSet[4] = 0;
	CTimeLocation::calcGeocentricSpherical();
	CTimeLocation::calcHeliocentricSphericalRetrograde();

//	Create and display results box
	m_pModelessRadius = new CRadiusDisplay(this);
	m_pModelessRadius->Create((LPCTSTR) IDD_RADIUS_DISPLAY, NULL);
	left = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("top"), 0);

	m_pModelessRadius->MoveWindow(left, top, 450, 568, true);
	m_pModelessRadius->ShowWindow(SW_SHOW);

//	Output data to dialog
	CTimeLocation::assignGeocentricSphericalValues();
	if(m_pPlanetSet[1] == 1)
	{
		m_pModelessRadius->m_sMoonDur = CTimeLocation::CalculateMoonsQuarter();
	}
	m_pModelessRadius->UpdateData(false);

}

//	Calculate Geocentric Spherical
void CTimeLocation::calcGeocentricSpherical()
{
	CPlanet body;

	CTimeLocation::zeroAllValues();
	int i;

	for(i=0; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1 )
		{
			CTimeLocation::getBody(body, i);
			body.geocentricSphericalAppPlanet(m_sTimeEntered.m_dJulianDay, m_pValues[i][0],
											 m_pValues[i][1], m_pValues[i][2]);
		}
	}
}

//	Assign values to variables for Geocentric Spherical
void CTimeLocation::assignGeocentricSphericalValues()
{
	CTimeLocation::assignModelessRadiusValues();

	m_pModelessRadius->m_cDegreeStyle.LoadString(m_cOutputStyle);
	m_pModelessRadius->m_cRadiusDisplayTime = m_sTimeEntered.DateLongString();
	m_pModelessRadius->m_sLat = CTimeLocation::DataDisplayLatLon(
		"Latitude", m_cLatitude, m_cLatitude_NS);
	m_pModelessRadius->m_sLon = CTimeLocation::DataDisplayLatLon(
		"Longitude", m_cLongitude, m_cLongitude_WE);
	m_pModelessRadius->m_cDisplayTitle = "Geocentric Ecliptic Apparent Coordinates";
	m_pModelessRadius->m_cRadiusDisplayLambda1 = "Geocentric";
	m_pModelessRadius->m_cRadiusDisplayLambda2 = "Longitude";
	m_pModelessRadius->m_cRadiusDisplayBeta1 = "Geocentric";
	m_pModelessRadius->m_cRadiusDisplayBeta2 = "Latitude";
	m_pModelessRadius->m_cRadiusDisplayRadius1 = "Distance";
	m_pModelessRadius->m_cRadiusDisplayRadius2 = "From Earth";
	m_pModelessRadius->m_sMercuryDur = m_cMercRetro;
	m_pModelessRadius->m_sVenusDur = m_cVenRetro;
	m_pModelessRadius->m_sMarsDur = m_cMarRetro;
	m_pModelessRadius->m_sJupiterDur = m_cJupRetro;
	m_pModelessRadius->m_sSaturnDur = m_cSatRetro;
	m_pModelessRadius->m_sUranusDur = m_cUranRetro;
	m_pModelessRadius->m_sNeptuneDur = m_cNepRetro;
	m_pModelessRadius->m_sPlutoDur = m_cPlutRetro;

}

//	"Geocentric Ecliptic True Spherical" button
void CTimeLocation::OnGeocentricSphericalTrue() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top;
	
	m_sCalcMethod = "GeocentricEcliptic";
	m_sCalcType = "Spherical";
	UpdateData(true);	//Bring in values from dialog
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
	m_pPlanetSet[4] = 0;
	CTimeLocation::calcGeocentricSphericalTrue();
	CTimeLocation::calcHeliocentricSphericalRetrograde();

//	Create and display results box
	m_pModelessRadius = new CRadiusDisplay(this);
	m_pModelessRadius->Create((LPCTSTR) IDD_RADIUS_DISPLAY, NULL);
	left = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("top"), 0);

	m_pModelessRadius->MoveWindow(left, top, 450, 568, true);
	m_pModelessRadius->ShowWindow(SW_SHOW);

//	Output data to dialog
	CTimeLocation::assignGeocentricSphericalTrueValues();
	if(m_pPlanetSet[1] == 1)
	{
		m_pModelessRadius->m_sMoonDur = CTimeLocation::CalculateMoonsQuarter();
	}
	m_pModelessRadius->UpdateData(false);

}

//	Calculate Geocentric Spherical True
void CTimeLocation::calcGeocentricSphericalTrue()
{
	CPlanet body;

	CTimeLocation::zeroAllValues();
	int i;

	for(i=0; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1 )
		{
			CTimeLocation::getBody(body, i);
			body.geocentricSphericalTruePlanet(m_sTimeEntered.m_dJulianDay, m_pValues[i][0],
											 m_pValues[i][1], m_pValues[i][2]);
		}
	}
}

//	Assign values to variables for Geocentric Spherical True
void CTimeLocation::assignGeocentricSphericalTrueValues()
{
	CTimeLocation::assignModelessRadiusValues();

	m_pModelessRadius->m_cDegreeStyle.LoadString(m_cOutputStyle);
	m_pModelessRadius->m_cRadiusDisplayTime = m_sTimeEntered.DateLongString();
	m_pModelessRadius->m_sLat = CTimeLocation::DataDisplayLatLon(
		"Latitude", m_cLatitude, m_cLatitude_NS);
	m_pModelessRadius->m_sLon = CTimeLocation::DataDisplayLatLon(
		"Longitude", m_cLongitude, m_cLongitude_WE);
	m_pModelessRadius->m_cDisplayTitle = "Geocentric Ecliptic True Coordinates";
	m_pModelessRadius->m_cRadiusDisplayLambda1 = "Geocentric";
	m_pModelessRadius->m_cRadiusDisplayLambda2 = "Longitude";
	m_pModelessRadius->m_cRadiusDisplayBeta1 = "Geocentric";
	m_pModelessRadius->m_cRadiusDisplayBeta2 = "Latitude";
	m_pModelessRadius->m_cRadiusDisplayRadius1 = "Distance";
	m_pModelessRadius->m_cRadiusDisplayRadius2 = "From Earth";
	m_pModelessRadius->m_sMercuryDur = m_cMercRetro;
	m_pModelessRadius->m_sVenusDur = m_cVenRetro;
	m_pModelessRadius->m_sMarsDur = m_cMarRetro;
	m_pModelessRadius->m_sJupiterDur = m_cJupRetro;
	m_pModelessRadius->m_sSaturnDur = m_cSatRetro;
	m_pModelessRadius->m_sUranusDur = m_cUranRetro;
	m_pModelessRadius->m_sNeptuneDur = m_cNepRetro;
	m_pModelessRadius->m_sPlutoDur = m_cPlutRetro;
}

//	Heliocentric Cartesian button
void CTimeLocation::OnHeliocentricCartesian() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top;
	
	m_sCalcMethod = "HeliocentricCartesian";
	m_sCalcType = "Cartesian";
	UpdateData(true);	//Bring in values from dialog
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
	m_pPlanetSet[0] = 0;
	m_pPlanetSet[1] = 0;
	CTimeLocation::calcHeliolcentricCartesian();

//	Create and display results box
	m_pModelessRadius = new CRadiusDisplay(this);
	m_pModelessRadius->Create((LPCTSTR) IDD_RADIUS_DISPLAY, NULL);
	left = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("top"), 0);

	m_pModelessRadius->MoveWindow(left, top, 450, 568, true);
	m_pModelessRadius->ShowWindow(SW_SHOW);

//	Output data to dialog
	CTimeLocation::assignHelioCartesianValues();
	m_pModelessRadius->UpdateData(false);
	
}

//	Calculate Heliocentric Cartesian values
void CTimeLocation::calcHeliolcentricCartesian()
{
	CPlanet body;

	CTimeLocation::zeroAllValues();
	int i;

	for(i=0; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1 )
		{
			CTimeLocation::getBody(body, i);
			body.heliocentricCartesianPlanet(m_sTimeEntered.m_dJulianDay, m_pValues[i][0],
											 m_pValues[i][1], m_pValues[i][2]);
		}
	}
}

//	Assign values to variables for Heliocentric Cartesian
void CTimeLocation::assignHelioCartesianValues()
{
	CTimeLocation::assignModelessRadiusValues();
	
	m_pModelessRadius->m_cRadiusDisplayTime = m_sTimeEntered.DateLongString();
	m_pModelessRadius->m_sLat = CTimeLocation::DataDisplayLatLon(
		"Latitude", m_cLatitude, m_cLatitude_NS);
	m_pModelessRadius->m_sLon = CTimeLocation::DataDisplayLatLon(
		"Longitude", m_cLongitude, m_cLongitude_WE);
	m_pModelessRadius->m_cDisplayTitle = "Heliocentric Cartesian Coordinates";
	m_pModelessRadius->m_cDegreeStyle = "astronomical units";
	m_pModelessRadius->m_cRadiusDisplayLambda1 = "";
	m_pModelessRadius->m_cRadiusDisplayLambda2 = "X";
	m_pModelessRadius->m_cRadiusDisplayBeta1 = "";
	m_pModelessRadius->m_cRadiusDisplayBeta2 = "Y";
	m_pModelessRadius->m_cRadiusDisplayRadius1 = "";
	m_pModelessRadius->m_cRadiusDisplayRadius2 = "Z";
}

//	Now button.  Sets Time Location time and date to today, right now.
void CTimeLocation::OnNow()
{
	convert Convert;
	time_t osBinaryTime;  // C run-time time (defined in <time.h>)
	time( &osBinaryTime ) ;  // Get the current time from the 
		                     // operating system.
	int iNowHour, err;
	int iNowMinute, iNowSecond;
	
	struct tm m_pNow;
	err = localtime_s(&m_pNow, &osBinaryTime);
	if (err) {
		printf("Invalid argument to _localtime64_s.");
		exit(1);
	}
	
	m_iYear = m_pNow.tm_year + 1900;
	m_iMonth = m_pNow.tm_mon + 1;
	m_sMonth = Convert.MonthName(m_iMonth);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MONTH);
	pSpin->SetPos(m_iMonth);
	m_iDate = m_pNow.tm_mday;

	iNowHour = m_pNow.tm_hour;
	if(iNowHour == 0)
	{
		iNowHour = 12;
		m_cAmpm = "a";
	}
	else if(iNowHour >= 12)
	{
		m_cAmpm = "p";
		if(iNowHour > 12)iNowHour -= 12;
	}

	iNowMinute = m_pNow.tm_min;
	iNowSecond = m_pNow.tm_sec;

	m_dHour = iNowHour + iNowMinute / (double)100 + iNowSecond / (double)10000;

	if(m_pNow.tm_isdst > 0)
	{
		m_cDst = "y";
	}
	else
	{
		m_cDst = "n";
	}

	this->UpdateData(false);
}

//	"Rise, Set, Transit" button
void CTimeLocation::OnRiseSetTransit() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top;
	
	m_sCalcMethod = "RiseSetTransit";
	m_sCalcType = "Data";
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
	m_pPlanetSet[4] = 0;
	CTimeLocation::calcRiseSetTransit();

//	Create and display results box
	m_pModelessRTS = new CRiseTransitSet(this);
	m_pModelessRTS->Create((LPCTSTR) IDD_RISE_TRANSIT_SET, NULL);
	left = pApp->GetProfileInt( _T ("RiseTransitSet"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("RiseTransitSet"), _T ("top"), 0);

	m_pModelessRTS->MoveWindow(left, top, 630, 515, true);
	m_pModelessRTS->ShowWindow(SW_SHOW);

//	Output data to dialog
	CTimeLocation::assignRiseSetTransitValues();
	m_pModelessRTS->UpdateData(false);
}

//	Calculate Rise, Set, Transit
void CTimeLocation::calcRiseSetTransit()
{
	CPlanet body;
	convert Convert;

	double dJulianDay, localTimeCorr;
	double temp;
	double riseValue, setValue, extraValue;
	int i;

	CTimeLocation::zeroAllValues();

	dJulianDay = m_sTimeEntered.m_dJulianDay;
	localTimeCorr = -m_sTimeEntered.m_dTimeZone;
	if(m_cDst == "y")localTimeCorr += (double)1;

	for(i=0; i<11; i++)
	{
		m_iSpecialFlag[i] = 0;
		if(m_pPlanetSet[i] == 1 )
		{
			CTimeLocation::getBody(body, i);

			body.riseSetTransitPlanet(dJulianDay,
									  m_sTimeEntered.m_dLatitude,
									  m_sTimeEntered.m_dLongitude,
									  m_pValues[i][0],
									  m_pValues[i][1],
									  m_pValues[i][2],
									  m_pValues[i][3],
									  i,
									  localTimeCorr,
									  m_iSpecialFlag[i]);

//	This section calculates how long each body is up.  m_iSpecialFlag
//	tracks how many values were found for rise/set at high latitude.  If 
//	the value is 2 or 6 it means there is a double value.  If there is not
//	calculation of time up is quite easy
			riseValue = m_pValues[i][0];
			setValue = m_pValues[i][2];
			if(		m_iSpecialFlag[i] == 2
			   ||	m_iSpecialFlag[i] == 6)
			{//	2 means 2 sets, 6 means 2 rises
			}
			else
			{//	Set the second rise/set to a too high value
				m_pValues[i][3] = 30.0;
			}

			if(		m_iSpecialFlag[i] == 2
			   ||	m_iSpecialFlag[i] == 6)
			{//	We have 2 values of rise or set, do the math
				extraValue = m_pValues[i][3];
				if(m_iSpecialFlag[i] == 6)
				{
					temp = setValue - riseValue - extraValue + 24.0;
				}
				else
				{
					temp = setValue - riseValue + extraValue;
				}
			}
			else if(riseValue < 0)
			{//	We do not have 2 values or we are not high lat
				if(setValue < 0)
				{
					if(riseValue < -10)
					{
						temp = 24.0;
					}
					else
					{
						temp = 0;
					}
				}
				else
				{
					temp = setValue;
				}
			}
			else if(setValue < 0)
			{
				temp = 24.0 - riseValue;
			}
			else if(riseValue < setValue)
			{
				temp = setValue - riseValue;
			}
			else
			{
				temp = setValue - riseValue + 24.0;
			}
		
			if(	m_cOutputStyle == IDS_DEGREE || m_cOutputStyle == IDS_RADIAN)
			{
				m_sDurValues[i] = Convert.HMSToString(Convert.degreeToDMS(temp), "h", m_iPrecision);
			}
			else
			{
				m_sDurValues[i] = Convert.DecimalToString(temp, m_iPrecision);
			}
		}
	}
}

//	Assign values to variables for Rise, Set, Transit
void CTimeLocation::assignRiseSetTransitValues()
{
	CTimeLocation::assignModelessRTSValues();

	if(	m_cOutputStyle == IDS_DEGREE || m_cOutputStyle == IDS_RADIAN)
		m_pModelessRTS->m_cTimeStyle = "hours h.mmss";

	if(m_cOutputStyle == IDS_DECIMAL)
		m_pModelessRTS->m_cTimeStyle = "decimal hours";
	
	m_sTimeEntered.calcMonthName();
	m_pModelessRTS->m_cDate = m_sTimeEntered.m_sDay + 
		" " + m_sTimeEntered.m_sMonthName + ", " + m_sTimeEntered.m_sYear;
	m_pModelessRTS->m_cLat = CTimeLocation::DataDisplayLatLon(
		"Latitude", m_cLatitude, m_cLatitude_NS);
	m_pModelessRTS->m_cLon = CTimeLocation::DataDisplayLatLon(
		"Longitude", m_cLongitude, m_cLongitude_WE);

	m_pModelessRTS->m_cSunUp = m_sDurValues[0];
	m_pModelessRTS->m_cMoonUp = m_sDurValues[1];
	m_pModelessRTS->m_cMercuryUp = m_sDurValues[2];
	m_pModelessRTS->m_cVenusUp = m_sDurValues[3];
	m_pModelessRTS->m_cMarsUp = m_sDurValues[5];
	m_pModelessRTS->m_cJupiterUp = m_sDurValues[6];
	m_pModelessRTS->m_cSaturnUp = m_sDurValues[7];
	m_pModelessRTS->m_cUranusUp = m_sDurValues[8];
	m_pModelessRTS->m_cNeptuneUp = m_sDurValues[9];
	m_pModelessRTS->m_cPlutoUp = m_sDurValues[10];
}

//	Astronomical Data button
void CTimeLocation::OnAstronomicalData() 
{
	astrotime Astrotime;
	astrocalc Astrocalc;

	CWinApp* pApp = AfxGetApp();
	int left, top;
	double julDay;
	
	m_sCalcMethod = "AstronomicalData";
	m_sCalcType = "Data";
	UpdateData(true);	//Bring in values from dialog
	CTimeLocation::UpdateDataTL();
	CTimeLocation::ProcessData();	//Make them doubles

	m_pModelessAstro = new CAstronomicalData();
	m_pModelessAstro->Create((LPCTSTR) IDD_ASTRONOMICAL_DATA, NULL);
	left = pApp->GetProfileInt( _T ("AstronomicalData"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("AstronomicalData"), _T ("top"), 0);

	m_pModelessAstro->MoveWindow(left, top, 336, 449, true);
	m_pModelessAstro->ShowWindow(SW_SHOW);

	m_sTimeEntered.calcJulianDay();
	julDay = m_sTimeEntered.m_dJulianDay;

	m_pModelessAstro->m_dJulianDay2 = julDay;
	m_pModelessAstro->m_dJulianDayEphemeris = Astrotime.calcJulianDayEphemeris(julDay);
	m_pModelessAstro->m_dDeltaT = Astrotime.deltaT(julDay);
	m_pModelessAstro->m_dMeanSiderealDeg = Astrocalc.meanSiderealDegree(julDay);
	m_pModelessAstro->m_dAppSiderealDeg = Astrocalc.apparSiderealDegree(julDay);
	m_pModelessAstro->m_dEccentricity = Astrocalc.eccentricityEarthOrbitJulDay(julDay);
	m_pModelessAstro->m_dLongitudePerihelion = Astrocalc.longitudePerihelionEarth(julDay);
	m_pModelessAstro->m_dMeanAnomaly = Astrocalc.meanAnomalyEarth(julDay);
	m_pModelessAstro->m_dMeanObliquityEcliptic = Astrocalc.meanObliquityOfEcliptic(julDay);
	m_pModelessAstro->m_dTrueObliquityEcliptic = Astrocalc.trueObliquityOfEcliptic(julDay);
	m_pModelessAstro->m_cLocalTime = m_sTimeEntered.DateLongString();
	m_pModelessAstro->m_cUT = Astrotime.TimeDisplayUT(m_sTimeEntered.m_dYear,
							  m_sTimeEntered.m_dMonth, m_sTimeEntered.m_dDay,
							  m_sTimeEntered.m_dHour, m_iPrecision);

//	Output data to dialog
	m_pModelessAstro->UpdateData(false);
}

//	"Daylight savings time" button
void CTimeLocation::OnButtonDst() 
{
	int flag = 1;

	if(	m_cDst == "y")
	{
		m_cDst = "n";
		flag = 0;
	}

	if(flag)m_cDst = "y";
	UpdateData(false);
	
}

//	Am Pm button
void CTimeLocation::OnButtonAmpm() 
{
	int flag = 1;

	if(	m_cAmpm == "a")
	{
		m_cAmpm = "p";
		flag = 0;
	}

	if(flag)m_cAmpm = "a";
	UpdateData(false);
}

//	Latitude North/South button
void CTimeLocation::OnButtonNs() 
{
	int flag = 1;

	if(	m_cLatitude_NS == "N" || m_cLatitude_NS == "n")
	{
		m_cLatitude_NS = "S";
		flag = 0;
	}

	if(flag)m_cLatitude_NS = "N";

	UpdateData(false);	
}

//	Longitude West/East button
void CTimeLocation::OnButtonWe() 
{
	int flag = 1;

	if(	m_cLongitude_WE == "W" || m_cLongitude_WE == "w")
	{
		m_cLongitude_WE = "E";
		flag = 0;
	}

	if(flag)m_cLongitude_WE = "W";

	UpdateData(false);
}

//	Operates the Output radio button group
void CTimeLocation::OnOutputGroup() 
{
	CButton* dec;
	CButton* hms;
	CButton* rad;

	dec = (CButton*)this->GetDlgItem(IDC_RADIO_DECIMAL);
	hms = (CButton*)this->GetDlgItem(IDC_RADIO_HMS);
	rad = (CButton*)this->GetDlgItem(IDC_RADIO_RADIAN);

	if(dec->GetCheck() == 1)
	{
		m_cOutputStyle = IDS_DECIMAL;
	}
	else if(hms->GetCheck() == 1)
	{
		m_cOutputStyle = IDS_DEGREE;
	}
	else
	{
		m_cOutputStyle = IDS_RADIAN;
	}
}

//	Finds which planets are being requested and stores them in pPlanetSet[]
void CTimeLocation::WhichPlanets(CTimeLocation* pTLBox, int pPlanetSet[11])
{
	int i;

	for (i=0;i < 11;i++)
	{
		pPlanetSet[i] = 0;
	}

	m_pSunCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_SUN);
	m_pMoonCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_MOON);
	m_pMercuryCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_MERCURY);
	m_pVenusCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_VENUS);
	m_pEarthCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_EARTH);
	m_pMarsCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_MARS);
	m_pJupiterCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_JUPITER);
	m_pSaturnCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_SATURN);
	m_pUranusCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_URANUS);
	m_pNeptuneCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_NEPTUNE);
	m_pPlutoCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_DO_PLUTO);
//	m_pStarsCheckBox = (CButton*)pTLBox->GetDlgItem(IDC_STARS);

	if(m_pSunCheckBox->GetCheck() == 1)pPlanetSet[0] = 1;
	if(m_pMoonCheckBox->GetCheck() == 1)pPlanetSet[1] = 1;
	if(m_pMercuryCheckBox->GetCheck() == 1)pPlanetSet[2] = 1;
	if(m_pVenusCheckBox->GetCheck() == 1)pPlanetSet[3] = 1;
	if(m_pEarthCheckBox->GetCheck() == 1)pPlanetSet[4] = 1;
	if(m_pMarsCheckBox->GetCheck() == 1)pPlanetSet[5] = 1;
	if(m_pJupiterCheckBox->GetCheck() == 1)pPlanetSet[6] = 1;
	if(m_pSaturnCheckBox->GetCheck() == 1)pPlanetSet[7] = 1;
	if(m_pUranusCheckBox->GetCheck() == 1)pPlanetSet[8] = 1;
	if(m_pNeptuneCheckBox->GetCheck() == 1)pPlanetSet[9] = 1;
	if(m_pPlutoCheckBox->GetCheck() == 1)pPlanetSet[10] = 1;
//	if(m_pStarsCheckBox->GetCheck() == 1)m_bStars = true;
}

int CTimeLocation::CountPlanets()
{
	int i, iCount;

	iCount = 0;

	for(i=0; i<11; i++)
	{
		iCount += m_pPlanetSet[i];
	}
	return iCount;
}

//	Zero value holders.  When any of the functions are called to 
//	calculate values, they are stored in these sets.
void CTimeLocation::zeroAllValues()
{
	int i, j;
	for (i=0; i<11; i++)
	{
		for(j=0; j<4; j++)
		{
			m_pValues[i][j] = (double)0;
			m_sDurValues[i].Empty();
		}
	}
}

//	Given an integer, return the proper body
void CTimeLocation::getBody(class CPlanet &body, int p)
{
	switch( p )
	{
	case 0:
		body.sun();
		break;
	case 1:
		body.moon();
		break;
	case 2:
		body.mercury();
		break;
	case 3:
		body.venus();
		break;
	case 4:
		body.earth();
		break;
	case 5:
		body.mars();
		break;
	case 6:
		body.jupiter();
		break;
	case 7:
		body.saturn();
		break;
	case 8:
		body.uranus();
		break;
	case 9:
		body.neptune();
		break;
	case 10:
		body.pluto();
		break;
	}
}

//	Assign values to variables for Azimuth/Altitude table
void CTimeLocation::assignModelessArray()
{
	double dDummy1, dDummy2;

	m_pModelessValues[0][0] = &m_pModeless->m_sSunAzimuth;
	m_pModelessValues[0][1] = &m_pModeless->m_sSunAltitude;
	m_pDataDisplayValues[0][0] = &m_pModeless->m_dSunAzimuth;
	m_pDataDisplayValues[0][1] = &m_pModeless->m_dSunAltitude;
	
	m_pModelessValues[1][0] = &m_pModeless->m_sMoonAzimuth;
	m_pModelessValues[1][1] = &m_pModeless->m_sMoonAltitude;
	m_pDataDisplayValues[1][0] = &m_pModeless->m_dMoonAzimuth;
	m_pDataDisplayValues[1][1] = &m_pModeless->m_dMoonAltitude;
	
	m_pModelessValues[2][0] = &m_pModeless->m_sMercuryAzimuth;
	m_pModelessValues[2][1] = &m_pModeless->m_sMercuryAltitude;
	m_pDataDisplayValues[2][0] = &m_pModeless->m_dMercuryAzimuth;
	m_pDataDisplayValues[2][1] = &m_pModeless->m_dMercuryAltitude;
	
	m_pModelessValues[3][0] = &m_pModeless->m_sVenusAzimuth;
	m_pModelessValues[3][1] = &m_pModeless->m_sVenusAltitude;
	m_pDataDisplayValues[3][0] = &m_pModeless->m_dVenusAzimuth;
	m_pDataDisplayValues[3][1] = &m_pModeless->m_dVenusAltitude;
	
	m_pModelessValues[4][0] = &m_sDummy1;
	m_pModelessValues[4][1] = &m_sDummy2;
	m_pDataDisplayValues[4][0] = &dDummy1;
	m_pDataDisplayValues[4][1] = &dDummy2;

	m_pModelessValues[5][0] = &m_pModeless->m_sMarsAzimuth;
	m_pModelessValues[5][1] = &m_pModeless->m_sMarsAltitude;
	m_pDataDisplayValues[5][0] = &m_pModeless->m_dMarsAzimuth;
	m_pDataDisplayValues[5][1] = &m_pModeless->m_dMarsAltitude;
	
	m_pModelessValues[6][0] = &m_pModeless->m_sJupiterAzimuth;
	m_pModelessValues[6][1] = &m_pModeless->m_sJupiterAltitude;
	m_pDataDisplayValues[6][0] = &m_pModeless->m_dJupiterAzimuth;
	m_pDataDisplayValues[6][1] = &m_pModeless->m_dJupiterAltitude;
	
	m_pModelessValues[7][0] = &m_pModeless->m_sSaturnAzimuth;
	m_pModelessValues[7][1] = &m_pModeless->m_sSaturnAltitude;
	m_pDataDisplayValues[7][0] = &m_pModeless->m_dSaturnAzimuth;
	m_pDataDisplayValues[7][1] = &m_pModeless->m_dSaturnAltitude;
	
	m_pModelessValues[8][0] = &m_pModeless->m_sUranusAzimuth;
	m_pModelessValues[8][1] = &m_pModeless->m_sUranusAltitude;
	m_pDataDisplayValues[8][0] = &m_pModeless->m_dUranusAzimuth;
	m_pDataDisplayValues[8][1] = &m_pModeless->m_dUranusAltitude;
	
	m_pModelessValues[9][0] = &m_pModeless->m_sNeptuneAzimuth;
	m_pModelessValues[9][1] = &m_pModeless->m_sNeptuneAltitude;
	m_pDataDisplayValues[9][0] = &m_pModeless->m_dNeptuneAzimuth;
	m_pDataDisplayValues[9][1] = &m_pModeless->m_dNeptuneAltitude;
	
	m_pModelessValues[10][0] = &m_pModeless->m_sPlutoAzimuth;
	m_pModelessValues[10][1] = &m_pModeless->m_sPlutoAltitude;
	m_pDataDisplayValues[10][0] = &m_pModeless->m_dPlutoAzimuth;
	m_pDataDisplayValues[10][1] = &m_pModeless->m_dPlutoAltitude;
}

//	Assign values to variables for Horoscope table
void CTimeLocation::AssignModelessHorArray()
{
	m_pModelessValues[0][0] = &m_pModelessHor->m_sSunPos;
	m_pModelessValues[0][1] = &m_pModelessHor->m_sSunSign;
	m_pModelessHorInts[0] = &m_pModelessHor->m_iSunHouse;
	
	m_pModelessValues[1][0] = &m_pModelessHor->m_sMoonPos;
	m_pModelessValues[1][1] = &m_pModelessHor->m_sMoonSign;
	m_pModelessHorInts[1] = &m_pModelessHor->m_iMoonHouse;
	
	m_pModelessValues[2][0] = &m_pModelessHor->m_sMercuryPos;
	m_pModelessValues[2][1] = &m_pModelessHor->m_sMercurySign;
	m_pModelessHorInts[2] = &m_pModelessHor->m_iMercuryHouse;
	
	m_pModelessValues[3][0] = &m_pModelessHor->m_sVenusPos;
	m_pModelessValues[3][1] = &m_pModelessHor->m_sVenusSign;
	m_pModelessHorInts[3] = &m_pModelessHor->m_iVenusHouse;
	
	m_pModelessValues[4][0] = &m_pModelessHor->m_sAscNodePos;
	m_pModelessValues[4][1] = &m_pModelessHor->m_sAscNodeSign;
	m_pModelessHorInts[4] = &m_pModelessHor->m_iAscNodeHouse;

	m_pModelessValues[5][0] = &m_pModelessHor->m_sMarsPos;
	m_pModelessValues[5][1] = &m_pModelessHor->m_sMarsSign;
	m_pModelessHorInts[5] = &m_pModelessHor->m_iMarsHouse;
	
	m_pModelessValues[6][0] = &m_pModelessHor->m_sJupiterPos;
	m_pModelessValues[6][1] = &m_pModelessHor->m_sJupiterSign;
	m_pModelessHorInts[6] = &m_pModelessHor->m_iJupiterHouse;
	
	m_pModelessValues[7][0] = &m_pModelessHor->m_sSaturnPos;
	m_pModelessValues[7][1] = &m_pModelessHor->m_sSaturnSign;
	m_pModelessHorInts[7] = &m_pModelessHor->m_iSaturnHouse;
	
	m_pModelessValues[8][0] = &m_pModelessHor->m_sUranusPos;
	m_pModelessValues[8][1] = &m_pModelessHor->m_sUranusSign;
	m_pModelessHorInts[8] = &m_pModelessHor->m_iUranusHouse;
	
	m_pModelessValues[9][0] = &m_pModelessHor->m_sNeptunePos;
	m_pModelessValues[9][1] = &m_pModelessHor->m_sNeptuneSign;
	m_pModelessHorInts[9] = &m_pModelessHor->m_iNeptuneHouse;
	
	m_pModelessValues[10][0] = &m_pModelessHor->m_sPlutoPos;
	m_pModelessValues[10][1] = &m_pModelessHor->m_sPlutoSign;
	m_pModelessHorInts[10] = &m_pModelessHor->m_iPlutoHouse;
}

//	Assign values to variables for Rise, Set, Transit display
void CTimeLocation::assignModelessRTSArray()
{
	CString dummy;

	m_pModelessValues[0][0] = &m_pModelessRTS->m_cSunRise;
	m_pModelessValues[0][1] = &m_pModelessRTS->m_cSunTransit;
	m_pModelessValues[0][2] = &m_pModelessRTS->m_cSunSet;
	m_pModelessValues[0][3] = &m_pModelessRTS->m_cSun2;
	
	m_pModelessValues[1][0] = &m_pModelessRTS->m_cMoonRise;
	m_pModelessValues[1][1] = &m_pModelessRTS->m_cMoonTransit;
	m_pModelessValues[1][2] = &m_pModelessRTS->m_cMoonSet;
	m_pModelessValues[1][3] = &m_pModelessRTS->m_cMoon2;
	
	m_pModelessValues[2][0] = &m_pModelessRTS->m_cMercuryRise;
	m_pModelessValues[2][1] = &m_pModelessRTS->m_cMercuryTransit;
	m_pModelessValues[2][2] = &m_pModelessRTS->m_cMercurySet;
	m_pModelessValues[2][3] = &m_pModelessRTS->m_cMercury2;
	
	m_pModelessValues[3][0] = &m_pModelessRTS->m_cVenusRise;
	m_pModelessValues[3][1] = &m_pModelessRTS->m_cVenusTransit;
	m_pModelessValues[3][2] = &m_pModelessRTS->m_cVenusSet;
	m_pModelessValues[3][3] = &m_pModelessRTS->m_cVenus2;
	
	m_pModelessValues[4][0] = &m_pModelessRTS->m_cEarthRise;
	m_pModelessValues[4][1] = &m_pModelessRTS->m_cEarthTransit;
	m_pModelessValues[4][2] = &m_pModelessRTS->m_cEarthSet;
	m_pModelessValues[4][3] = &m_pModelessRTS->m_cEarth2;

	m_pModelessValues[5][0] = &m_pModelessRTS->m_cMarsRise;
	m_pModelessValues[5][1] = &m_pModelessRTS->m_cMarsTransit;
	m_pModelessValues[5][2] = &m_pModelessRTS->m_cMarsSet;
	m_pModelessValues[5][3] = &m_pModelessRTS->m_cMars2;
	
	m_pModelessValues[6][0] = &m_pModelessRTS->m_cJupiterRise;
	m_pModelessValues[6][1] = &m_pModelessRTS->m_cJupiterTransit;
	m_pModelessValues[6][2] = &m_pModelessRTS->m_cJupiterSet;
	m_pModelessValues[6][3] = &m_pModelessRTS->m_cJupiter2;
	
	m_pModelessValues[7][0] = &m_pModelessRTS->m_cSaturnRise;
	m_pModelessValues[7][1] = &m_pModelessRTS->m_cSaturnTransit;
	m_pModelessValues[7][2] = &m_pModelessRTS->m_cSaturnSet;
	m_pModelessValues[7][3] = &m_pModelessRTS->m_cSaturn2;
	
	m_pModelessValues[8][0] = &m_pModelessRTS->m_cUranusRise;
	m_pModelessValues[8][1] = &m_pModelessRTS->m_cUranusTransit;
	m_pModelessValues[8][2] = &m_pModelessRTS->m_cUranusSet;
	m_pModelessValues[8][3] = &m_pModelessRTS->m_cUranus2;
	
	m_pModelessValues[9][0] = &m_pModelessRTS->m_cNeptuneRise;
	m_pModelessValues[9][1] = &m_pModelessRTS->m_cNeptuneTransit;
	m_pModelessValues[9][2] = &m_pModelessRTS->m_cNeptuneSet;
	m_pModelessValues[9][3] = &m_pModelessRTS->m_cNeptune2;
	
	m_pModelessValues[10][0] = &m_pModelessRTS->m_cPlutoRise;
	m_pModelessValues[10][1] = &m_pModelessRTS->m_cPlutoTransit;
	m_pModelessValues[10][2] = &m_pModelessRTS->m_cPlutoSet;
	m_pModelessValues[10][3] = &m_pModelessRTS->m_cPluto2;
}

//	Assign values to variables for 
void CTimeLocation::assignModelessRTSValues()
{
	convert Convert;
	int i, j;
	CString temp;

	CTimeLocation::assignModelessRTSArray();
	for (i=0; i<11; i++)
	{
		for(j=0; j<3; j++)
		{
			if(m_pPlanetSet[i] == 0)
			{
				*m_pModelessValues[i][j] = "";
			}
			else
			{
				if(m_cOutputStyle == IDS_RADIAN)
				{
					if(m_pValues[i][j] < 0)
					{
						m_pModelessValues[i][j]->LoadString(IDS_NEVER_UP);// "Never up";
						if(m_pValues[i][j] < -10)
						{
							m_pModelessValues[i][j]->LoadString(IDS_ALWAYS_UP);// = "Always up";
						}
						if(m_pValues[i][j] < -100)
						{
							m_pModelessValues[i][j]->LoadString(IDS_NEXT_DAY);// = "Next Day";
						}
					}
					else
					{
						*m_pModelessValues[i][j] = Convert.HMSToString(Convert.hourToHMS(m_pValues[i][j]), m_sDisTypeHMS, m_iPrecision);
					}
				}
				else if(m_cOutputStyle == IDS_DECIMAL)
				{
					if(m_pValues[i][j] < 0)
					{
						m_pModelessValues[i][j]->LoadString(IDS_NEVER_UP);// "Never up";
						if(m_pValues[i][j] < -10)
						{
							m_pModelessValues[i][j]->LoadString(IDS_ALWAYS_UP);// = "Always up";
						}
						if(m_pValues[i][j] < -100)
						{
							m_pModelessValues[i][j]->LoadString(IDS_NEXT_DAY);// = "Next Day";
						}
					}
					else
					{
					*m_pModelessValues[i][j] = Convert.DecimalToString(m_pValues[i][j], m_iPrecision);
					}
				}
				else if (m_cOutputStyle == IDS_DEGREE)
				{
					if(m_pValues[i][j] < 0)
					{
						m_pModelessValues[i][j]->LoadString(IDS_NEVER_UP);// "Never up";
						if(m_pValues[i][j] < -10)
						{
							m_pModelessValues[i][j]->LoadString(IDS_ALWAYS_UP);// = "Always up";
						}
						if(m_pValues[i][j] < -100)
						{
							m_pModelessValues[i][j]->LoadString(IDS_NEXT_DAY);// = "Next Day";
						}
					}
					else
					{
						*m_pModelessValues[i][j] = Convert.HMSToString(Convert.hourToHMS(m_pValues[i][j]), m_sDisTypeHMS, m_iPrecision);
					}
				}
			}
		}
	}
	for (i=0; i<11; i++)
	{
		j=3;
		if(m_cOutputStyle == IDS_RADIAN)
		{
			if(m_pValues[i][j] > 25.0)
			{
				*m_pModelessValues[i][j] = "";
			}
			else
			{
				if(m_iSpecialFlag[i] == 2)
				{
					*m_pModelessValues[i][j] = "Set: ";
					*m_pModelessValues[i][j] += Convert.HMSToString(Convert.hourToHMS(m_pValues[i][j]), m_sDisTypeHMS, m_iPrecision);
				}
				else if(m_iSpecialFlag[i] == 6)
				{
					*m_pModelessValues[i][j] = "Rise: ";
					*m_pModelessValues[i][j] += Convert.HMSToString(Convert.hourToHMS(m_pValues[i][j]), m_sDisTypeHMS, m_iPrecision);
				}
			}
		}
		else if(m_cOutputStyle == IDS_DECIMAL)
		{
			if(m_pValues[i][j] > 25.0)
			{
				*m_pModelessValues[i][j] = "";
			}
			else
			{
				if(m_iSpecialFlag[i] == 2)
				{
					*m_pModelessValues[i][j] = "Set: ";
					*m_pModelessValues[i][j] += Convert.DecimalToString(m_pValues[i][j], m_iPrecision);
				}
				else if(m_iSpecialFlag[i] == 6)
				{
					*m_pModelessValues[i][j] = "Rise: ";
					*m_pModelessValues[i][j] += Convert.DecimalToString(m_pValues[i][j], m_iPrecision);
				}
			}
		}
		else if (m_cOutputStyle == IDS_DEGREE)
		{
			if(m_pValues[i][j] > 25.0)
			{
				*m_pModelessValues[i][j] = "";
			}
			else
			{
				if(m_iSpecialFlag[i] == 2)
				{
					*m_pModelessValues[i][j] = "Set: ";
					*m_pModelessValues[i][j] += Convert.HMSToString(Convert.hourToHMS(m_pValues[i][j]), m_sDisTypeHMS, m_iPrecision);
				}
				else if(m_iSpecialFlag[i] == 6)
				{
					*m_pModelessValues[i][j] = "Rise: ";
					*m_pModelessValues[i][j] += Convert.HMSToString(Convert.hourToHMS(m_pValues[i][j]), m_sDisTypeHMS, m_iPrecision);
				}
			}
		}
	}
}

//	Assign values to variables for 
void CTimeLocation::assignModelessRadiusArray()
{

	m_pModelessValues[0][0] = &m_pModelessRadius->m_sSunLambda;
	m_pModelessValues[0][1] = &m_pModelessRadius->m_sSunBeta;
	m_pModelessValues[0][2] = &m_pModelessRadius->m_sSunRadius;
	m_pRadiusDisplayValues[0][0] = &m_pModelessRadius->m_dSunLambda;
	m_pRadiusDisplayValues[0][1] = &m_pModelessRadius->m_dSunBeta;
	m_pRadiusDisplayValues[0][2] = &m_pModelessRadius->m_dSunRadius;
	
	m_pModelessValues[1][0] = &m_pModelessRadius->m_sMoonLambda;
	m_pModelessValues[1][1] = &m_pModelessRadius->m_sMoonBeta;
	m_pModelessValues[1][2] = &m_pModelessRadius->m_sMoonRadius;
	m_pRadiusDisplayValues[1][0] = &m_pModelessRadius->m_dMoonLambda;
	m_pRadiusDisplayValues[1][1] = &m_pModelessRadius->m_dMoonBeta;
	m_pRadiusDisplayValues[1][2] = &m_pModelessRadius->m_dMoonRadius;
	
	m_pModelessValues[2][0] = &m_pModelessRadius->m_sMercuryLambda;
	m_pModelessValues[2][1] = &m_pModelessRadius->m_sMercuryBeta;
	m_pModelessValues[2][2] = &m_pModelessRadius->m_sMercuryRadius;
	m_pRadiusDisplayValues[2][0] = &m_pModelessRadius->m_dMercuryLambda;
	m_pRadiusDisplayValues[2][1] = &m_pModelessRadius->m_dMercuryBeta;
	m_pRadiusDisplayValues[2][2] = &m_pModelessRadius->m_dMercuryRadius;
	
	m_pModelessValues[3][0] = &m_pModelessRadius->m_sVenusLambda;
	m_pModelessValues[3][1] = &m_pModelessRadius->m_sVenusBeta;
	m_pModelessValues[3][2] = &m_pModelessRadius->m_sVenusRadius;
	m_pRadiusDisplayValues[3][0] = &m_pModelessRadius->m_dVenusLambda;
	m_pRadiusDisplayValues[3][1] = &m_pModelessRadius->m_dVenusBeta;
	m_pRadiusDisplayValues[3][2] = &m_pModelessRadius->m_dVenusRadius;
	
	m_pModelessValues[4][0] = &m_pModelessRadius->m_sEarthLambda;
	m_pModelessValues[4][1] = &m_pModelessRadius->m_sEarthBeta;
	m_pModelessValues[4][2] = &m_pModelessRadius->m_sEarthRadius;
	m_pRadiusDisplayValues[4][0] = &m_pModelessRadius->m_dEarthLambda;
	m_pRadiusDisplayValues[4][1] = &m_pModelessRadius->m_dEarthBeta;
	m_pRadiusDisplayValues[4][2] = &m_pModelessRadius->m_dEarthRadius;

	m_pModelessValues[5][0] = &m_pModelessRadius->m_sMarsLambda;
	m_pModelessValues[5][1] = &m_pModelessRadius->m_sMarsBeta;
	m_pModelessValues[5][2] = &m_pModelessRadius->m_sMarsRadius;
	m_pRadiusDisplayValues[5][0] = &m_pModelessRadius->m_dMarsLambda;
	m_pRadiusDisplayValues[5][1] = &m_pModelessRadius->m_dMarsBeta;
	m_pRadiusDisplayValues[5][2] = &m_pModelessRadius->m_dMarsRadius;
	
	m_pModelessValues[6][0] = &m_pModelessRadius->m_sJupiterLambda;
	m_pModelessValues[6][1] = &m_pModelessRadius->m_sJupiterBeta;
	m_pModelessValues[6][2] = &m_pModelessRadius->m_sJupiterRadius;
	m_pRadiusDisplayValues[6][0] = &m_pModelessRadius->m_dJupiterLambda;
	m_pRadiusDisplayValues[6][1] = &m_pModelessRadius->m_dJupiterBeta;
	m_pRadiusDisplayValues[6][2] = &m_pModelessRadius->m_dJupiterRadius;
	
	m_pModelessValues[7][0] = &m_pModelessRadius->m_sSaturnLambda;
	m_pModelessValues[7][1] = &m_pModelessRadius->m_sSaturnBeta;
	m_pModelessValues[7][2] = &m_pModelessRadius->m_sSaturnRadius;
	m_pRadiusDisplayValues[7][0] = &m_pModelessRadius->m_dSaturnLambda;
	m_pRadiusDisplayValues[7][1] = &m_pModelessRadius->m_dSaturnBeta;
	m_pRadiusDisplayValues[7][2] = &m_pModelessRadius->m_dSaturnRadius;
	
	m_pModelessValues[8][0] = &m_pModelessRadius->m_sUranusLambda;
	m_pModelessValues[8][1] = &m_pModelessRadius->m_sUranusBeta;
	m_pModelessValues[8][2] = &m_pModelessRadius->m_sUranusRadius;
	m_pRadiusDisplayValues[8][0] = &m_pModelessRadius->m_dUranusLambda;
	m_pRadiusDisplayValues[8][1] = &m_pModelessRadius->m_dUranusBeta;
	m_pRadiusDisplayValues[8][2] = &m_pModelessRadius->m_dUranusRadius;
	
	m_pModelessValues[9][0] = &m_pModelessRadius->m_sNeptuneLambda;
	m_pModelessValues[9][1] = &m_pModelessRadius->m_sNeptuneBeta;
	m_pModelessValues[9][2] = &m_pModelessRadius->m_sNeptuneRadius;
	m_pRadiusDisplayValues[9][0] = &m_pModelessRadius->m_dNeptuneLambda;
	m_pRadiusDisplayValues[9][1] = &m_pModelessRadius->m_dNeptuneBeta;
	m_pRadiusDisplayValues[9][2] = &m_pModelessRadius->m_dNeptuneRadius;
	
	m_pModelessValues[10][0] = &m_pModelessRadius->m_sPlutoLambda;
	m_pModelessValues[10][1] = &m_pModelessRadius->m_sPlutoBeta;
	m_pModelessValues[10][2] = &m_pModelessRadius->m_sPlutoRadius;
	m_pRadiusDisplayValues[10][0] = &m_pModelessRadius->m_dPlutoLambda;
	m_pRadiusDisplayValues[10][1] = &m_pModelessRadius->m_dPlutoBeta;
	m_pRadiusDisplayValues[10][2] = &m_pModelessRadius->m_dPlutoRadius;

}

//	Assign values to variables for 
void CTimeLocation::assignModelessRadiusValues()
{
	convert Convert;
	int i, j;
	double temp;

	CTimeLocation::assignModelessRadiusArray();
	for (i=0; i<11; i++)
	{
		for(j=0; j<3; j++)
		{
			if(m_pPlanetSet[i] == 0)
			{
				*m_pRadiusDisplayValues[i][j] = 0.0;
				*m_pModelessValues[i][j] = "";
			}
			else
			{
				if(m_cOutputStyle == IDS_RADIAN)
				{
					if(m_sCalcType == "Data")
					{
						*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
						*m_pModelessValues[i][j] = Convert.HMSToString(Convert.hourToHMS(m_pValues[i][j]), m_sDisTypeHMS, m_iPrecision);
					}
					else
					{
						*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
						*m_pModelessValues[i][j] = Convert.DecimalToString(m_pValues[i][j], m_iPrecision);
					}
				}
				else if(m_cOutputStyle == IDS_DECIMAL)
				{
					if (m_sCalcType == "Data")
					{
						*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
						*m_pModelessValues[i][j] = Convert.DecimalToString(m_pValues[i][j], m_iPrecision);
					}
					else if(m_sCalcType == "Spherical" &&
							(j == 0 || j == 1))
					{
						if(	m_sCalcMethod == "GeocentricEquatorial" &&
							j == 0 )
						{
							*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
							*m_pModelessValues[i][j] = Convert.DecimalToString(Convert.radianToHour(m_pValues[i][j]), m_iPrecision);
						}
						else
						{
							*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
							*m_pModelessValues[i][j] = Convert.DecimalToString(Convert.radianToDegree(m_pValues[i][j]), m_iPrecision);
						}
					}
					else
					{
						*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
						*m_pModelessValues[i][j] = Convert.DecimalToString(m_pValues[i][j], m_iPrecision);
					}
				}
				else if (m_cOutputStyle == IDS_DEGREE)
				{
					if (m_sCalcType == "Data")
					{
						*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
						*m_pModelessValues[i][j] = Convert.HMSToString(Convert.hourToHMS(m_pValues[i][j]), m_sDisTypeHMS, m_iPrecision);
					}
					else if (m_sCalcType == "Almanac" &&
							(j == 0 || j == 1))
					{
						*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
						temp = Convert.degreeToDMS(Convert.radianToDegree(m_pValues[i][j]));
						*m_pModelessValues[i][j] = Convert.HMSToString(temp, m_sDisTypeDMS, m_iPrecision);
					}
					else if (m_sCalcType == "Spherical" &&
							(j == 0 || j == 1))
					{
						if(m_sCalcMethod == "GeocentricEquatorial" &&
							j == 0 )
						{
							*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
							temp = Convert.hourToHMS(Convert.radianToHour(m_pValues[i][j]));
							*m_pModelessValues[i][j] = Convert.HMSToString(temp, m_sDisTypeHMS, m_iPrecision);
						}
						else
						{
							*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
							temp = Convert.degreeToDMS(Convert.radianToDegree(m_pValues[i][j]));
							*m_pModelessValues[i][j] = Convert.HMSToString(temp, m_sDisTypeDMS, m_iPrecision);
						}
					}
					else
					{
						*m_pRadiusDisplayValues[i][j] = m_pValues[i][j];
						*m_pModelessValues[i][j] = Convert.DecimalToString(m_pValues[i][j], m_iPrecision);
					}
				}
			}
		}
	}
}

//	Get values from Time Location 
void CTimeLocation::UpdateDataTL()
{
	convert Convert;
	int err;
	char temp[6];

	UpdateData(true);

	m_sTimeEntered.m_dYear = (double)m_iYear;
	m_sTimeEntered.m_dMonth = (double)m_iMonth;
	m_sTimeEntered.m_dDay = (double)m_iDate;
	m_sTimeEntered.m_dHour = m_dHour;
	if(m_sCalcMethod == "RiseSetTransit")
	{
		m_sTimeEntered.m_sAmPm = "a";
		m_sTimeEntered.m_dHour = 12;
	}
	else
	{
		m_sTimeEntered.m_sAmPm = m_cAmpm;
	}
	m_sTimeEntered.m_sDst = m_cDst;
	m_sTimeEntered.m_dTimeZone = m_dTimeZone;

	m_sTimeEntered.m_sLatitude = m_sLatitude;
	m_sTimeEntered.m_sLongitude = m_sLongitude;

	m_sTimeEntered.ProcessLatLon();
//	have this function return an error message if lat
//	or lon is out of range.  return program to timelocation dialog
//	without doing anything

	m_sTimeEntered.m_sHourLongString.Empty();
	m_sTimeEntered.m_sHourLongString = Convert.HMSToString(m_dHour, 'h', m_iPrecision);

//    _itoa( m_iYear, temp, 10 );
	err = _itoa_s(m_iYear, temp, 6, 10);
 	m_sTimeEntered.m_sYear = (CString)temp;

//    _itoa( m_iMonth, temp, 10 );
	err = _itoa_s(m_iMonth, temp, 6, 10);
	m_sTimeEntered.m_sMonth = (CString)temp;
	
//	_itoa( m_iDate, temp, 10 );
	err = _itoa_s(m_iDate, temp, 6, 10);
	m_sTimeEntered.m_sDay = (CString)temp;

	m_cLatitude = Convert.HMSToString(Convert.degreeToDMS(m_sTimeEntered.m_dLatitude), "d", 4);
	m_cLongitude = Convert.HMSToString(Convert.degreeToDMS(m_sTimeEntered.m_dLongitude), "d", 4);
}

//	"GHA and Dec" button
void CTimeLocation::OnGhaDec() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top;
	
	m_sCalcMethod = "GhaDec";
	m_sCalcType = "Almanac";
	UpdateData(true);	//Bring in values from dialog
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
	m_pPlanetSet[4] = 0;
	CTimeLocation::calcEquatorialApparent();
	CTimeLocation::calcGHADec();

//	Create and display results box
	m_pModelessRadius = new CRadiusDisplay(this);
	m_pModelessRadius->Create((LPCTSTR) IDD_RADIUS_DISPLAY, NULL);
	left = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("RadiusDisplay"), _T ("top"), 0);

	m_pModelessRadius->MoveWindow(left, top, 450, 568, true);
	m_pModelessRadius->ShowWindow(SW_SHOW);

//	Output data to dialog
	CTimeLocation::assignGHADecValues(m_sTimeEntered.m_dJulianDay);
	m_pModelessRadius->UpdateData(false);	
}

//	Calculate GHA and Dec
void CTimeLocation::calcGHADec()
{
	convert Convert;
	astrocalc Astrocalc;
	CPlanet body;

	double m_2Pi, GrenSidRadian;

	m_2Pi = (double)2 * Convert.Pi();
	GrenSidRadian = Astrocalc.apparSiderealRadian(m_sTimeEntered.m_dJulianDay);

	int i;
	for(i=0; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1 )
		{
			m_pValues[i][0] = GrenSidRadian - m_pValues[i][0];
			m_pValues[i][0] = Convert.radianPositiveValue(m_pValues[i][0]);
			m_pValues[i][2] = 0.0;
		}
	}
}

//	Assign values to variables for GHA and Dec
void CTimeLocation::assignGHADecValues(double julDay)
{
	convert Convert;
	astrocalc Astrocalc;

	double d_sidTime;
	CString s_sidTime;

	CTimeLocation::assignModelessRadiusValues();

	m_pModelessRadius->m_cDegreeStyle.LoadString(m_cOutputStyle);
	m_pModelessRadius->m_cRadiusDisplayTime = m_sTimeEntered.DateLongString();
	m_pModelessRadius->m_cDisplayTitle = "Greenwich Hour Angle and Declination";
	m_pModelessRadius->m_cRadiusDisplayLambda1 = "";
	m_pModelessRadius->m_cRadiusDisplayLambda2 = "GHA";
	m_pModelessRadius->m_cRadiusDisplayBeta1 = "";
	m_pModelessRadius->m_cRadiusDisplayBeta2 = "Declination";
	m_pModelessRadius->m_cRadiusDisplayRadius1 = "";
	m_pModelessRadius->m_cRadiusDisplayRadius2 = "";

	d_sidTime = Convert.degreeToDMS(Astrocalc.apparSiderealDegree(julDay));
	s_sidTime = Convert.HMSToString(d_sidTime, "d", m_iPrecision);
	m_pModelessRadius->m_sLat = "GHA of Aries = " + s_sidTime;
}

//	Stores certain values for the next time Time Location is opened
void CTimeLocation::KeepValues() 
{
	CWinApp* pApp = AfxGetApp();
	CButton *all, *output0, *output1, *output2;
	CButton *sun, *moon, *mercury, *venus, *earth;
	CButton *mars, *jup, *sat, *uranus, *nep, *pluto;
	CComboBox* pLocation;
	CString sLocation;
	int iCL;
	
	pLocation = (CComboBox*)this->GetDlgItem(IDC_LOCATION);
	iCL = pLocation->GetCurSel();
	if(iCL == -1)
	{
		pApp->WriteProfileString( _T ("TimeLocation"), _T ("location"), _T (""));
	}
	else
	{
		pLocation->GetLBText(iCL, sLocation);
		pApp->WriteProfileString( _T ("TimeLocation"), _T ("location"), sLocation);
	}

	UpdateData(true);

	all =		(CButton*)this->GetDlgItem(IDC_DO_ALL);
	output0 =	(CButton*)this->GetDlgItem(IDC_RADIO_DECIMAL);
	output1 =	(CButton*)this->GetDlgItem(IDC_RADIO_HMS);
	output2 =	(CButton*)this->GetDlgItem(IDC_RADIO_RADIAN);
	sun =		(CButton*)this->GetDlgItem(IDC_DO_SUN);
	moon =		(CButton*)this->GetDlgItem(IDC_DO_MOON);
	mercury =	(CButton*)this->GetDlgItem(IDC_DO_MERCURY);
	venus =		(CButton*)this->GetDlgItem(IDC_DO_VENUS);
	earth =		(CButton*)this->GetDlgItem(IDC_DO_EARTH);
	mars =		(CButton*)this->GetDlgItem(IDC_DO_MARS);
	jup =		(CButton*)this->GetDlgItem(IDC_DO_JUPITER);
	sat =		(CButton*)this->GetDlgItem(IDC_DO_SATURN);
	uranus =	(CButton*)this->GetDlgItem(IDC_DO_URANUS);
	nep =		(CButton*)this->GetDlgItem(IDC_DO_NEPTUNE);
	pluto =		(CButton*)this->GetDlgItem(IDC_DO_PLUTO);
	
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("all"), all->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("output0"), output0->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("output1"), output1->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("output2"), output2->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("sun"), sun->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("moon"), moon->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("mercury"), mercury->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("venus"), venus->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("earth"), earth->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("mars"), mars->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("jupiter"), jup->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("saturn"), sat->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("uranus"), uranus->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("neptune"), nep->GetCheck());
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("pluto"), pluto->GetCheck());
}

void CTimeLocation::OnDestroy() 
{
	CTimeLocation::WriteValues();
	CDialog::OnDestroy();
}

void CTimeLocation::OnClose() 
{
	CTimeLocation::WriteValues();
	CDialog::OnClose();
}

//	Stores location of dialog box and 'Keep' values
void CTimeLocation::WriteValues()
{
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("top"), winRect.top);
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("left"), winRect.left);
	CTimeLocation::KeepValues();
}

BOOL CTimeLocation::OnInitDialog() 
{
	CWinApp* pApp = AfxGetApp();

	CString sLat, sLon, sTimeZone;

	CDialog::OnInitDialog();
	
	m_iPrecision = pApp->GetProfileInt( _T ("TimeLocation"), _T ("precision"), 5);
	UpdateData(false);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MONTH);
	pSpin->SetRange(1, 12);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_YEAR);
	pSpin->SetRange(-4712, 4712);
	
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DATE);
	pSpin->SetRange(1, 31);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_PRECISION);
	pSpin->SetRange(0, 15);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_TIME_ZONE);
	pSpin->SetRange(-12, 12);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//	Angular Separation button
void CTimeLocation::OnAngularSeparation() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top;
	CButton *geo, *helio, *planets1, *stars1;
	CListBox* box1;
	CListBox* box2;

	m_sCalcMethod = "AngularSeparation";
	m_sCalcType = "Data";
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();

//	Create and display results box
	m_pModelessAngSep = new CAngularSeparation(this);
	m_pModelessAngSep->Create((LPCTSTR) IDD_ANGULAR_SEPARATION, NULL);

	box1 = (CListBox*)m_pModelessAngSep->GetDlgItem(IDC_BODY1);
	box2 = (CListBox*)m_pModelessAngSep->GetDlgItem(IDC_BODY2);
	box1->SetCurSel(pApp->GetProfileInt( _T ("AngularSeparation"), _T ("box1"), 0));
	box2->SetCurSel(pApp->GetProfileInt( _T ("AngularSeparation"), _T ("box2"), 0));

	geo = (CButton*)m_pModelessAngSep->GetDlgItem(IDC_GEOCENTRIC);
	helio = (CButton*)m_pModelessAngSep->GetDlgItem(IDC_HELIOCENTRIC);
	planets1 = (CButton*)m_pModelessAngSep->GetDlgItem(IDC_PLANETS1);
	stars1 = (CButton*)m_pModelessAngSep->GetDlgItem(IDC_STARS1);
	geo->SetCheck(pApp->GetProfileInt( _T ("AngularSeparation"), _T ("geo"), 1));
	helio->SetCheck(pApp->GetProfileInt( _T ("AngularSeparation"), _T ("helio"), 0));
	planets1->SetCheck(pApp->GetProfileInt( _T ("AngularSeparation"), _T ("planets1"), 1));
	stars1->SetCheck(pApp->GetProfileInt( _T ("AngularSeparation"), _T ("stars1"), 0));

	if(planets1->GetCheck())
	{
		m_pModelessAngSep->FillBodyBox(1);
	}
	else
	{
		m_pModelessAngSep->FillBodyBox(2);
	}

	left = pApp->GetProfileInt( _T ("AngularSeparation"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("AngularSeparation"), _T ("top"), 0);

	m_pModelessAngSep->MoveWindow(left, top, 520, 375, true);
	m_pModelessAngSep->ShowWindow(SW_SHOW);
}

//	"Hor" button
void CTimeLocation::OnHor() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top, i;
	
	m_sCalcMethod = "Hor";
	m_sCalcType = "Spherical";
	m_pModelessHor = new CHor(this);
	UpdateData(true);	//Bring in values from dialog
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
//	Always do all planets
	for (i=0;i < 11;i++)
	{
		m_pPlanetSet[i] = 1;
	}
//	Don't do Earth yet
	m_pPlanetSet[4] = 0;

//	Calculate Hour Angle and Declination of all bodies and 
//	Ascending Node of Moon (North Node)
	CTimeLocation::calcHor(&m_pModelessHor->m_pChart);

//	Now m_pPlanetSet[4] = North Node
	m_pPlanetSet[4] = 1;

//	Calculate and load array with retrograde info
	CTimeLocation::calcHeliocentricSphericalRetrograde();
	CTimeLocation::LoadRetroArray();

//	Find house cusps
	m_pModelessHor->m_pChart.CalculateHouses(&m_sTimeEntered);

//	Find the sign of each house cusp
	m_pModelessHor->m_pChart.PlaceHousesInSigns();

//	Find the house and sign of each body
	m_pModelessHor->m_pChart.PlaceBodiesInHouses();
	m_pModelessHor->m_pChart.PlaceBodiesInSigns();
	m_pModelessHor->m_pChart.MakeBodyStrings();

	m_pModelessHor->m_pChart.CalculateTriplicities();
	m_pModelessHor->m_pChart.CalculateAspects();

//	Create and display results box
	m_pModelessHor->Create((LPCTSTR) IDD_HOR, NULL);

	left = pApp->GetProfileInt( _T ("Hor"), _T ("left"), 200);
	top = pApp->GetProfileInt( _T ("Hor"), _T ("top"), 0);

	m_pModelessHor->MoveWindow(left, top, 420, 600, true);
	m_pModelessHor->ShowWindow(SW_SHOW);

//	Output data to dialog
	CTimeLocation::assignHorValues(&m_pModelessHor->m_pChart);
	m_pModelessHor->UpdateData(false);
}

//	This is required for Horoscope because it does not follow normal
//	pattern. Since Sun, Moon and Earth cannot be 'R', set to ""
void CTimeLocation::LoadRetroArray()
{
	m_pModelessHor->m_pChart.m_sRetrograde[0] = "";
	m_pModelessHor->m_pChart.m_sRetrograde[1] = "";
	m_pModelessHor->m_pChart.m_sRetrograde[2] = m_cMercRetro;
	m_pModelessHor->m_pChart.m_sRetrograde[3] = m_cVenRetro;
	m_pModelessHor->m_pChart.m_sRetrograde[4] = "";
	m_pModelessHor->m_pChart.m_sRetrograde[5] = m_cMarRetro;
	m_pModelessHor->m_pChart.m_sRetrograde[6] = m_cJupRetro;
	m_pModelessHor->m_pChart.m_sRetrograde[7] = m_cSatRetro;
	m_pModelessHor->m_pChart.m_sRetrograde[8] = m_cUranRetro;
	m_pModelessHor->m_pChart.m_sRetrograde[9] = m_cNepRetro;
	m_pModelessHor->m_pChart.m_sRetrograde[10] = m_cPlutRetro;
}

//	Calculate Horoscope
void CTimeLocation::calcHor(CChart *pChart)
{
	astrocalc smith;
	convert Convert;

	int i;
	double NNode;

	CTimeLocation::zeroAllValues();
//	Planet positions are geocentric spherical
	CTimeLocation::calcGeocentricSpherical();
//	Ascending node of Moon calculated seperately
//	Ascending Node latitude is 0.0 by definition
	NNode =	smith.MoonAscNode(m_sTimeEntered.m_dJulianDay);
	m_pValues[4][0] = Convert.radianReduce(NNode);
	m_pValues[4][1] = 0;

//	m_dBody[11] = Hour Angle of body
//	m_dBodyDec[11] = Declination of body
	for(i=0; i<11; i++)
	{
		pChart->m_dBody[i] = m_pValues[i][0];
		pChart->m_dBodyDec[i] = m_pValues[i][1];
	}
}

//	Assign values to variables for Horoscope
void CTimeLocation::assignHorValues(CChart *pChart)
{
	convert Convert;

	int i;
	double temp;

	CTimeLocation::AssignModelessHorArray();

	for (i=0; i<11; i++)
	{
		if(m_pPlanetSet[i] == 1)
		{
			*m_pModelessValues[i][1] = pChart->m_sBodySignLocation[i];
			*m_pModelessHorInts[i] = pChart->m_iBodyHouse[i];
			if(m_cOutputStyle == IDS_RADIAN)
			{
				*m_pModelessValues[i][0] = Convert.DecimalToString(m_pValues[i][0], m_iPrecision);
			}
			else if(m_cOutputStyle == IDS_DECIMAL)
			{
				*m_pModelessValues[i][0] = Convert.DecimalToString(Convert.radianToDegree(m_pValues[i][0]), m_iPrecision);
			}
			else if(m_cOutputStyle == IDS_DEGREE)
			{
				temp = Convert.degreeToDMS(Convert.radianToDegree(m_pValues[i][0]));
				*m_pModelessValues[i][0] = Convert.HMSToString(temp, m_sDisTypeDMS, m_iPrecision);
			}
		}
		else
		{
			*m_pModelessValues[i][0] = "";
			*m_pModelessValues[i][1] = "";
		}
	}
	m_pModelessHor->m_sBirthTime = m_sTimeEntered.DateLongString();
	m_pModelessHor->m_sMercRet = m_cMercRetro;
	m_pModelessHor->m_sVenRet = m_cVenRetro;
	m_pModelessHor->m_sMarRet = m_cMarRetro;
	m_pModelessHor->m_sJupRet = m_cJupRetro;
	m_pModelessHor->m_sSatRet = m_cSatRetro;
	m_pModelessHor->m_sUranRet = m_cUranRetro;
	m_pModelessHor->m_sNepRet = m_cNepRetro;
	m_pModelessHor->m_sPlutRet = m_cPlutRetro;
	m_pModelessHor->m_sBirthPlace = m_sLocation;
}

//	Spin control for month button
void CTimeLocation::OnDeltaposSpinMonth(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	*pResult = 0;
}

void CTimeLocation::OnKillfocusMonth() 
{
	UpdateData(false);
}

void CTimeLocation::OnKillfocusLatitude() 
{
	UpdateData(true);	
}

void CTimeLocation::OnKillfocusLongitude() 
{
	UpdateData(true);	
}

void CTimeLocation::OnKillfocusAmpm() 
{
	UpdateData(true);	
}

void CTimeLocation::OnKillfocusDate() 
{
	UpdateData(true);	
}

void CTimeLocation::OnKillfocusDaylightSt() 
{
	UpdateData(true);	
}

void CTimeLocation::OnKillfocusHour() 
{
	UpdateData(true);	
}

void CTimeLocation::OnKillfocusLatitudeNs() 
{
	UpdateData(true);	
}

void CTimeLocation::OnKillfocusLongitudeWe() 
{
	UpdateData(true);	
}

void CTimeLocation::OnKillfocusTimeZone() 
{
	UpdateData(true);	
}

void CTimeLocation::OnKillfocusYear() 
{
	UpdateData(true);	
}

//	Converts spin number to string
void CTimeLocation::OnChangeMonth() 
{
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MONTH);
	m_iMonth = pSpin->GetPos();
	switch ( m_iMonth )
	{
	case 1:
		m_sMonth.LoadString(IDS_JANUARY);// = "January";
		break;
	case 2:
		m_sMonth.LoadString(IDS_FEBRUARY);// = "February";
		break;
	case 3:
		m_sMonth.LoadString(IDS_MARCH);// = "March";
		break;
	case 4:
		m_sMonth.LoadString(IDS_APRIL);// = "April";
		break;
	case 5:
		m_sMonth.LoadString(IDS_MAY);// = "May";
		break;
	case 6:
		m_sMonth.LoadString(IDS_JUNE);// = "June";
		break;
	case 7:
		m_sMonth.LoadString(IDS_JULY);// = "July";
		break;
	case 8:
		m_sMonth.LoadString(IDS_AUGUST);// = "August";
		break;
	case 9:
		m_sMonth.LoadString(IDS_SEPTEMBER);// = "September";
		break;
	case 10:
		m_sMonth.LoadString(IDS_OCTOBER);// = "October";
		break;
	case 11:
		m_sMonth.LoadString(IDS_NOVEMBER);// = "November";
		break;
	case 12:
		m_sMonth.LoadString(IDS_DECEMBER);// = "December";
		break;
	}		// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CTimeLocation::OnAddPlace() 
{
	CComboBox* pLocation;
	CString pPlace;
	CString sLat, sLon, sTZ;
	char temp[9];

	CTimeLocation::UpdateDataTL();
	pLocation = (CComboBox*)this->GetDlgItem(IDC_LOCATION);

	std::wofstream outfile;
	outfile.open("places.tap", std::ios::app );

	_gcvt_s(temp, 9, m_dTimeZone, 4);
	sTZ = (CString)temp;

	outfile<< (LPCTSTR)m_sLocation<<std::endl;
	outfile<< (LPCTSTR)m_sLatitude<<std::endl;
	outfile<< (LPCTSTR)m_cLatitude_NS<<std::endl;
	outfile<< (LPCTSTR)m_sLongitude<<std::endl;
	outfile<< (LPCTSTR)m_cLongitude_WE<<std::endl;
	outfile<< (LPCTSTR)sTZ<<std::endl;

	outfile.close();

	pLocation->AddString(m_sLocation);
}

void CTimeLocation::OnSelchangeLocation() 
{
	CComboBox* pLocation;
	CString sPlace;
	CString sLat, sLon;
	char buf1[40];
	char temp[25];
	int done;

	UpdateData(true);
	
	pLocation = (CComboBox*)this->GetDlgItem(IDC_LOCATION);
	pLocation->GetLBText(pLocation->GetCurSel(), sPlace);

	std::ifstream infile;
	infile.open("places.tap", std::ios::in);

	done = 0;
	while(done == 0)
	{
		infile.getline(buf1, 40, '\n');
		if(sPlace == buf1)
		{
			infile>>temp;
			m_sLatitude = (CString)temp;
			infile>>temp;
			m_cLatitude_NS = (CString)temp;
			infile>>temp;
			m_sLongitude = (CString)temp;
			infile>>temp;
			m_cLongitude_WE = (CString)temp;
			m_sLocation = sPlace;
			infile>>m_dTimeZone;

			UpdateData(false);
			done = 1;
			break;
		}
	}
	infile.close();
}

void CTimeLocation::OnPlaceDelete() 
{
	CComboBox* pLocation;
	CString sPlace, sPlaceToRemove;
	CString sLat, sLon, sTZ;
	char buf1[40];
	int iEOF, iCurrentSelection;

	pLocation = (CComboBox*)this->GetDlgItem(IDC_LOCATION);
	iCurrentSelection = pLocation->GetCurSel();

	if(iCurrentSelection == -1)
	{
		pLocation->Clear();
	}
	else
	{
		pLocation->GetLBText(iCurrentSelection, sPlaceToRemove);
		pLocation->DeleteString(iCurrentSelection);
	}

	std::ifstream infile;
	infile.open("places.tap", std::ios::in );

	std::wofstream outfile;
	outfile.open("temp.tap", std::ios::trunc );

	iEOF = 0;
 	infile.getline(buf1, 40, '\n');
	while(iEOF == 0 )
	{
		sPlace = buf1;
		if(sPlace == sPlaceToRemove)
		{
		 	infile.getline(buf1, 40, '\n');
		 	infile.getline(buf1, 40, '\n');
		 	infile.getline(buf1, 40, '\n');
		 	infile.getline(buf1, 40, '\n');
		 	infile.getline(buf1, 40, '\n');
		 	infile.getline(buf1, 40, '\n');
			iEOF = infile.eof();
		}
		else
		{
			outfile<< (LPCTSTR)sPlace<<std::endl;
		 	infile.getline(buf1, 40, '\n');
			outfile<<buf1<<std::endl;
		 	infile.getline(buf1, 40, '\n');
			outfile<<buf1<<std::endl;
		 	infile.getline(buf1, 40, '\n');
			outfile<<buf1<<std::endl;
		 	infile.getline(buf1, 40, '\n');
			outfile<<buf1<<std::endl;
		 	infile.getline(buf1, 40, '\n');
			outfile<<buf1<<std::endl;
		 	infile.getline(buf1, 40, '\n');
			iEOF = infile.eof();
		}
	}

	infile.close();
	outfile.close();

	infile.open("temp.tap", std::ios::in );
	outfile.open("places.tap", std::ios::trunc );

	iEOF = 0;
 	infile.getline(buf1, 40, '\n');
	while(iEOF == 0 )
	{
		sPlace = buf1;
		if(sPlace == "")
		{
			infile.getline(buf1, 40, '\n');
			iEOF = infile.eof();
		}
		else
		{
			outfile<< (LPCTSTR)sPlace<<std::endl;
	 		infile.getline(buf1, 40, '\n');
			outfile<<buf1<<std::endl;
			infile.getline(buf1, 40, '\n');
			outfile<<buf1<<std::endl;
			infile.getline(buf1, 40, '\n');
			outfile<<buf1<<std::endl;
			infile.getline(buf1, 40, '\n');
			outfile<<buf1<<std::endl;
			infile.getline(buf1, 40, '\n');
			outfile<<buf1<<std::endl;
			infile.getline(buf1, 40, '\n');
			iEOF = infile.eof();
		}
	}
	infile.close();
	outfile.close();

	if( remove( "temp.tap" ) == -1 )
		printf( "Could not delete 'temp.tap'" );
	else
		printf( "Deleted 'temp.tap'\n" );
}

void CTimeLocation::OnMagneticVariation() 
{
	CWinApp* pApp = AfxGetApp();
	int left, top, iFail, err;
	
	iFail = 0;
	m_sCalcMethod = "Magnetic";
	m_sCalcType = "Data";
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_iPrecision = 2;

	iFail = CTimeLocation::calcMagneticVariation();
	if(1 == iFail) // igrf not found
	{
		CError pErr;
		pErr.ShowError("You must have file 'igrf' in same folder as program");
	}
	else if(2 == iFail) // incorrect year
	{
		// LS 31 Jan 2019
		// buf size needs to be at least one larger than int length to allow for null end.
		char buf1[5];
		CError pErr;

		CString ff = "Only good from ";
		err = _itoa_s(static_cast<int>(m_dMagneticVariation), buf1, 5, 10);
		ff += buf1;
		ff += " - December 31, ";
		err = _itoa_s(static_cast<int>(m_dMagneticDip), buf1, 5, 10);
		ff += buf1;
		pErr.ShowError(ff);
	}
	else if(3 == iFail) // corrupt file
	{
		char buf1[5];
		CError pErr;

		CString ff = "Corrupt record in 'igrf' on line ";
		err = _itoa_s(static_cast<int>(m_dMagneticVariation), buf1, 5, 10);
		ff += buf1;
		pErr.ShowError(ff);
	}
	else if(4 == iFail) // too many models in file
	{
		CError pErr;

		pErr.ShowError("Too many models in file");
	}
	else
	{

	//	Create and display results box
		m_pModelessVar = new CVariationBox(this);
		m_pModelessVar->Create((LPCTSTR) IDD_VARIATION_BOX, NULL);

		left = pApp->GetProfileInt( _T ("VariationBox"), _T ("left"), 200);
		top = pApp->GetProfileInt( _T ("VariationBox"), _T ("top"), 0);

		m_pModelessVar->MoveWindow(left, top, 725, 285, true);
		m_pModelessVar->ShowWindow(SW_SHOW);

	//	Output data to dialog
		CTimeLocation::assignMagneticVariationValues();
		m_pModelessVar->UpdateData(false);
	}
}

int CTimeLocation::calcMagneticVariation()
{
	convert Convert;
	Cvariation pVar;
	double decLat, decLon;
	int iFail;

	decLat = Convert.radianToDegree(m_sTimeEntered.m_dLatitude);
	decLon = -Convert.radianToDegree(m_sTimeEntered.m_dLongitude);
	iFail = pVar.geomag((int)m_sTimeEntered.m_dYear,
						(int)m_sTimeEntered.m_dMonth,
						(int)m_sTimeEntered.m_dDay,
						decLat,
						decLon,
						&m_dMagneticVariation,
						&m_dMagneticDip,
						&m_dMagneticHorizontal,
						&m_dMagneticNorth,
						&m_dMagneticEast,
						&m_dMagneticVertical,
						&m_dMagneticTotal);
	return iFail;
}

void CTimeLocation::assignMagneticVariationValues()
{
	convert Convert;
	CString sVariation;
	CString sDip;
	CString sHorizontal;
	CString sNorth;
	CString sEast;
	CString sVertical;
	CString sTotal;
	double temp;
	CString sTemp;
	
	if(m_cOutputStyle == IDS_RADIAN)
	{
		sVariation	= Convert.DecimalToString(m_dMagneticVariation,		m_iPrecision);
		sDip		= Convert.DecimalToString(m_dMagneticDip,			m_iPrecision);
		m_pModelessVar->m_sDegreeStyle = "radians";
	}
	else if(m_cOutputStyle == IDS_DECIMAL)
	{
		sVariation	= Convert.DecimalToString(Convert.radianToDegree(m_dMagneticVariation),		m_iPrecision);
		sDip		= Convert.DecimalToString(Convert.radianToDegree(m_dMagneticDip),			m_iPrecision);
		m_pModelessVar->m_sDegreeStyle = "decimal degrees";
	}
	else if (m_cOutputStyle == IDS_DEGREE)
	{
		temp = Convert.degreeToDMS(Convert.radianToDegree(m_dMagneticVariation));
		sVariation = Convert.HMSToString(temp, m_sDisTypeDMS, m_iPrecision);

		temp = Convert.degreeToDMS(Convert.radianToDegree(m_dMagneticDip));
		sDip = Convert.HMSToString(temp, m_sDisTypeDMS, m_iPrecision);

		m_pModelessVar->m_sDegreeStyle = "";
	}
	sHorizontal = Convert.DecimalToString(m_dMagneticHorizontal, 0);
	sNorth = Convert.DecimalToString(m_dMagneticNorth, 0);
	sEast = Convert.DecimalToString(m_dMagneticEast, 0);
	sVertical = Convert.DecimalToString(m_dMagneticVertical, 0);
	sTotal = Convert.DecimalToString(m_dMagneticTotal, 0);

	m_pModelessVar->m_sTime = m_sTimeEntered.DateShortString();
	m_pModelessVar->m_sLatitude = CTimeLocation::DataDisplayLatLon(
		"Latitude", m_cLatitude, m_cLatitude_NS);
	m_pModelessVar->m_sLongitude = CTimeLocation::DataDisplayLatLon(
		"Longitude", m_cLongitude, m_cLongitude_WE);
	m_pModelessVar->m_sVariation = sVariation;
	m_pModelessVar->m_sDip = sDip;
	m_pModelessVar->m_sMagneticHorizontal = sHorizontal;
	m_pModelessVar->m_sMagneticNorth = sNorth;
	m_pModelessVar->m_sMagneticEast = sEast;
	m_pModelessVar->m_sMagneticVertical = sVertical;
	m_pModelessVar->m_sMagneticTotal = sTotal;
	m_pModelessVar->m_sLocation = m_sLocation;
}

void CTimeLocation::OnMoonPhaseBtn() 
{
	CWinApp* pApp = AfxGetApp();
	CMoonDialog *pDlg;
	
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles

	pDlg = new CMoonDialog(this);
	pDlg->Create((LPCTSTR) IDD_MOON_PHASES, NULL);

	pDlg->ShowWindow(SW_SHOW);
	pDlg->StartUp();
}

void CTimeLocation::OnCancel() 
{
	DestroyWindow();	
}

void CTimeLocation::PostNcDestroy() 
{
	delete this;	
	CDialog::PostNcDestroy();
}

BOOL CTimeLocation::PreTranslateMessage(MSG* pMsg) 
{
	UINT uMess;

	uMess = pMsg->message;

	switch(uMess)
	{
	case WM_CHAR:
		// first validate character, then see if field makes sense

		CValidate tom;
		int wParam;
		UINT t;
		CString cClassName;

		CWnd* mif = this->GetFocus();

		t = mif->GetDlgCtrlID();
		wParam = pMsg->wParam;

		// combobox uses edit ctrl for editing.  Below finds out if this is happening
		CWnd * pPar = mif->GetParent();
		cClassName.ReleaseBuffer(::RealGetWindowClass(pPar->m_hWnd, cClassName.GetBuffer(128), 128));
		if (cClassName.CollateNoCase(_T("combobox")) == 0)
		{
			t = ::GetDlgCtrlID(*pPar);
		}
		if(wParam != VK_BACK)
		{
			switch(t)
			{
			case IDC_YEAR:
				{
					if(!tom.validateChar(IDS_EDIT_BOX_INT, wParam))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int lo, hi, gLength;
					CString g;

					CEdit* mag = (CEdit*)GetDlgItem(IDC_YEAR);
					mag->GetSel(lo, hi);
					mag->GetWindowText(g);
					gLength = g.GetLength();

					// we have the whole field, so replace with this character (wParam)
					// which means do nothing here since handled above, but do not go to
					// validateField() unless is number
					if(0 == lo && gLength == hi)
					{
						if(wParam == 0x002d)  // allow for negative years
							break;
					}
	
					//This is needed because CEdit does not update until after PreTranslate()
					CString newField = g.Left(lo);
					newField += wchar_t(wParam);
					newField += g.Right(gLength - hi);

					// Field is an integer
					if(!tom.validateField(IDS_EDIT_BOX_INT, newField))
					{
						pMsg->wParam = 0x0;
						break;
					}

					// Field is correct for this box 
					int val = _ttoi(newField);
					if(!tom.validateYear(val) )
					{
						pMsg->wParam = 0x0;
						break;
					}
	
					break;
				}
			case IDC_MONTH:
				{
					if(!tom.validateChar(IDS_EDIT_BOX_INT, wParam))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int lo, hi, gLength;
					CString g;

					CEdit* mag = (CEdit*)GetDlgItem(IDC_MONTH);
					mag->GetSel(lo, hi);
					mag->GetWindowText(g);
					gLength = g.GetLength();

					// we have the whole field, so replace with this character (wParam)
					// which means do nothing here since handled above, but do not go to
					// validateField() unless is number
					if(0 == lo && gLength == hi)
					{
						if(wParam == 0x002d)  // allow for negative years
						{
							pMsg->wParam = 0x0; // negative numbers not allowed
							break;
						}
					}

					//This is needed because CEdit does not update until after PreTranslate()
					CString newField = g.Left(lo);
					newField += wchar_t(wParam);
					newField += g.Right(gLength - hi);

					// Field is an integer
					if(!tom.validateField(IDS_EDIT_BOX_INT, newField))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int val = _ttoi(newField);
					if(!tom.validateMonth(val) )
					{
						pMsg->wParam = 0x0;
						break;
					}
	
					break;
				}
			case IDC_DATE:
				{
					if(!tom.validateChar(IDS_EDIT_BOX_INT, wParam))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int lo, hi, gLength;
					CString g;

					CEdit* mag = (CEdit*)GetDlgItem(IDC_DATE);
					mag->GetSel(lo, hi);
					mag->GetWindowText(g);
					gLength = g.GetLength();

					// we have the whole field, so replace with this character (wParam)
					// which means do nothing here since handled above, but do not go to
					// validateField() unless is number
					if(0 == lo && gLength == hi)
					{
						if(wParam == 0x002d)  // allow for negative years
						{
							pMsg->wParam = 0x0; // negative numbers not allowed
							break;
						}
					}

					//This is needed because CEdit does not update until after PreTranslate()
					CString newField = g.Left(lo);
					newField += wchar_t(wParam);
					newField += g.Right(gLength - hi);

					// Field is an integer
					if(!tom.validateField(IDS_EDIT_BOX_INT, newField))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int val = _ttoi(newField);
					if(!tom.validateDate(val) )
					{
						pMsg->wParam = 0x0;
						break;
					}
	
					break;
				}
			case IDC_HOUR:
				{
					if(!tom.validateChar(IDS_EDIT_BOX_DOUBLE, wParam))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int lo, hi, gLength;
					CString g;

					CEdit* mag = (CEdit*)GetDlgItem(IDC_HOUR);
					mag->GetSel(lo, hi);
					mag->GetWindowText(g);
					gLength = g.GetLength();

					// we have the whole field, so replace with this character (wParam)
					// which means do nothing here since handled above, but do not go to
					// validateField() unless is number
					if(0 == lo && gLength == hi)
					{
						if(wParam == 0x002d)  // allow for negative years
						{
							pMsg->wParam = 0x0; // negative numbers not allowed
							break;
						}
					}

					//This is needed because CEdit does not update until after PreTranslate()
					CString newField = g.Left(lo);
					newField += wchar_t(wParam);
					newField += g.Right(gLength - hi);

					// Field is an double
					if(!tom.validateField(IDS_EDIT_BOX_DOUBLE, newField))
					{
						pMsg->wParam = 0x0;
						break;
					}

//					double val = atof(newField);
					double val = _tstof(newField);
					if(!tom.validateHour(static_cast<int>(val)) )
					{
						pMsg->wParam = 0x0;
						break;
					}
	
					break;
				}
			case IDC_LATITUDE:
			case IDC_LONGITUDE:
				{
					if(!tom.validateChar(IDS_EDIT_BOX_LATLON, wParam))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int lo, hi, gLength;
					CString g;
					CEdit* mag = (CEdit*)GetDlgItem(IDC_LATITUDE);

					if(IDC_LONGITUDE == t)
					{
						mag = (CEdit*)GetDlgItem(IDC_LONGITUDE);
					}

					mag->GetSel(lo, hi);
					mag->GetWindowText(g);
					gLength = g.GetLength();

					// we have the whole field, so replace with this character (wParam)
					// which means do nothing here since handled above, but do not go to
					// validateField() unless is number
					if(0 == lo && gLength == hi)
					{
						if(wParam == 0x002d)  // allow for negative years
						{
							pMsg->wParam = 0x0; // negative numbers not allowed
							break;
						}
					}

					//This is needed because CEdit does not update until after PreTranslate()
					CString newField = g.Left(lo);
					newField += wchar_t(wParam);
					newField += g.Right(gLength - hi);

					if(!tom.validateField(IDS_EDIT_BOX_LATLON, newField))
					{
						pMsg->wParam = 0x0;
						break;
					}

					switch(t)
					{
					case IDC_LATITUDE:
						{
							if(!tom.validateLatLon(newField, IDS_LATITUDE) )
							{
								pMsg->wParam = 0x0;
								break;
							}
							break;
						}
					case IDC_LONGITUDE:
						{
							if(!tom.validateLatLon(newField, IDS_LONGITUDE) )
							{
								pMsg->wParam = 0x0;
								break;
							}
							break;
						}
					break;
					}
				}
			}
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


//void CTimeLocation::OnCbnSetfocusLocation()
//{
//	int y = 5;
//	// TODO: Add your control notification handler code here
//}


//void CTimeLocation::OnCbnEditchangeLocation()
//{
//	int y = 5;
//	// TODO: Add your control notification handler code here
//}


//void CTimeLocation::OnCbnSetfocusLocation()
//{
//	int y = 5;
//	// TODO: Add your control notification handler code here
//}


void CTimeLocation::OnBnClickedStarsPrint()
{
	class CMainFrame* pCMainFrame;
	class CChildFrame* pChildFrame;
	class CPlanetsView* pCView;

	pCMainFrame = (CMainFrame*)this->GetOwner();

	//	Make new document
	CPlanetsApp* pApp = (CPlanetsApp*)AfxGetApp();
	pApp->OnNewFile();
	pChildFrame = (CChildFrame*)pCMainFrame->MDIGetActive();
	pCView = (CPlanetsView*)pChildFrame->GetActiveView();

	// Set values for printing
	pCView->m_iHorCir.x = 425;
	pCView->m_iHorCir.y = -550;
	pCView->m_iHorCirRadius = 375;

		// This starts a CStar
	pCView->StarsSetUp(this);

	int iNumPlanets;
	CString dateString;
	CArray<int, int> iConnys;

	m_sCalcMethod = "GeocentricHorizontal";
	m_sCalcType = "Spherical";
	CTimeLocation::UpdateDataTL();
	CTimeLocation::OnOutputGroup();
	CTimeLocation::ProcessData();	//Make them doubles
	m_sTimeEntered.calcJulianDay();
	CTimeLocation::WhichPlanets(this, m_pPlanetSet);
	//	Don't do Earth
	m_pPlanetSet[4] = 0;
	iNumPlanets = CTimeLocation::CountPlanets();

	if (iNumPlanets > 0)
	{
		CTimeLocation::calcAzimuthAltitude();
	}

	CTimeLocation::WhichConstellations(&iConnys);
	dateString = m_sTimeEntered.DateLongString();

	pCView->m_pCStar->doStars(iNumPlanets, m_sTimeEntered.m_dJulianDay,
		m_sTimeEntered.m_dLatitude, m_sTimeEntered.m_dLongitude,
		0, dateString, &iConnys);

	pCView->OnFilePrintView();
	pChildFrame->OnClose();
}
