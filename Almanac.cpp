// Almanac.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Almanac.h"
#include "astrotime.h"
#include "astrocalc.h"
#include "convert.h"
#include "AngularSeparation.h"
#include "variation.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlmanac dialog


CAlmanac::CAlmanac(CPlanetsDoc* bob)
//CAlmanac::CAlmanac(CWnd* pParent /*=NULL*/)
//	: CDialog(CAlmanac::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlmanac)
	m_iNoRuns = 0;
	m_sProgress = _T("");
	m_iPrecision = 3;
	m_iDayIn = 0;
	m_iDayInc = 0;
	m_iDayOut = 0;
	m_iHourIn = 0;
	m_iHourInc = 0;
	m_iHourOut = 0;
	m_iMinuteInc = 0;
	m_iMonthIn = 0;
	m_iMonthInc = 0;
	m_iMonthOut = 0;
	m_iSecondInc = 0;
	m_iYearIn = 0;
	m_iYearInc = 0;
	m_iYearOut = 0;
	m_cLatEndNS = _T("");
	m_cLatStartNS = _T("");
	m_cLonEndEW = _T("");
	m_cLonStartEW = _T("");
	m_dTimeZone = 0.0;
	m_iLatRuns = 0;
	m_iLonRuns = 0;
	m_iWhichCalc = -1;
	m_sLatEnd = _T("");
	m_sLatInc = _T("");
	m_sLatStart = _T("");
	m_sLonEnd = _T("");
	m_sLonInc = _T("");
	m_sLonStart = _T("");
	//}}AFX_DATA_INIT

}

CAlmanac::CAlmanac(CWnd* pParent /*=NULL*/)
	: CDialog(CAlmanac::IDD, pParent)
{
}

