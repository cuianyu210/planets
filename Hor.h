#if !defined(AFX_HOR_H__C4D567BC_EB39_4532_AB81_A68421C49A41__INCLUDED_)
#define AFX_HOR_H__C4D567BC_EB39_4532_AB81_A68421C49A41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hor.h : header file
//
#include "MainFrm.h"
#include "ChildFrm.h"
#include "PlanetsView.h"
#include "Chart.h"

/////////////////////////////////////////////////////////////////////////////
// CHor dialog

class CHor : public CDialog
{
// Construction
public:
//	CHor(CWnd* pParent = NULL);   // standard constructor
	CHor(class CTimeLocation* dick);
	class CTimeLocation* m_pCTimeLocation;
	class CChart m_pChart;

// Dialog Data
	//{{AFX_DATA(CHor)
	enum { IDD = IDD_HOR };
	int		m_iAscNodeHouse;
	int		m_iJupiterHouse;
	int		m_iMarsHouse;
	int		m_iMercuryHouse;
	int		m_iMoonHouse;
	int		m_iNeptuneHouse;
	int		m_iPlutoHouse;
	int		m_iSaturnHouse;
	int		m_iSunHouse;
	int		m_iUranusHouse;
	int		m_iVenusHouse;
	CString	m_sVenusSign;
	CString	m_sUranusSign;
	CString	m_sSunSign;
	CString	m_sSaturnSign;
	CString	m_sPlutoSign;
	CString	m_sNeptuneSign;
	CString	m_sMoonSign;
	CString	m_sMercurySign;
	CString	m_sMarsSign;
	CString	m_sJupiterSign;
	CString	m_sAscNodeSign;
	CString	m_sAscNodePos;
	CString	m_sBirthPlace;
	CString	m_sBirthTime;
	CString	m_sJupRet;
	CString	m_sJupiterPos;
	CString	m_sMarRet;
	CString	m_sMarsPos;
	CString	m_sMercRet;
	CString	m_sMercuryPos;
	CString	m_sMoonPos;
	CString	m_sName;
	CString	m_sNepRet;
	CString	m_sNeptunePos;
	CString	m_sPlutRet;
	CString	m_sPlutoPos;
	CString	m_sSatRet;
	CString	m_sSaturnPos;
	CString	m_sSunPos;
	CString	m_sUranRet;
	CString	m_sUranusPos;
	CString	m_sVenRet;
	CString	m_sVenusPos;
	//}}AFX_DATA

	double	m_dAscNodePos;
	double	m_dJupiterPos;
	double	m_dMarsPos;
	double	m_dMercuryPos;
	double	m_dMoonPos;
	double	m_dNeptunePos;
	double	m_dPlutoPos;
	double	m_dSaturnPos;
	double	m_dSunPos;
	double	m_dUranusPos;
	double	m_dVenusPos;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHor)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOR_H__C4D567BC_EB39_4532_AB81_A68421C49A41__INCLUDED_)
