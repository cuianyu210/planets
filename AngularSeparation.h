#if !defined(AFX_ANGULARSEPARATION_H__04A8FD21_813B_4D36_B610_14F98D1A2BE7__INCLUDED_)
#define AFX_ANGULARSEPARATION_H__04A8FD21_813B_4D36_B610_14F98D1A2BE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AngularSeparation.h : header file
//
#include "TimeLocation.h"
/////////////////////////////////////////////////////////////////////////////
// CAngularSeparation dialog

class CAngularSeparation : public CDialog
{
// Construction
public:
	CAngularSeparation(CWnd* pParent = NULL);   // standard constructor
	CAngularSeparation(class CTimeLocation* dick);
	CTimeLocation* m_pTimeLocation;
	double CalculateAngularSeparation(double alpha1, double alpha2,
									double delta1, double delta2);
	void CalculatePositionsGeocentric(double julDay, 
									  int body1, int body2,
									  double &L1, double &L2,
									  double &B1, double &B2);
	void CalculatePositionsHelioentric(double julDay,
									  int body1, int body2,
									  double &L1, double &L2,
									  double &B1, double &B2);
	void WriteProfiles();
	void FillBodyBox(int iWhich);
	void NoHelioWithStars();

	void SetBodyPlanet();
	void SetBodyConstellationStars();
	void SetBodyNamedStars();

	void GetStarNames();
	void SortStarNames();

// Dialog Data
	//{{AFX_DATA(CAngularSeparation)
	enum { IDD = IDD_ANGULAR_SEPARATION };
	CListBox	m_sBody2;
	CListBox	m_sBody1;
	CString	m_sAngSep;
	BOOL	m_bGeocentric;
	BOOL	m_bHeliocentric;
	BOOL	m_bPlanets1;
	BOOL	m_bStars1;
	BOOL	m_bPlanets2;
	BOOL	m_bStars2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAngularSeparation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	int m_iBody1;
	int m_iBody2;
	int m_iStarArraySize;
	CArray<int, int> m_iStarPlace;
	CArray<CString, CString> m_sStarShortNames;
	bool m_bChangedHelio;

	// Generated message map functions
	//{{AFX_MSG(CAngularSeparation)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnRun();
	afx_msg void OnPlanets1();
	afx_msg void OnStars1();
	afx_msg void OnHeliocentric();
	afx_msg void OnSelchangeBody1();
	afx_msg void OnSelchangeBody2();
	afx_msg void OnGeocentric();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANGULARSEPARATION_H__04A8FD21_813B_4D36_B610_14F98D1A2BE7__INCLUDED_)
