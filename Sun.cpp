// Sun.cpp : implementation file
//

#include "stdafx.h"
#include "Sun.h"
#include "Earth.h"
#include "astrotime.h"
#include "convert.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSun

CSun::CSun()
{
}

CSun::~CSun()
{
}


BEGIN_MESSAGE_MAP(CSun, CWnd)
	//{{AFX_MSG_MAP(CSun)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSun message handlers
void CSun::geocentricLongitudeSun(double julDay, double &sunL)

{

	CEarth Earth;
	convert Convert;
	astrotime Astrotime;
	
	double sunL0, sunL1, sunL2, sunL3, sunL4, sunL5;
	double JDE, time, arg, time2, time3, time4, time5;

	int i;
	
	sunL0 = sunL1 = sunL2 = sunL3 = sunL4 = sunL5 = 0;

	JDE = Astrotime.calcJulianDayEphemeris(julDay);
	time = Astrotime.calcJulianMillenia2000(JDE);
	
	time2 = time  * time;
	time3 = time2 * time;
	time4 = time3 * time;
	time5 = time4 * time;

	for ( i=1; i<=Earth.earthL0[0][0]; i++)
	{
		arg	= (Earth.earthL0[i][1] + Earth.earthL0[i][2] * time);
		arg = Convert.radianReduce(arg);
		sunL0 += Earth.earthL0[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthL1[0][0]; i++)
		{
		arg	= (Earth.earthL1[i][1] + Earth.earthL1[i][2] * time);
		arg = Convert.radianReduce(arg);
		sunL1 += Earth.earthL1[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthL2[0][0]; i++)
		{
		arg	= (Earth.earthL2[i][1] + Earth.earthL2[i][2] * time);
		arg = Convert.radianReduce(arg);
		sunL2 += Earth.earthL2[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthL3[0][0]; i++)
		{
		arg	= (Earth.earthL3[i][1] + Earth.earthL3[i][2] * time);
		arg = Convert.radianReduce(arg);
		sunL3 += Earth.earthL3[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthL4[0][0]; i++)
		{
		arg	= (Earth.earthL4[i][1] + Earth.earthL4[i][2] * time);
		arg = Convert.radianReduce(arg);
		sunL4 += Earth.earthL4[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthL5[0][0]; i++)
		{
		arg	= (Earth.earthL5[i][1] + Earth.earthL5[i][2] * time);
		arg = Convert.radianReduce(arg);
		sunL5 += Earth.earthL5[i][0] * cos(arg);
		}

	sunL =	sunL0 +
			sunL1 * time +
			sunL2 * time2 +
			sunL3 * time3 +
			sunL4 * time4 +
			sunL5 * time5;
	sunL += double(3.141592654);
	sunL = Convert.radianReduce(sunL);
	sunL = Convert.radianPositiveValue(sunL);
}


void CSun::geocentricLatitudeSun(double julDay, double &sunB)
{

	CEarth Earth;
	convert Convert;
	astrotime Astrotime;
	
	double sunB0, sunB1, sunB2, sunB3, sunB4;
	double JDE, time, arg, time2, time3, time4, time5;
	int i;
	
	sunB0 = sunB1 = sunB2 = sunB3 = sunB4 = 0;

	JDE = Astrotime.calcJulianDayEphemeris(julDay);
	time = Astrotime.calcJulianMillenia2000(JDE);
	
	time2 = time  * time;
	time3 = time2 * time;
	time4 = time3 * time;
	time5 = time4 * time;

	for ( i=1; i<=Earth.earthB0[0][0]; i++)
		{
		arg	= Earth.earthB0[i][1] + Earth.earthB0[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunB0 += Earth.earthB0[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthB1[0][0]; i++)
		{
		arg	= Earth.earthB1[i][1] + Earth.earthB1[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunB1 += Earth.earthB1[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthB2[0][0]; i++)
		{
		arg	= Earth.earthB2[i][1] + Earth.earthB2[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunB2 += Earth.earthB2[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthB3[0][0]; i++)
		{
		arg	= Earth.earthB3[i][1] + Earth.earthB3[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunB3 += Earth.earthB3[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthB4[0][0]; i++)
		{
		arg	= Earth.earthB4[i][1] + Earth.earthB4[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunB4 += Earth.earthB4[i][0] * cos(arg);
		}

	sunB =	sunB0 +
			sunB1 * time +
			sunB2 * time2 +
			sunB3 * time3 +
			sunB4 * time4;
	sunB = -Convert.radianReduce(sunB);
}


void CSun::geocentricRadiusSun(double julDay, double &sunR)
{

	CEarth Earth;
	convert Convert;
	astrotime Astrotime;
	
	double sunR0, sunR1, sunR2, sunR3, sunR4, sunR5;
	double JDE, time, arg, time2, time3, time4, time5;
	int i;
	
	sunR0 = sunR1 = sunR2 = sunR3 = sunR4 = sunR5 = 0;

	JDE = Astrotime.calcJulianDayEphemeris(julDay);
	time = Astrotime.calcJulianMillenia2000(JDE);
	
	time2 = time  * time;
	time3 = time2 * time;
	time4 = time3 * time;
	time5 = time4 * time;

	for ( i=1; i<=Earth.earthR0[0][0]; i++)
		{
		arg	= Earth.earthR0[i][1] + Earth.earthR0[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunR0 += Earth.earthR0[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthR1[0][0]; i++)
		{
		arg	= Earth.earthR1[i][1] + Earth.earthR1[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunR1 += Earth.earthR1[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthR2[0][0]; i++)
		{
		arg	= Earth.earthR2[i][1] + Earth.earthR2[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunR2 += Earth.earthR2[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthR3[0][0]; i++)
		{
		arg	= Earth.earthR3[i][1] + Earth.earthR3[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunR3 += Earth.earthR3[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthR4[0][0]; i++)
		{
		arg	= Earth.earthR4[i][1] + Earth.earthR4[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunR4 += Earth.earthR4[i][0] * cos(arg);
		}

	for ( i=1; i<=Earth.earthR5[0][0]; i++)
		{
		arg	= Earth.earthR5[i][1] + Earth.earthR5[i][2] * time;
		arg = Convert.radianReduce(arg);
		sunR5 += Earth.earthR5[i][0] * cos(arg);
		}

	sunR =	sunR0 +
			sunR1 * time +
			sunR2 * time2 +
			sunR3 * time3 +
			sunR4 * time4 +
			sunR5 * time5;
}

void CSun::geocentricSphericalTrueSun(double julDay, double &sunLambda,
		  double &sunBeta, double &sunRadius)
{
	//astrocalc smith;

	CSun::geocentricLongitudeSun(julDay, sunLambda);
	CSun::geocentricLatitudeSun(julDay, sunBeta);
	CSun::geocentricRadiusSun(julDay, sunRadius);
}