void CAlmanac::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlmanac)
	DDX_Text(pDX, IDC_NO_RUNS, m_iNoRuns);
	DDX_Text(pDX, IDC_PROGRESS, m_sProgress);
	DDX_Text(pDX, IDC_PRECISION, m_iPrecision);
	DDV_MinMaxInt(pDX, m_iPrecision, 0, 6);
	DDX_Text(pDX, IDC_DAY_IN, m_iDayIn);
	DDX_Text(pDX, IDC_DAY_INC, m_iDayInc);
	DDX_Text(pDX, IDC_DAY_OUT, m_iDayOut);
	DDX_Text(pDX, IDC_HOUR_IN, m_iHourIn);
	DDX_Text(pDX, IDC_HOUR_INC, m_iHourInc);
	DDX_Text(pDX, IDC_HOUR_OUT, m_iHourOut);
	DDX_Text(pDX, IDC_MINUTE_INC, m_iMinuteInc);
	DDX_Text(pDX, IDC_MONTH_IN, m_iMonthIn);
	DDX_Text(pDX, IDC_MONTH_INC, m_iMonthInc);
	DDX_Text(pDX, IDC_MONTH_OUT, m_iMonthOut);
	DDX_Text(pDX, IDC_SECOND_INC, m_iSecondInc);
	DDX_Text(pDX, IDC_YEAR_IN, m_iYearIn);
	DDX_Text(pDX, IDC_YEAR_INC, m_iYearInc);
	DDX_Text(pDX, IDC_YEAR_OUT, m_iYearOut);
	DDX_Text(pDX, IDC_LAT_END_NS, m_cLatEndNS);
	DDX_Text(pDX, IDC_LAT_START_NS, m_cLatStartNS);
	DDX_Text(pDX, IDC_LON_END_EW, m_cLonEndEW);
	DDX_Text(pDX, IDC_LON_START_EW, m_cLonStartEW);
	DDX_Text(pDX, IDC_ALM_TIME_ZONE, m_dTimeZone);
	DDX_Text(pDX, IDC_LAT_RUNS, m_iLatRuns);
	DDX_Text(pDX, IDC_LON_RUNS, m_iLonRuns);
	DDX_LBIndex(pDX, IDC_ALMANAC_LIST, m_iWhichCalc);
	DDX_Text(pDX, IDC_LAT_END, m_sLatEnd);
	DDX_Text(pDX, IDC_LAT_INC, m_sLatInc);
	DDX_Text(pDX, IDC_LAT_START, m_sLatStart);
	DDX_Text(pDX, IDC_LON_END, m_sLonEnd);
	DDX_Text(pDX, IDC_LON_INC, m_sLonInc);
	DDX_Text(pDX, IDC_LON_START, m_sLonStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlmanac, CDialog)
	//{{AFX_MSG_MAP(CAlmanac)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ALM_OUTPUT, OnAlmOutput)
	ON_LBN_SELCHANGE(IDC_ALMANAC_LIST, OnSelchangeAlmanacList)
	ON_BN_CLICKED(IDC_ALL, OnDoAll)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_ALMANAC, OnAlmanac)
	ON_BN_CLICKED(IDC_ANG_SEP_GROUP, OnAngSepGroup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlmanac message handlers

void CAlmanac::OnOK() 
{
	CWinApp* pApp = AfxGetApp();

	CString sFileName;

//	Deal with file to write data
	sFileName = pApp->GetProfileString( _T ("Almanac"), _T("saveFile"), _T("almanac"));
	CFileDialog fileBox(false, _T ("txt"), sFileName,OFN_OVERWRITEPROMPT,
						_T ("Text Files (*.txt)|*.txt||") );

	if((fileBox.DoModal()) == 1)
	{//	save
		m_sFileName = fileBox.GetPathName();
		pApp->WriteProfileString( _T ("Almanac"), _T("saveFile"), m_sFileName);	
	}
	else//cancelled
	{
		return;
	}

	CAlmanac::UpdateDataTL();
	this->m_sProgress = "Working";
	UpdateData(false);
	CAlmanac::ProcessData();
	CAlmanac::OnAlmOutput();
	CAlmanac::OnAngSepGroup();
	CAlmanac::WhichPlanets(this, m_iValueSet);
	if(m_iCalc == 10)//Magnetic Variation
	{
		m_iPrecision = 2;
	}
	CAlmanac::CalculateValues();
	this->m_sProgress = "Done";
	UpdateData(false);
}

void CAlmanac::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CAlmanac::ProcessData()
{
	convert Convert;

	m_sTimeIn.convertToDoubleGMT(m_iPrecision);

	if (m_cLatStartNS.GetLength() != 0)
	{
		if(		m_cLatStartNS[0] == 's'
		   ||	m_cLatStartNS[0] == 'S')m_sTimeIn.m_dLatitude *= (double)-1;
	}
	m_sTimeIn.m_dLatitude = Convert.degreeToRadian(m_sTimeIn.m_dLatitude);
	
	if (m_cLonStartEW.GetLength() != 0)
	{
		if(		m_cLonStartEW[0] == 'e'
		   ||	m_cLonStartEW[0] == 'E')m_sTimeIn.m_dLongitude *= (double)-1;
	}
	m_sTimeIn.m_dLongitude = Convert.degreeToRadian(m_sTimeIn.m_dLongitude);

	m_sTimeOut.convertToDoubleGMT(m_iPrecision);

	if (m_cLatEndNS.GetLength() != 0)
	{
		if(		m_cLatEndNS[0] == 's'
		   ||	m_cLatEndNS[0] == 'S')m_sTimeOut.m_dLatitude *= (double)-1;
	}
	m_sTimeOut.m_dLatitude = Convert.degreeToRadian(m_sTimeOut.m_dLatitude);
	
	if (m_cLonEndEW.GetLength() != 0)
	{
		if(		m_cLonEndEW[0] == 'e'
		   ||	m_cLonEndEW[0] == 'E')m_sTimeOut.m_dLongitude *= (double)-1;
	}
	m_sTimeOut.m_dLongitude = Convert.degreeToRadian(m_sTimeOut.m_dLongitude);

	m_sTimeInc.m_dLatitude = Convert.degreeToRadian(m_sTimeInc.m_dLatitude);
	m_sTimeInc.m_dLongitude = Convert.degreeToRadian(m_sTimeInc.m_dLongitude);

	m_sTimeInc.FractionOfJulianDay();
	m_sTimeIn.calcJulianDay();
	m_sTimeOut.calcJulianDay();
}

void CAlmanac::UpdateDataTL()
{
	m_pWhichCalc = (CListBox*)this->GetDlgItem(IDC_ALMANAC_LIST);
	m_iCalc = m_pWhichCalc->GetCurSel();

	UpdateData(true);
	m_sTimeIn.m_dYear	 =	(double)m_iYearIn;
	m_sTimeIn.m_dMonth	 =	(double)m_iMonthIn;
	m_sTimeIn.m_dDay	 =	(double)m_iDayIn;
	m_sTimeIn.m_dHour	 =	(double)m_iHourIn;
	m_sTimeIn.m_sLatitude = m_sLatStart;
	m_sTimeIn.m_sLongitude = m_sLonStart;
	m_sTimeIn.ProcessLatLon();

	m_sTimeOut.m_dYear	 =	(double)m_iYearOut;
	m_sTimeOut.m_dMonth  =	(double)m_iMonthOut;
	m_sTimeOut.m_dDay	 =	(double)m_iDayOut;
	m_sTimeOut.m_dHour	 =	(double)m_iHourOut;
	m_sTimeOut.m_sLatitude = m_sLatEnd;
	m_sTimeOut.m_sLongitude = m_sLonEnd;
	m_sTimeOut.ProcessLatLon();

	m_sTimeInc.m_dYear	 =	(double)m_iYearInc;
	m_sTimeInc.m_dMonth  =	(double)m_iMonthInc;
	m_sTimeInc.m_dDay	 =	(double)m_iDayInc;
	m_sTimeInc.m_dHour	 =	(double)m_iHourInc;
	m_sTimeInc.m_dMinute =	(double)m_iMinuteInc;
	m_sTimeInc.m_dSecond =	(double)m_iSecondInc;
	m_sTimeInc.m_sLatitude = m_sLatInc;
	m_sTimeInc.m_sLongitude = m_sLonInc;
	m_sTimeInc.ProcessLatLon();

	if(m_iCalc == 7)
	{
		m_sTimeIn.m_sAmPm = "a";
		m_sTimeIn.m_dHour = 12;
	}

	m_sTimeIn.m_dTimeZone = m_dTimeZone;
	m_sTimeOut.m_dTimeZone = m_dTimeZone;
	m_sTimeInc.m_dTimeZone = m_dTimeZone;
}

void CAlmanac::CalculateValues()
{
	astrotime Astrotime;
	astrocalc Astrocalc;
	convert Convert;
	CPlanet body;
	CAngularSeparation pAngle;
	CPlanetTime pTime;
	Cvariation pVar;

	double julDay;
	int iNoTimesThrough, iNoTimesThroughLat, iNoTimesThroughLon;
	double year, month, day, date;
	double dHour, lat, lon, val1, val2, val3, val4, val5, val6, val7;
	CString str1, str2, str3, str4, str5, str6, str7, strLat, strLon;
	CString dateString;
	UINT cOutputStyle;
	int flag, iBody1, iBody2, i;
	int i_Found;
	double L1, L2, B1, B2;
	bool bContinueLat, bContinueLon, bContinueTime;
	double decLat, decLon;
	int iFail;

//////////////////////////////////////////////////////////
//m_iCalc =												//
//			0 = "Azimuth Altitude";						//
//			1 = "Equatorial Apparent";					//
//			2 = "Ecliptic Apparent Spherical";			//
//			3 = "Ecliptic True Spherical";				//
//			4 = "Ecliptic True Cartesian";				//
//			5 = "Heliocentric Spherical";				//
//			6 = "Heliocentric Cartesian";				//
//			7 = "Rise, Set, Transit";					//
//			8 = "GHA and Dec";							//
//			9 = "Angular Separation"					//
//			10 = "Magnetic Variation";					//
//////////////////////////////////////////////////////////

	CAlmanac::PrintTitles(m_iCalc);

	std::wofstream outfile;
	outfile.open(m_sFileName, std::ios::app );

	julDay = m_sTimeIn.m_dJulianDay;

	iNoTimesThrough = 0;
	do
	{
		Astrotime.calcYearMonthDay(julDay, year, month, day);
		dHour = (Convert.LSmodf(day, &date) * 24.0) - m_sTimeIn.m_dTimeZone;
		pTime.hourAdjust(year, month, date, dHour);

		dateString = Astrotime.TimeDisplayUT(year, month, date, dHour, 4);
		if(m_iValueSet[0] == 1 )
		{
			m_dAries = Astrocalc.apparSiderealRadian(julDay);
			CAlmanac::MakeString(m_dAries, m_sAries, m_cOutputStyle, m_iPrecision);
		}//end of "if(m_iValueSet[0] == 1 )"

		iNoTimesThroughLat = 0;
		lat = m_sTimeIn.m_dLatitude;
		do
		{
			iNoTimesThroughLon = 0;
			lon = m_sTimeIn.m_dLongitude;
			do
			{
				outfile<< std::endl;
				outfile<<(LPCTSTR) (Convert.DecimalToString(julDay, 6))<<"; ";
				outfile<< (LPCTSTR)dateString<<"; ";

				CAlmanac::MakeString(lat, strLat, m_cOutputStyle, m_iPrecision);
				CAlmanac::MakeString(lon, strLon, m_cOutputStyle, m_iPrecision);
				outfile<< (LPCTSTR)strLat<<"; ";
				outfile<< (LPCTSTR)strLon<<"; ";

				if(m_iCalc != 10)
				{
					if(m_iValueSet[0] == 1 )
					{
					outfile<< (LPCTSTR)m_sAries<<"; ";
					}//end of "if(m_iValueSet[0] == 1 )"
				}

				if(		m_iCalc !=9
					&&
						m_iCalc != 10)
				{
					int i;
					for(i=1; i<12; i++)
					{
						if(m_iValueSet[i] == 1 )
						{
							switch ( i )
							{
							case 1:
								body.venus();
								break;
							case 2:
								body.mars();
								break;
							case 3:
								body.jupiter();
								break;
							case 4:
								body.saturn();
								break;
							case 5:
								body.sun();
								break;
							case 6:
								body.moon();
								break;
							case 7:
								body.mercury();
								break;
							case 8:
								body.earth();
								break;
							case 9:
								body.uranus();
								break;
							case 10:
								body.neptune();
								break;
							case 11:
								body.pluto();
								break;
							}//end of "switch ( i )"
							switch (m_iCalc)
							{
							case 0:
								body.azimuthAltitudePlanet(julDay, lat, lon, val1, val2);
								break;
							case 1:
								body.equatorialAppPlanet(julDay, val1, val2, val3);
								break;
							case 2:
								body.geocentricSphericalAppPlanet(julDay, val1, val2, val3);
								break;
							case 3:
								body.geocentricSphericalTruePlanet(julDay, val1, val2, val3);
								break;
							case 4:
								body.geocentricCartesianTruePlanet(julDay, val1, val2, val3);
								break;
							case 5:
								body.primaryBodyLocation(julDay, val1, val2, val3);
								break;
							case 6:
								body.heliocentricCartesianPlanet(julDay, val1, val2, val3);
								break;
							case 7:
								body.riseSetTransitPlanet(julDay, lat, lon, val1, val2, val3, val4,
									CAlmanac::ConvertValue(i), -m_sTimeIn.m_dTimeZone, flag);
								break;
							case 8:
								body.equatorialAppPlanet(julDay, val1, val2, val3);
								val1 = Convert.radianPositiveValue(m_dAries - val1);
								break;
//							case 10:

							}//end of "switch (m_iCalc)"
							switch (m_iCalc)
							{
							case 0:
								CAlmanac::MakeString(val1, str1, m_cOutputStyle, m_iPrecision);
								CAlmanac::MakeString(val2, str2, m_cOutputStyle, m_iPrecision);
								outfile<< (LPCTSTR)str1<<"; "<< (LPCTSTR)str2<<"; ";
								break;

							case 1:
							case 2:
							case 3:
							case 5:
								CAlmanac::MakeString(val1, str1, m_cOutputStyle, m_iPrecision);
								CAlmanac::MakeString(val2, str2, m_cOutputStyle, m_iPrecision);
								outfile<< (LPCTSTR)str1<<"; "<< (LPCTSTR)str2<<"; ";
								CAlmanac::MakeString(val3, str3, IDS_RADIAN, m_iPrecision);
								outfile<< (LPCTSTR)str3<<"; ";
								break;
							
							case 4:
							case 6:
								CAlmanac::MakeString(val1, str1, IDS_RADIAN, m_iPrecision);
								CAlmanac::MakeString(val2, str2, IDS_RADIAN, m_iPrecision);
								CAlmanac::MakeString(val3, str3, IDS_RADIAN, m_iPrecision);
								outfile<< (LPCTSTR)str1<<"; "<< (LPCTSTR)str2<<"; "<< (LPCTSTR)str3<<"; ";
								break;

							case 7:
								if(		IDS_RADIAN == m_cOutputStyle 
								   ||	m_cOutputStyle == IDS_DECIMAL)
								{
									cOutputStyle = IDS_RADIAN;
								}
								else
								{
									cOutputStyle = IDS_HOUR;
								}

								str1 = CAlmanac::RiseSetOutputString(val1, cOutputStyle);
								str2 = CAlmanac::RiseSetOutputString(val2, cOutputStyle);
								str3 = CAlmanac::RiseSetOutputString(val3, cOutputStyle);

								str4 = "";
								if(flag == 2 || flag == 6)
								{
									CAlmanac::MakeString(val4, str4, cOutputStyle, m_iPrecision);
								}

								outfile<< (LPCTSTR)str1<<"; "<< (LPCTSTR)str2<<"; "<< (LPCTSTR)str3<<"; "<< (LPCTSTR)str4<<"; ";
								break;
							case 8:
								CAlmanac::MakeString(val1, str1, IDS_DEGREE, m_iPrecision);
								CAlmanac::MakeString(val2, str2, IDS_DEGREE, m_iPrecision);
								outfile<< (LPCTSTR)str1<<"; "<< (LPCTSTR)str2<<"; ";
								break;
							}//end of "switch (m_iCalc)"
						}//end of "if(m_iValueSet[i] == 1 )"
					}//end of "for(i=1; i<12; i++)"
				}//end of "if(m_iCalc !=9)"
				else if (m_iCalc == 9)
				{// Calculating Angular Separation
					i_Found = 0;
					for(i=0; i<12; i++)
					{
						if(m_iValueSet[i] == 1)
						{
							if(i_Found == 0)
							{
								iBody1 = i;
								i_Found ++;
							}
							else
							{
								iBody2 = i;
								i_Found ++;
								break;
							}
						}// end of "if(m_iValueSet[i] == 1"
						if(i_Found > 1)break;
					}//end of "for(i=0; i<11; i++)"

					iBody1 = CAlmanac::ConvertValue(iBody1);
					iBody2 = CAlmanac::ConvertValue(iBody2);

					if(		m_sAngSepType == "geo" 
						&& (iBody1 == 4 || iBody2 == 4))
					{
						val1 = 0;
					}
					else if(	m_sAngSepType == "helio"
							&&	(iBody1 == 0 || iBody2 == 0))
					{
						val1 = 0;
					}
					else if(m_sAngSepType == "geo")
					{
						pAngle.CalculatePositionsGeocentric(julDay, iBody1, iBody2,
															L1, L2, B1, B2);
						val1 = pAngle.CalculateAngularSeparation(L1, L2, B1, B2);
					}
					else
					{
						pAngle.CalculatePositionsHelioentric(julDay, iBody1, iBody2,
															 L1, L2, B1, B2);
						val1 = pAngle.CalculateAngularSeparation(L1, L2, B1, B2);
					}
					CAlmanac::MakeString(val1, str1, m_cOutputStyle, m_iPrecision);
					outfile<< (LPCTSTR)str1<<"; ";
				}
				else if (m_iCalc == 10)
				{
					decLat = Convert.radianToDegree(lat);
					decLon = -Convert.radianToDegree(lon);
					iFail = pVar.geomag((int)year,
										(int)month,
										(int)date,
										decLat,
										decLon,
										&val1,
										&val2,
										&val3,
										&val4,
										&val5,
										&val6,
										&val7);
					if(iFail)// Wrong dates or no file
					{
						val1 = 0;
						val2 = 0;
						val3 = 0;
						val4 = 0;
						val5 = 0;
						val6 = 0;
						val7 = 0;
					}
					CAlmanac::MakeString(val1, str1, IDS_DEGREE, m_iPrecision);
					CAlmanac::MakeString(val2, str2, IDS_DEGREE, m_iPrecision);
					CAlmanac::MakeString(val3, str3, IDS_RADIAN, 0);
					CAlmanac::MakeString(val4, str4, IDS_RADIAN, 0);
					CAlmanac::MakeString(val5, str5, IDS_RADIAN, 0);
					CAlmanac::MakeString(val6, str6, IDS_RADIAN, 0);
					CAlmanac::MakeString(val7, str7, IDS_RADIAN, 0);
					outfile<< (LPCTSTR)str1<<"; "<< (LPCTSTR)str2<<"; " << (LPCTSTR)str3<<"; "<< (LPCTSTR)str4<<"; "<< (LPCTSTR)str5<<"; "<< (LPCTSTR)str6<<"; "<< (LPCTSTR)str7<<"; ";
				}

				iNoTimesThroughLon += 1;
				lon += m_sTimeInc.m_dLongitude;
				bContinueLon = true;
				if(m_iLonRuns > 0)// use m_iLonRuns as criterion
				{
					if(!(iNoTimesThroughLon < m_iLonRuns))
					{
						bContinueLon = false;
					}
				}
				else if(m_sTimeOut.m_dLongitude == m_sTimeIn.m_dLongitude)
				{
					bContinueLon = false;
				}
				else if(!(lon <= m_sTimeOut.m_dLongitude))// use lon as criterion
				{
					bContinueLon = false;
				}
			}//end of "while(lon < m_sTimeOut.m_dLongitude..."
			while(bContinueLon);

			iNoTimesThroughLat += 1;
			lat += m_sTimeInc.m_dLatitude;
			bContinueLat = true;
			if(m_iLatRuns > 0)// use m_iLatRuns as criterion
			{
				if(!(iNoTimesThroughLat < m_iLatRuns))
				{
					bContinueLat = false;
				}
			}
			else if(m_sTimeOut.m_dLatitude == m_sTimeIn.m_dLatitude)
			{
				bContinueLat = false;
			}
			else if(!(lat <= m_sTimeOut.m_dLatitude))//	use lat as criterion
			{
				bContinueLat = false;
			}
		}//end of "while( lat < m_sTimeOut.m_dLatitude..."
		while(bContinueLat);

		iNoTimesThrough += 1;
		julDay += m_sTimeInc.m_dFractionJulianDay;
		bContinueTime = true;
		if(m_iNoRuns > 0)
		{//	use m_iNoRuns as criterion
			if(!(iNoTimesThrough < m_iNoRuns))
			{
				bContinueTime = false;
			}
		}
		else if(m_sTimeOut.m_dJulianDay == m_sTimeIn.m_dJulianDay)
		{
			bContinueTime = false;
		}
		else if(!(julDay <= m_sTimeOut.m_dJulianDay))
		{//	use julDay as criterion
			bContinueTime = false;
		}
	}	//end of "while(julDay	< m_sTimeOut.m_dJulianDay...)"
	while(bContinueTime);

	outfile.close();
}

CString CAlmanac::RiseSetOutputString(double value, UINT cOutputStyle)
{
	CString stringValue;

	if(value < 0)
	{
		stringValue.LoadString(IDS_NEVER_UP);
		if(value < -10)
		{
			stringValue.LoadString(IDS_ALWAYS_UP);
		}
		if(value < -100)
		{
			stringValue.LoadString(IDS_NEXT_DAY);
		}
	}
	else
	{
		CAlmanac::MakeString(value, stringValue, cOutputStyle, m_iPrecision);
	}
	return stringValue;
}

//	Need this to convert CAlmanac value to Planets value
int CAlmanac::ConvertValue(int value)
{
//	sun, moon, merc, ven, eart, mars, jup, sat, uran, nep, plu
//	0	  1		2	  3		4	 5		6	7	  8		9	10
	switch (value)
	{
	case 1:
		return 3;
		break;
	case 2:
		return 5;
		break;
	case 3:
		return 6;
		break;
	case 4:
		return 7;
		break;
	case 5:
		return 0;
		break;
	case 6:
		return 1;
		break;
	case 7:
		return 2;
		break;
	case 8:
		return 4;
		break;
	case 9:
		return 8;
		break;
	case 10:
		return 9;
		break;
	default:
		return 10;
		break;
	}
}

void CAlmanac::MakeString(double value, CString &retString,
						  UINT type, int iPrecision)
{
	convert Convert;
	double temp;

	if(type == IDS_RADIAN)
	{
		retString = Convert.DecimalToString(value, iPrecision);
	}
	else if(type == IDS_DECIMAL)
	{
		retString = Convert.DecimalToString(Convert.radianToDegree(value), iPrecision);
	}
	else if (type == IDS_DEGREE)
	{
		temp = Convert.degreeToDMS(Convert.radianToDegree(value));
		retString = Convert.HMSToString(temp, "d", iPrecision);
	}
	else if (type == IDS_HOUR)
	{
		temp = Convert.hourToHMS(value);
		retString = Convert.HMSToString(temp, "h", iPrecision);
	}
}

void CAlmanac::WhichPlanets(CAlmanac* pAlBox, int iValueSet[12])
{
	int i;

	for (i=0; i<12; i++)
	{
		iValueSet[i] = 0;
	}

	m_pAriesCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_ARIES);
	m_pVenusCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_VENUS);
	m_pMarsCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_MARS);
	m_pJupiterCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_JUPITER);
	m_pSaturnCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_SATURN);
	m_pSunCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_SUN);
	m_pMoonCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_MOON);
	m_pMercuryCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_MERCURY);
	m_pEarthCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_EARTH);
	m_pUranusCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_URANUS);
	m_pNeptuneCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_NEPTUNE);
	m_pPlutoCheckBox = (CButton*)pAlBox->GetDlgItem(IDC_PLUTO);

	if(m_pAriesCheckBox		->GetCheck() == 1)iValueSet[0] = 1;
	if(m_pVenusCheckBox		->GetCheck() == 1)iValueSet[1] = 1;
	if(m_pMarsCheckBox		->GetCheck() == 1)iValueSet[2] = 1;
	if(m_pJupiterCheckBox	->GetCheck() == 1)iValueSet[3] = 1;
	if(m_pSaturnCheckBox	->GetCheck() == 1)iValueSet[4] = 1;
	if(m_pSunCheckBox		->GetCheck() == 1)iValueSet[5] = 1;
	if(m_pMoonCheckBox		->GetCheck() == 1)iValueSet[6] = 1;
	if(m_pMercuryCheckBox	->GetCheck() == 1)iValueSet[7] = 1;
	if(m_pEarthCheckBox		->GetCheck() == 1)iValueSet[8] = 1;
	if(m_pUranusCheckBox	->GetCheck() == 1)iValueSet[9] = 1;
	if(m_pNeptuneCheckBox	->GetCheck() == 1)iValueSet[10] = 1;
	if(m_pPlutoCheckBox		->GetCheck() == 1)iValueSet[11] = 1;
