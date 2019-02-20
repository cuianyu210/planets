// MoonPhase.cpp : implementation file
//

#include "stdafx.h"
#include "astrotime.h"
#include "astrocalc.h"
#include "convert.h"
#include "MoonPhase.h"
#include "MoonDialog.h"
#include <fstream>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoonPhase

CMoonPhase::CMoonPhase( )
{
	convert Convert;

	m_dMeanLunarMonth = 29.530588853;

	m_pSun.sun();
	m_pMoon.moon();

	m_dPi = Convert.Pi();
	m_dPiOver2 = m_dPi / (double)2;
}

CMoonPhase::~CMoonPhase()
{
	delete m_pSun;
	delete m_pMoon;
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CMoonPhase, CWnd)
	//{{AFX_MSG_MAP(CMoonPhase)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMoonPhase message handlers

double CMoonPhase::phase2(double julDay, ULONG uPhase, ULONG *PHASEFOUND)
{
	convert Convert;

	double startJulDay, phaseTime;
	double difFract, posDif;
	ULONG LAST_PHASE;
	ULONG uNEXTQuarter;

	posDif = Convert.radianPositiveValue(AngleDifference(julDay));
	difFract = DifferenceFraction(posDif);
	LAST_PHASE = LastPhase(posDif);

	if(NEXT_QUARTER == uPhase)
	{
		switch ( LAST_PHASE )
		{
		case NEW_MOON :
			uNEXTQuarter = FIRST_QUARTER;
			break;
		case FIRST_QUARTER :
			uNEXTQuarter = FULL_MOON;
			break;
		case FULL_MOON :
			uNEXTQuarter = THIRD_QUARTER;
			break;
		case THIRD_QUARTER :
			uNEXTQuarter = NEW_MOON;
			break;
		}
	}
	else if ( PREVIOUS_QUARTER == uPhase)
	{
		switch ( LAST_PHASE )
		{
		case NEW_MOON :
			uNEXTQuarter = NEW_MOON;
			break;
		case FIRST_QUARTER :
			uNEXTQuarter = FIRST_QUARTER;
			break;
		case FULL_MOON :
			uNEXTQuarter = FULL_MOON;
			break;
		case THIRD_QUARTER :
			uNEXTQuarter = THIRD_QUARTER;
			break;
		}
	}
	else
	{
		uNEXTQuarter = uPhase;
	}
	*PHASEFOUND = uNEXTQuarter;

	startJulDay = TimeToStartSearch(LAST_PHASE, uPhase, julDay);

	difFract = DifferenceFraction(Convert.radianPositiveValue(AngleDifference(startJulDay)));
	
	phaseTime = FindNextQuarter(startJulDay,
								difFract,
								uNEXTQuarter);
	return phaseTime;
}

double CMoonPhase::AngleDifference(double julDay)
{
	double dif;
	double sunL, sunB, sunR, moonL, moonB, moonR;

	m_pSun.geocentricSphericalAppPlanet(julDay,sunL, sunB, sunR);
	m_pMoon.geocentricSphericalAppPlanet(julDay,moonL, moonB, moonR);

	dif = moonL - sunL;
	return dif;
}

ULONG CMoonPhase::LastPhase(double posDif)
{
	ULONG PHASE;

	if(posDif > 1.5 * m_dPi)
	{
		PHASE = THIRD_QUARTER;
	}
	else if(posDif > m_dPi)
	{
		PHASE = FULL_MOON;
	}
	else if(posDif > m_dPiOver2)
	{
		PHASE = FIRST_QUARTER;
	}
	else
	{
		PHASE = NEW_MOON;
	}
	return PHASE;
}

