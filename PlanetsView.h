// PlanetsView.h : interface of the CPlanetsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLANETSVIEW_H__05806A94_230A_47CC_A62B_2CACF163F584__INCLUDED_)
#define AFX_PLANETSVIEW_H__05806A94_230A_47CC_A62B_2CACF163F584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ArrayEx.h"
#include "PlanetsDoc.h"
#include "DataDisplay.h"
#include "DisplayControl.h"
#include "PPTooltip.h"
#include "Planet.h"

struct toolTipData
{
	UINT	type;
	CRect	rect;
	CString name;
	CString constellation;
	CString azimuth;
	CString altitude;
	CString magnitude;
};

class CPlanetsView : public CScrollView
{
protected: // create from serialization only
	CPlanetsView();
	DECLARE_DYNCREATE(CPlanetsView)
//	colors for various parts of drawing

//Constellation lines
	int m_iConR;
	int m_iConG;
	int m_iConB;

//Planet colors
	int m_iPlanetR;
	int m_iPlanetG;
	int m_iPlanetB;

//Horizon circle
	int m_iHorCirR;
	int m_iHorCirG;
	int m_iHorCirB;

//Cardinal letters
	int m_iCardR;
	int m_iCardG;
	int m_iCardB;

//Star colors
	int m_iStarR;
	int m_iStarG;
	int m_iStarB;

//	Used for grabbing and moving objects
	POSITION m_StrokePos;
	class CText* m_moveText;//The text to move
	class CStroke* m_moveStroke;
	int m_xDist;//x distance from mouse to text location
	int m_yDist;//y distance from mouse to text location
	CPoint m_pStartRotate;//Mouse start point for circle rotation
	bool m_bFoundText;
	bool m_bFoundStroke;
	bool m_bFoundCircle;
	bool m_bDisplayControl;

//	Horizon circle center and radius
	CPoint m_iHorCir;
	int m_iHorCirRadius;

	UINT m_uViewType;

// Attributes
public:
	class CPlanetsDoc*		GetDocument();
	class CPlanetsDoc*		m_pPlanetDoc;
	class CStar*			m_pCStar;
	class CStarData*		m_pStarData;
	CArray<int, int>		m_iConstList;
	int						m_iNumPlanets;
	class CToolTipCtrl			m_objTip ;
	class CPPToolTip		m_tooltip;

	class CArrayEx<struct toolTipData, struct toolTipData & > m_toolTipList;// collection of toolTipData structs
	class CDisplayControl*	m_cDisplayControl;
// Operations
public:
	void ShowWorking(UINT style);
	void RefreshScreen();
	void StarsSetUp(class CTimeLocation* tL);
	void ImportData(CArray<int, int> *iConstList, int iNumPlanets);
	void DrawAzAltPlanets(int iNumPlanets, int iWhichPlanets[],
						  double pAzimuth[], double pAltitude[],
						  CPoint dOrigin, int circleRadius);
	void DrawChart(class CHor* pCHor, class CTimeLocation* pTimeLocation);
	void DrawStars(CArray<int, int> *iConstList, int iNumPlanets);
	void DrawStars();

	void MakeCircle(int x, int y, int radius, int R, int G, int B);
	void MakeEllipse(int x1, int y1, int x2, int y2, UINT fill, int R, int G, int B);
	void MakeLine(CPoint pointOne, CPoint pointTwo, int R, int G, int B);
	void MakePointer(CPoint pointOne, CPoint pointTwo, int R, int G, int B);
	void DrawLines(CPoint dOrigin, double radius, double lambda, double textLocation, CString name);
	void DrawLine(CPoint dOrigin, double radius, double lambda);
	void DrawBody(CPoint dOrigin, double radius, double lambda,
							CString name);

