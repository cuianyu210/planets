// astrocalc.cpp : implementation file
//

#include "stdafx.h"
#include "astrocalc.h"
#include "Planet.h"
#include <math.h>
#include "convert.h"
#include "astrotime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// astrocalc

astrocalc::astrocalc()
{
}

astrocalc::~astrocalc()
{
}


BEGIN_MESSAGE_MAP(astrocalc, CWnd)
	//{{AFX_MSG_MAP(astrocalc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// astrocalc message handlers

//	Calculates the mean anomaly of the Earth.  See Meeus Ch 21 P 132
//	Formula on page 151 is less accurate
double astrocalc::meanAnomalyEarth(double julDay)
{
	double julDayEph, anom, T;
	convert Convert;
	astrotime Astrotime;

	julDayEph = Astrotime.calcJulianDayEphemeris(julDay);
	T = Astrotime.calcJulianCenturies2000(julDayEph);

	anom =	(double)357.52772 +
			(double)35999.05034 * T -
			(double)0.0001603 * T*T -
			T*T*T / (double)300000;
	anom = Convert.degreeReduce(anom);
	if (anom < 0) anom += ((double)360);
	anom = Convert.degreeToRadian(anom);

	return (anom);
}

//	Calculates nutation in longitude of the Earth.
//  See Meeus Ch 21 P 132
double astrocalc::nutationInLongitude(double julDay)
{
	double julDayEph, D, M, M1, F, Om, T, dPsi;
	convert Convert;
	astrotime Astrotime;

	julDayEph = Astrotime.calcJulianDayEphemeris(julDay);
	T = Astrotime.calcJulianCenturies2000(julDayEph);
	M = astrocalc::meanAnomalyEarth(julDay);

	D =	(double)297.85036 +
		(double)445267.11148 * T -
		(double)0.0019142 * T*T +
		T*T*T / (double)189474;
	D = Convert.degreeReduce(D);
	if (D < 0) D += ((double)360);
	D = Convert.degreeToRadian(D);

	M1 = (double)134.96298 +
		 (double)477198.867398 * T +
		 (double)0.0086972 * T*T +
		 T*T*T / (double)56250;
	M1 = Convert.degreeReduce(M1);
	if (M1 < 0) M1 += ((double)360);
	M1 = Convert.degreeToRadian(M1);


	F =	(double)93.27191 +
		(double)483202.017538 * T -
		(double)0.0036825 * T*T +
		T*T*T / (double)327270;
	F = Convert.degreeReduce(F);
	if (F < 0) F += ((double)360);
	F = Convert.degreeToRadian(F);

	Om = (double)125.04452 -
		 (double)1934.136261 * T +
		 (double)0.0020708 * T*T +
		 T*T*T / (double)450000;
	Om = Convert.degreeReduce(Om);
	if (Om < 0) Om += ((double)360);
	Om = Convert.degreeToRadian(Om);

	dPsi =	(-(double)171996 - 174.2 * T) * sin(Om) +
			(-(double)13187 - 1.6 * T) * sin(F * 2 - D * 2 + Om * 2) +
			(-(double)2274 - 0.2 * T) *	sin(F * 2 + Om * 2) +
			(+(double)2062 + 0.2 * T) *	sin(Om * 2)+
			(+(double)1426 - 3.4 * T) *	sin(M) +
			(+(double)712 + 0.1 * T) *	sin(M1) +
			(-(double)517 + 1.2 * T) *	sin(F * 2 + Om * 2 - D * 2 + M) +
			(-(double)386 - 0.4 * T) *	sin(F * 2 + Om) +
			(-(double)301) *			sin(F * 2 + Om * 2 + M1) +
			(+(double)217 - 0.5 * T) *	sin(F * 2 + Om * 2 - D * 2 - M) +
			(-(double)158) *			sin(M1 - D * 2) +
			(+(double)129 + 0.1 * T) *	sin(F * 2 + Om - D * 2) +
			(+(double)123) *			sin(F * 2 + Om * 2 - M1) +
			(+(double)63) *				sin(D * 2) +
			(+(double)63 + 0.1 * T) *	sin(M1 + Om) +
			(-(double)59) *				sin(F * 2 + Om * 2 + D * 2 - M1) +
			(-(double)58 - 0.1 * T) *	sin(Om - M1) +
			(-(double)51) *			sin(F * 2 + Om + M1) +
			(+(double)48) *			sin(M1 * 2 - D * 2) +
			(+(double)46) *			sin(F * 2 + Om - M1 * 2) +
			(-(double)38) *			sin(F * 2 + Om * 2 + D * 2) +
			(-(double)31) *			sin(F * 2 + Om * 2 + M1 * 2) +
			(+(double)29) *			sin(M1 * 2) +
			(+(double)29) *			sin(F * 2 + Om * 2 - D * 2 + M1) +
			(+(double)26) *			sin(F * 2) +
			(-(double)22) *			sin(F * 2 - D * 2) +
			(+(double)21) *			sin(F * 2 + Om - M1) +
			(+(double)17 - 0.1 * T) *	sin(M * 2) +
			(+(double)16) *				sin(Om - M1 + D * 2) +
			(-(double)16 + 0.1 * T) *	sin(F * 2 + Om * 2 - D * 2 + M * 2) +
			(-(double)15) *			sin(M + Om) +
			(-(double)13) *			sin(Om - D * 2 + M1) +
			(-(double)12) *			sin(Om - M) +
			(+(double)11) *			sin(- F * 2 + M1 * 2) +
			(-(double)10) *			sin(F * 2 + Om + D * 2 - M1) +
			(-(double)8) *			sin(F * 2 + Om * 2 + D * 2 + M1) +
			(+(double)7) *			sin(F * 2 + Om * 2 + M) +
			(-(double)7) *			sin(- D * 2 + M + M1) +
			(-(double)7) *			sin(F * 2 + Om * 2 - M) +
			(-(double)7) *			sin(F * 2 + Om + D * 2) +
			(+(double)6) *			sin(D * 2 + M1) +
			(+(double)6) *			sin(F * 2 + Om * 2 - D * 2 + M1 * 2) +
			(+(double)6) *			sin(F * 2 + Om - D * 2 + M1) +
			(-(double)6) *			sin(Om + D * 2 - M1 * 2) +
			(-(double)6) *			sin(Om + D * 2) +
			(+(double)5) *			sin(- M + M1) +
			(-(double)5) *			sin(F * 2 + Om - D * 2 - M) +
			(-(double)5) *			sin(Om - D * 2) +
			(-(double)5) *			sin(F * 2 + Om + M1 * 2) +
			(+(double)4) *			sin(Om - D * 2 + M1 * 2) +
			(+(double)4) *			sin(F * 2 + Om - D * 2 + M) +
			(+(double)4) *			sin(- F * 2 + M1) +
			(-(double)4) *			sin(- D + M1) +
			(-(double)4) *			sin(- D * 2 + M) +
			(-(double)4) *			sin(D) +
			(+(double)3) *			sin(F * 2 + M1) +
			(-(double)3) *			sin(F * 2 + Om * 2 - M1 * 2) +
			(-(double)3) *			sin(- D - M + M1) +
			(-(double)3) *			sin(M + M1) +
			(-(double)3) *			sin(F * 2 + Om * 2 - M + M1) +
			(-(double)3) *			sin(F * 2 + Om * 2 + D * 2 - M - M1) +
			(-(double)3) *			sin(F * 2 + Om * 2 + 3 * M1) +
			(-(double)3) *			sin(F * 2 + Om * 2 + D * 2 - M);

		dPsi = dPsi / (double)100000000;
		dPsi = Convert.DMSToDegree(dPsi);
		dPsi = Convert.degreeToRadian(dPsi);

		return (dPsi);
	}

