// PlanetsView.cpp : implementation of the CPlanetsView class
//

#include "stdafx.h"
#include "PlanetsView.h"
#include "Constellations.h"
#include "Star.h"
#include "StarData.h"
#include "convert.h"

#include <stdlib.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define STAR 0
#define PLANET 1
#define NO_VIEW 0
#define STAR_VIEW 2
#define HOROSCOPE_VIEW 3
/////////////////////////////////////////////////////////////////////////////
// CPlanetsView

IMPLEMENT_DYNCREATE(CPlanetsView, CScrollView)

BEGIN_MESSAGE_MAP(CPlanetsView, CScrollView)
	//{{AFX_MSG_MAP(CPlanetsView)
	ON_WM_HELPINFO()
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_CBN_SELCHANGE(IDS_FONT_SIZE, OnFontSize)
	//}}AFX_MSG_MAP
	// Standard printing commands
//	ON_COMMAND(ID_FILE_CLOSE,OnClose)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrintView)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
//	ON_WM_CLOSE()
//	ON_WM_DELETEITEM()
//	ON_COMMAND(ID_FILE_CLOSE, &CPlanetsView::OnFileClose)
//	ON_COMMAND(IDCLOSE, &CPlanetsView::OnIdclose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlanetsView construction/destruction

CPlanetsView::CPlanetsView()
{
	m_pCStar = NULL;
	m_pStarData = NULL;
	// there is not yet any display control
	m_bDisplayControl = false;
//	colors for various parts of drawing

//Constellation lines
	m_iConR = 0;
	m_iConG = 0;
	m_iConB = 0;

//Planet colors
	m_iPlanetR = 255;
	m_iPlanetG = 0;
	m_iPlanetB = 0;

//Horizon circle
	m_iHorCirR = 0;
	m_iHorCirG = 0;
	m_iHorCirB = 0;

//Cardinal letters
	m_iCardR = 0;
	m_iCardG = 0;
	m_iCardB = 0;

//Star colors
	m_iStarR = 0;
	m_iStarG = 0;
	m_iStarB = 0;
	
//	m_dViewDir = 0;//Initial view direction
	m_iHorCir.x = 650; // screen
	m_iHorCir.y = -530; // screen
	m_iHorCirRadius = 470; // screen
//	m_iHorCir.x = 425; // print
//	m_iHorCir.y = -550; // print
//	m_iHorCirRadius = 375; // print

	m_iConstList.SetSize(0, 10);

	EnableToolTips(TRUE);

	m_uViewType = NO_VIEW;
}

CPlanetsView::~CPlanetsView()
{
	delete m_pStarData;
	delete m_pCStar;
	if(m_bDisplayControl)
		delete m_cDisplayControl;
}

BOOL CPlanetsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

void CPlanetsView::StarsSetUp(CTimeLocation* tL)
{
	m_pCStar = new  CStar(tL);
	m_pStarData = new CStarData;

}

void CPlanetsView::OnFilePrintView()
{
	CScrollView::OnFilePrint();
}

/////////////////////////////////////////////////////////////////////////////
// CPlanetsView drawing
void CPlanetsView::ShowWorking(UINT style)
{
	CStatic* working;

	working = (CStatic*)(m_cDisplayControl->GetDlgItem(IDC_WORKING));

	working->ShowWindow(style);
	working->UpdateWindow();
}

void CPlanetsView::RefreshScreen()
{
	class CPlanetsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->EraseContents();

	CPlanetsView::DrawStars();
	InvalidateRect(NULL, true);
	OnPaint();
}

void CPlanetsView::OnDraw(CDC* pDC)
{
	class CPlanetsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CTypedPtrList<CObList, CStroke*>& strokeList = pDoc->m_strokeList;
	POSITION pos = strokeList.GetHeadPosition();
	while (pos != NULL)
	{
		CStroke* pStroke = strokeList.GetNext(pos);
		pStroke->DrawStroke(pDC);
	}

	CTypedPtrList<CObList, CStroke*>& arcList = pDoc->m_arcList;
	pos = arcList.GetHeadPosition();
	while (pos != NULL)
	{
		CStroke* pArc = arcList.GetNext(pos);
		pArc->DrawArc(pDC);
	}

	CTypedPtrList<CObList, CStroke*>& ellipseList = pDoc->m_ellipseList;
	pos = ellipseList.GetHeadPosition();
	while (pos != NULL)
	{
		CStroke* pEllipse = ellipseList.GetNext(pos);
		pEllipse->DrawEllipse(pDC);
	}

	CTypedPtrList<CObList, CText*>& textList = pDoc->m_textList;
	pos = textList.GetHeadPosition();
	while (pos != NULL)
	{
		CText* pText = textList.GetNext(pos);
		pText->WriteText(pDC);
	}
}

void CPlanetsView::DrawAzAltPlanets(int iNumPlanets, 
									int iWhichPlanets[],
									double pAzimuth[],
									double pAltitude[],
									CPoint dOrigin,
									int circleRadius)
{
	convert Convert;

	int i, x1, x2, y1, y2;
	double dPiOver2;
	CPoint dPlanet;
	CPoint dNameLocation;
	double planetRadius, planetAngle;
	double x, y;

	dPiOver2 = Convert.Pi() / 2.0;

	for(i=0; i<11; i++)
	{
		if(1 == iWhichPlanets[i])
		{
			if(pAltitude[i] > 0.0)
			{
			//	Locate star center from position
			//	radius comes from co-altitude
			//	angle from azimuth, but need to run in opposite direction from program
				planetRadius = ((dPiOver2 - pAltitude[i]) / dPiOver2) * circleRadius;
				planetAngle = dPiOver2 - pAzimuth[i] + m_cDisplayControl->m_dViewDirection;
				CPlanetsView::FindTextOriginPoint(dOrigin, planetRadius, planetAngle, &dPlanet, &x, &y);

			//	Find printed star size and location
				x1 = dPlanet.x - 5;
				x2 = dPlanet.x + 5;
				y1 = dPlanet.y + 5;
				y2 = dPlanet.y - 5;

				dNameLocation.x = x1;
				dNameLocation.y = y1;

				CClientDC dc(this);
				CString name = Convert.BodyNameShort(i);
				CSize textSize = dc.GetTextExtent(name);
				CRect tipRec;
				tipRec.left		= x1;
				tipRec.right	= x1 + textSize.cx;
				tipRec.top		= y1;
				tipRec.bottom	= y1 - textSize.cy;

				CPlanetsView::AddPlanetToolTip(tipRec, pAzimuth[i], pAltitude[i],
											   Convert.BodyName(i));
			//	Make planet
				CPlanetsView::PrintName(dNameLocation, 0, name, m_iPlanetR, m_iPlanetG, m_iPlanetB);
			}//end of "if(pAltitude[i] > 0.0)"
		}//end of "if(1 == iWhichPlanets[i])"
	}//end of "for(i=0; i<11; i++)"
}

void CPlanetsView::ImportData(CArray<int, int> *iConstList, int iNumPlanets)
{
	int size = iConstList->GetSize();

	if(size)
	{
		for(int i=0; i<size; i++)
		{
			int bb = iConstList->GetAt(i);
			m_iConstList.Add(bb);
		}
	}

	m_iNumPlanets = iNumPlanets;
}

void CPlanetsView::DrawStars(CArray<int, int> *iConstList, int iNumPlanets)
{
	CConstellations conny;

	bool bPrintStarNames;
	CPoint dStar;
	CPoint constellationPoints[IDS_NUM_CON_STARS];
	double realConPointXs[IDS_NUM_CON_STARS];//Collects all of the real points (as opposed
	double realConPointYs[IDS_NUM_CON_STARS];//to int's) for the locations of all con stars
//	for the sole purpose of passing them all eventually to CConstellations::FindIntersection
//	to fix bug wherin a line is drawn to the center of the circle from a constellation at
//	the edge.  This was caused by truncating real data to make the points for the stars.
//	This caused a sqrt of a negative number instead of just a small positive number.


	m_uViewType = STAR_VIEW;
	//	This should no longer be  needed as m_pCStar and m_pStarData are now members of 
	//	CPlanetsView LS 100204
	ImportData(iConstList, iNumPlanets);

	// This must come earlier as it contains data that is used below LS 100204
	m_cDisplayControl = new CDisplayControl(this);
	m_cDisplayControl->Create(IDD_DISPLAY_CONTROL, NULL);
	m_cDisplayControl->ShowWindow(SW_SHOW);
	m_bDisplayControl = true;

	bPrintStarNames = false;
	if(m_pCStar->m_iStarNames == 1)
	{
		bPrintStarNames = true;
	}

	CPlanetsView::MakeCircle(m_iHorCir.x, m_iHorCir.y, m_iHorCirRadius, m_iHorCirR, m_iHorCirG, m_iHorCirB);
	CPlanetsView::StarCardinals(m_iHorCir, m_iHorCirRadius);

	switch(m_pCStar->m_iWhichStars)
	{
	case IDS_MAGNITUDE_ONLY:
		CPlanetsView::MakeStarsByMag(m_pStarData->m_dNonConstellationMagnitude,
									 m_pStarData->m_dNonConstellationAzimuth,
									 m_pStarData->m_dNonConstellationAltitude,
									 m_pStarData->m_sNonConstellationShortName,
									 m_pStarData->m_iNonConArraySize,
									 m_pCStar->m_dMagnitude,
									 m_iHorCirRadius,
									 m_iHorCir,
									 bPrintStarNames);
		CPlanetsView::MakeStarsByMag(m_pStarData->m_dConstellationMagnitude,
									 m_pStarData->m_dConstellationAzimuth,
									 m_pStarData->m_dConstellationAltitude,
									 m_pStarData->m_sConstellationShortName,
									 m_pStarData->m_iConArraySize,
									 m_pCStar->m_dMagnitude,
									 m_iHorCirRadius,
									 m_iHorCir,
									 bPrintStarNames);
		break;
	case IDS_CONSTELLATION_ONLY:
		if(iConstList->GetAt(0) == 0)
		{
			CPlanetsView::MakeStarsByAll(m_pStarData->m_dConstellationMagnitude,
										 m_pStarData->m_dConstellationAzimuth,
										 m_pStarData->m_dConstellationAltitude,
										 m_pStarData->m_sConstellationShortName,
										 m_pStarData->m_iConArraySize,
										 m_iHorCirRadius,
										 m_iHorCir,
										 constellationPoints,
										 realConPointXs,
										 realConPointYs,
										 bPrintStarNames);
			conny.MakeAll(this,
						  m_pStarData->m_dConstellationAltitude,
						  constellationPoints,
						  realConPointXs,
						  realConPointYs,
						  m_iHorCirRadius,
						  m_iHorCir,
						  m_pCStar->m_iConNames,
						  m_iConR,
						  m_iConG,
						  m_iConB);
		}
		else
		{
			CPlanetsView::MakeStarsByList(m_pStarData->m_dConstellationMagnitude,
										  m_pStarData->m_dConstellationAzimuth,
										  m_pStarData->m_dConstellationAltitude,
										  m_pStarData->m_sConstellationShortName,
										  m_pStarData->m_iConArraySize,
										  m_iHorCirRadius,
										  m_iHorCir,
										  constellationPoints,
										  realConPointXs,
										  realConPointYs,
										  iConstList,
										  bPrintStarNames);
			conny.MakeList(this,
						   m_pStarData->m_dConstellationAltitude,
						   constellationPoints,
						   realConPointXs,
						   realConPointYs,
						   m_iHorCirRadius,
						   m_iHorCir,
						   iConstList,
						   m_pCStar->m_iConNames,
						   m_iConR,
						   m_iConG,
						   m_iConB);
		}

		break;
	case IDS_MAGNITUDE_AND_CONSTELLATION:
		CPlanetsView::MakeStarsByMag(m_pStarData->m_dNonConstellationMagnitude,
									 m_pStarData->m_dNonConstellationAzimuth,
									 m_pStarData->m_dNonConstellationAltitude,
									 m_pStarData->m_sNonConstellationShortName,
									 m_pStarData->m_iNonConArraySize,
									 m_pCStar->m_dMagnitude,
									 m_iHorCirRadius,
									 m_iHorCir,
									 bPrintStarNames);
		if(iConstList->GetAt(0) == 0)
		{
	CPlanetsView::MakeStarsByMagCon(m_pStarData->m_dConstellationMagnitude,
									m_pStarData->m_dConstellationAzimuth,
									m_pStarData->m_dConstellationAltitude,
									m_pStarData->m_sConstellationShortName,
									m_pStarData->m_iConArraySize,
									m_pCStar->m_dMagnitude,
									m_iHorCirRadius,
									m_iHorCir,
									constellationPoints,
									realConPointXs,
									realConPointYs,
									bPrintStarNames);
		conny.MakeAll(this,
					  m_pStarData->m_dConstellationAltitude,
					  constellationPoints,
					  realConPointXs,
					  realConPointYs,
					  m_iHorCirRadius,
					  m_iHorCir,
					  m_pCStar->m_iConNames,
					  m_iConR,
					  m_iConG,
					  m_iConB);
		}
		else
		{
			CPlanetsView::MakeStarsByMagList(m_pStarData->m_dConstellationMagnitude,
											 m_pStarData->m_dConstellationAzimuth,
											 m_pStarData->m_dConstellationAltitude,
											 m_pStarData->m_sConstellationShortName,
											 m_pStarData->m_iConArraySize,
											 m_pCStar->m_dMagnitude,
											 m_iHorCirRadius,
											 m_iHorCir,
											 constellationPoints,
											 realConPointXs,
											 realConPointYs,
											 iConstList,
											 bPrintStarNames);
			conny.MakeList(this,
						   m_pStarData->m_dConstellationAltitude,
						   constellationPoints,
						   realConPointXs,
						   realConPointYs,
						   m_iHorCirRadius,
						   m_iHorCir,
						   iConstList,
						   m_pCStar->m_iConNames,
						   m_iConR,
						   m_iConG,
						   m_iConB);
		}
		break;
	}

	if(iNumPlanets > 0)
	{
		CPlanetsView::DrawAzAltPlanets(iNumPlanets,
									   m_pCStar->m_pPlanetSet,
									   m_pCStar->m_dPlanetAzimuth,
									   m_pCStar->m_dPlanetAltitude,
									   m_iHorCir,
									   m_iHorCirRadius);
	}
	CPlanetsView::PrintStarData();
}

