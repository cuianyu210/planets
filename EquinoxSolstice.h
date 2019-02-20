#if !defined(AFX_EQUINOXSOLSTICE_H__08A3E39C_3122_46FA_A50D_190E95CC23E5__INCLUDED_)
#define AFX_EQUINOXSOLSTICE_H__08A3E39C_3122_46FA_A50D_190E95CC23E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EquinoxSolstice.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEquinoxSolstice dialog

class CEquinoxSolstice : public CDialog
{
// Construction
public:
	void OnYear();
	CEquinoxSolstice(CWnd* pParent = NULL);   // standard constructor
	CEquinoxSolstice(class CPlanetsDoc* bob);
// Dialog Data
	//{{AFX_DATA(CEquinoxSolstice)
	enum { IDD = IDD_EQUINOXSOLSTICE };
	int		m_iESYear;
	CString	m_sAutEqui;
	CString	m_sSumSol;
	CString	m_sVerEqui;
	CString	m_sWinSol;
	double	m_dAEDuration;
	double	m_dSSDuration;
	double	m_dVEDuration;
	double	m_dWSDuration;
	int		m_iPrecision;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEquinoxSolstice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEquinoxSolstice)
	virtual void OnOK();
	afx_msg void OnRun();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EQUINOXSOLSTICE_H__08A3E39C_3122_46FA_A50D_190E95CC23E5__INCLUDED_)