//	Calculates nutation in obliquity of the Earth.
//  See Meeus Ch 21 P 132
double astrocalc::nutationInObliquity(double julDay)
{
	double julDayEph, D, M, M1, F, Om, T, dEps;
	convert Convert;
	astrotime Astrotime;

	julDayEph = Astrotime.calcJulianDayEphemeris(julDay);
	T = Astrotime.calcJulianCenturies2000(julDayEph);
	M = astrocalc::meanAnomalyEarth(julDay);

	D = (double)297.85036 +
		(double)445267.11148 * T -
		(double)0.0019142 * T*T +
		T*T*T / (double)189474;
	D = Convert.degreeReduce(D);
	if (D < 0) D += ((double)360);
	D = Convert.degreeToRadian(D);

	M1 =	(double)134.96298 +
			(double)477198.867398 * T +
			(double)0.0086972 * T*T +
			T*T*T / (double)56250;
	M1 = Convert.degreeReduce(M1);
	if (M1 < 0) M1 += ((double)360);
	M1 = Convert.degreeToRadian(M1);

	F = (double)93.27191 +
		(double)483202.017538 * T -
		(double)0.0036825 * T*T +
		T*T*T / (double)327270;
	F = Convert.degreeToRadian(F);
	F = Convert.degreeReduce(F);
	if (F < 0) F += ((double)360);

	Om =	(double)125.04452 -
			(double)1934.136261 * T +
			(double)0.0020708 * T*T +
			T*T*T / (double)450000;
	Om = Convert.degreeReduce(Om);
	if (Om < 0) Om += ((double)360);
	Om = Convert.degreeToRadian(Om);

	dEps =	(+(double)92025 + 8.9 * T) * cos(Om) +
			(+(double)5736 - 3.1 * T) *	 cos(F * 2 - D * 2 + Om * 2) +
			(+(double)977 - 0.5 * T) *	 cos(F * 2 + Om * 2) +
			(-(double)895 + 0.5 * T) *	 cos(Om * 2) +
			(+(double)54 - 0.1 * T) *	 cos(M) +
			(-(double)7) *				 cos(M1) +
			(+(double)224 - 0.6 * T) *	 cos(F * 2 + Om * 2 - D * 2 + M) +
			(+(double)200) *			 cos(F * 2 + Om) +
			(+(double)129 - 0.1 * T) *	 cos(F * 2 + Om * 2 + M1) +
			(-(double)95 + 0.3 * T) *	 cos(F * 2 + Om * 2 - D * 2 - M) +
  			(-(double)70) *	cos(F * 2 + Om - D * 2) +
			(-(double)53) * cos(F * 2 + Om * 2 - M1) +
			(-(double)33) * cos(M1 + Om) +
			(+(double)26) * cos(F * 2 + Om * 2 + D * 2 - M1) +
			(+(double)32) * cos(Om - M1) +
			(+(double)27) * cos(F * 2 + Om + M1) +
			(-(double)24) * cos(F * 2 + Om - M1 * 2) +
			(+(double)16) * cos(F * 2 + Om * 2 + D * 2) +
			(+(double)13) * cos(F * 2 + Om * 2 + M1 * 2) +
			(-(double)12) * cos(F * 2 + Om * 2 - D * 2 + M1) +
			(-(double)10) * cos(F * 2 + Om - M1) +
			(-(double)8) *	cos(Om - M1 + D * 2) +
			(+(double)7) *	cos(F * 2 + Om * 2 - D * 2 + M * 2) +
			(+(double)9) *	cos(M + Om) +
			(+(double)7) *	cos(Om - D * 2 + M1) +
			(+(double)6) *	cos(Om - M) +
			(+(double)5) *	cos(F * 2 + Om + D * 2 - M1) +
			(+(double)3) *	cos(F * 2 + Om * 2 + D * 2 + M1) +
			(-(double)3) *	cos(F * 2 + Om * 2 + M) +
			(+(double)3) *	cos(F * 2 + Om * 2 - M) +
			(+(double)3) *	cos(F * 2 + Om + D * 2) +
			(-(double)3) *	cos(F * 2 + Om * 2 - D * 2 + M1 * 2) +
			(-(double)3) *	cos(F * 2 + Om - D * 2 + M1) +
			(+(double)3) *	cos(Om + D * 2 - M1 * 2) +
			(+(double)3) *	cos(Om + D * 2) +
			(+(double)3) *	cos(F * 2 + Om - D * 2 - M) +
			(+(double)3) *	cos(Om - D * 2) +
			(+(double)3) *	cos(F * 2 + Om + M1 * 2);

		dEps = dEps / (double)100000000;
		dEps = Convert.DMSToDegree(dEps);
		dEps = Convert.degreeToRadian(dEps);

	return (dEps);
}
	
