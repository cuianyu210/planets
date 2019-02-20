// Options.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Options.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptions dialog


COptions::COptions(CPlanetsDoc* bob)
//COptions::COptions(CWnd* pParent /*=NULL*/)
//	: CDialog(COptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptions)
	m_iPrecision = 0;
	//}}AFX_DATA_INIT
}


void COptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptions)
	DDX_Text(pDX, IDC_PRECISION, m_iPrecision);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptions, CDialog)
	//{{AFX_MSG_MAP(COptions)
	ON_BN_CLICKED(IDC_DO, OnDo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptions message handlers

void COptions::OnOK() 
{
	CWinApp* pApp = AfxGetApp();

	UpdateData(true);
	pApp->WriteProfileInt( _T ("TimeLocation"), _T ("precision"), m_iPrecision);

	CDialog::OnOK();
}

void COptions::OnDo() 
{
//	convert bob;

	UpdateData(true);
//	m_sHMSOut = bob.HMSToString(m_dHMSIn, m_sType, m_iPrecision);
//	UpdateData(false);

//	bob.NumVerify(&m_dValue);
	
}

BOOL COptions::OnInitDialog() 
{
	CWinApp* pApp = AfxGetApp();

	CDialog::OnInitDialog();
	
	m_iPrecision = pApp->GetProfileInt( _T ("TimeLocation"), _T ("precision"), 5);

	UpdateData(false);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_OPT_PRECISION);
	pSpin->SetRange(0, 15);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptions::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}
