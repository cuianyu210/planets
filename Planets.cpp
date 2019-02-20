// Planets.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Planets.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "PlanetsDoc.h"
#include "PlanetsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlanetsApp

BEGIN_MESSAGE_MAP(CPlanetsApp, CWinApp)
	//{{AFX_MSG_MAP(CPlanetsApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnNewFile)
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlanetsApp construction

CPlanetsApp::CPlanetsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPlanetsApp object

CPlanetsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPlanetsApp initialization

BOOL CPlanetsApp::InitInstance()
{
	CPlanetsDoc newDoc;
	CRect winRect;
	int winMainWidth, winMainHeight;
	CWinApp* pApp = AfxGetApp();
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Sawyer Engineering Planets Program"));
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_PLANETTYPE,
		RUNTIME_CLASS(CPlanetsDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPlanetsView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	winRect.left = pApp->GetProfileInt(_T("WinMain"), _T("left"), 0);
	winRect.top = pApp->GetProfileInt(_T("WinMain"), _T("top"), 0);
	winRect.bottom = pApp->GetProfileInt(_T("WinMain"), _T("bottom"), 200);
	winRect.right = pApp->GetProfileInt(_T("WinMain"), _T("right"), 200);
	winMainWidth = winRect.right - winRect.left;
	winMainHeight = winRect.bottom - winRect.top;
	
	pMainFrame->MoveWindow(winRect.left,
						   winRect.top,
						   winMainWidth,
						   winMainHeight,
						   true);
	pMainFrame->UpdateWindow();


// Start with Time Location box open and showing
	newDoc.OnToolsPlanets();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPlanetsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPlanetsApp message handlers


void CPlanetsApp::OnNewFile()
{
	CWinApp::OnFileNew();
}
/*
void CPlanetsApp::OnFontSize()
{
	int t;

	t = 5;
//	CWinApp::OnFileNew();
}
*/
void CPlanetsApp::OnHelpFinder()
{
/*	CString msg;
	HWND pHwnd;
	char buffer[50];
	CString URL;
	CString tempURL;
	DWORD nSize = 50;
	int iPage;

	pHwnd = this->GetSafeHwnd();

	GetModuleFileName(NULL, buffer, nSize);
	tempURL = buffer;
	URL = tempURL.Left(1 + tempURL.ReverseFind(_T('\\')));// remove "Planets.exe" from string

//	iPage = this->GetActiveIndex();

//	if(0 == iPage)
//	{
	URL   += _T("Planets.chm::/htm/helpcontents1.htm");
//	}
//	else
//	{
//		URL   += _T("SurfaceWorks.chm::/htm/theoptionstab.htm");
//	}

	if( !::HtmlHelp( pHwnd, URL, HH_DISPLAY_TOPIC, 0 ))
	{
        ::AfxFormatString1( msg, IDS_HELP_URL_NOT_FOUND, URL ) ;
		::AfxMessageBox( msg ) ;
    }	
*/
}
