#if !defined(AFX_MOONPHASE_H__3545AE59_F5AE_41A4_960A_2E224B5701CA__INCLUDED_)
#define AFX_MOONPHASE_H__3545AE59_F5AE_41A4_960A_2E224B5701CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoonPhase.h : header file
//
#include "TimeLocation.h"
#include "Planet.h"
/////////////////////////////////////////////////////////////////////////////
// CMoonPhase window

enum moonPhase
{
	NEW_MOON,
	FIRST_QUARTER,
	FULL_MOON,
	THIRD_QUARTER,
	NEXT_QUARTER,
	PREVIOUS_QUARTER
};

class CMoonPhase : public CWnd
{
// Construction
public:
	CMoonPhase();

	double phase2(double julDay, ULONG uPhase, ULONG *PHASEFOUND);
	double FindNextQuarter(double julDay,
						   double difFract,
						   ULONG uPHASE);
	double DifferenceFraction(double dif);
	double TimeToStartSearch(ULONG LASTPHASE,
							 ULONG FINDPHASE,
							 double julDay);
	double AngleDifference(double julDay);
	ULONG LastPhase(double posDif);

//	Calculate for whole year
	void WholeYear(class CMoonDialog *pMD, double julDay);
	void writeHeader(double julDay, ULONG lastPHASE);
	void writeValue(double time, ULONG uPHASE);
	void nextPhase(ULONG &last, ULONG &current);

// Attributes
public:
	CPlanet m_pSun;
	CPlanet m_pMoon;
	CString m_sFileName;//	Save file name

	double m_dMeanLunarMonth;
	double m_dPi;
	double m_dPiOver2;

	class CMoonDialog* m_pMoonDlg;

	double m_dJulDay;

	bool m_bParametersCalculated;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoonPhase)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMoonPhase();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMoonPhase)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOONPHASE_H__3545AE59_F5AE_41A4_960A_2E224B5701CA__INCLUDED_)