//	Set Sun and Moon or Earth to not calculate depending on 
//	what you are calculating
//////////////////////////////////////////////////////////
//m_iCalc =												//
//			0 = "Azimuth Altitude";						//
//			1 = "Equatorial Apparent";					//
//			2 = "Ecliptic Apparent Spherical";			//
//			3 = "Ecliptic True Spherical";				//
//			4 = "Ecliptic True Cartesian";				//
//			5 = "Heliocentric Spherical";				//
//			6 = "Heliocentric Cartesian";				//
//			7 = "Rise, Set, Transit";					//
//			8 = "GHA and Dec";							//
//			9 = "Angular Separation";					//
//			10 = "Magnetic Variation					//
//			Aries =	m_iValueSet[0]						//
//			Venus = m_iValueSet[1]						//
//			Mars = m_iValueSet[2]						//
//			Jupiter = m_iValueSet[3]					//
//			Saturn = m_iValueSet[4] 					//
//			Sun = m_iValueSet[5] 						//
//			Moon = m_iValueSet[6] 						//
//			Mercury = m_iValueSet[7]					//
//			Earth = m_iValueSet[8] 						//
//			Uranus = m_iValueSet[9]						//
//			Neptune = m_iValueSet[10]					//
//			Pluto = m_iValueSet[11]						//
//////////////////////////////////////////////////////////
	switch(m_iCalc)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 7:
	case 8:
		m_iValueSet[8] = 0;
		break;
	case 5:
	case 6:
		m_iValueSet[5] = 0;
		m_iValueSet[6] = 0;
		break;
	default:
		break;
	}
}

