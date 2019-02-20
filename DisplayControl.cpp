// DisplayControl.cpp : implementation file
//

#include "stdafx.h"
#include "DisplayControl.h"
#include "convert.h"
#include "Validate.h"
#include "Star.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DisplayControl dialog


//DisplayControl::DisplayControl(CWnd* pParent /*=NULL*/)
//	: CDialog(DisplayControl::IDD, pParent)
CDisplayControl::CDisplayControl(CPlanetsView* bob)
{
	m_pPlanetsView = bob;
	//{{AFX_DATA_INIT(DisplayControl)
	m_sMagnitude = _T("");
	m_sViewDirection = _T("");
	//}}AFX_DATA_INIT
}


void CDisplayControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DisplayControl)
	DDX_Text(pDX, IDC_MAG_VALUE, m_sMagnitude);
	DDX_Text(pDX, IDC_VIEW_DIR, m_sViewDirection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDisplayControl, CDialog)
	//{{AFX_MSG_MAP(DisplayControl)
	ON_BN_CLICKED(IDC_SHOW_STARS, OnShowStars)
	ON_EN_CHANGE(IDC_MAG_VALUE, OnChangeMagValue)
	ON_BN_CLICKED(IDC_SHOW_CONS, OnShowCons)
	ON_BN_CLICKED(IDC_SHOW_CON_NAMES, OnShowConNames)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_SHOW_STAR_NAMES, OnShowStarNames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DisplayControl message handlers

BOOL CDisplayControl::OnInitDialog() 
{
//	char *stopstring;
	convert Convert;
	CWinApp* pApp = AfxGetApp();
	CDialog::OnInitDialog();

	CButton*	starsCheckBox;
	CButton*	starNamesCheckBox;
	CButton*	consCheckBox;
	CButton*	conNamesCheckBox;
	CEdit*		magnitude;
	CEdit*		viewDirection;
	CSliderCtrl*	magSlider;

	starsCheckBox =		(CButton*)GetDlgItem(IDC_SHOW_STARS);
	starNamesCheckBox =	(CButton*)GetDlgItem(IDC_SHOW_STAR_NAMES);
	consCheckBox =		(CButton*)GetDlgItem(IDC_SHOW_CONS);
	conNamesCheckBox =	(CButton*)GetDlgItem(IDC_SHOW_CON_NAMES);
	magnitude =			(CEdit*)GetDlgItem(IDC_MAG_VALUE);
	viewDirection =		(CEdit*)GetDlgItem(IDC_VIEW_DIR);
	magSlider =			(CSliderCtrl*)GetDlgItem(IDC_MAG_SLIDER);

	m_iWhichStars = m_pPlanetsView->m_pCStar->m_iWhichStars;

	switch(m_iWhichStars)
	{
	case IDS_MAGNITUDE_ONLY:
		starsCheckBox->SetCheck(1);
		consCheckBox->SetCheck(0);
		break;
	case IDS_CONSTELLATION_ONLY:
		starsCheckBox->SetCheck(0);
		consCheckBox->SetCheck(1);
		break;
	case IDS_MAGNITUDE_AND_CONSTELLATION:
		starsCheckBox->SetCheck(1);
		consCheckBox->SetCheck(1);
		break;
	}
	m_iShowStars = starsCheckBox->GetCheck();
	m_iShowCons = consCheckBox->GetCheck();

	starNamesCheckBox->SetCheck(m_pPlanetsView->m_pCStar->m_iStarNames);
	conNamesCheckBox->SetCheck(m_pPlanetsView->m_pCStar->m_iConNames);
	m_iShowConNames = conNamesCheckBox->GetCheck();
	m_iShowStarNames = starNamesCheckBox->GetCheck();
	
	m_sMagnitude = m_pPlanetsView->m_pCStar->m_sMagnitude;
//	m_dMagnitude = strtod(m_sMagnitude, &stopstring);
	m_dMagnitude = _tstof(m_sMagnitude);
	m_sViewDirection = m_pPlanetsView->m_pCStar->m_sViewDirection;
	m_iViewDirection = _ttoi(m_pPlanetsView->m_pCStar->m_sViewDirection);
	m_dViewDirection = (double)m_iViewDirection * Convert.Pi() / 180.0;

	magSlider->SetRange(-1, 8, TRUE);
	magSlider->SetPos(static_cast<int>(floor(m_dMagnitude)));

	UpdateData(false);
	CDisplayControl::SetConButtons();
	CDisplayControl::SetStarButtons();

return TRUE;  // return TRUE unless you set the focus to a control
	          // EXCEPTION: OCX Property Pages should return FALSE
}

void CDisplayControl::SetWhichStars()
{
	CButton*	starsCheckBox;
	CButton*	consCheckBox;
	int sum;

	starsCheckBox =	(CButton*)GetDlgItem(IDC_SHOW_STARS);
	consCheckBox =	(CButton*)GetDlgItem(IDC_SHOW_CONS);

	sum = 0;
	sum += starsCheckBox->GetCheck();
	sum += consCheckBox->GetCheck() * 2;
	
	switch(sum)
	{
	case 1:
		m_iWhichStars = IDS_MAGNITUDE_ONLY;
		break;
	case 2:
		m_iWhichStars = IDS_CONSTELLATION_ONLY;
		break;
	case 3:
		m_iWhichStars = IDS_MAGNITUDE_AND_CONSTELLATION;
		break;
	}

}

