// astrotime.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "astrotime.h"
#include <math.h>
#include "convert.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// astrotime

astrotime::astrotime()
{
}

astrotime::~astrotime()
{
}


BEGIN_MESSAGE_MAP(astrotime, CWnd)
	//{{AFX_MSG_MAP(astrotime)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// astrotime message handlers


//	Calculates the Julian day at 0 hours UT on the date given.
//	0 hour UT is noon at Greenwich.  0 UT = 12 TD.
//	See Meeus Ch 7 P. 59.

double astrotime::calcJulianDay(double year, double month, double day)
{
	double cat, dog, julDay;

	if(month < 2.5)
	{
		year -= (double)1;
		month += (double)12;
	}
	cat = floor(year / (double)100);
	dog = (double)2 - cat + floor(cat / (double)4);
	if (year <= 1581) dog = 0;
	if (year == 1582 && month == 10 && day <= 4) dog = 0;
	if (year == 1582 && month < 10) dog = 0;
	julDay = floor((double)365.25 * (year + (double)4716)) +
		floor((double)30.6001 * (month + (double)1)) +
		day + dog - (double)1524.5;
	return (julDay);
}

//	Finds the calendar date from julian date
void astrotime::calcYearMonthDay(double JD, double &year, double &month,
						  double &day)
{
	convert Convert;
	double alpha, A, B, C, D, E, F, junk, bInt, Z;

	JD += 0.5;
	F = Convert.LSmodf(JD, &Z);

	if(Z < 2299161)
	{
		A = Z;
	}
	else
	{
		junk = Convert.LSmodf((Z - 1867216.25) / 36524.25, &alpha);
		junk = Convert.LSmodf((alpha / 4), &bInt);
		A = Z + 1 + alpha - bInt;
	}
	B = A + 1524;
	junk = Convert.LSmodf((B - 122.1) / 365.25, &C);
	junk = Convert.LSmodf(C * 365.25, &D);
	junk = Convert.LSmodf((B - D) / 30.6001, &E);

	junk = Convert.LSmodf(30.6001 * E, &bInt);

	day = B - D - bInt + F;
	if(E < 14)
	{
		month = E - 1;
	}
	else
	{
		month = E - 13;
	}
	if( month > 2)
	{
		year = C - 4716;
	}
	else
	{
		year = C - 4715;
	}

}

//	Calculates decimal year (2002.365) from Julian date
double astrotime::calcDecimalYearFromJulianDay(double julDay)
{
	double year, month, day;
	double decimalYear;

	calcYearMonthDay(julDay, year, month, day);
	decimalYear = calcDecimalYearFromYearMonthDay(year, month, day);
	return decimalYear;
}

double astrotime::calcDecimalYearFromYearMonthDay(double year,
												  double month,
												  double day)
{
	bool leap_year;
	double leap_day, date;
	double aggregate_first_day_of_month[13];
	double decimal_year;
	double remainder;

	aggregate_first_day_of_month[1] = 0;
	aggregate_first_day_of_month[2] = 31;
	aggregate_first_day_of_month[3] = 59;
	aggregate_first_day_of_month[4] = 90;
	aggregate_first_day_of_month[5] = 120;
	aggregate_first_day_of_month[6] = 151;
	aggregate_first_day_of_month[7] = 181;
	aggregate_first_day_of_month[8] = 212;
	aggregate_first_day_of_month[9] = 243;
	aggregate_first_day_of_month[10] = 273;
	aggregate_first_day_of_month[11] = 304;
	aggregate_first_day_of_month[12] = 334;

	leap_year = false;
	remainder = fmod(year, 100.);
	if(0. == remainder)//divisible by 100 (century year)
	{
		if(!fmod(year/100., 4.))//divisible by 400
		{
			leap_year = true;
		}
	}
	else if(!fmod(year, 4.))
	{
		leap_year = true;
	}

	if(leap_year && month > 2)
	{
		leap_day = 1.;
	}
	else
	{
		leap_day = 0.;
	}

	date = aggregate_first_day_of_month[(int)month] + day + leap_day;
	if (leap_year)
	{
		decimal_year = year + (date/366.0);
	}
	else
	{
		decimal_year = year + (date/365.0);
	}
	return(decimal_year);
}

