// StarBox.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "StarBox.h"
#include "Validate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStarBox dialog


CStarBox::CStarBox(CWnd* pParent /*=NULL*/)
	: CDialog(CStarBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStarBox)
	m_sMagnitude = _T("");
	m_sViewDirection = _T("");
	//}}AFX_DATA_INIT
}


void CStarBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStarBox)
	DDX_Text(pDX, IDC_MAGNITUDE, m_sMagnitude);
	DDX_Text(pDX, IDC_STAR_VIEW_DIR, m_sViewDirection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStarBox, CDialog)
	//{{AFX_MSG_MAP(CStarBox)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STAR_TO_FILE, OnStarToFile)
	ON_BN_CLICKED(IDC_VMAG, OnVmag)
	ON_BN_CLICKED(IDC_CONSTELLATION, OnConstellation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStarBox message handlers

void CStarBox::OnClose() 
{
	CWinApp* pApp = AfxGetApp();
	CRect winRect;
	CButton* vmag;
	CButton* constellation;
	CButton* starNames;
	CButton* conNames;
	CButton* fileCheck;
	CEdit* starFileName;
	CEdit* magnitude;
	CEdit* viewDir;
	CString sStarFileName;
	CString sMagnitude;
	CString sVDir;

	vmag			= (CButton*)GetDlgItem(IDC_VMAG);
	constellation	= (CButton*)GetDlgItem(IDC_CONSTELLATION);
	starNames		= (CButton*)GetDlgItem(IDC_STAR_NAMES);
	conNames		= (CButton*)GetDlgItem(IDC_CONST_NAMES);
	fileCheck		= (CButton*)GetDlgItem(IDC_STAR_TO_FILE);
	starFileName	= (CEdit*)GetDlgItem(IDC_STAR_FILENAME);
	magnitude		= (CEdit*)GetDlgItem(IDC_MAGNITUDE);
	viewDir			= (CEdit*)GetDlgItem(IDC_STAR_VIEW_DIR);

//	UpdateData(true);//for view direction//
	starFileName->GetWindowText(sStarFileName);
	magnitude->GetWindowText(sMagnitude);
	viewDir->GetWindowText(sVDir);

	GetWindowRect(&winRect);
	pApp->WriteProfileInt( _T ("StarBox"), _T ("top"), winRect.top);
	pApp->WriteProfileInt( _T ("StarBox"), _T ("left"), winRect.left);
	pApp->WriteProfileInt( _T ("StarBox"), _T ("vmag"), vmag->GetCheck());
	pApp->WriteProfileInt( _T ("StarBox"), _T ("constellation"), constellation->GetCheck());
	pApp->WriteProfileInt( _T ("StarBox"), _T ("starnames"), starNames->GetCheck());
	pApp->WriteProfileInt( _T ("StarBox"), _T ("connames"), conNames->GetCheck());
	pApp->WriteProfileInt( _T ("StarBox"), _T ("startofile"), fileCheck->GetCheck());
	pApp->WriteProfileString( _T ("StarBox"), _T ("viewdirection"), sVDir);
	pApp->WriteProfileString( _T ("StarBox"), _T ("starfilename"), sStarFileName);
	pApp->WriteProfileString( _T ("StarBox"), _T ("magnitude"), sMagnitude);

	CDialog::OnClose();
}

void CStarBox::OnDestroy() 
{
	CButton* vmag;
	CButton* constellation;
	CButton* starNames;
	CButton* conNames;
	CButton* fileCheck;
	CEdit* starFileName;
	CEdit* magnitude;
	CEdit* viewDir;
	int iVmag, iConst, iStarNames, iConNames, iStarToFile;
	CString sStarFileName;
	CString sMagnitude;
	CString sVDir;

	vmag = (CButton*)GetDlgItem(IDC_VMAG);
	constellation = (CButton*)GetDlgItem(IDC_CONSTELLATION);
	starNames = (CButton*)GetDlgItem(IDC_STAR_NAMES);
	conNames = (CButton*)GetDlgItem(IDC_CONST_NAMES);
	fileCheck = (CButton*)GetDlgItem(IDC_STAR_TO_FILE);
	starFileName = (CEdit*)GetDlgItem(IDC_STAR_FILENAME);
	magnitude = (CEdit*)GetDlgItem(IDC_MAGNITUDE);
	viewDir = (CEdit*)GetDlgItem(IDC_STAR_VIEW_DIR);

	iVmag = vmag->GetCheck();
	iConst = constellation->GetCheck();
	iStarNames = starNames->GetCheck();
	iConNames = conNames->GetCheck();
	iStarToFile = fileCheck->GetCheck();
	starFileName->GetWindowText(sStarFileName);
	magnitude->GetWindowText(sMagnitude);
	viewDir->GetWindowText(sVDir);

	CDialog::OnDestroy();
	
	CWinApp* pApp = AfxGetApp();
	CRect winRect;

	GetWindowRect(&winRect);
	pApp->WriteProfileInt( _T ("StarBox"), _T ("top"), winRect.top);
	pApp->WriteProfileInt( _T ("StarBox"), _T ("left"), winRect.left);
	pApp->WriteProfileInt( _T ("StarBox"), _T ("vmag"), iVmag);
	pApp->WriteProfileInt( _T ("StarBox"), _T ("constellation"), iConst);
	pApp->WriteProfileInt( _T ("StarBox"), _T ("starnames"), iStarNames);
	pApp->WriteProfileInt( _T ("StarBox"), _T ("connames"), iConNames);
	pApp->WriteProfileInt( _T ("StarBox"), _T ("startofile"), iStarToFile);
	pApp->WriteProfileString( _T ("StarBox"), _T ("viewdirection"), sVDir);
	pApp->WriteProfileString( _T ("StarBox"), _T ("starfilename"), sStarFileName);
	pApp->WriteProfileString( _T ("StarBox"), _T ("magnitude"), sMagnitude);
}

void CStarBox::OnOK() 
{
	CButton* vmag;
	CButton* constellation;
	CButton* starNames;
	CButton* conNames;
	CButton* fileCheck;
	CEdit* starFileName;
//	CEdit* magnitude;

	m_iBoxValue = 0;

	vmag = (CButton*)GetDlgItem(IDC_VMAG);
	constellation = (CButton*)GetDlgItem(IDC_CONSTELLATION);
	starNames = (CButton*)GetDlgItem(IDC_STAR_NAMES);
	conNames = (CButton*)GetDlgItem(IDC_CONST_NAMES);
	fileCheck = (CButton*)GetDlgItem(IDC_STAR_TO_FILE);
	starFileName = (CEdit*)GetDlgItem(IDC_STAR_FILENAME);
	UpdateData(true);//for view direction//

	m_iBoxValue += vmag->GetCheck();
	m_iBoxValue += constellation->GetCheck() * 2;
	
	m_iStarNames = starNames->GetCheck();
	m_iConNames = conNames->GetCheck();

	m_iStarToFile = fileCheck->GetCheck();
	starFileName->GetWindowText(m_sStarFileName);

	CDialog::OnOK();
}

BOOL CStarBox::OnInitDialog() 
{
	CWinApp* pApp = AfxGetApp();
	CDialog::OnInitDialog();
	
	CButton* vmag;
	CButton* constellation;
	CButton* starNames;
	CButton* conNames;
	CButton* fileCheck;
	CEdit* starFileName;

	CString sMag;
	CString sViewDir;

	vmag = (CButton*)GetDlgItem(IDC_VMAG);
	constellation = (CButton*)GetDlgItem(IDC_CONSTELLATION);
	starNames = (CButton*)GetDlgItem(IDC_STAR_NAMES);
	conNames = (CButton*)GetDlgItem(IDC_CONST_NAMES);
	fileCheck = (CButton*)GetDlgItem(IDC_STAR_TO_FILE);
	starFileName = (CEdit*)GetDlgItem(IDC_STAR_FILENAME);

	vmag->SetCheck(pApp->GetProfileInt( _T ("StarBox"), _T ("vmag"), 1));
	constellation->SetCheck(pApp->GetProfileInt( _T ("StarBox"), _T ("constellation"), 0));
	starNames->SetCheck(pApp->GetProfileInt( _T ("StarBox"), _T ("starnames"), 0));
	conNames->SetCheck(pApp->GetProfileInt( _T ("StarBox"), _T ("connames"), 0));
	fileCheck->SetCheck(pApp->GetProfileInt( _T ("StarBox"), _T ("startofile"), 1));

	starFileName->SetWindowText(pApp->GetProfileString( _T ("StarBox"), _T ("starfilename"), _T ("star.txt")));
	m_sMagnitude = pApp->GetProfileString( _T ("StarBox"), _T ("magnitude"), _T ("3.0"));

	m_sViewDirection = pApp->GetProfileString( _T ("StarBox"), _T ("viewdirection"), _T ("0"));
	UpdateData(false);
	CStarBox::OnStarToFile();
	CStarBox::OnVmag();
	CStarBox::OnConstellation();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStarBox::OnStarToFile() 
{
	CButton* fileCheck;
	CEdit* starFileName;
	
	fileCheck = (CButton*)GetDlgItem(IDC_STAR_TO_FILE);
	starFileName = (CEdit*)GetDlgItem(IDC_STAR_FILENAME);

	if(0 == fileCheck->GetCheck())
	{
		starFileName->EnableWindow(false);
	}
	else
	{
		starFileName->EnableWindow(true);
	}
}

void CStarBox::OnVmag() 
{
	CButton* pMag;
	CEdit* pMagValue;
	
	pMag = (CButton*)GetDlgItem(IDC_VMAG);
	pMagValue = (CEdit*)GetDlgItem(IDC_MAGNITUDE);

	if(0 == pMag->GetCheck())
	{
		pMagValue->EnableWindow(false);
	}
	else
	{
		pMagValue->EnableWindow(true);
	}
}

void CStarBox::OnConstellation() 
{
	CButton* pConst;
	CButton* pConstNames;
	
	pConst = (CButton*)GetDlgItem(IDC_CONSTELLATION);
	pConstNames = (CButton*)GetDlgItem(IDC_CONST_NAMES);

	if(0 == pConst->GetCheck())
	{
		pConstNames->EnableWindow(false);
	}
	else
	{
		pConstNames->EnableWindow(true);
	}
}


BOOL CStarBox::PreTranslateMessage(MSG* pMsg) 
{
	UINT uMess;
	int i;

	// The top WM messages are here for debugging purposes only
	uMess = pMsg->message;

	
	switch(uMess)
	{
	case WM_PAINT:
		i = 1;
		break;
	case WM_NCMOUSEMOVE:
		i = 1;
		break;
	case WM_MOUSEFIRST:
		i = 1;
		break;
	case WM_LBUTTONDOWN:
		i = 1;
		break;
	case WM_LBUTTONUP:
		i = 1;
		break;
	case 0x0118: // WM_SYSTIMER
		i = 1;
		break;
	case WM_CHAR:
		// first validate character, then see if field makes sense

		CValidate tom;
		int wParam;
		UINT t;

		CWnd* mif = this->GetFocus();
		t = mif->GetDlgCtrlID();
		wParam = pMsg->wParam;

		if(wParam != VK_BACK)
		{
			switch(t)
			{
			case IDC_MAGNITUDE:
				{

					if(!tom.validateChar(IDS_EDIT_BOX_DOUBLE, wParam))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int lo, hi, gLength;
					CString g;

					CEdit* mag = (CEdit*)GetDlgItem(IDC_MAGNITUDE);
					mag->GetSel(lo, hi);
					mag->GetWindowText(g);
					gLength = g.GetLength();

					// we have the whole field, so replace with this character (wParam)
					// which means do nothing here since handled above, but do not go to
					// validateField() unless is number
					if(0 == lo && gLength == hi)
					{
						if(wParam == 0x002d)
							break;
					}
	
					//This is needed because CEdit does not update until after PreTranslate()
					CString newField = g.Left(lo);
					newField = newField + (wchar_t)wParam;

					newField += g.Right(gLength - hi);

					if(!tom.validateField(IDS_EDIT_BOX_DOUBLE, newField))
					{
						pMsg->wParam = 0x0;
						break;
					}

					double val = _tstof(newField);
					if(!tom.validateMagnitude(val) )
					{
						pMsg->wParam = 0x0;
						break;
					}
	
					break;
				}
			case IDC_STAR_VIEW_DIR:
				{
					if(!tom.validateChar(IDS_EDIT_BOX_INT, wParam))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int lo, hi, gLength;
					CString g;

					CEdit* mag = (CEdit*)GetDlgItem(IDC_STAR_VIEW_DIR);
					mag->GetSel(lo, hi);
					mag->GetWindowText(g);
					gLength = g.GetLength();

					// we have the whole field, so replace with this character (wParam)
					// which means do nothing here since handled above, but do not go to
					// validateField() unless is number
					if(0 == lo && gLength == hi)
					{
						if(wParam == 0x002d)
							break;
					}
	
					//This is needed because CEdit does not update until after PreTranslate()
					CString newField = g.Left(lo);
					newField += (wchar_t)wParam;
					newField += g.Right(gLength - hi);

					if(!tom.validateField(IDS_EDIT_BOX_INT, newField))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int val = _ttoi(newField);
					if(!tom.validateViewDir(val) )
					{
						pMsg->wParam = 0x0;
						break;
					}
	
					break;
				}
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);

}