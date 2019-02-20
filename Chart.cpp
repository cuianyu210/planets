// Chart.cpp : implementation file
//

#include "stdafx.h"
#include "Chart.h"
#include "convert.h"
#include "astrocalc.h"
#include <math.h>
#include "AngularSeparation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChart

CChart::CChart()
{
	m_sSignNames[0].LoadString(IDS_ARIES);// = "Aries";
	m_sSignNames[1].LoadString(IDS_TAURUS);// = "Taurus";
	m_sSignNames[2].LoadString(IDS_GEMINI);// = "Gemini";
	m_sSignNames[3].LoadString(IDS_CANCER);// = "Cancer";
	m_sSignNames[4].LoadString(IDS_LEO);// = "Leo";
	m_sSignNames[5].LoadString(IDS_VIRGO);// = "Virgo";
	m_sSignNames[6].LoadString(IDS_LIBRA);// = "Libra";
	m_sSignNames[7].LoadString(IDS_SCORPIO);// = "Scorpio";
	m_sSignNames[8].LoadString(IDS_SAGITTARIUS);// = "Sagittarius";
	m_sSignNames[9].LoadString(IDS_CAPRICORN);// = "Capricorn";
	m_sSignNames[10].LoadString(IDS_AQUARIUS);// = "Aquarius";
	m_sSignNames[11].LoadString(IDS_PISCES);// = "Pisces";

	m_sSignNamesShort[0] = "Ari";
	m_sSignNamesShort[1] = "Tau";
	m_sSignNamesShort[2] = "Gem";
	m_sSignNamesShort[3] = "Can";
	m_sSignNamesShort[4] = "Leo";
	m_sSignNamesShort[5] = "Vir";
	m_sSignNamesShort[6] = "Lib";
	m_sSignNamesShort[7] = "Sco";
	m_sSignNamesShort[8] = "Sag";
	m_sSignNamesShort[9] = "Cap";
	m_sSignNamesShort[10] = "Aqu";
	m_sSignNamesShort[11] = "Pis";
	
	m_sBodyNames[0].LoadString(IDS_SUN);// = "Sun";
	m_sBodyNames[1].LoadString(IDS_MOON);// = "Moon";
	m_sBodyNames[2].LoadString(IDS_MERCURY);// = "Mercury";
	m_sBodyNames[3].LoadString(IDS_VENUS);// = "Venus";
	m_sBodyNames[4].LoadString(IDS_ASC_NODE);// = "Asc Node";
	m_sBodyNames[5].LoadString(IDS_MARS);// = "Mars";
	m_sBodyNames[6].LoadString(IDS_JUPITER);// = "Jupiter";
	m_sBodyNames[7].LoadString(IDS_SATURN);// = "Saturn";
	m_sBodyNames[8].LoadString(IDS_URANUS);// = "Uranus";
	m_sBodyNames[9].LoadString(IDS_NEPTUNE);// = "Neptune";
	m_sBodyNames[10].LoadString(IDS_PLUTO);// = "Pluto";
}

CChart::~CChart()
{
}


BEGIN_MESSAGE_MAP(CChart, CWnd)
	//{{AFX_MSG_MAP(CChart)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChart message handlers

