// Validate.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Validate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CValidate

CValidate::CValidate()
{
}

CValidate::~CValidate()
{
}


BEGIN_MESSAGE_MAP(CValidate, CWnd)
	//{{AFX_MSG_MAP(CValidate)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CValidate message handlers
bool CValidate::validateChar(UINT uEditStyle, int iChar) 
{
	bool retVal = false;

	switch(uEditStyle)
	{
	case IDS_EDIT_BOX_DOUBLE:
		{
			//                0       -          9                 "-"                "."
			if((iChar >= 0x0030 && iChar <= 0x0039) || iChar == 0x002d || iChar == 0x002e)
			{
				retVal = true;
			}
			else
			{
				retVal = false;
			}
			break;
		}
	case IDS_EDIT_BOX_INT:
		{
			//                0       -          9               "-"
			if(iChar >= 0x0030 && iChar <= 0x0039 || iChar == 0x002d)
			{
				retVal = true;
			}
			else
			{
				retVal = false;
			}
			break;
		}
	case IDS_EDIT_BOX_LATLON:
		{
			//               0       -          9                  ":"                "."
			if((iChar >= 0x0030 && iChar <= 0x0039) || iChar == 0x003a || iChar == 0x002e)
			{
				retVal = true;
			}
			else
			{
				retVal = false;
			}
			break;
		}
	}
	return retVal;
}

bool CValidate::validateField(UINT uEditStyle, CString t)
{
	bool retVal = false;
	int tLength;
	int curPos;
	bool bValid = true;
	bool haveRadix = false;
	bool haveColon = false;
	switch(uEditStyle)
	{
	case IDS_EDIT_BOX_DOUBLE:
		{
			curPos = 0;
			
			tLength = t.GetLength();
			if(t[0] == 0x002d) // a minus sign
				curPos++;
			while( (curPos < tLength)  && bValid)
			{
				if(t[curPos] == 0x002e)// '.' decimal point
				{
					if(!haveRadix)
					{
						haveRadix = true;
						curPos++;
					}
					else // uh oh 2 radices, validate fails
					{
						bValid = false;
						break; // will this work here to break out of while loop?
					}
				}
				//                         0       -             9
				else if( t[curPos] >= 0x0030 && t[curPos] <= 0x0039)
				{// we're good
					curPos++;
				}
				else
				{
					bValid = false;
					break;
				}
			}// while
			break;
		}
	case IDS_EDIT_BOX_INT:
		{
			curPos = 0;
			
			tLength = t.GetLength();
			if(t[0] == 0x002d) // a minus sign
				curPos++;
			while( (curPos < tLength)  && bValid)
			{
				if( t[curPos] >= 0x0030 && t[curPos] <= 0x0039)
				{// we're good
					curPos++;
				}
				else
				{
					bValid = false;
					break;
				}
			}// while
			break;
		}
	case IDS_EDIT_BOX_LATLON:
		{
			curPos = 0;
			tLength = t.GetLength();

			while( (curPos < tLength)  && bValid)
			{
				if(t[curPos] == 0x002e)// '.' decimal point
				{
					if(!haveRadix)
					{
						haveRadix = true;
						curPos++;
					}
					else // uh oh 2 radices, validate fails
					{
						bValid = false;
						break; // will this work here to break out of while loop?
					}
				}
				else if(t[curPos] == 0x003a)// ':' colon
				{
					if(!haveColon && !haveRadix)
					{
						haveColon = true;
						curPos++;
					}
					else // uh oh 2 colons or colon after radix, validate fails
					{
						bValid = false;
						break; // break out of while loop
					}
				}
				//                         0       -             9
				else if( t[curPos] >= 0x0030 && t[curPos] <= 0x0039)
				{// we're good
					curPos++;
				}
				else
				{
					bValid = false;
					break;
				}
			}// while
			break;
		}

	}
return bValid;

}

bool CValidate::validateMagnitude(double val)
{
	bool bValid = false;

	if(val >= -1 && val <= 8)
		bValid = true;
	return bValid;
}

bool CValidate::validateViewDir(int val)
{
	bool bValid = false;

	if(val >= 0 && val <= 360)
		bValid = true;
	return bValid;
}

bool CValidate::validateYear(int val)
{
	bool bValid = false;

	if(val >= -4712 && val <= 4712)
		bValid = true;
	return bValid;
}

bool CValidate::validateMonth(int val)
{
	bool bValid = false;

	if(val >= 1 && val <= 12)
		bValid = true;
	return bValid;
}

bool CValidate::validateDate(int val)
{
	bool bValid = false;

	if(val >= 1 && val <= 31)
		bValid = true;
	return bValid;
}

bool CValidate::validateHour(int val)
{
	bool bValid = false;

	if(val >= 0 && val <= 13)
		bValid = true;
	return bValid;
}

