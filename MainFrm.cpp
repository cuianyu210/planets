// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
//	ON_COMMAND(ID_FILE_CLOSE, &CMainFrame::OnFileClose)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

//	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
//		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
//		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
//	{
//		TRACE0("Failed to create toolbar\n");
//		return -1;      // fail to create
//	}
	if (!CreateToolBar())
	{
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL CMainFrame::CreateToolBar()
{
	const int nDropHeight = 100;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;       // fail to create
	}

// Create the combo box

	// Design guide advises 12 pixel gap between combos and buttons
	m_wndToolBar.SetButtonInfo(6, IDS_FONT_SIZE, TBBS_SEPARATOR, 52);
	CRect rect;
	m_wndToolBar.GetItemRect(6, &rect);
	rect.left += 3;
	rect.bottom = rect.top + nDropHeight;
	if (!m_comboBox.Create(
			CBS_DROPDOWNLIST|WS_VISIBLE|WS_TABSTOP,
			rect, &m_wndToolBar, IDS_FONT_SIZE))
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}

	//  Fill the combo box and set to 12
	CString szStyle;
	if (szStyle.LoadString(IDS_FONT_6))
		m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_FONT_8))
		m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_FONT_10))
		m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_FONT_12))
		m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_FONT_14))
		m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_FONT_16))
		m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_FONT_18))
		m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_FONT_20))
		m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_FONT_22))
		m_comboBox.AddString((LPCTSTR)szStyle);
	CWinApp* pApp = AfxGetApp();
	m_comboBox.SetCurSel(pApp->GetProfileInt(_T("Toolbar"), _T("fontposition"), 3));

	//  Create a font for the combobox
	LOGFONT logFont;
	memset(&logFont, 0, sizeof(logFont));

	if (!::GetSystemMetrics(SM_DBCSENABLED))
	{
		// Since design guide says toolbars are fixed height so is the font.
		logFont.lfHeight = -12;
		logFont.lfWeight = FW_BOLD;
		logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
		CString strDefaultFont;
		strDefaultFont.LoadString(IDS_DEFAULT_FONT);
		lstrcpy(logFont.lfFaceName, strDefaultFont);
		if (!m_font.CreateFontIndirect(&logFont)) {
			TRACE0("Could Not create font for combo\n");
		}
		else {
			m_comboBox.SetFont(&m_font);
		}
	}
	else
	{
		m_font.Attach(::GetStockObject(SYSTEM_FONT));
		m_comboBox.SetFont(&m_font);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnClose() 
{
	CRect winRect;
	CWinApp* pApp = AfxGetApp();

	GetWindowRect(&winRect);
	pApp->WriteProfileInt(_T("WinMain"), _T("left"), winRect.left);
	pApp->WriteProfileInt(_T("WinMain"), _T("top"), winRect.top);
	pApp->WriteProfileInt(_T("WinMain"), _T("right"), winRect.right);
	pApp->WriteProfileInt(_T("WinMain"), _T("bottom"), winRect.bottom);
	
	CMDIFrameWnd::OnClose();
}


//void CMainFrame::OnFileClose()
//{
//	int y = 3;
//	// TODO: Add your command handler code here
//}
