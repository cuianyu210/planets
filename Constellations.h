#if !defined(AFX_CONSTELLATIONS_H__A7C99BD9_6C8F_4490_83FE_0E0C372AF10F__INCLUDED_)
#define AFX_CONSTELLATIONS_H__A7C99BD9_6C8F_4490_83FE_0E0C372AF10F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Constellations.h : header file
//
#include "PlanetsView.h"

/////////////////////////////////////////////////////////////////////////////
// CConstellations window

class CConstellations : public CWnd
{
// Construction
public:
	CConstellations();

// Attributes
public:

// Operations
public:

	void MakeAll(CPlanetsView *pPlanetsView,
				 double allAltitude[],
				 CPoint conPoints[],
				 double realConPointXs[],
				 double realConPointYs[],
				 int circleRadius,
				 CPoint Origin,
				 int iConNames,
				 int R,
				 int G,
				 int B);// iConNames = 0 no names, 1 names
	void MakeList(CPlanetsView *pPlanetsView,
				 double altitude[],
				 CPoint conPoints[],
				 double realConPointXs[],
				 double realConPointYs[],
				 int circleRadius,
				 CPoint Origin,
				 CArray<int, int> *iConst,
				 int iConNames,
				 int R,
				 int G,
				 int B);
	void MakeSingle(CPlanetsView *pPlanetsView,
					double altitude[],
					CPoint pPoints[],
					double realSingleX[],
					double realSingleY[],
					int iWhich,
					int cirRadius,
					CPoint Origin,
					int iSize,
					int iConNames,
					int R,
					int G,
					int B);
	int LoadSingleArray(CPoint conPoints[],
						 CPoint singlePoints[],
						 double altitude[],
						 double constAltitude[],
						 double realConPointXs[],
						 double realConPointYs[],
						 double realSingleX[],
						 double realSingleY[],
						 int iConst);
	int LoadSingleArray(CString names[],
						CString singleNames[],
						int iConst);
	int LoadSingleArray(double inArray[],
						double outArray[],
						int iConst);
	int EvaluateArray(double altitude[], int iSize);
	int EvaluatePair(double dPoint1, double dPoint2);
	void FindIntersection(int radius, CPoint origin, double alt1,
						  CPoint p1, CPoint p2,
						  double realX1, double realY1,
						  double realX2, double realY2,
						  CPoint &pFirst, CPoint &pSecond);
	void DrawLine(CPlanetsView *pPlanetsView,
				  int first, int second, double altitude[],
				  CPoint pPoints[],
				  int radius,
				  CPoint origin,
				  int R, int G, int B, double realSingleX[], double realSingleY[]);
	double FindMiddleValue(double x1, double x2,
						   double value1, double value2);
	int FindHighestAltitude(double altitude[], int iSize);

int Andromeda(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Antlia(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Apus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Aquarius(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Aquila(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Ara(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Aries(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Auriga(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Bootes(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Caelum(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Camelopardalis(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Cancer(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int CanesVenatici(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int CanisMajor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int CanisMinor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Capricornus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Carina(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Cassiopeia(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Centaurus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Cepheus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Cetus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Chamaleon(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Circinus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Columba(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int ComaBerenices(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int CoronaAustralis(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int CoronaBorealis(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Corvus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Crater(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Crux(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Cygnus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Delphinus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Dorado(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Draco(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Equuleus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Eridanus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Fornax(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Gemini(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Grus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Hercules(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Horologium(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Hydra(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Hydrus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Indus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Lacerta(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Leo(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int LeoMinor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Lepus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Libra(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Lupus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Lynx(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Lyra(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Mensa(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Microscopium(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Monoceros(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Musca(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Norma(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Octans(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Ophiucus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Orion(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Pavo(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Pegasus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Perseus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Phoenix(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Pictor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Pisces(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int PiscesAustrinus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Puppis(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Pyxis(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Reticulum(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Sagitta(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Sagittarius(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Scorpius(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Sculptor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Scutum(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Serpens(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Sextans(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Taurus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Telescopium(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Triangulum(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int TriangulumAustrale(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Tucana(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int UrsaMajor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int UrsaMinor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Vela(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Virgo(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Volans(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);
int Vulpecula(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[]);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstellations)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConstellations();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConstellations)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTELLATIONS_H__A7C99BD9_6C8F_4490_83FE_0E0C372AF10F__INCLUDED_)
