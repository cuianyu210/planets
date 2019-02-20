#if !defined(AFX_PLANET_H__6CA3171C_78EA_44C2_AB55_E7616FEB57F4__INCLUDED_)
#define AFX_PLANET_H__6CA3171C_78EA_44C2_AB55_E7616FEB57F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPlanet window

struct date_LBR_Values
{
	UINT body;
	double date;
	double pL;
	double pB;
	double pR;
};

class CPlanet : public CWnd
{
// Construction
public:
	CPlanet();

// Attributes
public:
private:
	UINT m_iName;

// Operations
public:
	void sun();
	void moon();
	void mercury();
	void venus();
	void earth();
	void mars();
	void jupiter();
	void saturn();
	void uranus();
	void neptune();
	void pluto();
	void sunL();

	void primaryBodyLocation(double julDay, double &planetL,
							 double &planetB, double &planetR);
	void heliocentricCartesianPlanet(double julDay, double &X,
									 double &Y, double &Z);
	void geocentricCartesianTruePlanet(double julDay, double &Ex,
									   double &Ey, double &Ez);
	void geocentricSphericalTruePlanet(double julDay, double &Lambda,
									   double &Beta, double &Radius);
	void geocentricSphericalAppPlanet(double julDay, double &Lambda,
									  double &Beta, double &Radius);
	void equatorialAppPlanet(double julDay, double &Alpha,
							 double &Delta, double &Radius);
	void azimuthAltitudePlanet(double julDay, double latitude,
							   double longitude, double &Azimuth, double &Altitude);
	void riseSetTransitPlanet(double julDay, double latitude,
							  double longitude, double &hourAngleRise,
							  double &hourAngleTransit, double &hourAngleSet,
							  double &hourAngleExtra, int i, double timeCorrection,
							  int &specialFlag);
	void primaryBodyLocationVelocity(double julDay, double &Velocity);
	void geocentricLongitudeSun(double julDay, double &sunL);
	void sunDeltaLongitude(double julDay, double sunRadius,
						   double &sunDeltaL);
	int  riseSetFinder(double julDay1, double jDLoLimit, double jDHiLimit,
					   double latitude, double longitude, double height,
					   double timeAdjust, double &julDay2, bool rise, int *countFlag);
	void transitFinder(double julDay1, double latitude, double longitude,
					   double height, double timeAdjust, double &julDay2,
							 int *countFlag);
	void AdjustTransitParameters(double *latitude, double delta, 
								 double *testValue, double *timeAdjust);
	void FindTransitFraction(double julDay, double longitude, 
							 double *julDayZero, double *julDayZeroUT, 
							 double *transitFraction, double *delta2,
							 double *radius2);
	void Find_m_dH0(double radm_h0, double latitude, double delta2, double *m_dCosH);
	double FindNewStartTime(double julDay, double * newjulDayZeroUT, double radm_h0,
							double latitude, double longitude, bool type);
	void timeOfHighestPoint(double julDay1, double latitude, double longitude,
							 double timeAdjust, double &julDay2);
	void timeOfLowestPoint(double julDay1, double latitude, double longitude,
							 double timeAdjust, double &julDay2);
	void findHighLatRiseSet(double startTime, double increment, double latitude,
					 double longitude, int &countFlag, double &riseTime,
					 double &setTime, double height, double &extraTime, int &specialFlag);
	void findMinMax(double latitude, double longitude, double time1, double time2,
					double time3, double alt1, double alt2, double alt3,
					double &timeExt, double &altExt, int &countFlag, bool min);
	double extremeValue(double timeOne, double timeTwo, double timeThree,
					    double altOne, double altTwo, double altThree);
	void azimuthAltitudeFromEquatorialApp(double julDay,
										  double latitude, double longitude,
										  double Alpha, double Delta,
										  double &Azimuth, double &Altitude);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlanet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPlanet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlanet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLANET_H__6CA3171C_78EA_44C2_AB55_E7616FEB57F4__INCLUDED_)
