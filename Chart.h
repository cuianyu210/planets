#if !defined(AFX_CHART_H__CC7A9F14_3F3E_4C6A_963A_8A7376A999D5__INCLUDED_)
#define AFX_CHART_H__CC7A9F14_3F3E_4C6A_963A_8A7376A999D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Chart.h : header file
//
#include "PlanetTime.h"
/////////////////////////////////////////////////////////////////////////////
// CChart window

class CChart : public CWnd
{
// Construction
public:
	CChart();

// Attributes
public:
	CString m_sName;
	double m_dBody[11];				//	Hour Angle of body
	double m_dBodyDec[11];			//	Declination of body
	double m_dBodyAspect[55];		//	Angular separation of body pairs
	CString m_sBodyAspect[55];		//	String version of m_dBodyAspect[55]
	int m_iBodyAspect[55];			//	0 / 1 : no aspect / aspect
	CString m_sBodySignLocation[11];//	Name of body sign with value
	int m_iBodySign[11];			//	Number of body sign
	int m_iBodyHouse[11];			//	Number of body house
	double m_dHouse[14];			//	House positions
	CString m_sHouseSign[14];		//	House signs
	CString m_sBodyString[11];		//	Set of "Venus 12 Gem 26 R" strings
	CString m_sBodyNames[11];		//	Body Names
	double m_dBodyHousePosition[11];//	How far each body is in its house
	CString m_sSignNames[12];		//	List of sign names
	CString m_sSignNamesShort[12];	//	List of short sign names
	CString m_sRetrograde[11];		//	"R" if retrograde.  Even though only 8 of the 
									//	planets can be retrograde, all must be included
									//	because of how the array is processed.  The
									//	others are just set to "".
	CString m_sNumMasculine;		//	number of bodies that are Masculine
	CString m_sNumFeminine;			//	number of bodies that are Feminine
	CString m_sNumFire;				//	number of bodies that are Fire
	CString m_sNumEarth;			//	number of bodies that are Earth
	CString m_sNumAir;				//	number of bodies that are Air
	CString m_sNumWater;			//	number of bodies that are Water
	CString m_sNumCardinal;			//	number of bodies that are Cardinal
	CString m_sNumFixed;			//	number of bodies that are Fixed
	CString m_sNumMutable;			//	number of bodies that are Mutable


// Operations
public:
	void CalculateHouses(CPlanetTime *time);
	void PlaceHousesInSigns();
	void PlaceBodiesInHouses();
	void PlaceBodiesInSigns();
	void CalculateAspects();
	void AnalyzeAspects();
	void RadToString(double value, CString *sNum);
	void MakeBodyStrings();
	void CalculateTriplicities();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChart)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChart();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChart)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHART_H__CC7A9F14_3F3E_4C6A_963A_8A7376A999D5__INCLUDED_)
