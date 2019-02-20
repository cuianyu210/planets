#if !defined(AFX_MOONDIALOG_H__33A734F5_2835_4499_970C_CEF05C75B0D4__INCLUDED_)
#define AFX_MOONDIALOG_H__33A734F5_2835_4499_970C_CEF05C75B0D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoonDialog.h : header file
//
#include "MoonPhase.h"
/////////////////////////////////////////////////////////////////////////////
// CMoonDialog dialog

class CMoonDialog : public CDialog
{
// Construction
public:
	CMoonDialog(CWnd* pParent = NULL);   // standard constructor
	CMoonDialog(CTimeLocation* pTimeL);
	void UpdateDataMD();
	CString MakeTimeString(double julDay);
	CString FindTime(ULONG uPhase, ULONG *PHASE);
	void StartUp();
	void OnNextQuarterBtn();
	void OnNextNewBtn();
	void OnNextFullBtn();
	void OnPreviousQtrBtn();
	
	class CMoonPhase* pMoon;
	CTimeLocation *m_pTL;
	double m_dYear;
	double m_dMonth;
	double m_dDay;
	double m_dTZone;
	CString m_sAmpm;
	CString m_sDST;
	double m_dDecimal_Year;
	double m_dJulDay;
	CString m_sLocalDST;
	double m_dLocalTimeZone;

// Dialog Data
	//{{AFX_DATA(CMoonDialog)
	enum { IDD = IDD_MOON_PHASES };
	int		m_iMoonDay;
	CString	m_sMoonDST;
	int		m_iMoonYear;
	int		m_iMoonMonth;
	CString	m_sNextFull;
	CString	m_sNextNew;
	CString	m_sNextQuarter;
	CString	m_sPreviousQuarter;
	CString	m_sNextQtr;
	CString	m_sPrevQtr;
	double	m_dTimeZone;
	CString	m_sTimeType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoonDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMoonDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnMoonPhaseAll();
	afx_msg void OnMoonPhaseClear();
	afx_msg void OnUtBtn();
	afx_msg void OnMoonDoYear();
	virtual void OnCancel();
	afx_msg void OnKillfocusMoonHour();
	afx_msg void OnKillfocusMoonDst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOONDIALOG_H__33A734F5_2835_4499_970C_CEF05C75B0D4__INCLUDED_)
