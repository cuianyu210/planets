#if !defined(AFX_ASTROCALC_H__7EFE3A4F_CE72_461A_B5B6_3D752D8C69C9__INCLUDED_)
#define AFX_ASTROCALC_H__7EFE3A4F_CE72_461A_B5B6_3D752D8C69C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// astrocalc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// astrocalc window

class astrocalc : public CWnd
{
// Construction
public:
	astrocalc();

// Attributes
public:

// Operations
public:
	// moved from astrotime LS 20190213
	double meanSiderealRadian(double julDay);
	double meanSiderealDegree(double julDay);
	double meanSiderealHour(double julDay);
	double meanSiderealHMS(double julDay);
	double apparSiderealRadian(double julDay);
	double apparSiderealDegree(double julDay);
	double apparSiderealHour(double julDay);
	double apparSiderealHMS(double julDay);
	double meanAnomalyEarth(double julDay);
	double nutationInLongitude(double julDay);
	double nutationInObliquity(double julDay);
	double meanObliquityOfEcliptic(double julDay);
	double trueObliquityOfEcliptic(double julDay);
	double eccentricityEarthOrbitJulDay(double julDay);
	double eccentricityEarthOrbitT(double T);
	double longitudePerihelionEarth(double julDay);
	void aberration(double julDay, double lambda, double beta,
				    double &delLambda, double &delBeta);
	void convertToFk5(double julDay, double L, double B, double &fk5L,
					  double &fk5B);
	void geocentricCartesianTrue(double pL, double pB, double pR, double eL,
					  double eB, double eR, double &x, double &y,
					  double &z);
	void cartesianToSpherical(double Ex, double Ey, double Ez,
				double &pLambda, double &pBeta, double &pRadius);
	void eclipticToEquatorial(double julDay, double lambda, double beta,
							  double &alpha, double &delta);
	void equatorialToEcliptic(double julDay, double alpha, double delta,
							  double &lambda, double &beta);
	void equinoxSolstice(double year, double &verEqui, double &sumSol,
						 double &autEqui, double &winSol, double &verEqui2);
	double MoonAscNode(double julDay);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(astrocalc)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~astrocalc();

	// Generated message map functions
protected:
	//{{AFX_MSG(astrocalc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASTROCALC_H__7EFE3A4F_CE72_461A_B5B6_3D752D8C69C9__INCLUDED_)
