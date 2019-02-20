// convert.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "convert.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// convert

convert::convert()
{
}

convert::~convert()
{
}


BEGIN_MESSAGE_MAP(convert, CWnd)
	//{{AFX_MSG_MAP(convert)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// convert message handlers

//	Returns Pi
double convert::Pi()
{
	double value;
	return (value = 3.1415926535897932384626433);
}


//	Converts angles in radians to angles in decimal degrees//
double convert::radianToDegree(double value)
{
	value *= (double)180 / convert::Pi();
	return (value);
}


//	Converts angles in decimal degrees to angles in radians//
double convert::degreeToRadian(double value)
{
	value *= (convert::Pi() / (double)180);
	return value;
}

//	Converts angles in radians to angles in decimal hours//
double convert::radianToHour(double value)
{
	value *= (double)12 / convert::Pi();
	return (value);
}

//	Converts angles in decimal hours to angles in radians//
double convert::hourToRadian(double value)
{
	value *= (convert::Pi() / (double)12);
	return value;
}


//	Converts decimal hours to H.MMSSDecimalseconds//
double convert::hourToHMS(double value)
{
	double hour, min, sec, cat, cat1, tot;

	cat = convert::LSmodf(value, &hour);
	if(cat > .999999)// .0036 seconds
	{
		cat = 0.0;
		hour += 1.0;
	}
	cat *= (double)60;
	cat1 = convert::LSmodf(cat, &min);
	if(cat1 > .99999)//.0006 seconds
	{
		cat1 = 0.0;
		min += 1.0;
	}
	sec = cat1 * (double)60;
	tot = hour + min / (double)100 + sec / (double)10000;

	return (tot);
}

//	Converts H.MMSSDecimalseconds to decimal hours
double convert::HMSToHour(double value)
{
	double tot;
	
	tot = convert::DMSToDegree(value);

	return (tot);
}

//	Converts H.MMSSDecimalseconds to decimal degrees
double convert::HMSToDegree(double value)
{
	double tot;

	tot = convert::HMSToHour(value);
	tot = convert::hourToDegree(tot);

	return tot;
}

//	Converts decimal degrees to D.MMSSDecimalseconds//
double convert::degreeToDMS(double value)
{
	double deg, min, sec, cat, cat1, tot;

		cat = convert::LSmodf(value, &deg);
/*		if(cat > .999999)// .0036 seconds of arc
		{
			cat = 0.0;
			deg += 1.0;
		}*/
		cat *= (double)60;
		cat1 = convert::LSmodf(cat, &min);
/*		if(cat1 > .99999)//.0006 seconds of arc
		{
			cat1 = 0.0;
			min += 1.0;
		}*/
		sec = cat1 * (double)60;
		tot = deg + min / (double)100 + sec / (double)10000;

	return (tot);
}

//	Converts D.MMSSDecimalseconds to decimal degrees
double convert::DMSToDegree(double value)
{
	double deg, min, sec, cat, cat1, tot;

	cat = convert::LSmodf(value, &deg);
	cat *= (double)100;
	cat1 = convert::LSmodf(cat, &min);
	sec = cat1 * (double)100;
	tot = deg + min / (double)60 + sec / (double)3600;

	return (tot);
}

//	Converts D.MMDecimalminutes to decimal degrees
double convert::DMMToDegree(double value)
{
	double deg, cat, tot;

	cat = convert::LSmodf(value, &deg);
	cat *= (double)100;
	tot = deg + cat / (double)60;

	return (tot);
}

//	Converts angles in decimal degrees into angles in decimal hours.
//	360 degrees = 24 hours.
double convert::degreeToHour(double value)
{
	return (value /= 15);
}

//	Converts angles in decimal hours into angles in decimal degrees.
//	24 hours = 360 degrees.
double convert::hourToDegree(double value)
{
	return (value *= 15);
}

