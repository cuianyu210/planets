// PlanetsDoc.cpp : implementation of the CPlanetsDoc class
//

#include "stdafx.h"
#include "resource.h"
#include "convert.h"
#include "Options.h"
#include <math.h>
#include <fstream>

#include "PlanetsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlanetsDoc

IMPLEMENT_DYNCREATE(CPlanetsDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlanetsDoc, CDocument)
	//{{AFX_MSG_MAP(CPlanetsDoc)
	ON_COMMAND(IDD_TIME_LOCATION, OnTimeLocation)
	ON_COMMAND(IDD_EQUINOXSOLSTICE, OnEquinoxsolstice)
	ON_COMMAND(IDD_ALMANAC, OnAlmanac)
	ON_COMMAND(ID_OPTIONS, OnOptions)
	ON_COMMAND(ID_TOOLS_PLANETS, OnToolsPlanets)
	//}}AFX_MSG_MAP
//	ON_COMMAND(ID_FILE_CLOSE, OnClose)
//ON_COMMAND(ID_FILE_CLOSE, &CPlanetsDoc::OnFileClose)
//ON_COMMAND(IDCLOSE, &CPlanetsDoc::OnIdclose)
//ON_COMMAND(IDCANCEL, &CPlanetsDoc::OnIdcancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlanetsDoc construction/destruction

CPlanetsDoc::CPlanetsDoc()
{
	// 	m_pModeless = NULL;
}

CPlanetsDoc::~CPlanetsDoc()
{
}

BOOL CPlanetsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	InitDocument();

	return TRUE;
}

//	Each of the lists has to be deleted individually
void CPlanetsDoc::DeleteContents()
{
	while (!m_strokeList.IsEmpty())
	{
		delete m_strokeList.RemoveHead();
	}

	while (!m_arcList.IsEmpty())
	{
		delete m_arcList.RemoveHead();
	}

	while (!m_ellipseList.IsEmpty())
	{
		delete m_ellipseList.RemoveHead();
	}

	while (!m_textList.IsEmpty())
	{
		delete m_textList.RemoveHead();
	}

	CDocument::DeleteContents();
}

void CPlanetsDoc::EraseContents()
{
	while (!m_strokeList.IsEmpty())
	{
		delete m_strokeList.RemoveHead();
	}

	while (!m_arcList.IsEmpty())
	{
		delete m_arcList.RemoveHead();
	}

	while (!m_ellipseList.IsEmpty())
	{
		delete m_ellipseList.RemoveHead();
	}

	while (!m_textList.IsEmpty())
	{
		delete m_textList.RemoveHead();
	}
}


void CPlanetsDoc::InitDocument()
{
	ReplacePen();
	ReplaceFill();
}

void CPlanetsDoc::ReplacePen()
{
	m_nPenWidth = 1;
	m_penCur.DeleteObject();
	m_penCur.CreatePen(PS_SOLID, m_nPenWidth, RGB(0, 0, 0));
}

void CPlanetsDoc::ReplaceFill()
{
	m_nFill = BS_HOLLOW;

	m_logBrushCur.lbStyle = m_nFill;
	m_logBrushCur.lbColor = RGB(0, 0, 0);
	m_logBrushCur.lbHatch = HS_CROSS;
	m_pBrushCur.CreateBrushIndirect(&m_logBrushCur);
}
/////////////////////////////////////////////////////////////////////////////
// CPlanetsDoc serialization

void CPlanetsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
	m_strokeList.Serialize(ar);
	m_arcList.Serialize(ar);
	m_ellipseList.Serialize(ar);
	m_textList.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CPlanetsDoc diagnostics

#ifdef _DEBUG
void CPlanetsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlanetsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPlanetsDoc commands