void CAlmanac::PrintTitles(int method)
{
	int i;
	CString bodyText, calcParameter1, calcParameter2, calcParameter3;
	CString calcParameter4;
	bool set9Flag;

	std::wofstream outfile;
	outfile.open(m_sFileName, std::ios::trunc );

	switch (method)
	{
	case 0:
		outfile<<" Azimuth Altitude ";
		calcParameter1 = "Azimuth";
		calcParameter2 = "Altitude";
		break;
	case 1:
		outfile<<" Equatorial Apparent ";
		calcParameter1 = "Right Ascension";
		calcParameter2 = "Declination";
		calcParameter3 = "Radius";
		break;
	case 2:
		outfile<<" Ecliptic Apparent Spherical ";
		calcParameter1 = "Longitude";
		calcParameter2 = "Latitude";
		calcParameter3 = "Radius";
		break;
	case 3:
		outfile<<" Ecliptic True Spherical ";
		calcParameter1 = "Longitude";
		calcParameter2 = "Latitude";
		calcParameter3 = "Radius";
		break;
	case 4:
		outfile<<" Ecliptic True Cartesian ";
		calcParameter1 = "X";
		calcParameter2 = "Y";
		calcParameter3 = "Z";
		break;
	case 5:
		outfile<<" Heliocentric Spherical ";
		calcParameter1 = "Longitude";
		calcParameter2 = "Latitude";
		calcParameter3 = "Radius";
		break;
	case 6:
		outfile<<" Heliocentric Cartesian ";
		calcParameter1 = "X";
		calcParameter2 = "Y";
		calcParameter3 = "Z";
		break;
	case 7:
		outfile<<" Rise, Set, Transit ";
		calcParameter1 = "Rise";
		calcParameter2 = "Transit";
		calcParameter3 = "Set";
		calcParameter4 = "Extra Rise/Set";
		break;
	case 8:
		outfile<<" GHA and Dec ";
		calcParameter1 = "GHA";
		calcParameter2 = "Dec";
		break;
	case 9:
		outfile<<" Angular Separation ";
		break;
	case 10:
		outfile<<" Magnetic Variation ";
		calcParameter1 = "Variation";
		calcParameter2 = "Inclination (Dip); Horizontal; North; East; Vertical; Total";
		break;
	}
		outfile<< std::endl;
		outfile<<"Julian Date; ";
		outfile<<"Calendar Date; ";
		outfile<<"Latitude; ";
		outfile<<"Longitude; ";

	if(method != 10)
	{
		if(m_iValueSet[0] == 1)outfile<<"Aries; ";

		set9Flag = true;
		for (i=1; i<12; i++)
		{
			if(m_iValueSet[i] == 1)
			{
				switch (i)
				{
				case 1:
					bodyText.LoadString(IDS_VENUS);
					break;
				case 2:
					bodyText.LoadString(IDS_MARS);
					break;
				case 3:
					bodyText.LoadString(IDS_JUPITER);
					break;
				case 4:
					bodyText.LoadString(IDS_SATURN);
					break;
				case 5:
					bodyText.LoadString(IDS_SUN);
					break;
				case 6:
					bodyText.LoadString(IDS_MOON);
					break;
				case 7:
					bodyText.LoadString(IDS_MERCURY);
					break;
				case 8:
					bodyText.LoadString(IDS_EARTH);
					break;
				case 9:
					bodyText.LoadString(IDS_URANUS);
					break;
				case 10:
					bodyText.LoadString(IDS_NEPTUNE);
					break;
				case 11:
					bodyText.LoadString(IDS_PLUTO);
					break;
				}

			if(method == 9)
			{
				if(set9Flag)
				{
					outfile<< (LPCTSTR)bodyText<<"-";
					set9Flag = false;
				}
				else
				{
					outfile<< (LPCTSTR)bodyText;
				}
			}
			else if (method == 10)
			{
			}
			else
			{
				outfile<< (LPCTSTR)bodyText<<" "<< (LPCTSTR)calcParameter1<<"; ";
				outfile<< (LPCTSTR)bodyText<<" "<< (LPCTSTR)calcParameter2<<"; ";
			}

				switch (method)
				{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
			outfile<< (LPCTSTR)bodyText<<" "<< (LPCTSTR)calcParameter3<<"; ";
					break;
				case 7:
			outfile<< (LPCTSTR)bodyText<<" "<< (LPCTSTR)calcParameter3<<"; ";
			outfile<< (LPCTSTR)bodyText<<" "<< (LPCTSTR)calcParameter4<<"; ";
					break;
				}
			}
		}
	}
	else
	{
		outfile<< (LPCTSTR)calcParameter1<<"; ";
		outfile<< (LPCTSTR)calcParameter2<<"; ";
	}
	outfile.close();
}