//	Calculates mean obliquity of the ecliptic
//  See Meeus Ch 21 P 135
double astrocalc::meanObliquityOfEcliptic(double julDay)
{
	double julDayEph, U, eps_naught;
	convert Convert;
	astrotime Astrotime;

	julDayEph = Astrotime.calcJulianDayEphemeris(julDay);
	U = Astrotime.calcJulianCenturies2000(julDayEph) / (double)100;

	eps_naught = (double)23.4392911 +
				 ((- (double)4680.93 * U -
				 (double)1.55 	* U*U +
				 (double)1999.25 * U*U*U -
				 (double)51.38	* U*U*U*U -
				 (double)249.67	* U*U*U*U*U -
				 (double)39.05	* U*U*U*U*U*U +
				 (double)7.12	* U*U*U*U*U*U*U +
				 (double)27.87	* U*U*U*U*U*U*U*U +
				 (double)5.79	* U*U*U*U*U*U*U*U*U +
				 (double)2.45	* U*U*U*U*U*U*U*U*U*U) /
				 (double)3600);

	eps_naught = Convert.degreeToRadian(eps_naught);

	return(eps_naught);
}
	
//	Calculates true obliquity of the ecliptic
//  See Meeus Ch 21 P 132
double astrocalc::trueObliquityOfEcliptic(double julDay)
{
	double meanObOfEclip, trueE, delEps;
		
	meanObOfEclip = astrocalc::meanObliquityOfEcliptic(julDay);
	delEps = astrocalc::nutationInObliquity(julDay);

	trueE = meanObOfEclip + delEps;

	return trueE;
}