void CPlanetsDoc::OnToolsPlanets() 
{
	CWinApp* pApp = AfxGetApp();
	int top, left;
	CString sPlace;
	char buf1[40];
	CString sLocation;
	int iEOF;
	bool bHaveMatch = false;

	CComboBox* pLocation;
	CListBox* pConstellations;

	m_pModeless = new CTimeLocation(this);
	m_pModeless->Create(IDD_TIME_LOCATION, NULL);

	pConstellations = (CListBox*)m_pModeless->GetDlgItem(IDC_CONST_LIST);
	CPlanetsDoc::LoadConstListBox(pConstellations);
	pConstellations->SetSel(0, true);

// Set degrees HMS check box and all bodies to whatever is in profile
	CPlanetsDoc::SetCheckBoxes();

//	Get the list of names that are saved in the places.tap file
//	and add them to the Location list box
	pLocation = (CComboBox*)m_pModeless->GetDlgItem(IDC_LOCATION);
	sLocation = pApp->GetProfileString(_T("TimeLocation"), _T("location"), NULL);

	std::ifstream infile;
	infile.open("places.tap", std::ios::in );
	infile.getline(buf1, 40, '\n');

/*	COMBOBOXEXITEM  item;
	ZeroMemory(&item, sizeof(item));
	item.mask = CBEIF_TEXT;
	item.iItem = 0;
	item.pszText = LPWSTR("Hello");
//	item.pszText = LPWSTR (buf1);
*/
	iEOF = 0;
	int i = -1;
	while(iEOF == 0 )
	{
		i++;
		sPlace = buf1;
		if(sPlace != "")// if not null, add
		{
	//		item.pszText = LPWSTR(buf1);
//			top = pLocation->InsertItem(&item);
//			top = pLocation->InsertString(i, LPCTSTR(buf1));
//			pLocation->InsertString()
			top = pLocation->AddString(sPlace);
			if (sPlace == sLocation)
				bHaveMatch = true;
		}
//	cycle through the other information to get to the next place name
		infile.getline(buf1, 40, '\n');
	 	infile.getline(buf1, 40, '\n');
	 	infile.getline(buf1, 40, '\n');
	 	infile.getline(buf1, 40, '\n');
	 	infile.getline(buf1, 40, '\n');
	 	infile.getline(buf1, 40, '\n');
		iEOF = infile.eof();
	}
	infile.close();

	if (!bHaveMatch) {
		pApp->WriteProfileString(_T("TimeLocation"), _T("location"), _T(""));
		sLocation = "";
	}
//	Set the name to the one stored in profile
//	sLocation =	pApp->GetProfileString(_T("TimeLocation"), _T("location"), NULL);
	pLocation->SelectString(0, sLocation);
	if(sLocation != "")
	{
		m_pModeless->OnSelchangeLocation();
	}

//	fill time with current time
	m_pModeless->OnNow();

	left = pApp->GetProfileInt( _T ("TimeLocation"), _T("left"), 200);
	top = pApp->GetProfileInt( _T ("TimeLocation"), _T("top"), 0);

	m_pModeless->MoveWindow(left, top, 500, 600, true);
	m_pModeless->ShowWindow(SW_SHOW);
}