void CAlmanac::OnDoAll()
{
	m_pCDialog = this;
	m_pDoAll			= (CButton*)m_pCDialog->GetDlgItem(IDC_ALL);
	m_pDoAlmanac		= (CButton*)m_pCDialog->GetDlgItem(IDC_ALMANAC);
	m_pAriesCheckBox	= (CButton*)m_pCDialog->GetDlgItem(IDC_ARIES);
	m_pVenusCheckBox	= (CButton*)m_pCDialog->GetDlgItem(IDC_VENUS);
	m_pMarsCheckBox		= (CButton*)m_pCDialog->GetDlgItem(IDC_MARS);
	m_pJupiterCheckBox	= (CButton*)m_pCDialog->GetDlgItem(IDC_JUPITER);
	m_pSaturnCheckBox	= (CButton*)m_pCDialog->GetDlgItem(IDC_SATURN);
	m_pSunCheckBox		= (CButton*)m_pCDialog->GetDlgItem(IDC_SUN);
	m_pMoonCheckBox		= (CButton*)m_pCDialog->GetDlgItem(IDC_MOON);
	m_pMercuryCheckBox	= (CButton*)m_pCDialog->GetDlgItem(IDC_MERCURY);
	m_pEarthCheckBox	= (CButton*)m_pCDialog->GetDlgItem(IDC_EARTH);
	m_pUranusCheckBox	= (CButton*)m_pCDialog->GetDlgItem(IDC_URANUS);
	m_pNeptuneCheckBox	= (CButton*)m_pCDialog->GetDlgItem(IDC_NEPTUNE);
	m_pPlutoCheckBox	= (CButton*)m_pCDialog->GetDlgItem(IDC_PLUTO);

	if(m_pDoAll->GetCheck() == 1)
	{
		m_pAriesCheckBox	->SetCheck(1);
		m_pVenusCheckBox	->SetCheck(1);
		m_pMarsCheckBox		->SetCheck(1);
		m_pJupiterCheckBox	->SetCheck(1);
		m_pSaturnCheckBox	->SetCheck(1);
		m_pSunCheckBox		->SetCheck(1);
		m_pMoonCheckBox		->SetCheck(1);
		m_pMercuryCheckBox	->SetCheck(1);
		m_pEarthCheckBox	->SetCheck(1);
		m_pUranusCheckBox	->SetCheck(1);
		m_pNeptuneCheckBox	->SetCheck(1);
		m_pPlutoCheckBox	->SetCheck(1);
		m_pDoAlmanac		->SetCheck(0);
	}
	else
	{
		m_pAriesCheckBox->SetCheck(0);
		m_pVenusCheckBox->SetCheck(0);
		m_pMarsCheckBox->SetCheck(0);
		m_pJupiterCheckBox->SetCheck(0);
		m_pSaturnCheckBox->SetCheck(0);
		m_pSunCheckBox->SetCheck(0);
		m_pMoonCheckBox->SetCheck(0);
		m_pMercuryCheckBox->SetCheck(0);
		m_pEarthCheckBox->SetCheck(0);
		m_pUranusCheckBox->SetCheck(0);
		m_pNeptuneCheckBox->SetCheck(0);
		m_pPlutoCheckBox->SetCheck(0);
		m_pDoAlmanac->SetCheck(0);
	}
}

