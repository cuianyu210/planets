#if !defined(AFX_VARIATION_H__028F436E_C0A4_434F_B7E1_371F647DFFAC__INCLUDED_)
#define AFX_VARIATION_H__028F436E_C0A4_434F_B7E1_371F647DFFAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// variation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cvariation window

class Cvariation : public CWnd
{
// Construction
public:
	Cvariation();

// Attributes
public:

// Operations
public:
	#define NaN log(-1.0)
	#define FT2KM (1.0/0.0003048)
	#define PI 3.141592654
	#define RAD2DEG (180.0/PI)

	#ifndef SEEK_SET
	#define SEEK_SET 0
	#define SEEK_CUR 1
	#define SEEK_END 2
	#endif

	#define IEXT 0
	#define FALSE 0
	#define TRUE 1                  /* constants */
	#define RECL 81

	#define MAXINBUFF RECL+14

	/** Max size of in buffer **/

	#define MAXREAD MAXINBUFF-2
	/** Max to read 2 less than total size (just to be safe) **/

	#define MAXMOD 30
	/** Max number of models in a file **/

	#define PATH MAXREAD
	/** Max path and filename length **/

	#define EXT_COEFF1 (double)0
	#define EXT_COEFF2 (double)0
	#define EXT_COEFF3 (double)0

	#define MAXDEG 13
	#define MAXCOEFF (MAXDEG*(MAXDEG+2)+1) /* index starts with 1!, (from old Fortran?) */

/* Geomag global variables */
//	double gh1[200];
//	double gh2[200];
//	double gha[200];  
//	double ghb[200];
//	double d,f,h,i;
//	double dtemp,ftemp,htemp,itemp;
//	double x,y,z;
//	double xtemp,ytemp,ztemp;

	double gh1[MAXCOEFF];
	double gh2[MAXCOEFF];
	double gha[MAXCOEFF];              /* Geomag global variables */
	double ghb[MAXCOEFF];
//	double d=0,f=0,h=0,i=0;
	double d,f,h,i;
	double dtemp,ftemp,htemp,itemp;
//	double x=0,y=0,z=0;
	double x,y,z;
	double xtemp,ytemp,ztemp;

//	FILE *stream = NULL;                /* Pointer to specified model data file */// Overrides
	FILE *stream;                /* Pointer to specified model data file */// Overrides

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cvariation)
	//}}AFX_VIRTUAL

// Implementation
public:
	int		geomag(	int year, int month, int day, double latitude,
					double longitude, double *variation, double *dip,
					double *m_dMagneticHorizonatal, double *m_dMagneticNorth,
					double *m_dMagneticEast, double *m_dMagneticVertical,
					double *m_dMagneticTotal);
	double	degrees_to_decimal();
	double	julday(int month, int day, int year);
	int		interpsh(double date, double dte1, int nmax1, double dte2, int nmax2,
								 int gh);
	int		extrapsh(double date, double dte1, int nmax1, int nmax2, int gh);
	int		shval3(	int igdgc, double flat, double flon, double elev, int nmax,
								int gh, int iext, double ext1, double ext2, double ext3);
	int		dihf(int gh);
	int		safegets(char *buffer,int n);
	int		getshc(CString file, int iflag, long strec, int nmax_of_gh, int gh);
	virtual ~Cvariation();

	// Generated message map functions
protected:
	//{{AFX_MSG(Cvariation)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VARIATION_H__028F436E_C0A4_434F_B7E1_371F647DFFAC__INCLUDED_)