//	Calculates the Julian day (JDE) at 0 hours TD on the date given.
//	TD = UT + deltaT.  (deltaT is calculated below).
//	See Meeus Ch 7 P. 59.
double astrotime::calcJulianDayEphemeris(double julDay)
{
	double JDE, delT;

	delT = astrotime::deltaT(julDay);
	delT /= 86400;
	JDE = julDay + delT;

	return(JDE);
}

double astrotime::calcJulianDayFromJDE(double JDE)
{
	double julDay, delT;

	delT = astrotime::deltaT(JDE);
	delT /= 86400;
	julDay = JDE - delT;

	return(julDay);
}


//	Calculates the Julian days from 2000 January 1 00:00:00 UT.

double astrotime::calcJulianDays2000(double julDay)
{
	double from2000;

	from2000 = julDay - (double)2451545;

	return (from2000);
}

//	Calculates the Julian years from 2000 January 1 00:00:00 UT.

double astrotime::calcJulianYears2000(double julDay)
{
	double julYear;

	julYear = (julDay - (double)2451545) / (double)365.25;

	return (julYear);
}

//	Calculates the Julian centuries from 2000 January 1 00:00:00 UT.

double astrotime::calcJulianCenturies2000(double julDay)
{
	double julCentury;

	julCentury = (julDay - (double)2451545) / (double)36525;

	return (julCentury);
}

//	Calculates the Julian millenia from 2000 January 1 00:00:00 UT.

double astrotime::calcJulianMillenia2000(double julDay)
{
	double julMillenia;

	julMillenia = (julDay - (double)2451545) / (double)365250;

	return (julMillenia);
}