void CAlmanac::WriteProfiles()
{
	CWinApp* pApp = AfxGetApp();
	CButton *output0, *output1, *output2;
	CListBox* calc;
	CButton *almanac, *all, *aries;
	CButton *sun, *moon, *mercury, *venus, *earth;
	CButton *mars, *jup, *sat, *uranus, *nep, *pluto;
	int err;

	char sTimeZone[9];

	output0 = (CButton*)this->GetDlgItem(IDC_DECIMAL_RADIO);
	output1 = (CButton*)this->GetDlgItem(IDC_DEGREE_RADIO);
	output2 = (CButton*)this->GetDlgItem(IDC_RADIAN_RADIO);
	pApp->WriteProfileInt( _T ("Almanac"), _T("output0"), output0->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("output1"), output1->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("output2"), output2->GetCheck());

	calc = (CListBox*)this->GetDlgItem(IDC_ALMANAC_LIST);
	m_iCalc = calc->GetCurSel();
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iCalc"), m_iCalc);

	pApp->WriteProfileString( _T ("Almanac"), _T("m_cLatStartNS"), m_cLatStartNS);
	pApp->WriteProfileString( _T ("Almanac"), _T("m_cLatEndNS"), m_cLatEndNS);
	pApp->WriteProfileString( _T ("Almanac"), _T("m_cLonStartEW"), m_cLonStartEW);
	pApp->WriteProfileString( _T ("Almanac"), _T("m_cLonEndEW"), m_cLonEndEW);

	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iYearIn"), m_iYearIn);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iMonthIn"), m_iMonthIn);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iDayIn"), m_iDayIn);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iHourIn"), m_iHourIn);

	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iYearOut"), m_iYearOut);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iMonthOut"), m_iMonthOut);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iDayOut"), m_iDayOut);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iHourOut"), m_iHourOut);

	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iYearInc"), m_iYearInc);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iMonthInc"), m_iMonthInc);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iDayInc"), m_iDayInc);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iHourInc"), m_iHourInc);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iMinuteInc"), m_iMinuteInc);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iMonthOut"), m_iMonthOut);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iSecondInc"), m_iSecondInc);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iNoRuns"), m_iNoRuns);

	pApp->WriteProfileString( _T ("Almanac"), _T("m_sLatStart"), m_sLatStart);
	pApp->WriteProfileString( _T ("Almanac"), _T("m_sLatEnd"), m_sLatEnd);
	pApp->WriteProfileString( _T ("Almanac"), _T("m_sLatInc"), m_sLatInc);
	pApp->WriteProfileString( _T ("Almanac"), _T("m_sLonStart"), m_sLonStart);
	pApp->WriteProfileString( _T ("Almanac"), _T("m_sLonEnd"), m_sLonEnd);
	pApp->WriteProfileString( _T ("Almanac"), _T("m_sLonInc"), m_sLonInc);

	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iLatRuns"), m_iLatRuns);
	pApp->WriteProfileInt( _T ("Almanac"), _T("m_iLonRuns"), m_iLonRuns);

	err = _gcvt_s(sTimeZone, 9, m_dTimeZone, 4);
	pApp->WriteProfileString( _T ("Almanac"), _T("m_dTimeZone"), LPCTSTR (sTimeZone));

	almanac = (CButton*)this->GetDlgItem(IDC_ALMANAC);
	all		= (CButton*)this->GetDlgItem(IDC_ALL);
	aries	= (CButton*)this->GetDlgItem(IDC_ARIES);
	sun		= (CButton*)this->GetDlgItem(IDC_SUN);
	moon	= (CButton*)this->GetDlgItem(IDC_MOON);
	mercury	= (CButton*)this->GetDlgItem(IDC_MERCURY);
	venus	= (CButton*)this->GetDlgItem(IDC_VENUS);
	earth	= (CButton*)this->GetDlgItem(IDC_EARTH);
	mars	= (CButton*)this->GetDlgItem(IDC_MARS);
	jup		= (CButton*)this->GetDlgItem(IDC_JUPITER);
	sat		= (CButton*)this->GetDlgItem(IDC_SATURN);
	uranus	= (CButton*)this->GetDlgItem(IDC_URANUS);
	nep		= (CButton*)this->GetDlgItem(IDC_NEPTUNE);
	pluto	= (CButton*)this->GetDlgItem(IDC_PLUTO);

	pApp->WriteProfileInt( _T ("Almanac"), _T("almanac")	, almanac	->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("all")		, all		->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("aries")		, aries		->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("sun")		, sun		->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("moon")		, moon		->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("mercury")	, mercury	->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("venus")		, venus		->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("earth")		, earth		->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("mars")		, mars		->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("jupiter")	, jup		->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("saturn")		, sat		->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("uranus")		, uranus	->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("neptune")	, nep		->GetCheck());
	pApp->WriteProfileInt( _T ("Almanac"), _T("pluto")		, pluto		->GetCheck());
}
void CAlmanac::OnClose() 
{
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	CAlmanac::WriteProfiles();
	GetWindowRect(&winRect);
	pApp->WriteProfileInt( _T ("Almanac"), _T("top"), winRect.top);
	pApp->WriteProfileInt( _T ("Almanac"), _T("left"), winRect.left);
	
	CDialog::OnClose();
}