void CPlanetsDoc::LoadConstListBox(CListBox *pListBox)
{
	pListBox->AddString( _T ("All") );
	pListBox->AddString( _T ("Andromeda") );
	pListBox->AddString( _T ("Antlia") );
	pListBox->AddString( _T ("Apus") );
	pListBox->AddString( _T ("Aquarius") );
	pListBox->AddString( _T ("Aquila") );
	pListBox->AddString( _T ("Ara") );
	pListBox->AddString( _T ("Aries") );
	pListBox->AddString( _T ("Auriga") );
	pListBox->AddString( _T ("Bootes") );
	pListBox->AddString( _T ("Caelum") );
	pListBox->AddString( _T ("Camelopardalis") );
	pListBox->AddString( _T ("Cancer") );
	pListBox->AddString( _T ("Canes Venatici") );
	pListBox->AddString( _T ("Canis Major") );
	pListBox->AddString( _T ("Canis Minor") );
	pListBox->AddString( _T ("Capricornus") );
	pListBox->AddString( _T ("Carina") );
	pListBox->AddString( _T ("Cassiopeia") );
	pListBox->AddString( _T ("Centaurus") );
	pListBox->AddString( _T ("Cepheus") );
	pListBox->AddString( _T ("Cetus") );
	pListBox->AddString( _T ("Chamaleon") );
	pListBox->AddString( _T ("Circinus") );
	pListBox->AddString( _T ("Columba") );
	pListBox->AddString( _T ("Coma Berenices") );
	pListBox->AddString( _T ("Corona Australis") );
	pListBox->AddString( _T ("Corona Borealis") );
	pListBox->AddString( _T ("Corvus") );
	pListBox->AddString( _T ("Crater") );
	pListBox->AddString( _T ("Crux") );
	pListBox->AddString( _T ("Cygnus") );
	pListBox->AddString( _T ("Delphinus") );
	pListBox->AddString( _T ("Dorado") );
	pListBox->AddString( _T ("Draco") );
	pListBox->AddString( _T ("Equuleus") );
	pListBox->AddString( _T ("Eridanus") );
	pListBox->AddString( _T ("Fornax") );
	pListBox->AddString( _T ("Gemini") );
	pListBox->AddString( _T ("Grus") );
	pListBox->AddString( _T ("Hercules") );
	pListBox->AddString( _T ("Horologium") );
	pListBox->AddString( _T ("Hydra") );
	pListBox->AddString( _T ("Hydrus") );
	pListBox->AddString( _T ("Indus") );
	pListBox->AddString( _T ("Lacerta") );
	pListBox->AddString( _T ("Leo") );
	pListBox->AddString( _T ("Leo Minor") );
	pListBox->AddString( _T ("Lepus") );
	pListBox->AddString( _T ("Libra") );
	pListBox->AddString( _T ("Lupus") );
	pListBox->AddString( _T ("Lynx") );
	pListBox->AddString( _T ("Lyra") );
	pListBox->AddString( _T ("Mensa") );
	pListBox->AddString( _T ("Microscopium") );
	pListBox->AddString( _T ("Monoceros") );
	pListBox->AddString( _T ("Musca") );
	pListBox->AddString( _T ("Norma") );
	pListBox->AddString( _T ("Octans") );
	pListBox->AddString( _T ("Ophiucus") );
	pListBox->AddString( _T ("Orion") );
	pListBox->AddString( _T ("Pavo") );
	pListBox->AddString( _T ("Pegasus") );
	pListBox->AddString( _T ("Perseus") );
	pListBox->AddString( _T ("Phoenix") );
	pListBox->AddString( _T ("Pictor") );
	pListBox->AddString( _T ("Pisces") );
	pListBox->AddString( _T ("Pisces Austrinus") );
	pListBox->AddString( _T ("Puppis") );
	pListBox->AddString( _T ("Pyxis") );
	pListBox->AddString( _T ("Reticulum") );
	pListBox->AddString( _T ("Sagitta") );
	pListBox->AddString( _T ("Sagittarius") );
	pListBox->AddString( _T ("Scorpius") );
	pListBox->AddString( _T ("Sculptor") );
	pListBox->AddString( _T ("Scutum") );
	pListBox->AddString( _T ("Serpens") );
	pListBox->AddString( _T ("Sextans") );
	pListBox->AddString( _T ("Taurus") );
	pListBox->AddString( _T ("Telescopium") );
	pListBox->AddString( _T ("Triangulum") );
	pListBox->AddString( _T ("Triangulum Australe") );
	pListBox->AddString( _T ("Tucana") );
	pListBox->AddString( _T ("Ursa Major") );
	pListBox->AddString( _T ("Ursa Minor") );
	pListBox->AddString( _T ("Vela") );
	pListBox->AddString( _T ("Virgo") );
	pListBox->AddString( _T ("Volans") );
	pListBox->AddString( _T ("Vulpecula") );
}