bool CValidate::validateLatLon(CString val, UINT tudeType)
{
	bool bValid = false;
	bool bValidDeg = false;
	bool bValidMin = false;
	bool bValidSec = false;
	bool haveColon = false;
	bool haveRadix = false;
	bool haveDeg = false;
	bool haveMin = false;
	bool haveSec = false;
	bool haveMaxDeg = false;
	CString deg;
	CString min;
	CString sec;
	CString temp;
	int iDeg;
	double dDeg;
	int iMin;
	double dMin;
	double dSec;
	int sLength;
	int curPos = 0;
	int minLength = 0;
	int colonPos;
	int maxDigits;
	int fieldType = NO_DELIMITER;
//	char *stopstring;
	int maxDeg = 90;

	if(tudeType == IDS_LONGITUDE)
		maxDeg = 180;

	deg.Empty();
	min.Empty();
	sec.Empty();

	sLength = val.GetLength();
	while(curPos < sLength)// find colon and radix positions
	{
		temp = val.GetAt(curPos);
		curPos++;

		if(temp[0] == 0x003a )// ':' colon
		{
			haveColon = true;
			colonPos = curPos - 1;
			fieldType += COLON;
		}
		else if(temp[0] == 0x002e)// '.' decimal point
		{
			haveRadix = true;
			fieldType += RADIX;
		}
	}
	// reset curPos
	curPos = 0;

	switch(fieldType) // load 'deg' 'min' and 'sec'
	{
	case NO_DELIMITER://  neither colon nor radix
		{
			while(curPos < sLength)
			{
				deg += val.GetAt(curPos);
				haveDeg = true;
				curPos++;
			}
			break;
		}
	case COLON_ONLY:// have D:mmssssss
		{
			while(curPos < colonPos)
			{
				deg += val.GetAt(curPos);
				haveDeg = true;
				curPos++;
			}

			curPos++;
			maxDigits = 1;
			while(curPos < sLength && maxDigits < 3)
			{
				maxDigits++;
				min += val.GetAt(curPos);
				haveMin = true;
				curPos++;
			}
			maxDigits = 1;
			while(curPos < sLength && maxDigits < 3)
			{
				maxDigits++;
				sec += val.GetAt(curPos);
				haveSec = true;
				curPos++;
			}
			if(curPos < sLength)
				sec += ".";
			while(curPos < sLength)
			{
				sec += val.GetAt(curPos);
				haveSec = true;
				curPos++;
			}
			break;
		}
	case RADIX_ONLY:// have D.ddddddd
		{
			while(curPos < sLength)
			{
				deg += val.GetAt(curPos);
				haveDeg = true;
				curPos++;
			}
			break;
		}
	case COLON_AND_RADIX:// have D:mm.mmmmm
		{
			while(curPos < colonPos)
			{
				deg += val.GetAt(curPos);
				haveDeg = true;
				curPos++;
			}

			curPos++;
			while(curPos < sLength)
			{
				min += val.GetAt(curPos);
				haveMin = true;
				curPos++;
			}
			break;
		}
	}

	if(haveDeg) //  evaluate 'deg' for value
	{
		switch(fieldType)
		{
		case NO_DELIMITER:// only have degree, no radix or colon
		case COLON_ONLY:
		case COLON_AND_RADIX:
			{
				iDeg = _ttoi((LPCTSTR)deg);
				if(iDeg >= 0 && iDeg <= maxDeg)
				{
					bValidDeg = true;
					if(iDeg > maxDeg - 1) // we have either 90 or 180
						haveMaxDeg = true;
				}
				break;
			}
		case RADIX_ONLY:
			{
			//  DLAS 18Feb9
			//	See https://stackoverflow.com/questions/916790/how-do-i-convert-a-cstring-to-a-double-in-c
			//	for explanation of this change
//				dDeg = strtod(deg, &stopstring);
				dDeg = _tstof(deg);
				
				if(dDeg >= 0 && dDeg <= (double)maxDeg)
				{
					bValidDeg = true;
					if(dDeg > (double)maxDeg - 0.5) // we have either 90 or 180
						haveMaxDeg = true;
				}
				break;
			}
		}
	}
	else
	{
		bValidDeg = true;
	}


	if(haveMin)
	{
		switch(fieldType)
		{
		case COLON_ONLY:
			{
				iMin = _ttoi((LPCTSTR)min);
				if(iMin >= 0 && iMin < 60)
				{
					bValidMin = true; // we're good, within range
					if(haveDeg && haveMaxDeg)
						bValidMin = false; // Uh-oh, we have either 90 or 180
				}
				break;
			}
		case COLON_AND_RADIX:
			{
			//  DLAS 18Feb9
			//	See https://stackoverflow.com/questions/916790/how-do-i-convert-a-cstring-to-a-double-in-c
			//	for explanation of this change
			//	dMin = strtod(min, &stopstring);
				dMin = _tstof(min);
				if(dMin >= 0 && dMin < 60)
				{
					bValidMin = true; // we're good, within range
					if(haveDeg && haveMaxDeg)
						bValidMin = false; // Uh-oh, we have either 90 or 180

				}
				break;
			}
		}
	}
	else
	{
		bValidMin = true;
	}


	if(haveSec)
	{
		//  DLAS 18Feb9
		//	See https://stackoverflow.com/questions/916790/how-do-i-convert-a-cstring-to-a-double-in-c
		//	for explanation of this change
		//	dSec =  strtod(sec, &stopstring);
		dSec = _tstof(sec);
		if(dSec >= 0 && dSec < 60)
		{
			bValidSec = true; // we're good, within range
			if(haveDeg && haveMaxDeg)
				bValidMin = false; // Uh-oh, we have either 90 or 180
		}
	}
	else
	{
		bValidSec = true;
	}

	if(bValidDeg && bValidMin && bValidSec)
		bValid = true;

	return bValid;
}
	