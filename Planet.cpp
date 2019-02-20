// Planet.cpp : implementation file
//

#include "stdafx.h"
#include "ArrayEx.h"
#include "resource.h"
#include "Planet.h"
#include "Sun.h"
#include "Moon.h"
#include "Mercury.h"
#include "Venus.h"
#include "Earth.h"
#include "Mars.h"
#include "Jupiter.h"
#include "Saturn.h"
#include "Uranus.h"
#include "Neptune.h"
#include "Pluto.h"

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "astrotime.h"
#include "astrocalc.h"
#include "convert.h"
#include <string.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlanet

CPlanet::CPlanet()
{

}

CPlanet::~CPlanet()
{
}


BEGIN_MESSAGE_MAP(CPlanet, CWnd)
	//{{AFX_MSG_MAP(CPlanet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPlanet message handlers

void CPlanet::sun()
{
	m_iName = IDS_SUN;
}

void CPlanet::moon()
{
	m_iName = IDS_MOON;
}

void CPlanet::mercury()
{
	m_iName = IDS_MERCURY;
}

void CPlanet::venus()
{
	m_iName = IDS_VENUS;
}

void CPlanet::earth()
{
	m_iName = IDS_EARTH;
}

void CPlanet::mars()
{
	m_iName = IDS_MARS;
}

void CPlanet::jupiter()
{
	m_iName = IDS_JUPITER;
}

void CPlanet::saturn()
{
	m_iName = IDS_SATURN;
}

void CPlanet::uranus()
{
	m_iName = IDS_URANUS;
}

void CPlanet::neptune()
{
	m_iName = IDS_NEPTUNE;
}

void CPlanet::pluto()
{
	m_iName = IDS_PLUTO;
}

void CPlanet::sunL()
{
	m_iName = IDS_SUN_LONGITUDE;
}