double CMoonPhase::FindNextQuarter(double julDay,
								   double difFract,
								   ULONG uPHASE)
{
	convert Convert;

	double day1, day2, dif, posDif;
	double factor, dCheck;

	dCheck = 0.1;
	day1 = julDay;
	switch ( uPHASE )
	{
	case NEW_MOON :
		factor = 0.;
		break;
	case FIRST_QUARTER :
		factor = m_dPiOver2;
		break;
	case FULL_MOON :
		factor = m_dPi;
		break;
	case THIRD_QUARTER :
		factor = 3*m_dPiOver2;
		break;
	}
	day2 = day1 + (1-difFract) * m_dMeanLunarMonth / 4.;
	while (fabs(dCheck) > .0000001)
	{
		dif = AngleDifference(day2);
		posDif = Convert.radianPositiveValue(dif);
		difFract = DifferenceFraction(posDif);

		day1 = day2;
		if(NEW_MOON == uPHASE)
		{
			dCheck = dif;
		}
		else
		{
			dCheck = fabs(posDif)-factor;
		}
		if(dCheck < 0)
		{
			day2 = day1 + (1-difFract) * m_dMeanLunarMonth / 4.;
		}
		else
		{
			day2 = day1 - (difFract) * m_dMeanLunarMonth / 4.;
		}
	}
	return day1;
}

double CMoonPhase::DifferenceFraction(double dif)
{
	double difFract;

	if(dif > 1.5 * m_dPi)
	{
		difFract = (dif -  (1.5 * m_dPi))/ m_dPiOver2;
	}
	else if(dif > m_dPi)
	{
		difFract = (dif - m_dPi) / m_dPiOver2;
	}
	else if(dif > m_dPiOver2)
	{
		difFract = (dif - m_dPiOver2) / m_dPiOver2;
	}
	else
	{
		difFract = dif / m_dPiOver2;
	}
	return difFract;
}

double CMoonPhase::TimeToStartSearch(ULONG LASTPHASE,
									 ULONG FINDPHASE,
									 double julDay)
{
	double newJulDay;
	double factor;

	switch ( FINDPHASE )
	{
	case NEW_MOON :
		switch ( LASTPHASE )
		{
		case NEW_MOON :
			factor = 0.75;
			break;
		case FIRST_QUARTER :
			factor = 0.5;
			break;
		case FULL_MOON :
			factor = 0.25;
			break;
		case THIRD_QUARTER :
			factor = 0.;
			break;
		}
		break;
	case FIRST_QUARTER :
		switch ( LASTPHASE )
		{
		case NEW_MOON :
			factor = 0.;
			break;
		case FIRST_QUARTER :
			factor = 0.75;
			break;
		case FULL_MOON :
			factor = 0.5;
			break;
		case THIRD_QUARTER :
			factor = 0.25;
			break;
		}
		break;
	case FULL_MOON :
		switch ( LASTPHASE )
		{
		case NEW_MOON :
			factor = 0.25;
			break;
		case FIRST_QUARTER :
			factor = 0.;
			break;
		case FULL_MOON :
			factor = 0.75;
			break;
		case THIRD_QUARTER :
			factor = 0.5;
			break;
		}
		break;
	case THIRD_QUARTER :
		switch ( LASTPHASE )
		{
		case NEW_MOON :
			factor = 0.5;
			break;
		case FIRST_QUARTER :
			factor = 0.25;
			break;
		case FULL_MOON :
			factor = 0.0;
			break;
		case THIRD_QUARTER :
			factor = 0.75;
			break;
		}
		break;
	case NEXT_QUARTER :
		factor = 0.;
		break;
	case PREVIOUS_QUARTER :
		factor = -0.25;
		break;
	}
	newJulDay = julDay + factor * m_dMeanLunarMonth;
	return newJulDay;
}

