// Constellations.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include <math.h>
#include "Constellations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConstellations

CConstellations::CConstellations()
{
//	m_NullPoint.x = -999;
//	m_NullPoint.y = -999;
}

CConstellations::~CConstellations()
{
}


BEGIN_MESSAGE_MAP(CConstellations, CWnd)
	//{{AFX_MSG_MAP(CConstellations)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CConstellations message handlers

void CConstellations::MakeAll(CPlanetsView *pPlanetsView,
							  double allAltitude[],
							  CPoint allPoints[],
							  double allRealPointXs[],
							  double allRealPointYs[],
							  int circleRadius,
							  CPoint Origin,
							  int iConNames,
							  int R,
							  int G,
							  int B)
{
	CPoint singlePoint[28];//holds point data for each constellation
	double singleAltitude[28];//holds altitude data for each constellation
	double singleRealX[28];
	double singleRealY[28];
	int i, iArraySize;

//	Load singleCon with appropriate data
	for(i=0; i<88; i++)
	{
		iArraySize = CConstellations::LoadSingleArray(allPoints, singlePoint,
													  allAltitude,singleAltitude,
													  allRealPointXs,
													  allRealPointYs,
													  singleRealX,
													  singleRealY,
													  i);
		CConstellations::MakeSingle(pPlanetsView, singleAltitude, singlePoint,
									singleRealX, singleRealY, i,
									circleRadius, Origin, iArraySize, iConNames,
									R, G, B);
	}
}

void CConstellations::MakeList(CPlanetsView *pPlanetsView,
							  double allAltitude[],
							  CPoint allPoints[],
							  double allRealPointXs[],
							  double allRealPointYs[],
							  int circleRadius,
							  CPoint Origin,
							  CArray<int, int> *iConst,
							  int iConNames,
							  int R,
							  int G,
							  int B)
{
	CPoint singlePoint[28];//holds point data for each constellation
	double singleAltitude[28];//holds altitude data for each constellation
	int i, iArraySize, iWhichCon;
	double singleRealX[28];
	double singleRealY[28];

//	Load singleCon with appropriate data
	for(i=0; i<iConst->GetSize(); i++)
	{
		iWhichCon = iConst->GetAt(i) - 1;
		iArraySize = CConstellations::LoadSingleArray(allPoints, singlePoint,
													  allAltitude,singleAltitude,
													  allRealPointXs,
													  allRealPointYs,
													  singleRealX,
													  singleRealY,
													  iWhichCon);
		CConstellations::MakeSingle(pPlanetsView, singleAltitude, singlePoint, singleRealX,
									singleRealY, iWhichCon,
									circleRadius, Origin, iArraySize, iConNames,
									R, G, B);
	}
}