//	This calculates the position of the each body.  Sun and Moon are geocentric 
//	spherical true.  All planets are heliocentric spherical positions.  The last
//	one (i=11) is for Sun longitude calculation
//	Every time it goes through (per session) it keeps the calculated values.  If you
//	ask for a time that is within tolerance, you get the same value without having
//	to re-calculate.
void CPlanet::primaryBodyLocation(double julDay, double &planetL, double &planetB,
			  double &planetR)
{
	static CArrayEx< date_LBR_Values, date_LBR_Values > dateHolder;
	struct date_LBR_Values pBody;

	astrocalc Astrocalc;
	
	int i, flagGotOne;

	i = 0;
	flagGotOne = 0;

//	Here's where we check to see if we have this value already
	i=0;
	while (i < dateHolder.GetSize() && flagGotOne == 0)
	{
		if ( dateHolder[i].body == m_iName)
		{
			if(fabs(julDay - dateHolder[i].date) < .00000001)
			{
				planetL = dateHolder[i].pL;
				planetB = dateHolder[i].pB;
				planetR = dateHolder[i].pR;
				flagGotOne = 1;
			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}

	if(flagGotOne == 1)
	{
//	We already have these values, do nothing
	}
	else
	{
	if(m_iName == IDS_SUN)
	{
		CSun sun;
		sun.geocentricSphericalTrueSun(julDay, planetL, planetB, planetR);
	}
	else if (m_iName == IDS_MOON)
	{
		CMoon moon;
		moon.geocentricSphericalTrueMoon(julDay, planetL, planetB, planetR);
	}
	else if (m_iName == IDS_MERCURY)
	{
		CMercury merc;
		merc.heliocentricSphericalMercury(julDay, planetL, planetB, planetR);
	}
	else if (m_iName == IDS_VENUS)
	{
		CVenus venus;
		venus.heliocentricSphericalVenus(julDay, planetL, planetB, planetR);
	}
	else if (m_iName == IDS_EARTH)
	{
		CEarth earth;
		earth.heliocentricSphericalEarth(julDay, planetL, planetB, planetR);
	}
	else if (m_iName== IDS_MARS)
	{
		CMars mars;
		mars.heliocentricSphericalMars(julDay, planetL, planetB, planetR);
	}
	else if (m_iName == IDS_JUPITER)
	{
		CJupiter jupiter;
		jupiter.heliocentricSphericalJupiter(julDay, planetL, planetB, planetR);
	}
	else if (m_iName == IDS_SATURN)
	{
		CSaturn saturn;
		saturn.heliocentricSphericalSaturn(julDay, planetL, planetB, planetR);
	}
	else if (m_iName == IDS_URANUS)
	{
		CUranus uranus;
		uranus.heliocentricSphericalUranus(julDay, planetL, planetB, planetR);
	}
	else if (m_iName == IDS_NEPTUNE)
	{
		CNeptune neptune;
		neptune.heliocentricSphericalNeptune(julDay, planetL, planetB, planetR);
	}
	else if (m_iName == IDS_PLUTO)
	{
		CPluto pop;
		pop.heliocentricSphericalPluto(julDay, planetL, planetB, planetR);
	}
	else if (m_iName == IDS_SUN_LONGITUDE)
	{
		CSun sun;
		sun.geocentricLongitudeSun(julDay, planetL);
		sun.geocentricLatitudeSun(julDay, planetB);
		planetR = (double)0;
	}

	if (m_iName != IDS_MOON)
	{
		Astrocalc.convertToFk5(julDay, planetL, planetB, planetL, planetB);
	}

//	Store the calculated values in this array
	pBody.body = m_iName;
	pBody.date = julDay;
	pBody.pL = planetL;
	pBody.pB = planetB;
	pBody.pR = planetR;
	dateHolder.Add(pBody);
	}
}

//	Sun is not included, of course, and Moon heliocentric coord are not yet
//	calculated.  When they are, will need special handling here.  For the rest
//	primary is heliocentric, so just convert to Cartesian
void CPlanet::heliocentricCartesianPlanet(double julDay,
			 double &X, double &Y, double &Z)
{
	convert Convert;

	double L, B, R;

	CPlanet::primaryBodyLocation(julDay, L, B, R);
	Convert.sphericalToCartesian(L, B, R, X, Y, Z);
}

//	No allowance made for light time
void CPlanet::geocentricCartesianTruePlanet(double julDay,
			 double &Ex, double &Ey, double &Ez)
{
	CPlanet ernie;
	astrocalc Astrocalc;
	convert Convert;

	double L, B, R, earthL, earthB, earthR;

	CPlanet::primaryBodyLocation(julDay, L, B, R);
	
	if(m_iName == IDS_SUN || m_iName == IDS_MOON)
	{
		Convert.sphericalToCartesian(L, B, R, Ex, Ey, Ez);
	}
	else
	{
		ernie.earth();
		ernie.primaryBodyLocation(julDay, earthL, earthB, earthR);
		Astrocalc.geocentricCartesianTrue(L, B, R,
									  earthL, earthB, earthR,
									  Ex, Ey, Ez);
	}
}

//	No allowance made for light time
void CPlanet::geocentricSphericalTruePlanet(double julDay,
			 double &Lambda, double &Beta,
			 double &Radius)
{
	astrocalc Astrocalc;

	double Ex, Ey, Ez;

	if(m_iName == IDS_SUN || m_iName == IDS_MOON || m_iName == IDS_SUN_LONGITUDE)
	{
		CPlanet::primaryBodyLocation(julDay, Lambda, Beta, Radius);
	}
	else
	{
		CPlanet::geocentricCartesianTruePlanet(julDay, Ex, Ey, Ez);
		Astrocalc.cartesianToSpherical(Ex, Ey, Ez, Lambda, Beta, Radius);
	}
}

//	Allow for light time and this is where body appears to be
void CPlanet::geocentricSphericalAppPlanet(double julDay,
	 double &Lambda, double &Beta, double &Radius)
{
	convert Convert;
	CPlanet ernie;
	astrocalc Astrocalc;
	
	double earthL, earthB, earthR;
	double Ex, Ey, Ez, deltaLambda, deltaBeta;
	double dist, delT1, delT2, appJulDay, deltaPsi;

	CPlanet::primaryBodyLocation(julDay, Lambda, Beta, Radius);

	// different for the sun
	if(m_iName == IDS_SUN)
	{
	//  This is very accurate aberation calculation	
		CPlanet::sunDeltaLongitude(julDay, Radius, deltaLambda);
		Lambda  += deltaLambda;
	}
	else if(m_iName == IDS_MOON)
	{
	}
	else
	{
		ernie.earth();
		ernie.primaryBodyLocation(julDay, earthL, earthB, earthR);
		Astrocalc.geocentricCartesianTrue(Lambda, Beta, Radius,
									  earthL, earthB, earthR,
									  Ex, Ey, Ez);
		dist = sqrt(Ex * Ex + Ey * Ey + Ez * Ez);
		delT1 = (double)0.0057755183 * dist;
		delT2 = delT1;
		do
		{
			delT1 = delT2;
			appJulDay = julDay - delT1;
			CPlanet::primaryBodyLocation(appJulDay, Lambda, Beta, Radius);
			Astrocalc.geocentricCartesianTrue(Lambda, Beta, Radius,
										  earthL, earthB, earthR,
										  Ex, Ey, Ez);
			dist = sqrt(Ex * Ex + Ey * Ey + Ez * Ez);
			delT2 = (double)0.0057755183 * dist;
		}while (fabs(delT2 - delT1) > (double)0.0000000001);
		
		Astrocalc.cartesianToSpherical(Ex, Ey, Ez, Lambda, Beta, Radius);
		Astrocalc.aberration(julDay, Lambda, Beta, deltaLambda, deltaBeta);
		Lambda += deltaLambda;
		Beta += deltaBeta;
	}
	
		deltaPsi = Astrocalc.nutationInLongitude(julDay);
		Lambda += deltaPsi;
		Lambda = Convert.radianReduce(Lambda);
		Lambda = Convert.radianPositiveValue(Lambda);
}


void CPlanet::equatorialAppPlanet(double julDay,
	 double &Alpha, double &Delta, double &Radius)
{
	double Lambda, Beta;

	astrocalc Astrocalc;

	CPlanet::geocentricSphericalAppPlanet(julDay, Lambda, Beta, Radius);

	Astrocalc.eclipticToEquatorial(julDay, Lambda, Beta, Alpha, Delta);
}
//////////////////////////////////////////////////////////////////
//	After much testing and a discussion with John Letcher, I now
//	believe that this is working properly.  When a body passees to
//	within 15 degrees or so of the zenith, the resulting azimuth
//	changes very rapidly during transit.  The graph of azimuth when
//	this is happening is really weird looking.  If it bothers you,
//	don't look at it.
//////////////////////////////////////////////////////////////////

void CPlanet::azimuthAltitudePlanet(double julDay, double latitude,
	 double longitude, double &Azimuth, double &Altitude)
{
	double Alpha, Delta, Radius;

	CPlanet::equatorialAppPlanet(julDay, Alpha, Delta, Radius);
	CPlanet::azimuthAltitudeFromEquatorialApp(julDay,
										latitude, longitude,
										Alpha, Delta,
										Azimuth, Altitude);
}

void CPlanet::azimuthAltitudeFromEquatorialApp(double julDay,
									double latitude, double longitude,
									double Alpha, double Delta,
									double &Azimuth, double &Altitude)
{
	double siderealAngle, H;
	convert Convert;
	astrocalc Astrocalc;

	siderealAngle = Astrocalc.apparSiderealRadian(julDay);
	H = siderealAngle - longitude - Alpha;
	H = Convert.radianPositiveValue(H);

	Azimuth = atan2(sin(H), cos(H)*sin(latitude) - tan(Delta)*cos(latitude));
	Azimuth = Convert.radianPositiveValue(Azimuth);
	Azimuth += Convert.Pi();
	Azimuth = Convert.radianReduce(Azimuth);
	Altitude = asin(sin(latitude)*sin(Delta)+
			   cos(latitude)*cos(Delta)*cos(H));
}
//	Finds starting time for calculating transit from Meeus p97
void CPlanet::FindTransitFraction(double julDay, double longitude,
								  double *julDayZero, double *julDayZeroUT,
								  double *transitFraction, double *delta2,
								  double *radius2)
{
	astrotime Astrotime;
	astrocalc Astrocalc;
	convert Convert;
	double deltaT, appSidTime, alpha2;
	double cat, m_Pi;

	m_Pi = Convert.Pi();
	deltaT = Astrotime.deltaT(julDay);
	cat = Convert.LSmodf(julDay, julDayZeroUT);

//	Remember, julian days start at UT = .5 (noon) so to find julian day 
//	for UT .0 you must adjust julian day to .5
	*julDayZeroUT = *julDayZeroUT + (double)0.5;

//	This allows calculation of locations at UT zero
	*julDayZero = *julDayZeroUT - (deltaT / (double)86400);
	CPlanet::equatorialAppPlanet(*julDayZero, alpha2, *delta2, *radius2);
	

//	Find starting transit time
	appSidTime = Astrocalc.apparSiderealRadian(*julDayZeroUT);
	*transitFraction = (alpha2 + longitude - appSidTime)/((double)2 * m_Pi);
	*transitFraction = Convert.zeroToOne(*transitFraction);
}
void CPlanet::Find_m_dH0(double radm_h0, double latitude, double delta2,
							double *m_dH0)
{
	convert Convert;
	double m_dCosH0, m_Pi;

	m_Pi = Convert.Pi();
	m_dCosH0 = (sin(radm_h0) - sin(latitude)*sin(delta2))/
			   (cos(latitude)*cos(delta2));

	if		(m_dCosH0 < -1)	*m_dH0 = m_Pi;
	else if	(m_dCosH0 >  1)	*m_dH0 = 0;
	else					*m_dH0 = acos(m_dCosH0);
}

//////////////////////////////////////////////////////////////////////////
//	The Meeus method works OK, but falters somewhat when a body	        //
//	approaches the zenith and at high latitudes.  I have modified his	//
//  method a bit to deal with this and for the regular calculation as	//
//	well.																//
//	For all transit calculations and for low latitude rise and set		//
//  calculations, I make an initial estimate (from Meeus p. 97) and then//
//	move in on the true value in steps of 10 minutes.  In nearly every	//
//	case, this results in only 3 or 4 calculations of the location,		//
//	which is the time sink in this function.  Possible return values	//
//	are:																//
//		negative  actually happened the day before, so if you want the	//
//				  answer for today, check out tomorrow's value.  If		//
//				  tomorrows value is also negative, then take that value//
//				  (adjusted for today) otherwise, this is where the body//
//				  does not rise (or set or transit) today.				//
//		between 0 and 24												//
//		greater than 24 actually happens tomorrow, so if you want		//
//				  today's value, check out yesterday.  If  yesterday's	//
//				  value is also >24, then take that value (adjusted for	//
//				  today) otherwise, this is where the body does not rise//
//				  (or set or transit) today.							//
//	This negative and >24 value problem was solved by comparing			//
//	calculated values with Almanac values.								//
//	Because the method gets squirrely when the transit happens around	//
//	the zenith, I move the latitude away to get a better angle in these	//
//	situations (AdjustTransitParameters).								//
//	High latitude has situations where bodies are never up, always up	//
//	or rise or set twice in one day.  At high latitudes the curve of	//
//	altitude with time is sinusoidal (which means sometimes parabolic	//
//	and sometimes a straight line depending on what part of the curve	//
//	you are on and the shape of the curve at that latitude).  Sometimes	//
//	it has a high followed by a low and other times a low followed by a	//
//	high.  All of these situations are handled individually.			//
//																		//
//	'planet' is an integer:
//	Sun, Moon, Merc, Venus, Earth, Mars, Jup, Sat, Uran, Nep, Pluto		//
//	 0	   1	2		3	  4		5	  6		7	 8	  9		10		//
//	'timeCorrection' is minus the Time Zone,							//
//  'specialFlag' returns 2 or 6 if the planet has an extra rise or set	//
//////////////////////////////////////////////////////////////////////////

void CPlanet::riseSetTransitPlanet(double julDay, double latitude, double longitude,
	 double &hourAngleRise, double &hourAngleTransit, double &hourAngleSet,
	 double &hourAngleExtra, int planet, double timeCorrection, int &specialFlag)
{
	double delta2, radius2;
	double riseFraction, setFraction, transitFraction;
	double julDayZero, julDayZeroUT;
	double m_dH0;
	double m_Pi, radm_h0;
	double m_h0 = -0.566667;
	double julDayZeroUTTransit, julDayZeroUTRise, julDayZeroUTSet;
	double testValue, moonParallax;
	double timeAdjust = .0069444; /* = 10 minutes in 24 hours*/
	double transitValue, riseValue, setValue, dCalculationLatitude;
	double dTransitTimeAdjust;// = .0069444; /* = 10 minutes in 24 hours*/
	double newjulDayZeroUT, newjulDayZeroUTTransit;
	double currentRiseValue, currentSetValue, julDayH, tempJulDay;

	int rFlag, sFlag, tFlag, tempFlag;
	int flag, done;
	int riseSetFlag;
/*/////////////////////////////////////////////////
	FILE *stream;
*//////////////////////////////////////////////////

	convert Convert;

	specialFlag = 0;
	m_Pi = Convert.Pi();
	flag = 0;
	rFlag = sFlag = tFlag = tempFlag = 0;
	done = 0;
	dTransitTimeAdjust = timeAdjust / (double)2;

	CPlanet::FindTransitFraction(julDay, longitude, &julDayZero, &julDayZeroUT,
		&transitFraction, &delta2, &radius2);

	julDayZeroUTTransit = julDayZero + transitFraction;

//	Do we have to look N for transit or S?  Also if body passes within 15 degrees of 
//	zenith, calculate transit from a latitude that is further away so we don't have 
//	to deal with the body moving so fast as it passes through the transit.
	dCalculationLatitude = latitude;
	CPlanet::AdjustTransitParameters(&dCalculationLatitude, delta2,
									 &testValue, &dTransitTimeAdjust);

//	Now calculate more exact transit time
	CPlanet::transitFinder(julDayZeroUTTransit, dCalculationLatitude, longitude,
						   testValue, dTransitTimeAdjust, hourAngleTransit, &tFlag);
	transitValue = ((hourAngleTransit - julDayZeroUT) * (double)24) + timeCorrection;
	transitFraction = hourAngleTransit - julDayZero;
	newjulDayZeroUTTransit = hourAngleTransit;

	if(transitValue < 0)
	{
		julDayZeroUTTransit = hourAngleTransit + (double)1;
		CPlanet::transitFinder(julDayZeroUTTransit, dCalculationLatitude, longitude,
							   testValue, dTransitTimeAdjust, hourAngleTransit, &tempFlag);
		tempFlag *= 100;
		tFlag += tempFlag;
		transitValue = ((hourAngleTransit - julDayZeroUT - (double)1) * (double)24) + timeCorrection;
		if(transitValue > 0)
		{
			transitValue = -999;
		}
		else
		{
			transitValue += (double)24;
			newjulDayZeroUTTransit = hourAngleTransit;
			transitFraction = hourAngleTransit - (double)1 - julDayZero;
		}
	}//	end of "(transitValue < 0)"
	else if (transitValue > 24)
	{
		julDayZeroUTTransit = hourAngleTransit - (double)1;
		CPlanet::transitFinder(julDayZeroUTTransit, dCalculationLatitude, longitude,
							   testValue, dTransitTimeAdjust, hourAngleTransit, &tempFlag);
		tempFlag *= 10000;
		tFlag += tempFlag;
		transitValue = ((hourAngleTransit - julDayZeroUT + (double)1) * (double)24) + timeCorrection;
		if(transitValue < 24)
		{
			transitValue = -999;
		}
		else
		{
			transitValue -= (double)24;
			newjulDayZeroUTTransit = hourAngleTransit;
			transitFraction = hourAngleTransit + (double)1 - julDayZero;
		}
	}//	end of "(transitValue > 24)"
	hourAngleTransit = transitValue;

//	Calculate rise time and then set time.

//	For sun and moon, use different height
	if(planet == 0)m_h0 = -.833333;
	if(planet == 1)
	{
		moonParallax = asin(6378.14 / radius2);// Meeus p. 307
		m_h0 = .7275 * Convert.radianToDegree(moonParallax) - 0.566667;
	}
	radm_h0 = Convert.degreeToRadian(m_h0);

	if(fabs(latitude) > 1.047)// ~60 degrees
	{
		hourAngleRise = hourAngleSet = hourAngleExtra = 0.0;
		CPlanet::findHighLatRiseSet(julDay, .007, latitude, longitude,
			tempFlag, hourAngleRise, hourAngleSet, radm_h0, hourAngleExtra, specialFlag);
		sFlag = tempFlag;
	}
	else
	{
		CPlanet::Find_m_dH0(radm_h0, latitude, delta2, &m_dH0);

//		Find starting values for rise from Meeus p 97
		riseFraction = transitFraction - (m_dH0 / ((double)2 * m_Pi));
		julDayZeroUTRise = julDayZeroUT + riseFraction;

		riseSetFlag = CPlanet::riseSetFinder(julDayZeroUTRise, julDayZeroUTRise - 0.5,
											 julDayZeroUTRise + 0.5, latitude,
											 longitude, radm_h0, timeAdjust,
											 hourAngleRise, true, &rFlag);
		if(riseSetFlag == 0)// value found
		{
			riseValue = (hourAngleRise - julDayZeroUT) * (double)24 + timeCorrection;

			if(riseValue < 0)
			{
//	FindNewStartTime was originally written because when you go to the next or
//	previous day to see what is going on, you sometimes get bad results if you
//	just add (or subtract) 1 to the current julDay value.  I would guess that 
//	this is no linger an issue with findHighLatRiseSet, but it is safer, so it
//	stays
				julDayZeroUTRise = CPlanet::FindNewStartTime(julDay + (double)1, &newjulDayZeroUT,
															 radm_h0, latitude, longitude, true);
				riseSetFlag = CPlanet::riseSetFinder(julDayZeroUTRise, julDayZeroUTRise - 0.5,
													 julDayZeroUTRise + 0.5, latitude,
													 longitude, radm_h0, timeAdjust,
													 hourAngleRise, true, &tempFlag);
				tempFlag += 2500;
				rFlag += tempFlag;
				if(riseSetFlag == 0)
				{
					riseValue = (hourAngleRise - newjulDayZeroUT) * (double)24 + timeCorrection;
					if(riseValue > 0)
					{
						riseValue = -999;
					}
					else
					{
						riseValue += (double)24;
					}
				}
				else if (riseSetFlag == 1)
				{
					riseValue = (double)-99;//Always up
				}
				else
				{
					riseValue = (double)-9;//Never up
				}
			}
			else if (riseValue > 24)
			{
	//	Test to see if next day is always up or never up
				julDayZeroUTRise = CPlanet::FindNewStartTime(julDay - (double)1, &newjulDayZeroUT,
															 radm_h0, latitude, longitude, true);
				riseSetFlag = CPlanet::riseSetFinder(julDayZeroUTRise, julDayZeroUTRise - 0.5,
													 julDayZeroUTRise + 0.5, latitude,
													 longitude, radm_h0, timeAdjust,
													 hourAngleRise, true, &tempFlag);
				tempFlag += 2600;
				rFlag += tempFlag;
				if(riseSetFlag == 0)
				{
					riseValue = (hourAngleRise - newjulDayZeroUT) * (double)24 + timeCorrection;
					if(riseValue < 24)
					{
						riseValue = -999;
					}
					else
					{
						riseValue -= (double)24;
					}
				}
				else if (riseSetFlag == 1)
				{
					riseValue = (double)-99;//Always up
				}
				else
				{
					riseValue = (double)-9;//Never up
				}
			}
		}
//	Theoretically, since findHighLatRiseSet deals with high latitude cases, this
//	is no longer necessary, and never used.  but it remains just in case...
		else  //if (riseSetFlag == 1 || 2)
		{
			if(riseSetFlag == 1)	currentRiseValue = -99;
			else					currentRiseValue = -9;

			tempJulDay = julDayZeroUTRise + (double)1;
			if(currentRiseValue < -10) //Always up
//	Because I had trouble being on the wrong side of the extreme value sometimes
//	which would then give a false answer, timeOfLowestPoint and timeOfHighestPoint
//	finds the low or high point from which to start the search
			{
				CPlanet::timeOfLowestPoint(tempJulDay, latitude, longitude, timeAdjust, julDayH);
			}
			else
			{
				CPlanet::timeOfHighestPoint(tempJulDay, latitude, longitude, timeAdjust, julDayH);
			}

			riseSetFlag = CPlanet::riseSetFinder(julDayH, julDayH - 0.5, julDayH + 0.5,
												 latitude, longitude, radm_h0, timeAdjust,
												 hourAngleRise, true, &tempFlag);
	tempFlag += 2700;
	rFlag += tempFlag;
			if(riseSetFlag == 0)
			{
				riseValue = (hourAngleRise - julDayZeroUT - (double)1) * (double)24 + timeCorrection;
				if(riseValue > 0)
				{
					riseValue = currentRiseValue;// look back
				}
				else
				{
					riseValue += (double)24;
				}
			}
			else
			{
				riseValue = currentRiseValue;// look back
			}

			if(riseValue < 0)
			{
				tempJulDay = julDayZeroUTRise - (double)1;
				if(currentRiseValue < -10) //Always up
				{
					CPlanet::timeOfLowestPoint(tempJulDay, latitude, longitude, timeAdjust, julDayH);
				}
				else
				{
					CPlanet::timeOfHighestPoint(tempJulDay, latitude, longitude, timeAdjust, julDayH);
				}
				
				riseSetFlag = CPlanet::riseSetFinder(julDayH, julDayH - 0.5, julDayH + 0.5,
													 latitude, longitude, radm_h0, timeAdjust,
													 hourAngleRise, true, &tempFlag);
	tempFlag += 2800;
	rFlag += tempFlag;
				if(riseSetFlag == 0)
				{
					riseValue = (hourAngleRise - julDayZeroUT + (double)1) * (double)24 + timeCorrection;
					if(riseValue < 24)
					{
						riseValue = currentRiseValue;
					}
					else
					{
						riseValue -= (double)24;
					}
				}
				else
				{
					riseValue = currentRiseValue;
				}
			}
		}

  		hourAngleRise = riseValue;
			
	//		Find starting values for set
		setFraction = transitFraction  + (m_dH0 / ((double)2 * m_Pi));
		julDayZeroUTSet = julDayZeroUT + setFraction;
		
		riseSetFlag = CPlanet::riseSetFinder(julDayZeroUTSet, julDayZeroUTSet - 0.5,
											 julDayZeroUTSet + 0.5, latitude,
											 longitude, radm_h0, timeAdjust,
											 hourAngleSet, false, &sFlag);
		if(riseSetFlag == 0)
		{
			setValue = (hourAngleSet - julDayZeroUT) * (double)24 + timeCorrection;
		
			if(setValue < 0)
			{
	//	Test to see if next day is always up or never up
				julDayZeroUTSet = CPlanet::FindNewStartTime(julDay + (double)1, &newjulDayZeroUT,
															 radm_h0, latitude, longitude, false);
				riseSetFlag = CPlanet::riseSetFinder(julDayZeroUTSet, julDayZeroUTSet - 0.5,
													 julDayZeroUTSet + 0.5, latitude,
													 longitude, radm_h0, timeAdjust,
													 hourAngleSet, false, &tempFlag);
				tempFlag += 2900;
				sFlag += tempFlag;
				if(riseSetFlag == 0)
				{
					setValue = (hourAngleSet - newjulDayZeroUT) * (double)24 + timeCorrection;
					if(setValue > 0)
					{
						setValue = -999;
					}
					else
					{
						setValue += (double)24;
					}
				}
				else if(riseSetFlag == 1)
				{
					setValue = (double)-99;//Always up
				}
				else
				{
					setValue = (double)-9;//Never up
				}
			}
			else if (setValue > 24)
			{
	//	Test to see if next day is always up or never up
				julDayZeroUTSet = CPlanet::FindNewStartTime(julDay - (double)1, &newjulDayZeroUT,
															 radm_h0, latitude, longitude, false);
				riseSetFlag = CPlanet::riseSetFinder(julDayZeroUTSet, julDayZeroUTSet - 0.5,
													 julDayZeroUTSet + 0.5, latitude,
													 longitude, radm_h0, timeAdjust,
													 hourAngleSet, false, &tempFlag);
				tempFlag += 3000;
				sFlag += tempFlag;
				if(riseSetFlag == 0)
				{
					setValue = (hourAngleSet - newjulDayZeroUT) * (double)24 + timeCorrection;
					if(setValue < 24)
					{
						setValue = -999;
					}
					else
					{
						setValue -= (double)24;
					}
				}
				else if(riseSetFlag == 1)
				{
					setValue = (double)-99;//Always up
				}
				else
				{
					setValue = (double)-9;//Never up
				}
			}
		}
		else  //if(riseSetFlag == 1 || 2)
		{
			if(riseSetFlag == 1)	currentSetValue = -99;
			else					currentSetValue = -9;

			tempJulDay = julDayZeroUTSet + (double)1;
			if(currentRiseValue < -10) //Always up
			{
				CPlanet::timeOfLowestPoint(tempJulDay, latitude, longitude, timeAdjust, julDayH);
			}
			else
			{
				CPlanet::timeOfHighestPoint(tempJulDay, latitude, longitude, timeAdjust, julDayH);
			}

			riseSetFlag = CPlanet::riseSetFinder(julDayH, julDayH - 0.5,
												 julDayH + 0.5, latitude,
												 longitude, radm_h0, timeAdjust,
												 hourAngleSet, false, &tempFlag);
	tempFlag += 3100;
	sFlag += tempFlag;
			if(riseSetFlag == 0)
			{
				setValue = (hourAngleSet - julDayZeroUT - (double)1) * (double)24 + timeCorrection;
				if(setValue > 0)
				{
					setValue = currentSetValue;// look back
				}
				else
				{
					setValue += (double)24;
				}
			}
			else //if (riseSetFlag == 1)
			{
				setValue = currentSetValue;// look back
			}

			if(setValue < 0)
			{
				tempJulDay = julDayZeroUTSet - (double)1;
				if(currentRiseValue < -10) //Always up
				{
					CPlanet::timeOfLowestPoint(tempJulDay, latitude, longitude, timeAdjust, julDayH);
				}
				else
				{
					CPlanet::timeOfHighestPoint(tempJulDay, latitude, longitude, timeAdjust, julDayH);
				}
				riseSetFlag = CPlanet::riseSetFinder(julDayH, julDayH - 0.5,
													 julDayH + 0.5, latitude,
													 longitude, radm_h0, timeAdjust,
													 hourAngleSet, false, &tempFlag);
				tempFlag += 3200;
				sFlag += tempFlag;
				if(riseSetFlag == 0)
				{
					setValue = (hourAngleSet - julDayZeroUT + (double)1) * (double)24 + timeCorrection;
					if(setValue < 24)
					{
						setValue = currentSetValue;
					}
					else
					{
						setValue -= (double)24;
					}
				}
				else
				{
					setValue = currentSetValue;
				}
			}
		}

		hourAngleSet = setValue;
	}

/*///////////////////////////////////////////////////////////////////////
	if( (stream  = fopen( "astrol.txt", "a+" )) == NULL )
	printf( "The file 'astrol.txt' was not opened\n" );
	else
	printf( "The file 'astrol.txt' was opened\n" );
	fprintf( stream, "%i, %i, %i,", rFlag, tFlag, sFlag);
	fclose( stream );
*/////////////////////////////////////////////////////////////////////

}

//	Used for those cases from finding the rise or set time where the value
//	is returned negative or >24.  This starts at a new day and finds the 
//	time to start looking for rise or set value

double CPlanet::FindNewStartTime(double julDay, double * newjulDayZeroUT, double radm_h0,
								 double latitude, double longitude, bool type)
{
	convert Convert;

	double newjulDayZero, newtransitFraction, newdelta2, newradius2;
	double newm_dH0, julDayZeroUT, Fraction, m_Pi;

	m_Pi = Convert.Pi();

	CPlanet::FindTransitFraction(julDay, longitude, &newjulDayZero,
								 newjulDayZeroUT, &newtransitFraction,
								 &newdelta2, &newradius2);
	CPlanet::Find_m_dH0(radm_h0, latitude, newdelta2, &newm_dH0);
	if(type)
	{
		Fraction = newtransitFraction - (newm_dH0 / ((double)2 * m_Pi));
	}
	else
	{
		Fraction = newtransitFraction + (newm_dH0 / ((double)2 * m_Pi));
	}
	julDayZeroUT = *newjulDayZeroUT + Fraction;

	return julDayZeroUT;
}

//	If the altitude of the body at transit is too close to the zenith, 
//	errors can result in the calculation of the time of transit.  Therefore
//	this function changes the latitude up or down to get away from this
//	situation.  If you are too close to one of the poles, you cannot 
//	move closer to the pole to get away, and so must move in the other 
//	direction.  Also, if you are in the southern hemisphere, you must look 
//	north to see the transit, this makes that adjustment by setting 
//	*testValue to 0.0 and by reversing the timeAdjust so that the transitFinder
//	function works properly
void CPlanet::AdjustTransitParameters(double *latitude, double delta, 
									  double *testValue, double *timeAdjust)
{
	convert Convert;

	double m_Pi;

	m_Pi = Convert.Pi();

	if (*latitude < delta)
	{
		if(fabs(delta - *latitude) < 0.2618)
		{
			if( *latitude > -1.2)
			{
				*latitude -= .35;
				*testValue = 0;
				*timeAdjust *= -(double)1;
			}
			else
			{
				*latitude += .7;
				*testValue = m_Pi;
			}
		}
		else
		{
			*testValue = 0;
			*timeAdjust *= -(double)1;
		}
	}
	else
	{
		if (fabs(delta - *latitude) < 0.2618)
		{
		if(	*latitude < 1.2)
			{
				*latitude += .35;
				*testValue = m_Pi;
			}
			else
			{
				*latitude -= .7;
				*testValue = 0;
				*timeAdjust *= -(double)1;
			}
		}
		else
		{
			*testValue = m_Pi;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//	High latitude has situations where bodies are never up, always up	//
//	or rise or set twice in one day.  At high latitudes the curve of	//
//	altitude with time is sinusoidal (which means sometimes parabolic	//
//	and sometimes a straight line depending on what part of the curve	//
//	you are on and the shape of the curve at that latitude).  Sometimes	//
//	it has a high followed by a low and other times a low followed by a	//
//	high.  The horizon can occur anywhere along this curve (including	//
//	not on it).  All of these situations have to be handled				//
//	individually.														//
//																		//
//	MIN means the curve has one minimum									//
//	MAX one maximum														//
//	DEC always decreasing												//
//	MINMAX minimum followed by maximum									//
//	INC always increasing												//
//	MAXMIN maximum folowed by minimum									//
//																		//
//	The function works by initially finding the values of the altitude	//
//	for each end of the day in question and an 'increment' amount of	//
//	time inside either end of the day.  These 4 points begin the process//
//	of determining what kind of curve you are dealing with.  MAX and MIN//
//	are easy, but DEC/MINMAX and INC/MAXMIN pairs look the same from	//
//	their ends so more information is required to find the true shape.	//
//	We begin by looking at .5 and .51.  The results of comparing these	//
//	two put us either in the DEC/MINMAX or INC/MAXMIN camp.  If we end	//
//	up either in MINMAX or MAXMIN, which is usually the case, we also	//
//	need to take .25 and .75 points.  Sometimes we can break out of here//
//	early if we are always up or never up, but if not, we continue and	//
//	end up using riseSetFinder.  Its as simple as that.
//////////////////////////////////////////////////////////////////////////
void CPlanet::findHighLatRiseSet(double startTime, double increment,
						  double latitude, double longitude,
						  int &countFlag, double &riseTime, double &setTime,
						  double height, double &extraTime, int &specialFlag)
{
	double azimuth1, altitude1, azimuth2 ;
	double azimuthM1, azimuthM2;
	double azimuthA, azimuthB ;
	double azimuth3, azimuth4 ;
	double endTime, tempTime;
	double julDayMin, altitudeMin, julDayMax, altitudeMax;
	double julDay[8], altitude[8];
	int flag, i, maxI, minI, typeFlag;

	endTime = startTime + 1.0;
	countFlag = typeFlag = specialFlag = 0;

	julDay[0] = startTime;
	julDay[1] = startTime + increment;
	julDay[7] = endTime;
	julDay[6] = endTime - increment;
	CPlanet::azimuthAltitudePlanet(julDay[0], latitude, longitude,
								   azimuth1, altitude[0]);
	CPlanet::azimuthAltitudePlanet(julDay[1], latitude, longitude,
								   azimuth2, altitude[1]);
	CPlanet::azimuthAltitudePlanet(julDay[7], latitude, longitude,
								   azimuthA, altitude[7]);
	CPlanet::azimuthAltitudePlanet(julDay[6], latitude, longitude,
								   azimuthB, altitude[6]);
countFlag +=4;
	
	if(		altitude[1] < altitude[0]
		&&	altitude[6] < altitude[7])// MIN// MIN// MIN// MIN// MIN// MIN// MIN
	{
		if(		altitude[0] < height
			&&	altitude[7] < height)// -9, always below horizon
		{
			riseTime = setTime = -9;
countFlag +=100;
			goto finish;
		}
		julDay[3] = startTime + 0.5;
		CPlanet::azimuthAltitudePlanet(julDay[3], latitude, longitude,
									   azimuthM1, altitude[3]);
countFlag +=1;
////////////////////////////////////////////////////////////
		CPlanet::findMinMax(latitude, longitude,
							julDay[0], julDay[3], julDay[7],
							altitude[0], altitude[3], altitude[7],
							julDayMin, altitudeMin, flag, true);
countFlag += flag;
////////////////////////////////////////////////////////////
		if(altitudeMin > height)// -99, always above horizon
		{
			riseTime = setTime = -99;
countFlag +=200;
			goto finish;
		}

		if(altitude[0] > height)
		{
			CPlanet::riseSetFinder(julDay[0], julDay[0], julDay[3], latitude,
								   longitude, height, 0.007, setTime, false, &flag);
			setTime -= startTime;
countFlag +=flag;
		}
		else// no set
		{
			setTime = -999;
		}

		if(altitude[7] > height)
		{
			CPlanet::riseSetFinder(julDay[7], julDay[3], julDay[7], latitude,
								   longitude, height, 0.007, riseTime, true, &flag);
			riseTime -= startTime;
countFlag +=flag;
countFlag +=300;
			goto finish;
		}
		else// no rise
		{
			riseTime = -999;
countFlag +=400;
			goto finish;
		}
	}
	else if(	altitude[1] > altitude[0]
			&&	altitude[6] > altitude[7])// MAX// MAX// MAX// MAX// MAX// MAX// MAX// MAX
	{
		if(		altitude[0] > height
			&&	altitude[7] > height)// -99, always above horizon
		{
			riseTime = setTime = -99;
countFlag +=500;
			goto finish;
		}
		julDay[3] = startTime + 0.5;
		CPlanet::azimuthAltitudePlanet(julDay[3], latitude, longitude,
									   azimuthM1, altitude[3]);
countFlag +=1;
////////////////////////////////////////////////////////////
		CPlanet::findMinMax(latitude, longitude,
							julDay[0], julDay[3], julDay[7],
							altitude[0], altitude[3], altitude[7],
							julDayMax, altitudeMax, flag, false);
countFlag += flag;
////////////////////////////////////////////////////////////
		if(altitudeMax < height)// -9, always below horizon
		{
			riseTime = setTime = -9;
countFlag +=600;
			goto finish;
		}

		if(altitude[0] < height)
		{
			CPlanet::riseSetFinder(julDay[0], julDay[0], julDay[3], latitude,
								   longitude, height, 0.007, riseTime, true, &flag);
			riseTime -= startTime;
countFlag +=flag;
		}
		else//	no rise
		{
			riseTime = -999;
		}

		if(altitude[7] < height)
		{
			CPlanet::riseSetFinder(julDay[7], julDay[3], julDay[7], latitude,
								   longitude, height, 0.007, setTime, false, &flag);
			setTime -= startTime;
countFlag +=flag;
countFlag +=700;
			goto finish;
		}
		else// no set
		{
			setTime = -999;
countFlag +=800;
			goto finish;
		}
	}
	else
	{
		julDay[3] = startTime + .5;
		julDay[4] = startTime + .51;
		CPlanet::azimuthAltitudePlanet(julDay[3], latitude, longitude,
									   azimuthM1, altitude[3]);
		CPlanet::azimuthAltitudePlanet(julDay[4], latitude, longitude,
									   azimuthM2, altitude[4]);
countFlag +=2;
		if(		altitude[1] < altitude[0]
			&&	altitude[6] > altitude[7])
		{
			if(		altitude[3] > altitude[4]
				&&	altitude[3] < altitude[1]
				&&	altitude[3] > altitude[7])// DEC// DEC// DEC// DEC// DEC// DEC// DEC// DEC// DEC
			{
				if(altitude[0] < height)// -9, always below horizon
				{
					riseTime = setTime = -9;
countFlag +=900;
					goto finish;
				}
				if(altitude[7] > height)// -99, always above horizon
				{
					riseTime = setTime = -99;
countFlag +=1000;
					goto finish;
				}
				setTime = julDay[0] - ((julDay[0] - julDay[7]) * ((altitude[0] - height) /
															(altitude[0] - altitude[7])) );
				setTime -= startTime;
				riseTime = -99;
countFlag +=1100;
				goto finish;
			}
			else// MINMAX// MINMAX// MINMAX// MINMAX// MINMAX// MINMAX// MINMAX
			{
				setTime = -9999;

				julDay[2] = startTime + .25;
				CPlanet::azimuthAltitudePlanet(julDay[2], latitude, longitude,
											   azimuth3, altitude[2]);
countFlag +=1;
				altitude1 = altitude[0];
				for(i=1; i<5; i++)
				{
					if(altitude1 < altitude[i])
					{
					}
					else
					{
						altitude1 = altitude[i];
						minI = i;
					}
				}
////////////////////////////////////////////////////////////////////////////
				CPlanet::findMinMax(latitude, longitude,
									julDay[minI-1], julDay[minI], julDay[minI+1],
									altitude[minI-1], altitude[minI], altitude[minI+1],
									julDayMin, altitudeMin, flag, true);
countFlag += flag;
////////////////////////////////////////////////////////////////////////////
				if(		altitude[0]	> height
					&&	altitudeMin	> height
					&&	altitude[7]	> height)
				{
					riseTime = setTime = -99;
countFlag +=1200;
					goto finish;
				}

				julDay[5] = startTime + .75;
				CPlanet::azimuthAltitudePlanet(julDay[5], latitude, longitude,
											   azimuth4, altitude[5]);
countFlag +=1;
				altitude1 = altitude[7];
				for(i=6; i>2; i--)
				{
					if(altitude1 > altitude[i])
					{
					}
					else
					{
						altitude1 = altitude[i];
						maxI = i;
					}
				}
///////////////////////////////////////////////////////////////////////
				CPlanet::findMinMax(latitude, longitude,
									julDay[maxI-1], julDay[maxI], julDay[maxI+1],
									altitude[maxI-1], altitude[maxI], altitude[maxI+1],
									julDayMax, altitudeMax, flag, false);
countFlag +=flag;
///////////////////////////////////////////////////////////////////////

				if(		altitude[0]	< height
					&&	altitudeMax	< height
					&&	altitude[7]	< height)
				{
					riseTime = setTime = -9;
countFlag +=1300;
					goto finish;
				}

				if(		altitudeMin < height
					&&	altitudeMax > height)//	We have a rise
				{
					if(julDayMin < julDay[minI])
					{
						CPlanet::riseSetFinder(julDay[minI], julDayMin, julDayMax, latitude,
											   longitude, height, 0.007, riseTime, true, &flag);
					riseTime -= startTime;
countFlag +=flag;
					}
					else
					{
						CPlanet::riseSetFinder(julDay[minI+1], julDayMin, julDayMax, latitude,
											   longitude, height, 0.007, riseTime, true, &flag);
					riseTime -= startTime;
countFlag +=flag;
					}
				}
				else
				{
					typeFlag = 1;
				}

				setTime = -999;

				if(		altitude[0] > height
				  &&	altitudeMin < height)//	We have set here
				{
					CPlanet::riseSetFinder(julDay[0], julDay[0], julDayMin, latitude,
										   longitude, height, 0.007, setTime, false, &flag);
					setTime -= startTime;
					specialFlag += 1;
countFlag +=flag;
countFlag +=1400;
					if(typeFlag == 1)
					{
						riseTime = -9;
					}
				}
				if(		altitudeMax > height
					&&	altitude[7] < height)// or we have set here
				{
					CPlanet::riseSetFinder(julDay[7], julDayMax, julDay[7], latitude,
										   longitude, height, 0.007, tempTime, false, &flag);
					if(specialFlag > 0)
					{
						extraTime = tempTime - startTime;
					}
					else
					{
						setTime = tempTime - startTime;
					}
					specialFlag += 1;
countFlag +=flag;
countFlag +=1500;
					if(typeFlag == 1)
					{
						riseTime = -99;
					}
				}
				if(specialFlag < 1)//	or next day
				{
countFlag +=1600;
				}
			}
		}

		else
		{
			if(		altitude[3] < altitude[4]
				&&	altitude[3] > altitude[1]
				&&	altitude[3] < altitude[7])// INC// INC// INC// INC// INC// INC// INC// INC// INC
			{
				if(altitude[7] < height)// -9, always below horizon
				{
					riseTime = setTime = -9;
countFlag +=1700;
					goto finish;
				}
				if(altitude[0] > height)// -99, always above horizon
				{
					riseTime = setTime = -99;
countFlag +=1800;
					goto finish;
				}
				riseTime = julDay[0] - ((julDay[0] - julDay[7]) * ((altitude[0] - height) /
															(altitude[0] - altitude[7])) );
				riseTime -= startTime;
				setTime = -99;
countFlag +=1900;
				goto finish;
			}
			else// MAXMIN// MAXMIN// MAXMIN// MAXMIN// MAXMIN// MAXMIN// MAXMIN// MAXMIN// MAXMIN
			{
				riseTime = -9999;

				julDay[2] = startTime + .25;
				CPlanet::azimuthAltitudePlanet(julDay[2], latitude, longitude,
											   azimuth3, altitude[2]);
countFlag +=1;
				altitude1 = altitude[0];
				for(i=1; i<5; i++)
				{
					if(altitude1 > altitude[i])
					{
					}
					else
					{
						altitude1 = altitude[i];
						maxI = i;
					}
				}
////////////////////////////////////////////////////////////////////////
				CPlanet::findMinMax(latitude, longitude,
									julDay[maxI-1], julDay[maxI], julDay[maxI+1],
									altitude[maxI-1], altitude[maxI], altitude[maxI+1],
									julDayMax, altitudeMax, flag, false);
countFlag += flag;
////////////////////////////////////////////////////////////////////////
			  if(		altitude[0]	< height
					&&	altitudeMax	< height
					&&	altitude[7]	< height)
				{
					riseTime = setTime = -9;
countFlag +=2000;
					goto finish;
				}

				julDay[5] = startTime + .75;
				CPlanet::azimuthAltitudePlanet(julDay[5], latitude, longitude,
											   azimuth4, altitude[5]);
countFlag +=1;
				altitude1 = altitude[7];
				for(i=6; i>2; i--)
				{
					if(altitude1 < altitude[i])
					{
					}
					else
					{
						altitude1 = altitude[i];
						minI = i;
					}
				}
////////////////////////////////////////////////////////////////////////////
				CPlanet::findMinMax(latitude, longitude,
									julDay[minI-1], julDay[minI], julDay[minI+1],
									altitude[minI-1], altitude[minI], altitude[minI+1],
									julDayMin, altitudeMin, flag, true);
countFlag += flag;
////////////////////////////////////////////////////////////////////////////
				if(		altitude[0]	> height
					&&	altitudeMin	> height
					&&	altitude[7]	> height)
				{
					riseTime = setTime = -99;
countFlag +=2100;
					goto finish;
				}


			    if(		altitudeMax > height
					&&	altitudeMin < height)//	We have a set
				{
					if(julDayMax < julDay[maxI])
					{
						CPlanet::riseSetFinder(julDay[maxI], julDayMax, julDayMin, latitude,
											   longitude, height, 0.007, setTime, false, &flag);
					setTime -= startTime;
countFlag +=flag;
					}
					else
					{
						CPlanet::riseSetFinder(julDay[maxI+1], julDayMax, julDayMin, latitude,
											   longitude, height, 0.007, setTime, false, &flag);
					setTime -= startTime;
countFlag +=flag;
					}
				}
				else
				{
					typeFlag = 1;
				}

				riseTime = -999;

				if(		altitude[0] < height
				  &&	altitudeMax > height)//	We have rise here
				{
					CPlanet::riseSetFinder(julDay[0], julDay[0], julDayMax, latitude,
										   longitude, height, 0.007, riseTime, true, &flag);
					riseTime -= startTime;
					specialFlag += 3;
countFlag +=flag;
countFlag +=2200;
					if(typeFlag == 1)
					{
						setTime = -99;
					}
				}
				if(		altitudeMin < height
					&&	altitude[7] > height)// or we have rise here
				{
					CPlanet::riseSetFinder(julDay[7], julDayMin, julDay[7], latitude,
										   longitude, height, 0.007, tempTime, true, &flag);
					if(specialFlag > 0)
					{
						extraTime = tempTime - startTime;
					}
					else
					{
						riseTime = tempTime - startTime;
					}
					specialFlag += 3;
countFlag +=flag;
countFlag +=2300;
					if(typeFlag == 1)
					{
						setTime = -9;
					}
				}
				if(specialFlag < 1)//	or next day
				{
countFlag +=2400;
				}
			}
		}
	}
finish: riseTime = riseTime < 0.0 ? riseTime : riseTime * 24.0;
		setTime = setTime < 0.0 ? setTime : setTime * 24.0;
		extraTime = extraTime < 0.0 ? extraTime : extraTime * 24.0;

}

//////////////////////////////////////////////////////////////////////////
//	Given three y values and their resultant x values, calculates the	//
//	location of the y value of the extreme value.  The three points mus	//
//	be such that the middle x-value is the same side of the outer values//
//	(lower or higher).	I did not figure out why, but if you do not do	//
//	this, you can get some funny results.								//
//																		//
//			1  y1(x2^2 - x3^2) - y2(x1^2 - x3^2) + y3(x1^2 - x2^2)		//
//	value = - ------------------------------------------------------	//
//			2			y1(x1-x3) - y2(x1-x3) + y3(x1-x2)				//
//																		//
//	Get this equation by finding the equation of a parabola given		//
//	three points and then taking the derivative of the result			//
//////////////////////////////////////////////////////////////////////////
double CPlanet::extremeValue(double time1, double time2, double time3,
						   double alt1, double alt2, double alt3)
{
	double value;

	value =  ((alt1 * (time2 * time2 - time3 * time3) -
			  alt2 * (time1 * time1 - time3 * time3) +
			  alt3 * (time1 * time1 - time2 * time2)) / 
			  (alt1 * (time2 - time3) -
			  alt2 * (time1 - time3) +
			  alt3 * (time1 - time2))) / 2.0;

	return value;
}

//////////////////////////////////////////////////////////////////////////
//	This function really manages the extremeValue function.  eV finds	//
//	extreme values, but only if the middle value sent is the current	//
//	extreme value.  The return value, time4, is used to find alt4.		//
//	There are 4 possible locations for alt4 (minimum case):							//
//																		//
//			alt1		alt3											//
//			  			 												//
//			alt4(4d)  alt4(4b)											//
//				  	  													//
//				   alt2													//
//																		//
//			alt4(4c)  alt4(4a)											//
//																		//
//	Once we find the location of alt4, we adjust our values and go back	//
//	to eV for another round.											//
//																		//
//	When the difference between time1 and time3 gets very small, eV		//
//	tends to return values outside of the time1-time3 interval,(I think	//
//	it looks too much like a straight line), so return the current		//
//	extreme value.														//
//																		//
//////////////////////////////////////////////////////////////////////////
void CPlanet::findMinMax(double latitude, double longitude,
						 double timeOne, double timeTwo, double timeThree,
						 double altOne, double altTwo, double altThree,
						 double &timeExt, double &altExt, int &countFlag,
						 bool MIN)
{
	double TEST, dif, absDif, az;
	double time1, time2, time3, time4, alt1, alt2, alt3, alt4;

	TEST = 1.0e-004;
	countFlag = 0;
	dif = absDif = 2;
	time1 = timeOne;
	time2 = timeExt = timeTwo;
	time3 = timeThree;
	alt1 = altOne;
	alt2 = altExt = altTwo;
	alt3 = altThree;

	while(absDif > TEST)
	{
		time4 = CPlanet::extremeValue(time1, time2, time3, alt1, alt2, alt3);

		if(		time4 < time1
			||	time4 > time3)
		{
			return;
		}

		dif = time4 - time2;
		absDif = fabs(dif);
		if(absDif < TEST)
		{
			if(		(	MIN
					&&	alt4 > alt2)
				||
					(	!MIN
					&&	alt4 < alt2))
			{
			}
			else
			{
				timeExt = time4;
				altExt = alt4;
			}
			return;
		}

		CPlanet::azimuthAltitudePlanet(time4, latitude, longitude, az, alt4);
countFlag += 1;

		if(dif > 0.0)//4a and 4b
		{
			if(		(	MIN
					&&	alt4 < alt2)
				||
					(	!MIN
					&&	alt4 > alt2))//	4a
			{//2, 4, 3
				timeExt = time4;
				altExt = alt4;

				time1 = time2;
				time2 = time4;
				alt1 = alt2;
				alt2 = alt4;
			}
			else//  4b
			{//1, 2, 4
				time3 = time4;
				alt3 = alt4;
			}
		}
		else//4c and 4d
		{
			if(		(	MIN
					&&	alt4 < alt2)
				||
					(	!MIN
					&&	alt4 > alt2))//	4c
			{//1, 4, 2
				timeExt = time4;
				altExt = alt4;

				time3 = time2;
				time2 = time4;
				alt3 = alt2;
				alt2 = alt4;
			}
			else//  4d
			{//4, 2, 3
				time1 = time4;
				alt1 = alt4;
			}
		}
	}
}

//	I don't trust this one or timeOfHighestPoint.  Both should probably be scrapped
//	A better function is findMinMax, although these two start with different values
void CPlanet::timeOfLowestPoint(double julDay1, double latitude, double longitude,
								double timeAdjust, double &julDay2)
{
	double azimuth1, altitude1, azimuth3, altitude3;
	double azimuth2, altitude2, azimuth4, altitude4;
	double julDay3, julDay4, julDayHolder;
	double a, b, c, n0;
	int flag;

	flag = 0;
	julDay2 = julDayHolder = julDay1;
	julDay1 -= timeAdjust;
	julDay3 = julDay2 + timeAdjust;
	CPlanet::azimuthAltitudePlanet(julDay1, latitude, longitude,
									azimuth1, altitude1);
	CPlanet::azimuthAltitudePlanet(julDay2, latitude, longitude,
									azimuth2, altitude2);
	CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
									azimuth3, altitude3);

	while(	  altitude3 < altitude2
		  &&  flag < 8)
	{
		julDay4 = julDay3 + timeAdjust;
		CPlanet::azimuthAltitudePlanet(julDay4, latitude, longitude,
									   azimuth4, altitude4);
		julDay1 = julDay2;
		julDay2 = julDay3;
		julDay3 = julDay4;
		altitude1 = altitude2;
		altitude2 = altitude3;
		altitude3 = altitude4;
		flag +=1;
	}

	if(flag < 1)
	{
		while(	  altitude1 < altitude2
			  &&  flag < 8)
		{
			julDay4 = julDay1 - timeAdjust;
			CPlanet::azimuthAltitudePlanet(julDay4, latitude, longitude,
										   azimuth4, altitude4);
			julDay3 = julDay2;
			julDay2 = julDay1;
			julDay1 = julDay4;
			altitude3 = altitude2;
			altitude2 = altitude1;
			altitude1 = altitude4;
			flag +=1;
		}
	}

	if(flag > 7)
	{
		julDay2 = julDayHolder;
	}
	else
	{
		a = altitude2 - altitude1;
		b = altitude3 - altitude2;
		c = b - a;
		n0 = -(a+b) / 2*c;
		julDay2 += n0 * timeAdjust;
	}
}

void CPlanet::timeOfHighestPoint(double julDay1, double latitude, double longitude,
							 double timeAdjust, double &julDay2)
{
	double azimuth1, altitude1, azimuth3, altitude3;
	double azimuth2, altitude2, azimuth4, altitude4;
	double julDay3, julDay4, julDayHolder;
	double a, b, c, n0;
	int flag;

	flag = 0;
	julDay2 = julDayHolder = julDay1;
	julDay1 -= timeAdjust;
	julDay3 = julDay2 + timeAdjust;
	CPlanet::azimuthAltitudePlanet(julDay1, latitude, longitude,
									azimuth1, altitude1);
	CPlanet::azimuthAltitudePlanet(julDay2, latitude, longitude,
									azimuth2, altitude2);
	CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
									azimuth3, altitude3);

	while(	  altitude3 > altitude2
		  &&  flag < 8)
	{
		julDay4 = julDay3 + timeAdjust;
		CPlanet::azimuthAltitudePlanet(julDay4, latitude, longitude,
									   azimuth4, altitude4);
		julDay1 = julDay2;
		julDay2 = julDay3;
		julDay3 = julDay4;
		altitude1 = altitude2;
		altitude2 = altitude3;
		altitude3 = altitude4;
		flag +=1;
	}

	if(flag < 1)
	{
		while(	  altitude1 > altitude2
			  &&  flag < 8)
		{
			julDay4 = julDay1 - timeAdjust;
			CPlanet::azimuthAltitudePlanet(julDay4, latitude, longitude,
										   azimuth4, altitude4);
			julDay3 = julDay2;
			julDay2 = julDay1;
			julDay1 = julDay4;
			altitude3 = altitude2;
			altitude2 = altitude1;
			altitude1 = altitude4;
			flag +=1;
		}
	}

	if(flag > 7)
	{
		julDay2 = julDayHolder;
	}
	else
	{
		a = altitude2 - altitude1;
		b = altitude3 - altitude2;
		c = b - a;
		n0 = -(a+b) / 2*c;
		julDay2 += n0 * timeAdjust;
	}
}
//////////////////////////////////////////////////////////////////
//	This compares the altitude to a given height and adjusts the time
//	until the altitude is at that given height
//////////////////////////////////////////////////////////////////
int CPlanet::riseSetFinder(double julDay1, double jDLoLimit, double jDHiLimit, double latitude,
						   double longitude, double height, double timeAdjust, double &julDay2,
						   bool rise, int *countFlag)
{
	double azimuth1, altitude1, azimuth3, altitude3;
	double azimuth2, altitude2;
	double transfer, julDay3, dist, upper, factor;
	double accuracy, deltaTime, temp;
	int flag, stopFlag, step;

	flag = 0;
	*countFlag = 0;
	accuracy = 20;
	if(!rise)
	{
		timeAdjust *= -1.0;
	}
	deltaTime = timeAdjust;
	while(accuracy > 5)
	{
		stopFlag = 0;
		CPlanet::azimuthAltitudePlanet(julDay1, latitude, longitude,
										azimuth1, altitude1);
		*countFlag += 1;
		if(altitude1 > height)
		{
			julDay3 = julDay1 - timeAdjust;
			CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
										azimuth3, altitude3);
			*countFlag += 1;
			if(altitude3 > altitude1)
			{
				flag = 1;
				accuracy = 0;
			}
			else
			{
				dist = altitude1 - height;
				upper = altitude1 - altitude3;
				factor = dist / upper;
				step = 0;
				while (		altitude3	> height
						&&	factor		> 2
						&&	step		< 20)
				{
					step += 1;
					julDay1 = julDay3;
					altitude1 = altitude3;

					deltaTime = (factor - 1.5) * timeAdjust;
					temp = julDay3 - deltaTime;
					if(temp > jDHiLimit)
					{
						deltaTime = (julDay3 - jDHiLimit) / 2.0;
						if(fabs(deltaTime) < .0000001)
						{//	error
						}
						julDay3 -= deltaTime;
					}
					else if(temp < jDLoLimit)
					{
						deltaTime = (julDay3 - jDLoLimit) / 2.0;
						if(deltaTime < .0000001)
						{//	error
						}
						julDay3 -= deltaTime;
					}
					else
					{
						julDay3 = temp;
					}
					CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
												azimuth3, altitude3);
					*countFlag += 1;
					dist = altitude1 - height;
					upper = altitude1 - altitude3;
					factor = dist / upper;
				}
				while (		altitude3 > height 
						&&	altitude3 < altitude1
						&&	stopFlag  < 56)
				{
					altitude1 = altitude3;
					julDay1 = julDay3;
					julDay3 = julDay1 - timeAdjust;
					deltaTime = timeAdjust;
					CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
											azimuth3, altitude3);
					*countFlag += 1;
					stopFlag += 1;
					if(stopFlag > 55)
					{
						flag = 1;
						accuracy = 0;
					}
					if(altitude3 > altitude1)
					{
						flag = 1;
						accuracy = 0;
					}
				}
			}
		}

		if(altitude1 < height)
		{
			julDay3 = julDay1 + timeAdjust;
			CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
										azimuth3, altitude3);
			*countFlag += 1;
			if(altitude3 < altitude1)
			{
				flag = 2;
				accuracy = 0;
			}
			else
			{
				dist = height - altitude1;
				upper = altitude3 - altitude1;
				factor = dist / upper;
				step = 0;
				while (		altitude3	< height
							&&	factor	> 2
							&&	step	< 20)
				{
					step += 1;
					julDay1 = julDay3;
					altitude1 = altitude3;
					deltaTime = (factor - 1.5) * timeAdjust;
					temp = julDay3 + deltaTime;
					if(temp > jDHiLimit)
					{
						deltaTime = (jDHiLimit - julDay3) / 2.0;
						if(fabs(deltaTime) < .0000001)
						{//	error
						}
						julDay3 += deltaTime;
					}
					else if(temp < jDLoLimit)
					{
						deltaTime = (jDLoLimit - julDay3) / 2.0;
						if(deltaTime < .0000001)
						{//	error
						}
						julDay3 += deltaTime;
					}
					else
					{
						julDay3 = temp;
					}
					CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
												azimuth3, altitude3);
					*countFlag += 1;
					dist = height - altitude1;
					upper = altitude3 - altitude1;
					factor = dist / upper;
				}
				while (		altitude3 < height
						&&	altitude3 > altitude1
						&&	stopFlag < 56)
				{
					altitude1 = altitude3;
					julDay1 = julDay3;
					julDay3 = julDay1 + timeAdjust;
					deltaTime = timeAdjust;
					CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
											azimuth3, altitude3);
					*countFlag += 1;
					stopFlag += 1;
					if(stopFlag > 55)
					{
						flag = 2;
						accuracy = 0;
					}
					if(altitude3 < altitude1)
					{
						flag = 2;
						accuracy = 0;
					}
				}
				if(flag == 0)
				{
					transfer = altitude1;
					altitude1 = altitude3;
					altitude3 = transfer;
				
					transfer = julDay1;
					julDay1 = julDay3;
					julDay3 = transfer;
				}
			}
		}

		if (flag == 0)
		{
			dist = altitude1 - altitude3;
			upper = altitude1 - height;
			factor = upper / dist;
			julDay2 = julDay1 - (deltaTime * factor);
	
			CPlanet::azimuthAltitudePlanet(julDay2, latitude, longitude,
										azimuth2, altitude2);
			*countFlag += 1;
			accuracy = (fabs(altitude2 - height) / dist) * (deltaTime / timeAdjust) * (double)600;
			if(accuracy > 5)
			{
				if(accuracy < 20)
				{
					julDay1 = julDay2;
					timeAdjust /= 4;
					deltaTime = timeAdjust;
				}
				else
				{
					julDay1 = julDay2;
					deltaTime = timeAdjust;
				}
			}
		}
	}
	return flag;
}