//	Calculates eccentricity of Earth's orbit
//  See Meeus Ch 22 Page 139
double astrocalc::eccentricityEarthOrbitJulDay(double julDay)
{
	double julDayEph, e1, T;
	astrotime Astrotime;

	julDayEph = Astrotime.calcJulianDayEphemeris(julDay);
	T = Astrotime.calcJulianCenturies2000(julDayEph);
	e1 = eccentricityEarthOrbitT(T);

	return (e1);
}

//	Calculates eccentricity of Earth's orbit
//  See Meeus Ch 22 Page 139
double astrocalc::eccentricityEarthOrbitT(double T)
{
	double e1;

	e1 = (double)0.016708617 -
		 (double)0.000042037 * T -
		 (double)0.0000001236 * T*T;

	return (e1);
}

//	Calculates longitude of perihelion of Earth's orbit
//  See Meeus Ch 22 Page 139
double astrocalc::longitudePerihelionEarth(double julDay)
{
	double julDayEph, pe, T;
	convert Convert;
	astrotime Astrotime;

	julDayEph = Astrotime.calcJulianDayEphemeris(julDay);
	T = Astrotime.calcJulianCenturies2000(julDayEph);

	pe = (double)102.93735 +
		 (double)0.71953 * T +
		 (double)0.00046 * T*T;

	pe = Convert.degreeToRadian(pe);
	
	return (pe);
}
//	Annual aberration due to Earth's orbit
//	p. 139
void astrocalc::aberration(double julDay, double lambda, double beta,
				  double &delLambda, double &delBeta)
{
	CPlanet body;
	astrotime Astrotime;
	convert Convert;

	double e, pi, time, sunLon;
	double k = 20.49552;

	k = Convert.degreeToRadian(k / double(3600));
	time = Astrotime.calcJulianCenturies2000(julDay);
	body.sunL();
	body.geocentricLongitudeSun(julDay, sunLon);
	
	e = astrocalc::eccentricityEarthOrbitJulDay(julDay);
	pi = astrocalc::longitudePerihelionEarth(julDay);
	delLambda = (e * k * cos(pi - lambda) - k * cos(sunLon - lambda)) /
					cos(beta);
	delBeta = -k * sin(beta) * (sin(sunLon - lambda)-
			   e * sin(pi - lambda));
}
//	Convert to the FK5 system  Meeus p. 207
//	See also pp. 154 and 139
void astrocalc::convertToFk5(double julDay, double L, double B, double &fk5L, double &fk5B)
{
	convert Convert;
	astrotime Astrotime;

	double L1, delL, delB, time;

	time = Astrotime.calcJulianCenturies2000(julDay);

	L1 = L - Convert.degreeToRadian(time * (double) 1.397 + time * time * (double)0.00031);
	delL = Convert.degreeToRadian(((double)0.03916 * (cos(L1) + sin(L1)) * tan(B) - .09033) / (double) 3600);
	delB = Convert.degreeToRadian(((cos(L1) - sin(L1)) * (double)0.03916) / (double)3600);

	fk5L = L + delL;
	fk5B = B + delB;
}