//	Calculates the difference in seconds (delta T) between UT and TD
//	as regressed by DLA Sawyer.
// redone 26 Feb 2018 to bring up to date
double astrotime::deltaT(double julDay)
{
	double T, dT, y, u;
	T = astrotime::calcJulianCenturies2000(julDay);

	if(julDay < 1538433)				//-4000 -> -499 inclusive
		dT = 2715.6 + 573.36 * T + 46.5 * T*T;

	else if(julDay < 1392332.70833333)	//-500 -> 899 inclusive
		dT = -2060768.4932884
			 -1229137.61131718*T
			 -313051.606448683*T*T
			 -43813.7347584692*T*T*T
			 -3544.68588216332*T*T*T*T
			 -147.849762829047*T*T*T*T*T
			 -0.460726961883343*T*T*T*T*T*T
			 +0.258973909376742*T*T*T*T*T*T*T
			 +0.0110473800720826*T*T*T*T*T*T*T*T
			 +8.44696683127749E-05*T*T*T*T*T*T*T*T*T
			 -6.27492112705661E-06*T*T*T*T*T*T*T*T*T*T
			 -1.89270434869852E-07*T*T*T*T*T*T*T*T*T*T*T
			 -1.67696909808115E-09*T*T*T*T*T*T*T*T*T*T*T*T;

	else if(julDay < 2312752.70833333)	// 900 -> 1619 inclusive
		dT = 239129.669721566
			 +298947.171031704*T
			 +153225.830332569*T*T
			 +40902.8986453687*T*T*T
			 +6075.49809297458*T*T*T*T
			 +608.391705087795*T*T*T*T*T
			 +93.6100401791791*T*T*T*T*T*T
			 +18.4751226597234*T*T*T*T*T*T*T
			 +1.90016910907799*T*T*T*T*T*T*T*T
			 +0.016841760089551*T*T*T*T*T*T*T*T*T
			 -0.0138409712080649*T*T*T*T*T*T*T*T*T*T
			 -0.00114147782643979*T*T*T*T*T*T*T*T*T*T*T
			 -2.93552429257232E-05*T*T*T*T*T*T*T*T*T*T*T*T;

	else if(julDay < 2344528.70833333)	//1620 -> 1706 inclusive
		dT = -895431.751540955
			 -1007387.9447492*T
			 -319712.297567507*T*T
			 +4009.21957615807*T*T*T
			 +3005.39853650309*T*T*T*T
			 -6587.0580005133*T*T*T*T*T
			 -55.6974799182472*T*T*T*T*T*T
			 +1029.6475933031*T*T*T*T*T*T*T
			 +255.862148180868*T*T*T*T*T*T*T*T
			 +18.8704052700327*T*T*T*T*T*T*T*T*T;

	else if(julDay < 2374479.70833333)	//1707 -> 1788 inclusive
		dT = -18628.9793815954
			 -38082.7531057139*T
			 -27849.5141293754*T*T
			 -6601.87492030024*T*T*T
			 +1370.66750304681*T*T*T*T
			 +425.84676003162*T*T*T*T*T
			 -431.028332503418*T*T*T*T*T*T
			 -234.922101340191*T*T*T*T*T*T*T
			 -43.7726703172452*T*T*T*T*T*T*T*T
			 -2.88956134220909*T*T*T*T*T*T*T*T*T;

	else if(julDay < 2396027.70833333)	//1789 -> 1847 inclusive
		dT = -68999.8630845876
			 -104731.463988645*T
			 -10858.1810900178*T*T
			 +6125.71623631057*T*T*T
			 -71888.7141141011*T*T*T*T
			 -57506.8031966378*T*T*T*T*T
			 +11234.0539025314*T*T*T*T*T*T
			 +26786.6758155007*T*T*T*T*T*T*T
			 +10289.4136186433*T*T*T*T*T*T*T*T
			 +1293.720409348*T*T*T*T*T*T*T*T*T;

	else if(julDay < 2414655.70833333)	//1848 -> 1898 inclusive
		dT = 1381987.45386384
			 +6549817.565034*T
			 +12123343.412324*T*T
			 +9999894.62892262*T*T*T
			 +1427419.07627713*T*T*T*T
			 -3773248.56328164*T*T*T*T*T
			 -2851441.84346529*T*T*T*T*T*T
			 -703227.85603993*T*T*T*T*T*T*T
			 +14816.501538687*T*T*T*T*T*T*T*T
			 +22887.7287877309*T*T*T*T*T*T*T*T*T;

	else if(julDay < 2430725.70833333)	//1899 -> 1942 inclusive
		dT = 13694.7203163728
			 +107871.826402786*T
			 +334593.301573991*T*T
			 +459302.570149165*T*T*T
			 +70314.8843323636*T*T*T*T
			 -630500.457903645*T*T*T*T*T
			 -848900.17253533*T*T*T*T*T*T
			 -451548.847013962*T*T*T*T*T*T*T
			 -76481.6999726037*T*T*T*T*T*T*T*T
			 +8098.57162765298*T*T*T*T*T*T*T*T*T;

	else if(julDay < 2459215.70833333)	//1943 -> 2020 inclusive
		dT = 63.37224805767
			 + 43.3132053321201*T
			 - 209.860668910781*T*T
			 - 339.246616233897*T*T*T
			 + 5435.63056617202*T*T*T*T
			 + 28920.3958046024*T*T*T*T*T
			 - 29086.6528386614*T*T*T*T*T*T
			 - 427720.614416852*T*T*T*T*T*T*T
			 - 869870.568508364*T*T*T*T*T*T*T*T
			 - 549178.495444595*T*T*T*T*T*T*T*T*T;

/*old  replaced feb 2018
		dT = 63.2849433551292
			 +43.4292484838584*T
			 -169.281146130534*T*T
			 -2.58016163169373*T*T*T
			 +5763.2881081001*T*T*T*T
			 +24039.3356948382*T*T*T*T*T
			 -47522.6581032968*T*T*T*T*T*T
			 -449088.138000135*T*T*T*T*T*T*T
			 -869874.284519008*T*T*T*T*T*T*T*T
			 -539042.541087767*T*T*T*T*T*T*T*T*T;
			 */

	else if (julDay < 2469807.70833333) {	//greater than 2020 less than 2050, slowly increasing
		y = calcDecimalYearFromJulianDay(julDay) - 2000;
		dT = 62.92 + 0.32217 * y + 0.005589 * y*y;
//OLD		dT = 63.46924509 + 61.96840934 * T;
	}
	else if (julDay < 2506331.70833333)	{ // greater than 2050 less than 2150
		y = calcDecimalYearFromJulianDay(julDay);
		double g = (5+8) ^ 2;
		dT = -20 + 32 * (  pow ((y - 1820) / 100,2) ) - 0.5628 * (2150 - y);
	}
	else { // greater than 2150
		y = calcDecimalYearFromJulianDay(julDay);
		u = (y - 1820) / 100;
		dT = -20 + 32 * u * u;
	}

/*	
From delta T page from NASA
	https://eclipse.gsfc.nasa.gov/SEhelp/deltatpoly2004.html
	y is year + (month-.5)/12
	ΔT = 62.92 + 0.32217 * t + 0.005589 * t^2
	where: t = y - 2000

This expression is derived from estimated values of ΔT in the years 2010 and 2050
The value for 2010 (66.9 seconds) is based on a linearly extrapolation from 2005 using 0.39 seconds/year (average from 1995 to 2005)
The value for 2050 (93 seconds) is linearly extrapolated from 2010 using 0.66 seconds/year (average rate from 1901 to 2000).

Between years 2050 and 2150, calculate:

	ΔT = -20 + 32 * ((y-1820)/100)^2 - 0.5628 * (2150 - y)

The last term is introduced to eliminate the discontinuity at 2050.

After 2150, calculate:

	ΔT = -20 + 32 * u^2
	where:	u = (year-1820)/100
*/

	return(dT);
}

