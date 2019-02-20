// PlanetTime.cpp : implementation file
//

#include "stdafx.h"
#include "PlanetTime.h"
#include "resource.h"
#include "convert.h"
#include "astrotime.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlanetTime

CPlanetTime::CPlanetTime()
{
}

CPlanetTime::~CPlanetTime()
{
}


BEGIN_MESSAGE_MAP(CPlanetTime, CWnd)
	//{{AFX_MSG_MAP(CPlanetTime)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPlanetTime message handlers

//	Calculates the date (day + time) as a decimal i.e. 27.4526
void CPlanetTime::convertToDoubleGMT(int precision)
{
	CString hrString, minString, tm_sHour, m_Temp, buffer;

	CPlanetTime::makeGMTHour();
	m_dDeciHour = m_dHour / (double) 24;
	m_dDate = m_dDay + m_dDeciHour;
}

//	Calculates the Julian day at 0 hours UT on the date given.
//	0 hour UT is noon at Greenwich.  0 UT = 12 TD.
//	See Meeus Ch 7 P. 59.
void CPlanetTime::calcJulianDay()
{
	astrotime Astrotime;

	m_dJulianDay = Astrotime.calcJulianDay(m_dYear, m_dMonth, m_dDate);
}

//	Makes date string like "7h 45m 06s pm 23 July 2003"
CString CPlanetTime::DateLongString()
{
	CPlanetTime::calcMonthName();
	sDateLongString = m_sHourLongString + " " + m_sAmPm + "m" + " " + m_sDay +
					  " " + m_sMonthName + ", " + m_sYear;
	return sDateLongString;
}

//	Makes date string like "23 July 2003"
CString CPlanetTime::DateShortString()
{
	CPlanetTime::calcMonthName();
	sDateShortString = m_sDay + " " + m_sMonthName + ", " + m_sYear;
	return sDateShortString;
}

//	Given integer value for month (as string), find string name
void CPlanetTime::calcMonthName()
{
	if(m_sMonth == "1") m_sMonthName.LoadString(IDS_JANUARY);// = "January";
	if(m_sMonth == "2") m_sMonthName.LoadString(IDS_FEBRUARY);// = "February";
	if(m_sMonth == "3") m_sMonthName.LoadString(IDS_MARCH);// = "March";
	if(m_sMonth == "4") m_sMonthName.LoadString(IDS_APRIL);// = "April";
	if(m_sMonth == "5") m_sMonthName.LoadString(IDS_MAY);// = "May";
	if(m_sMonth == "6") m_sMonthName.LoadString(IDS_JUNE);// = "June";
	if(m_sMonth == "7") m_sMonthName.LoadString(IDS_JULY);// = "July";
	if(m_sMonth == "8") m_sMonthName.LoadString(IDS_AUGUST);// = "August";
	if(m_sMonth == "9") m_sMonthName.LoadString(IDS_SEPTEMBER);// = "September";
	if(m_sMonth == "10") m_sMonthName.LoadString(IDS_OCTOBER);// = "October";
	if(m_sMonth == "11") m_sMonthName.LoadString(IDS_NOVEMBER);// = "November";
	if(m_sMonth == "12") m_sMonthName.LoadString(IDS_DECEMBER);// = "December";

}

//	This converts the input data into Greenwich time
void CPlanetTime::makeGMTHour()
{
	convert Convert;

//	If am and between 12 and 13, subtract 12.  So if 14 and am, still get 14
//	and assume am is a mistake.
//	If pm and less than 12, add 12.  If 14 and pm, do nothing
	if(m_sAmPm.GetLength() != 0)
	{
	if(m_sAmPm[0] == 'a' && m_dHour >= 12.0 && m_dHour < 13.0) m_dHour -= (double)12.0;
	if(m_sAmPm[0] == 'p' && m_dHour < 12.0) m_dHour += (double)12.0;
	}

	if (m_sDst.GetLength() != 0)
	{
	if(m_sDst[0] == 'y') m_dHour -= (double)1.0;
	}
	m_dHour += m_dTimeZone;

//NEED TO ADJUST here for going over or under a day


	CPlanetTime::hourAdjust(m_dYear, m_dMonth, m_dDay, m_dHour);
	
	m_dHour = Convert.HMSToHour(m_dHour);
}