//////////////////////////////////////////////////////////////////
//	This compares the azimuth to a given direction and adjusts the time
//	until the azimuth is at that given direction
//////////////////////////////////////////////////////////////////
void CPlanet::transitFinder(double julDay1, double latitude, double longitude,
							 double direction, double timeAdjust, double &julDay2,
							 int *countFlag)
{
	convert Convert;
	double azimuth1, altitude1, azimuth3, altitude3;
	double azimuth2, altitude2;
	double transfer, julDay3, dist, upper, factor, m_Pi;
	double accuracy, deltaTime;

	m_Pi = Convert.Pi();
	*countFlag = 0;
	accuracy = 20;
	deltaTime = timeAdjust;
	while(accuracy > 5)
	{
		CPlanet::azimuthAltitudePlanet(julDay1, latitude, longitude,
										azimuth1, altitude1);
		*countFlag += 1;
		if(direction < 3)azimuth1 = Convert.minusPiToPi(azimuth1);
		if(azimuth1 > direction)
		{
			julDay3 = julDay1 - timeAdjust;
			CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
										azimuth3, altitude3);
			*countFlag += 1;
			if(direction < 3)azimuth3 = Convert.minusPiToPi(azimuth3);
	
			dist = azimuth1 - direction;
			upper = azimuth1 - azimuth3;
			factor = dist / upper;
			if (factor > 2)
			{
				deltaTime = (factor - 1.5) * timeAdjust;
				julDay3 -= deltaTime;
				CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
											azimuth3, altitude3);
				*countFlag += 1;
				if(direction < 3)azimuth3 = Convert.minusPiToPi(azimuth3);
			}
			while (azimuth3 > direction)
			{
				azimuth1 = azimuth3;
				julDay1 = julDay3;
				julDay3 = julDay1 - timeAdjust;
				deltaTime = timeAdjust;
				CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
										azimuth3, altitude3);
				*countFlag += 1;
				if(direction < 3)azimuth3 = Convert.minusPiToPi(azimuth3);
			}
		}
	
		if(azimuth1 < direction)
		{
			julDay3 = julDay1 + timeAdjust;
			CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
										azimuth3, altitude3);
			*countFlag += 1;
			if(direction < 3)azimuth3 = Convert.minusPiToPi(azimuth3);
			dist = direction - azimuth1;
			upper = azimuth3 - azimuth1;
			factor = dist / upper;
			if (factor > 2)
			{
				deltaTime = (factor - 1.5) * timeAdjust;
				julDay3 += deltaTime;
				CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
											azimuth3, altitude3);
				*countFlag += 1;
				if(direction < 3)azimuth3 = Convert.minusPiToPi(azimuth3);
			}
			while (azimuth3 < direction)
			{
				azimuth1 = azimuth3;
				julDay1 = julDay3;
				julDay3 = julDay1 + timeAdjust;
				deltaTime = timeAdjust;
				CPlanet::azimuthAltitudePlanet(julDay3, latitude, longitude,
										azimuth3, altitude3);
				*countFlag += 1;
				if(direction < 3)azimuth3 = Convert.minusPiToPi(azimuth3);
			}
			transfer = azimuth1;
			azimuth1 = azimuth3;
			azimuth3 = transfer;
	
			transfer = julDay1;
			julDay1 = julDay3;
			julDay3 = transfer;
		}
		dist = azimuth1 - azimuth3;
		upper = azimuth1 - direction;
		factor = upper / dist;
		julDay2 = julDay1 - (deltaTime * factor);
	
		CPlanet::azimuthAltitudePlanet(julDay2, latitude, longitude,
										azimuth2, altitude2);
		*countFlag += 1;
		if(direction < 3)azimuth2 = Convert.minusPiToPi(azimuth2);

		accuracy = (fabs(azimuth2 - direction) / dist) * (deltaTime / timeAdjust) * (double)600;

		if(accuracy > 5)
		{
			if(accuracy < 20)
			{
				julDay1 = julDay2;
				timeAdjust /= 4;
				deltaTime = timeAdjust;
			}
			else
			{
				julDay1 = julDay2;
				deltaTime = timeAdjust;
			}
		}
	}
}