//	Converts time in tenths of seconds to H.MMSSDecimalseconds//
double convert::deciSecondToHMS(double value)
{
	double hour, cat;

	hour = value / (double)36000;
	cat= convert::hourToHMS(hour);

	return (cat);
}

//	Converts large angle in radians to angle between -2Pi and 2 Pi//
double convert::radianReduce(double value)
{
	if(value == 0) return(0);

	value = fmod(value, (convert::Pi() * (double)2));

	return (value);
}


//	Converts large angle in degrees to angle between -360 and 360//
double convert::degreeReduce(double value)
{
	if(value == 0) return(0);

	value = fmod(value, (double)360);

	return (value);
}

//	Converts negative value in radians to equivalent positive
//	value in radians.(-2Pi < value < 2 Pi).(-Pi radians -> Pi radians)
double convert::radianPositiveValue(double value)
{
	if (value < 0) value += (convert::Pi() * (double)2);
	
	return (value);
}

//	Converts negative value in degrees to equivalent positive
//	value in degrees.( -360 < value < 360).(-60 degrees -> 300 degrees)
double convert::degreePositiveValue(double value)
{
	if (value < 0) value += 360;

	return (value);
}


//	Allows direct calculation of sin from angle in degrees//
double convert::Lsin(double value)
{
	double cat, min;

	cat = (value / (double)180) * convert::Pi();
	min = sin(cat);

	return (min);
}

/**'cstringToDouble' is designed to take care of that problem with reading
	in numbers and finding that they have been truncated or worse by the
	computer.  It does so by taking a number that was read in as a
	character string and transforming it into a double.  But it is only
	built for time or angular data which is loaded in by minutes and
	seconds, as it converts these into decimal hours and degrees.
	It works for numbers from .xxxxxxx to xxx.xxxxxxx.  It also
	takes a number without a decimal point and assumes it is either hours
	or degrees.  It cannot take a number such as 2354.456.  Too many
	hours.  It also ignores digits beyond the seventh (thousandths of seconds).**/