//	Given Body heliocentric lat, lon and rad, and Earth heliocentric lat, lon and rad
//	find geocentric Cartesian true of Body.
void astrocalc::geocentricCartesianTrue(double pL, double pB, double pR,
							 double eL, double eB, double eR,
							 double &x, double &y, double &z)
{
	x = pR * cos(pB) * cos(pL) - eR * cos(eB) * cos(eL);
	y = pR * cos(pB) * sin(pL) - eR * cos(eB) * sin(eL);
	z = pR * sin(pB) - eR * sin(eB);
}
//	lat, lon and radius from Cartesian

void astrocalc::cartesianToSpherical(double Ex, double Ey, double Ez,
				double &pLambda, double &pBeta, double &pRadius)
{
	convert Convert;

	Convert.cartesianToSpherical(Ex, Ey, Ez, pLambda, pBeta, pRadius);
	pLambda = Convert.radianPositiveValue(pLambda);
}


//	Converts Ecliptical coordinates (lambda and beta) to Equatorial
//	coordinates (alpha and delta, right ascension and declination)
void astrocalc::eclipticToEquatorial(double julDay, double lambda,
								   double beta, double &alpha,
								   double &delta)
{
	convert Convert;

	double eps;
	
	eps = astrocalc::trueObliquityOfEcliptic(julDay);

	alpha = atan2((sin(lambda) * cos(eps) - tan(beta) * sin(eps)), cos(lambda));
	alpha = Convert.radianPositiveValue(alpha);
	delta = asin(sin(beta) * cos(eps) + cos(beta) * sin(eps) * sin(lambda));
}


//	Converts Equatorial coordinates (alpha and delta, right ascension
//	and declinatin) to Ecliptical coordinates (lambda and beta)
void astrocalc::equatorialToEcliptic(double julDay, double alpha,
								   double delta, double &lambda,
								   double &beta)
{
	convert Convert;

	double eps;
	
	eps = astrocalc::trueObliquityOfEcliptic(julDay);

	lambda = atan2((sin(alpha) * cos(eps) + tan(delta) * sin(eps)), cos(alpha));
	lambda = Convert.radianPositiveValue(lambda);
	beta = asin(sin(delta) * cos(eps) - cos(delta) * sin(eps) * sin(alpha));
}

