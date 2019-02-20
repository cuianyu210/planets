#if !defined(AFX_MOON1_H__1CC3036B_682A_44C6_9401_AA5228147760__INCLUDED_)
#define AFX_MOON1_H__1CC3036B_682A_44C6_9401_AA5228147760__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Moon1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoon window

class CMoon : public CWnd
{
// Construction
public:
	CMoon();

// Attributes
public:
private:
	static double elp1[1024][5];
	static double elp2[919][5];
	static double elp3[705][5];
	static double elp4[348][7];
	static double elp5[317][7];
	static double elp6[238][7];
	static double elp7[15][6];
	static double elp8[12][6];
	static double elp9[9][6];
	static double elp10[14329][13];
	static double elp11[5234][13];
	static double elp12[6632][13];
	static double elp13[4385][11];
	static double elp14[834][11];
	static double elp15[1716][11];
	static double elp16[171][8];
	static double elp17[151][7];
	static double elp18[115][8];
	static double elp19[227][7];
	static double elp20[189][7];
	static double elp21[170][7];
	static double elp22[4][6];
	static double elp23[3][5];
	static double elp24[3][6];
	static double elp25[7][3];
	static double elp26[5][5];
	static double elp27[6][4];
	static double elp28[21][6];
	static double elp29[13][6];
	static double elp30[15][6];
	static double elp31[12][5];
	static double elp32[5][5];
	static double elp33[11][5];
	static double elp34[29][6];
	static double elp35[14][6];
	static double elp36[20][5];

// Operations
public:
	void geocentricSphericalTrueMoon(double julDay, double &moonL,
		 double &moonB, double &moonR);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoon)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMoon();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMoon)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOON1_H__1CC3036B_682A_44C6_9401_AA5228147760__INCLUDED_)