void CPlanetsView::DrawStars()
{
	CConstellations conny;

	bool bPrintStarNames;
	CPoint dStar;
	CPoint constellationPoints[IDS_NUM_CON_STARS];
	double realConPointXs[IDS_NUM_CON_STARS];
	double realConPointYs[IDS_NUM_CON_STARS];

	bPrintStarNames = false;
	if(m_cDisplayControl->m_iShowStarNames == 1)
	{
		bPrintStarNames = true;
	}

	CPlanetsView::MakeCircle(m_iHorCir.x, m_iHorCir.y, m_iHorCirRadius, m_iHorCirR, m_iHorCirG, m_iHorCirB);
	CPlanetsView::StarCardinals(m_iHorCir, m_iHorCirRadius);

	switch(m_cDisplayControl->m_iWhichStars)
	{
	case IDS_MAGNITUDE_ONLY:
		CPlanetsView::MakeStarsByMag(m_pStarData->m_dNonConstellationMagnitude,
									 m_pStarData->m_dNonConstellationAzimuth,
									 m_pStarData->m_dNonConstellationAltitude,
									 m_pStarData->m_sNonConstellationShortName,
									 m_pStarData->m_iNonConArraySize,
									 m_cDisplayControl->m_dMagnitude,
									 m_iHorCirRadius,
									 m_iHorCir,
									 bPrintStarNames);
		CPlanetsView::MakeStarsByMag(m_pStarData->m_dConstellationMagnitude,
									 m_pStarData->m_dConstellationAzimuth,
									 m_pStarData->m_dConstellationAltitude,
									 m_pStarData->m_sConstellationShortName,
									 m_pStarData->m_iConArraySize,
									 m_cDisplayControl->m_dMagnitude,
									 m_iHorCirRadius,
									 m_iHorCir,
									 bPrintStarNames);
		break;
	case IDS_CONSTELLATION_ONLY:
		if(m_iConstList.GetAt(0) == 0)
		{
			CPlanetsView::MakeStarsByMagCon(m_pStarData->m_dConstellationMagnitude,
									m_pStarData->m_dConstellationAzimuth,
									m_pStarData->m_dConstellationAltitude,
									m_pStarData->m_sConstellationShortName,
									m_pStarData->m_iConArraySize,
									m_cDisplayControl->m_dMagnitude,
									m_iHorCirRadius,
									m_iHorCir,
									constellationPoints,
									realConPointXs,
									realConPointYs,
									bPrintStarNames);

			conny.MakeAll(this,
						  m_pStarData->m_dConstellationAltitude,
						  constellationPoints,
						  realConPointXs,
						  realConPointYs,
						  m_iHorCirRadius,
						  m_iHorCir,
						  m_cDisplayControl->m_iShowConNames,
						  m_iConR,
						  m_iConG,
						  m_iConB);
		}
		else
		{
			CPlanetsView::MakeStarsByMagList(m_pStarData->m_dConstellationMagnitude,
											 m_pStarData->m_dConstellationAzimuth,
											 m_pStarData->m_dConstellationAltitude,
											 m_pStarData->m_sConstellationShortName,
											 m_pStarData->m_iConArraySize,
											 m_cDisplayControl->m_dMagnitude,
											 m_iHorCirRadius,
											 m_iHorCir,
											 constellationPoints,
											 realConPointXs,
											 realConPointYs,
											 &m_iConstList,
											 bPrintStarNames);
			conny.MakeList(this,
						   m_pStarData->m_dConstellationAltitude,
						   constellationPoints,
						   realConPointXs,
						   realConPointYs,
						   m_iHorCirRadius,
						   m_iHorCir,
						   &m_iConstList,
						   m_cDisplayControl->m_iShowConNames,
						   m_iConR,
						   m_iConG,
						   m_iConB);
		}

		break;
	case IDS_MAGNITUDE_AND_CONSTELLATION:
		CPlanetsView::MakeStarsByMag(m_pStarData->m_dNonConstellationMagnitude,
									 m_pStarData->m_dNonConstellationAzimuth,
									 m_pStarData->m_dNonConstellationAltitude,
									 m_pStarData->m_sNonConstellationShortName,
									 m_pStarData->m_iNonConArraySize,
									 m_cDisplayControl->m_dMagnitude,
									 m_iHorCirRadius,
									 m_iHorCir,
									 bPrintStarNames);
		if(m_iConstList.GetAt(0) == 0)
		{
	CPlanetsView::MakeStarsByMagCon(m_pStarData->m_dConstellationMagnitude,
									m_pStarData->m_dConstellationAzimuth,
									m_pStarData->m_dConstellationAltitude,
									m_pStarData->m_sConstellationShortName,
									m_pStarData->m_iConArraySize,
									m_cDisplayControl->m_dMagnitude,
									m_iHorCirRadius,
									m_iHorCir,
									constellationPoints,
									realConPointXs,
									realConPointYs,
									bPrintStarNames);
		conny.MakeAll(this,
					  m_pStarData->m_dConstellationAltitude,
					  constellationPoints,
					  realConPointXs,
					  realConPointYs,
					  m_iHorCirRadius,
					  m_iHorCir,
					  m_cDisplayControl->m_iShowConNames,
					  m_iConR,
					  m_iConG,
					  m_iConB);
		}
		else
		{
			CPlanetsView::MakeStarsByMagList(m_pStarData->m_dConstellationMagnitude,
											 m_pStarData->m_dConstellationAzimuth,
											 m_pStarData->m_dConstellationAltitude,
											 m_pStarData->m_sConstellationShortName,
											 m_pStarData->m_iConArraySize,
											 m_cDisplayControl->m_dMagnitude,
											 m_iHorCirRadius,
											 m_iHorCir,
											 constellationPoints,
											 realConPointXs,
											 realConPointYs,
											 &m_iConstList,
											 bPrintStarNames);
			conny.MakeList(this,
						   m_pStarData->m_dConstellationAltitude,
						   constellationPoints,
						   realConPointXs,
						   realConPointYs,
						   m_iHorCirRadius,
						   m_iHorCir,
						   &m_iConstList,
						   m_cDisplayControl->m_iShowConNames,
						   m_iConR,
						   m_iConG,
						   m_iConB);
		}
		break;
	}

	if(m_iNumPlanets > 0)
	{
		CPlanetsView::DrawAzAltPlanets(m_iNumPlanets,
									   m_pCStar->m_pPlanetSet,
									   m_pCStar->m_dPlanetAzimuth,
									   m_pCStar->m_dPlanetAltitude,
									   m_iHorCir,
									   m_iHorCirRadius);
	}
	

	CPlanetsView::PrintStarData();
}

void CPlanetsView::AddPlanetToolTip(CRect rect, double az, double alt, CString name)
{
	convert Convert;
	toolTipData data;

	data.type			= PLANET;
	data.rect			= rect;
	data.azimuth		= Convert.DecimalToString(Convert.radianToDegree(az), 2);
	data.altitude		= Convert.DecimalToString(Convert.radianToDegree(alt), 2);
	data.name			= name;

	m_toolTipList.Add(data);
}

void CPlanetsView::AddStarToolTip(CRect rect, int i, int arraySize)
{
	convert Convert;
	toolTipData data;

	data.type	= STAR;
	data.rect	= rect;

	if( IDS_NUM_CON_STARS == arraySize)
	{
		data.azimuth		= Convert.DecimalToString(Convert.radianToDegree(m_pStarData->m_dConstellationAzimuth[i]),2);
		data.altitude		= Convert.DecimalToString(Convert.radianToDegree(m_pStarData->m_dConstellationAltitude[i]), 2);
		data.name			= m_pStarData->m_sConstellationFullName[i];
		data.constellation	= m_pStarData->m_sConstellationLatinConName[i];
		data.magnitude		= Convert.DecimalToString(m_pStarData->m_dConstellationMagnitude[i], 2);
	}
	else
	{
		data.azimuth		= Convert.DecimalToString(Convert.radianToDegree(m_pStarData->m_dNonConstellationAzimuth[i]), 2);
		data.altitude		= Convert.DecimalToString(Convert.radianToDegree(m_pStarData->m_dNonConstellationAltitude[i]), 2);
		data.name			= m_pStarData->m_sNonConstellationFullName[i];
		data.constellation	= m_pStarData->m_sNonConstellationLatinConName[i];
		data.magnitude		= Convert.DecimalToString(m_pStarData->m_dNonConstellationMagnitude[i], 2);
	}
	m_toolTipList.Add(data);
}

void CPlanetsView::AddStarToolTip(CRect rect, double az, double alt, CString name,
								  CString sConst, double mag)
{
	convert Convert;
	toolTipData data;

	data.type			= STAR;
	data.rect			= rect;
	data.azimuth		= Convert.DecimalToString(Convert.radianToDegree(az), 2);
	data.altitude		= Convert.DecimalToString(Convert.radianToDegree(alt), 2);
	data.name			= name;
	data.constellation	= sConst;
	data.magnitude		= Convert.DecimalToString(mag, 2);

	m_toolTipList.Add(data);
}

void CPlanetsView::MakeStarsByMag(double magArray[],
								  double azimuth[], double altitude[],
								  CString names[],
								  int iArraySize, double testMag, int circleRadius,
								  CPoint dOrigin, bool doNames)
{
	convert Convert;
	
	int i;
	double VMag, starRadius, starAngle, dPiOver2;
	int x1, y1, x2, y2;
	CPoint dStar;
	double x, y;
	CRect rec;

	dPiOver2 = Convert.Pi() / 2.0;

	for(i=0; i<iArraySize; i++)
	{
		VMag = magArray[i];
		if(VMag <= testMag)
		{
			if(altitude[i] > 0.0)
			{
			//	Locate star center from position
			//	radius comes from co-altitude
			//	angle from azimuth, but need to run in opposite direction from program
				starRadius = ((dPiOver2 - altitude[i]) / dPiOver2) * circleRadius;
				starAngle = dPiOver2 - azimuth[i] + m_cDisplayControl->m_dViewDirection;
				CPlanetsView::FindTextOriginPoint(dOrigin, starRadius, starAngle, &dStar, &x, &y);

			//	Find printed star size and location
				CPlanetsView::StarPrintSize(VMag, dStar, &x1, &y1, &x2, &y2);

			//	Make star
				CPlanetsView::MakeEllipse(x1, y1, x2, y2, BS_SOLID,
										  m_iStarR, m_iStarG, m_iStarB);

				rec.left = x1;
				rec.right = x2;
				rec.top = y1;
				rec.bottom = y2;
				CPlanetsView::AddStarToolTip( rec, i, iArraySize);

			//	Adjust location of text to move further from star.
				dStar.x += 3;
				dStar.y += 3;
				if(doNames)CPlanetsView::PrintName(dStar, 0, names[i],
												   m_iStarR, m_iStarG, m_iStarB);

			}//end of "if(altitude[i] > 0.0)"
		}//end of "if(VMag <= testMag)"
	}//end of "for(i=0, 1<iArraySize, i++)"
}

