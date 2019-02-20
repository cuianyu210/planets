#if !defined(AFX_VALIDATE_H__2AF731A8_4598_489F_9DE2_45B05068F635__INCLUDED_)
#define AFX_VALIDATE_H__2AF731A8_4598_489F_9DE2_45B05068F635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Validate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CValidate window
enum
{
	NO_DELIMITER,
	COLON,
	COLON_ONLY = 1,
	RADIX,
	RADIX_ONLY = 2,
	COLON_AND_RADIX
};

class CValidate : public CWnd
{
// Construction
public:
	CValidate();
	bool validateChar(UINT uEditStyle, int iChar);
	bool validateField(UINT uEditStyle, CString t);
	bool validateMagnitude(double val);
	bool validateViewDir(int val);
	bool validateYear(int val);
	bool validateMonth(int val);
	bool validateDate(int val);
	bool validateHour(int val);
	bool validateLatLon(CString val, UINT tudeType);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValidate)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CValidate();

	// Generated message map functions
protected:
	//{{AFX_MSG(CValidate)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VALIDATE_H__2AF731A8_4598_489F_9DE2_45B05068F635__INCLUDED_)