void CPlanetsDoc::SetCheckBoxes()
{
    CWinApp* pApp = AfxGetApp();
	CButton *all, *output0, *output1, *output2;
	CButton *sun, *moon, *mercury, *venus, *earth;
	CButton *mars, *jup, *sat, *uranus, *nep, *pluto;

	all = (CButton*)m_pModeless->GetDlgItem(IDC_DO_ALL);
	output0 = (CButton*)m_pModeless->GetDlgItem(IDC_RADIO_DECIMAL);
	output1 = (CButton*)m_pModeless->GetDlgItem(IDC_RADIO_HMS);
	output2 = (CButton*)m_pModeless->GetDlgItem(IDC_RADIO_RADIAN);
	sun = (CButton*)m_pModeless->GetDlgItem(IDC_DO_SUN);
	moon = (CButton*)m_pModeless->GetDlgItem(IDC_DO_MOON);
	mercury = (CButton*)m_pModeless->GetDlgItem(IDC_DO_MERCURY);
	venus = (CButton*)m_pModeless->GetDlgItem(IDC_DO_VENUS);
	earth = (CButton*)m_pModeless->GetDlgItem(IDC_DO_EARTH);
	mars = (CButton*)m_pModeless->GetDlgItem(IDC_DO_MARS);
	jup = (CButton*)m_pModeless->GetDlgItem(IDC_DO_JUPITER);
	sat = (CButton*)m_pModeless->GetDlgItem(IDC_DO_SATURN);
	uranus = (CButton*)m_pModeless->GetDlgItem(IDC_DO_URANUS);
	nep = (CButton*)m_pModeless->GetDlgItem(IDC_DO_NEPTUNE);
	pluto = (CButton*)m_pModeless->GetDlgItem(IDC_DO_PLUTO);
	
	all->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("all"), 1));
	output0->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("output0"), 0));
	output1->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("output1"), 1));
	output2->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("output2"), 0));
	sun->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("sun"), 1));
	moon->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("moon"), 1));
	mercury->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("mercury"), 1));
	venus->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("venus"), 1));
	earth->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("earth"), 1));
	mars->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("mars"), 1));
	jup->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("jupiter"), 1));
	sat->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("saturn"), 1));
	uranus->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("uranus"), 1));
	nep->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("neptune"), 1));
	pluto->SetCheck(pApp->GetProfileInt( _T ("TimeLocation"), _T("pluto"), 1));
}

void CPlanetsDoc::OnEquinoxsolstice() 
{
    CWinApp* pApp = AfxGetApp();
	int top, left;

	m_pESModeless = new CEquinoxSolstice(this);
	m_pESModeless->Create(IDD_EQUINOXSOLSTICE, NULL);
	
	m_pESModeless->OnYear();

	left = pApp->GetProfileInt( _T ("EquinoxSolstice"), _T("left"), 200);
	top = pApp->GetProfileInt( _T ("EquinoxSolstice"), _T("top"), 0);

	m_pESModeless->MoveWindow(left, top, 408, 263, true);
	m_pESModeless->ShowWindow(SW_SHOW);
}