double convert::cstringToDouble(CString pig)
{
	CString temp1('0'), temp2('0'), temp3('0'), temp4('0');
	CString temp5('0'), temp6('0'), temp7('0'), temp8('0');
	CString temp9('0'), temp10('0');
	int i, m_pigLength, flag, flag1;
	long iHour, iMin, iSec, iDsec;
	double hour, min, sec, dsec, value;

	flag = flag1 = 0;

//	If zero length, send back 0
	m_pigLength = pig.GetLength();
	if(m_pigLength < 1) goto finish;

//	if negative, remove'-' for processing, return it at end
	if(pig[0] == '-')
	{
		flag1 = 1;
		pig.Remove('-');
		m_pigLength -= 1;
		if(m_pigLength < 1) goto finish;
	}

//	Find out if there is a '.' in the string
	for ( i = 0; i < m_pigLength; i++ )
	{
		if(pig[i] == '.') flag = 1;
	}
	
//	For the case where a '.' exists, place digits in appropriate places
	if (flag == 1)
	{
												/*	012 34 567  */
	if(pig[0] == '.')							/*  .xx xx xxx  */
	{											/*  .45 67 890  */
		if (pig.GetLength() < 2) goto finish;
		pig += 'x';

		temp4.SetAt(0,pig[1]); if(pig[2] == 'x') goto finish;
		temp5.SetAt(0,pig[2]); if(pig[3] == 'x') goto finish;
		temp6.SetAt(0,pig[3]); if(pig[4] == 'x') goto finish;
		temp7.SetAt(0,pig[4]); if(pig[5] == 'x') goto finish;
		temp8.SetAt(0,pig[5]); if(pig[6] == 'x') goto finish;
		temp9.SetAt(0,pig[6]); if(pig[7] == 'x') goto finish;
		temp10.SetAt(0,pig[7]); goto finish;
	}
												/*	0123 45 678  */
	if(pig[1] == '.')							/*  x.xx xx xxx  */
	{											/*  3.45 67 890  */
		pig += 'x';
		temp3.SetAt(0,pig[0]); if(pig[2] == 'x') goto finish;
		temp4.SetAt(0,pig[2]); if(pig[3] == 'x') goto finish;
		temp5.SetAt(0,pig[3]); if(pig[4] == 'x') goto finish;
		temp6.SetAt(0,pig[4]); if(pig[5] == 'x') goto finish;
		temp7.SetAt(0,pig[5]); if(pig[6] == 'x') goto finish;
		temp8.SetAt(0,pig[6]); if(pig[7] == 'x') goto finish;
		temp9.SetAt(0,pig[7]); if(pig[8] == 'x') goto finish;
		temp10.SetAt(0,pig[8]); goto finish;
	}
												/*	01234 56 789  */
	if(pig[2] == '.')							/*  xx.xx xx xxx  */
	{											/*  23.45 67 890  */
		pig += 'x';
		temp2.SetAt(0,pig[0]);
		temp3.SetAt(0,pig[1]); if(pig[3] == 'x') goto finish;
		temp4.SetAt(0,pig[3]); if(pig[4] == 'x') goto finish;
		temp5.SetAt(0,pig[4]); if(pig[5] == 'x') goto finish;
		temp6.SetAt(0,pig[5]); if(pig[6] == 'x') goto finish;
		temp7.SetAt(0,pig[6]); if(pig[7] == 'x') goto finish;
		temp8.SetAt(0,pig[7]); if(pig[8] == 'x') goto finish;
		temp9.SetAt(0,pig[8]); if(pig[9] == 'x') goto finish;
		temp10.SetAt(0,pig[9]); goto finish;
	}
												/*	012345 67 890  */
	if(pig[3] == '.')							/*  xxx.xx xx xxx  */
	{											/*  123.45 67 890  */
		pig += 'x';
		temp1.SetAt(0,pig[0]);
		temp2.SetAt(0,pig[1]);
		temp3.SetAt(0,pig[2]); if(pig[4] == 'x') goto finish;
		temp4.SetAt(0,pig[4]); if(pig[5] == 'x') goto finish;
		temp5.SetAt(0,pig[5]); if(pig[6] == 'x') goto finish;
		temp6.SetAt(0,pig[6]); if(pig[7] == 'x') goto finish;
		temp7.SetAt(0,pig[7]); if(pig[8] == 'x') goto finish;
		temp8.SetAt(0,pig[8]); if(pig[9] == 'x') goto finish;
		temp9.SetAt(0,pig[9]); if(pig[10] == 'x') goto finish;
		temp10.SetAt(0,pig[10]); goto finish;
	}
}
			
//	For the case where there is no '.'
	if(flag == 0)
	{
		temp3 = pig;
	}
			
//	Make a double out of the strings
finish:;
	iHour = (_ttol(temp1)*100 + _ttol(temp2)*10 + _ttol(temp3));
	iMin = (_ttol(temp4)*10 + _ttol(temp5));
	iSec = (_ttol(temp6)*10 + _ttol(temp7));
	iDsec = (_ttol(temp8)*100 + _ttol(temp9)*10 + _ttol(temp10));
	hour = (double) iHour;
	min = (double)iMin / 100;
	sec = (double)iSec / 10000;
	dsec = (double)iDsec / 10000000;
	value = hour + min + sec + dsec;

	if(flag1) value *= -1;
	return(value);
}

/**	Converts longs representing decimal seconds of time or degrees of
	any size into doubles of hours minutes and seconds.  That is into
	xxxx.xx xx xxxxxx.  The first four are hours (or degrees) the first
	two after the decimal are minutes the next two are seconds and the
	rest are decimals of seconds.*****/