//	Input Year, Month, Date and Hour as doubles, returns string
CString astrotime::TimeDisplayUT(double m_dYear, double m_dMonth,
								 double m_dDate, double m_dHour,
								 int precision)
{
	CString value, chMonth, cHour, m_Temp, cDate, cYear;
	double m_ThisHour;
	int  decimal, sign, err;
	char *buffer = 0;
 
	convert Convert;

	if(m_dMonth + 0.1 < 13) chMonth.LoadString(IDS_DECEMBER);
	if(m_dMonth + 0.1 < 12) chMonth.LoadString(IDS_NOVEMBER);
	if(m_dMonth + 0.1 < 11) chMonth.LoadString(IDS_OCTOBER);
	if(m_dMonth + 0.1 < 10) chMonth.LoadString(IDS_SEPTEMBER);
	if(m_dMonth + 0.1 < 9)  chMonth.LoadString(IDS_AUGUST);
	if(m_dMonth + 0.1 < 8)  chMonth.LoadString(IDS_JULY);
	if(m_dMonth + 0.1 < 7)  chMonth.LoadString(IDS_JUNE);
	if(m_dMonth + 0.1 < 6)  chMonth.LoadString(IDS_MAY);
	if(m_dMonth + 0.1 < 5)  chMonth.LoadString(IDS_APRIL);
	if(m_dMonth + 0.1 < 4)  chMonth.LoadString(IDS_MARCH);
	if(m_dMonth + 0.1 < 3)  chMonth.LoadString(IDS_FEBRUARY);
	if(m_dMonth + 0.1 < 2)  chMonth.LoadString(IDS_JANUARY);

	m_ThisHour = Convert.hourToHMS(m_dHour);
	cHour = Convert.HMSToString(m_ThisHour, 'h', precision);

	// DLAS 18Feb9
//		buffer = _fcvt( m_dDate, 7, &decimal, &sign );

	buffer = (char*)malloc(_CVTBUFSIZE);
	err = _fcvt_s(buffer, _CVTBUFSIZE, m_dDate, 7, &decimal, &sign);
	if (err != 0) {
		printf("_fcvt_s failed with error code %d\n", err);
		exit(1);
	}
	cDate = (CString)buffer;

	m_Temp = cDate.Left(decimal);
	cDate = m_Temp;

	// DLAS 18Feb9
//	buffer = _fcvt( m_dYear, 7, &decimal, &sign );
	err = _fcvt_s(buffer, _CVTBUFSIZE, m_dYear, 7, &decimal, &sign);
	if (err != 0) {
		printf("_fcvt_s failed with error code %d\n", err);
		exit(1);
	}


	if(sign == 1)
	{
		cYear = '-';
	}
	else
	{
		cYear.Empty();
	}
	m_Temp = (CString)buffer;
	free(buffer);
	cYear = cYear + m_Temp.Left(decimal);

	value = cHour + " " + cDate + " " + chMonth + ", " + cYear;
	return value;
}