void CPlanetsView::MakeStarsByAll(double magArray[],
								  double azimuth[], double altitude[],
								  CString names[],
								  int iArraySize, int circleRadius,
								  CPoint dOrigin, CPoint conPoints[],
								  double realConPointXs[],double realConPointYs[],
								  bool doNames)
{
	convert Convert;
	
	int i;
	double starRadius, starAngle, dPiOver2;
	int x1, y1, x2, y2;
	CPoint dStar;
	CRect rec;

	dPiOver2 = Convert.Pi() / 2.0;

	for(i=0; i<iArraySize; i++)
	{
	//	Locate star center from position
	//	radius comes from co-altitude
	//	angle from azimuth, but need to run in opposite direction from program
		starRadius = ((dPiOver2 - altitude[i]) / dPiOver2) * circleRadius;
		starAngle = dPiOver2 - azimuth[i] + m_cDisplayControl->m_dViewDirection;
		CPlanetsView::FindTextOriginPoint(dOrigin, starRadius, starAngle, &dStar,
										  &realConPointXs[i], &realConPointYs[i]);
		conPoints[i].x = dStar.x;
		conPoints[i].y = dStar.y;

		if(altitude[i] > 0.0)//if above horizon, make ellipse
		{
		//	Find printed star size
			CPlanetsView::StarPrintSize(magArray[i], dStar, &x1, &y1, &x2, &y2);

		//	Make star
			CPlanetsView::MakeEllipse(x1, y1, x2, y2, BS_SOLID,
									  m_iStarR, m_iStarG, m_iStarB);

			rec.left = x1;
			rec.right = x2;
			rec.top = y1;
			rec.bottom = y2;
			CPlanetsView::AddStarToolTip( rec, i, iArraySize);

			//	Adjust location of text to move further from star.
			dStar.x += 3;
			dStar.y += 3;
			if(doNames)CPlanetsView::PrintName(dStar, 0, names[i],
											   m_iStarR, m_iStarG, m_iStarB);
		}
	}//end of "for(i=0, 1<iArraySize, i++)"
}

void CPlanetsView::MakeStarsByList(double magArray[],
								  double azimuth[], double altitude[],
								  CString names[],
								  int iArraySize, int circleRadius,
								  CPoint dOrigin, CPoint conPoints[],
								  double realConPointXs[],double realConPointYs[],
								  CArray<int, int> *iConst, bool doNames)
{
	convert Convert;
	CConstellations conny;
	
	CPoint singleCon[28];//holds point data for each constellation
	double constAltitude[28];//holds altitude data for each constellation
	CString conNames[28];//holds name data for each constellation
	CString conLongNames[28];//long names
	CString conConstName[28];//constellation name for each star
	double realSingleX[28];//real x's for point locations
	double realSingleY[28];//real y's for point locations
	double conAz[28];//azimuths for each constellation
	double conMag[28];//magnitudes for each constellation
	int i, j;
	double starRadius, starAngle, dPiOver2;
	int x1, y1, x2, y2;
	CPoint dStar;
	int iWhichCon, iSize;
	CRect rec;

	dPiOver2 = Convert.Pi() / 2.0;

	for(i=0; i<iArraySize; i++)
	{
	//	Locate star center from position
	//	radius comes from co-altitude
	//	angle from azimuth, but need to run in opposite direction from program
		starRadius = ((dPiOver2 - altitude[i]) / dPiOver2) * circleRadius;
		starAngle = dPiOver2 - azimuth[i] + m_cDisplayControl->m_dViewDirection;
		CPlanetsView::FindTextOriginPoint(dOrigin, starRadius, starAngle, &dStar,
										  &realConPointXs[i], &realConPointYs[i]);
		conPoints[i].x = dStar.x;
		conPoints[i].y = dStar.y;
	}

	//	Make appropriate stars
	for(i=0; i<iConst->GetSize(); i++)
	{
		iWhichCon = iConst->GetAt(i) - 1;
		iSize = conny.LoadSingleArray(conPoints, singleCon,
									  altitude, constAltitude,
									  realConPointXs, realConPointYs,// needed to satisfy
									  realSingleX, realSingleY,//		function
									  iWhichCon);
		conny.LoadSingleArray(names, conNames, iWhichCon);
		conny.LoadSingleArray(magArray, conMag, iWhichCon);
		conny.LoadSingleArray(azimuth, conAz, iWhichCon);
		conny.LoadSingleArray(m_pStarData->m_sConstellationFullName, conLongNames, iWhichCon);
		conny.LoadSingleArray(m_pStarData->m_sConstellationLatinConName, conConstName, iWhichCon);
		for(j=0; j<iSize; j++)
		{
		//	If visible, find printed star size and print
			if(constAltitude[j] > 0.0)
			{
				CPlanetsView::StarPrintSize(conMag[j], singleCon[j],
											&x1, &y1, &x2, &y2);
				CPlanetsView::MakeEllipse(x1, y1, x2, y2, BS_SOLID,
										  m_iStarR, m_iStarG, m_iStarB);

				rec.left = x1;
				rec.right = x2;
				rec.top = y1;
				rec.bottom = y2;
				CPlanetsView::AddStarToolTip( rec, conAz[j], constAltitude[j],
											  conLongNames[j], conConstName[j],
											  conMag[j]);

//				Adjust location of text to move further from star.
				dStar.x += 3;
				dStar.y += 3;
				if(doNames)CPlanetsView::PrintName(singleCon[j], 0, conNames[j],
												   m_iStarR, m_iStarG, m_iStarB);
			}
		}
	}
}

void CPlanetsView::MakeStarsByMagList(double magArray[], double azimuth[],
									  double altitude[],CString names[],
									  int iArraySize, double testMag, int circleRadius,
									  CPoint dOrigin, CPoint conPoints[],
									  double realConPointXs[],double realConPointYs[],
									  CArray<int, int> *iConst, bool doNames)
{
	convert Convert;
	CConstellations conny;
	
	CPoint singleCon[28];//holds point data for each constellation
	double constAltitude[28];//holds altitude data for each constellation
	CString conNames[28];//holds name data for each constellation
	CString conLongNames[28];//long names
	CString conConstName[28];//constellation name for each star
	double realSingleX[28];//real x's for point locations
	double realSingleY[28];//real y's for point locations
	double conAz[28];//azimuths for each constellation
	double conMag[28];//magnitudes for each constellation
	int i, j;
	double starRadius, starAngle, dPiOver2, VMag;
	int x1, y1, x2, y2;
	CPoint dStar;
	CRect rec;
	int iWhichCon, iSize;

	dPiOver2 = Convert.Pi() / 2.0;

	for(i=0; i<iArraySize; i++)
	{
	//	Locate star center from position
	//	radius comes from co-altitude
	//	angle from azimuth, but need to run in opposite direction from program
		starRadius = ((dPiOver2 - altitude[i]) / dPiOver2) * circleRadius;
		starAngle = dPiOver2 - azimuth[i] + m_cDisplayControl->m_dViewDirection;
		CPlanetsView::FindTextOriginPoint(dOrigin, starRadius, starAngle, &dStar,
										  &realConPointXs[i], &realConPointYs[i]);
		conPoints[i].x = dStar.x;
		conPoints[i].y = dStar.y;
	}

	//	Make appropriate stars
	for(i=0; i<iConst->GetSize(); i++)
	{
		iWhichCon = iConst->GetAt(i) - 1;
		iSize = conny.LoadSingleArray(conPoints, singleCon,
									  altitude, constAltitude,
									  realConPointXs, realConPointYs,// needed to satisfy
									  realSingleX, realSingleY,//		function
									  iWhichCon);
		conny.LoadSingleArray(names, conNames, iWhichCon);
		conny.LoadSingleArray(magArray, conMag, iWhichCon);
		conny.LoadSingleArray(azimuth, conAz, iWhichCon);
		conny.LoadSingleArray(m_pStarData->m_sConstellationFullName, conLongNames, iWhichCon);
		conny.LoadSingleArray(m_pStarData->m_sConstellationLatinConName, conConstName, iWhichCon);

		for(j=0; j<iSize; j++)
		{
			VMag = conMag[j];
		//	If visible, find printed star size and print
			if(		constAltitude[j] > 0.0
				&&	VMag < testMag)
			{
				CPlanetsView::StarPrintSize(VMag, singleCon[j],
											&x1, &y1, &x2, &y2);
				CPlanetsView::MakeEllipse(x1, y1, x2, y2, BS_SOLID,
										  m_iStarR, m_iStarG, m_iStarB);

				rec.left = x1;
				rec.right = x2;
				rec.top = y1;
				rec.bottom = y2;
				CPlanetsView::AddStarToolTip( rec, conAz[j], constAltitude[j],
											  conLongNames[j], conConstName[j],
											  conMag[j]);

//				Adjust location of text to move further from star.
				dStar.x += 3;
				dStar.y += 3;
				if(doNames)CPlanetsView::PrintName(singleCon[j], 0, conNames[j],
												   m_iStarR, m_iStarG, m_iStarB);
			}
		}
	}
}

void CPlanetsView::MakeStarsByMagCon(double magArray[],
									 double azimuth[], double altitude[],
									 CString names[],
									 int iArraySize, double testMag,
									 int circleRadius, CPoint dOrigin,
									 CPoint conPoints[],
									 double realConPointXs[],double realConPointYs[],
									 bool doNames)
{
	convert Convert;
	
	int i;
	double starRadius, starAngle, dPiOver2, VMag;
	int x1, y1, x2, y2;
	CPoint dStar;
	CRect rec;

	dPiOver2 = Convert.Pi() / 2.0;

	for(i=0; i<iArraySize; i++)
	{
		VMag = magArray[i];
	//	Locate star center from position
	//	radius comes from co-altitude
	//	angle from azimuth, but need to run in opposite direction from program
		starRadius = ((dPiOver2 - altitude[i]) / dPiOver2) * circleRadius;
		starAngle = dPiOver2 - azimuth[i] + m_cDisplayControl->m_dViewDirection;
		CPlanetsView::FindTextOriginPoint(dOrigin, starRadius, starAngle, &dStar,
										  &realConPointXs[i], &realConPointYs[i]);
		conPoints[i].x = dStar.x;
		conPoints[i].y = dStar.y;

		if(		altitude[i] > 0.0
			&&	VMag <= testMag)
		{
		//	Find printed star size
			CPlanetsView::StarPrintSize(VMag, dStar, &x1, &y1, &x2, &y2);

		//	Make star if above horizon, and mag correct
			CPlanetsView::MakeEllipse(x1, y1, x2, y2, BS_SOLID,
									  m_iStarR, m_iStarG, m_iStarB);

			rec.left = x1;
			rec.right = x2;
			rec.top = y1;
			rec.bottom = y2;
			CPlanetsView::AddStarToolTip( rec, i, iArraySize);

//			Adjust location of text to move further from star.
			dStar.x += 3;
			dStar.y += 3;
			if(doNames)CPlanetsView::PrintName(dStar, 0, names[i],
											   m_iStarR, m_iStarG, m_iStarB);
		}
	}//end of "for(i=0, 1<iArraySize, i++)"
}

