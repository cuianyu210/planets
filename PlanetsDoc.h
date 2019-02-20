// PlanetsDoc.h : interface of the CPlanetsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLANETSDOC_H__AAD9EEF7_37EE_43D7_800B_3EAB362EE78D__INCLUDED_)
#define AFX_PLANETSDOC_H__AAD9EEF7_37EE_43D7_800B_3EAB362EE78D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "PlanetsView.h"
#include "TimeLocation.h"
#include "EquinoxSolstice.h"
#include "Almanac.h"

struct fontAttributes
{
	int nHeight;
	int nWidth;
	int nEscapement;
	int nOrientation;
	int nWeight;
	BYTE bItalic;
	BYTE bUnderline;
	BYTE cStrikeOut;
	BYTE nCharSet;
	BYTE nOutPrecision;
	BYTE nClipPrecision;
	BYTE nQuality;
	BYTE nPitchAndFamily;
	LPCTSTR lpszFacename;
};

class CStroke : public CObject
{
public:
	CStroke(UINT nPenWidth, UINT nFill);
	virtual void Serialize(CArchive& ar);

protected:
	CStroke();
	DECLARE_SERIAL (CStroke)

// Attribute
protected:
	UINT m_nPenWidth;
	UINT m_nFill;
public:
	CArray<CPoint, CPoint> m_pointArray;
	CArray<int, int> m_arcArray;
	CArray<int, int> m_ellipseArray;
	int m_iPenR;
	int m_iPenG;
	int m_iPenB;

//Operations
public:
	BOOL DrawStroke(CDC* pDC);
	BOOL DrawArc(CDC* pDC);
	BOOL DrawEllipse(CDC* pDC);

public:
};
//////////////////////////////////////////////////////////
class CText : public CObject
{
public:
	CText();
	virtual void Serialize(CArchive& ar);

protected:
//	CText();
	DECLARE_SERIAL (CText)

// Attribute
protected:
//	UINT m_nPenWidth;
public:
	CPoint m_pTextOrig;
	CPoint m_pTextLocation;
	int m_width;
	int m_height;
	int m_iPenR;
	int m_iPenG;
	int m_iPenB;
	CString m_text;
	struct fontAttributes m_font;
	bool m_bHasPointer;

//Operations
public:
	BOOL WriteText(CDC* pDC);
	double Distance(CPoint p1, CPoint p2);

public:
};
//////////////////////////////////////////////////////////

class CPlanetsDoc : public CDocument
{
protected: // create from serialization only
//	CPlanetsDoc();
	DECLARE_DYNCREATE(CPlanetsDoc)

// Attributes
public:
	CPlanetsDoc();
	CTypedPtrList<CObList, CStroke*> m_strokeList;
	CTypedPtrList<CObList, CStroke*> m_arcList;
	CTypedPtrList<CObList, CStroke*> m_ellipseList;
	CTypedPtrList<CObList, CText*> m_textList;
	CPen* GetCurrentPen() {return &m_penCur;}
	class CTimeLocation* m_pModeless;
	class CEquinoxSolstice* m_pESModeless;
	class CAlmanac* m_pAlModeless;
//	class COptions* m_pOpModal;
	class COptions* m_pOpModeless;
	CRect m_cWinMainRect;
	int m_iWinMainWidth;
	int m_iWinMainHeight;
	CComboBox m_cFontCombo;

private:
protected:
	UINT m_nPenWidth;
	CPen m_penCur;
	UINT m_nFill;
	LOGBRUSH m_logBrushCur;
	CBrush m_pBrushCur;

	void InitDocument();
	void ReplacePen();
	void ReplaceFill();

// Operations
public:

	afx_msg void OnToolsPlanets();
	virtual void DeleteContents();
	void EraseContents();
	CStroke* NewStroke();
	CStroke* NewArc();
	CStroke* NewEllipse(UINT nFill);
	CText* NewText();
	void SetCheckBoxes();
	void SetAlmanacCheckBoxes();
	void LoadConstListBox(CListBox* pListBox);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlanetsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
//	virtual void OnClose();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPlanetsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPlanetsDoc)
	afx_msg void OnTimeLocation();
	afx_msg void OnEquinoxsolstice();
	afx_msg void OnAlmanac();
	afx_msg void OnOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnFileClose();
//	afx_msg void OnIdclose();
//	afx_msg void OnIdcancel();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLANETSDOC_H__AAD9EEF7_37EE_43D7_800B_3EAB362EE78D__INCLUDED_)