//	Calculates houses using the Koch method
//	fill double m_dHouse[14] with house positions
void CChart::CalculateHouses(CPlanetTime* time)
{
	convert Convert;
	astrocalc Astrocalc;

	double H[4], P[4], F[4], R[4], M[4];
	double RAMC, e, cose, Pi60, Pi30, MC, Asc;
	double pi;
	double tanLat;
	double temp;
	int i;

	pi = Convert.Pi();
	Pi60 = pi / (double)3;
	Pi30 = Pi60 / (double)2;
	tanLat = tan(time->m_dLatitude);

//	Right Ascension of the Mid-Heaven
	RAMC = Astrocalc.apparSiderealRadian(time->m_dJulianDay) -
									 time->m_dLongitude;
	RAMC = Convert.radianPositiveValue(RAMC);
	e = Astrocalc.trueObliquityOfEcliptic(time->m_dJulianDay);
	cose = cos(e);

//	Mid-Heaven
	MC = atan2(tan(RAMC), cose);
	MC = Convert.radianPositiveValue(MC);

//	Ascendant
	Asc = atan2(cos(RAMC), -(tanLat * sin(e) + sin(RAMC) * cose));
	Asc = Convert.radianPositiveValue(Asc);

//	Intermediates
	H[0] = Pi30;
	H[1] = Pi60;
	H[2] = Pi60 + Pi60;
	H[3] = H[2] + Pi30;
	F[0] = RAMC + Pi30;
	F[1] = RAMC + Pi60;
	F[2] = F[1] + Pi60;
	F[3] = F[2] + Pi30;

	for(i=0; i<4; i++)
	{
		P[i] = atan(tanLat * sin(H[i]));
		M[i] = atan2(tan(P[i]), cos(F[i]));
		R[i] = atan2(tan(F[i]) * cos(M[i]), cos(M[i] + e));
	}

//	The house positions.  Need [0] and [13] for later calculations
	m_dHouse[1] = Asc;
	m_dHouse[2] = R[2];
	m_dHouse[3] = R[3];
	m_dHouse[4] = MC + pi;
	m_dHouse[5] = R[0] + pi;
	m_dHouse[6] = R[1] + pi;
	m_dHouse[7] = Asc + pi;
	m_dHouse[8] = R[2] + pi;
	m_dHouse[9] = R[3] + pi;
	m_dHouse[10] = MC;
	m_dHouse[11] = R[0];
	m_dHouse[12] = R[1];
	m_dHouse[0] = m_dHouse[12];
	m_dHouse[13] = m_dHouse[1];

	for (i=0; i<14; i++)
	{
		m_dHouse[i] = Convert.radianReduce(Convert.radianPositiveValue(m_dHouse[i]));
	}

//	For some reason, [4] and [10] can get reversed.  This kluge fixes it
	if ( !(m_dHouse[4] > m_dHouse[3] && m_dHouse[5] > m_dHouse[4]))
	{
		temp = m_dHouse[4];
		m_dHouse[4] = m_dHouse[10];
		m_dHouse[10] = temp;
	}
}

//	Find house for each body
//	int m_iBodyHouse[11] number of body house
//	double m_dBodyHousePosition[11] how far each body is in its house
void CChart::PlaceBodiesInHouses()
{
	int i, j;
	int done;

	for(i=0; i<11; i++)
	{
		done = 0;
		j = 1;
		while (done == 0)
		{//	First bit deals with the situation where house value goes
		 //	"around the corner" from 6.xx to 0.xx
			if(		m_dHouse[j] > m_dHouse[j+1]
			    &&	(	m_dBody[i] > m_dHouse[j]
					 ||	m_dBody[i] < m_dHouse[j+1]))
			{
				m_iBodyHouse[i] = j;
				m_dBodyHousePosition[i] = m_dBody[i] - m_dHouse[j];
				done = 1;
			}
			else if(	m_dBody[i] > m_dHouse[j]
					 &&	m_dBody[i] < m_dHouse[j+1])
			{
				m_iBodyHouse[i] = j;
				m_dBodyHousePosition[i] = m_dBody[i] - m_dHouse[j];
				done = 1;
			}
			j++;
			if(j == 14)
			{
				done = 1;
			}
		}
	}
}

//	For each body as calculated in CTimeLocation::calcHor(&m_pModelessHor->m_pChart),
//	find its sign.  These are eliterated in ::CChart.  0-30 degrees = Aries
//	int m_iBodySign[11] number of body sign
//	CString m_sBodySignLocation[11] name of body sign with value
void CChart::PlaceBodiesInSigns()
{
	convert Convert;

	double div, Pi30, dTemp;
	int i;
	CString sTemp;

	Pi30 = Convert.Pi() / (double)6;

	for(i=0; i<11; i++)
	{
		dTemp = m_dBody[i] / Pi30;
		div = floor(dTemp);
		sTemp = Convert.HMSToString(Convert.degreeToDMS(Convert.radianToDegree((dTemp - div) * Pi30)),"d", 2);
		m_sBodySignLocation[i] = sTemp + m_sSignNames[(int)div];
		m_iBodySign[i] = (int)div;
	}
}

//	For each house as calculated in ::CalculateHouses, find its sign.  These are
//	eliterated in ::CChart.  0-30 degrees = Aries
void CChart::PlaceHousesInSigns()
{
	convert Convert;

	double div, Pi30, dTemp;
	int i;
	CString sTemp;

	Pi30 = Convert.Pi() / (double)6;

	for(i=1; i<13; i++)
	{
		dTemp = m_dHouse[i] / Pi30;
		div = floor(dTemp);
		sTemp = Convert.HMSToString(Convert.degreeToDMS(Convert.radianToDegree((dTemp - div) * Pi30)),"d", 2);
		m_sHouseSign[i] = sTemp + " " + m_sSignNamesShort[(int)div];
	}
}