void CPlanetsView::StarCardinals(CPoint dOrigin, int circleRadius)
{
	convert Convert;
	CPoint pLoc;
	double dPi, halfPi, sAngle, nAngle, wAngle, eAngle;
	int a, b;

	dPi = Convert.Pi();
	halfPi = dPi / 2.0;
	circleRadius += 5;//add to place letter outside horizon circle

	nAngle = m_cDisplayControl->m_dViewDirection;
	wAngle = nAngle + halfPi;
	sAngle = nAngle + dPi;
	eAngle = nAngle + dPi + halfPi;

	a = (int)floor(circleRadius * sin(m_cDisplayControl->m_dViewDirection));
	b = (int)floor(circleRadius * cos(m_cDisplayControl->m_dViewDirection));

	pLoc.x = dOrigin.x - a;
	pLoc.y = dOrigin.y - b;
	CPlanetsView::PrintName(pLoc, nAngle, "N", m_iCardR, m_iCardG, m_iCardB);

	pLoc.x = dOrigin.x + a;
	pLoc.y = dOrigin.y + b;
	CPlanetsView::PrintName(pLoc, sAngle, "S", m_iCardR, m_iCardG, m_iCardB);

	pLoc.x = dOrigin.x - b;
	pLoc.y = dOrigin.y + a;
	CPlanetsView::PrintName(pLoc, wAngle, "W", m_iCardR, m_iCardG, m_iCardB);

	pLoc.x = dOrigin.x + b;
	pLoc.y = dOrigin.y - a;
	CPlanetsView::PrintName(pLoc, eAngle, "E", m_iCardR, m_iCardG, m_iCardB);
}

void CPlanetsView::StarPrintSize(double dMagnitude, CPoint dStar,
								int *x1, int *y1, int *x2, int *y2)
{
	int x1Add, y1Add, x2Add, y2Add;
	x1Add = y1Add = 1;
	x2Add = y2Add = 0;

	if(dMagnitude <  6)//	1+1
	{
		x2Add += 1;
		y2Add += 1;
	}
	if(dMagnitude <  5)//	1+2
	{
		x1Add += 1;
		y1Add += 1;
	}
	if(dMagnitude <  4)//	2+2
	{
		x2Add += 1;
		y2Add += 1;
	}
	if(dMagnitude <  3)//	2+3
	{
		x1Add += 1;
		y1Add += 1;
	}
	if(dMagnitude <  2)//	3+3
	{
		x2Add += 1;
		y2Add += 1;
	}
	if(dMagnitude <  1)//	3+4
	{
		x1Add += 1;
		y1Add += 1;
	}
	if(dMagnitude <  0)//	4+4
	{
		x2Add += 1;
		y2Add += 1;
	}
	if(dMagnitude < -1)//	4+5
	{
		x1Add += 1;
		y1Add += 1;
	}
	
	*x1 = dStar.x - x1Add;
	*y1 = dStar.y + y1Add;
	*x2 = dStar.x + x2Add;
	*y2 = dStar.y - y2Add;
}

//	Make a chart
void CPlanetsView::DrawChart(CHor* pCHor, CTimeLocation* pTimeLocation)
{
	CPoint dOrigin;
	int circleRadius, smallCircleRadius, radiusDif;
	m_uViewType = HOROSCOPE_VIEW;
    CClientDC myDC(this);
	myDC.SetMapMode(MM_LOENGLISH);
	circleRadius = /*430;*/ 350;
	smallCircleRadius = 75;
	radiusDif = circleRadius - smallCircleRadius;
	dOrigin.x = /*670;*/ 425;
	dOrigin.y = /*-530;*/ -400;

//	Print out all horizontal text except aspects
	CPlanetsView::PrintChartNames(pCHor);

//	Print circles and lines of chart
	CPlanetsView::MakeCircle(dOrigin.x, dOrigin.y, circleRadius, 0, 0, 0);
	CPlanetsView::MakeCircle(dOrigin.x, dOrigin.y, smallCircleRadius, 0, 0, 0);

//	Draw house cusp lines and label house cusps
	CPlanetsView::HouseLines(pCHor, dOrigin, smallCircleRadius, circleRadius);
	
	CPlanetsView::DrawAspectTable();
	CPlanetsView::LabelAspectTable(pCHor);
	CPlanetsView::PopulateAspectTable(pCHor);

//	place body strings around 
//	chart in their proper house.  Notice that this does not place bodies
//	relative to their true positions.  If there is one body in a house
//	it is placed in the middle of that house, if 2 bodies, house is 
//	split into thirds etc.
	CPlanetsView::PlaceBodiesOnChart(pCHor, dOrigin, smallCircleRadius,
									 circleRadius - 10);
}

//	Puts labels on aspect table
void CPlanetsView::LabelAspectTable(class CHor *pCHor)
{
    CClientDC pDC(this);

	pDC.SetMapMode(MM_LOENGLISH);

	CPoint pText;
	int hGap, vGap, i;
	CString sText;
	
	CFont font;
	struct fontAttributes myFont;

	CPlanetsView::MakeFont(0, &font, &myFont);
	CFont* def_font = pDC.SelectObject(&font);
	pDC.SetTextColor(RGB(0, 0, 0));

	pText.x = 10;
	pText.y = -670;
	hGap = 35;
	vGap = 35;
	
	for(i=1; i<12; i++)
	{
		pText.x += hGap;
		pText.y -= vGap;
		switch ( i )
		{
		case 1:
			sText = "Su";
			break;
		case 2:
			sText = "Mo";
			break;
		case 3:
			sText = "Me";
			break;
		case 4:
			sText = "V";
			break;
		case 5:
			sText = "NN";
			break;
		case 6:
			sText = "Ma";
			break;
		case 7:
			sText = "Ju";
			break;
		case 8:
			sText = "Sa";
			break;
		case 9:
			sText = "U";
			break;
		case 10:
			sText = "N";
			break;
		case 11:
			sText = "P";
			break;
		}//	end of "switch ( i )"
		
		pDC.TextOut(pText.x, pText.y, sText);
		CSize textSize = pDC.GetTextExtent(sText);

		m_pTextCur = GetDocument()->NewText();
		m_pTextCur->m_pTextOrig.x = pText.x;
		m_pTextCur->m_pTextOrig.y = pText.y;
		m_pTextCur->m_pTextLocation.x = pText.x;
		m_pTextCur->m_pTextLocation.y = pText.y;
		m_pTextCur->m_width = textSize.cx;
		m_pTextCur->m_height = textSize.cy;
		m_pTextCur->m_text = sText;
		m_pTextCur->m_font = myFont;
		m_pTextCur->m_iPenR = 0;
		m_pTextCur->m_iPenG = 0;
		m_pTextCur->m_iPenB = 0;
		m_pTextCur->m_bHasPointer = false;

	}//	end of "for(i=1; i<12; i++)"

	pDC.SelectObject(def_font);
	font.DeleteObject();
}

//	Place body strings around chart in their proper house.  Notice
//	that this does not place bodies relative to their true positions.
//	If there is one body in a house it is placed in the middle of
//	that house, if 2 bodies, house is split into thirds etc.
void CPlanetsView::PlaceBodiesOnChart(class CHor* pCHor, CPoint dOrigin,
									  int innerCircle, int outerCircle)
{
	convert Convert;

	CArray< int, int > HouseHolder;
	int i, j, k, l, m, temp, hHSize, numberOfBodies, printCircle;
	int iPasses;
	double lambda, Pi30, gap, offset;
	CRect textBox;
	bool bChanged;

	Pi30 = Convert.Pi() / (double)6;

	for(i=1; i<13; i++)
	{

		for (j=0; j<11; j++)
		{
			if(pCHor->m_pChart.m_iBodyHouse[j] == i)
			{//	Are there any bodies in house [i], if so then add them to HouseHolder
				HouseHolder.Add(j);
			}
		}
		hHSize = HouseHolder.GetSize();
		if(hHSize > 1)
		{
			bChanged = true;
			iPasses = 0;
			for (k=0; k<hHSize - 1; k++)
			{
				if(bChanged == false) continue;
				bChanged = false;
				iPasses++;
				for(l=0; l<hHSize -iPasses; l++)
				{
					if(		pCHor->m_pChart.m_dBodyHousePosition[HouseHolder[l]]
						>	pCHor->m_pChart.m_dBodyHousePosition[HouseHolder[l+1]])
					{
						temp = HouseHolder[l];
						HouseHolder[l] = HouseHolder[l+1];
						HouseHolder[l+1] = temp;
						bChanged = true;
					}
				}
			}
		}

		numberOfBodies = HouseHolder.GetSize();

		if(numberOfBodies >0)
		{
			if(i > 3 && i < 10)
			{
				printCircle = outerCircle - 135;
				offset = 3.12;
			}
			else
			{
				printCircle = outerCircle;
				offset = 3.16;
			}
			gap = Pi30 / (numberOfBodies + 1);
			for(m=1; m<numberOfBodies + 1; m++)
			{
				lambda = Convert.radianPositiveValue(offset - ((i-1) * Pi30 + m*gap));
				CPlanetsView::DrawBody(dOrigin, printCircle, lambda,
					pCHor->m_pChart.m_sBodyString[HouseHolder[m-1]]);
			}
			HouseHolder.RemoveAll();
		}
	}
}

//	Given origin, radius, angle and text, print the text at the
//	proper angle at the right location
void CPlanetsView::DrawBody(CPoint dOrigin, double radius,
							double lambda, CString name)
{
    CClientDC myDC(this);

	myDC.SetMapMode(MM_LOENGLISH);

	double textAngle;
	CPoint dBody, textLocation;
	CFont font;
	struct fontAttributes myFont;
	double x, y;

	CPlanetsView::SetTextAngle(lambda, textAngle);
	CPlanetsView::MakeFont(textAngle, &font, &myFont);
	CPlanetsView::FindTextOriginPoint(dOrigin, radius, lambda, &dBody, &x, &y );

	myDC.SetTextColor(RGB(0, 0, 0));
	CFont* def_font = myDC.SelectObject(&font);
	myDC.TextOut(dBody.x, dBody.y, name);
	CSize textSize = myDC.GetTextExtent(name);
	myDC.SelectObject(def_font);
	font.DeleteObject();

	m_pTextCur = GetDocument()->NewText();
	m_pTextCur->m_pTextOrig.x = dBody.x;
	m_pTextCur->m_pTextOrig.y = dBody.y;
	m_pTextCur->m_pTextLocation.x = dBody.x;
	m_pTextCur->m_pTextLocation.y = dBody.y;
	m_pTextCur->m_width = textSize.cx;
	m_pTextCur->m_height = textSize.cy;
	m_pTextCur->m_text = name;
	m_pTextCur->m_font = myFont;
	m_pTextCur->m_iPenR = 0;
	m_pTextCur->m_iPenG = 0;
	m_pTextCur->m_iPenB = 0;
	m_pTextCur->m_bHasPointer = false;
}

void CPlanetsView::PrintStarData()
{
	convert Convert;
	
	CPoint textLoc;
	CString text;
	CString sLat, sLon, NSString, EWString, sVMag, sViewDir;
	double lat, lon, dVMag;

	lat = m_pCStar->m_dLatitude;
	lon = m_pCStar->m_dLongitude;
	NSString = "N";
	EWString = "W";
	if(lat < 0)NSString = "S";
	if(lon < 0)EWString = "E";
	dVMag = m_cDisplayControl->m_dMagnitude;
	sViewDir = Convert.DecimalToString(Convert.degreePositiveValue(Convert.degreeReduce(floor(m_cDisplayControl->m_dViewDirection * 180 / Convert.Pi()))),0);

	sLat = Convert.HMSToString(Convert.degreeToDMS(Convert.radianToDegree(fabs(lat))), "d", 2);
	sLon = Convert.HMSToString(Convert.degreeToDMS(Convert.radianToDegree(fabs(lon))), "d", 2);
	sVMag = Convert.DecimalToString(dVMag, 2);

	text = m_pCStar->m_sDateString;

	textLoc.x = 50;
	textLoc.y = -1000;
	CPlanetsView::PrintName(textLoc, 0, text, 0, 0, 0);

	textLoc.y -= 16;
	text = sLat + " " + NSString;
	CPlanetsView::PrintName(textLoc, 0, text, 0, 0, 0);

	textLoc.y -= 16;
	text = sLon + " " + EWString;
	CPlanetsView::PrintName(textLoc, 0, text, 0, 0, 0);

	textLoc.y -= 16;
	text = "VMag < " + sVMag;
	CPlanetsView::PrintName(textLoc, 0, text, 0, 0, 0);

	textLoc.y -= 16;
	text = "Looking " + sViewDir;
	CPlanetsView::PrintName(textLoc, 0, text, 0, 0, 0);
}