void CPlanetsDoc::OnAlmanac() 
{
    CWinApp* pApp = AfxGetApp();
	int top, left, iCalc;

	CListBox* pListBox;

	m_pAlModeless = new CAlmanac(this);
	m_pAlModeless->Create(IDD_ALMANAC, NULL);

	CPlanetsDoc::SetAlmanacCheckBoxes();

//	Load method list box with the available methods
	pListBox = (CListBox*)m_pAlModeless->GetDlgItem(IDC_ALMANAC_LIST);
	pListBox->AddString( _T ("Azimuth Altitude") );
	pListBox->AddString( _T ("Equatorial Apparent") );
	pListBox->AddString( _T ("Ecliptic Apparent Spherical") );
	pListBox->AddString( _T ("Ecliptic True Spherical") );
	pListBox->AddString( _T ("Ecliptic True Cartesian") );
	pListBox->AddString( _T ("Heliocentric Spherical") );
	pListBox->AddString( _T ("Heliocentric Cartesian") );
	pListBox->AddString( _T ("Rise, Set, Transit") );
	pListBox->AddString( _T ("GHA and Dec") );
	pListBox->AddString( _T ("Angular Separation") );
	pListBox->AddString( _T ("Magnetic Variation") );
	iCalc = pApp->GetProfileInt( _T ("Almanac"), _T("m_iCalc"), 0);
	pListBox->SetCurSel(iCalc);

//	if Angular separation is desired, fire up the geocentric/heliocentric
//	radio buttons
	if(iCalc == 9)
	{
		CButton* geoRadio = (CButton*)m_pAlModeless->GetDlgItem(IDC_GEO);
		CButton* helioRadio = (CButton*)m_pAlModeless->GetDlgItem(IDC_HELIO);
		geoRadio->ShowWindow(SW_SHOW);
		geoRadio->SetCheck(1);
		helioRadio->ShowWindow(SW_SHOW);
		helioRadio->SetCheck(0);
	}
	
	left = pApp->GetProfileInt( _T ("Almanac"), _T("left"), 200);
	top = pApp->GetProfileInt( _T ("Almanac"), _T("top"), 0);

	m_pAlModeless->MoveWindow(left, top, 520, 495, true);
	m_pAlModeless->ShowWindow(SW_SHOW);
}

void CPlanetsDoc::SetAlmanacCheckBoxes()
{
    CWinApp* pApp = AfxGetApp();
	CButton *almanac, *all, *aries, *output0, *output1, *output2;
	CButton *sun, *moon, *mercury, *venus, *earth;
	CButton *mars, *jup, *sat, *uranus, *nep, *pluto;

	output0 =	(CButton*)m_pAlModeless->GetDlgItem(IDC_DECIMAL_RADIO);
	output1 =	(CButton*)m_pAlModeless->GetDlgItem(IDC_DEGREE_RADIO);
	output2 =	(CButton*)m_pAlModeless->GetDlgItem(IDC_RADIAN_RADIO);
	almanac =	(CButton*)m_pAlModeless->GetDlgItem(IDC_ALMANAC);
	all		=	(CButton*)m_pAlModeless->GetDlgItem(IDC_ALL);
	aries	=	(CButton*)m_pAlModeless->GetDlgItem(IDC_ARIES);
	sun		=	(CButton*)m_pAlModeless->GetDlgItem(IDC_SUN);
	moon	=	(CButton*)m_pAlModeless->GetDlgItem(IDC_MOON);
	mercury =	(CButton*)m_pAlModeless->GetDlgItem(IDC_MERCURY);
	venus	=	(CButton*)m_pAlModeless->GetDlgItem(IDC_VENUS);
	earth	=	(CButton*)m_pAlModeless->GetDlgItem(IDC_EARTH);
	mars	=	(CButton*)m_pAlModeless->GetDlgItem(IDC_MARS);
	jup		=	(CButton*)m_pAlModeless->GetDlgItem(IDC_JUPITER);
	sat		=	(CButton*)m_pAlModeless->GetDlgItem(IDC_SATURN);
	uranus	=	(CButton*)m_pAlModeless->GetDlgItem(IDC_URANUS);
	nep		=	(CButton*)m_pAlModeless->GetDlgItem(IDC_NEPTUNE);
	pluto	=	(CButton*)m_pAlModeless->GetDlgItem(IDC_PLUTO);
	
	output0	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("output0")	, 0));
	output1	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("output1")	, 1));
	output2	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("output2"), 0));
	almanac	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("almanac"), 1));
	all		->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("all"), 0));
	aries	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("aries"), 1));
	sun		->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("sun"), 1));
	moon	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("moon"), 1));
	mercury	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("mercury"), 0));
	venus	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("venus"), 1));
	earth	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("earth"), 0));
	mars	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("mars"), 1));
	jup		->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("jupiter"), 1));
	sat		->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("saturn"), 1));
	uranus	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("uranus"), 0));
	nep		->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("neptune"), 0));
	pluto	->SetCheck(pApp->GetProfileInt( _T ("Almanac"), _T("pluto"), 0));
}