//	Use Angular Separation functionaslity to calculate aspects
//	Aspects are true separation including latitude of each body
//	Fills double m_dBodyAspect[55] angular separation of body pairs
void CChart::CalculateAspects()
{
	CAngularSeparation sep;

	int i, j, k;

	k = 0;

	for(i=0; i<10; i++)
	{
		for (j=i+1; j<11; j++)
		{
			m_dBodyAspect[k] = sep.CalculateAngularSeparation(m_dBody[i], m_dBody[j],
															  m_dBodyDec[i], m_dBodyDec[j]);
			k += 1;
		}
	}
	CChart::AnalyzeAspects();
}

//	Decides if each aspect has astrological value
//	Fills int m_iBodyAspect[55] 0/1 : no aspect / aspect
//	Fills CString m_sBodyAspect[55] string version of m_dBodyAspect[55] but
//	only if m_iBodyAspect[i] is 1
void CChart::AnalyzeAspects()
{
	convert Convert;

	double edge[19];
	double Pi;
	int i;

	Pi = Convert.Pi();

	edge[0] = (double)0;
	edge[1] = Pi * (double)1 / (double)180;
	edge[2] = Pi * (double)10 / (double)180;
	edge[3] = Pi * (double)25 / (double)180;
	edge[4] = Pi * (double)35 / (double)180;
	edge[5] = Pi * (double)40 / (double)180;
	edge[6] = Pi * (double)50 / (double)180;
	edge[7] = Pi * (double)52 / (double)180;
	edge[8] = Pi * (double)68 / (double)180;
	edge[9] = Pi * (double)71.5 / (double)180;
	edge[10] = Pi * (double)72.5 / (double)180;
	edge[11] = Pi * (double)82 / (double)180;
	edge[12] = Pi * (double)98 / (double)180;
	edge[13] = Pi * (double)110 / (double)180;
	edge[14] = Pi * (double)130 / (double)180;
	edge[15] = Pi * (double)142 / (double)180;
	edge[16] = Pi * (double)158 / (double)180;
	edge[17] = Pi * (double)170 / (double)180;
	edge[18] = Pi * (double)180 / (double)180;

	for(i=0; i<55; i++)
	{
		if(		m_dBodyAspect[i] > edge[0]
			&&  m_dBodyAspect[i] < edge[1])
		{
			m_iBodyAspect[i] = 1;
			CChart::RadToString(m_dBodyAspect[i], &m_sBodyAspect[i]);
		}
		else if(	m_dBodyAspect[i] > edge[1]
				&&  m_dBodyAspect[i] < edge[2])
		{
			m_iBodyAspect[i] = 2;
			CChart::RadToString(m_dBodyAspect[i], &m_sBodyAspect[i]);
		}
		else if(	m_dBodyAspect[i] > edge[3]
				&&  m_dBodyAspect[i] < edge[4])
		{
			m_iBodyAspect[i] = 3;
			CChart::RadToString(m_dBodyAspect[i], &m_sBodyAspect[i]);
		}
		else if(	m_dBodyAspect[i] > edge[5]
				&&  m_dBodyAspect[i] < edge[6])
		{
			m_iBodyAspect[i] = 4;
			CChart::RadToString(m_dBodyAspect[i], &m_sBodyAspect[i]);
		}
		else if(	m_dBodyAspect[i] > edge[7]
				&&  m_dBodyAspect[i] < edge[8])
		{
			m_iBodyAspect[i] = 5;
			CChart::RadToString(m_dBodyAspect[i], &m_sBodyAspect[i]);
		}
		else if(	m_dBodyAspect[i] > edge[9]
				&&  m_dBodyAspect[i] < edge[10])
		{
			m_iBodyAspect[i] = 6;
			CChart::RadToString(m_dBodyAspect[i], &m_sBodyAspect[i]);
		}
		else if(	m_dBodyAspect[i] > edge[11]
				&&  m_dBodyAspect[i] < edge[12])
		{
			m_iBodyAspect[i] = 7;
			CChart::RadToString(m_dBodyAspect[i], &m_sBodyAspect[i]);
		}
		else if(	m_dBodyAspect[i] > edge[13]
				&&  m_dBodyAspect[i] < edge[14])
		{
			m_iBodyAspect[i] = 8;
			CChart::RadToString(m_dBodyAspect[i], &m_sBodyAspect[i]);
		}
		else if(	m_dBodyAspect[i] > edge[15]
				&&  m_dBodyAspect[i] < edge[16])
		{
			m_iBodyAspect[i] = 9;
			CChart::RadToString(m_dBodyAspect[i], &m_sBodyAspect[i]);
		}
		else if(	m_dBodyAspect[i] > edge[17]
				&&  m_dBodyAspect[i] < edge[18])
		{
			m_iBodyAspect[i] = 10;
			CChart::RadToString(m_dBodyAspect[i], &m_sBodyAspect[i]);
		}
		else
		{
			m_iBodyAspect[i] = 0;
		}
	}
}

