#if !defined(AFX_VARIATIONBOX_H__D6ABEC13_10A6_4EF7_A255_8B8271B5CB9C__INCLUDED_)
#define AFX_VARIATIONBOX_H__D6ABEC13_10A6_4EF7_A255_8B8271B5CB9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VariationBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVariationBox dialog

class CVariationBox : public CDialog
{
// Construction
public:
//	CVariationBox(CWnd* pParent = NULL);   // standard constructor
	CVariationBox(class CTimeLocation* dick);
	class CTimeLocation* m_pCTimeLocation;

// Dialog Data
	//{{AFX_DATA(CVariationBox)
	enum { IDD = IDD_VARIATION_BOX };
	CString	m_sDip;
	CString	m_sLatitude;
	CString	m_sLocation;
	CString	m_sLongitude;
	CString	m_sTime;
	CString	m_sVariation;
	CString	m_sDegreeStyle;
	CString	m_sMagneticHorizontal;
	CString	m_sMagneticNorth;
	CString	m_sMagneticEast;
	CString	m_sMagneticVertical;
	CString	m_sMagneticTotal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVariationBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVariationBox)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VARIATIONBOX_H__D6ABEC13_10A6_4EF7_A255_8B8271B5CB9C__INCLUDED_)