void CAlmanac::OnDestroy() 
{
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	CAlmanac::WriteProfiles();
	GetWindowRect(&winRect);
	pApp->WriteProfileInt( _T ("Almanac"), _T("top"), winRect.top);
	pApp->WriteProfileInt( _T ("Almanac"), _T("left"), winRect.left);
	CDialog::OnDestroy();
}

BOOL CAlmanac::OnInitDialog() 
{
	CWinApp* pApp = AfxGetApp();

//	char *stopstring;
	CDialog::OnInitDialog();
	CString sLatStart, sLatEnd, sLatInc, sLonStart;
	CString sLonEnd, sLonInc, sTimeZone;
	
	m_cLatStartNS = pApp->GetProfileString( _T ("Almanac"), _T("m_cLatStartNS"), _T("n"));
	m_cLatEndNS = pApp->GetProfileString( _T ("Almanac"), _T("m_cLatEndNS"), _T("n"));
	m_cLonStartEW = pApp->GetProfileString( _T ("Almanac"), _T("m_cLonStartEW"), _T("w"));
	m_cLonEndEW = pApp->GetProfileString( _T ("Almanac"), _T("m_cLonEndEW"), _T("w"));

	m_iYearIn = pApp->GetProfileInt( _T ("Almanac"), _T("m_iYearIn"), 2010);
	m_iMonthIn = pApp->GetProfileInt( _T ("Almanac"), _T("m_iMonthIn"), 1);
	m_iDayIn = pApp->GetProfileInt( _T ("Almanac"), _T("m_iDayIn"), 2);
	m_iHourIn = pApp->GetProfileInt( _T ("Almanac"), _T("m_iHourIn"), 2);

	m_iYearOut = pApp->GetProfileInt( _T ("Almanac"), _T("m_iYearOut"), 2012);
	m_iMonthOut = pApp->GetProfileInt( _T ("Almanac"), _T("m_iMonthOut"), 2);
	m_iDayOut = pApp->GetProfileInt( _T ("Almanac"), _T("m_iDayOut"), 1);
	m_iHourOut = pApp->GetProfileInt( _T ("Almanac"), _T("m_iHourOut"), 3);

	m_iYearInc = pApp->GetProfileInt( _T ("Almanac"), _T("m_iYearInc"), 0);
	m_iMonthInc = pApp->GetProfileInt( _T ("Almanac"), _T("m_iMonthInc"), 0);
	m_iDayInc = pApp->GetProfileInt( _T ("Almanac"), _T("m_iDayInc"), 1);
	m_iHourInc = pApp->GetProfileInt( _T ("Almanac"), _T("m_iHourInc"), 0);
	m_iMinuteInc = pApp->GetProfileInt( _T ("Almanac"), _T("m_iMinuteInc"), 0);
	m_iSecondInc = pApp->GetProfileInt( _T ("Almanac"), _T("m_iSecondInc"), 0);
	m_iNoRuns = pApp->GetProfileInt( _T ("Almanac"), _T("m_iNoRuns"), 0);

	m_sLatStart = pApp->GetProfileString( _T ("Almanac"), _T("m_sLatStart"), _T("44"));
	m_sLatEnd = pApp->GetProfileString( _T ("Almanac"), _T("m_sLatEnd"), 0);
	m_sLatInc = pApp->GetProfileString( _T ("Almanac"), _T("m_sLatInc"), 0);
	m_sLonStart = pApp->GetProfileString( _T ("Almanac"), _T("m_sLonStart"), _T("68"));
	m_sLonEnd = pApp->GetProfileString( _T ("Almanac"), _T("m_sLonEnd"), 0);
	m_sLonInc = pApp->GetProfileString( _T ("Almanac"), _T("m_sLonInc"), 0);

	m_iLatRuns = pApp->GetProfileInt( _T ("Almanac"), _T("m_iLatRuns"), 0);
	m_iLonRuns = pApp->GetProfileInt( _T ("Almanac"), _T("m_iLonRuns"), 0);

	sTimeZone = pApp->GetProfileString( _T ("Almanac"), _T("m_dTimeZone"), _T("5"));
	//  DLAS 18Feb9
	//	See https://stackoverflow.com/questions/916790/how-do-i-convert-a-cstring-to-a-double-in-c
	//	for explanation of this change
	//m_dTimeZone = strtod(sTimeZone, &stopstring);
	m_dTimeZone = _tstof(sTimeZone);

	m_iPrecision = pApp->GetProfileInt( _T ("TimeLocation"), _T("precision"), 5);

	UpdateData(false);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAlmanac::OnAlmanac() 
{
	m_pCDialog = this;
	m_pDoAll = (CButton*)m_pCDialog->GetDlgItem(IDC_ALL);
	m_pDoAlmanac = (CButton*)m_pCDialog->GetDlgItem(IDC_ALMANAC);
	m_pAriesCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_ARIES);
	m_pVenusCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_VENUS);
	m_pMarsCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_MARS);
	m_pJupiterCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_JUPITER);
	m_pSaturnCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_SATURN);
	m_pSunCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_SUN);
	m_pMoonCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_MOON);
	m_pMercuryCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_MERCURY);
	m_pEarthCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_EARTH);
	m_pUranusCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_URANUS);
	m_pNeptuneCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_NEPTUNE);
	m_pPlutoCheckBox = (CButton*)m_pCDialog->GetDlgItem(IDC_PLUTO);

	if(m_pDoAlmanac->GetCheck() == 1)
	{
		m_pAriesCheckBox->SetCheck(1);
		m_pVenusCheckBox->SetCheck(1);
		m_pMarsCheckBox->SetCheck(1);
		m_pJupiterCheckBox->SetCheck(1);
		m_pSaturnCheckBox->SetCheck(1);
		m_pSunCheckBox->SetCheck(1);
		m_pMoonCheckBox->SetCheck(1);
		m_pMercuryCheckBox->SetCheck(0);
		m_pEarthCheckBox->SetCheck(0);
		m_pUranusCheckBox->SetCheck(0);
		m_pNeptuneCheckBox->SetCheck(0);
		m_pPlutoCheckBox->SetCheck(0);
		m_pDoAll->SetCheck(0);
	}
	else
	{
		m_pAriesCheckBox->SetCheck(0);
		m_pVenusCheckBox->SetCheck(0);
		m_pMarsCheckBox->SetCheck(0);
		m_pJupiterCheckBox->SetCheck(0);
		m_pSaturnCheckBox->SetCheck(0);
		m_pSunCheckBox->SetCheck(0);
		m_pMoonCheckBox->SetCheck(0);
	}
}

