// Star.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Star.h"
#include "StarBox.h"
#include "TimeLocation.h"
#include "StarData.h"
#include "PlanetsView.h"
#include "convert.h"
#include <math.h>
#include <fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStar

CStar::CStar()
{
}

CStar::CStar(class CTimeLocation* dick)
{
	m_pTimeLocation = dick;
}

CStar::~CStar()
{
}


BEGIN_MESSAGE_MAP(CStar, CWnd)
	//{{AFX_MSG_MAP(CStar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStar message handlers

void CStar::doStars(int iNumPlanets, double julDay,
					double latitude, double longitude,
					int iMethod, CString sDateString,
					CArray<int, int> *iConstList)
{
	CWinApp* pApp = AfxGetApp();

	std::wofstream outfile;
	CString PlanetAzimuthString[11];
	CString PlanetAltitudeString[11];
	int i;

	class CMainFrame* pCMainFrame;
	class CChildFrame* pChildFrame;
	class CPlanetsView* pCView;

	pCMainFrame = (CMainFrame*)m_pTimeLocation->GetOwner();

//	if no child window, make one by calling File New from theApp
	if(!(pChildFrame = (CChildFrame*)pCMainFrame->MDIGetActive()))
	{
		CPlanetsApp* pApp = (CPlanetsApp*)AfxGetApp();
		pApp->OnNewFile();
		pChildFrame = (CChildFrame*)pCMainFrame->MDIGetActive();
		pCView = (CPlanetsView*)pChildFrame->GetActiveView();
	}
	else // we have a window, so get the view
	{
		pCView = (CPlanetsView*)pChildFrame->GetActiveView();
	}

	m_dLatitude = latitude;
	m_dLongitude = longitude;
	m_sDateString = sDateString;

	if(iNumPlanets > 0)// Are we doing any planets?
	{
		for(i=0; i<11; i++)//  Get the planet data
		{
			this->m_dPlanetAzimuth[i] = m_pTimeLocation->m_pValues[i][0];
			this->m_dPlanetAltitude[i] = m_pTimeLocation->m_pValues[i][1];
			this->m_pPlanetSet[i] = m_pTimeLocation->m_pPlanetSet[i];
		}
	//	Make strings for azimuth and altitude data
		pCView->m_pCStar->MakePlanetStrings(m_dPlanetAzimuth, m_dPlanetAltitude,
								 PlanetAzimuthString, PlanetAltitudeString,
								 m_pPlanetSet);
	}

//	Open Star Box
//	What sort of star information are we looking for
	m_iWhichStars = pCView->m_pCStar->MagConst();
	if(IDS_CANCEL == m_iWhichStars)//return without calculation
	{
		goto starCancel;
	}

//	Find positions of all of the stars so set magnitude to 8.0 and do all constellations
//	etc so can show what you want later
	pCView->m_pStarData->CalculatePositions(IDS_MAGNITUDE_AND_CONSTELLATION, 8.0, julDay,
							 latitude, longitude);

	if(1 == m_iStarToFile)// if want to print to file
	{
		CFileDialog fileBox(false, _T ("txt"), m_sStarFileName,OFN_OVERWRITEPROMPT,
							_T ("Text Files (*.txt)|*.txt||"));
	//	Find file name
		if((fileBox.DoModal()) == 1)
		{//	save
			m_sStarFileName = fileBox.GetPathName();
			pApp->WriteProfileString(_T ("StarBox"), _T ("starfilename"), m_sStarFileName);

	//	Print headers
		outfile.open(m_sStarFileName, std::ios::trunc );
		outfile<<"Name"<<"; ";
		outfile<<"Constellation"<<"; ";
		outfile<<"Right Ascension"<<";"<<"Declination"<<"; ";
		outfile<<"Magnitude"<<std::endl;
		outfile.close();

		if(iNumPlanets > 0)//  print planets
		{
			pCView->m_pCStar->OutputPlanetData(m_pPlanetSet,
									PlanetAzimuthString, PlanetAltitudeString);
		}
		
	//	print star data
		pCView->m_pStarData->PrintData(m_iWhichStars, m_sStarFileName, 8.0);
		//	Output numbers to file
		}
		else//cancelled
		{
		}

	}
//	all data to screen
	pCView->DrawStars(iConstList, iNumPlanets);
starCancel:;
}//end of "CStar::doStars(double julDay, int iMethod)"

void CStar::OutputPlanetData(int pPlanetSet[],
						  CString sPlanetAzimuthArray[],
						  CString sPlanetAltitudeArray[])
{
	convert Convert;

	int j;

	std::wofstream outfile;
	outfile.open(m_sStarFileName, std::ios::app );

	for(j=0; j<11; j++)
	{
		if(1 == pPlanetSet[j])
		{
			outfile<< (LPCTSTR)Convert.BodyName(j)<<"; ";
			outfile<<"; ";
			outfile<< (LPCTSTR)sPlanetAzimuthArray[j]<<"; ";
			outfile<< (LPCTSTR)sPlanetAltitudeArray[j]<<"; ";
			outfile<<"; "<<std::endl;
		}
	}
	outfile.close();
}

void CStar::MakePlanetStrings(double azimuth[], double altitude[],
							  CString sPlanetAzimuthArray[],
							  CString sPlanetAltitudeArray[],
							  int pPlanetSet[])
{
	CAlmanac pAlmanac;
	int i;

	for(i=0; i<11; i++)
	{
		if(1 == pPlanetSet[i])
		{
			pAlmanac.MakeString(azimuth[i], sPlanetAzimuthArray[i],
								IDS_DECIMAL, 5);
			pAlmanac.MakeString(altitude[i], sPlanetAltitudeArray[i],
								IDS_DECIMAL, 5);
		}
	}
}

UINT CStar::MagConst()
{
	CStarBox pStarBox;
	int value, retVal;
	UINT type;

	value = 0;

	while(		value < 1
			||
				value > 3)
	{
		retVal = -1;
		retVal = pStarBox.DoModal();
		if(retVal > 1)
		{
			value = 0;
			break;
		}//return -retVal;//user abort or cancel
		else
		{
			value = pStarBox.m_iBoxValue;
		}
	}
	switch(value)
	{
	case 0:
		type = IDS_CANCEL;
		return type;
		break;
	case 1:
		type = IDS_MAGNITUDE_ONLY;
		break;
	case 2:
		type = IDS_CONSTELLATION_ONLY;
		break;
	case 3:
		type = IDS_MAGNITUDE_AND_CONSTELLATION;
		break;
	}

	m_iStarNames = pStarBox.m_iStarNames;
	m_iConNames = pStarBox.m_iConNames;
	m_iStarToFile = pStarBox.m_iStarToFile;
	m_sStarFileName = pStarBox.m_sStarFileName;
	m_sMagnitude = pStarBox.m_sMagnitude;
	m_dMagnitude = _tstof(pStarBox.m_sMagnitude);
	m_sViewDirection = pStarBox.m_sViewDirection;

	return type;
}