//	Converts double value in radians to string value DMS
void CChart::RadToString(double value, CString *sNum)
{
	convert Convert;
	double temp;

	temp = Convert.degreeToDMS(Convert.radianToDegree(value));
	*sNum = Convert.HMSToString(temp, "", 1);
}

//	Make strings for each body
//	CString m_sBodyString[11] set of "Venus 12 Gem 26 R" strings
void CChart::MakeBodyStrings()
{
	CString sTemp;
	int i;

	for (i=0; i<11; i++)
	{
		m_sBodyString[i] = m_sBodyNames[i] + " " + m_sBodySignLocation[i] + " " + m_sRetrograde[i];
	}
}

//	Add up number of bodies in each section
void CChart::CalculateTriplicities()
{
	int i;
	int iNumMasculine, iNumFeminine, iNumCardinal = 0;
	int iNumFixed, iNumMutable, iNumFire, iNumEarth =0;
	int iNumAir, iNumWater, err;
	//  LS 31 Jan 2019
	//  increased to allow for null termination and in _itoa_s call below
	char buffer[4];

	iNumMasculine = 0;
	iNumFeminine = 0;

	iNumCardinal = 0;
	iNumFixed = 0;
	iNumMutable = 0;

	iNumFire =0;
	iNumEarth =0;
	iNumAir =0;
	iNumWater =0;

	for(i=0; i<11; i++)
	{
		if(i != 4)
		{
			switch( m_iBodySign[i] )
			{
			case 0:
				iNumMasculine += 1;
				iNumCardinal += 1;
				iNumFire +=1;
				break;
			case 1:
				iNumFeminine += 1;
				iNumFixed += 1;
				iNumEarth +=1;
				break;
			case 2:
				iNumMasculine += 1;
				iNumMutable += 1;
				iNumAir +=1;
				break;
			case 3:
				iNumFeminine += 1;
				iNumCardinal += 1;
				iNumWater +=1;
				break;
			case 4:
				iNumMasculine += 1;
				iNumFixed += 1;
				iNumFire +=1;
				break;
			case 5:
				iNumFeminine += 1;
				iNumMutable += 1;
				iNumEarth +=1;
				break;
			case 6:
				iNumMasculine += 1;
				iNumCardinal += 1;
				iNumAir +=1;
				break;
			case 7:
				iNumFeminine += 1;
				iNumFixed += 1;
				iNumWater +=1;
				break;
			case 8:
				iNumMasculine += 1;
				iNumMutable += 1;
				iNumFire +=1;
				break;
			case 9:
				iNumFeminine += 1;
				iNumCardinal += 1;
				iNumEarth +=1;
				break;
			case 10:
				iNumMasculine += 1;
				iNumFixed += 1;
				iNumAir +=1;
				break;
			case 11:
				iNumFeminine += 1;
				iNumMutable += 1;
				iNumWater +=1;
				break;
			}
		}
	}
//	_itoa(iNumMasculine, buffer,10);
	err = _itoa_s(iNumMasculine, buffer, 4, 10);
	m_sNumMasculine = buffer;

	err = _itoa_s(iNumFeminine, buffer, 4, 10);
	m_sNumFeminine = buffer;

	err = _itoa_s(iNumCardinal, buffer, 4, 10);
	m_sNumCardinal = buffer;

	err = _itoa_s(iNumFixed, buffer, 4, 10);
	m_sNumFixed = buffer;

	err = _itoa_s(iNumMutable, buffer, 4, 10);
	m_sNumMutable = buffer;

	err = _itoa_s(iNumFire, buffer, 4, 10);
	m_sNumFire = buffer;

	err = _itoa_s(iNumEarth, buffer, 4, 10);
	m_sNumEarth = buffer;

	err = _itoa_s(iNumAir, buffer, 4, 10);
	m_sNumAir = buffer;

	err = _itoa_s(iNumWater, buffer, 4, 10);
	m_sNumWater = buffer;
}
