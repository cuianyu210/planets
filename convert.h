#if !defined(AFX_CONVERT_H__F0F4FAFC_8C38_4866_968C_8FBA536529CC__INCLUDED_)
#define AFX_CONVERT_H__F0F4FAFC_8C38_4866_968C_8FBA536529CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// convert.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// convert window

class convert : public CWnd
{
// Construction
public:
	convert();

// Attributes
public:

// Operations
public:
	double Pi();
	double radianToDegree(double value);
	double degreeToRadian(double value);
	double radianToHour(double value);
	double hourToRadian(double value);
	double hourToHMS(double value);
	double HMSToHour(double value);
	double HMSToDegree(double value);
	double degreeToDMS(double value);
	double DMSToDegree(double value);
	double DMMToDegree(double value);
	double degreeToHour(double value);
	double hourToDegree(double value);
	double deciSecondToHMS(double value);
	double radianReduce(double value);
	double degreeReduce(double value);
	double radianPositiveValue(double value);
	double degreePositiveValue(double value);
	double Lsin(double value);
	double cstringToDouble(CString pig);
	double decimalSecondsToXMS(long value);
	void cartesianToSpherical(double x, double y, double z,
								double &l, double &b, double &r);
	void sphericalToCartesian(double theta, double gamma, double r,
							  double &x, double &y, double &z);
	double zeroToOne(double in);
	double minusPiToPi(double value);
	double minusPiOver2ToPiOver2(double value);
	CString DecimalToString(double dValue, int length);
	CString HMSToString(double dValue, CString type, int precision);
	void Round(double &value, int level);
	double LSmodf(double dValue, double *deg);
	void NumVerify(double *num);
	CString MonthName(int iMonth);
	CString BodyName(int iBody);
	CString BodyNameShort(int iBody);
	double StringToDecimal(CString value);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(convert)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~convert();

	// Generated message map functions
protected:
	//{{AFX_MSG(convert)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVERT_H__F0F4FAFC_8C38_4866_968C_8FBA536529CC__INCLUDED_)