double convert::decimalSecondsToXMS(long value)
{
	double hr;
	double cat, mn, sc, ds, cat1, tot;
	int flag;
	
	flag = 0;
	if(value < 0)
	{
		flag = 1;
		value *= -1;
	}
	hr = floor(value/36000);
	cat = fmod(value, 36000);
	mn = floor(cat/600);
	cat1 = fmod(cat, 600);
	sc = floor(cat1/10);
	ds = fmod(cat1, 10);
	tot = hr + mn/100 + sc/10000 + ds/100000;
	if(flag) tot *= -1;
	return(tot);
}

/**	Converts 3 dimensional coordinates (x, y, z) into spherical coordinates
	(lambda, beta, radius). ***/
void convert::cartesianToSpherical(double x, double y, double z,
									 double &l, double &b, double &r)
{
	l = atan2(y, x);
	b = atan2(z, sqrt(x*x + y*y));
	r = sqrt(x*x + y*y + z*z);
}

/**	Converts spherical coordinates (lambda, beta, radius) into 3 dimensional
	coordinates (x, y, z)  . ***/
void convert::sphericalToCartesian(double l, double b,
				double r, double &x, double &y, double &z)
{
	x = r * cos(b) * cos(l);
	y = r * cos(b) * sin(l);
	z = r * sin(b);
}

/** This converts numbers between -1 and 2 to numbers between
	0 and 1.   ***/
double convert::zeroToOne(double in)
{
	if(in < 0) in += (double)1;
	if(in > 1) in -= (double)1;
	
	return (in);

}

/** This converts angles in radians to numbers between
	-Pi and Pi. This is meant for angles that are
	around 0.0 but sometimes end up 6.28 because of the
	wrap  ***/
double convert::minusPiToPi(double value)
{
	double m_Pi, m_2Pi;

	m_Pi = convert::Pi();
	m_2Pi = 2.0 * m_Pi;

	while (value > m_Pi)
	{
		value -= m_2Pi;
	}
	while (value < -m_Pi)
	{
		value += m_2Pi;
	}

	return (value);
}

//	Not used
/** This converts angles in radians to angles between
	-Pi/2 and Pi/2. ***/
double convert::minusPiOver2ToPiOver2(double value)
{
	double m_HalfPi, m_Pi;

	m_Pi = convert::Pi();
	m_HalfPi = m_Pi / 2.0;

	while (value > m_HalfPi)
	{
		value -= m_Pi;
	}
	while (value < -m_HalfPi)
	{
		value += m_Pi;
	}

	return (value);
}

//	Makes a string out of a decimal degree or time value
//	length is like precision, ie # decimal places
CString convert::DecimalToString(double dValue, int length)
{
	CString cHour, m_Temp, cDay, cYear;
	int  i, decimal, sign, iNoZeroes, err;
	char *buffer=0;
 
	if(dValue != 0)
	{
		// DLAS changed 18Feb9
//		buffer = _fcvt( dValue, length, &decimal, &sign );
		buffer = (char*)malloc(_CVTBUFSIZE);
		err = _fcvt_s(buffer, _CVTBUFSIZE, dValue, length, &decimal, &sign);
//		if (err != 0) {
//			printf("_fcvt_s failed with error code %d\n", err);
//			exit(1);
//		}
		m_Temp = (CString)buffer;
		free(buffer);

		if(sign == 1)
		{
			cHour = '-';
		}
		else
		{
			cHour.Empty();
		}
		if(decimal < 1)
		{
			cHour += "0.";
			iNoZeroes = 0;
			for(i=decimal; i<0; i++)
			{
				if(iNoZeroes < length)
				{
					cHour += '0';
					iNoZeroes += 1;
				}
			}
			cHour += m_Temp.Right(length);
		}
		else
		{
			cHour += m_Temp.Left(decimal) + "." + m_Temp.Right(length);
		}
	}
	else
	{
		cHour = '0';
	}
	return cHour;
}