void CDisplayControl::SetStarButtons() 
{
	CButton* pStar;
	CButton* pConst;
	
	pStar =		(CButton*)GetDlgItem(IDC_SHOW_STARS);
	pConst =	(CButton*)GetDlgItem(IDC_SHOW_CONS);

	if(0 == pStar->GetCheck() )
	{
		if( 1 == pConst->GetCheck() )
		{
			m_iShowStars = 0;
		}
		else
		{
			pStar->SetCheck(true);
		}
	}
	else
	{
		m_iShowStars = 1;
	}
}

void CDisplayControl::OnShowStars() 
{
	// display 'working' in control window
	m_pPlanetsView->ShowWorking(SW_SHOW);

	SetStarButtons();
	SetWhichStars();
	m_pPlanetsView->RefreshScreen();

	// turn 'working' off
	m_pPlanetsView->ShowWorking(SW_HIDE);
}

void CDisplayControl::SetStarNamesMember() 
{
	CButton*	starNamesCheckBox;

	starNamesCheckBox =	(CButton*)GetDlgItem(IDC_SHOW_STAR_NAMES);
	m_iShowStarNames = starNamesCheckBox->GetCheck();
}

void CDisplayControl::OnShowStarNames() 
{
	// display 'working' in control window
	m_pPlanetsView->ShowWorking(SW_SHOW);

	SetStarNamesMember();
	m_pPlanetsView->RefreshScreen();

	// turn 'working' off
	m_pPlanetsView->ShowWorking(SW_HIDE);
}

void CDisplayControl::OnChangeMagValue()
{
	CSliderCtrl* slider;
	int iMag;
//	char *stopstring;

	// display 'working' in control window
	m_pPlanetsView->ShowWorking(SW_SHOW);

	UpdateData(true);
	
	iMag = _ttoi(m_sMagnitude);
//	m_dMagnitude = strtod(m_sMagnitude, &stopstring);
	m_dMagnitude = +_tstof(m_sMagnitude);
	slider = (CSliderCtrl*)GetDlgItem(IDC_MAG_SLIDER);
	slider->SetPos(iMag);
	UpdateData(false);
	m_pPlanetsView->RefreshScreen();

	// turn 'working' off
	m_pPlanetsView->ShowWorking(SW_HIDE);
}

void CDisplayControl::SetConButtons() 
{
	CButton* pConst;
	CButton* pStar;
	CButton* pConstNames;
	
	pConst = (CButton*)GetDlgItem(IDC_SHOW_CONS);
	pStar =		(CButton*)GetDlgItem(IDC_SHOW_STARS);
	pConstNames = (CButton*)GetDlgItem(IDC_SHOW_CON_NAMES);

	if(0 == pConst->GetCheck())
	{
		if(1 == pStar->GetCheck() )
		{
			pConstNames->EnableWindow(false);
			m_iShowCons = 0;
		}
		else
		{
			pConst->SetCheck(true);
		}
	}
	else
	{
		pConstNames->EnableWindow(true);
		m_iShowCons = 1;
	}
}

void CDisplayControl::OnShowCons() 
{
	// display 'working' in control window
	m_pPlanetsView->ShowWorking(SW_SHOW);

	SetConButtons();
	SetWhichStars();
	m_pPlanetsView->RefreshScreen();

	// turn 'working' off
	m_pPlanetsView->ShowWorking(SW_HIDE);
}


void CDisplayControl::SetConNamesMember() 
{
	CButton*	conNamesCheckBox;

	conNamesCheckBox =	(CButton*)GetDlgItem(IDC_SHOW_CON_NAMES);
	m_iShowConNames = conNamesCheckBox->GetCheck();
}

void CDisplayControl::OnShowConNames() 
{
	// display 'working' in control window
	m_pPlanetsView->ShowWorking(SW_SHOW);

	SetConNamesMember();
	m_pPlanetsView->RefreshScreen();

	// turn 'working' off
	m_pPlanetsView->ShowWorking(SW_HIDE);
}

void CDisplayControl::UpdateViewDirection(double NewValue)
{
	convert bob;

	NewValue = NewValue * 180.0 / bob.Pi();
	m_iViewDirection = (int)floor(NewValue);
	m_sViewDirection.Format(_T("%d"), m_iViewDirection);

	UpdateData(false);
	UpdateWindow();
}

//  This is for the View Direction button
void CDisplayControl::OnOK() 
{
	convert bob;

	// display 'working' in control window
	m_pPlanetsView->ShowWorking(SW_SHOW);

	UpdateData(true);

	m_iViewDirection = _ttoi(m_sViewDirection);
	m_dViewDirection = (double)m_iViewDirection * bob.Pi() / 180.0;

	if(m_iViewDirection >= 0 || m_iViewDirection <= 360)
	{
		class CPlanetsDoc* pDoc = m_pPlanetsView->GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->EraseContents();
	
		m_pPlanetsView->RefreshScreen();
	}

	// turn 'working' off
	m_pPlanetsView->ShowWorking(SW_HIDE);
}

