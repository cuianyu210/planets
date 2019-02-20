#if !defined(AFX_OPTIONS_H__AF389D33_D60E_4904_8C69_2DA9C1240DA7__INCLUDED_)
#define AFX_OPTIONS_H__AF389D33_D60E_4904_8C69_2DA9C1240DA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Options.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptions dialog

class COptions : public CDialog
{
// Construction
public:
	COptions(CWnd* pParent = NULL);   // standard constructor
	COptions(class CPlanetsDoc* bob);

// Dialog Data
	//{{AFX_DATA(COptions)
	enum { IDD = IDD_OPTIONS };
	int		m_iPrecision;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptions)
	afx_msg void OnOK();
	afx_msg void OnDo();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONS_H__AF389D33_D60E_4904_8C69_2DA9C1240DA7__INCLUDED_)