	void MakeFont(double angle, CFont* font, struct fontAttributes* nFont);
	void GetTextLocation(CPoint origin, CPoint body, CPoint* text, double location);
	void GetChartTextLocation(CPoint origin, CPoint body, CPoint* text, double location);
	void SetTextAngle(double lambda, double& textAngle);
	void HouseLines(class CHor* pCHor, CPoint dOrigin, int innerRadius, int outerRadius);
	void DrawAspectTable();
	void LabelAspectTable(class CHor* pCHor);
	void PopulateAspectTable(class CHor* pCHor);
	void PlaceBodiesOnChart(class CHor* pCHor, CPoint dOrigin,
									  int innerCircle, int outerCircle);
	void FindOriginPoints(CPoint dOrigin, double innerRadius,
						  double body[11], CPoint pPoints[11]);
	void FindTextOriginPoint(CPoint dOrigin, double innerRadius,
							   double lambda, CPoint* pPoint,
										 double *x, double *y);
	void PrintName(CPoint textLoc, double textAngle, CString text,
					int R, int G, int B);
	void MakeAspect(int type, CPoint pPoint);
	void PrintChartNames(class CHor* pCHor);
	void StarPrintSize(double dMagnitude, CPoint dStar,
					   int *x1, int *y1, int *x2, int *y2);
	void StarCardinals(CPoint dOrigin, int circleDiameter);
	void PrintStarData();
	void MakeStarsByMag(double magArray[], double azimuth[], double altitude[],
						CString names[], int iArraySize, double testMag,
						int circleRadius, CPoint dOrigin, bool doNames);
	void MakeStarsByAll(double magArray[], double azimuth[], double altitude[],
						CString names[], int iArraySize, int circleRadius,
						CPoint dOrigin, CPoint conPoints[], double realConPointXs[],
						double realConPointYs[], bool doNames);
	void MakeStarsByList(double magArray[], double azimuth[], double altitude[],
						CString names[], int iArraySize, int circleRadius,
						CPoint dOrigin, CPoint conPoints[], double realConPointXs[],
						double realConPointYs[], CArray<int, int> *iConst,
						bool doNames);
	void MakeStarsByMagCon(double magArray[], double azimuth[], double altitude[],
						CString names[], int iArraySize, double testMag,
						int circleRadius, CPoint dOrigin, CPoint conPoints[],
						double realConPointXs[], double realConPointYs[],
						bool doNames);
	void MakeStarsByMagList(double magArray[], double azimuth[], double altitude[],
						CString names[], int iArraySize, double testMag,
						int circleRadius, CPoint dOrigin, CPoint conPoints[],
						double realConPointXs[], double realConPointYs[],
						CArray<int, int> *iConst, bool doNames);
	void TransformToScrollPos(int sPosX, int sPosY, int *pPosX, int *pPosY);
	void TransformToScrollPos(int sPosX, int sPosY, long *pPosX, long *pPosY);
	void AddStarToolTip(CRect rect, int i, int arraySize);
	void AddStarToolTip(CRect rect, double az, double alt, CString name,
						 CString sConst, double mag);
	bool PointInRect(CRect rec, CPoint pt);
	void AddPlanetToolTip(CRect rect, double az, double alt, CString name);
	CString MakeTipText(struct toolTipData data);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlanetsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnFilePrintView();
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPlanetsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	class CStroke* m_pStrokeCur;
	class CStroke* m_pArcCur;
	class CStroke* m_pEllipseCur;
	class CText* m_pTextCur;
	CPoint m_ptPrev;

// Generated message map functions
protected:
	//{{AFX_MSG(CPlanetsView)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnHelpFinder();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFontSize();
	//}}AFX_MSG
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnClose();
//	afx_msg void OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
//	afx_msg void OnFileClose();
//	afx_msg void OnIdclose();
};

#ifndef _DEBUG  // debug version in PlanetsView.cpp
inline CPlanetsDoc* CPlanetsView::GetDocument()
   { return (CPlanetsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLANETSVIEW_H__05806A94_230A_47CC_A62B_2CACF163F584__INCLUDED_)