//	Given year, month, day and hour, adjusts all so that 
//	hour lies between 0 and 24.
void CPlanetTime::hourAdjust(double &dYear, double &dMonth, 
							 double &dDay, double &dHour)
{
	convert Convert;

	double cat,testHour, testMonth, testYear, testYear2;
	int iTestMonth;

	cat = Convert.LSmodf(dHour, &testHour);

	if (testHour < 0)
	{//	Time is negative, so you are looking at the day before so if 
	 //	you are at the beginning of a month, you will need to adjust
	 //	and if you were Jan1, then you will need a new year as well
		dHour += (double)24;
		dDay -= (double)1;
		if(dDay < 1)
		{
			dMonth -= (double)1;
			
			cat = Convert.LSmodf(dMonth, &testMonth);
			iTestMonth = (int)testMonth;

			switch( iTestMonth )
			{
			case 0://	New year
				dYear -= (double)1;
				dMonth = (double)12;
				dDay = (double)31;
				break;
			case 1://	Go to January 31
				dDay = (double)31;
				break;
			case 2://	Go to February ?? adjust for leap year
				cat = Convert.LSmodf((dYear / 100),&testYear);
				
				if(cat == 0)
				{
					cat = Convert.LSmodf((testYear/4),&testYear2);
					if(cat == 0)
					{
						dDay = (double)29;
						break;
					}
					else
					{
						dDay = (double)28;
						break;
					}
				}//end of "if(cat == 0)"
				else 
				{
					cat = Convert.LSmodf((dYear / 4),&testYear);
					if(cat == 0) dDay = (double)29;
					else
						dDay = (double)28;
				}
				break;
			case 3://	Go to March 31
				dDay = (double)31;
				break;
			case 4://	Go to April 30
				dDay = (double)30;
				break;
			case 5://	Go to May 31
				dDay = (double)31;
				break;
			case 6://	Go to June 30
				dDay = (double)30;
				break;
			case 7://	Go to July 31
				dDay = (double)31;
				break;
			case 8://	Go to August 31
				dDay = (double)31;
				break;
			case 9://	Go to September 30
				dDay = (double)30;
				break;
			case 10://	Go to October 31
				dDay = (double)31;
				break;
			case 11://	Go to November 30
				dDay = (double)30;
				break;
			}// end of "switch( iTestMonth )
		}// end of "if(m_dDay < 1)"
	}//end of "if (testHour < 0)"

	if (testHour >= 24)
	{//	Time is positive and greater than 24 so you are into the
	 // next day so must adjust month and maybe year
		dHour -= (double)24;
		dDay += (double)1;
		
		cat = Convert.LSmodf(dMonth, &testMonth);
		iTestMonth = (int)testMonth;

		switch( iTestMonth )
		{
		case 1:// January
			if(dDay >= 32)
			{// becomes February
				dDay = (double)1;
				dMonth = (double)2;
				break;
			}
			else
			{
				break;
			}
		case 2:// February
			if(dDay >= 29 && dDay < 30)
			{// There are two kinds of February involving leap year
				cat = Convert.LSmodf((dYear / 100),&testYear);
				
				if(cat == 0)
				{
					cat = Convert.LSmodf((testYear/4),&testYear2);
					if(cat == 0)  //  This is a valid leap year
					{
						break;
					}
					else //  This is not a valid leap year
					{
						dDay = (double)1;
						dMonth = (double)3;
						break;
					}
				}
				else
				{
					cat = Convert.LSmodf((dYear / 4),&testYear);
					if(cat == 0)//  This is a valid leap year
					{
						break;
					}
					else//  This is not a valid leap year
					{
						dDay = (double)1;
						dMonth = (double)3;
						break;
					}
				}
			}
			if(dDay >=30)
			{
				dDay = (double)1;
				dMonth = (double)3;
				break;
			}
			else
			{
				break;
			}
		case 3:// March
			if(dDay >=32)
			{// becomes april
				dDay = (double)1;
				dMonth = (double)4;
				break;
			}
			else
			{
				break;
			}
		case 4:// April
			if(dDay >=31)
			{// becomes May
				dDay = (double)1;
				dMonth = (double)5;
				break;
			}
			else
			{
				break;
			}
		case 5:// May
			if(dDay >=32)
			{// becomes June
				dDay = (double)1;
				dMonth = (double)6;
				break;
			}
			else
			{
				break;
			}
		case 6:// June
			if(dDay >=31)
			{// becomes July
				dDay = (double)1;
				dMonth = (double)7;
				break;
			}
			else
			{
				break;
			}
		case 7:// July
			if(dDay >=32)
			{// becomes August
				dDay = (double)1;
				dMonth = (double)8;
				break;
			}
			else
			{
				break;
			}
		case 8:// August
			if(dDay >=32)
			{// becomes September
				dDay = (double)1;
				dMonth = (double)9;
				break;
			}
			else
			{
				break;
			}
		case 9:// September
			if(dDay >=31)
			{// becomes October
				dDay = (double)1;
				dMonth = (double)10;
				break;
			}
			else
			{
				break;
			}
		case 10:// October
			if(dDay >=32)
			{// becomes November
				dDay = (double)1;
				dMonth = (double)11;
				break;
			}
			else
			{
				break;
			}
		case 11:// November
			if(dDay >=31)
			{// becomes December
				dDay = (double)1;
				dMonth = (double)12;
				break;
			}
			else
			{
				break;
			}
		case 12:// December
			if(dDay >=32)
			{// becomes January of a new year
				dDay = (double)1;
				dMonth = (double)1;
				dYear += (double)1;
				break;
			}
			else
			{
				break;
			}
		}// end of "switch( iTestMonth )"
	}// end of "if (testHour >= 24)"
}

//	Used in Almanac for time adjustment value
void CPlanetTime::FractionOfJulianDay()
{
	m_dFractionJulianDay =	 m_dYear * (double)365 +
							 m_dMonth * 30.5 +
							 m_dDay +
							 m_dHour / (double)24 +
							 m_dMinute / (double)1440 +
							 m_dSecond / (double)86400;
}

void CPlanetTime::ProcessLatLon()
{
	convert Convert;

	m_dLatitude = Convert.StringToDecimal(m_sLatitude);
	m_dLongitude = Convert.StringToDecimal(m_sLongitude);
}
