#if !defined(AFX_STARDATA_H__5F63E074_845D_43B5_8B93_B6EB290E32FE__INCLUDED_)
#define AFX_STARDATA_H__5F63E074_845D_43B5_8B93_B6EB290E32FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StarData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStarData window

class CStarData : public CWnd
{
// Construction
public:
	CStarData();

// Attributes
public:
	double m_dConstellationAzimuth[IDS_NUM_CON_STARS];
	double m_dConstellationAltitude[IDS_NUM_CON_STARS];
	CString m_sConstellationAzimuthString[IDS_NUM_CON_STARS];
	CString m_sConstellationAltitudeString[IDS_NUM_CON_STARS];
	static double m_dConstellationMagnitude[IDS_NUM_CON_STARS];	
	static CString m_sConstellationShortName[IDS_NUM_CON_STARS];
	static double m_dConstellationAlpha[IDS_NUM_CON_STARS];
	static double m_dConstellationDelta[IDS_NUM_CON_STARS];
	double m_dNonConstellationAzimuth[IDS_NUM_NON_CON_STARS];
	double m_dNonConstellationAltitude[IDS_NUM_NON_CON_STARS];
	CString m_sNonConstellationAzimuthString[IDS_NUM_NON_CON_STARS];
	CString m_sNonConstellationAltitudeString[IDS_NUM_NON_CON_STARS];
	static double m_dNonConstellationMagnitude[IDS_NUM_NON_CON_STARS];	
	static CString m_sNonConstellationShortName[IDS_NUM_NON_CON_STARS];

	int m_iNonConArraySize;
	int m_iConArraySize;

	static CString m_sConstellationFullName[IDS_NUM_CON_STARS];
	static CString m_sConstellationLatinConName[IDS_NUM_CON_STARS];
	static CString m_sNonConstellationFullName[IDS_NUM_NON_CON_STARS];
	static CString m_sNonConstellationLatinConName[IDS_NUM_NON_CON_STARS];
private:
	static double m_dNonConstellationAlpha[IDS_NUM_NON_CON_STARS];
	static double m_dNonConstellationDelta[IDS_NUM_NON_CON_STARS];

// Operations
public:
	void CalculatePositions(UINT uStars, double dMagnitude,
							double dJulDay, double dLatitude,
							double dLongitude);
	void OutputMagData(UINT uStar, CString sFileName, double dMagnitude);
	void OutputAllData(UINT uStar, CString sFileName);
	void CalcAll(double dMagnitude, double dJulDay,
				 double dLatitude, double dLongitude);
	void CalcByMag(UINT uStar, int iArraySize, double dMagnitude,
				   double dJulDay, double dLatitude, double dLongitude);
	void azimuthAltitude(double julDay,	double latitude, double longitude,
						 double alpha_0, double delta_0,
						 double &azimuth, double &altitude);
	void equatorialApp(double julDay, double alpha_0, double delta_0,
					   double &alpha, double &delta);
	void PrintData(UINT uStars, CString sFileName, double dMagnitude);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStarData)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStarData();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStarData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARDATA_H__5F63E074_845D_43B5_8B93_B6EB290E32FE__INCLUDED_)