//	Find body location at time, find body location at time plus 1 day
//	subtract new longitude from original longitude.  Actual calculation 
//	of velocity would require converting this angular difference at this
//	radius and this amount of time into a velocity.  This is only good 
//	for planets (not moon)
void CPlanet::primaryBodyLocationVelocity(double julDay, double &Velocity)
{
	double L, B, R, newL, newB, newR;
	double newJulDay;

	newJulDay = julDay + (double)1;

	CPlanet::primaryBodyLocation(julDay, L, B, R);
	CPlanet::primaryBodyLocation(newJulDay, newL, newB, newR);

	Velocity = newL - L;
}

void CPlanet::geocentricLongitudeSun(double julDay, double &sunL)
{
	double sunB, R;

	CPlanet::geocentricSphericalTruePlanet(julDay, sunL, sunB, R);
}

//	page 156

	void CPlanet::sunDeltaLongitude(double julDay, double sunRadius,
							double &sunDeltaL)
{
	convert Convert;
	astrotime Astrotime;

	double tau;

	tau = Astrotime.calcJulianDayEphemeris(julDay);
	tau = Astrotime.calcJulianMillenia2000(tau);
	
	sunDeltaL =	(double)3548.193 +
	(double)118.568 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					  (double)87.5287 + (double)359993.7286 * tau))) +
	(double)2.476 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)85.0561 + (double)719987.4571 * tau))) +
	(double)1.376 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)27.8502 + (double)4452671.1152 * tau))) +
	(double)0.119 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)73.1375 + (double)450368.8564 * tau))) +
	(double)0.114 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)337.2264 + (double)329644.6718 * tau))) +
	(double)0.086 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)222.54 + (double)659289.3436 * tau))) +
	(double)0.078 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)162.8136 + (double)9224659.7915 * tau))) +
	(double)0.054 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)82.5823 + (double)1079981.1857 * tau))) +
	(double)0.052 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)171.5189 + (double)225184.4282 * tau))) +
	(double)0.034 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)30.3214 + (double)4092677.3866 * tau))) +
	(double)0.033 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)119.8105 + (double)337181.4711 * tau))) +
	(double)0.023 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)247.5418 + (double)299295.6151 * tau))) +
	(double)0.023 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)325.1526 + (double)315559.556 * tau))) +
	(double)0.021 * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)155.1241 + (double)675553.2846 * tau))) +
	(double)7.311 * tau * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)333.4515 + (double)359993.7286 * tau))) +
	(double)0.305 * tau  * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)330.9814 + (double)719987.4571 * tau))) +
	(double)0.01 * tau  * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)328.517 + (double)1079981.1857 * tau))) +
	(double)0.309 * tau  * tau  * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)241.4518 + (double)359993.7286 * tau))) +
	(double)0.021 * tau  * tau  * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)205.0482 + (double)719987.4571 * tau))) +
	(double)0.004 * tau  * tau  * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)297.861 + (double)4452671.1152 * tau))) +
	(double)0.01 * tau  * tau  * sin(Convert.degreeToRadian(Convert.degreeReduce(
					(double)154.7066 + (double)359993.7286 * tau)));

	sunDeltaL = Convert.degreeToRadian(-sunDeltaL * sunRadius * (double)0.0057755183 / (double)3600);
}