void CPlanetsDoc::OnOptions() 
{
    CWinApp* pApp = AfxGetApp();

	m_pOpModeless = new COptions(this);
	m_pOpModeless->Create(IDD_OPTIONS, NULL);

	m_pOpModeless->m_iPrecision = pApp->GetProfileInt( _T ("TimeLocation"), _T("precision"), 5);

	m_pOpModeless->ShowWindow(SW_SHOW);
}

void CPlanetsDoc::OnTimeLocation() 
{
	CPlanetsDoc::OnToolsPlanets();
}

CStroke* CPlanetsDoc::NewStroke()
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth, m_nFill);
	m_strokeList.AddTail(pStrokeItem);
	SetModifiedFlag();
	return pStrokeItem;
}

CStroke* CPlanetsDoc::NewArc()
{
	CStroke* pArcItem = new CStroke(m_nPenWidth, m_nFill);
	m_arcList.AddTail(pArcItem);
	SetModifiedFlag();
	return pArcItem;
}

CStroke* CPlanetsDoc::NewEllipse(UINT nFill)
{
	CStroke* pEllipseItem = new CStroke(m_nPenWidth, nFill);
	m_ellipseList.AddTail(pEllipseItem);
	SetModifiedFlag();
	return pEllipseItem;
}

CText* CPlanetsDoc::NewText()
{
	CText* pTextItem = new CText();
	m_textList.AddTail(pTextItem);
	SetModifiedFlag();
	return pTextItem;
}
//////////////////////////////////////////////////////////////////
//class CStroke
IMPLEMENT_SERIAL(CStroke, CObject, 1)
CStroke::CStroke()
{
}

CStroke::CStroke(UINT nPenWidth, UINT nFill)
{
	m_nPenWidth = nPenWidth;
	m_nFill = nFill;
}

void CStroke::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)m_nPenWidth;
		ar << (WORD)m_nFill;
		ar << m_iPenR;
		ar << m_iPenG;
		ar << m_iPenB;
		m_pointArray.Serialize(ar);
		m_arcArray.Serialize(ar);
		m_ellipseArray.Serialize(ar);
	}
	else
	{
		WORD w;
		ar >> w;
		m_nPenWidth = w;
		ar >> w;
		m_nFill = w;
		int r, g, b;
		ar>> r;
		ar>> g;
		ar>> b;
		m_iPenR = r;
		m_iPenG = g;
		m_iPenB = b;
		m_pointArray.Serialize(ar);
		m_arcArray.Serialize(ar);
		m_ellipseArray.Serialize(ar);
	}
}

BOOL CStroke::DrawStroke(CDC* pDC)
{
	CPen penStroke;
	if (!penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(m_iPenR, m_iPenG, m_iPenB)))
		return FALSE;
	CPen* pOldPen = pDC->SelectObject(&penStroke);
	pDC->SetMapMode(MM_LOENGLISH);
	pDC->MoveTo(m_pointArray[0]);
	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		pDC->LineTo(m_pointArray[i]);
	}
	pDC->SelectObject(pOldPen);
	return TRUE;
}