void CAlmanac::OnAlmOutput() 
{
	CButton* dec;
	CButton* deg;
	CButton* rad;

	dec = (CButton*)this->GetDlgItem(IDC_DECIMAL_RADIO);
	deg = (CButton*)this->GetDlgItem(IDC_DEGREE_RADIO);
	rad = (CButton*)this->GetDlgItem(IDC_RADIAN_RADIO);

	if(dec->GetCheck() == 1)
	{
		m_cOutputStyle = IDS_DECIMAL;
	}
	else if(deg->GetCheck() == 1)
	{
		m_cOutputStyle = IDS_DEGREE;
	}
	else
	{
		m_cOutputStyle = IDS_RADIAN;
	}	
}

void CAlmanac::OnSelchangeAlmanacList() 
{
//////////////////////////////////////////////////////////
//m_iCalc =												//
//			0 = "Azimuth Altitude";						//
//			1 = "Equatorial Apparent";					//
//			2 = "Ecliptic Apparent Spherical";			//
//			3 = "Ecliptic True Spherical";				//
//			4 = "Ecliptic True Cartesian";				//
//			5 = "Heliocentric Spherical";				//
//			6 = "Heliocentric Cartesian";				//
//			7 = "Rise, Set, Transit";					//
//			8 = "GHA and Dec";							//
//			9 = "Angular Separation";					//
//			10 = "Magnetic Variation"					//
//////////////////////////////////////////////////////////

	CButton* geoRadio;
	CButton* helioRadio;
	CListBox* calc;

	calc = (CListBox*)this->GetDlgItem(IDC_ALMANAC_LIST);
	m_iCalc = calc->GetCurSel();

	geoRadio = (CButton*)this->GetDlgItem(IDC_GEO);
	helioRadio = (CButton*)this->GetDlgItem(IDC_HELIO);

	if(m_iCalc == 9)
	{
		geoRadio->ShowWindow(SW_SHOW);
		helioRadio->ShowWindow(SW_SHOW);
		geoRadio->SetCheck(1);
		helioRadio->SetCheck(0);
	}
	else if(geoRadio->IsWindowVisible())
	{
		geoRadio->ShowWindow(SW_HIDE);
		helioRadio->ShowWindow(SW_HIDE);
	}
}

void CAlmanac::OnAngSepGroup() 
{
	CButton* geo;

	geo = (CButton*)this->GetDlgItem(IDC_GEO);

	if(geo->GetCheck() == 1)
	{
		m_sAngSepType = "geo";
	}
	else
	{
		m_sAngSepType = "helio";
	}
}

void CAlmanac::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}