void CConstellations::MakeSingle(CPlanetsView *pPlanetsView,
								 double singleAltitude[],
								 CPoint singlePoints[],
								 double singleRealX[],
								 double singleRealY[],
								 int iWhich,
								 int cirRadius,
								 CPoint Origin,
								 int iSize,
								 int iConNames,
								 int R,
								 int G,
								 int B)
{
	CString sName;
	CPoint pPoint;
	int iType, highAlt;

	switch(iWhich)
	{

case 0:
iType = CConstellations::Andromeda(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Andromeda";
break;
case 1:
iType = CConstellations::Antlia(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Antlia";
break;
case 2:
iType = CConstellations::Apus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Apus";
break;
case 3:
iType = CConstellations::Aquarius(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Aquarius";
break;
case 4:
iType = CConstellations::Aquila(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Aquila";
break;
case 5:
iType = CConstellations::Ara(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Ara";
break;
case 6:
iType = CConstellations::Aries(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Aries";
break;
case 7:
iType = CConstellations::Auriga(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Auriga";
break;
case 8:
iType = CConstellations::Bootes(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Bootes";
break;
case 9:
iType = CConstellations::Caelum(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Caelum";
break;
case 10:
iType = CConstellations::Camelopardalis(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Camelopardalis";
break;
case 11:
iType = CConstellations::Cancer(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Cancer";
break;
case 12:
iType = CConstellations::CanesVenatici(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "CanesVenatici";
break;
case 13:
iType = CConstellations::CanisMajor(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "CanisMajor";
break;
case 14:
iType = CConstellations::CanisMinor(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "CanisMinor";
break;
case 15:
iType = CConstellations::Capricornus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Capricornus";
break;
case 16:
iType = CConstellations::Carina(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Carina";
break;
case 17:
iType = CConstellations::Cassiopeia(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Cassiopeia";
break;
case 18:
iType = CConstellations::Centaurus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Centaurus";
break;
case 19:
iType = CConstellations::Cepheus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Cepheus";
break;
case 20:
iType = CConstellations::Cetus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Cetus";
break;
case 21:
iType = CConstellations::Chamaleon(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Chamaleon";
break;
case 22:
iType = CConstellations::Circinus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Circinus";
break;
case 23:
iType = CConstellations::Columba(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Columba";
break;
case 24:
iType = CConstellations::ComaBerenices(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "ComaBerenices";
break;
case 25:
iType = CConstellations::CoronaAustralis(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "CoronaAustralis";
break;
case 26:
iType = CConstellations::CoronaBorealis(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "CoronaBorealis";
break;
case 27:
iType = CConstellations::Corvus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Corvus";
break;
case 28:
iType = CConstellations::Crater(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Crater";
break;
case 29:
iType = CConstellations::Crux(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Crux";
break;
case 30:
iType = CConstellations::Cygnus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Cygnus";
break;
case 31:
iType = CConstellations::Delphinus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Delphinus";
break;
case 32:
iType = CConstellations::Dorado(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Dorado";
break;
case 33:
iType = CConstellations::Draco(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Draco";
break;
case 34:
iType = CConstellations::Equuleus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Equuleus";
break;
case 35:
iType = CConstellations::Eridanus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Eridanus";
break;
case 36:
iType = CConstellations::Fornax(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Fornax";
break;
case 37:
iType = CConstellations::Gemini(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Gemini";
break;
case 38:
iType = CConstellations::Grus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Grus";
break;
case 39:
iType = CConstellations::Hercules(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Hercules";
break;
case 40:
iType = CConstellations::Horologium(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Horologium";
break;
case 41:
iType = CConstellations::Hydra(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Hydra";
break;
case 42:
iType = CConstellations::Hydrus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Hydrus";
break;
case 43:
iType = CConstellations::Indus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Indus";
break;
case 44:
iType = CConstellations::Lacerta(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Lacerta";
break;
case 45:
iType = CConstellations::Leo(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Leo";
break;
case 46:
iType = CConstellations::LeoMinor(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "LeoMinor";
break;
case 47:
iType = CConstellations::Lepus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Lepus";
break;
case 48:
iType = CConstellations::Libra(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Libra";
break;
case 49:
iType = CConstellations::Lupus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Lupus";
break;
case 50:
iType = CConstellations::Lynx(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Lynx";
break;
case 51:
iType = CConstellations::Lyra(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Lyra";
break;
case 52:
iType = CConstellations::Mensa(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Mensa";
break;
case 53:
iType = CConstellations::Microscopium(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Microscopium";
break;
case 54:
iType = CConstellations::Monoceros(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Monoceros";
break;
case 55:
iType = CConstellations::Musca(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Musca";
break;
case 56:
iType = CConstellations::Norma(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Norma";
break;
case 57:
iType = CConstellations::Octans(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Octans";
break;
case 58:
iType = CConstellations::Ophiucus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Ophiucus";
break;
case 59:
iType = CConstellations::Orion(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Orion";
break;
case 60:
iType = CConstellations::Pavo(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Pavo";
break;
case 61:
iType = CConstellations::Pegasus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Pegasus";
break;
case 62:
iType = CConstellations::Perseus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Perseus";
break;
case 63:
iType = CConstellations::Phoenix(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Phoenix";
break;
case 64:
iType = CConstellations::Pictor(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Pictor";
break;
case 65:
iType = CConstellations::Pisces(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Pisces";
break;
case 66:
iType = CConstellations::PiscesAustrinus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "PiscesAustrinus";
break;
case 67:
iType = CConstellations::Puppis(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Puppis";
break;
case 68:
iType = CConstellations::Pyxis(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Pyxis";
break;
case 69:
iType = CConstellations::Reticulum(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Reticulum";
break;
case 70:
iType = CConstellations::Sagitta(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Sagitta";
break;
case 71:
iType = CConstellations::Sagittarius(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Sagittarius";
break;
case 72:
iType = CConstellations::Scorpius(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Scorpius";
break;
case 73:
iType = CConstellations::Sculptor(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Sculptor";
break;
case 74:
iType = CConstellations::Scutum(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Scutum";
break;
case 75:
iType = CConstellations::Serpens(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Serpens";
break;
case 76:
iType = CConstellations::Sextans(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Sextans";
break;
case 77:
iType = CConstellations::Taurus(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Taurus";
break;
case 78:
iType = CConstellations::Telescopium(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Telescopium";
break;
case 79:
iType = CConstellations::Triangulum(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Triangulum";
break;
case 80:
iType = CConstellations::TriangulumAustrale(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "TriangulumAustrale";
break;
case 81:
iType = CConstellations::Tucana(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Tucana";
break;
case 82:
iType = CConstellations::UrsaMajor(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "UrsaMajor";
break;
case 83:
iType = CConstellations::UrsaMinor(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "UrsaMinor";
break;
case 84:
iType = CConstellations::Vela(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Vela";
break;
case 85:
iType = CConstellations::Virgo(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Virgo";
break;
case 86:
iType = CConstellations::Volans(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Volans";
break;
case 87:
iType = CConstellations::Vulpecula(pPlanetsView, singleAltitude, singlePoints, cirRadius, Origin, iSize, iConNames, R, G, B, singleRealX, singleRealY);
sName = "Vulpecula";
break;
}

if(iConNames == 1)
{
	if(iType != 3)
	{
		if(iType == 1)pPoint = singlePoints[1];
		if(iType == 2)
		{
			highAlt = CConstellations::FindHighestAltitude(singleAltitude, iSize);
			pPoint = singlePoints[highAlt];
		}
		pPlanetsView->PrintName(pPoint, 0, sName, 0, 0, 255);
	}
}

}

int CConstellations::LoadSingleArray(CPoint allPoints[],
									 CPoint singlePoints[],
									 double allAltitude[],
									 double singleAltitude[],
									 double allRealPointXs[],
									 double allRealPointYs[],
									 double singleRealX[],
									 double singleRealY[],
									 int iConst)
{
	int i, A, B, iSize, j;

	switch(iConst)
	{
	case 0://and
		A = 0;
		B = 9;
		break;
	case 1://ant
		A = 9;
		B = 12;
		break;
	case 2://aps
		A = 12;
		B = 16;
		break;
	case 3://aqr
		A = 16;
		B = 35;
		break;
	case 4://aql
		A = 35;
		B = 46;
		break;
	case 5://ara
		A = 46;
		B = 54;
		break;
	case 6://ari
		A = 54;
		B = 58;
		break;
	case 7://aur
		A = 58;
		B = 66;
		break;
	case 8://boo
		A = 66;
		B = 78;
		break;
	case 9://cae
		A = 78;
		B = 82;
		break;
	case 10://cam
		A = 82;
		B = 88;
		break;
	case 11://cnc
		A = 88;
		B = 93;
		break;
	case 12://cvn
		A = 93;
		B = 96;
		break;
	case 13://cma
		A = 96;
		B = 106;
		break;
	case 14://cmi
		A = 106;
		B = 108;
		break;
	case 15://cap
		A = 108;
		B = 122;
		break;
	case 16://car
		A = 122;
		B = 132;
		break;
	case 17://cas
		A = 132;
		B = 137;
		break;
	case 18://cen
		A = 137;
		B = 149;
		break;
	case 19://cep
		A = 149;
		B = 154;
		break;
	case 20://cet
		A = 154;
		B = 170;
		break;
	case 21://cha
		A = 170;
		B = 175;
		break;
	case 22://cir
		A = 175;
		B = 178;
		break;
	case 23://col
		A = 178;
		B = 184;
		break;
	case 24://com
		A = 184;
		B = 187;
		break;
	case 25://cra
		A = 187;
		B = 195;
		break;
	case 26://crb
		A = 195;
		B = 202;
		break;
	case 27://crv
		A = 202;
		B = 207;
		break;
	case 28://crt
		A = 207;
		B = 216;
		break;
	case 29://cru
		A = 216;
		B = 220;
		break;
	case 30://cyg
		A = 220;
		B = 226;
		break;
	case 31://del
		A = 226;
		B = 231;
		break;
	case 32://dor
		A = 231;
		B = 235;
		break;
	case 33://dra
		A = 235;
		B = 254;
		break;
	case 34://equ
		A = 254;
		B = 257;
		break;
	case 35://eri
		A = 257;
		B = 285;
		break;
	case 36://for
		A = 285;
		B = 289;
		break;
	case 37://gem
		A = 289;
		B = 299;
		break;
	case 38://gru
		A = 299;
		B = 309;
		break;
	case 39://her
		A = 309;
		B = 328;
		break;
	case 40://hor
		A = 328;
		B = 334;
		break;
	case 41://hya
		A = 334;
		B = 351;
		break;
	case 42://hyi
		A = 351;
		B = 355;
		break;
	case 43://ind
		A = 355;
		B = 359;
		break;
	case 44://lac
		A = 359;
		B = 366;
		break;
	case 45://leo
		A = 366;
		B = 375;
		break;
	case 46://lmi
		A = 375;
		B = 378;
		break;
	case 47://lep
		A = 378;
		B = 386;
		break;
	case 48://lib
		A = 386;
		B = 392;
		break;
	case 49://lup
		A = 392;
		B = 403;
		break;
	case 50://lyn
		A = 403;
		B = 410;
		break;
	case 51://lyr
		A = 410;
		B = 415;
		break;
	case 52://men
		A = 415;
		B = 419;
		break;
	case 53://mic
		A = 419;
		B = 423;
		break;
	case 54://mon
		A = 423;
		B = 428;
		break;
	case 55://mus
		A = 428;
		B = 435;
		break;
	case 56://nor
		A = 435;
		B = 440;
		break;
	case 57://oct
		A = 440;
		B = 443;
		break;
	case 58://oph
		A = 443;
		B = 454;
		break;
	case 59://ori
		A = 454;
		B = 472;
		break;
	case 60://pav
		A = 472;
		B = 479;
		break;
	case 61://peg
		A = 479;
		B = 493;
		break;
	case 62://per
		A = 493;
		B = 510;
		break;
	case 63://phe
		A = 510;
		B = 517;
		break;
	case 64://pic
		A = 517;
		B = 520;
		break;
	case 65://psc
		A = 520;
		B = 537;
		break;
	case 66://psa
		A = 537;
		B = 545;
		break;
	case 67://pup
		A = 545;
		B = 555;
		break;
	case 68://pyx
		A = 555;
		B = 558;
		break;
	case 69://ret
		A = 558;
		B = 564;
		break;
	case 70://sge
		A = 564;
		B = 568;
		break;
	case 71://sgr
		A = 568;
		B = 584;
		break;
	case 72://sco
		A = 584;
		B = 597;
		break;
	case 73://scl
		A = 597;
		B = 601;
		break;
	case 74://sct
		A = 601;
		B = 604;
		break;
	case 75://ser
		A = 604;
		B = 613;
		break;
	case 76://sex
		A = 613;
		B = 617;
		break;
	case 77://tau
		A = 617;
		B = 627;
		break;
	case 78://tel
		A = 627;
		B = 630;
		break;
	case 79://tri
		A = 630;
		B = 633;
		break;
	case 80://tra
		A = 633;
		B = 637;
		break;
	case 81://tuc
		A = 637;
		B = 643;
		break;
	case 82://uma
		A = 643;
		B = 662;
		break;
	case 83://umi
		A = 662;
		B = 670;
		break;
	case 84://vel
		A = 670;
		B = 678;
		break;
	case 85://vir
		A = 678;
		B = 689;
		break;
	case 86://vol
		A = 689;
		B = 695;
		break;
	case 87://vul
		A = 695;
		B = 698;
		break;
	}

	iSize = B - A;

	j = A;
	for(i=0; i<iSize; i++)
	{
		singlePoints[i].x	= allPoints[j].x;
		singlePoints[i].y	= allPoints[j].y;
		singleAltitude[i]	= allAltitude[j];
		singleRealX[i]		= allRealPointXs[j],
		singleRealY[i]		= allRealPointYs[j],
		j++;
	}
	return iSize;
}

int CConstellations::LoadSingleArray(CString names[],
									 CString singleNames[],
									 int iConst)
{
	int i, A, B, iSize, j;

	switch(iConst)
	{
	case 0://and
		A = 0;
		B = 9;
		break;
	case 1://ant
		A = 9;
		B = 12;
		break;
	case 2://aps
		A = 12;
		B = 16;
		break;
	case 3://aqr
		A = 16;
		B = 35;
		break;
	case 4://aql
		A = 35;
		B = 46;
		break;
	case 5://ara
		A = 46;
		B = 54;
		break;
	case 6://ari
		A = 54;
		B = 58;
		break;
	case 7://aur
		A = 58;
		B = 66;
		break;
	case 8://boo
		A = 66;
		B = 78;
		break;
	case 9://cae
		A = 78;
		B = 82;
		break;
	case 10://cam
		A = 82;
		B = 88;
		break;
	case 11://cnc
		A = 88;
		B = 93;
		break;
	case 12://cvn
		A = 93;
		B = 96;
		break;
	case 13://cma
		A = 96;
		B = 106;
		break;
	case 14://cmi
		A = 106;
		B = 108;
		break;
	case 15://cap
		A = 108;
		B = 122;
		break;
	case 16://car
		A = 122;
		B = 132;
		break;
	case 17://cas
		A = 132;
		B = 137;
		break;
	case 18://cen
		A = 137;
		B = 149;
		break;
	case 19://cep
		A = 149;
		B = 154;
		break;
	case 20://cet
		A = 154;
		B = 170;
		break;
	case 21://cha
		A = 170;
		B = 175;
		break;
	case 22://cir
		A = 175;
		B = 178;
		break;
	case 23://col
		A = 178;
		B = 184;
		break;
	case 24://com
		A = 184;
		B = 187;
		break;
	case 25://cra
		A = 187;
		B = 195;
		break;
	case 26://crb
		A = 195;
		B = 202;
		break;
	case 27://crv
		A = 202;
		B = 207;
		break;
	case 28://crt
		A = 207;
		B = 216;
		break;
	case 29://cru
		A = 216;
		B = 220;
		break;
	case 30://cyg
		A = 220;
		B = 226;
		break;
	case 31://del
		A = 226;
		B = 231;
		break;
	case 32://dor
		A = 231;
		B = 235;
		break;
	case 33://dra
		A = 235;
		B = 254;
		break;
	case 34://equ
		A = 254;
		B = 257;
		break;
	case 35://eri
		A = 257;
		B = 285;
		break;
	case 36://for
		A = 285;
		B = 289;
		break;
	case 37://gem
		A = 289;
		B = 299;
		break;
	case 38://gru
		A = 299;
		B = 309;
		break;
	case 39://her
		A = 309;
		B = 328;
		break;
	case 40://hor
		A = 328;
		B = 334;
		break;
	case 41://hya
		A = 334;
		B = 351;
		break;
	case 42://hyi
		A = 351;
		B = 355;
		break;
	case 43://ind
		A = 355;
		B = 359;
		break;
	case 44://lac
		A = 359;
		B = 366;
		break;
	case 45://leo
		A = 366;
		B = 375;
		break;
	case 46://lmi
		A = 375;
		B = 378;
		break;
	case 47://lep
		A = 378;
		B = 386;
		break;
	case 48://lib
		A = 386;
		B = 392;
		break;
	case 49://lup
		A = 392;
		B = 403;
		break;
	case 50://lyn
		A = 403;
		B = 410;
		break;
	case 51://lyr
		A = 410;
		B = 415;
		break;
	case 52://men
		A = 415;
		B = 419;
		break;
	case 53://mic
		A = 419;
		B = 423;
		break;
	case 54://mon
		A = 423;
		B = 428;
		break;
	case 55://mus
		A = 428;
		B = 435;
		break;
	case 56://nor
		A = 435;
		B = 440;
		break;
	case 57://oct
		A = 440;
		B = 443;
		break;
	case 58://oph
		A = 443;
		B = 454;
		break;
	case 59://ori
		A = 454;
		B = 472;
		break;
	case 60://pav
		A = 472;
		B = 479;
		break;
	case 61://peg
		A = 479;
		B = 493;
		break;
	case 62://per
		A = 493;
		B = 510;
		break;
	case 63://phe
		A = 510;
		B = 517;
		break;
	case 64://pic
		A = 517;
		B = 520;
		break;
	case 65://psc
		A = 520;
		B = 537;
		break;
	case 66://psa
		A = 537;
		B = 545;
		break;
	case 67://pup
		A = 545;
		B = 555;
		break;
	case 68://pyx
		A = 555;
		B = 558;
		break;
	case 69://ret
		A = 558;
		B = 564;
		break;
	case 70://sge
		A = 564;
		B = 568;
		break;
	case 71://sgr
		A = 568;
		B = 584;
		break;
	case 72://sco
		A = 584;
		B = 597;
		break;
	case 73://scl
		A = 597;
		B = 601;
		break;
	case 74://sct
		A = 601;
		B = 604;
		break;
	case 75://ser
		A = 604;
		B = 613;
		break;
	case 76://sex
		A = 613;
		B = 617;
		break;
	case 77://tau
		A = 617;
		B = 627;
		break;
	case 78://tel
		A = 627;
		B = 630;
		break;
	case 79://tri
		A = 630;
		B = 633;
		break;
	case 80://tra
		A = 633;
		B = 637;
		break;
	case 81://tuc
		A = 637;
		B = 643;
		break;
	case 82://uma
		A = 643;
		B = 662;
		break;
	case 83://umi
		A = 662;
		B = 670;
		break;
	case 84://vel
		A = 670;
		B = 678;
		break;
	case 85://vir
		A = 678;
		B = 689;
		break;
	case 86://vol
		A = 689;
		B = 695;
		break;
	case 87://vul
		A = 695;
		B = 698;
		break;
	}

	iSize = B - A;

	j = A;
	for(i=0; i<iSize; i++)
	{
		singleNames[i] = names[j];
		j++;
	}
	return iSize;
}

int CConstellations::LoadSingleArray(double inArray[],
									 double outArray[],
									 int iConst)
{
	int i, A, B, iSize, j;

	switch(iConst)
	{
	case 0://and
		A = 0;
		B = 9;
		break;
	case 1://ant
		A = 9;
		B = 12;
		break;
	case 2://aps
		A = 12;
		B = 16;
		break;
	case 3://aqr
		A = 16;
		B = 35;
		break;
	case 4://aql
		A = 35;
		B = 46;
		break;
	case 5://ara
		A = 46;
		B = 54;
		break;
	case 6://ari
		A = 54;
		B = 58;
		break;
	case 7://aur
		A = 58;
		B = 66;
		break;
	case 8://boo
		A = 66;
		B = 78;
		break;
	case 9://cae
		A = 78;
		B = 82;
		break;
	case 10://cam
		A = 82;
		B = 88;
		break;
	case 11://cnc
		A = 88;
		B = 93;
		break;
	case 12://cvn
		A = 93;
		B = 96;
		break;
	case 13://cma
		A = 96;
		B = 106;
		break;
	case 14://cmi
		A = 106;
		B = 108;
		break;
	case 15://cap
		A = 108;
		B = 122;
		break;
	case 16://car
		A = 122;
		B = 132;
		break;
	case 17://cas
		A = 132;
		B = 137;
		break;
	case 18://cen
		A = 137;
		B = 149;
		break;
	case 19://cep
		A = 149;
		B = 154;
		break;
	case 20://cet
		A = 154;
		B = 170;
		break;
	case 21://cha
		A = 170;
		B = 175;
		break;
	case 22://cir
		A = 175;
		B = 178;
		break;
	case 23://col
		A = 178;
		B = 184;
		break;
	case 24://com
		A = 184;
		B = 187;
		break;
	case 25://cra
		A = 187;
		B = 195;
		break;
	case 26://crb
		A = 195;
		B = 202;
		break;
	case 27://crv
		A = 202;
		B = 207;
		break;
	case 28://crt
		A = 207;
		B = 216;
		break;
	case 29://cru
		A = 216;
		B = 220;
		break;
	case 30://cyg
		A = 220;
		B = 226;
		break;
	case 31://del
		A = 226;
		B = 231;
		break;
	case 32://dor
		A = 231;
		B = 235;
		break;
	case 33://dra
		A = 235;
		B = 254;
		break;
	case 34://equ
		A = 254;
		B = 257;
		break;
	case 35://eri
		A = 257;
		B = 285;
		break;
	case 36://for
		A = 285;
		B = 289;
		break;
	case 37://gem
		A = 289;
		B = 299;
		break;
	case 38://gru
		A = 299;
		B = 309;
		break;
	case 39://her
		A = 309;
		B = 328;
		break;
	case 40://hor
		A = 328;
		B = 334;
		break;
	case 41://hya
		A = 334;
		B = 351;
		break;
	case 42://hyi
		A = 351;
		B = 355;
		break;
	case 43://ind
		A = 355;
		B = 359;
		break;
	case 44://lac
		A = 359;
		B = 366;
		break;
	case 45://leo
		A = 366;
		B = 375;
		break;
	case 46://lmi
		A = 375;
		B = 378;
		break;
	case 47://lep
		A = 378;
		B = 386;
		break;
	case 48://lib
		A = 386;
		B = 392;
		break;
	case 49://lup
		A = 392;
		B = 403;
		break;
	case 50://lyn
		A = 403;
		B = 410;
		break;
	case 51://lyr
		A = 410;
		B = 415;
		break;
	case 52://men
		A = 415;
		B = 419;
		break;
	case 53://mic
		A = 419;
		B = 423;
		break;
	case 54://mon
		A = 423;
		B = 428;
		break;
	case 55://mus
		A = 428;
		B = 435;
		break;
	case 56://nor
		A = 435;
		B = 440;
		break;
	case 57://oct
		A = 440;
		B = 443;
		break;
	case 58://oph
		A = 443;
		B = 454;
		break;
	case 59://ori
		A = 454;
		B = 472;
		break;
	case 60://pav
		A = 472;
		B = 479;
		break;
	case 61://peg
		A = 479;
		B = 493;
		break;
	case 62://per
		A = 493;
		B = 510;
		break;
	case 63://phe
		A = 510;
		B = 517;
		break;
	case 64://pic
		A = 517;
		B = 520;
		break;
	case 65://psc
		A = 520;
		B = 537;
		break;
	case 66://psa
		A = 537;
		B = 545;
		break;
	case 67://pup
		A = 545;
		B = 555;
		break;
	case 68://pyx
		A = 555;
		B = 558;
		break;
	case 69://ret
		A = 558;
		B = 564;
		break;
	case 70://sge
		A = 564;
		B = 568;
		break;
	case 71://sgr
		A = 568;
		B = 584;
		break;
	case 72://sco
		A = 584;
		B = 597;
		break;
	case 73://scl
		A = 597;
		B = 601;
		break;
	case 74://sct
		A = 601;
		B = 604;
		break;
	case 75://ser
		A = 604;
		B = 613;
		break;
	case 76://sex
		A = 613;
		B = 617;
		break;
	case 77://tau
		A = 617;
		B = 627;
		break;
	case 78://tel
		A = 627;
		B = 630;
		break;
	case 79://tri
		A = 630;
		B = 633;
		break;
	case 80://tra
		A = 633;
		B = 637;
		break;
	case 81://tuc
		A = 637;
		B = 643;
		break;
	case 82://uma
		A = 643;
		B = 662;
		break;
	case 83://umi
		A = 662;
		B = 670;
		break;
	case 84://vel
		A = 670;
		B = 678;
		break;
	case 85://vir
		A = 678;
		B = 689;
		break;
	case 86://vol
		A = 689;
		B = 695;
		break;
	case 87://vul
		A = 695;
		B = 698;
		break;
	}

	iSize = B - A;

	j = A;
	for(i=0; i<iSize; i++)
	{
		outArray[i] = inArray[j];
		j++;
	}
	return iSize;
}


int CConstellations::EvaluateArray(double altitude[], int iSize)
{
	int iType;//1= positive, 2=negative, 3=mixed
	int i;

	iType = 0;

	if(altitude[0] > 0)
	{
		iType = 1;
	}
	else
	{
		iType = 2;
	}

	for(i=1; i<iSize; i++)
	{
		switch (iType)
		{
		case 1:
			if(altitude[i] < 0)iType = 3;
			break;
		case 2:
			if(altitude[i] > 0)iType = 3;
			break;
		}
		if(iType == 3)return iType;
	}
	return iType;
}

void CConstellations::DrawLine(CPlanetsView *pPlanetsView,
							   int first, int second, double altitude[],
							   CPoint pPoints[],
							   int radius,
							   CPoint origin,
							   int R, int G, int B,
							   double realSingleX[], double realSingleY[])
{
	int iPair;
	CPoint pFirst, pSecond;
	double A1, A2;

	A1 = altitude[first];
	A2 = altitude[second];

	iPair = CConstellations::EvaluatePair(A1, A2);

	switch(iPair)
	{
	case 1:
		pPlanetsView->MakeLine(pPoints[first], pPoints[second], R, G, B);
		break;
	case 2:
		break;
	case 3:
		double realX1 = realSingleX[first];
		double realY1 = realSingleY[first];
		double realX2 = realSingleX[second];
		double realY2 = realSingleY[second];

		CConstellations::FindIntersection(radius,
										  origin,
										  A1,
										  pPoints[first],
										  pPoints[second],
										  realX1,
										  realY1,
										  realX2,
										  realY2,
										  pFirst,
										  pSecond);

		pPlanetsView->MakeLine(pFirst, pSecond, R, G, B);
		break;
	}
}
//First adjust data to origin at center of circle, then find slope and y-intercept
//"m" and "s".  To find intersection, set equation of line (y=mx+b)= to equation of circle
//(y**2 + x**2 = r**2) or y=sqrt(r**2 - x**2) and use quadratic formula to solve.
//The two results are quadResult 1 and 2.  The right result is the one between the two 
//points. LS 1/12/05
void CConstellations::FindIntersection(int radius, CPoint origin, double alt1,
									   CPoint p1, CPoint p2,
									   double realX1, double realY1,
									   double realX2, double realY2,
									   CPoint &pFirst, CPoint &pSecond)
{
	double x1, y1, x2, y2, x3, y3, OriginX, OriginY;
	double xIntersection, yIntersection;
	double m, s, m2, s2, r2, quadResult1, quadResult2;
	double temp;//(1 + a*a)
	double temp2;//sqrt[(1+a*a)radius*radius - b*b]
	double distx1, distx2;

	OriginX = origin.x;
	OriginY = origin.y;
	x1 = realX1 - OriginX;
	y1 = realY1 - OriginY;
	x2 = realX2 - OriginX;
	y2 = realY2 - OriginY;

	r2 = radius*radius;

	if(fabs(x1 - x2) > .5)// have slope, find intersection to curve
	{
		m = (double)((y2 - y1) / (x2 - x1));
		s = ((x2 * y1) - (x1 * y2)) / (x2 - x1);
		m2 = m*m;
		s2 = s*s;
		temp = 1.0 + m2;
		temp2 = sqrt(temp*r2 - s2);

		quadResult1 = (-(m*s) + temp2) / temp;
		quadResult2 = (-(m*s) - temp2) / temp;

		xIntersection = CConstellations::FindMiddleValue(x1, x2, quadResult1, quadResult2);
		yIntersection = m*xIntersection + s;
	}
	else//x1 and x2 same, vertical line, slope = undefined
	{//In this case the x-intersection is the x-value of the points and the y-intersection
	 //is the y-value on the circle for that x-value.
		x3 = x1;
		y3 = sqrt(r2 - x3*x3);//y value on the circle at x3
		if(!(		(	y1	<	y3
				&&	y3	<	y2)
			||
				(	y1	>	y3
				&&	y3	>	y2)))y3 *= -1.0;

		distx1 = sqrt(x1*x1 + y1*y1);
		distx2 = sqrt(x2*x2 + y2*y2);
		if(distx1 < radius)
		{
			alt1 = 5;//alt1 positive
		}
		else
		{
			alt1 = -5;//alt1 negative
		}
		yIntersection = y3;
		xIntersection = x3;
	}

	if(alt1 > 0)
	{
		pFirst.x = p1.x;
		pFirst.y = p1.y;
	}
	else
	{
		pFirst.x = p2.x;
		pFirst.y = p2.y;
	}
	pSecond.x = (int)xIntersection + (int)OriginX;
	pSecond.y = (int)yIntersection + (int)OriginY;
}
//	sometimes both quadReturns are outside x1 and x2.  In this case
//	pick the value closest to one of the points (x1 or x2)
double CConstellations::FindMiddleValue(double x1, double x2, double value1, double value2)
{
	double x1ToValue1, x1ToValue2, x2ToValue1, x2ToValue2;
	int iWhichVal1, iWhichVal2;
	double temp1, temp2;

	if(		(	x1		> value1
			&&	value1	> x2)
		||
			(	x1		< value1 
			&&	value1	< x2))
	{
		return value1;
	}
	else if(	(	x1		> value2
				&&	value2	> x2)
			||
				(	x1		< value2
				&&	value2	< x2))
	{
		return value2;
	}
	else
	{
		x1ToValue1 = fabs(x1 - value1);
		x1ToValue2 = fabs(x1 - value2);
		x2ToValue1 = fabs(x2 - value1);
		x2ToValue2 = fabs(x2 - value2);

		if(x1ToValue1 < x1ToValue2)
		{
			temp1 = x1ToValue1;
			iWhichVal1 = 1;
		}
		else
		{
			temp1 = x1ToValue2;
			iWhichVal1 = 2;
		}

		if(x2ToValue1 < x2ToValue2)
		{
			temp2 = x2ToValue1;
			iWhichVal2 = 3;
		}
		else
		{
			temp2 = x2ToValue2;
			iWhichVal2 = 4;
		}

		if(temp1 < temp2)
		{
			if(iWhichVal1 == 1)
			{
				return value1;
			}
			else
			{
				return value2;
			}
		}
		else
		{
			if(iWhichVal2 == 3)
			{
				return value1;
			}
			else
			{
				return value2;
			}
		}
	}
}

int CConstellations::EvaluatePair(double dPoint1, double dPoint2)
{
	if(		dPoint1 > 0
		&&	dPoint2 > 0)
	{
		return 1;//both positive
	}

	else if(	dPoint1 < 0
			&&	dPoint2 < 0)
	{
		return 2;//both negative
	}

	else
	{
		return 3;//mixed
	}
}

int CConstellations::FindHighestAltitude(double altitude[], int iSize)
{
	int i, iHighValue;
	double tempHigh;

	tempHigh = altitude[0];
	iHighValue = 0;

	for(i=1; i<iSize; i++)
	{
		if(altitude[i] > tempHigh)
		{
			tempHigh = altitude[i];
			iHighValue = i;
		}
	}
	return iHighValue;
}

int CConstellations::Andromeda(CPlanetsView *pPlanetsView,
								double altitude[],
								CPoint data[],
								int radius,
								CPoint origin,
								int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		pPlanetsView->MakeLine(data[5], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
	
		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Antlia(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Apus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Aquarius(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		pPlanetsView->MakeLine(data[5], data[7], R, G, B);

		pPlanetsView->MakeLine(data[5], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);
		pPlanetsView->MakeLine(data[13], data[14], R, G, B);
		pPlanetsView->MakeLine(data[14], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[16], R, G, B);
		pPlanetsView->MakeLine(data[16], data[17], R, G, B);
		pPlanetsView->MakeLine(data[17], data[8], R, G, B);

		pPlanetsView->MakeLine(data[15], data[18], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 13, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 14, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 16, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 16, 17, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 17, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 15, 18, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Aquila(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[2], R, G, B);

		pPlanetsView->MakeLine(data[8], data[10], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 8, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Ara(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);

		pPlanetsView->MakeLine(data[2], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		pPlanetsView->MakeLine(data[5], data[7], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 2, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Aries(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Auriga(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[2], R, G, B);

		pPlanetsView->MakeLine(data[0], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 0, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Bootes(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);

		pPlanetsView->MakeLine(data[7], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);

		pPlanetsView->MakeLine(data[7], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 7, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 7, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Caelum(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Camelopardalis(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		pPlanetsView->MakeLine(data[2], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 2, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Cancer(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		pPlanetsView->MakeLine(data[2], data[4], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 2, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::CanesVenatici(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::CanisMajor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		pPlanetsView->MakeLine(data[1], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		pPlanetsView->MakeLine(data[5], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 1, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::CanisMinor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Capricornus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);
		pPlanetsView->MakeLine(data[13], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 13, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Carina(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		pPlanetsView->MakeLine(data[2], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[4], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 2, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Cassiopeia(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Centaurus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);

		pPlanetsView->MakeLine(data[4], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);

		pPlanetsView->MakeLine(data[8], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[1], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 4, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 8, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Cepheus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[1], R, G, B);

		pPlanetsView->MakeLine(data[4], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 4, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Cetus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		pPlanetsView->MakeLine(data[4], data[7], R, G, B);

		pPlanetsView->MakeLine(data[4], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);
		pPlanetsView->MakeLine(data[13], data[14], R, G, B);
		pPlanetsView->MakeLine(data[14], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[10], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 4, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 4, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 13, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 14, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Chamaleon(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Circinus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Columba(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		pPlanetsView->MakeLine(data[2], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 2, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::ComaBerenices(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::CoronaAustralis(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::CoronaBorealis(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Corvus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[1], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Crater(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	//	need to find a point half way between two others,
	//	so add a point to the array and make it the half way point

	data[9].x = (data[2].x + data[3].x) / 2;
	data[9].y = (data[2].y + data[3].y) / 2;
	altitude[9] = altitude[2] + altitude[3] / 2;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);

		pPlanetsView->MakeLine(data[9], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);

		pPlanetsView->MakeLine(data[6], data[8], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 9, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 6, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Crux(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);

		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Cygnus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		pPlanetsView->MakeLine(data[4], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[5], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 4, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Delphinus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[1], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Dorado(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Draco(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);
		pPlanetsView->MakeLine(data[13], data[10], R, G, B);

		pPlanetsView->MakeLine(data[6], data[14], R, G, B);
		pPlanetsView->MakeLine(data[14], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[16], R, G, B);
		pPlanetsView->MakeLine(data[16], data[17], R, G, B);
		pPlanetsView->MakeLine(data[17], data[18], R, G, B);
		pPlanetsView->MakeLine(data[18], data[10], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 13, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 6, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 14, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 16, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 16, 17, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 17, 18, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 18, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Equuleus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Eridanus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);
		pPlanetsView->MakeLine(data[13], data[14], R, G, B);
		pPlanetsView->MakeLine(data[14], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[16], R, G, B);
		pPlanetsView->MakeLine(data[16], data[17], R, G, B);
		pPlanetsView->MakeLine(data[17], data[18], R, G, B);
		pPlanetsView->MakeLine(data[18], data[19], R, G, B);
		pPlanetsView->MakeLine(data[19], data[20], R, G, B);
		pPlanetsView->MakeLine(data[20], data[21], R, G, B);
		pPlanetsView->MakeLine(data[21], data[22], R, G, B);
		pPlanetsView->MakeLine(data[22], data[23], R, G, B);
		pPlanetsView->MakeLine(data[23], data[24], R, G, B);
		pPlanetsView->MakeLine(data[24], data[25], R, G, B);
		pPlanetsView->MakeLine(data[25], data[26], R, G, B);
		pPlanetsView->MakeLine(data[26], data[27], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 13, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 14, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 16, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 16, 17, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 17, 18, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 18, 19, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 19, 20, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 20, 21, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 21, 22, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 22, 23, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 23, 24, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 24, 25, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 25, 26, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 26, 27, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Fornax(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Gemini(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Grus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);

		pPlanetsView->MakeLine(data[3], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);

		pPlanetsView->MakeLine(data[5], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 3, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Hercules(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);

		pPlanetsView->MakeLine(data[4], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);

		pPlanetsView->MakeLine(data[8], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);

		pPlanetsView->MakeLine(data[8], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[5], R, G, B);

		pPlanetsView->MakeLine(data[12], data[13], R, G, B);
		pPlanetsView->MakeLine(data[13], data[14], R, G, B);

		pPlanetsView->MakeLine(data[13], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[16], R, G, B);
		pPlanetsView->MakeLine(data[16], data[17], R, G, B);
		pPlanetsView->MakeLine(data[17], data[18], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 4, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 8, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 8, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 13, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 13, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 16, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 16, 17, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 17, 18, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Horologium(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Hydra(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);
		pPlanetsView->MakeLine(data[13], data[14], R, G, B);
		pPlanetsView->MakeLine(data[14], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[11], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 13, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 14, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Hydrus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Indus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		pPlanetsView->MakeLine(data[1], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 1, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Lacerta(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Leo(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[6], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::LeoMinor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Lepus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		pPlanetsView->MakeLine(data[5], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[7], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Libra(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Lupus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Lynx(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Lyra(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[1], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Mensa(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Microscopium(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Monoceros(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Musca(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Norma(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Octans(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Ophiucus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Orion(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);

		pPlanetsView->MakeLine(data[2], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[5], R, G, B);

		pPlanetsView->MakeLine(data[10], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);
		pPlanetsView->MakeLine(data[13], data[14], R, G, B);
		pPlanetsView->MakeLine(data[14], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[16], R, G, B);
		pPlanetsView->MakeLine(data[16], data[17], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 2, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 10, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 13, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 14, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 16, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 16, 17, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Pavo(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[6], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Pegasus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[4], R, G, B);

		pPlanetsView->MakeLine(data[5], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);

		pPlanetsView->MakeLine(data[5], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Perseus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);

		pPlanetsView->MakeLine(data[5], data[14], R, G, B);
		pPlanetsView->MakeLine(data[14], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[16], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 14, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 16, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Phoenix(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[6], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Pictor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Pisces(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);
		pPlanetsView->MakeLine(data[13], data[14], R, G, B);
		pPlanetsView->MakeLine(data[14], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[11], R, G, B);

		pPlanetsView->MakeLine(data[13], data[16], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 13, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 14, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 13, 16, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::PiscesAustrinus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		pPlanetsView->MakeLine(data[5], data[7], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Puppis(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[5], R, G, B);

		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[7], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Pyxis(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Reticulum(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Sagitta(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		pPlanetsView->MakeLine(data[1], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 1, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Sagittarius(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[4], R, G, B);

		pPlanetsView->MakeLine(data[5], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);

		pPlanetsView->MakeLine(data[10], data[14], R, G, B);

		pPlanetsView->MakeLine(data[8], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[7], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 10, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 8, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Scorpius(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);

		pPlanetsView->MakeLine(data[10], data[12], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 10, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Sculptor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Scutum(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Serpens(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);

		pPlanetsView->MakeLine(data[5], data[7], R, G, B);

		pPlanetsView->MakeLine(data[5], data[8], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Sextans(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Taurus(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);

		pPlanetsView->MakeLine(data[4], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 4, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Telescopium(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Triangulum(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::TriangulumAustrale(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Tucana(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[0], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 0, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::UrsaMajor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);

		pPlanetsView->MakeLine(data[5], data[8], R, G, B);
		pPlanetsView->MakeLine(data[8], data[9], R, G, B);

		pPlanetsView->MakeLine(data[4], data[10], R, G, B);
		pPlanetsView->MakeLine(data[10], data[11], R, G, B);
		pPlanetsView->MakeLine(data[11], data[3], R, G, B);

		pPlanetsView->MakeLine(data[11], data[12], R, G, B);
		pPlanetsView->MakeLine(data[12], data[13], R, G, B);
		pPlanetsView->MakeLine(data[13], data[14], R, G, B);
		pPlanetsView->MakeLine(data[14], data[15], R, G, B);
		pPlanetsView->MakeLine(data[15], data[16], R, G, B);
		pPlanetsView->MakeLine(data[16], data[17], R, G, B);

		pPlanetsView->MakeLine(data[12], data[18], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 8, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 4, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 10, 11, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 11, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 11, 12, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 12, 13, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 13, 14, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 14, 15, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 15, 16, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 16, 17, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 12, 18, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::UrsaMinor(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[3], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Vela(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[6], R, G, B);

		pPlanetsView->MakeLine(data[5], data[7], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 5, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Virgo(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[6], R, G, B);
		pPlanetsView->MakeLine(data[6], data[7], R, G, B);
		pPlanetsView->MakeLine(data[7], data[8], R, G, B);

		pPlanetsView->MakeLine(data[6], data[9], R, G, B);
		pPlanetsView->MakeLine(data[9], data[10], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 6, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 6, 7, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 7, 8, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		CConstellations::DrawLine(pPlanetsView, 6, 9, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 9, 10, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Volans(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);
		pPlanetsView->MakeLine(data[2], data[3], R, G, B);
		pPlanetsView->MakeLine(data[3], data[4], R, G, B);
		pPlanetsView->MakeLine(data[4], data[5], R, G, B);
		pPlanetsView->MakeLine(data[5], data[1], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 2, 3, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 3, 4, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 4, 5, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 5, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}
int CConstellations::Vulpecula(CPlanetsView *pPlanetsView,   double altitude[],   CPoint data[],   int radius,   CPoint origin, int iSize, int iConNames, int R, int G, int B, double realSingleX[], double realSingleY[])
{
	int iType;

	iType = CConstellations::EvaluateArray(altitude, iSize);

	if(iType == 1)// all positive, go ahead and make figure
	{
		pPlanetsView->MakeLine(data[0], data[1], R, G, B);
		pPlanetsView->MakeLine(data[1], data[2], R, G, B);

		return 1;
	}
	else if(iType == 3)//mixed, must evaluate each point
	{
		CConstellations::DrawLine(pPlanetsView, 0, 1, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);
		CConstellations::DrawLine(pPlanetsView, 1, 2, altitude, data, radius, origin, R, G, B, realSingleX, realSingleY);

		return 2;
	}
	else//all negative, don't bother
	{
		return 3;
	}
}