BOOL CStroke::DrawArc(CDC* pDC)
{
	CPen penStroke;
	if (!penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(m_iPenR, m_iPenG, m_iPenB)))
		return FALSE;
	CPen* pOldPen = pDC->SelectObject(&penStroke);
	pDC->SetMapMode(MM_LOENGLISH);

	pDC->Arc(m_arcArray[0], m_arcArray[1],
			 m_arcArray[2], m_arcArray[3],
			 m_arcArray[4], m_arcArray[5],
			 m_arcArray[6], m_arcArray[7]);

	pDC->SelectObject(pOldPen);
	return TRUE;
}

BOOL CStroke::DrawEllipse(CDC* pDC)
{
	CPen penStroke;
	CBrush pBrush;
	LOGBRUSH logBrush;

//	Make and selcect pen
	if (!penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(m_iPenR, m_iPenG, m_iPenB)))
		return FALSE;
	CPen* pOldPen = pDC->SelectObject(&penStroke);

//	Make and select brush
	logBrush.lbStyle = m_nFill;
	logBrush.lbColor = RGB(m_iPenR, m_iPenG, m_iPenB);
	logBrush.lbHatch = HS_CROSS;

	if (!pBrush.CreateBrushIndirect(&logBrush))
		return FALSE;

// Select the brush into the device context.
	CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&pBrush);
	
	pDC->SetMapMode(MM_LOENGLISH);

	pDC->Ellipse(m_ellipseArray[0], m_ellipseArray[1],
			 m_ellipseArray[2], m_ellipseArray[3]);

// Restore the original device context objects.
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	return TRUE;
}

//////////////////////////////////////////////////////////////////
//class CText
IMPLEMENT_SERIAL(CText, CObject, 1)
CText::CText()
{
}

void CText::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_iPenR;				//a
		ar << m_iPenG;				//b
		ar << m_iPenB;				//c
		ar << m_pTextOrig.x;		//d
		ar << m_pTextOrig.y;		//e
		ar << m_pTextLocation.x;	//f
		ar << m_pTextLocation.y;	//g
		ar << m_width;				//h
		ar << m_height;				//i
		ar << m_text;				//s1
		ar << m_font.nHeight;		//j
		ar << m_font.nWidth;		//k
		ar << m_font.nEscapement;	//l
		ar << m_font.nOrientation;	//m
		ar << m_font.nWeight;		//n
		ar << m_font.bItalic;		//b1
		ar << m_font.bUnderline;	//b2
		ar << m_font.cStrikeOut;	//b3
		ar << m_font.nCharSet;		//b4
		ar << m_font.nOutPrecision;	//b5
		ar << m_font.nClipPrecision;//b6
		ar << m_font.nQuality;		//b7
		ar << m_font.nPitchAndFamily;//b8
		ar << (CString)m_font.lpszFacename;//s2
	}
	else
	{
		int a, b, c, d, e, f, g, h, i, j, k, l, m, n;
		CString s1, s2;
		BYTE b1, b2, b3, b4, b5, b6, b7, b8;

		ar >> a;
		ar >> b;
		ar >> c;
		ar >> d;
		ar >> e;
		ar >> f;
		ar >> g;
		ar >> h;
		ar >> i;
		ar >> s1;
		ar >> j;
		ar >> k;
		ar >> l;
		ar >> m;
		ar >> n;
		ar >> b1;
		ar >> b2;
		ar >> b3;
		ar >> b4;
		ar >> b5;
		ar >> b6;
		ar >> b7;
		ar >> b8;
		ar >> s2;
		m_iPenR						= a;
		m_iPenG						= b;
		m_iPenB						= c;
		m_pTextOrig.x				= d;
		m_pTextOrig.y				= e;
		m_pTextLocation.x			= f;
		m_pTextLocation.y			= g;
		m_width						= h;
		m_height					= i;
		m_text						= s1;
		m_font.nHeight				= j;
		m_font.nWidth				= k;
		m_font.nEscapement			= l;
		m_font.nOrientation			= m;
		m_font.nWeight				= n;
		m_font.bItalic				= b1;
		m_font.bUnderline			= b2;
		m_font.cStrikeOut			= b3;
		m_font.nCharSet				= b4;
		m_font.nOutPrecision		= b5;
		m_font.nClipPrecision		= b6;
		m_font.nQuality				= b7;
		m_font.nPitchAndFamily		= b8;
		m_font.lpszFacename			= (LPCTSTR)s2;
	}
}

