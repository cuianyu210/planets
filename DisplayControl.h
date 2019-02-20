#if !defined(AFX_DISPLAYCONTROL_H__849B9A55_6446_46C2_9C05_26A6EA391340__INCLUDED_)
#define AFX_DISPLAYCONTROL_H__849B9A55_6446_46C2_9C05_26A6EA391340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisplayControl.h : header file
//
#include "PlanetsView.h"


/////////////////////////////////////////////////////////////////////////////
// DisplayControl dialog

class CDisplayControl : public CDialog
{
// Construction
public:
	CDisplayControl(class CPlanetsView* m_pPlanetsView);   // standard constructor
	void UpdateViewDirection(double NewValue);
	void OnSliderMove(CScrollBar* pScrollBar);
	void SetStarButtons();
	void SetConButtons();
	void SetStarNamesMember();
	void SetConNamesMember();
	void SetWhichStars();

//	DisplayControl(CWnd* pParent = NULL);   // standard constructor
	class CPlanetsView* m_pPlanetsView;
	int	m_iShowConNames;
	int	m_iShowCons;
	int	m_iShowStarNames;
	int	m_iShowStars;
	UINT m_iWhichStars;//	1 = mag only, 2 = const only, 3 = both
	double m_dMagnitude;
	int m_iViewDirection;
	double m_dViewDirection;

// Dialog Data
	//{{AFX_DATA(DisplayControl)
	enum { IDD = IDD_DISPLAY_CONTROL };
	CString	m_sMagnitude;
	CString	m_sViewDirection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DisplayControl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(DisplayControl)
	afx_msg void OnShowStars();
	afx_msg void OnChangeMagValue();
	afx_msg void OnShowCons();
	afx_msg void OnShowConNames();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnShowStarNames();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYCONTROL_H__849B9A55_6446_46C2_9C05_26A6EA391340__INCLUDED_)
