#if !defined(AFX_ERROR_H__F4938BCA_BF14_48E8_8741_84F9B18CB7A4__INCLUDED_)
#define AFX_ERROR_H__F4938BCA_BF14_48E8_8741_84F9B18CB7A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Error.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CError dialog

class CError : public CDialog
{
// Construction
public:
	CError(CWnd* pParent = NULL);   // standard constructor
	int ShowError(CString mes);

// Dialog Data
	//{{AFX_DATA(CError)
	enum { IDD = IDD_ERROR };
	CString	m_sMessage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CError)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CError)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERROR_H__F4938BCA_BF14_48E8_8741_84F9B18CB7A4__INCLUDED_)