//	Given location, angle and string print string
void CPlanetsView::PrintName(CPoint textLoc, double textAngle, CString text,
							 int R, int G, int B)
{
    if(text != "")
	{
		CClientDC pDC(this);

		pDC.SetMapMode(MM_LOENGLISH);

		CFont font;
		struct fontAttributes myFont;

		CPlanetsView::MakeFont(textAngle, &font, &myFont);
		CFont* def_font = pDC.SelectObject(&font);
		pDC.SetTextColor(RGB(R, G, B));
		CSize textSize = pDC.GetTextExtent(text);

//	First save coordinates of points
		m_pTextCur = GetDocument()->NewText();
		m_pTextCur->m_pTextOrig.x = textLoc.x;
		m_pTextCur->m_pTextOrig.y = textLoc.y;
		m_pTextCur->m_pTextLocation.x = textLoc.x;
		m_pTextCur->m_pTextLocation.y = textLoc.y;
		m_pTextCur->m_width = textSize.cx;
		m_pTextCur->m_height = textSize.cy;
		m_pTextCur->m_text = text;
		m_pTextCur->m_font = myFont;
		m_pTextCur->m_iPenR = R;
		m_pTextCur->m_iPenG = G;
		m_pTextCur->m_iPenB = B;
		m_pTextCur->m_bHasPointer = false;

//	Then transform to scroll position
		CPoint sPos = GetScrollPosition();
		TransformToScrollPos(sPos.x, sPos.y, &textLoc.x, &textLoc.y );

		pDC.TextOut(textLoc.x + 1, textLoc.y + 1, text);

		pDC.SelectObject(def_font);
		pDC.SetTextColor(RGB(0, 0, 0));

		font.DeleteObject();
	}
}

//	Prints out all horizontal text except aspects
void CPlanetsView::PrintChartNames(class CHor* pCHor)
{
	CString name;
	CPoint dBody;
	int iNewLine;

	iNewLine = 20;

	dBody.x = 20;
	dBody.y = -20;
	CPlanetsView::PrintName(dBody, 0, pCHor->m_sName, 0, 0, 0);

	dBody.y -= iNewLine;
	CPlanetsView::PrintName(dBody, 0, pCHor->m_sBirthPlace, 0, 0, 0);

	dBody.y -= iNewLine;
	CString text = pCHor->m_pCTimeLocation->m_cLatitude +
				   " " +
				   pCHor->m_pCTimeLocation->m_cLatitude_NS +
				   "  " +
				   pCHor->m_pCTimeLocation->m_cLongitude +
				   " " +
				   pCHor->m_pCTimeLocation->m_cLongitude_WE;
	CPlanetsView::PrintName(dBody, 0, text, 0, 0, 0);

	dBody.y -= iNewLine;
	CPlanetsView::PrintName(dBody, 0, pCHor->m_sBirthTime, 0, 0, 0);

	dBody.x = 450;
	dBody.y = -1000;
	name = "Masculine: " + pCHor->m_pChart.m_sNumMasculine;
	CPlanetsView::PrintName(dBody, 0, name, 0, 0, 0);

	dBody.y -= iNewLine;
	name = "Feminine: " + pCHor->m_pChart.m_sNumFeminine;
	CPlanetsView::PrintName(dBody, 0, name, 0, 0, 0);

	dBody.x = 525;
	dBody.y = -1000;
	name = "Cardinal: " + pCHor->m_pChart.m_sNumCardinal;
	CPlanetsView::PrintName(dBody, 0, name, 0, 0, 0);

	dBody.y -= iNewLine;
	name = "Fixed: " + pCHor->m_pChart.m_sNumFixed;
	CPlanetsView::PrintName(dBody, 0, name, 0, 0, 0);

	dBody.y -= iNewLine;
	name = "Mutable: " + pCHor->m_pChart.m_sNumMutable;
	CPlanetsView::PrintName(dBody, 0, name, 0, 0, 0);

	dBody.x = 600;
	dBody.y = -1000;
	name = "Fire: " + pCHor->m_pChart.m_sNumFire;
	CPlanetsView::PrintName(dBody, 0, name, 0, 0, 0);

	dBody.y -= iNewLine;
	name = "Earth: " + pCHor->m_pChart.m_sNumEarth;
	CPlanetsView::PrintName(dBody, 0, name, 0, 0, 0);

	dBody.y -= iNewLine;
	name = "Air: " + pCHor->m_pChart.m_sNumAir;
	CPlanetsView::PrintName(dBody, 0, name, 0, 0, 0);

	dBody.y -= iNewLine;
	name = "Water: " + pCHor->m_pChart.m_sNumWater;
	CPlanetsView::PrintName(dBody, 0, name, 0, 0, 0);
}

//	Given center and radius of two circles, label house cusps and draw
//	house cusp lines.  Labels are made at angle of cusp line except for
//	house 4 and 10 which are horizontal (perpendicular to cusp line).
void CPlanetsView::HouseLines(class CHor* pCHor, CPoint dOrigin,
							  int innerRadius, int outerRadius)
{
    CClientDC pDC(this);

	pDC.SetMapMode(MM_LOENGLISH);

	convert Convert;

	double xStart, yStart, zStart;
	int i, offset, iSpace;
	CPoint pStart, dBody;
	double dAngle, Pi30, dPi, dTextAngle, d9Angle;
	CFont font;
	struct fontAttributes myFont;
	CString sTemp, sText;
	int R, G, B;
	double x, y;

	R = G = B = 0;
	pDC.SetTextColor(RGB(R, G, B));

	dPi = Convert.Pi();
	Pi30 = dPi / (double)6;

	dAngle = dPi;

//	First write house cusps
	for(i=1; i<13; i++)
	{
		if(i > 3 && i < 11)
		{//	These bodies start at outer circle and print outwards
		 //	(see exceptions below)
			offset = outerRadius + 10;
			dTextAngle = dAngle - .02;
		}
		else
		{//	These bodies start beyond outer circle and print inwards
		 //	towards the outer circle
			offset = outerRadius + 70;
			dTextAngle = dAngle + .02;
		}

		if(i == 1 || i == 7)
		{//	These print horizontally, 1 inward, 7 outward
			CPlanetsView::SetTextAngle(0, d9Angle);
			CPlanetsView::MakeFont(d9Angle, &font, &myFont);
			CPlanetsView::FindTextOriginPoint(dOrigin, offset, dTextAngle, &dBody, &x, &y);
			CFont* def_font = pDC.SelectObject(&font);
			dBody.y += 10;
			if(i==1)
			{
				dBody.x += 25;
			}
			sTemp = pCHor->m_pChart.m_sHouseSign[i];// "30 deg 15m Can"

		//	For 1 and 7, break up into "30 deg 15 m" and "Can"
			iSpace = sTemp.Find(LPCTSTR(" "), 4);
			sText = sTemp.Left(iSpace);
		//	Write first part
			pDC.TextOut(dBody.x, dBody.y, sText);
			CSize textSize = pDC.GetTextExtent(sText);
			pDC.SelectObject(def_font);
			font.DeleteObject();

			m_pTextCur = GetDocument()->NewText();
			m_pTextCur->m_pTextOrig.x = dBody.x;
			m_pTextCur->m_pTextOrig.y = dBody.y;
			m_pTextCur->m_pTextLocation.x = dBody.x;
			m_pTextCur->m_pTextLocation.y = dBody.y;
			m_pTextCur->m_width = textSize.cx;
			m_pTextCur->m_height = textSize.cy;
			m_pTextCur->m_text = sText;
			m_pTextCur->m_font = myFont;
			m_pTextCur->m_iPenR = R;
			m_pTextCur->m_iPenG = G;
			m_pTextCur->m_iPenB = B;
			m_pTextCur->m_bHasPointer = false;

		//	New line
			dBody.x += 5;
			dBody.y -= 20;

		//	Write second part
			sText = sTemp.Right(sTemp.GetLength() - iSpace);
			pDC.TextOut(dBody.x, dBody.y, sText);
			textSize = pDC.GetTextExtent(sText);
			pDC.SelectObject(def_font);
			font.DeleteObject();

			m_pTextCur = GetDocument()->NewText();
			m_pTextCur->m_pTextOrig.x = dBody.x;
			m_pTextCur->m_pTextOrig.y = dBody.y;
			m_pTextCur->m_pTextLocation.x = dBody.x;
			m_pTextCur->m_pTextLocation.y = dBody.y;
			m_pTextCur->m_width = textSize.cx;
			m_pTextCur->m_height = textSize.cy;
			m_pTextCur->m_text = sText;
			m_pTextCur->m_font = myFont;
			m_pTextCur->m_iPenR = R;
			m_pTextCur->m_iPenG = G;
			m_pTextCur->m_iPenB = B;
			m_pTextCur->m_bHasPointer = false;
		}//	end of "if(i == 1 || i == 7)"
		else if(i == 10 || i == 4)
		{//	These print horizontally, 10 up top, 4 on bottom
			CPlanetsView::SetTextAngle(0, d9Angle);
			CPlanetsView::MakeFont(d9Angle, &font, &myFont);
			CPlanetsView::FindTextOriginPoint(dOrigin, offset, dTextAngle, &dBody, &x, &y);
			if(i==10)
			{
				dBody.x -= 20;
				dBody.y += 10;
			}
			else
			{
				dBody.x -= 30;
				dBody.y -= 5;
			}
			CFont* def_font = pDC.SelectObject(&font);
			pDC.TextOut(dBody.x, dBody.y, pCHor->m_pChart.m_sHouseSign[i]);
			CSize textSize = pDC.GetTextExtent(pCHor->m_pChart.m_sHouseSign[i]);
			pDC.SelectObject(def_font);
			font.DeleteObject();

			m_pTextCur = GetDocument()->NewText();
			m_pTextCur->m_pTextOrig.x = dBody.x;
			m_pTextCur->m_pTextOrig.y = dBody.y;
			m_pTextCur->m_pTextLocation.x = dBody.x;
			m_pTextCur->m_pTextLocation.y = dBody.y;
			m_pTextCur->m_width = textSize.cx;
			m_pTextCur->m_height = textSize.cy;
			m_pTextCur->m_text = pCHor->m_pChart.m_sHouseSign[i];
			m_pTextCur->m_font = myFont;
			m_pTextCur->m_iPenR = R;
			m_pTextCur->m_iPenG = G;
			m_pTextCur->m_iPenB = B;
			m_pTextCur->m_bHasPointer = false;
		}//	end of "if(i == 10 || i == 4)"
		else
		{
			CPlanetsView::DrawBody(dOrigin, offset, dTextAngle, pCHor->m_pChart.m_sHouseSign[i]);
		}//	end of "else"

		pDC.SetTextColor(RGB(0, 0, 0));
		
//	Now draw house cusp lines

	//	With our current angle, find start point of cusp line.  This starts 
	//	on inner circle and ends on outer circle so we need to find x, y
	//	location of inner circle for this line
		Convert.sphericalToCartesian(dAngle, 0, innerRadius, xStart, yStart, zStart);
		pStart.x = (int)(xStart + dOrigin.x);
		pStart.y = (int)(dOrigin.y - yStart);

	//	Now draw line.
		CPlanetsView::DrawLine(pStart, outerRadius - innerRadius, dAngle);

	//	Increment dAngle so it is ready for the next cusp
		dAngle = Convert.radianPositiveValue(dAngle - Pi30);
	}//	end of "for(i=1; i<13; i++)"
}//end of "CPlanetsView::HouseLines"