void CDisplayControl::OnSliderMove(CScrollBar* pScrollBar)
{
	int pos;
	CSliderCtrl* bob;
	bob = (CSliderCtrl*) pScrollBar;

	// display 'working' in control window
	m_pPlanetsView->ShowWorking(SW_SHOW);

	pos = bob->GetPos();
	m_dMagnitude = (double)pos;
	m_sMagnitude.Format(_T("%.0f"), m_dMagnitude);
	UpdateData(false);
	m_pPlanetsView->RefreshScreen();

	// turn 'working' off
	m_pPlanetsView->ShowWorking(SW_HIDE);
}

void CDisplayControl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int i, err;
	CSliderCtrl* slider;
	
	slider = (CSliderCtrl*) pScrollBar;
	i = slider->GetPos();
	switch(nSBCode)
	{
	case TB_BOTTOM:  // VK_END
		i = 1;
		break;
	case TB_ENDTRACK:  // WM_KEYUP (the user released a key that sent a relevant virtual-key code) 
		i = 1;
		break;
	case TB_LINEDOWN:  // VK_RIGHT or VK_DOWN
		i = 1;
		break;
	case TB_LINEUP:  // VK_LEFT or VK_UP
		i = 1;
		break;
	case TB_PAGEDOWN:  // VK_NEXT (the user clicked the channel below or to the right of the slider)
		i = 1;
		CDisplayControl::OnSliderMove(pScrollBar);
		break;
	case TB_PAGEUP:  // VK_PRIOR (the user clicked the channel above or to the left of the slider)
		i = 1;
		CDisplayControl::OnSliderMove(pScrollBar);
		break;
	case TB_THUMBPOSITION:  // WM_LBUTTONUP following a TB_THUMBTRACK notification message
		i = 1;
		CDisplayControl::OnSliderMove(pScrollBar);
		break;
	case TB_THUMBTRACK:  // Slider movement (the user dragged the slider)
		//  LS 31 Jan 2019
		//  increased to allow for null termination and in _itoa_s call below
		char buffer[4];
		int pos;
//		CEdit* magnitude;
		CSliderCtrl* slide;
		
//		magnitude = (CEdit*)GetDlgItem(IDC_MAG_VALUE);
		slide = (CSliderCtrl*)GetDlgItem(IDC_MAG_SLIDER);

		pos = slide->GetPos();
//		m_sMagnitude = _itoa(pos, buffer, 10);
		err = _itoa_s(pos, buffer, 4, 10);
		m_sMagnitude = buffer;
		UpdateData(false);

		
		break;
	case TB_TOP:  // VK_HOME
		i = 1;
		break;
	}
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CDisplayControl::PreTranslateMessage(MSG* pMsg) 
{
	UINT uMess;
	int i;

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
			case IDC_MAG_VALUE:
				{
					if(!tom.validateChar(IDS_EDIT_BOX_DOUBLE, wParam))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int lo, hi, gLength;
					CString g;

					CEdit* mag = (CEdit*)GetDlgItem(IDC_MAG_VALUE);
					mag->GetSel(lo, hi);
					mag->GetWindowText(g);
					gLength = g.GetLength();

					// we have the whole field, so replace with this character (wParam)
					// which means do nothing here since handled above, but do not go to
					// validateField() unless is number
					if(0 == lo && gLength == hi)
					{
						if(wParam == 0x002d)  /* VK_INSERT  */
							break;
					}
	
					//This is needed because CEdit does not update until after PreTranslate()
					CString newField = g.Left(lo);
					newField += wchar_t(wParam);
					newField += g.Right(gLength - hi);

					if(!tom.validateField(IDS_EDIT_BOX_DOUBLE, newField))
					{
						pMsg->wParam = 0x0;
						break;
					}

//					double val = atof(newField);
					double val = _tstof(newField);
					if(!tom.validateMagnitude(val) )
					{
						pMsg->wParam = 0x0;
						break;
					}
	
					break;
				}
			case IDC_VIEW_DIR:
				{
					if(!tom.validateChar(IDS_EDIT_BOX_INT, wParam))
					{
						pMsg->wParam = 0x0;
						break;
					}

					int lo, hi, gLength;
					CString g;

					CEdit* mag = (CEdit*)GetDlgItem(IDC_VIEW_DIR);
					mag->GetSel(lo, hi);
					mag->GetWindowText(g);
					gLength = g.GetLength();

					// we have the whole field, so replace with this character (wParam)
					// which means do nothing here since handled above, but do not go to
					// validateField() unless is number
					if(0 == lo && gLength == hi)
					{
						if(wParam == 0x002d)  /* VK_INSERT  */
							break;
					}
	
					//This is needed because CEdit does not update until after PreTranslate()
					CString newField = g.Left(lo);
					newField += wchar_t(wParam);
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