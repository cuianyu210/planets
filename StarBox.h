#if !defined(AFX_STARBOX_H__3F710DF4_D83C_4DF3_A1EA_F7E6615EEFE9__INCLUDED_)
#define AFX_STARBOX_H__3F710DF4_D83C_4DF3_A1EA_F7E6615EEFE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StarBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStarBox dialog

class CStarBox : public CDialog
{
// Construction
public:
	CStarBox(CWnd* pParent = NULL);   // standard constructor

	int m_iBoxValue;
	int m_iStarNames;
	int m_iConNames;
	int m_iStarToFile;
	CString m_sStarFileName;

// Dialog Data
	//{{AFX_DATA(CStarBox)
	enum { IDD = IDD_STAR_BOX };
	CString	m_sMagnitude;
	CString	m_sViewDirection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStarBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStarBox)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnStarToFile();
	afx_msg void OnVmag();
	afx_msg void OnConstellation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARBOX_H__3F710DF4_D83C_4DF3_A1EA_F7E6615EEFE9__INCLUDED_)