//	Draw table for the listing and labelling of aspects
void CPlanetsView::DrawAspectTable()
{
    CClientDC pDC(this);

	pDC.SetMapMode(MM_LOENGLISH);
	CPen penNew;
	CPen* pOldPen;

	penNew.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(0, 0, 0));
	pOldPen = pDC.SelectObject(&penNew);

	CPoint Point1, Point2;
	int TopX, TopY, BottomX, BottomY, hGap, vGap;
	int i;

	TopX = 35;
	TopY = -695;
	hGap = 35;
	vGap = 35;
	BottomX = TopX;
	BottomY = TopY - (vGap * 11);

	Point1.x = TopX;
	Point1.y = TopY;
	Point2.x = TopX;
	Point2.y = BottomY;

	pDC.MoveTo(Point1);
	pDC.LineTo(Point2);
	
	m_pStrokeCur = GetDocument()->NewStroke();
	m_pStrokeCur->m_pointArray.Add(Point1);
	m_pStrokeCur->m_pointArray.Add(Point2);
	m_pStrokeCur->m_iPenR = 0;
	m_pStrokeCur->m_iPenG = 0;
	m_pStrokeCur->m_iPenB = 0;

	Point1.x = TopX;
	Point1.y = TopY + vGap;
	Point2.x = Point1.x;
	Point2.y = BottomY;

	for(i=1; i<12; i++)
	{
		Point1.x += hGap;
		Point1.y -= vGap;
		Point2.x += hGap;

		pDC.MoveTo(Point1);
		pDC.LineTo(Point2);
	
		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(Point1);
		m_pStrokeCur->m_pointArray.Add(Point2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;
	}

	Point1.x = TopX;
	Point1.y = TopY + vGap;
	Point2.x = Point1.x;
	Point2.y = Point1.y;

	for(i=1; i<12; i++)
	{
		Point1.y -= vGap;
		Point2.x += hGap;
		Point2.y = Point1.y;
		
		pDC.MoveTo(Point1);
		pDC.LineTo(Point2);
	
		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(Point1);
		m_pStrokeCur->m_pointArray.Add(Point2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;
	}

	Point1.y = Point2.y = Point1.y - vGap;
	pDC.MoveTo(Point1);
	pDC.LineTo(Point2);
	
	m_pStrokeCur = GetDocument()->NewStroke();
	m_pStrokeCur->m_pointArray.Add(Point1);
	m_pStrokeCur->m_pointArray.Add(Point2);
	m_pStrokeCur->m_iPenR = 0;
	m_pStrokeCur->m_iPenG = 0;
	m_pStrokeCur->m_iPenB = 0;

	pDC.SelectObject(pOldPen);
	penNew.DeleteObject();
}

//	If there is an aspect, places it in the table.  Table is filled from top
//	to bottom, then next column and top to bottom again
void CPlanetsView::PopulateAspectTable(CHor *pCHor)
{
    CClientDC pDC(this);

	pDC.SetMapMode(MM_LOENGLISH);

	CPoint tPoint, gPoint;
	CFont font;
	struct fontAttributes myFont;
	int i, hGap, vGap, xStart, yStart, iAspect;
	CString name;

	xStart = 40;
	yStart = -752;
	tPoint.x = xStart;
	tPoint.y = yStart;
	hGap = 35;
	vGap = 35;
	
	pDC.SetTextColor(RGB(0, 0, 0));
	CPlanetsView::MakeFont(0, &font, &myFont);

	CFont* def_font = pDC.SelectObject(&font);

	for(i=0; i<55; i++)
	{
		iAspect = pCHor->m_pChart.m_iBodyAspect[i];
		if(iAspect != 0)// 0 = no aspect, 1 = aspect
		{//	Write value of aspect into proper location in table
			name = pCHor->m_pChart.m_sBodyAspect[i];
			pDC.TextOut(tPoint.x, tPoint.y, name);
			CSize textSize = pDC.GetTextExtent(name);
			pDC.SelectObject(def_font);
			font.DeleteObject();

			m_pTextCur = GetDocument()->NewText();
			m_pTextCur->m_pTextOrig.x = tPoint.x;
			m_pTextCur->m_pTextOrig.y = tPoint.y;
			m_pTextCur->m_pTextLocation.x = tPoint.x;
			m_pTextCur->m_pTextLocation.y = tPoint.y;
			m_pTextCur->m_width = textSize.cx;
			m_pTextCur->m_height = textSize.cy;
			m_pTextCur->m_text = name;
			m_pTextCur->m_font = myFont;
			m_pTextCur->m_iPenR = 0;
			m_pTextCur->m_iPenG = 0;
			m_pTextCur->m_iPenB = 0;
			m_pTextCur->m_bHasPointer = false;

		//	Move location to draw aspect symbol
			gPoint.x = tPoint.x;
			gPoint.y = tPoint.y + 5;

		//	Draw aspect symbol
			CPlanetsView::MakeAspect(iAspect, gPoint);
		}//	end of "if(iAspect != 0)"

	//	Need to move start point of each column periodically
		switch ( i )
		{
		case 9:
			tPoint.x += hGap;
			tPoint.y = yStart;
			break;

		case 18:
			tPoint.x += hGap;
			tPoint.y = yStart - vGap * 1;
			break;

		case 26:
			tPoint.x += hGap;
			tPoint.y = yStart - vGap * 2;
			break;

		case 33:
			tPoint.x += hGap;
			tPoint.y = yStart - vGap * 3;
			break;

		case 39:
			tPoint.x += hGap;
			tPoint.y = yStart - vGap * 4;
			break;

		case 44:
			tPoint.x += hGap;
			tPoint.y = yStart - vGap * 5;
			break;

		case 48:
			tPoint.x += hGap;
			tPoint.y = yStart - vGap * 6;
			break;

		case 51:
			tPoint.x += hGap;
			tPoint.y = yStart - vGap * 7;
			break;

		case 53:
			tPoint.x += hGap;
			tPoint.y = yStart - vGap * 8;
			break;
		}
	//	Move down for next aspect
		tPoint.y -= vGap;
	}
}

//	Given origin, radius and angle returns x, y coordinates
void CPlanetsView::FindTextOriginPoint(CPoint dOrigin, double innerRadius,
										 double lambda, CPoint* pPoint,
										 double *x, double *y)
{
	convert Convert;

	double xStart, yStart, zStart;

	Convert.sphericalToCartesian(lambda, 0, innerRadius,
						xStart, yStart, zStart);
	*x = xStart + (double)dOrigin.x;
	*y = (double)dOrigin.y - yStart;
	pPoint->x = (int)(xStart + dOrigin.x);
	pPoint->y = (int)(dOrigin.y - yStart);
}

void CPlanetsView::TransformToScrollPos(int sPosX, int sPosY,
										int *pPosX, int *pPosY)
{
	*pPosX -= sPosX;
	*pPosY -= sPosY;
}

void CPlanetsView::TransformToScrollPos(int sPosX, int sPosY,
										long *pPosX, long *pPosY)
{
	*pPosX -= sPosX;
	*pPosY -= sPosY;
}


//	Given origin, radius and angle draw line starting at origin and moving 
//	a distance radius at an angle of lambda
void CPlanetsView::DrawLine(CPoint dOrigin, double radius, double lambda)
{
    CClientDC myDC(this);

	myDC.SetMapMode(MM_LOENGLISH);
	convert Convert;

	double xBody, yBody, zBody;
	CPoint dBody;

	CPen penNew;
	CPen* pOldPen;

	penNew.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(0, 0, 0));
	pOldPen = myDC.SelectObject(&penNew);

	Convert.sphericalToCartesian(lambda, 0, radius, xBody, yBody, zBody);

	dBody.x = (int)(xBody + dOrigin.x);
	dBody.y = (int)(dOrigin.y - yBody);

//	First save coordinates of points
	m_pStrokeCur = GetDocument()->NewStroke();
	m_pStrokeCur->m_pointArray.Add(dOrigin);
	m_pStrokeCur->m_pointArray.Add(dBody);
	m_pStrokeCur->m_iPenR = 0;
	m_pStrokeCur->m_iPenG = 0;
	m_pStrokeCur->m_iPenB = 0;

//	Then transform to scroll position
	CPoint sPos = GetScrollPosition();
	TransformToScrollPos(sPos.x, sPos.y, &dOrigin.x, &dOrigin.y );
	TransformToScrollPos(sPos.x, sPos.y, &dBody.x, &dBody.y );

	myDC.MoveTo(dOrigin);
	myDC.LineTo(dBody);

	myDC.SelectObject(pOldPen);
	penNew.DeleteObject();
	
}

void CPlanetsView::MakeLine(CPoint pointOne, CPoint pointTwo, int R, int G, int B)
{
    CClientDC myDC(this);

	myDC.SetMapMode(MM_LOENGLISH);

	CPen newPen;
	CPen* pOldPen;

	newPen.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(R, G, B));
	pOldPen = myDC.SelectObject(&newPen);

//	First save coordinates of points
	m_pStrokeCur = GetDocument()->NewStroke();
	m_pStrokeCur->m_pointArray.Add(pointOne);
	m_pStrokeCur->m_pointArray.Add(pointTwo);
	m_pStrokeCur->m_iPenR = R;
	m_pStrokeCur->m_iPenG = G;
	m_pStrokeCur->m_iPenB = B;

//	Then transform to scroll position
	CPoint sPos = GetScrollPosition();
	TransformToScrollPos(sPos.x, sPos.y, &pointOne.x, &pointOne.y );
	TransformToScrollPos(sPos.x, sPos.y, &pointTwo.x, &pointTwo.y );

	myDC.MoveTo(pointOne);
	myDC.LineTo(pointTwo);

	myDC.SelectObject(pOldPen);
	newPen.DeleteObject();
	
}

void CPlanetsView::MakePointer(CPoint pointOne, CPoint pointTwo, int R, int G, int B)
{
    CClientDC myDC(this);

	myDC.SetMapMode(MM_LOENGLISH);

	CPen newPen;
	CPen* pOldPen;

	newPen.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(R, G, B));
	pOldPen = myDC.SelectObject(&newPen);

	myDC.MoveTo(pointOne);
	myDC.LineTo(pointTwo);

	myDC.SelectObject(pOldPen);
	newPen.DeleteObject();
}


void CPlanetsView::DrawLines(CPoint dOrigin,
							 double radius, double lambda,
							 double textDistance, CString name)
{
    CClientDC myDC(this);

	myDC.SetMapMode(MM_LOENGLISH);
	convert Convert;

	double xBody, yBody, zBody, textAngle;
	CPoint dBody, textLocation;
	CFont font;
	struct fontAttributes myFont;

	CPen penNew;
	CPen* pOldPen;

	penNew.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(0, 0, 0));
	pOldPen = myDC.SelectObject(&penNew);

	Convert.sphericalToCartesian(lambda, 0, radius, xBody, yBody, zBody);
	dBody.x = (int)(xBody + dOrigin.x);
	dBody.y = (int)(dOrigin.y - yBody);
	myDC.MoveTo(dOrigin);
	myDC.LineTo(dBody);
	
	m_pStrokeCur = GetDocument()->NewStroke();
	m_pStrokeCur->m_pointArray.Add(dOrigin);
	m_pStrokeCur->m_pointArray.Add(dBody);
	m_pStrokeCur->m_iPenR = 0;
	m_pStrokeCur->m_iPenG = 0;
	m_pStrokeCur->m_iPenB = 0;
				
	CPlanetsView::SetTextAngle(lambda, textAngle);
	CPlanetsView::MakeFont(textAngle, &font, &myFont);
	CPlanetsView::GetTextLocation(dOrigin, dBody, &textLocation, textDistance);

	myDC.SetTextColor(RGB(0, 0, 0));
	CFont* def_font = myDC.SelectObject(&font);
	myDC.TextOut(textLocation.x, textLocation.y, name);
	CSize textSize = myDC.GetTextExtent(name);
	myDC.SelectObject(def_font);
	font.DeleteObject();
	myDC.SelectObject(pOldPen);
	penNew.DeleteObject();

	m_pTextCur = GetDocument()->NewText();
	m_pTextCur->m_pTextOrig.x = textLocation.x;
	m_pTextCur->m_pTextOrig.y = textLocation.y;
	m_pTextCur->m_pTextLocation.x = textLocation.x;
	m_pTextCur->m_pTextLocation.y = textLocation.y;
	m_pTextCur->m_width = textSize.cx;
	m_pTextCur->m_height = textSize.cy;
	m_pTextCur->m_text = name;
	m_pTextCur->m_font = myFont;
	m_pTextCur->m_iPenR = 0;
	m_pTextCur->m_iPenG = 0;
	m_pTextCur->m_iPenB = 0;
	m_pTextCur->m_bHasPointer = false;
}