double CText::Distance(CPoint p1, CPoint p2)
{
	double dist;

	int xdif = p1.x - p2.x;
	int ydif = p1.y - p2.y;

	return dist = sqrt(xdif*xdif + ydif*ydif);
}


BOOL CText::WriteText(CDC* pDC)
{
	CFont wFont;

	pDC->SetMapMode(MM_LOENGLISH);
	VERIFY(wFont.CreateFont(
		m_font.nHeight,
		m_font.nWidth,
		m_font.nEscapement,
		m_font.nOrientation,
		m_font.nWeight,
		m_font.bItalic,
		m_font.bUnderline,
		m_font.cStrikeOut,
		m_font.nCharSet,
		m_font.nOutPrecision,
		m_font.nClipPrecision,
		m_font.nQuality,
		m_font.nPitchAndFamily,
		m_font.lpszFacename));

	CFont* def_font = pDC->SelectObject(&wFont);
	pDC->SetTextColor(RGB(m_iPenR, m_iPenG, m_iPenB));

	pDC->TextOut(m_pTextLocation.x, m_pTextLocation.y, m_text);

	pDC->SelectObject(def_font);

	wFont.DeleteObject();

	if(		!(m_pTextOrig.x == m_pTextLocation.x)
		||
			!(m_pTextOrig.y == m_pTextLocation.y))
	{
	//	In order to have line go from closest point on text to origin, find corner 
	//	that has shortest distance to origin.
		CArray<CPoint, CPoint> textPoints;
	//	Upper Left	= m_pTextLocation
		CPoint UR;
		CPoint LL;
		CPoint LR;
		CPoint toPoint;
		CPoint buf;

		UR.x = m_pTextLocation.x + m_width;
		UR.y = m_pTextLocation.y;
		LL.x = m_pTextLocation.x;
		LL.y = m_pTextLocation.y - m_height;
		LR.x = m_pTextLocation.x + m_width;
		LR.y = m_pTextLocation.y - m_height;

		textPoints.Add(m_pTextLocation);
		textPoints.Add(UR);
		textPoints.Add(LL);
		textPoints.Add(LR);

		double dist[4];
		dist[0] = Distance(m_pTextOrig, m_pTextLocation);
		dist[1] = Distance(m_pTextOrig, UR);
		dist[2] = Distance(m_pTextOrig, LL);
		dist[3] = Distance(m_pTextOrig, LR);

		double distMin = dist[0];
		buf = textPoints.GetAt(0);
		toPoint.x = buf.x;
		toPoint.y = buf.y;

		for(int i=1; i<4; i++)
		{
			if(dist[i] < distMin)
			{
				distMin = dist[i];
				buf = textPoints.GetAt(i);
				toPoint.x = buf.x;
				toPoint.y = buf.y;
			}
		}

		CPen newPen;
		CPen* pOldPen;

		newPen.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(0, 255, 0));
		pOldPen = pDC->SelectObject(&newPen);

		pDC->MoveTo(m_pTextOrig);
		pDC->LineTo(toPoint);

		pDC->SelectObject(pOldPen);
		newPen.DeleteObject();
	}
	
	return TRUE;
}


BOOL CPlanetsDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	InitDocument();
	return TRUE;
}


//void CPlanetsDoc::OnFileClose()
//{
//	int g = 3;
//	// TODO: Add your command handler code here
//}


//void CPlanetsDoc::OnIdclose()
//{
//	int g = 3;
//	// TODO: Add your command handler code here
//}


//void CPlanetsDoc::OnIdcancel()
//{
//	int y = 3;
//	// TODO: Add your command handler code here
//}