//	Makes a string out of a HMS or DMS value
CString convert::HMSToString(double dValue, CString type, int precision)
{
	CString cHour, sTemp, cDay, cYear, point;
	int  decimal, sign, err;
	double dTemp, cat, cat1, deg, sec, min, dsec;
	char *buffer = 0;

	point = '.';

//	First round the value properly...
	if(dValue != 0)
	{
//	Positive values first
		if(dValue > 0 )
		{
			switch ( precision )
			{
			case 0:// 150d or 13 h
				cat = convert::LSmodf(dValue, &deg);
				if (cat > .3 )
				{
					deg += 1;
				}
				dTemp = deg;
				break;
			case 1:// 150.8d or 13.8h (same as decimal degrees)
				dTemp = convert::DMSToDegree(dValue);
				break;
			case 2:// 150d 45m or 13h 45m
				cat = convert::LSmodf(dValue, &deg);
				cat *= (double)100;
				cat1 = convert::LSmodf(cat, &min);
				if (cat1 > .3 )
				{
					min += 1;
					if (min > 59)
					{
						min = 0;
						deg += 1;
					}
				}
				dTemp = deg + min / (double)100;
				break;
			case 3:// 150d 45.8m or 13h 45.8m
				cat = convert::LSmodf(dValue, &deg);
				cat *= (double)100;
				cat1 = convert::LSmodf(cat, &min);
				if ((cat1 / .6) > .9499999)
				{
					min += 1;
					cat1 = 0;
					if (min > 59)
					{
						min = 0;
						deg += 1;
					}
				}
				dTemp = deg + min / (double)100 + cat1 / 60;
				break;
			case 4:// 150d 45m 45s or 13h 45m 45s
				cat = convert::LSmodf(dValue, &deg);
				cat *= (double)100;
				cat1 = convert::LSmodf(cat, &min);
				cat1 *= (double)100;
				dsec = convert::LSmodf(cat1, &sec);
				if (dsec > 0.499999)
				{
					sec += 1;
					if (sec > 59)
					{
						sec = 0;
						min += 1;
						if (min > 59)
						{
							min = 0;
							deg += 1;
						}
					}
				}
				dTemp = deg + min / (double)100 + sec / (double)10000;
				break;
			case 5:
				cat = convert::LSmodf(dValue, &deg);
				if( cat > .59599499999)
				{
					dTemp = deg + 1;
				}
				else
				{
					dTemp = dValue;
				}
				break;
			case 6:
				cat = convert::LSmodf(dValue, &deg);
				if( cat > .595999499999)
				{
					dTemp = deg + 1;
				}
				else
				{
					dTemp = dValue;
				}
				break;
			default:
				dTemp = dValue;
			}
		}
		else
//	Here if negative
		{
			switch ( precision )
			{
			case 0:// 150d or 13 h
				cat = convert::LSmodf(dValue, &deg);
				if (cat < -0.3 )
				{
					deg -= 1;
				}
				dTemp = deg;
				break;
			case 1:// 150.8d or 13.8h (same as decimal degrees)
				dTemp = convert::DMSToDegree(dValue);
				break;
			case 2:// 150d 45m or 13h 45m
				cat = convert::LSmodf(dValue, &deg);
				cat *= (double)100;
				cat1 = convert::LSmodf(cat, &min);
				if (cat1 < -0.3 )
				{
					min -= 1;
					if (min < -59)
					{
						min = 0;
						deg -= 1;
					}
				}
				dTemp = deg + min / (double)100;
				break;
			case 3:// 150d 45.8m or 13h 45.8m
				cat = convert::LSmodf(dValue, &deg);
				cat *= (double)100;
				cat1 = convert::LSmodf(cat, &min);
				if ((cat1 / .6) < -0.9499999)
				{
					min -= 1;
					cat1 = 0;
					if (min < -59)
					{
						min = 0;
						deg -= 1;
					}
				}
				dTemp = deg + min / (double)100 + cat1 / 60;
				break;
			case 4:// 150d 45m 45s or 13h 45m 45s
				cat = convert::LSmodf(dValue, &deg);
				cat *= (double)100;
				cat1 = convert::LSmodf(cat, &min);
				cat1 *= (double)100;
				dsec = convert::LSmodf(cat1, &sec);
				if (dsec < -0.499999)
				{
					sec -= 1;
					if (sec < -59)
					{
						sec = 0;
						min -= 1;
						if (min < -59)
						{
							min = 0;
							deg -= 1;
						}
					}
				}
				dTemp = deg + min / (double)100 + sec / (double)10000;
				break;
			case 5:
				cat = convert::LSmodf(dValue, &deg);
				if( cat < -.59599499999)
				{
					dTemp = deg - 1;
				}
				else
				{
					dTemp = dValue;
				}
				break;
			case 6:
				cat = convert::LSmodf(dValue, &deg);
				if( cat < -.595999499999)
				{
					dTemp = deg - 1;
				}
				else
				{
					dTemp = dValue;
				}
				break;
			default:
				dTemp = dValue;
			}
		}

//	...and then make string

// DLAS 18Feb9
//		buffer = _fcvt(dTemp, precision, &decimal, &sign);

		buffer = (char*)malloc(_CVTBUFSIZE);
		err = _fcvt_s(buffer, _CVTBUFSIZE, dTemp, precision, &decimal, &sign);
//		if (err != 0) {
//			printf("_fcvt_s failed with error code %d\n", err);
//			exit(1);
//		}
		sTemp = (CString)buffer;
		free(buffer);
		if(sign == 1)
		{
			cHour = '-';
		}
		else
		{
			cHour.Empty();
		}

//	Here if 0.xxxxxx
		if(decimal < 1)
		{
			switch ( precision )
			{
			case 0:
				cHour += '0' + type;
				break;
			case 1:
				cHour += '0' + point;
				switch (decimal)
				{
				case 0:
					cHour += sTemp.Right(1) + type;
					break;
				default:
					cHour += '0' + type;
					break;
				}
				break;
			case 2:
				cHour += '0' + type + ' ';
				switch (decimal)
				{
				case 0:
				case -1:
					cHour += sTemp.Right(2) + 'm';
					break;
				default:
					cHour += "0m";
					break;
				}
				break;
			case 3:
				cHour += '0' + type + ' ';
				switch (decimal)
				{
				case 0:
					cHour += sTemp.Left(2) + point + sTemp.Right(1) + 'm';
					break;
				case -1:
					cHour += sTemp.Left(1) + point + sTemp.Right(1) + 'm';
					break;
				case -2:
					cHour += '0' + point + sTemp.Right(1) + 'm';
					break;
				default:
					cHour += "0.0m";
					break;
				}
				break;
			case 4:
				cHour += '0' + type + ' ';
				switch ( decimal )
				{
				case 0:
					cHour += sTemp.Left(2) + "m " + sTemp.Right(2) + 's';
					break;
				case -1:
					cHour += sTemp.Left(1) + "m " + sTemp.Right(2) + 's';
					break;
				case -2:
					cHour += "0m " + sTemp.Right(2) + 's';
					break;
				case -3:
					cHour += "0m " + sTemp.Right(1) + 's';
					break;
				default:
					cHour += "0m 0s";
					break;
				}
				break;
			case 5:
				cHour += '0' + type + ' ';
				switch ( decimal )
				{
				case 0:
					cHour += sTemp.Left(2) + "m " + sTemp.Mid((2), 2) +
							 point + sTemp.Right(1) + 's';
					break;
				case -1:
					cHour += sTemp.Left(1) + "m " + sTemp.Mid((1), 2) +
							 point + sTemp.Right(1) + 's';
					break;
				case -2:
					cHour += "0m " + sTemp.Left(2) + point + sTemp.Right(1) + 's';
					break;
				case -3:
					cHour += "0m " + sTemp.Left(1) + point + sTemp.Right(1) + 's';
					break;
				case -4:
					cHour += "0m 0" + point + sTemp.Right(1) + 's';
					break;
				default:
					cHour += "0m 0.0s";
					break;
				}
				break;
			default:
				cHour += '0' + type + ' ';
				switch ( decimal )
				{
				case 0:
					cHour += sTemp.Left(2) + "m " + sTemp.Mid((2), 2) +
							 point + sTemp.Right(precision - 4) + 's';
					break;
				case -1:
					cHour += sTemp.Left(1) + "m " + sTemp.Mid((1), 2) +
							 point + sTemp.Right(precision - 4) + 's';
					break;
				case -2:
					cHour += "0m " + sTemp.Left(2) + point + sTemp.Right(precision - 4) + 's';
					break;
				case -3:
					cHour += "0m " + sTemp.Left(1) + point + sTemp.Right(precision - 4) + 's';
					break;
				case -4:
					cHour += "0m 0" + point + sTemp.Right(precision + decimal) + 's';
					break;
				default:
					cHour += "0m 0" + point + "0" + sTemp.Right(precision + decimal) + 's';
					break;
				}
				break;
			}
		}
		else
//	or here if xxx.xxxxx
		{
			switch ( precision )
			{
			case 0:
				cHour += sTemp.Left(decimal) + type;
				break;
			case 1:
				cHour += sTemp.Left(decimal) + '.' + sTemp.Right(1) + type;
				break;
			case 2:
				cHour += sTemp.Left(decimal) + type + ' ' + sTemp.Right(2) + "m";
				break;
			case 3:
				cHour += sTemp.Left(decimal) + type + ' ' + sTemp.Mid(decimal, 2) + '.' +
						 sTemp.Right(1) + "m";
				break;
			case 4:
				cHour += sTemp.Left(decimal) + type + ' ' + sTemp.Mid(decimal, 2) + "m " +
					 sTemp.Right(2) + 's';
				break;
			default:
				cHour += sTemp.Left(decimal) + type + ' ' + sTemp.Mid(decimal, 2) + "m " +
					 sTemp.Mid(decimal + 2, 2) + '.' + sTemp.Right(precision - 4) + 's';
				break;
			}
		}
	}
	else
	{
		cHour = "0";
	}
	return cHour;
}