//	Given location of center and radius, draw circle
void CPlanetsView::MakeCircle(int x, int y, int radius, int R, int G, int B)
{
    CClientDC pcDC(this);

	pcDC.SetMapMode(MM_LOENGLISH);

	CPen penNew;
	CPen* pOldPen;

	penNew.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(R, G, B));
	pOldPen = pcDC.SelectObject(&penNew);

//	First save coordinates of points
	m_pArcCur = GetDocument()->NewArc();
	m_pArcCur->m_arcArray.Add(x - radius);
	m_pArcCur->m_arcArray.Add(y - radius);
	m_pArcCur->m_arcArray.Add(x + radius);
	m_pArcCur->m_arcArray.Add(y + radius);
	m_pArcCur->m_arcArray.Add(x + radius);
	m_pArcCur->m_arcArray.Add(y);
	m_pArcCur->m_arcArray.Add(x + radius);
	m_pArcCur->m_arcArray.Add(y);
	m_pArcCur->m_iPenR = R;
	m_pArcCur->m_iPenG = G;
	m_pArcCur->m_iPenB = B;

//	Then transform to scroll position
	CPoint sPos = GetScrollPosition();
	TransformToScrollPos(sPos.x, sPos.y, &x, &y );

	pcDC.Arc(
	x - radius, y - radius,
	x + radius, y + radius,
	x + radius, y,
	x + radius, y);

	pcDC.SelectObject(pOldPen);
	penNew.DeleteObject();
}

void CPlanetsView::MakeEllipse(int x1, int y1, int x2, int y2,
							   UINT fill, int R, int G, int B)
{
	CBrush pBrush;
	LOGBRUSH logBrush;
    CClientDC pcDC(this);
	CPen penNew;
	CPen* pOldPen;

	penNew.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(R, G, B));

//	Make and select brush
	logBrush.lbStyle = fill;
	logBrush.lbColor = RGB(R, G, B);
	logBrush.lbHatch = HS_CROSS;
	pBrush.CreateBrushIndirect(&logBrush);

	pOldPen = pcDC.SelectObject(&penNew);
	CBrush* pOldBrush = (CBrush*)pcDC.SelectObject(&pBrush);
	pcDC.SetMapMode(MM_LOENGLISH);

//	First save coordinates of points
	m_pEllipseCur = GetDocument()->NewEllipse(fill);
	m_pEllipseCur->m_ellipseArray.Add(x1);
	m_pEllipseCur->m_ellipseArray.Add(y1);
	m_pEllipseCur->m_ellipseArray.Add(x2);
	m_pEllipseCur->m_ellipseArray.Add(y2);
	m_pEllipseCur->m_iPenR = R;
	m_pEllipseCur->m_iPenG = G;
	m_pEllipseCur->m_iPenB = B;

//	Then transform to scroll position
	CPoint sPos = GetScrollPosition();
	TransformToScrollPos(sPos.x, sPos.y, &x1, &y1 );
	TransformToScrollPos(sPos.x, sPos.y, &x2, &y2 );
	
	pcDC.Ellipse(x1, y1, x2, y2);

	pcDC.SelectObject(pOldPen);
	pcDC.SelectObject(pOldBrush);

	penNew.DeleteObject();
	pOldBrush->DeleteObject();

}

//	Given angle, and pointer to font, make font.  Makes font with point
//	size as selected from toolbar, style is Arial with adjustable angle
void CPlanetsView::MakeFont(double angle, CFont* font, struct fontAttributes* nFont)
{
	CWinApp* pApp = AfxGetApp();
	convert Convert;
	int textAngle;
	CString sFontString;
	int iCurSel, iFontSize;

	CMainFrame* pFrame = (CMainFrame*)pApp->m_pMainWnd;
	iCurSel = pFrame->m_comboBox.GetCurSel();
	pFrame->m_comboBox.GetLBText(iCurSel,sFontString);
	iFontSize = _tstoi(sFontString);

	textAngle = (int)(angle * (double)10 * (double)180 / Convert.Pi());

	VERIFY(font->CreateFont(
	iFontSize ,                // nHeight
	0,                         // nWidth
	textAngle,                 // nEscapement
	0,                         // nOrientation
	FW_NORMAL,                 // nWeight
	FALSE,                     // bItalic
	FALSE,                     // bUnderline
	0,                         // cStrikeOut
	ANSI_CHARSET,              // nCharSet
	OUT_DEFAULT_PRECIS,        // nOutPrecision
	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	DEFAULT_QUALITY,           // nQuality
	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	LPCTSTR ("Arial")));                 // lpszFacename

	nFont->nHeight = iFontSize;
	nFont->nWidth = 0;
	nFont->nEscapement = textAngle;
	nFont->nOrientation = 0;
	nFont->nWeight = FW_NORMAL;
	nFont->bItalic = FALSE;
	nFont->bUnderline = FALSE;
	nFont->cStrikeOut = 0;
	nFont->nCharSet = ANSI_CHARSET;
	nFont->nOutPrecision = OUT_DEFAULT_PRECIS;
	nFont->nClipPrecision = CLIP_DEFAULT_PRECIS;
	nFont->nQuality = DEFAULT_QUALITY;
	nFont->nPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	nFont->lpszFacename = LPCTSTR ("Arial");

}

void CPlanetsView::GetTextLocation(CPoint origin, CPoint body, CPoint* text, double location)
{
	text->x = (long)((body.x - origin.x) * location + origin.x);
	text->y = (long)((body.y - origin.y) * location + origin.y);
}

//	Given an angle to print the text at, lambda, set the print
//	angle, textAngle, so that text is mostly upright.  Without 
//	this adjustment, text at left horizontal would be upside down
void CPlanetsView::SetTextAngle(double lambda, double& textAngle)
{
	convert Convert;
	double m_Pi;
	m_Pi = Convert.Pi();

	if(lambda > m_Pi / (double)2 && lambda < m_Pi * 1.5)
	{
		textAngle = Convert.radianReduce(lambda + m_Pi);
	}
	else
	{
		textAngle = lambda;
	}
}

//	Draws aspect symbol at location pPoint
void CPlanetsView::MakeAspect(int type, CPoint pPoint)
{
	CClientDC pcDC(this);

	CPoint pPoint2;
	int radius, length;

	radius = 3;
	length = 6;

	CPen penNew;
	CPen* pOldPen;

	penNew.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(0, 0, 0));
	pOldPen = pcDC.SelectObject(&penNew);

	pcDC.SetMapMode(MM_LOENGLISH);

	switch ( type )
	{
	case 1:
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x + 5;
		pPoint2.y = pPoint.y;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x;
		pPoint2.y = pPoint.y + (2 * length);
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		radius = 4;
		pcDC.Arc(
		pPoint2.x - radius, pPoint2.y,
		pPoint2.x + radius, pPoint2.y - (2 * radius),
		pPoint2.x, pPoint2.y - (2 * radius),
		pPoint2.x, pPoint2.y);
		
		m_pArcCur = GetDocument()->NewArc();
		m_pArcCur->m_arcArray.Add(pPoint2.x - radius);
		m_pArcCur->m_arcArray.Add(pPoint2.y);
		m_pArcCur->m_arcArray.Add(pPoint2.x + radius);
		m_pArcCur->m_arcArray.Add(pPoint2.y - (2 * radius));
		m_pArcCur->m_arcArray.Add(pPoint2.x);
		m_pArcCur->m_arcArray.Add(pPoint2.y - (2 * radius));
		m_pArcCur->m_arcArray.Add(pPoint2.x);
		m_pArcCur->m_arcArray.Add(pPoint2.y);
		break;
	case 2:
		pPoint.x += 2;
		CPlanetsView::MakeCircle(pPoint.x, pPoint.y, radius, 0, 0, 0);
		pPoint.x += 2;
		pPoint.y += 2;
		pcDC.MoveTo(pPoint);

		pPoint2.x = pPoint.x + length;
		pPoint2.y = pPoint.y + length;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;
		break;
	case 3:
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x + (2 * length);
		pPoint2.y = pPoint.y;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pPoint.x += 6;
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x - 5;
		pPoint2.y = pPoint.y + 5;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x + 5;
		pPoint2.y = pPoint.y + 5;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;
		break;
	case 4:
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x + (2 * length);
		pPoint2.y = pPoint.y;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x;
		pPoint2.y = pPoint.y + (2 * length);
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;
		break;
	case 5:
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x + (2 * length);
		pPoint2.y = pPoint.y + (2 * length);
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pPoint.x += 6;
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x;
		pPoint2.y = pPoint.y + (2 * length);
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pPoint.x += 6;
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x - (2 * length);
		pPoint2.y = pPoint.y + (2 * length);
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pPoint.y += 6;
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x - (2 * length);
		pPoint2.y = pPoint.y;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;
		break;
	case 6:
		pPoint.y += 9;
		pPoint.x += 3;
		CPlanetsView::PrintName(pPoint, 0, "Q", 0, 0, 0);
		break;
	case 7:
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x + (2 * length);
		pPoint2.y = pPoint.y;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x;
		pPoint2.y = pPoint.y + (2 * length);
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pPoint.x += (2 * length);
		pPoint.y += (2 * length);
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x - (2 * length);
		pPoint2.y = pPoint.y;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x;
		pPoint2.y = pPoint.y - (2 * length);
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;
		break;
	case 8:
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x + (2 * length);
		pPoint2.y = pPoint.y;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pPoint2.x = pPoint.x + (length);
		pPoint2.y = pPoint.y + (7);
		pcDC.MoveTo(pPoint2);
		pcDC.LineTo(pPoint);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pPoint.x += 12;
		pcDC.MoveTo(pPoint2);
		pcDC.LineTo(pPoint);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;
		break;
	case 9:
		pPoint.y +=5;
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x + (2 * length);
		pPoint2.y = pPoint.y;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pPoint.x += 6;
		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x - 5;
		pPoint2.y = pPoint.y - 5;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pcDC.MoveTo(pPoint);
		pPoint2.x = pPoint.x + 5;
		pPoint2.y = pPoint.y - 5;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;
		break;
	case 10:
		pPoint.x += 2;
		CPlanetsView::MakeCircle(pPoint.x, pPoint.y, radius, 0, 0, 0);
		pPoint.x += 2;
		pPoint.y += 2;
		pcDC.MoveTo(pPoint);

		pPoint2.x = pPoint.x + length;
		pPoint2.y = pPoint.y + length;
		pcDC.LineTo(pPoint2);

		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(pPoint);
		m_pStrokeCur->m_pointArray.Add(pPoint2);
		m_pStrokeCur->m_iPenR = 0;
		m_pStrokeCur->m_iPenG = 0;
		m_pStrokeCur->m_iPenB = 0;

		pPoint.x += 9;
		pPoint.y += 7;
		CPlanetsView::MakeCircle(pPoint.x, pPoint.y, radius, 0, 0, 0);

		break;
	}
	pcDC.SelectObject(pOldPen);
	penNew.DeleteObject();
}


void CPlanetsView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 850;
	sizeTotal.cy = 1100;
	SetScrollSizes(MM_LOENGLISH, sizeTotal);
   // Create the CPPToolTip object

	m_toolTipList.SetSize(0, 20);

	m_tooltip.Create(this);
	m_tooltip.SetNotify();
	CRect rec;
	rec.left = rec.right = rec.top = rec.bottom = 0;

	PPTOOLTIP_INFO ti;
	ti.nBehaviour = PPTOOLTIP_MULTIPLE_SHOW || PPTOOLTIP_NOCLOSE_OVER;
	ti.nIDTool = 0;
	ti.rectBounds = rec;
	ti.sTooltip = "";
	ti.nMask = PPTOOLTIP_MASK_BEHAVIOUR;

	m_tooltip.AddTool(this, ti);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL,10);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP,10000);

}

/////////////////////////////////////////////////////////////////////////////
// CPlanetsView printing

BOOL CPlanetsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanetsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanetsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPlanetsView diagnostics