void CMoonPhase::WholeYear(CMoonDialog *pMD, double julDay)
{
	convert Convert;

	double startJulDay, endJulDay;
	double difFract, posDif, phaseTime;
	ULONG LAST_PHASE;
	ULONG uNEXTQuarter;

	m_pMoonDlg = pMD;
	CFileDialog fileBox(false, _T ("txt"), _T ("MoonPhases"),OFN_OVERWRITEPROMPT,
						_T ("Text Files (*.txt)|*.txt||"));

	if((fileBox.DoModal()) == 1)
	{//	save
		m_sFileName = fileBox.GetPathName();
	}
	else//cancelled
	{
		return;
	}

	startJulDay = julDay;
	endJulDay = julDay + 366.;

	posDif = Convert.radianPositiveValue(AngleDifference(julDay));
	difFract = DifferenceFraction(posDif);
	LAST_PHASE = LastPhase(posDif);

	writeHeader(julDay, LAST_PHASE);

	switch ( LAST_PHASE )
	{
	case NEW_MOON :
		uNEXTQuarter = FIRST_QUARTER;
		break;
	case FIRST_QUARTER :
		uNEXTQuarter = FULL_MOON;
		break;
	case FULL_MOON :
		uNEXTQuarter = THIRD_QUARTER;
		break;
	case THIRD_QUARTER :
		uNEXTQuarter = NEW_MOON;
		break;
	}

	while( startJulDay < endJulDay)
	{
		difFract = DifferenceFraction(Convert.radianPositiveValue(AngleDifference(startJulDay)));
		phaseTime = FindNextQuarter(startJulDay, difFract, uNEXTQuarter);
		writeValue(phaseTime, uNEXTQuarter);
		startJulDay = phaseTime + 0.2 * m_dMeanLunarMonth;
		nextPhase(LAST_PHASE, uNEXTQuarter);
	}
}

void CMoonPhase::nextPhase(ULONG &last, ULONG &current)
{
	switch ( last )
	{
	case NEW_MOON :
		last = FIRST_QUARTER;
		current = FULL_MOON;
		break;
	case FIRST_QUARTER :
		last = FULL_MOON;
		current = THIRD_QUARTER;
		break;
	case FULL_MOON :
		last = THIRD_QUARTER;
		current = NEW_MOON;
		break;
	case THIRD_QUARTER :
		last = NEW_MOON;
		current = FIRST_QUARTER;
		break;
	}
}


void CMoonPhase::writeHeader(double julDay, ULONG lastPHASE)
{
	std::wofstream outfile;

	CString sTime;

	julDay -= m_pMoonDlg->m_dTZone / 24.;
	if(m_pMoonDlg->m_sDST == "y")julDay += 1.;
	sTime = m_pMoonDlg->MakeTimeString(julDay);

	outfile.open(m_sFileName, std::ofstream::trunc );

	outfile<<"Moon Phases for:"<<m_pMoonDlg->m_iMoonYear<<std::endl;
	outfile<<"New Moon Julian"<<"; " << "New Moon Day" << "; " <<"First Quarter Julian"<<"; " << "First Quarter Day" << "; ";
	outfile <<"Full Moon Julian" << "; " << "Full Moon Day" << "; " << "Third Quarter Julian" << "; " << "Third Quarter Day";
	outfile<<std::endl;
	switch ( lastPHASE )
	{
	case NEW_MOON :
		outfile<<";; ";
		break;
	case FIRST_QUARTER :
		outfile<<";;;; ";
		break;
	case FULL_MOON :
		outfile<<";;;;;; ";
		break;
	case THIRD_QUARTER :
		break;
	}
	outfile.close();
}

void CMoonPhase::writeValue(double time, ULONG uPHASE)
{
	std::wofstream outfile;
	CString sTime;

	outfile.open(m_sFileName, std::ofstream::app );

	time -= m_pMoonDlg->m_dTZone / 24.;
	sTime = m_pMoonDlg->MakeTimeString(time);
	outfile.precision(6);

	switch ( uPHASE )
	{
	case NEW_MOON :
	case FIRST_QUARTER :
	case FULL_MOON :
		outfile << std::fixed << time << "; " <<(LPCTSTR)sTime<<"; ";
		break;
	case THIRD_QUARTER :
		outfile << std::fixed << time << "; " << (LPCTSTR)sTime<< std::endl;
		break;
	}
	outfile.close();
}

void CMoonPhase::PostNcDestroy() 
{	
	CWnd::PostNcDestroy();
}