//	Not used
void convert::Round(double &value, int level)
{
	double factor, temp, cat, intPortion;
	int i;

	factor = 1.0;
	for (i=0; i<level; i++)
	{
		factor *= (double)10;
	}

	temp = value * factor;
	cat = convert::LSmodf(temp, &intPortion);
	if (cat > 0.5)intPortion +=(double)1;
	value = intPortion / factor;
}

//	Use this instead of modf to solve computer rounding issues
double convert::LSmodf(double dValue, double *deg)
{
	double cat;

	cat = modf(dValue, deg);
	if (cat > 0.999999999)
	{
		*deg += 1;
		cat = 0;
	}
	return cat;
}

//	Not used. It is supposed to verify that the number you think is 3 
//	is not represented in the computer as 2.99999999999
void convert::NumVerify(double *num)
{
	double cat, fract, whole;
	double temp, multiplier;
	int i;

	cat = modf(*num, &temp);
	if (cat > 0.9999999999999)
	{
		cat = 0;
	}

	multiplier = 1e011;
	fract = .99;
	i = 0;

	while (fract > .9)
	{
		i++;
		multiplier *= (double)10;
		cat = *num * multiplier;
		fract = modf(cat, &whole);
	}
	if (i > 1)
	{
		*num += (double)1 / (multiplier / (double)10);
	}
}