#ifdef _DEBUG
void CPlanetsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPlanetsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CPlanetsDoc* CPlanetsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanetsDoc)));
	return (CPlanetsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPlanetsView message handlers

BOOL CPlanetsView::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CScrollView::OnHelpInfo(pHelpInfo);
}

void CPlanetsView::OnHelpFinder() 
{
	CString msg;
	HWND pHwnd;
	// LS 20190213 buffer overflow warning
	char buffer[300];
	CString URL;
	CString tempURL;
	DWORD nSize = 150;

	pHwnd = this->GetSafeHwnd();

	GetModuleFileName(NULL, LPWSTR (buffer), nSize);
	tempURL = buffer;
	URL = tempURL.Left(1 + tempURL.ReverseFind(_T('\\')));// remove "Planets.exe" from string
	URL   += _T("Planets.chm::/htm/helpcontents1.htm");

	if( !::HtmlHelp( pHwnd, URL, HH_DISPLAY_TOPIC, 0 ))
	{
        ::AfxFormatString1( msg, IDS_HELP_URL_NOT_FOUND, URL ) ;
		::AfxMessageBox( msg ) ;
    }	
}

//	First try to find if cursor is over circle.  If so try to rotate.
//	Then see if over text, if so, try to move.
void CPlanetsView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int left, right, top, bottom;
	POSITION textPos;

	m_bFoundText   = false;
	m_bFoundStroke = false;
	m_bFoundCircle = false;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	int disX = point.x - m_iHorCir.x;
	int disY = point.y - m_iHorCir.y;

	class CPlanetsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(fabs(sqrt((disX * disX) + (disY * disY)) - m_iHorCirRadius) < 3)
	{
		m_bFoundCircle = true;
		m_pStartRotate.x = point.x;
		m_pStartRotate.y = point.y;
		goto exit;
	}
	
	textPos = pDoc->m_textList.GetTailPosition();
	while (		textPos != NULL
			&&
				m_bFoundText == false)
	{
		CText* pText = pDoc->m_textList.GetPrev(textPos);

		left = pText->m_pTextLocation.x;
		right = left + pText->m_width;
		top = pText->m_pTextLocation.y;
		bottom = top - pText->m_height;

		if(		point.x > left
			&&
				point.x < right
			&&
				point.y < top
			&&
				point.y > bottom	)
		{
			m_moveText = pText;
		//	Find distance between cursor and text anchor point
			m_xDist = point.x - pText->m_pTextLocation.x;
			m_yDist = point.y - pText->m_pTextLocation.y;
			m_bFoundText = true;
		}
	}
exit:
	if(m_bFoundText || m_bFoundStroke || m_bFoundCircle)SetCapture();
	CScrollView::OnLButtonDown(nFlags, point);
}

void CPlanetsView::OnMouseMove(UINT nFlags, CPoint point) 
{
	convert Convert;
	CWnd* pView = (CWnd*) this ;

	CPoint mP;
	mP.x = point.x;
	mP.y = point.y;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	if (GetCapture() != this)
		return; // If this window (view) didn't capture the mouse,
				// then the user isn't drawing in this window.
	CPoint pOrigPt;
	int offset;

	offset = 20;

	if(m_bFoundCircle)
	{
		double lStart, b, r, lEnd, deltaAngle;

		ShowWorking(SW_SHOW);

		Convert.cartesianToSpherical(m_pStartRotate.x - m_iHorCir.x, m_pStartRotate.y - m_iHorCir.y, 0,
								 lStart, b, r);
		Convert.cartesianToSpherical(point.x - m_iHorCir.x, point.y - m_iHorCir.y, 0,
								 lEnd, b, r);
		m_pStartRotate.x = point.x;
		m_pStartRotate.y = point.y;
		deltaAngle = lStart - lEnd;

		class CPlanetsDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->EraseContents();

		// First change view direction
		m_cDisplayControl->m_dViewDirection += deltaAngle;

		// then adjust to keep between 0 and 360
		if (m_cDisplayControl->m_dViewDirection < 0)
		{
			m_cDisplayControl->m_dViewDirection += (2*Convert.Pi());
		}
	
		if (m_cDisplayControl->m_dViewDirection > (2*Convert.Pi()))
		{
			m_cDisplayControl->m_dViewDirection -= (2*Convert.Pi());
		}
	
		// now update display control box
		m_cDisplayControl->UpdateViewDirection(m_cDisplayControl->m_dViewDirection);
		DrawStars();
		InvalidateRect(NULL, true);
		OnPaint();
		ShowWorking(SW_HIDE);
	}

	if(m_bFoundText || m_bFoundStroke)
	{
		class CPlanetsDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		CPoint newPos;
		newPos.x = point.x - m_xDist;
		newPos.y = point.y - m_yDist;
//		This leaves a blue tracer below the green tracer when the 
//		view is moved down, so take it out.
//		MakePointer(m_moveText->m_pTextOrig, newPos, 0, 0, 255);

		CRect redrawRect;
		pOrigPt.x = m_moveText->m_pTextOrig.x;
		pOrigPt.y = m_moveText->m_pTextOrig.y;
		dc.LPtoDP(&pOrigPt);
		if(newPos.x < m_moveText->m_pTextOrig.x)
		{
			if(newPos.y < m_moveText->m_pTextOrig.y)
			{//Lower Left
				int t;
				t = mP.x - m_xDist + m_moveText->m_width;

				redrawRect.left = mP.x - m_xDist - offset;
				redrawRect.top = pOrigPt.y - offset;
				redrawRect.right = pOrigPt.x < t ? t + offset : pOrigPt.x + offset;
				redrawRect.bottom = mP.y + m_yDist + m_moveText->m_height + offset;
			}
			else
			{//Upper Left
				int right;
				int bottom;
				bottom = mP.y + m_yDist + m_moveText->m_height;
				right = mP.x - m_xDist + m_moveText->m_width;

				redrawRect.left = mP.x - m_xDist - offset;
				redrawRect.top = mP.y + m_yDist - offset;
				redrawRect.right = pOrigPt.x < right ? right + offset : pOrigPt.x + offset;
				redrawRect.bottom = pOrigPt.y < bottom ? bottom + offset : pOrigPt.y + offset;
			}
		}
		else
		{
			if(newPos.y < m_moveText->m_pTextOrig.y)
			{//Lower Right
				redrawRect.left = pOrigPt.x - offset;
				redrawRect.top = pOrigPt.y - offset;
				redrawRect.right = mP.x - m_xDist + m_moveText->m_width + offset;
 				redrawRect.bottom = mP.y + m_yDist + m_moveText->m_height + offset;
			}
			else
			{//Upper Right
				int t;
				t = mP.y + m_yDist + m_moveText->m_height;

				redrawRect.left = pOrigPt.x - offset;
				redrawRect.top = mP.y + m_yDist - offset;
				redrawRect.right = mP.x - m_xDist + m_moveText->m_width + offset;
				redrawRect.bottom = pOrigPt.y < t ? t + offset : pOrigPt.y + offset;
			}
		}

	//calculate new position of text
		m_moveText->m_pTextLocation.x = point.x - m_xDist;
		m_moveText->m_pTextLocation.y = point.y - m_yDist;
	//	Draw line from original location to new location
	//redraw
		InvalidateRect(redrawRect, true);
		OnDraw(&dc);
	}

	CScrollView::OnMouseMove(nFlags, point);
}

void CPlanetsView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	convert Convert;

	ReleaseCapture();   // Release the mouse capture established at

	if(m_bFoundCircle)
	{
		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DPtoLP(&point);

		double lStart, b, r, lEnd, deltaAngle;

		ShowWorking(SW_SHOW);
		Convert.cartesianToSpherical(m_pStartRotate.x - m_iHorCir.x, m_pStartRotate.y - m_iHorCir.y, 0,
								 lStart, b, r);
		Convert.cartesianToSpherical(point.x - m_iHorCir.x, point.y - m_iHorCir.y, 0,
								 lEnd, b, r);
		deltaAngle = lStart - lEnd;

		class CPlanetsDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->EraseContents();

		// First change view direction
 		m_cDisplayControl->m_dViewDirection += deltaAngle;

		// then adjust to keep between 0 and 360
		if (m_cDisplayControl->m_dViewDirection < 0)
		{
			m_cDisplayControl->m_dViewDirection += (2*Convert.Pi());
		}
	
		if (m_cDisplayControl->m_dViewDirection > (2*Convert.Pi()))
		{
			m_cDisplayControl->m_dViewDirection -= (2*Convert.Pi());
		}
	
		// now update display control box
		m_cDisplayControl->UpdateViewDirection(m_cDisplayControl->m_dViewDirection);

	//	Need to remove tooltips
		m_toolTipList.RemoveAll();
		DrawStars();
		m_bFoundCircle = false;
		InvalidateRect(NULL, true);
		OnPaint();
		ShowWorking(SW_HIDE);
	}
	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CPlanetsView::OnFontSize()
{
	POSITION textPos;
	CWinApp* pApp = AfxGetApp();
	CString sFontString;
	int iCurSel, iFontSize;

	CMainFrame* pFrame = (CMainFrame*)pApp->m_pMainWnd;
	iCurSel = pFrame->m_comboBox.GetCurSel();
	pFrame->m_comboBox.GetLBText(iCurSel,sFontString);
//	iFontSize = atoi(sFontString);
	iFontSize = _tstoi(sFontString);

	class CPlanetsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	textPos = pDoc->m_textList.GetHeadPosition();
	while (		textPos != NULL )
	{
		CText* pText = pDoc->m_textList.GetNext(textPos);
		pText->m_font.nHeight = iFontSize;
	}

	InvalidateRect(NULL, true);
	OnPaint();
	pApp->WriteProfileInt(_T ("Toolbar"), _T ("fontposition"), iCurSel);
}

BOOL CPlanetsView::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);	
	return CScrollView::PreTranslateMessage(pMsg);
}

bool CPlanetsView::PointInRect(CRect rec, CPoint pt)
{
	int ptX = pt.x;
	int ptY = pt.y;

	if(		ptX >= rec.left
		&&
			ptX < rec.right
		&&
			ptY <= rec.top
		&&
			ptY > rec.bottom )
		return true;
	return false;
}

CString CPlanetsView::MakeTipText(struct toolTipData data)
{
	CString text;
	CString br;
	br = "<br>";

	switch (data.type)
	{
	case STAR:
		text = data.name + br +
			   data.constellation + br +
			   "azimuth = " + data.azimuth + br +
			   "altitude = " + data.altitude + br +
			   "magnitude = " + data.magnitude;
		break;
	case PLANET:
		text = data.name + br +
			   "azimuth = " + data.azimuth + br +
			   "altitude = " + data.altitude;
	}
	return text;
}

void CPlanetsView::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
	*result = 0;
	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;

	if (	pNotify->ti->nIDTool == 0
		 &&
			STAR_VIEW == m_uViewType)
	{
		CPoint pt = *pNotify->pt;
		ScreenToClient(&pt);

		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DPtoLP(&pt);

		int disX = pt.x - m_iHorCir.x;
		int disY = pt.y - m_iHorCir.y;

	//	You are on Horizon Circle
		if(fabs(sqrt((disX * disX) + (disY * disY)) - m_iHorCirRadius) < 3)
		{
			pNotify->ti->sTooltip = "Horizon Circle";
		}
		else// look for star or planet
		{
			struct toolTipData tData;
			int iSize = (int)m_toolTipList.GetSize();
			CRect rec;

			for(int i=0; i<iSize; i++)
			{
				tData = m_toolTipList.GetAt(i);
				rec = tData.rect;
				if(PointInRect(rec, pt) )
				{
					CString text = CPlanetsView::MakeTipText(tData);
					pNotify->ti->sTooltip = text;

					return;
				}
			}
		}
	} //if
} //End NotifyDisplayTooltip


//void CPlanetsView::OnClose()
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CScrollView::OnClose();
//}


//void CPlanetsView::OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CScrollView::OnDeleteItem(nIDCtl, lpDeleteItemStruct);
//}


//void CPlanetsView::OnFileClose()
//{
//	int j = 3;
//	// TODO: Add your command handler code here
//}


//void CPlanetsView::OnIdclose()
//{
//	int g = 4;
//	// TODO: Add your command handler code here
//}
