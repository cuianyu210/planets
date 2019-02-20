#if !defined(AFX_STAR_H__ACC7C5C6_F6AF_4D95_AE7F_8CE7AF8431B3__INCLUDED_)
#define AFX_STAR_H__ACC7C5C6_F6AF_4D95_AE7F_8CE7AF8431B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Star.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStar window

class CStar : public CWnd
{
// Construction
public:
	CStar();
	CStar(class CTimeLocation* dick);
	void doStars(int iNumPlanets,
				 double julDay, double latitude, double longitude,int iMethod,
				 CString sDateString, CArray<int, int> *iConstList);
//	void showStars(CArray<int, int> *iConst, int NumPlanets,CStarData* pStarData);
	UINT MagConst();
/*	void LoadData(ifstream *infile,
				  CString name[],
				  CString namedName[],
				  CString latin[],
				  CString english[],
				  double alpha[],
				  double delta[],
				  double mag[],
				  int &iArraySize);
*/
	void MakePlanetStrings( double azimuth[], double altitude[],
							CString sPlanetAzimuthArray[], CString sPlanetAltitudeArray[],
							int pPlanetSet[]);
	void OutputPlanetData(int pPlanetSet[],
						  CString sPlanetAzimuthArray[],
						  CString sPlanetAltitudeArray[]);

// Attributes
public:

	class CTimeLocation* m_pTimeLocation;

	CString m_sDateString;// date string to be used for printing
	CString m_sMagnitude;//	magnitude string
	CString m_sViewDirection;
	double m_dMagnitude;//	limiting magnitude set by user
	double m_dLatitude;//	latitude of observer
	double m_dLongitude;//	longitude of observer
//	int	   m_iViewDirection;//  View direction as int
//	double m_dViewDirection;//	View direction for drawing

	int m_pPlanetSet[11];// array of planets with data
	double m_dPlanetAzimuth[11];//	array of azimuths for planet collection
	double m_dPlanetAltitude[11];// array of altitudes for planet collection
	double m_dPlanetMagnitude[11];// array of magnitudes for planet collection

	UINT m_iWhichStars;//	1 = mag only, 2 = const only, 3 = both
	int m_iStarNames;//	1 = print star names
	int m_iConNames;//	1 = print constellation names
	int m_iStarToFile;//	1 = print to file
	CString m_sStarFileName;//	File name for above

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAR_H__ACC7C5C6_F6AF_4D95_AE7F_8CE7AF8431B3__INCLUDED_)