//	Given integer, assign string value
CString convert::MonthName(int iMonth)
{
	CString sMonth;
	switch ( iMonth )
	{
	case 1:
		sMonth.LoadString(IDS_JANUARY);// = "January";
		break;
	case 2:
		sMonth.LoadString(IDS_FEBRUARY);// = "February";
		break;
	case 3:
		sMonth.LoadString(IDS_MARCH);// = "March";
		break;
	case 4:
		sMonth.LoadString(IDS_APRIL);// = "April";
		break;
	case 5:
		sMonth.LoadString(IDS_MAY);// = "May";
		break;
	case 6:
		sMonth.LoadString(IDS_JUNE);// = "June";
		break;
	case 7:
		sMonth.LoadString(IDS_JULY);// = "July";
		break;
	case 8:
		sMonth.LoadString(IDS_AUGUST);// = "August";
		break;
	case 9:
		sMonth.LoadString(IDS_SEPTEMBER);// = "September";
		break;
	case 10:
		sMonth.LoadString(IDS_OCTOBER);// = "October";
		break;
	case 11:
		sMonth.LoadString(IDS_NOVEMBER);// = "November";
		break;
	case 12:
		sMonth.LoadString(IDS_DECEMBER);// = "December";
		break;
	}
	return sMonth;
}