//	Input the year and return the time of the vernal equinox, summer solstice,
//	autumnal equinox and winter solstice.  One more vernal eqiunox is required 
//	for calculating the duration of winter.  See Meeus p. 165
void astrocalc::equinoxSolstice(double year, double &verEqui,
								double &sumSol, double &autEqui,
								double &winSol, double &verEqui2)
{
// type 0 = vernal equinox
// type 1 = summer solstice
// type 2 = autumnal equinox
// type 3 = winter solstice
// type 4 = next vernal equinox for calculating duration of winter

	CPlanet body;
	convert Convert;
	astrotime Astrotime;
	double year2, year3, year4, test;
	double deltaT, L, B, R, correction;
	double julDay, type[5];
	int i;

	if(year < 1000)
	{
		year /= (double)1000;
		year2 = year * year;
		year3 = year2 * year;
		year4 = year3 * year;

		type[0] = type[4] = 1721139.29189 +
	      					365242.13740 * year +
	    /*verEqui*/			0.06134 * year2 +
	      					0.00111 * year3 -
	      					0.00071 * year4;
	
		type[1] = 1721233.25401 +
					 365241.72562 * year -
		/*sumSol*/	 0.05323 * year2 +
					 0.00907 * year3 +
					 0.00025 * year4;
			
		type[2] = 1721325.70455 +
					 365242.49558 * year -
		/*autEqui*/  0.11677 * year2 -
					 0.00297 * year3 +
					 0.00074 * year4;

		type[3] = 1721414.39987 +
					 365242.88257 * year -
		/*winSol*/	 0.00769 * year2 -
					 0.00933 * year3 -
					 0.00006 * year4;
	}
	else
	{
		year = (year - (double)2000) / (double)1000;
		year2 = year * year;
		year3 = year2 * year;
		year4 = year3 * year;

		type[0] = type[4] = 2451623.80984 +
		      				365242.37404 * year +
		/*verEqui*/			0.05169 * year2 -
		   					0.00411 * year3 -
		   					0.00057 * year4;

		type[1] = 2451716.56767 +
					 365241.62603 * year +
		/*sumSol*/	 0.00325 * year2 +
					 0.00888 * year3 -
					 0.00030 * year4;

		type[2] = 2451810.21715 +
					 365242.01767 * year -
		/*autEqui*/	 0.11575 * year2 +
					 0.00337 * year3 +
					 0.00078 * year4;

		type[3] = 2451900.05952 +
					 365242.74049 * year +
		/*winSol*/	 0.06223 * year2 +
					 0.00823 * year3 -
					 0.00032 * year4;
	}
	type[4] += (double)365;

	body.sun();
	for(i=0; i<5; i++)
	{
		deltaT = Astrotime.deltaT(type[i]) / 86400;
		julDay = type[i] - deltaT;
		body.geocentricSphericalAppPlanet(julDay, L, B, R);
		if(i == 0 || i == 4)
		{
			L = Convert.minusPiToPi(L);
			test = -L;
		}
		else
		{
			test = ((double)i * 1.5707963268) - L;
		}
		while(fabs(test) > .000001)
		{
			correction = 58 * sin(test);
			type[i] += correction;
			julDay = type[i] - deltaT;
			body.geocentricSphericalAppPlanet(julDay, L, B, R);
			if(i == 0 || i == 4)
			{
				L = Convert.minusPiToPi(L);
				test = -L;
			}
			else
			{
				test = ((double)i * 1.5707963268) - L;
			}
		}
		type[i] = julDay;
	}
	verEqui = type[0];
	sumSol = type[1];
	autEqui = type[2];
	winSol = type[3];
	verEqui2 = type[4];
}