//	Given integer, assign string value
CString convert::BodyName(int iBody)
{
	CString sBody;

	switch ( iBody )
	{
	case 0:
		sBody.LoadString(IDS_SUN);// = "Sun";
		break;
	case 1:
		sBody.LoadString(IDS_MOON);// = "Moon";
		break;
	case 2:
		sBody.LoadString(IDS_MERCURY);// = "Mercury";
		break;
	case 3:
		sBody.LoadString(IDS_VENUS);// = "Venus";
		break;
	case 4:
		sBody.LoadString(IDS_EARTH);// = "Earth";
		break;
	case 5:
		sBody.LoadString(IDS_MARS);// = "Mars";
		break;
	case 6:
		sBody.LoadString(IDS_JUPITER);// = "Jupiter";
		break;
	case 7:
		sBody.LoadString(IDS_SATURN);// = "Saturn";
		break;
	case 8:
		sBody.LoadString(IDS_URANUS);// = "Uranus";
		break;
	case 9:
		sBody.LoadString(IDS_NEPTUNE);// = "Neptune";
		break;
	case 10:
		sBody.LoadString(IDS_PLUTO);// = "Pluto";
		break;
	}
	return sBody;
}

//	Given integer, assign string value
CString convert::BodyNameShort(int iBody)
{
	CString sBody;

	switch ( iBody )
	{
	case 0:
		sBody = "Su";
		break;
	case 1:
		sBody = "Mo";
		break;
	case 2:
		sBody = "Me";
		break;
	case 3:
		sBody = "V";
		break;
	case 4:
		sBody = "E";
		break;
	case 5:
		sBody = "Ma";
		break;
	case 6:
		sBody = "J";
		break;
	case 7:
		sBody = "Sa";
		break;
	case 8:
		sBody = "U";
		break;
	case 9:
		sBody = "N";
		break;
	case 10:
		sBody = "P";
		break;
	}
	return sBody;
}

//	Returns decimal double (D.dddd) for strings:
//	DD:mmss		Degrees minutes seconds
//	DD:mm.mm	Degrees minutes decimal minutes
//	DD.dddd		Degrees decimal degrees
double convert::StringToDecimal(CString value)
{
	CString sTemp;
	double dTemp;

	if(value.Find(':') > 0)
	{
		sTemp = value;
		if(value.Find('.') > 0)
		{
			sTemp.Remove('.');
			sTemp.SetAt(value.Find(':'), '.');
			dTemp = convert::DMMToDegree(_tstof(sTemp));
			return dTemp;
		}
		sTemp.SetAt(value.Find(':'), '.');
		dTemp = convert::DMSToDegree(_tstof(sTemp));
		return dTemp;
	}
	else
	{
		dTemp = _tstof(value);
		return dTemp;
	}
}