//	See Meeus Ch. 49 p. 333
double astrocalc::MoonAscNode(double julDay)
{
	astrotime Astrotime;
	convert Convert;
	double NNode, JDE, T;

	JDE = Astrotime.calcJulianDayEphemeris(julDay);
	T = Astrotime.calcJulianCenturies2000(JDE);

	NNode =	125.044555 -
		   1934.1361849 * T +
			   .0020762 * T*T +
						  T*T*T / (double)467410 -
						  T*T*T*T / (double)60616000;
	NNode = Convert.degreeToRadian(Convert.degreePositiveValue(Convert.degreeReduce(NNode)));
	return NNode;
}

//	Calculates the mean sidereal angle (time) for any time in
//	Julian centuries from 2000 January 1 00:00:00 UT.  Allowance
//	is NOT made for nutation or obliquity of the ecliptic.
//	See Meeus Ch 11.

double astrocalc::meanSiderealDegree(double julDay)
{
	double sidAngle, T;
	convert Convert;
	astrotime Astrotime;

	T = Astrotime.calcJulianCenturies2000(julDay);
	sidAngle = (double)280.46061837 +
		(double)360.98564736629 * (T * (double)36525) +
		(double)0.000387933 * T*T -
		T * T*T / (double)38710000;
	sidAngle = Convert.degreeReduce(sidAngle);
	sidAngle = Convert.degreePositiveValue(sidAngle);

	return (sidAngle);
}

//	Calculates sidereal time (radians) not adjusted for nutation
//	and obliquity of the ecliptic

double astrocalc::meanSiderealRadian(double julDay)
{
	double sidAngle;
	convert Convert;

	sidAngle = astrocalc::meanSiderealDegree(julDay);
	sidAngle = Convert.degreeToRadian(sidAngle);

	return (sidAngle);
}

//	Calculates sidereal time (hour) not adjusted for nutation
//	and obliquity of the ecliptic

double astrocalc::meanSiderealHour(double julDay)
{
	double sidTime;
	convert Convert;

	sidTime = astrocalc::meanSiderealDegree(julDay);
	sidTime = Convert.degreeToHour(sidTime);

	return (sidTime);
}

//	Calculates sidereal time (HMS) not adjusted for nutation
//	and obliquity of the ecliptic

double astrocalc::meanSiderealHMS(double julDay)
{
	double sidTime;
	convert Convert;

	sidTime = astrocalc::meanSiderealHour(julDay);
	sidTime = Convert.hourToHMS(sidTime);

	return (sidTime);
}

//	Calculates the apparent sidereal angle for any time in Julian
//	centuries from 2000 January 1 00:00:00 UT.  Allowance is
//	made for nutation and obliquity of the ecliptic.
//	See Meeus Ch 11.

double astrocalc::apparSiderealDegree(double julDay)
{
	double sidAngle;
	convert Convert;

	sidAngle = astrocalc::apparSiderealRadian(julDay);
	sidAngle = Convert.radianToDegree(sidAngle);

	return (sidAngle);
}

double astrocalc::apparSiderealRadian(double julDay)
{

	double sidAngle, dPsi, trueE;
	convert Convert;
	astrocalc Astrocalc;

	sidAngle = astrocalc::meanSiderealRadian(julDay);
	dPsi = Astrocalc.nutationInLongitude(julDay);
	trueE = Astrocalc.trueObliquityOfEcliptic(julDay);

	sidAngle += (dPsi * cos(trueE));
	sidAngle = Convert.radianReduce(sidAngle);
	sidAngle = Convert.radianPositiveValue(sidAngle);

	return (sidAngle);
}

double astrocalc::apparSiderealHour(double julDay)
{
	double sidTime;
	convert Convert;

	sidTime = astrocalc::apparSiderealDegree(julDay);
	sidTime = Convert.degreeToHour(sidTime);

	return (sidTime);
}

double astrocalc::apparSiderealHMS(double julDay)
{
	double sidTime;
	convert Convert;

	sidTime = astrocalc::apparSiderealHour(julDay);
	sidTime = Convert.hourToHMS(sidTime);

	return (sidTime);
}
